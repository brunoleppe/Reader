//
// Created by bleppe on 03/04/23.
//

#include "sst26.h"
#include "Drivers/SPI/spi_driver.h"
#include "FreeRTOS.h"
#include "task.h"
#include "hal.h"
#include <string.h>


typedef struct{
    DriverHandle spi;
    GPIO_PinMap ssPin;
    FlashMemID memID;
}sst26;

static uint8_t locks[]={WBPR,
                        0x55,0x55,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
};

static sst26 mem;

static inline bool _Flash_WriteCommand(uint8_t cmd)
{
    uint8_t dummy;
    GPIO_pin_write(mem.ssPin, GPIO_LOW);
    bool res = SpiDriver_transfer(mem.spi,&cmd,NULL,1);
    GPIO_pin_write(mem.ssPin, GPIO_HIGH);
    return res;
}

static inline bool _Flash_WriteData(void *txBuffer, size_t size)
{
    GPIO_pin_write(mem.ssPin, GPIO_LOW);
    bool res = SpiDriver_write_dma(mem.spi,txBuffer,size);
    GPIO_pin_write(mem.ssPin, GPIO_HIGH);
    return res;
}

static bool _Flash_SectorErase(unsigned int address)
{
    _Flash_WriteCommand(WREN);
    uint8_t buffer[4];
    buffer[0]=SE;
    buffer[1]=address>>16;
    buffer[2]=address>>8;
    buffer[3]=address;
    if(!_Flash_WriteData(buffer,4))
        return false;
    if(mem.memID.mID == Microchip)
        vTaskDelay(50);
    else
        vTaskDelay(100);
    return true;
}
static bool _Flash_Unlock()
{
    if(mem.memID.mID != Microchip)
        return true;

    if(!_Flash_WriteCommand(WREN))
        return false;
    if(!_Flash_WriteCommand(ULBPR))
        return false;
    vTaskDelay(25);
    return true;
}
static bool _Flash_Lock()
{
    if(mem.memID.mID == Microchip)
        return _Flash_WriteData(locks,sizeof(locks));
    return true;
}
static bool _Flash_PageProgram(void* buffer, size_t len, unsigned int address)
{
    if(!_Flash_WriteCommand(WREN))
        return false;
    uint8_t *op = pvPortMalloc(len+4);
    op[0] = 0x02;
    op[1] = address >> 16;
    op[2] = address >> 8;
    op[3] = address;
    memcpy(op+4, buffer, len);
    GPIO_pin_write(mem.ssPin, GPIO_LOW);
    bool res =SpiDriver_write_dma(mem.spi, op, len+4);
//    bool res = SpiDriver_write_dma(mem.spi, op, 4);
//    res = SpiDriver_write_dma(mem.spi, buffer,len);
    GPIO_pin_write(mem.ssPin, GPIO_HIGH);
    vPortFree(op);
    return res;
}

bool sst26_sector_erase(int address)
{
    _Flash_WriteCommand(WREN);
    _Flash_WriteCommand(ULBPR);
    vTaskDelay(25);
    _Flash_WriteCommand(WREN);
    uint8_t buffer[4];
    buffer[0]=SE;
    buffer[1]=address>>16;
    buffer[2]=address>>8;
    buffer[3]=address;
    GPIO_pin_write(mem.ssPin, GPIO_LOW);
    bool res = SpiDriver_transfer(mem.spi, buffer, NULL, 4);
    GPIO_pin_write(mem.ssPin, GPIO_HIGH);
    vTaskDelay(50);
    return res;
}

static unsigned char __attribute__ ((coherent, aligned(16))) buffer[260];
bool sst26_page_program(void *data, int length, int address)
{
    buffer[0] = 0x02;
    buffer[1] = address >> 16;
    buffer[2] = address >> 8;
    buffer[3] = address;
    memcpy(buffer+4, data, length);
    _Flash_WriteCommand(WREN);
    GPIO_pin_write(mem.ssPin, GPIO_LOW);
//    bool res = SpiDriver_transfer(mem.spi, op, NULL, length+4);
    bool res = SpiDriver_write_dma(mem.spi, buffer, length + 4);
    GPIO_pin_write(mem.ssPin, GPIO_HIGH);
    vTaskDelay(2);
    return res;
}

void sst26_initialize(uint32_t spiDriverIndex, GPIO_PinMap ssPin)
{
    mem.spi = SpiDriver_open(spiDriverIndex);
    mem.ssPin = ssPin;
    SpiDriverSetup setup = {
            .csPin = GPIO_PIN_INVALID,
            .sample = SPI_SAMPLE_END,
            .spiMode = SPI_MODE_3,
            .baudRate = 40000000
    };
    SpiDriver_setup(mem.spi, &setup);
    mem.memID.mID = Microchip;
}

MEM_TYPE sst26_get_type(){
    return mem.memID.mID;
}

FlashMemID* sst26_read_id()
{
    uint8_t jedec[] = {JEDEC,0,0,0};
    uint8_t rxBuffer[4];
    GPIO_pin_write(mem.ssPin, GPIO_LOW);
    SpiDriver_transfer(mem.spi,jedec,rxBuffer,4);
    GPIO_pin_write(mem.ssPin, GPIO_HIGH);
    memcpy(&mem.memID,rxBuffer+1,3);
    return &mem.memID;
}
bool sst26_write(void* data, int length, unsigned int address)
{
//    if(!_Flash_Unlock())
//        return false;
    uint8_t rep = length/0x1000 + ((length%0x1000) != 0);
    int i;
    for(i = 0;i<rep;i++)
    {
        if(!_Flash_SectorErase((address & 0xFFFFF000) + i*0x1000))
            return false;
    }

    uint8_t repeat = length / MAX_WRITE_BUFFER;
    uint8_t repeat_over = length % MAX_WRITE_BUFFER;

    for ( i = 0; i < repeat; i++ )
    {
        if(!_Flash_PageProgram(data, MAX_WRITE_BUFFER, address))
            return false;
        address+=MAX_WRITE_BUFFER;
        data=(uint8_t*)data+MAX_WRITE_BUFFER;
    }
    if ( repeat_over )
    {
        if(!_Flash_PageProgram(data, repeat_over, address))
            return false;
    }

//    if(!_Flash_Lock())
//        return false;

    return true;

}
bool sst26_read(void* data, int length, unsigned int address)
{
    uint8_t op[4];
    op[0] = 0x03;
    op[1] = address >> 16;
    op[2] = address >> 8;
    op[3] = address;
    GPIO_pin_write(mem.ssPin, GPIO_LOW);
    bool res = SpiDriver_write_read(mem.spi, op, 4, data, length);
//    bool res = SpiDriver_transfer(mem.spi, op, NULL, 4);
//    res = SpiDriver_transfer(mem.spi, NULL, data,length);
    GPIO_pin_write(mem.ssPin, GPIO_HIGH);
    return res;
}