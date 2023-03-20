/**
* @file uart.c
* @author Bruno Leppe
* @brief
* @version 0.1
* @date 2022-09-28
*
* @copyright Copyright (c) 2022
*
*/

/**********************************************************************
* Includes
**********************************************************************/
#include "uart.h"
#include "pic32mz_registers.h"
#include "evic.h"
#include <xc.h>
#include "system.h"
/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/
#define UART_BASE                               _UART1_BASE_ADDRESS
#define UART_NUMBER_OF_CHANNELS                 (6)
#define UART_PERIPHERAL_INTERVAL                (0x200)
/**********************************************************************
* Module Preprocessor Macros
**********************************************************************/
#define UART_DESCRIPTOR(channel)                ((UART_Descriptor)(((uint8_t*)(UART_BASE)) + UART_PERIPHERAL_INTERVAL*(channel)))
#define UART_RX_INTERRUPT_CHANNEL(channel)      (uartIRQBase[channel] + 1)
#define UART_TX_INTERRUPT_CHANNEL(channel)      (uartIRQBase[channel] + 2)
#define UART_FAULT_INTERRUPT_CHANNEL(channel)   (uartIRQBase[channel])
/**********************************************************************
* Module Typedefs
**********************************************************************/
typedef struct{
    bool            busy;
    void            *txBuffer;
    void            *rxBuffer;
    size_t          rxCount;
    size_t          txCount;
    size_t          rxSize;
    size_t          txSize;
    SPI_Callback    callback;
}UART_Object;
/*********************************************************************
* Module Variable Definitions
**********************************************************************/
static UART_Object uartObjects[UART_NUMBER_OF_CHANNELS];
static const EVIC_CHANNEL uartIRQBase[UART_NUMBER_OF_CHANNELS]={
        EVIC_CHANNEL_UART1_FAULT,
        EVIC_CHANNEL_UART2_FAULT,
        EVIC_CHANNEL_UART3_FAULT,
        EVIC_CHANNEL_UART4_FAULT,
        EVIC_CHANNEL_UART5_FAULT,
        EVIC_CHANNEL_UART6_FAULT,
};
/**********************************************************************
* Function Prototypes
**********************************************************************/
static int UART_baudrate(UART_Channel channel, int baudrate);
/**********************************************************************
* Function Definitions
**********************************************************************/
//
//#define UART_PARITY_NONE                                    0x0000
//#define UART_PARITY_ODD                                     0x0001
//#define UART_PARITY_EVEN                                    0x0002
//#define UART_DATA_BITS_8                                    0x0000
//#define UART_DATA_BITS_9                                    0x0008
//#define UART_STOP_BITS_1                                    0x0000
//#define UART_STOP_BITS_2                                    0x0010
//#define UART_LOOP_BACK                                      0x0020
//#define UART_RX_INVERTED                                    0x0040
//#define UART_RX_DISABLED                                    0x0100
//#define UART_TX_INVERTED                                    0x0080
//#define UART_TX_DISABLED                                    0x0200

int     UART_initialize(UART_Channel channel, UART_Flags flags, int baudrate)
{
    uartObjects[channel].busy = false;
    return UART_setup(channel, flags, baudrate);
}
int     UART_setup(UART_Channel channel, UART_Flags flags, int baudrate)
{
    UART_DESCRIPTOR(channel)->umode.reg = 0;
    int brg = UART_baudrate(channel, baudrate);
    if(brg < 0)
        return -1;
    UART_DESCRIPTOR(channel)->ubrg.reg = brg;

    if((flags & UART_PARITY_EVEN) == UART_PARITY_EVEN)
        UART_DESCRIPTOR(channel)->umode.set = _U1MODE_PDSEL0_MASK;
    else if((flags & UART_PARITY_ODD) == UART_PARITY_ODD)
        UART_DESCRIPTOR(channel)->umode.set = _U1MODE_PDSEL1_MASK;
    if((flags & UART_DATA_BITS_9) == UART_DATA_BITS_9)
        UART_DESCRIPTOR(channel)->umode.set = _U1MODE_PDSEL_MASK;
    if((flags & UART_STOP_BITS_2) == UART_STOP_BITS_2)
        UART_DESCRIPTOR(channel)->umode.set = _U1MODE_STSEL_MASK;
    if((flags & UART_LOOP_BACK) == UART_LOOP_BACK)
        UART_DESCRIPTOR(channel)->umode.set = _U1MODE_LPBACK_MASK;




    UART_DESCRIPTOR(channel)->usta.set =  _U1STA_URXEN_MASK | _U1STA_UTXEN_MASK;

    if((flags & UART_RX_INVERTED) == UART_RX_INVERTED)
        UART_DESCRIPTOR(channel)->umode.set = _U1MODE_RXINV_MASK;
    if((flags & UART_RX_DISABLED) == UART_RX_DISABLED)
        UART_DESCRIPTOR(channel)->usta.clr = _U1STA_URXEN_MASK;
    if((flags & UART_TX_INVERTED) == UART_TX_INVERTED)
        UART_DESCRIPTOR(channel)->usta.set = _U1STA_UTXINV_MASK;
    if((flags & UART_TX_DISABLED) == UART_TX_DISABLED)
        UART_DESCRIPTOR(channel)->usta.clr = _U1STA_UTXEN_MASK;
    return 0;
}

size_t  UART_write(UART_Channel channel, uint8_t *txBuffer, size_t size);
size_t  UART_read(UART_Channel channel, uint8_t *rxBuffer, size_t size);
uint8_t UART_write_byte(UART_Channel channel, uint8_t data);
uint8_t UART_read_byte(UART_Channel channel);

bool    UART_write_isr(UART_Channel channel, uint8_t *txBuffer, size_t size);
bool    UART_read_isr(UART_Channel channel, uint8_t *rxBuffer, size_t size);

static int UART_baudrate(UART_Channel channel, int baudrate){
    int clock;
    int brg_lo;
    int brg_hi;
    int error_lo, error_hi;
    int brg;

    clock = (int)SYS_peripheral_clock_frequency_get(SYS_PERIPHERAL_CLOCK_2);
    brg_lo = ((clock/(int)baudrate)>>4)-1;
    brg_hi = ((clock/(int)baudrate)>>2)-1;
    if(brg_lo < 0)
        return brg_hi;
    if(brg_hi < 0)
        return -1;
    error_lo = (clock / ((brg_lo + 1)<<4)) - baudrate;
    brg = brg_lo;
    if((UART_DESCRIPTOR(channel)->umode.reg & _U1MODE_STSEL_MASK) == 0){
        error_hi = (clock / ((brg_lo + 1)<<2)) - baudrate;
        if(brg_hi < 65535 && error_hi < error_lo) {
            brg = brg_hi;
            UART_DESCRIPTOR(channel)->umode.set = _U1MODE_BRGH_MASK;
        }
    }
    if(brg > 65535)
        return -1;
    return brg;
}