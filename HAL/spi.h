/**
 * @file spi.h
 * @author Bruno Leppe (bruno.leppe.dev@gmail.com)
 * @brief SPI peripheral definitions.
 * @version 0.1
 * @date 2022-09-29
 */

/*******************************************************************************
* Copyright (c) 2022 Bruno Leppe
* Permission is hereby granted, free of charge, to any person
* obtaining a copy of this software and associated documentation
* files (the "Software"), to deal in the Software without
* restriction, including without limitation the rights to use,
* copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following
* conditions:
*
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
* OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
* HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*******************************************************************************/

#ifndef SPI_H
#define SPI_H

/**********************************************************************
* Includes
**********************************************************************/

#include "hal_defs.h"

/**********************************************************************
* Preprocessor Constants
**********************************************************************/


#define SPI_CHANNEL_1                       (0)
#define SPI_CHANNEL_2                       (1)
#define SPI_CHANNEL_3                       (2)
#define SPI_CHANNEL_4                       (3)
#define SPI_CHANNEL_5                       (4)
#define SPI_CHANNEL_6                       (5)

/*Configuration Flags*/
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
typedef struct{
    uint32_t        usDelay;
    uint8_t         stopChar;
    bool            stopCharEnable;
}SPI_TransferSetup;

typedef struct{
    bool            busy;
    void            *txBuffer;
    void            *rxBuffer;
    size_t          count;
    size_t          rxSize;
    size_t          txSize;
}SPI_Object;

///**
// * @brief Configuration table.
// * This table is used to configure SPI peripherals on initialization function.
// *
// */
//typedef struct{
//    SPI_MODE mode; ///<SPI mode
//    SPI_MASTER_SLAVE mastermode;///<SPI working mode
//    uint32_t baudrate;///<SPI channel baudrate;
//    SPI_DATA_SAMPLE sample;///<SPI channel sampling scheme
//}SPI_Setup;
//
///**
// * @brief Struct that defines the data structure for SPI transfers.
// *
// */
//struct _SPI_Handler{
//    SPI_CHANNEL         channel;
//    SPI_Setup           setup; ///<Configuration table of current SPI peripheral.
//
//    uint8_t             *txBuffer; ///<Pointer to TX buffer.
//    size_t              txSize; ///<Size of TX buffer.
//    size_t              txCount; ///<Maintains the count of transfered bytes, when txCount == txSize all bytes are transmited.
//
//    uint8_t             *rxBuffer; ///<Pointer to RX buffer.
//    size_t              rxSize; ///<Size of RX buffer.
//    size_t              rxCount; ///<Maintains the count of transfered bytes, when rxCount == rxSize all bytes are received.
//
//    size_t              dummySize; ///<Member that specifies dummy bytes to transmit when a transfer is only receiving data.
//
//    SPI_ERROR           error; ///<Contains the error.
//
//    uint32_t            usDelay; ///<Time in us to wait between every transfered byte. Useful when dealing with QTouch comms. Used in blocking transfers.
//    uint8_t             dummyByte;///<Value to transmit when a transfer is only receiving data.
//
//    bool                busy; ///<Busy state of the SPI channel. True when a transfer is in progress.
//
//    SPI_Callback        errorCallback; ///<Function to be called when an error occurs.
//    SPI_Callback        cpltCallback; ///<Function to be called when a byte has been transfered.
//    SPI_Callback        halfCallback; ///<Function to be called when a transfer is completed.
//};

/**********************************************************************
* Function Prototypes
**********************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

int         SPI_initialize      (uint32_t spiChannel, uint32_t configFlags, uint32_t baudrate);
size_t      SPI_transfer        (uint32_t spiChannel, const SPI_TransferSetup *setup, void *txBuffer, void *rxBuffer, size_t size);
uint8_t     SPI_byte_transfer   (uint32_t spiChannel, uint8_t data);
size_t      SPI_transfer_isr    (uint32_t spiChannel, const SPI_TransferSetup *setup, void *txBuffer, void *rxBuffer, size_t size);
//bool SPI_TransferSetup(const SPI_Handler spiChannel, SPI_Setup *setup);

static inline
size_t      SPI_Write           (uint32_t spiChannel, SPI_TransferSetup *setup, void *txBuffer, size_t size)
{
    return SPI_transfer(spiChannel, setup, txBuffer, NULL, size);
}

static inline
size_t      SPI_Read            (uint32_t spiChannel,  SPI_TransferSetup *setup, void *rxBuffer, size_t size)
{
    return SPI_transfer(spiChannel, setup, NULL, rxBuffer, size);
}

#ifdef __cplusplus
}
#endif

#endif /*SPI_H*/