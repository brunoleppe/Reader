//
// Created by bleppe on 21/03/23.
//

#ifndef READER_SPI_DRIVER_H
#define READER_SPI_DRIVER_H

/***********************************************************************************************************************
* Includes
***********************************************************************************************************************/
#include "HAL/spi.h"
#include "HAL/gpio.h"
#include "spi_driver_config.h"
/***********************************************************************************************************************
* Preprocessor Constants
***********************************************************************************************************************/

/***********************************************************************************************************************
* Typedefs
***********************************************************************************************************************/
typedef struct  SpiDriverInit{
    SPI_Channel                     spiChannel;
    DMA_Channel                     txDmaChannel;
    DMA_Channel                     rxDmaChannel;
    int                             nClientsMax;
    void*                           clientArray;
}SpiDriverInit;

typedef struct SpiDriverSetup{
    int                             baudRate;
    int                             spiMode;
    int                             sample;
    GPIO_PinMap                     csPin;
}SpiDriverSetup;

typedef struct SpiClientObject{
    void*                           driverObject;
    bool                            inUse;
    SpiDriverSetup                  setup;
    bool                            setupChanged;
    uintptr_t                       clientHandle;
    GPIO_PinMap                     csPin;
}SpiClientObject;

typedef uintptr_t SpiDriverHandle;
/***********************************************************************************************************************
* Function Prototypes
***********************************************************************************************************************/

int SpiDriver_initialize(uint32_t driverIndex, SpiDriverInit *driverInit);
SpiDriverHandle SpiDriver_open(uint32_t driverIndex);
int SpiDriver_setup(SpiDriverHandle handle, SpiDriverSetup *setup);
size_t SpiDriver_transfer(SpiDriverHandle handle, void *txBuffer, void *rxBuffer, size_t size);
bool SpiDriver_byte_transfer(SpiDriverHandle handle, uint8_t data, uint8_t *outData);
bool SpiDriver_write_dma(SpiDriverHandle handle, void *txBuffer, size_t size);


#endif //READER_SPI_DRIVER_H
