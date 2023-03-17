//
// Created by bleppe on 17/03/23.
//

#ifndef UART_H
#define UART_H

/**********************************************************************
* Includes
**********************************************************************/

#include "hal_defs.h"

/**********************************************************************
* Preprocessor Constants
**********************************************************************/

#define UART_CHANNEL_1                                      1
#define UART_CHANNEL_2                                      2
#define UART_CHANNEL_3                                      3
#define UART_CHANNEL_4                                      4
#define UART_CHANNEL_5                                      5
#define UART_CHANNEL_6                                      6


#define UART_PARITY_NONE                                    0x0000
#define UART_PARITY_ODD                                     0x0001
#define UART_PARITY_EVEN                                    0x0002
#define UART_DATA_BITS_8                                    0x0000
#define UART_DATA_BITS_9                                    0x0008
#define UART_STOP_BITS_1                                    0x0000
#define UART_STOP_BITS_2                                    0x0010
#define UART_LOOP_BACK                                      0x0020
#define UART_RX_INVERTED                                    0x0040
#define UART_RX_DISABLED                                    0x0100
#define UART_TX_INVERTED                                    0x0080
#define UART_TX_DISABLED                                    0x0200

/**********************************************************************
* Typedefs
**********************************************************************/
#if defined (__LANGUAGE_C__) || defined (__LANGUAGE_C_PLUS_PLUS)

typedef int UART_Channel;
typedef uint32_t UART_Flags;
typedef void (*UART_Callback)(UART_Channel, )

/**********************************************************************
* Function Prototypes
**********************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

int     UART_initialize(UART_Channel channel, UART_Flags flags, int baudrate);
int     UART_setup(UART_Channel channel, UART_Flags flags, int baudrate);
size_t  UART_write(UART_Channel channel, uint8_t *txBuffer, size_t size);
size_t  UART_read(UART_Channel channel, uint8_t *rxBuffer, size_t size);
uint8_t UART_write_byte(UART_Channel channel, uint8_t data);
uint8_t UART_read_byte(UART_Channel channel);

bool    UART_write_isr(UART_Channel channel, uint8_t *txBuffer, size_t size);
bool    UART_read_isr(UART_Channel channel, uint8_t *rxBuffer, size_t size);
void    UART_callback_register(UART_Channel channel, )

#ifdef __cplusplus
}
#endif
#endif



#endif //UART_H
