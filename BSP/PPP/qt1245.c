//
// Created by bleppe on 29/03/23.
//

#include "qt1245.h"
#include "FreeRTOS.h"
#include "task.h"
#include "hal.h"
#include "lcd.h"
#include "linux_keys.h"
#include "Drivers/SPI/spi_driver.h"
#include "debug.h"

typedef struct{
    DriverHandle handle;
    GPIO_PinMap cs;
    GPIO_PinMap rst;
    GPIO_PinMap change;
    GPIO_PinMap drdy;
}QTouch;

union QTouchKeyUnion{
    struct{
        uint8_t key_0;
        uint8_t key_1;
        uint8_t key_2;
    };
    int key;
};

static QTouch qt;

uint16_t sixteen_bit_crc(uint16_t crc, uint8_t data)
{
    uint8_t index;// shift counter
    crc ^= (uint16_t)(data) << 8;
    index = 8;
    do{
        if(crc & 0x8000)
            crc= (crc << 1) ^ 0x1021;
        else
            crc= crc << 1;
    }while(--index);
    return crc;
}

static void QTouch_transfer(uint8_t *txBuffer, uint8_t *rxBuffer, size_t size)
{
    GPIO_pin_write(qt.cs, GPIO_LOW);
    uint8_t receivedData;
    while(size--){
        SpiDriver_byte_transfer(qt.handle, *txBuffer, &receivedData);
        HAL_delay_us(40);
        while(!GPIO_pin_read(qt.drdy));
        if(rxBuffer != NULL)
            *rxBuffer++ = receivedData;
        txBuffer++;
    }
    GPIO_pin_write(qt.cs, GPIO_HIGH);
}

int     QTouch_initialize(int spiDriverIndex, GPIO_PinMap cs, GPIO_PinMap rst, GPIO_PinMap change, GPIO_PinMap drdy)
{
    qt.cs = cs;
    qt.rst = rst;
    qt.change = change;
    qt.drdy = drdy;

    qt.handle = SpiDriver_open(spiDriverIndex);

    SpiDriverSetup setup = {
            .csPin = GPIO_PIN_INVALID,
            .spiMode = SPI_MODE_3,
            .baudRate = 1000000,
            .sample = SPI_SAMPLE_END
    };
    int r = SpiDriver_setup(qt.handle, &setup);
    GPIO_pin_write(qt.rst, GPIO_LOW);
    vTaskDelay(10);
    GPIO_pin_write(qt.rst, GPIO_HIGH);
    vTaskDelay(300);

//    QTouch_calibrate_all();
//    vTaskDelay(1000);
    return 0;
}

int     QTouch_calibrate_all()
{
    uint8_t data[] = {140, 1, 0xFF};
    QTouch_transfer(data, NULL, sizeof(data));
    return 0;
}
bool     QTouch_get_key(int *outKey)
{
    uint8_t  data[] = {6, 128+3, 0, 0 ,0, 0, 0};
    uint8_t rxBuffer[7];
    QTouch_transfer(data, rxBuffer, sizeof(data));

    rxBuffer[0] = 6;
    rxBuffer[1] = 3;

    uint16_t crc = 0;
    for(int i=0;i<5;i++){
        crc = sixteen_bit_crc(crc,rxBuffer[i]);
    }

    uint16_t rxCRC = ((uint16_t)rxBuffer[6] << 8) | rxBuffer[5];
    if(rxCRC != crc)
        return false;

    union QTouchKeyUnion key;
    key.key = 0;
    key.key_0 = rxBuffer[2];
    key.key_1 = rxBuffer[3];
    key.key_2 = rxBuffer[4];

    *outKey = key.key;

    return true;
}