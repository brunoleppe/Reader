/**
 * @file spi.h
 * @author Bruno Leppe (bruno.leppe.dev\@gmail.com)
 * @brief SPI peripheral definitions.
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

#ifndef SPI_H
#define SPI_H

/**********************************************************************
* Includes
**********************************************************************/

#include "hal_defs.h"

/**********************************************************************
* Preprocessor Constants
**********************************************************************/

/**
 * @brief Defines the channel number for SPI.
 */
#define SPI_CHANNEL_1                       (0)
#define SPI_CHANNEL_2                       (1)
#define SPI_CHANNEL_3                       (2)
#define SPI_CHANNEL_4                       (3)
#define SPI_CHANNEL_5                       (4)
#define SPI_CHANNEL_6                       (5)

/**
 * @brief Configuration Flags for SPI.
 */
#define SPI_MODE_0                          (0x0000)
#define SPI_MODE_1                          (0x0001)
#define SPI_MODE_2                          (0x0002)
#define SPI_MODE_3                          (0x0004)
#define SPI_SLAVE                           (0x0000)
#define SPI_MASTER                          (0x0010)
#define SPI_SAMPLE_MID                      (0x0000)
#define SPI_SAMPLE_END                      (0x0020)
#define SPI_DATA_BITS_8                     (0x0000)
#define SPI_DATA_BITS_16                    (0x0040)
#define SPI_DATA_BITS_32                    (0x0080)
#define SPI_SDO_DISABLE                     (0x0100)
#define SPI_SDI_DISABLE                     (0x0200)
#define SPI_SS_ENABLE                       (0x0400)
#define SPI_IRQ_ENABLE                      (0x0800)

#define SPI_DEFAULT                         (SPI_MODE_0 | SPI_MASTER | SPI_SAMPLE_MID | SPI_DATA_BITS_8)

/**********************************************************************
* Typedefs
**********************************************************************/

typedef uint32_t SPI_Channel;

/**
 * @brief Structure representing the setup parameters for an SPI transfer.
 */
typedef struct{
    uint32_t        usDelay;            /**< The delay in microseconds between bytes during a transfer. */
    uint8_t         stopChar;           /**< The stop character to be transmitted after the transfer. */
    bool            stopCharEnable;     /**< Flag indicating whether the stop character should be transmitted. */
}SPI_TransferSetup;

/**
 * @brief Callback function type for SPI events.
 *
 * @param spiChannel The SPI channel number.
 * @param context User-defined context data.
 */
typedef void (*SPI_Callback)(SPI_Channel spiChannel, uintptr_t context);

/**
 * @brief Structure representing the IRQ (Interrupt Request) vectors for SPI.
 */
typedef struct{
    int fault;  /**< Fault IRQ vector. */
    int tx;     /**< Transmit IRQ vector. */
    int rx;     /**< Receive IRQ vector. */
}SPI_IRQ_Vector;

/**********************************************************************
* Function Prototypes
**********************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Initializes the SPI module.
 *
 * This function initializes the specified SPI channel with the provided configuration flags and baudrate.
 *
 * @param spiChannel The SPI channel number.
 * @param configFlags The configuration flags for the SPI channel.
 * @param baudrate The desired baudrate for the SPI channel.
 * @return 0 on success, or a negative error code on failure.
 */
int         SPI_initialize              (uint32_t spiChannel, uint32_t configFlags, uint32_t baudrate);

/**
 * @brief Performs a full-duplex SPI transfer.
 *
 * This function performs a full-duplex SPI transfer, simultaneously transmitting and receiving data.
 *
 * @param spiChannel The SPI channel number.
 * @param txBuffer Pointer to the transmit buffer.
 * @param rxBuffer Pointer to the receive buffer.
 * @param size The number of bytes to transfer.
 * @return The number of bytes transferred.
 */
size_t      SPI_transfer                (uint32_t spiChannel, void *txBuffer, void *rxBuffer, size_t size);

/**
 * @brief Performs a single-byte SPI transfer.
 *
 * This function performs a single-byte SPI transfer, transmitting the given data and returning the received data.
 *
 * @param spiChannel The SPI channel number.
 * @param data The byte to transmit.
 * @return The received byte.
 */
uint8_t     SPI_byte_transfer           (uint32_t spiChannel, uint8_t data);

/**
 * @brief Checks if the SPI module is busy.
 *
 * This function checks if the SPI module is currently busy with a transfer.
 *
 * @param spiChannel The SPI channel number.
 * @return True if the SPI module is busy, false otherwise.
 */
bool        SPI_is_busy                 (uint32_t spiChannel);

/**
 * @brief Registers a callback function for SPI events.
 *
 * This function registers a callback function to be called when an SPI event occurs.
 *
 * @param spiChannel The SPI channel number.
 * @param callback The callback function to register.
 * @param context User-defined context data to be passed to the callback.
 */
void        SPI_callback_register       (SPI_Channel spiChannel, SPI_Callback callback, uintptr_t context);

/**
 * @brief Performs an SPI transfer using interrupt service routine (ISR).
 *
 * This function performs an SPI transfer using interrupt service routine (ISR).
 * It is intended to be called from the ISR when an SPI interrupt occurs.
 *
 * @param spiChannel The SPI channel number.
 * @param txBuffer Pointer to the transmit buffer.
 * @param rxBuffer Pointer to the receive buffer.
 * @param size The number of bytes to transfer.
 * @return True if the transfer is successful, false otherwise.
 */
bool        SPI_transfer_isr            (uint32_t spiChannel, void* txBuffer, void* rxBuffer, size_t size);

/**
 * @brief Handler for the SPI receive interrupt.
 *
 * This function is the handler for the SPI receive interrupt.
 * It is intended to be called from the ISR when an SPI receive interrupt occurs.
 *
 * @param spiChannel The SPI channel number.
 */
void        SPI_rx_interrupt_handler    (SPI_Channel spiChannel);

/**
 * @brief Handler for the SPI transmit interrupt.
 *
 * This function is the handler for the SPI transmit interrupt.
 * It is intended to be called from the ISR when an SPI transmit interrupt occurs.
 *
 * @param spiChannel The SPI channel number.
 */
void        SPI_tx_interrupt_handler    (SPI_Channel spiChannel);

/**
 * @brief Performs an SPI write using DMA (Direct Memory Access).
 *
 * This function performs an SPI write using DMA (Direct Memory Access).
 *
 * @param spiChannel The SPI channel number.
 * @param dmaChannel The DMA channel number to use for the transfer.
 * @param txBuffer Pointer to the transmit buffer.
 * @param size The number of bytes to transfer.
 * @return True if the transfer is successful, false otherwise.
 */
bool        SPI_write_dma               (SPI_Channel spiChannel, uint32_t dmaChannel, void *txBuffer, size_t size);

/**
 * @brief Performs an SPI read using DMA (Direct Memory Access).
 *
 * This function performs an SPI read using DMA (Direct Memory Access).
 *
 * @param spiChannel The SPI channel number.
 * @param dmaChannel The DMA channel number to use for the transfer.
 * @param rxBuffer Pointer to the receive buffer.
 * @param size The number of bytes to transfer.
 * @return True if the transfer is successful, false otherwise.
 */
bool        SPI_read_dma                (SPI_Channel spiChannel, uint32_t dmaChannel, void *rxBuffer, size_t size);

/**
 * @brief Sets up the SPI channel with the specified configuration.
 *
 * This function sets up the SPI channel with the specified configuration.
 *
 * @param spiChannel The SPI channel number.
 * @param configFlags The configuration flags for the SPI channel.
 * @param baudrate The desired baudrate for the SPI channel.
 */
void        SPI_setup                   (SPI_Channel spiChannel, uint32_t configFlags, uint32_t baudrate);

/**
 * @brief Performs an SPI write.
 *
 * This function performs an SPI write, transmitting data from the transmit buffer.
 *
 * @param spiChannel The SPI channel number.
 * @param txBuffer Pointer to the transmit buffer.
 * @param size The number of bytes to transfer.
 * @return The number of bytes transferred.
 */
static inline
size_t      SPI_write           (uint32_t spiChannel, void *txBuffer, size_t size)
{
    return SPI_transfer(spiChannel, txBuffer, NULL, size);
}

/**
 * @brief Performs an SPI read.
 *
 * This function performs an SPI read, receiving data into the receive buffer.
 *
 * @param spiChannel The SPI channel number.
 * @param rxBuffer Pointer to the receive buffer.
 * @param size The number of bytes to transfer.
 * @return The number of bytes transferred.
 */
static inline
size_t      SPI_read            (uint32_t spiChannel, void *rxBuffer, size_t size)
{
    return SPI_transfer(spiChannel, NULL, rxBuffer, size);
}

/**
 * @brief Performs an SPI write using interrupt service routine (ISR).
 *
 * This function performs an SPI write using interrupt service routine (ISR),
 * transmitting data from the transmit buffer.
 *
 * @param spiChannel The SPI channel number.
 * @param txBuffer Pointer to the transmit buffer.
 * @param size The number of bytes to transfer.
 * @return The number of bytes transferred.
 */
static inline
size_t      SPI_write_isr       (uint32_t spiChannel, void *txBuffer, size_t size)
{
    return SPI_transfer_isr(spiChannel, txBuffer, NULL, size);
}

/**
 * @brief Performs an SPI read using interrupt service routine (ISR).
 *
 * This function performs an SPI read using interrupt service routine (ISR),
 * receiving data into the receive buffer.
 *
 * @param spiChannel The SPI channel number.
 * @param rxBuffer Pointer to the receive buffer.
 * @param size The number of bytes to transfer.
 * @return The number of bytes transferred.
 */
static inline
size_t      SPI_read_isr        (uint32_t spiChannel, void *rxBuffer, size_t size)
{
    return SPI_transfer_isr(spiChannel, NULL, rxBuffer, size);
}

#ifdef __cplusplus
}
#endif
#endif /* SPI_H */