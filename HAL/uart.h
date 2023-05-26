/**
 * @file timer.h
 * @brief UART Module
 * @author Bruno Leppe (bruno.leppe.dev\@gmail.com)
 * This module provides functions for initializing and controlling UART communication.
 * @version 0.1
 * @date 2022-09-29
 *
 * @copyright (c) 2023
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef UART_H
#define UART_H

/**********************************************************************
* Includes
**********************************************************************/

#include "hal_defs.h"

/**********************************************************************
* Preprocessor Constants
**********************************************************************/

#define UART_CHANNEL_1                                      0
#define UART_CHANNEL_2                                      1
#define UART_CHANNEL_3                                      2
#define UART_CHANNEL_4                                      3
#define UART_CHANNEL_5                                      4
#define UART_CHANNEL_6                                      5


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

#define UART_CALLBACK_ENABLE_THRESHOLD                      0x0001
#define UART_CALLBACK_ENABLE_TERMINATION                    0x0002

/**********************************************************************
* Typedefs
**********************************************************************/

/**
 * @brief Enumeration of UART channel events.
 */
typedef enum {
    UART_CHANNEL_EVENT_BUFFER_FULL,     /**< Buffer full event */
    UART_CHANNEL_EVENT_BYTE_RECEIVED,   /**< Byte received event */
    UART_CHANNEL_EVENT_READ_ERROR       /**< Read error event */
} UART_CHANNEL_EVENT;

/**
 * @brief Enumeration of UART error codes.
 */
typedef enum {
    UART_ERROR_NONE = 0,                /**< No error */
    UART_ERROR_OVERRUN = 0x00000002,    /**< Overrun error */
    UART_ERROR_FRAMING = 0x00000004,    /**< Framing error */
    UART_ERROR_PARITY  = 0x00000008     /**< Parity error */
} UART_ERROR;

/**
 * @brief UART channel type.
 */
typedef int UART_Channel;

/**
 * @brief UART flags type.
 */
typedef uint32_t UART_Flags;

/**
 * @brief Callback function type for UART events.
 *
 * This callback function is called when UART events occur.
 *
 * @param channel The UART channel associated with the event.
 * @param event The event that occurred.
 * @param context The context parameter provided during registration.
 */
typedef void (*UART_Callback)(UART_Channel channel, UART_CHANNEL_EVENT event, uintptr_t context);

/**
 * @brief Structure for UART interrupt vector.
 */
typedef struct {
    int fault; /**< Fault interrupt */
    int tx;    /**< Transmit interrupt */
    int rx;    /**< Receive interrupt */
} UART_IRQ_Vector;
/**********************************************************************
* Function Prototypes
**********************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Initializes the UART channel with the specified configuration.
 *
 * This function initializes the UART channel with the provided configuration.
 *
 * @param channel The UART channel to initialize.
 * @param flags The configuration flags for the UART channel.
 * @param baudrate The baud rate for UART communication.
 * @param rxBuffer The receive buffer for UART data.
 * @param bufferSize The size of the receive buffer.
 * @return 0 if initialization was successful.
 */
int UART_initialize(UART_Channel channel, UART_Flags flags, int baudrate, uint8_t *rxBuffer, size_t bufferSize);

/**
 * @brief Sets up the UART channel with the specified configuration.
 *
 * This function sets up the UART channel with the provided configuration.
 *
 * @param channel The UART channel to set up.
 * @param flags The configuration flags for the UART channel.
 * @param baudrate The baud rate for UART communication.
 * @return 0 if setup was successful.
 */
int UART_setup(UART_Channel channel, UART_Flags flags, int baudrate);

/**
 * @brief Writes data to the UART channel.
 *
 * This function writes the specified data to the UART channel.
 *
 * @param channel The UART channel to write data to.
 * @param txBuffer The transmit buffer containing the data to write.
 * @param size The size of the data to write.
 * @return The number of bytes written.
 */
size_t UART_write(UART_Channel channel, uint8_t *txBuffer, size_t size);

/**
 * @brief Reads data from the UART channel.
 *
 * This function reads data from the UART channel into the specified receive buffer.
 *
 * @param channel The UART channel to read data from.
 * @param rxBuffer The receive buffer to store the read data.
 * @param size The size of the receive buffer.
 * @return The number of bytes read.
 */
size_t UART_read(UART_Channel channel, uint8_t *rxBuffer, size_t size);

/**
 * @brief Starts reading data from the UART channel.
 *
 * This function starts reading data from the UART channel.
 *
 * @param channel The UART channel to start reading from.
 */
void UART_read_start(UART_Channel channel);

/**
 * @brief Aborts the ongoing UART read operation.
 *
 * This function aborts the ongoing UART read operation.
 *
 * @param channel The UART channel to abort the read operation.
 */
void UART_read_abort(UART_Channel channel);

/**
 * @brief Writes a single byte of data to the UART channel.
 *
 * This function writes a single byte of data to the UART channel.
 *
 * @param channel The UART channel to write data to.
 * @param data The byte of data to write.
 * @return The byte of data written.
 */
uint8_t UART_write_byte(UART_Channel channel, uint8_t data);

/**
 * @brief Reads a single byte of data from the UART channel.
 *
 * This function reads a single byte of data from the UART channel.
 *
 * @param channel The UART channel to read data from.
 * @return The byte of data read.
 */
uint8_t UART_read_byte(UART_Channel channel);

/**
 * @brief Checks if the UART channel is ready to transmit data.
 *
 * This function checks if the UART channel is ready to transmit data.
 *
 * @param channel The UART channel to check.
 * @return True if the UART channel is ready to transmit, false otherwise.
 */
bool UART_tx_ready(UART_Channel channel);

/**
 * @brief Retrieves the error status of the UART channel.
 *
 * This function retrieves the error status of the UART channel.
 *
 * @param channel The UART channel to get the error status from.
 * @return The error status of the UART channel.
 */
UART_ERROR UART_error_get(UART_Channel channel);

/**
 * @brief Registers a callback function for UART channel events.
 *
 * This function registers a callback function to be called when UART channel events occur.
 *
 * @param channel The UART channel to register the callback for.
 * @param callback The callback function to register.
 * @param context The context parameter to be passed to the callback function.
 */
void UART_callback_register(UART_Channel channel, UART_Callback callback, uintptr_t context);

#ifdef __cplusplus
}
#endif

#endif // UART_H
