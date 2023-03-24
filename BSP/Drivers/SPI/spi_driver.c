//
// Created by bleppe on 21/03/23.
//
/***********************************************************************************************************************
* Includes
***********************************************************************************************************************/
#include "spi_driver.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "debug.h"
/***********************************************************************************************************************
* Module Preprocessor Constants
***********************************************************************************************************************/

/***********************************************************************************************************************
* Module Preprocessor Macros
***********************************************************************************************************************/

/***********************************************************************************************************************
* Module Typedefs
***********************************************************************************************************************/
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
/**********************************************************************************************************************
* Module Variable Definitions
***********************************************************************************************************************/
SpiDriverObject spiDriverInstances[SPI_DRIVER_INSTANCES];
/***********************************************************************************************************************
* Function Prototypes
***********************************************************************************************************************/
static void SPI_callback_function(SPI_Channel channel, uintptr_t context);
static uintptr_t SPI_Driver_handle_create(uint32_t driverIndex, uint32_t clientIndex, uint32_t token);
static SpiClientObject* SPI_Driver_handle_validate(uintptr_t handle);
/***********************************************************************************************************************
* Function Definitions
***********************************************************************************************************************/

int SpiDriver_initialize(uint32_t driverIndex, SpiDriverInit *driverInit)
{
    if(driverIndex >= SPI_DRIVER_INSTANCES || driverInit == NULL)
        return -1;


    SpiDriverObject *dObj = &spiDriverInstances[driverIndex];

    if(dObj->inUse)
        return -1;

    dObj->spiChannel = driverInit->spiChannel;
    dObj->txDmaChannel = driverInit->txDmaChannel;
    dObj->rxDmaChannel = driverInit->rxDmaChannel;
    dObj->nClientsMax = driverInit->nClientsMax;
    dObj->clientArray = driverInit->clientArray;
    dObj->nClients = 0;
    dObj->clientToken = 1;
    dObj->activeClient = NULL;

    if((dObj->clientMutex = xSemaphoreCreateMutex()) == NULL)
        return -1;
    if((dObj->hardwareMutex = xSemaphoreCreateMutex()) == NULL)
        return -1;
    if((dObj->transferSemaphore = xSemaphoreCreateBinary()) == NULL)
        return -1;

    SPI_callback_register(dObj->spiChannel, SPI_callback_function, (uintptr_t)dObj);

    dObj->inUse = true;
    return 0;
}
DriverHandle SpiDriver_open(uint32_t driverIndex)
{
    if(driverIndex >= SPI_DRIVER_INSTANCES)
        return 0;
    SpiDriverObject *dObj = &spiDriverInstances[driverIndex];
    if(!dObj->inUse)
        return (uintptr_t)NULL;

    if(dObj->nClients >= dObj->nClientsMax)
        return 0;

    if(xSemaphoreTake(dObj->clientMutex, portMAX_DELAY) == pdFALSE)
        return 0;

    SpiClientObject *client = NULL;
    uintptr_t   clientHandle = 0;

    for(int i=0; i<dObj->nClientsMax; i++){
        if(!dObj->clientArray[i].inUse){
            client = &dObj->clientArray[i];
            break;
        }
    }
    if(client != NULL) {
        client->driverObject = dObj;
        client->clientHandle = SPI_Driver_handle_create(driverIndex, dObj->nClients, dObj->clientToken);
        client->inUse = true;
        client->setupChanged = false;
        client->csPin = 0xFFFFFFFF;
        dObj->nClients++;
        dObj->clientToken++;
        dObj->activeClient = client;
        clientHandle = client->clientHandle;
    }
    xSemaphoreGive(dObj->clientMutex);
    return clientHandle;
}
int SpiDriver_setup(DriverHandle handle, SpiDriverSetup *setup)
{
    SpiClientObject *obj = SPI_Driver_handle_validate(handle);
    if(obj == NULL)
        return -1;
    obj->setupChanged = true;
    obj->setup = *setup;
    obj->csPin = setup->csPin;
    return 0;
}
size_t SpiDriver_transfer(DriverHandle handle, void *txBuffer, void *rxBuffer, size_t size)
{
    SpiClientObject *client = SPI_Driver_handle_validate(handle);
    if(client == NULL)
        return 0;
    SpiDriverObject *dObj = client->driverObject;

    if(xSemaphoreTake(dObj->hardwareMutex, portMAX_DELAY) == pdFALSE)
        return 0;

    if(dObj->activeClient != client || client->setupChanged)
    {
        SPI_setup(dObj->spiChannel, client->setup.sample | client->setup.spiMode, client->setup.baudRate);
        client->setupChanged = false;
    }

    dObj->activeClient = client;
    if(client->csPin != GPIO_PIN_INVALID)
        GPIO_pin_write(client->csPin, GPIO_LOW);

    size_t result = SPI_transfer(dObj->spiChannel, txBuffer, rxBuffer, size);

    if(client->csPin != GPIO_PIN_INVALID)
        GPIO_pin_write(client->csPin, GPIO_HIGH);

    xSemaphoreGive(dObj->hardwareMutex);

    return result;
}
bool SpiDriver_byte_transfer(DriverHandle handle, uint8_t data, uint8_t *outData)
{
    SpiClientObject *client = SPI_Driver_handle_validate(handle);
    if(client == NULL)
        return false;

//    DEBUG_PRINT("validated\n\r");

    SpiDriverObject *dObj = client->driverObject;

    if(xSemaphoreTake(dObj->hardwareMutex, portMAX_DELAY) == pdFALSE)
        return false;

    if(dObj->activeClient != client || client->setupChanged)
    {
        SPI_setup(dObj->spiChannel, client->setup.sample | client->setup.spiMode, client->setup.baudRate);
        client->setupChanged = false;
    }

    dObj->activeClient = client;
    if(client->csPin != GPIO_PIN_INVALID)
        GPIO_pin_write(client->csPin, GPIO_LOW);

    *outData = SPI_byte_transfer(dObj->spiChannel, data);

    if(client->csPin != GPIO_PIN_INVALID)
        GPIO_pin_write(client->csPin, GPIO_LOW);

    xSemaphoreGive(dObj->hardwareMutex);

    return true;
}
bool SpiDriver_write_dma(DriverHandle handle, void *txBuffer, size_t size)
{
    SpiClientObject *client = SPI_Driver_handle_validate(handle);
    if(client == NULL)
        return 0;
    SpiDriverObject *dObj = client->driverObject;

    if(xSemaphoreTake(dObj->hardwareMutex, portMAX_DELAY) == pdFALSE)
        return 0;

    if(dObj->activeClient != client || client->setupChanged)
    {
        SPI_setup(dObj->spiChannel, client->setup.sample | client->setup.spiMode, client->setup.baudRate);
        client->setupChanged = false;
    }

    dObj->activeClient = client;
    if(client->csPin != GPIO_PIN_INVALID)
        GPIO_pin_write(client->csPin, GPIO_LOW);

    bool result = SPI_write_dma(dObj->spiChannel, dObj->txDmaChannel, txBuffer, size);

    if (result && xSemaphoreTake(dObj->transferSemaphore, portMAX_DELAY) == pdTRUE){
        result = true;
    }

    xSemaphoreGive(dObj->hardwareMutex);

    return result;
}

static void SPI_callback_function(SPI_Channel channel, uintptr_t context)
{
    (void)channel;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    SpiDriverObject *dObj = (SpiDriverObject*)context;
    if(dObj->activeClient->setup.csPin != GPIO_PIN_INVALID){
        GPIO_pin_write(dObj->activeClient->setup.csPin, GPIO_HIGH);
    }
    xSemaphoreGiveFromISR(dObj->transferSemaphore, &xHigherPriorityTaskWoken);
    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}
static uintptr_t SPI_Driver_handle_create(uint32_t driverIndex, uint32_t clientIndex, uint32_t token)
{
    const int magic = 0xBAD5;
    return (((token|magic) << 16) | (clientIndex << 8) | driverIndex);
}
static SpiClientObject*  SPI_Driver_handle_validate(uintptr_t handle)
{
    if(handle == 0)
        return NULL;
    uint32_t driverIndex = (handle) & 0xFF;
    uint32_t clientIndex = (handle >> 8) & 0xFF;
    if(driverIndex >= SPI_DRIVER_INSTANCES)
        return NULL;
    SpiDriverObject *obj = &spiDriverInstances[driverIndex];
    if(clientIndex >= obj->nClientsMax)
        return NULL;

    SpiClientObject *client = &obj->clientArray[clientIndex];
    if(!client->inUse || client->clientHandle != handle)
        return NULL;
    return client;
}