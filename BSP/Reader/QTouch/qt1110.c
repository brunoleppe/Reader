//
// Created by bleppe on 20/03/23.
//

#include "qt1110.h"
#include "FreeRTOS.h"
#include "task.h"
#include "hal.h"
#include "lcd.h"
#include "linux_keys.h"
#include "Drivers/SPI/spi_driver.h"
#include "debug_bsp.h"

enum QT_CONTROL_COMMANDS{
    QT_CALIBRATE = 0x03,///<Comando para realizar auto calibración
    QT_READ_KEY = 0xC1,///<Comando para obtener estado de las teclas
    QT_WRITE_SETUPS = 0x01,///<Comando para preparar al chip para recibir 42 bytes de configuraciones
    QT_READ_SETUPS = 0xC8,///<Comando para leer 42 bytes de configuraciones actuales
    QT_RESET = 0x04,///<Comando para resetear el chip
};

enum QT_KEY{
    QT_KEY_NONE     = 0,        ///< ninguna tecla
    QT_KEY_OPTION   = 0x100,    ///< tecla 1
    QT_KEY_RETURN   = 0x200,    ///< tecla 2
    QT_KEY_ENTER    = 0x400,    ///< tecla 3
    QT_KEY_DOWN     = 0x800,    ///< tecla 4
    QT_KEY_UP       = 0x1000,   ///< Tecla 5
    QT_KEY_READER   = 0x2000,   ///< tecla 6
    QT_KEY_INVALID  = 0xFFFF    ///< Tecla inválida
};

typedef struct{
    DriverHandle handle;
    SPI_Channel spi;
    GPIO_PinMap cs;
    GPIO_PinMap rst;
    GPIO_PinMap change;
    GPIO_PinMap drdy;
}QTouch;

union QTouchKeyUnion{
    struct{
        uint8_t key_0;
        uint8_t key_1;
    };
    int key;
};
static QTouch qt;
static uint8_t setup_data[43] = {
    0x01,
    0xB2, 0x68, 0x38, 0x12, 0x06, 0x06, 0x12, 0x07, 0xFF, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x7F, 0x00, 0x2A,
    0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A,
    0x00, 0x7A, 0x7A, 0x7A, 0x7A, 0x7A, 0x7A, 0x7A, 0x7A, 0x7A,
    0x7A, 0x7A,
};

static int QTouch_key_map(enum QT_KEY k)
{
    switch(k){
        case QT_KEY_NONE:       return 0;
        case QT_KEY_OPTION:     return 1;
        case QT_KEY_RETURN:     return 2;
        case QT_KEY_ENTER:      return 3;
        case QT_KEY_DOWN:       return 4;
        case QT_KEY_UP:         return 5;
        case QT_KEY_READER:     return 6;
        case QT_KEY_INVALID:    return 7;
    }
}

static void QTouch_transfer(uint8_t *txBuffer, uint8_t *rxBuffer, size_t size)
{
    GPIO_pin_write(qt.cs, GPIO_LOW);
    uint8_t receivedData;
    while(size--){
//        receivedData = SPI_byte_transfer(qt.spi, *txBuffer);
        SpiDriver_byte_transfer(qt.handle, *txBuffer, &receivedData);
        HAL_delay_us(160);
        if(rxBuffer != NULL)
            *rxBuffer++ = receivedData;
        txBuffer++;
    }
    GPIO_pin_write(qt.cs, GPIO_HIGH);
}


int     QTouch_initialize(SPI_Channel channel, GPIO_PinMap cs, GPIO_PinMap rst, GPIO_PinMap change, GPIO_PinMap drdy)
{
    qt.spi = channel;
//    qt.spi = SpiDriver_open(0);
    qt.change = change;
    qt.cs = cs;
    qt.drdy = drdy;
    qt.rst = rst;

    DEBUG_PRINT("----QTOUCH----\n\r");

    qt.handle = SpiDriver_open(0);
    DEBUG_PRINT("handle = %x\n\r", qt.handle);

    SpiDriverSetup setup = {
            .csPin = GPIO_PIN_INVALID,
            .spiMode = SPI_MODE_3,
            .baudRate = 1000000,
            .sample = SPI_SAMPLE_END
    };

    int r = SpiDriver_setup(qt.handle, &setup);
    DEBUG_PRINT("setup = %x\n\r", r);
    DEBUG_PRINT("----QTOUCH----\n\r");
    GPIO_pin_write(qt.rst, GPIO_LOW);
    vTaskDelay(10);
    GPIO_pin_write(qt.rst, GPIO_HIGH);
    vTaskDelay(200);

    QTouch_transfer(setup_data,NULL,sizeof(setup_data));
    vTaskDelay(1);

    return 0;
}
int     QTouch_get_key()
{
    uint8_t read_key[] = {0xC1, 0x00, 0x00};
    uint8_t rxBuffer[3];
    QTouch_transfer(read_key, rxBuffer, 3);

    union QTouchKeyUnion key;
    key.key = 0;
    key.key_0 = rxBuffer[1];
    key.key_1 = rxBuffer[2];

    return QTouch_key_map(key.key);
}
int     QTouch_calibrate_all()
{
    GPIO_pin_write(qt.cs, GPIO_LOW);
    SPI_byte_transfer(qt.spi,QT_CALIBRATE);
    GPIO_pin_write(qt.cs, GPIO_HIGH);
    vTaskDelay(150);
    return 0;
}