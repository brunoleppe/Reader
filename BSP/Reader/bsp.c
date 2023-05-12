// <editor-fold desc="Configuration Bits">
#pragma config DEBUG =      OFF
#pragma config JTAGEN =     OFF
#pragma config ICESEL =     ICS_PGx1
#pragma config TRCEN =      OFF
#pragma config BOOTISA =    MIPS32
#pragma config FECCCON =    OFF_UNLOCKED
#pragma config FSLEEP =     OFF
#pragma config DBGPER =     PG_ALL
#pragma config SMCLR =      MCLR_NORM
#pragma config SOSCGAIN =   GAIN_LEVEL_3
#pragma config SOSCBOOST =  ON
#pragma config POSCGAIN =   GAIN_LEVEL_3
#pragma config POSCBOOST =  ON
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

/*** DEVCFG3 ***/
#pragma config USERID =     0xffff
#pragma config FMIIEN =     OFF
#pragma config FETHIO =     ON
#pragma config PGL1WAY =    ON
#pragma config PMDL1WAY =   ON
#pragma config IOL1WAY =    ON
#pragma config FUSBIDIO =   ON

/*** BF1SEQ0 ***/

#pragma config TSEQ =       0xffff
#pragma config CSEQ =       0x0
// </editor-fold>

#include <xc.h>
#include "bsp.h"
#include "board_defs.h"
#include "hal.h"
#include "Drivers/SPI/spi_driver.h"
#include "debug_bsp.h"
#include "lcd.h"
#include "FreeRTOS.h"
#include "task.h"
#include "keypad.h"
#include "Reader/FlashMem/sst26.h"

#include "core/net.h"
#include "drivers/mac/pic32mz_eth_driver.h"
#include "drivers/phy/ksz8041_driver.h"
#include "drivers/switch/lan9303_driver.h"
#include "tcp_port.h"


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
        .txDmaChannel = LCD_TX_DMA_CHANNEL,
};

static SpiClientObject spiDriverInstance2_clientArray[SPI_DRIVER_INSTANCE_2_CLIENTS];
static SpiDriverInit   spiDriverInstance2_init = {
        .nClientsMax = SPI_DRIVER_INSTANCE_2_CLIENTS,
        .spiChannel = FLASH_SPI_CHANNEL,
        .clientArray = spiDriverInstance2_clientArray,
        .txDmaChannel = FLASH_TX_DMA_CHANNEL,
        .rxDmaChannel = FLASH_RX_DMA_CHANNEL,
};

static void blink(void *params);

_Noreturn static void lcd_task(void *params);

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

    GPIO_pin_initialize(FLASH_SS, GPIO_OUTPUT);
    GPIO_pin_initialize(FLASH_SDO, GPIO_OUTPUT);
    GPIO_pin_initialize(FLASH_SDI, GPIO_INPUT);
    GPIO_pin_write(FLASH_SS, GPIO_HIGH);

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

    ANSELB = 0;
    ANSELD = 0;
    ANSELF = 0;
    ANSELG = 0;


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
    /*FLASH SPI*/
    PPS_pin_mapping(FLASH_SPI_INPUT_REG, FLASH_SPI_INPUT_MAP);
    PPS_pin_mapping(FLASH_SPI_OUTPUT_REG, FLASH_SPI_OUTPUT_MAP);

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
    SPI_initialize(FLASH_SPI_CHANNEL, SPI_MASTER | SPI_MODE_3 | SPI_SAMPLE_END, 40000000);

    TMR_initialize(TMR_CHANNEL_2, TMR_PRESCALER_64, 5971);
    OC_initialize(OC_CHANNEL_1, OC_MODE_PWM | OC_MODE_USE_TMR2, 2985);

    DMA_init();
    DMA_channel_init(FLASH_TX_DMA_CHANNEL, DMA_CHANNEL_PRIORITY_2 | DMA_CHANNEL_START_IRQ);
    DMA_channel_init(LCD_TX_DMA_CHANNEL, DMA_CHANNEL_PRIORITY_3 | DMA_CHANNEL_START_IRQ);
    DMA_channel_init(FLASH_RX_DMA_CHANNEL, DMA_CHANNEL_PRIORITY_1 | DMA_CHANNEL_START_IRQ);
}

void BSP_drivers_initialize( void )
{

//    int r =
            SpiDriver_initialize(0, &spiDriverInstance0_init);
    DEBUG_PRINT("r = %d\n\r", r);
//    r =
            SpiDriver_initialize(1, &spiDriverInstance1_init);
    DEBUG_PRINT("r = %d\n\r", r);
    SpiDriver_initialize(2, &spiDriverInstance2_init);



    sst26_initialize(2, FLASH_SS);
    LCD_init(1, LCD_TX_DMA_CHANNEL, LCD_SS, LCD_BLA, LCD_DC, LCD_RST);


    MacAddr macAddr;
    NetInterface *interface;
    Ipv4Addr ipv4Addr;

    netInit();
    interface = &netInterface[0];
    netSetInterfaceName(interface, "eth0");
    netSetHostname(interface, "TEST");
    macStringToAddr("00-00-00-00-00-00", &macAddr);
    netSetMacAddr(interface, &macAddr);
    netSetDriver(interface, &pic32mzEthDriver);
    netSetPhyDriver(interface, &ksz8041PhyDriver);

//    netSetSwitchDriver(interface, &lan9303SwitchDriver);
//    netSetSwitchPort(interface,LAN9303_PORT1);

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

void BSP_interrupts_initialize(void )
{
    INTCONSET = _INTCON_MVEC_MASK;

    EVIC_channel_priority(EVIC_CHANNEL_CHANGE_NOTICE_E, EVIC_PRIORITY_4, EVIC_SUB_PRIORITY_2);
    EVIC_channel_set(EVIC_CHANNEL_CHANGE_NOTICE_E);
    EVIC_channel_priority(EVIC_CHANNEL_DMA0, EVIC_PRIORITY_2, EVIC_SUB_PRIORITY_2);
    EVIC_channel_set(EVIC_CHANNEL_DMA0);

    EVIC_channel_priority(EVIC_CHANNEL_DMA1, EVIC_PRIORITY_2, EVIC_SUB_PRIORITY_2);
    EVIC_channel_set(EVIC_CHANNEL_DMA1);
    EVIC_channel_priority(EVIC_CHANNEL_DMA2, EVIC_PRIORITY_2, EVIC_SUB_PRIORITY_2);
    EVIC_channel_set(EVIC_CHANNEL_DMA2);

    EVIC_channel_priority(EVIC_CHANNEL_UART1_FAULT, EVIC_PRIORITY_4, EVIC_SUB_PRIORITY_1);
    EVIC_channel_priority(EVIC_CHANNEL_UART1_RX, EVIC_PRIORITY_4, EVIC_SUB_PRIORITY_2);

    EVIC_enable_interrupts();
}

void BSP_task_initialize(void)
{
    xTaskCreate(blink,"blink_task",256,(void*)&pinParamsLed1,1,NULL);
    xTaskCreate(blink,"blink_task",256,(void*)&pinParamsLed2,1,NULL);
//    xTaskCreate(lcd_task, "lcd_task", 2048, NULL, 3, NULL);
    xTaskCreate(keypad_task, "qt_task", 2048, NULL, 1, NULL);
    xTaskCreate(tcp_port_task, "socket", 1024, NULL, 2, NULL);


}

void BSP_system_initialize()
{
    __builtin_disable_interrupts();

    PRECONbits.PREFEN = 3;
    PRECONbits.PFMWS = 3;
    CFGCONbits.ECCCON = 3;


//    BSP_interrupts_initialize();
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

_Noreturn void blink(void *params)
{
    PinParams *p = (PinParams*)params;
    while(1){
        GPIO_pin_toggle(p->pinMap);
        vTaskDelay(p->delay_ms);
    }
}

_Noreturn void lcd_task(void *params)
{
//    (void)params;
//    while(true){
//        LCD_print();
//        vTaskDelay(17);
//    }
}


void ETHERNET_handler_bsp(void)
{
    GPIO_pin_toggle(LED3);
    pic32mzEthIrqHandler();
}