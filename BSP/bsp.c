#include <xc.h>
#include "bsp.h"
#include "hal.h"
#include "Drivers/SPI/spi_driver.h"

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
};

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

    SYS_Unlock(SYS_UNLOCK_IO);
    /* LCD SPI */
    PPS_pin_mapping(LCD_SPI_OUTPUT_REG, LCD_SPI_OUTPUT_MAP);
    /* QTOUCH SPI */
    PPS_pin_mapping(QT_SPI_OUTPUT_REG, QT_SPI_OUTPUT_MAP);
    PPS_pin_mapping(QT_SPI_INPUT_REG, QT_SPI_INPUT_MAP);
    /*BUZZER*/
    PPS_pin_mapping(BUZZER_OUTPUT_REG, BUZZER_OUTPUT_MAP);

    SYS_Lock();

    SPI_initialize(
        LCD_SPI_CHANNEL,
        SPI_MASTER | SPI_SDI_DISABLE | SPI_MODE_3 ,
        20000000);
    SPI_initialize(QT_SPI_CHANNEL, SPI_MASTER | SPI_MODE_3 | SPI_SAMPLE_END, 1000000);

    TMR_initialize(TMR_CHANNEL_2, TMR_PRESCALER_64, 5971);
    OC_initialize(OC_CHANNEL_1, OC_MODE_PWM | OC_MODE_USE_TMR2, 2985);

    DMA_channel_init(LCD_DMA_CHANNEL, DMA_CHANNEL_PRIORITY_3 | DMA_CHANNEL_START_IRQ);

    SpiDriver_initialize(0, &spiDriverInstance0_init);
    SpiDriver_initialize(1, &spiDriverInstance1_init);
}

void BSP_interrupts_initialize(void )
{
    EVIC_channel_priority(EVIC_CHANNEL_CHANGE_NOTICE_E, EVIC_PRIORITY_4, EVIC_SUB_PRIORITY_2);
    EVIC_channel_set(EVIC_CHANNEL_CHANGE_NOTICE_E);
    EVIC_channel_priority(EVIC_CHANNEL_DMA0, EVIC_PRIORITY_2, EVIC_SUB_PRIORITY_2);
    EVIC_channel_set(EVIC_CHANNEL_DMA0);
//    EVIC_channel_priority(EVIC_CHANNEL_SPI2_RX, EVIC_PRIORITY_2, EVIC_SUB_PRIORITY_2);
//    EVIC_channel_priority(EVIC_CHANNEL_SPI2_TX, EVIC_PRIORITY_2, EVIC_SUB_PRIORITY_2);
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