#include <assert.h>
#include <features.h>
//
// Created by bleppe on 28/03/23.
//
#include "bsp.h"
#include "HAL/hal.h"
#include "board_defs.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Drivers/SPI/spi_driver.h"
#include "lcd.h"
#include "debug_bsp.h"
#include "keypad.h"

#include "sst26.h"
#include <xc.h>
// <editor-fold desc="Configuration Bits">
/*** DEVCFG0 ***/
#pragma config DEBUG =      OFF
#pragma config ICESEL =     ICS_PGx2
#pragma config PWP =        OFF
#pragma config BWP =        OFF
#pragma config CP =         OFF


/*** DEVCFG1 ***/
#pragma config FNOSC =      FRCPLL
#pragma config FPBDIV =     DIV_1
#pragma config FSOSCEN =    OFF
#pragma config IESO =       ON
#pragma config POSCMOD =    OFF
#pragma config OSCIOFNC =   OFF
#pragma config FCKSM =      CSDCMD
#pragma config WDTPS =      PS1048576
#pragma config FWDTEN =     OFF


/*** DEVCFG2 ***/
#pragma config FPLLIDIV =   DIV_2
#pragma config FPLLMUL =    MUL_20
#pragma config FPLLODIV =   DIV_1
#pragma config UPLLEN =     OFF
#pragma config UPLLIDIV =   DIV_2

/*** DEVCFG3 ***/
#pragma config FSRSSEL =    PRIORITY_7
#pragma config FVBUSONIO =  ON
#pragma config USERID =     0xffff
#pragma config FUSBIDIO =   ON
#pragma config FMIIEN =     OFF
#pragma config FETHIO =     ON
#pragma config FCANIO =     OFF
//</editor-fold>

_Noreturn static void lcd_task(void *params);

static SpiClientObject spiDriverInstance0_clientArray[SPI_DRIVER_INSTANCE_0_CLIENTS];
static SpiDriverInit   spiDriverInstance0_init = {
        .nClientsMax = SPI_DRIVER_INSTANCE_0_CLIENTS,
        .spiChannel = SPI_CHANNEL,
        .clientArray = spiDriverInstance0_clientArray,
        .txDmaChannel = LCD_TX_DMA_CHANNEL,
        .rxDmaChannel = LCD_RX_DMA_CHANNEL,
};

void BSP_system_initialize(void)
{
    EVIC_disable_interrupts();
    SYS_initialize();
}
void BSP_gpio_initialize(void )
{
    GPIO_pin_initialize(LED_M_COL0_PIN, GPIO_OUTPUT);
    GPIO_pin_initialize(LED_M_COL1_PIN, GPIO_OUTPUT);
    GPIO_pin_initialize(LED_M_COL2_PIN, GPIO_OUTPUT);
    GPIO_pin_initialize(LED_M_COL3_PIN, GPIO_OUTPUT);
    GPIO_pin_initialize(LED_M_ROW0_PIN, GPIO_OUTPUT);
    GPIO_pin_initialize(LED_M_ROW1_PIN, GPIO_OUTPUT);
    GPIO_pin_initialize(LED_M_ROW2_PIN, GPIO_OUTPUT);
    GPIO_pin_initialize(LED_M_ROW3_PIN, GPIO_OUTPUT);
    GPIO_pin_initialize(LED_M_ROW4_PIN, GPIO_OUTPUT);

    GPIO_pin_initialize(LCD_BLA_PIN, GPIO_OUTPUT);
    GPIO_pin_initialize(LCD_DC_PIN, GPIO_OUTPUT);
    GPIO_pin_initialize(LCD_RST_PIN, GPIO_OUTPUT);
    GPIO_pin_initialize(LCD_SS_PIN, GPIO_OUTPUT);

    GPIO_pin_initialize(QT_DRDY_PIN, GPIO_INPUT);
    GPIO_pin_initialize(QT_RST_PIN, GPIO_OUTPUT);
    GPIO_pin_initialize(QT_SS_PIN, GPIO_OUTPUT);
    GPIO_pin_initialize(QT_CHANGE_PIN, GPIO_INPUT | GPIO_PULLUP);


    GPIO_pin_write(LCD_BLA_PIN, GPIO_HIGH);
    GPIO_pin_write(LCD_DC_PIN, GPIO_HIGH);
    GPIO_pin_write(LCD_RST_PIN, GPIO_HIGH);
    GPIO_pin_write(LCD_SS_PIN, GPIO_HIGH);

    GPIO_pin_initialize(FLASH_SS_PIN, GPIO_OUTPUT);
    GPIO_pin_write(FLASH_SS_PIN, GPIO_HIGH);

    GPIO_pin_write(LED_M_COL0_PIN, GPIO_HIGH);
    GPIO_pin_write(LED_M_COL1_PIN, GPIO_HIGH);
    GPIO_pin_write(LED_M_COL2_PIN, GPIO_HIGH);
    GPIO_pin_write(LED_M_COL3_PIN, GPIO_HIGH);
    GPIO_pin_write(LED_M_ROW0_PIN, GPIO_LOW);
    GPIO_pin_write(LED_M_ROW1_PIN, GPIO_LOW);
    GPIO_pin_write(LED_M_ROW2_PIN, GPIO_LOW);
    GPIO_pin_write(LED_M_ROW3_PIN, GPIO_LOW);
    GPIO_pin_write(LED_M_ROW4_PIN, GPIO_LOW);


    GPIO_pin_initialize(ETXEN_PIN, GPIO_INPUT);
    GPIO_pin_initialize(ETXD0_PIN, GPIO_INPUT);
    GPIO_pin_initialize(ETXD1_PIN, GPIO_INPUT);
    GPIO_pin_initialize(EMDC_PIN, GPIO_INPUT);
    GPIO_pin_initialize(EMDIO_PIN, GPIO_INPUT);
    GPIO_pin_initialize(ERXD1_PIN, GPIO_INPUT);
    GPIO_pin_initialize(ERXD0_PIN, GPIO_INPUT);
    GPIO_pin_initialize(ECRSDV_PIN, GPIO_INPUT);
    GPIO_pin_initialize(EREFCLK_PIN, GPIO_INPUT);
    GPIO_pin_initialize(ERXERR_PIN, GPIO_INPUT);

    SPI_initialize(SPI_CHANNEL, SPI_MASTER | SPI_SDI_DISABLE | SPI_MODE_3, 20000000);

    static uint8_t uartRxBuffer[256];
    UART_initialize(DEBUG_UART, UART_PARITY_NONE | UART_DATA_BITS_8, 9600, uartRxBuffer, 256);
    char s[]="\n\r";
    UART_write(DEBUG_UART, (uint8_t*)s, 2);

}
void BSP_interrupts_initialize(void )
{
    EVIC_init(NULL);

    EVIC_channel_priority(EVIC_CHANNEL_DMA0, EVIC_PRIORITY_2, EVIC_SUB_PRIORITY_2);
    EVIC_channel_set(EVIC_CHANNEL_DMA0);
    EVIC_channel_priority(EVIC_CHANNEL_DMA1, EVIC_PRIORITY_2, EVIC_SUB_PRIORITY_2);
    EVIC_channel_set(EVIC_CHANNEL_DMA1);

    EVIC_channel_priority(EVIC_CHANNEL_UART1_ERR, EVIC_PRIORITY_4, EVIC_SUB_PRIORITY_2);
    EVIC_channel_priority(EVIC_CHANNEL_UART1_RX, EVIC_PRIORITY_4, EVIC_SUB_PRIORITY_2);

    EVIC_enable_interrupts();
}
void BSP_gpio_callback_register(GPIO_PinMap pinMap, GPIO_Callback callback, uintptr_t context)
{

}
void BSP_drivers_initialize( void )
{
    DMA_init();
    DMA_channel_init(LCD_TX_DMA_CHANNEL, DMA_CHANNEL_PRIORITY_3 | DMA_CHANNEL_START_IRQ);
    DMA_channel_init(LCD_RX_DMA_CHANNEL, DMA_CHANNEL_PRIORITY_3 | DMA_CHANNEL_START_IRQ);
    SpiDriver_initialize(SPI_DRIVER_INSTANCE_0, &spiDriverInstance0_init);

    sst26_initialize(FLASH_SPI_DRIVER_INDEX, FLASH_SS_PIN);

}
void BSP_task_initialize(void)
{
    xTaskCreate(lcd_task, "lcd_task", 2048, NULL, 3, NULL);
    xTaskCreate(keypad_task, "keypad", 1024, NULL, 2, NULL);
}

_Noreturn void lcd_task(void *params)
{
    (void)params;
    LCD_init(LCD_SPI_DRIVER_INDEX, LCD_TX_DMA_CHANNEL, LCD_SS_PIN, LCD_BLA_PIN, LCD_DC_PIN, LCD_RST_PIN);
    while(true){
        LCD_print();
        vTaskDelay(30);
    }
}