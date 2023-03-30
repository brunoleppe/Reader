#include <xc.h>
#include "bsp.h"
#include "board_defs.h"
#include "hal.h"
#include "Drivers/SPI/spi_driver.h"
#include "debug.h"
#include "bitmap.h"
#include "lcd.h"
#include "FreeRTOS.h"
#include "task.h"
#include "keypad.h"

typedef struct{
    GPIO_PinMap pinMap;
    int delay_ms;
}PinParams;

static const PinParams pinParamsLed1 = {
        .pinMap = LED1,
        .delay_ms = 500
};
static const PinParams pinParamsLed2 = {
        .pinMap = LED2,
        .delay_ms = 500
};


static GPIO_CALLBACK_OBJECT pinCallbackObj[] = {
        {.pin = QT_CHANGE, 0, 0}
};

static SpiClientObject spiDriverInstance0_clientArray[SPI_DRIVER_INSTANCE_0_CLIENTS];
static SpiDriverInit   spiDriverInstance0_init = {
    .nClientsMax = SPI_DRIVER_INSTANCE_0_CLIENTS,
    .spiChannel = QT_SPI_CHANNEL,
    .clientArray = spiDriverInstance0_clientArray,
};

static SpiClientObject spiDriverInstance1_clientArray[SPI_DRIVER_INSTANCE_1_CLIENTS];
static SpiDriverInit   spiDriverInstance1_init = {
        .nClientsMax = SPI_DRIVER_INSTANCE_1_CLIENTS,
        .spiChannel = LCD_SPI_CHANNEL,
        .clientArray = spiDriverInstance1_clientArray,
        .txDmaChannel = DMA_CHANNEL_0,
};

static void blink(void *params);
static void lcd_task(void *params);

void BSP_gpio_initialize(void )
{
    GPIO_pin_initialize(LED1, GPIO_OUTPUT);
    GPIO_pin_initialize(LED2, GPIO_OUTPUT);
    GPIO_pin_initialize(LED3, GPIO_OUTPUT);
    GPIO_pin_initialize(LED4, GPIO_OUTPUT);

    GPIO_pin_initialize(LCD_DC, GPIO_OUTPUT);
    GPIO_pin_initialize(LCD_BLA, GPIO_OUTPUT);
    GPIO_pin_initialize(LCD_RST, GPIO_OUTPUT);
    GPIO_pin_initialize(LCD_SS, GPIO_OUTPUT);

    GPIO_pin_initialize(QT_CHANGE, GPIO_INPUT_PULLUP | GPIO_IRQ);
    GPIO_pin_initialize(QT_RST, GPIO_OUTPUT);
    GPIO_pin_initialize(QT_SS, GPIO_OUTPUT);
    GPIO_pin_initialize(QT_SDO, GPIO_OUTPUT);
    GPIO_pin_initialize(QT_SDI, GPIO_INPUT);

    GPIO_pin_initialize(BUZZER, GPIO_OUTPUT);

    GPIO_pin_write(LCD_DC, GPIO_LOW);
    GPIO_pin_write(LCD_BLA, GPIO_LOW);
    GPIO_pin_write(LCD_RST, GPIO_LOW);
    GPIO_pin_write(LCD_SS, GPIO_HIGH);

    GPIO_pin_write(QT_RST, GPIO_HIGH);
    GPIO_pin_write(QT_SS, GPIO_HIGH);

    GPIO_pin_initialize(UART_TX_PIN, GPIO_OUTPUT);
    GPIO_pin_initialize(UART_RX_PIN, GPIO_INPUT);

    SYS_Unlock(SYS_UNLOCK_IO);
    /* LCD SPI */
    PPS_pin_mapping(LCD_SPI_OUTPUT_REG, LCD_SPI_OUTPUT_MAP);
    /* QTOUCH SPI */
    PPS_pin_mapping(QT_SPI_OUTPUT_REG, QT_SPI_OUTPUT_MAP);
    PPS_pin_mapping(QT_SPI_INPUT_REG, QT_SPI_INPUT_MAP);
    /*BUZZER*/
    PPS_pin_mapping(BUZZER_OUTPUT_REG, BUZZER_OUTPUT_MAP);
    /*UART*/
    PPS_pin_mapping(UART_RX_INPUT_REG, UART_RX_INPUT_MAP);
    PPS_pin_mapping(UART_TX_OUTPUT_REG, UART_TX_OUTPUT_MAP);

    SYS_Lock();

    static uint8_t uartRxBuffer[256];
    UART_initialize(UART, UART_PARITY_NONE | UART_DATA_BITS_8, 115200, uartRxBuffer, 256);
    char s[]="\n\r";
    UART_write(UART, (uint8_t*)s, 2);

    DEBUG_INIT(UART);
    DEBUG_PRINT("\n\r----Init----\n\r");


    SPI_initialize(
        LCD_SPI_CHANNEL,
        SPI_MASTER | SPI_SDI_DISABLE | SPI_MODE_3 ,
        20000000);
    SPI_initialize(QT_SPI_CHANNEL, SPI_MASTER | SPI_MODE_3 | SPI_SAMPLE_END, 1000000);

    TMR_initialize(TMR_CHANNEL_2, TMR_PRESCALER_64, 5971);
    OC_initialize(OC_CHANNEL_1, OC_MODE_PWM | OC_MODE_USE_TMR2, 2985);

    DMA_channel_init(LCD_DMA_CHANNEL, DMA_CHANNEL_PRIORITY_3 | DMA_CHANNEL_START_IRQ);



}

void BSP_drivers_initialize( void )
{
    int r = SpiDriver_initialize(0, &spiDriverInstance0_init);
    DEBUG_PRINT("r = %d\n\r", r);
    r = SpiDriver_initialize(1, &spiDriverInstance1_init);
    DEBUG_PRINT("r = %d\n\r", r);
}

void BSP_interrupts_initialize(void )
{
    EVIC_channel_priority(EVIC_CHANNEL_CHANGE_NOTICE_E, EVIC_PRIORITY_4, EVIC_SUB_PRIORITY_2);
    EVIC_channel_set(EVIC_CHANNEL_CHANGE_NOTICE_E);
    EVIC_channel_priority(EVIC_CHANNEL_DMA0, EVIC_PRIORITY_2, EVIC_SUB_PRIORITY_2);
    EVIC_channel_set(EVIC_CHANNEL_DMA0);

    EVIC_channel_priority(EVIC_CHANNEL_UART1_FAULT, EVIC_PRIORITY_4, EVIC_SUB_PRIORITY_1);
    EVIC_channel_priority(EVIC_CHANNEL_UART1_RX, EVIC_PRIORITY_4, EVIC_SUB_PRIORITY_2);


//    EVIC_channel_priority(EVIC_CHANNEL_SPI2_RX, EVIC_PRIORITY_2, EVIC_SUB_PRIORITY_2);
//    EVIC_channel_priority(EVIC_CHANNEL_SPI2_TX, EVIC_PRIORITY_2, EVIC_SUB_PRIORITY_2);
}

void BSP_task_initialize(void)
{
    xTaskCreate(blink,"blink_task",256,(void*)&pinParamsLed1,1,NULL);
    xTaskCreate(blink,"blink_task",256,(void*)&pinParamsLed2,1,NULL);
    xTaskCreate(lcd_task, "lcd_task", 2048, NULL, 3, NULL);
    xTaskCreate(keypad_task, "qt_task", 2048, NULL, 1, NULL);
}


void BSP_gpio_callback_register(GPIO_PinMap pinMap, GPIO_Callback callback, uintptr_t context)
{
    for(int i=0; i<sizeof(pinCallbackObj)/sizeof(GPIO_CALLBACK_OBJECT); i++){
        if(pinCallbackObj[i].pin == pinMap){
            pinCallbackObj[i].callback = callback;
            pinCallbackObj[i].context = context;
            return;
        }
    }
}

void    GPIO_pin_interrupt_callback     (uint32_t pin)
{
    for(int i=0; i<sizeof(pinCallbackObj)/sizeof(GPIO_CALLBACK_OBJECT); i++){
        if((pinCallbackObj[i].pin & pin) && (pinCallbackObj[i].callback != NULL) ){
            pinCallbackObj[i].callback(pinCallbackObj[i].pin, pinCallbackObj[i].context);
        }
    }
}

void blink(void *params)
{
    PinParams *p = (PinParams*)params;
    while(1){
        GPIO_pin_toggle(p->pinMap);
        vTaskDelay(p->delay_ms);
    }
}

void lcd_task(void *params)
{
    (void)params;
    LCD_init(1, LCD_DMA_CHANNEL, LCD_SS, LCD_BLA, LCD_DC, LCD_RST);

    LCD_draw_bitmap(0,0,bitmap,sizeof(bitmap));
    char *s = "Hola Mundo";
    LCD_draw_string(0,1,(char*)s,LCD_FONT_MEDIUM,LCD_COLOR_BLACK);
    while(true){
        LCD_print();
        vTaskDelay(17);
    }
}