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
#include "HAL/dma.h"
#include "spi_driver_config.h"
#include "Drivers/driver_defs.h"
#include "FreeRTOS.h"
#include "semphr.h"
/***********************************************************************************************************************
* Preprocessor Constants
***********************************************************************************************************************/

/***********************************************************************************************************************
* Typedefs
***********************************************************************************************************************/
struct SpiDriverObject;

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
    struct SpiDriverObject*         driverObject;
    bool                            inUse;
    SpiDriverSetup                  setup;
    bool                            setupChanged;
    uintptr_t                       clientHandle;
    GPIO_PinMap                     csPin;
}SpiClientObject;

typedef struct SpiDriverObject{
    bool                        inUse;
    SPI_Channel                 spiChannel;
    DMA_Channel                 txDmaChannel;
    DMA_Channel                 rxDmaChannel;
    int                         nClients;
    int                         clientToken;
    int                         nClientsMax;
    SpiClientObject*            clientArray;
    SpiClientObject*            activeClient;
    SemaphoreHandle_t           clientMutex;
    SemaphoreHandle_t           hardwareMutex;
    SemaphoreHandle_t           transferSemaphore;
}SpiDriverObject;

/***********************************************************************************************************************
* Function Prototypes
***********************************************************************************************************************/

int SpiDriver_initialize(uint32_t driverIndex, SpiDriverInit *driverInit);
DriverHandle SpiDriver_open(uint32_t driverIndex);
int SpiDriver_setup(DriverHandle handle, SpiDriverSetup *setup);
size_t SpiDriver_transfer(DriverHandle handle, void *txBuffer, void *rxBuffer, size_t size);
bool SpiDriver_byte_transfer(DriverHandle handle, uint8_t data, uint8_t *outData);
bool SpiDriver_write_dma(DriverHandle handle, void *txBuffer, size_t size);
bool SpiDriver_read_dma(DriverHandle handle, void *rxBuffer, size_t size);
bool SpiDriver_write_read(DriverHandle handle, void *txBuffer, size_t txSize, void *rxBuffer, size_t rxSize);
bool SpiDriver_transfer_custom(DriverHandle handle, void (*custom)(void));
SpiClientObject* SpiDriver_get_object(DriverHandle handle);
bool SpiDriver_mutex_take(DriverHandle handle, uint32_t blockTime);
bool SpiDriver_mutex_release(DriverHandle handle);
#endif //READER_SPI_DRIVER_H
