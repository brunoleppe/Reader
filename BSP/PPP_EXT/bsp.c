//
// Created by bleppe on 28/03/23.
//

// <editor-fold desc="Configuration Bits">
// DEVCFG3
#pragma config USERID = 0xFFFF          // Enter Hexadecimal value (Enter Hexadecimal value)
#pragma config FMIIEN = ON              // Ethernet RMII/MII Enable (MII Enabled)
#pragma config FETHIO = ON              // Ethernet I/O Pin Select (Default Ethernet I/O)
#pragma config PGL1WAY = ON             // Permission Group Lock One Way Configuration (Allow only one reconfiguration)
#pragma config PMDL1WAY = ON            // Peripheral Module Disable Configuration (Allow only one reconfiguration)
#pragma config IOL1WAY = ON             // Peripheral Pin Select Configuration (Allow only one reconfiguration)
#pragma config FUSBIDIO = ON            // USB USBID Selection (Controlled by the USB Module)

// DEVCFG2
#pragma config FPLLIDIV = DIV_1         // System PLL Input Divider (1x Divider)
#pragma config FPLLRNG = RANGE_5_10_MHZ // System PLL Input Range (5-10 MHz Input)
#pragma config FPLLICLK = PLL_FRC       // System PLL Input Clock Selection (FRC is input to the System PLL)
#pragma config FPLLMULT = MUL_50        // System PLL Multiplier (PLL Multiply by 50)
#pragma config FPLLODIV = DIV_2         // System PLL Output Clock Divider (2x Divider)
#pragma config UPLLFSEL = FREQ_24MHZ    // USB PLL Input Frequency Selection (USB PLL input is 24 MHz)
#pragma config UPLLEN = OFF             // USB PLL Enable (USB PLL is disabled)

// DEVCFG1
#pragma config FNOSC = SPLL             // Oscillator Selection Bits (System PLL)
#pragma config DMTINTV = WIN_127_128    // DMT Count Window Interval (Window/Interval value is 127/128 counter value)
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disable SOSC)
#pragma config IESO = OFF               // Internal/External Switch Over (Disabled)
#pragma config POSCMOD = OFF            // Primary Oscillator Configuration (Primary osc disabled)
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FCKSM = CSECME           // Clock Switching and Monitor Selection (Clock Switch Enabled, FSCM Enabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config WDTSPGM = STOP           // Watchdog Timer Stop During Flash Programming (WDT stops during Flash programming)
#pragma config WINDIS = NORMAL          // Watchdog Timer Window Mode (Watchdog Timer is in non-Window mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled)
#pragma config FWDTWINSZ = WINSZ_25     // Watchdog Timer Window Size (Window size is 25%)
#pragma config DMTCNT = DMT31           // Deadman Timer Count Selection (2^31 (2147483648))
#pragma config FDMTEN = OFF             // Deadman Timer Enable (Deadman Timer is disabled)

// DEVCFG0
#pragma config DEBUG = OFF              // Background Debugger Enable (Debugger is disabled)
#pragma config JTAGEN = OFF             // JTAG Enable (JTAG Disabled)
#pragma config ICESEL = ICS_PGx1        // ICE/ICD Comm Channel Select (Communicate on PGEC1/PGED1)
#pragma config TRCEN = OFF              // Trace Enable (Trace features in the CPU are disabled)
#pragma config BOOTISA = MIPS32         // Boot ISA Selection (Boot code and Exception code is MIPS32)
#pragma config FECCCON = OFF_UNLOCKED   // Dynamic Flash ECC Configuration (ECC and Dynamic ECC are disabled (ECCCON bits are writable))
#pragma config FSLEEP = OFF             // Flash Sleep Mode (Flash is powered down when the device is in Sleep mode)
#pragma config DBGPER = PG_ALL          // Debug Mode CPU Access Permission (Allow CPU access to all permission regions)
#pragma config EJTAGBEN = NORMAL        // EJTAG Boot (Normal EJTAG functionality)

// DEVCP0
#pragma config CP = OFF                 // Code Protect (Protection Disabled)

// SEQ0
#pragma config TSEQ = 0            // Boot Flash True Sequence Number (Enter Hexadecimal value)
#pragma config CSEQ = 0xFFFF               // Boot Flash Complement Sequence Number (Enter Hexadecimal value)
//</editor-fold>

#include "bsp.h"
#include "HAL/hal.h"
#include "board_defs.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Drivers/SPI/spi_driver.h"
#include "lcd.h"
#include "debug.h"
#include "keypad.h"
#include "led_matrix.h"
#include "sst26.h"
#include <xc.h>


_Noreturn static void lcd_task(void *params);

_Noreturn static void blink(void *params);

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
    INTCONSET = _INTCON_MVEC_MASK;
    BSP_interrupts_initialize();
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


    GPIO_pin_initialize(SPI_SDO_PIN, GPIO_OUTPUT);
    GPIO_pin_initialize(SPI_SDI_PIN, GPIO_INPUT);


    SYS_Unlock(SYS_UNLOCK_IO);
    PPS_pin_mapping(SPI_OUTPUT_REG, SPI_OUTPUT_MAP);
    PPS_pin_mapping(SPI_INPUT_REG, SPI_INPUT_MAP);

    SYS_Lock();


    SPI_initialize(SPI_CHANNEL, SPI_MASTER | SPI_SDI_DISABLE | SPI_MODE_3, 20000000);

//    static uint8_t uartRxBuffer[256];
//    UART_initialize(DEBUG_UART, UART_PARITY_NONE | UART_DATA_BITS_8, 9600, uartRxBuffer, 256);
//    char s[]="\n\r";
//    UART_write(DEBUG_UART, (uint8_t*)s, 2);

}
void BSP_interrupts_initialize(void )
{
//    EVIC_init(NULL);

    EVIC_channel_priority(EVIC_CHANNEL_DMA0, EVIC_PRIORITY_2, EVIC_SUB_PRIORITY_2);
    EVIC_channel_set(EVIC_CHANNEL_DMA0);
    EVIC_channel_priority(EVIC_CHANNEL_DMA1, EVIC_PRIORITY_2, EVIC_SUB_PRIORITY_2);
    EVIC_channel_set(EVIC_CHANNEL_DMA1);

//    EVIC_channel_priority(EVIC_CHANNEL_UART1_ERR, EVIC_PRIORITY_4, EVIC_SUB_PRIORITY_2);
//    EVIC_channel_priority(EVIC_CHANNEL_UART1_RX, EVIC_PRIORITY_4, EVIC_SUB_PRIORITY_2);

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
    xTaskCreate(lcd_task, "lcd_task", 2048, NULL, 2, NULL);
    xTaskCreate(keypad_task, "keypad", 1024, NULL, 3, NULL);
//    xTaskCreate(blink, "blink", 1024, NULL, 2, NULL);
}

void lcd_task(void *params)
{
    (void)params;
    LCD_init(LCD_SPI_DRIVER_INDEX, LCD_TX_DMA_CHANNEL, LCD_SS_PIN, LCD_BLA_PIN, LCD_DC_PIN, LCD_RST_PIN);
    while(true){
        LCD_print();
        vTaskDelay(17);
    }
}

static void blink(void *params)
{
    while(true){
        led_matrix_led_toggle(0,0);
        vTaskDelay(500);
    }
}