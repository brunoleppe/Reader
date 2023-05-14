//
// Created by bleppe on 28/03/23.
//

// <editor-fold desc="Configuration Bits">
/*** DEVCFG0 ***/

#pragma config DEBUG =      OFF
#pragma config JTAGEN =     OFF
#pragma config ICESEL =     ICS_PGx1
#pragma config TRCEN =      OFF
#pragma config BOOTISA =    MIPS32
#pragma config FECCCON =    OFF_UNLOCKED
#pragma config FSLEEP =     OFF
#pragma config DBGPER =     PG_ALL
#pragma config EJTAGBEN =   NORMAL
#pragma config CP =         OFF

/*** DEVCFG1 ***/

#pragma config FNOSC =      SPLL
#pragma config DMTINTV =    WIN_127_128
#pragma config FSOSCEN =    OFF
#pragma config IESO =       OFF
#pragma config POSCMOD =    OFF
#pragma config OSCIOFNC =   OFF
#pragma config FCKSM =      CSECME
#pragma config WDTPS =      PS1048576
#pragma config WDTSPGM =    STOP
#pragma config FWDTEN =     OFF
#pragma config WINDIS =     NORMAL
#pragma config FWDTWINSZ =  WINSZ_25
#pragma config DMTCNT =     DMT31
#pragma config FDMTEN =     OFF
/*** DEVCFG2 ***/

#pragma config FPLLIDIV =   DIV_1
#pragma config FPLLRNG =    RANGE_5_10_MHZ
#pragma config FPLLICLK =   PLL_FRC
#pragma config FPLLMULT =   MUL_50
#pragma config FPLLODIV =   DIV_2
#pragma config UPLLFSEL =   FREQ_24MHZ
#pragma config UPLLEN =     ON
/*** DEVCFG3 ***/

#pragma config USERID =     0xffff
#pragma config FMIIEN =     OFF
#pragma config FETHIO =     ON
#pragma config PGL1WAY =    ON
#pragma config PMDL1WAY =   ON
#pragma config IOL1WAY =    ON
#pragma config FUSBIDIO =   ON

/*** BF1SEQ0 ***/

#pragma config TSEQ =       0x0000
#pragma config CSEQ =       0xffff
//</editor-fold>

#include "bsp.h"
#include "HAL/hal.h"
#include "board_defs.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Drivers/SPI/spi_driver.h"
#include "lcd.h"
#include "debug_bsp.h"
#include "keypad.h"
#include "led_matrix.h"
#include "sst26.h"
#include "core/net.h"
#include "drivers/mac/pic32mz_eth_driver.h"
#include "drivers/phy/ksz8041_driver.h"
#include <xc.h>


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
    GPIO_pin_write(QT_SS_PIN, GPIO_HIGH);

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


    GPIO_pin_initialize(ETXD0_PIN,  GPIO_INPUT);
    GPIO_pin_initialize(ETXD1_PIN,  GPIO_INPUT);
    GPIO_pin_initialize(ERXD0_PIN,  GPIO_INPUT);
    GPIO_pin_initialize(ERXD1_PIN,  GPIO_INPUT);
    GPIO_pin_initialize(ETXEN_PIN,  GPIO_INPUT);
    GPIO_pin_initialize(ECRSDV_PIN, GPIO_INPUT);
    GPIO_pin_initialize(ERXERR_PIN, GPIO_INPUT);
    GPIO_pin_initialize(EREFCLK_PIN,GPIO_INPUT);
    GPIO_pin_initialize(EMDC_PIN,   GPIO_INPUT);
    GPIO_pin_initialize(EMDIO_PIN,  GPIO_INPUT);


    GPIO_pin_initialize(SPI_SDO_PIN, GPIO_OUTPUT);
    GPIO_pin_initialize(SPI_SDI_PIN, GPIO_INPUT);


    SYS_Unlock(SYS_UNLOCK_IO);
    PPS_pin_mapping(SPI_OUTPUT_REG, SPI_OUTPUT_MAP);
    PPS_pin_mapping(SPI_INPUT_REG, SPI_INPUT_MAP);

    SYS_Lock();


    SPI_initialize(SPI_CHANNEL, SPI_MASTER | SPI_MODE_3, 20000000);

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
    EVIC_channel_priority(EVIC_CHANNEL_ETHERNET, EVIC_PRIORITY_3, EVIC_SUB_PRIORITY_1);
    EVIC_channel_set(EVIC_CHANNEL_ETHERNET);

//    EVIC_channel_priority(EVIC_CHANNEL_UART1_ERR, EVIC_PRIORITY_4, EVIC_SUB_PRIORITY_2);
//    EVIC_channel_priority(EVIC_CHANNEL_UART1_RX, EVIC_PRIORITY_4, EVIC_SUB_PRIORITY_2);
    INTCONSET = _INTCON_MVEC_MASK;
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
    LCD_init(LCD_SPI_DRIVER_INDEX, LCD_TX_DMA_CHANNEL, LCD_SS_PIN, LCD_BLA_PIN, LCD_DC_PIN, LCD_RST_PIN);


    MacAddr macAddr;
    NetInterface *interface;
    Ipv4Addr ipv4Addr;
//
    netInit();
    interface = &netInterface[0];
    netSetInterfaceName(interface, "eth0");
    netSetHostname(interface, "TEST");
    macStringToAddr("00-00-00-00-00-00", &macAddr);
    netSetMacAddr(interface, &macAddr);
    netSetDriver(interface, &pic32mzEthDriver);
    netSetPhyAddr(interface, 1);
    netSetPhyDriver(interface, &ksz8041PhyDriver);
//
    netConfigInterface(interface);

    ipv4StringToAddr("10.1.1.244", &ipv4Addr);
    ipv4SetHostAddr(interface, ipv4Addr);

    ipv4StringToAddr("255.255.255.0", &ipv4Addr);
    ipv4SetSubnetMask(interface, ipv4Addr);

    ipv4StringToAddr("10.1.1.1", &ipv4Addr);
    ipv4SetDefaultGateway(interface, ipv4Addr);

    //Set primary and secondary DNS servers
    ipv4StringToAddr("0.0.0.0", &ipv4Addr);
    ipv4SetDnsServer(interface, 0, ipv4Addr);
    ipv4StringToAddr("0.0.0.0", &ipv4Addr);
    ipv4SetDnsServer(interface, 1, ipv4Addr);
}
void BSP_task_initialize(void)
{
    xTaskCreate(keypad_task, "keypad", 1024, NULL, 3, NULL);
}

void ETHERNET_interrupt_handler(void)
{
    pic32mzEthIrqHandler();
}