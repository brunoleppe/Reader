/**********************************************************************
* Includes
**********************************************************************/
#include "sst26.h"
#include "Drivers/SPI/spi_driver.h"
#include "FreeRTOS.h"
#include "task.h"
#include "hal.h"
#include <string.h>
#include <xc.h>
/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/

#define OPERATION_LENGTH                4

/**********************************************************************
* Module Preprocessor Macros
**********************************************************************/

/**********************************************************************
* Module Typedefs
**********************************************************************/
typedef struct{
    DriverHandle spi;
    GPIO_PinMap ssPin;
    FlashMemID memID;
}SST26_Flash;
/*********************************************************************
* Module Variable Definitions
**********************************************************************/

static SST26_Flash sst26;

static uint8_t locks[]={WBPR,
                        0x55,0x55,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
};

static unsigned char __attribute__ ((coherent, aligned(16))) buffer[OPERATION_LENGTH + MAX_WRITE_BUFFER];

/**********************************************************************
* Function Prototypes
**********************************************************************/
static inline bool _Flash_WriteCommand(uint8_t cmd);
static inline bool _Flash_WriteData(void *txBuffer, size_t size);
//static bool sst26_sector_erase( unsigned int address);
//static bool sst26_page_program(void *data, size_t length, unsigned int address);
static bool sst26_unlock();
static bool sst26_lock();

/**********************************************************************
* Function Definitions
**********************************************************************/

void sst26_initialize(uint32_t spiDriverIndex, GPIO_PinMap ssPin)
{
    sst26.spi = SpiDriver_open(spiDriverIndex);
    sst26.ssPin = ssPin;
    SpiDriverSetup setup = {
            .csPin = ssPin,
            .sample = SPI_SAMPLE_END,
            .spiMode = SPI_MODE_3,
            .baudRate = FLASH_SPEED
    };
    SpiDriver_setup(sst26.spi, &setup);
    sst26.memID.manufacturerId = Microchip;
}

bool sst26_sector_erase(unsigned int address)
{
    buffer[0]=SE;
    buffer[1]=address>>16;
    buffer[2]=address>>8;
    buffer[3]=address;
    _Flash_WriteCommand(WREN);
    _Flash_WriteCommand(ULBPR);
    vTaskDelay(25);
    _Flash_WriteCommand(WREN);
    bool res = SpiDriver_write_dma(sst26.spi, buffer, 4);
    vTaskDelay(50);
    return res;
}


bool sst26_page_program(void *data, size_t length, unsigned int address)
{
    buffer[0] = 0x02;
    buffer[1] = address >> 16;
    buffer[2] = address >> 8;
    buffer[3] = address;
    memcpy(buffer+4, data, length);
    _Flash_WriteCommand(WREN);
    bool res = SpiDriver_write_dma(sst26.spi, buffer, length + 4);
    vTaskDelay(2);
    return res;
}

MEM_TYPE sst26_get_type(){
    return sst26.memID.manufacturerId;
}

FlashMemID* sst26_read_id()
{
    uint8_t jedec[] = {JEDEC,0,0,0};
    uint8_t rxBuffer[4];
    GPIO_pin_write(sst26.ssPin, GPIO_LOW);
    SpiDriver_transfer(sst26.spi, jedec, rxBuffer, 4);
    GPIO_pin_write(sst26.ssPin, GPIO_HIGH);
    memcpy(&sst26.memID, rxBuffer + 1, 3);
    return &sst26.memID;
}
bool sst26_write(void* data, int length, unsigned int address)
{
    if(!sst26_unlock())
        return false;
    uint8_t rep = length/0x1000 + ((length%0x1000) != 0);
    int i;
    for(i = 0;i<rep;i++)
    {
        if(!sst26_sector_erase((address & 0xFFFFF000) + i * 0x1000))
            return false;
    }

    uint8_t repeat = length / MAX_WRITE_BUFFER;
    uint8_t repeat_over = length % MAX_WRITE_BUFFER;

    for ( i = 0; i < repeat; i++ )
    {
        if(!sst26_page_program(data, MAX_WRITE_BUFFER, address))
            return false;
        address+=MAX_WRITE_BUFFER;
        data=(uint8_t*)data+MAX_WRITE_BUFFER;
    }
    if ( repeat_over )
    {
        if(!sst26_page_program(data, repeat_over, address))
            return false;
    }

    if(!sst26_lock())
        return false;

    return true;

}
bool sst26_read(void* data, int length, unsigned int address)
{
    bool res;
    uint8_t op[4];
    op[0] = 0x03;
    op[1] = address >> 16;
    op[2] = address >> 8;
    op[3] = address;
    res = SpiDriver_write_read(sst26.spi, op, 4, data, length);
    return res;
}

static inline bool _Flash_WriteCommand(uint8_t cmd)
{
//    uint8_t dummy;
    bool res = SpiDriver_transfer(sst26.spi, &cmd, NULL, 1);
    return res;
}

static inline bool _Flash_WriteData(void *txBuffer, size_t size)
{
    bool res = SpiDriver_write_dma(sst26.spi, txBuffer, size);
    return res;
}
static bool sst26_unlock()
{
    if(sst26.memID.manufacturerId != Microchip)
        return true;

    if(!_Flash_WriteCommand(WREN))
        return false;
    if(!_Flash_WriteCommand(ULBPR))
        return false;
    vTaskDelay(25);
    return true;
}
static bool sst26_lock() {
    if (sst26.memID.manufacturerId == Microchip)
        return _Flash_WriteData(locks, sizeof(locks));
    return true;
}