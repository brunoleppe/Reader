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

#include "hal.h"
#include "gpio.h"

/**********************************************************************
* Preprocessor Constants
**********************************************************************/
/**
 * Number of SPI peripherals of processor.
*/
#define NUMBER_OF_SPI_CHANNELS              (6)
/**********************************************************************
* Typedefs
**********************************************************************/

/**
 * @brief Struct that defines the data structure for SPI transfers.
 *
 */
typedef struct _SPI_Handler *SPI_Handler;
/**
 * @brief SPI callback functions definition
 *
 */
typedef void (*SPI_Callback)(SPI_Handler);

/**
 * @brief SPI error flags.
 *
 */
typedef enum{
    /*Errores en la transferencia spi*/
    SPI_ERROR_NULL_BUFFERS = 1, ///<Both TX and RX buffers are NULL when calling SPI_Transfer.
    SPI_ERROR_ZERO_SIZE_BUFFER, ///<A buffer size of 0 was passed to a transfer function.
    SPI_ERROR_BAUDRATE_TOO_LOW, ///<Specified baudrate too low, cannot configure baudrate generator.
    SPI_ERROR_BAD_SPI_MODE,     ///<SPI mode not supported
    SPI_ERROR_CHANNEL_BUSY,     ///<SPI channel is busy.
}SPI_ERROR;
/**
 * @brief Possible SPI Modes for SPI channel.
 *
 */
typedef enum{
    SPI_MODE_0,
    SPI_MODE_1,
    SPI_MODE_2,
    SPI_MODE_3,
}SPI_MODE;
/**
 * @brief Possible SPI channel working mode.
 *
 */
typedef enum{
    SPI_MASTER,
    SPI_SLAVE,
}SPI_MASTER_SLAVE;
/**
 * @brief Available SPI channel for current processor.
 *
 */
typedef enum{
    SPI_CHANNEL_1=0,
    SPI_CHANNEL_2,
    SPI_CHANNEL_3,
    SPI_CHANNEL_4,
    SPI_CHANNEL_5,
    SPI_CHANNEL_6,
}SPI_CHANNEL;
/**
 * @brief Possible data sampling schemes for current processor.
 *
 */
typedef enum{
    SPI_SAMPLE_END,
    SPI_SAMPLE_MID
}SPI_DATA_SAMPLE;
/**
 * @brief Configuration table.
 * This table is used to configure SPI peripherals on initialization function.
 *
 */
typedef struct{
    SPI_MODE mode; ///<SPI mode
    SPI_MASTER_SLAVE mastermode;///<SPI working mode
    uint32_t baudrate;///<SPI channel baudrate;
    SPI_DATA_SAMPLE sample;///<SPI channel sampling scheme
}SPI_Setup;

/**
 * @brief Struct that defines the data structure for SPI transfers.
 *
 */
struct _SPI_Handler{
    SPI_CHANNEL         channel;
    SPI_Setup           setup; ///<Configuration table of current SPI peripheral.

    uint8_t             *txBuffer; ///<Pointer to TX buffer.
    size_t              txSize; ///<Size of TX buffer.
    size_t              txCount; ///<Maintains the count of transfered bytes, when txCount == txSize all bytes are transmited.

    uint8_t             *rxBuffer; ///<Pointer to RX buffer.
    size_t              rxSize; ///<Size of RX buffer.
    size_t              rxCount; ///<Maintains the count of transfered bytes, when rxCount == rxSize all bytes are received.

    size_t              dummySize; ///<Member that specifies dummy bytes to transmit when a transfer is only receiving data.

    SPI_ERROR           error; ///<Contains the error.

    uint32_t            usDelay; ///<Time in us to wait between every transfered byte. Useful when dealing with QTouch comms. Used in blocking transfers.
    uint8_t             dummyByte;///<Value to transmit when a transfer is only receiving data.

    bool                busy; ///<Busy state of the SPI channel. True when a transfer is in progress.

    SPI_Callback        errorCallback; ///<Function to be called when an error occurs.
    SPI_Callback        cpltCallback; ///<Function to be called when a byte has been transfered.
    SPI_Callback        halfCallback; ///<Function to be called when a transfer is completed.
};

/**********************************************************************
* Function Prototypes
**********************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

int SPI_Init(SPI_Handler config, SPI_CHANNEL channel, SPI_Setup *setup);
int SPI_Transfer(const SPI_Handler handler, void *txBuffer, void *rxBuffer, size_t size);
uint8_t SPI_TransferByte(const SPI_Handler handler, uint8_t data);
bool SPI_TransferSetup(const SPI_Handler handler, SPI_Setup *setup);
int SPI_InputMapping(SPI_CHANNEL channel, GPIO_ALTERNATE_FUNCTION alternate_function);

static inline int SPI_Write(const SPI_Handler handler, void *txBuffer, size_t size){
    return SPI_Transfer(handler,txBuffer,NULL,size);
}

static inline int SPI_Read(const SPI_Handler handler, void *rxBuffer, size_t size){
    return SPI_Transfer(handler,NULL,rxBuffer,size);
}

static inline
void SPI_ErrorCallbackRegister(SPI_Handler handler,SPI_Callback callback)
{
    handler->errorCallback = callback;
}

static inline
void SPI_CpltCallbackRegister(SPI_Handler handler,SPI_Callback callback)
{
    handler->cpltCallback = callback;
}

static inline
void SPI_HalfCpltcallbackRegister(SPI_Handler handler,SPI_Callback callback)
{
    handler->halfCallback = callback;
}


#ifdef __cplusplus
}
#endif

#endif /*SPI_H*/