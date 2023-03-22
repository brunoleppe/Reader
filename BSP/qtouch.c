//
// Created by bleppe on 20/03/23.
//

#include "qtouch.h"
#include "FreeRTOS.h"
#include "task.h"
#include "hal.h"
#include "lcd.h"
#include "linux_keys.h"

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

static void QTouch_transfer(uint8_t *txBuffer, uint8_t *rxBuffer, size_t size)
{
    GPIO_pin_write(qt.cs, GPIO_LOW);
    while(size--){
        *rxBuffer = SPI_byte_transfer(qt.spi, *txBuffer);
        HAL_delay_us(160);
        rxBuffer++;
        txBuffer++;
    }
    GPIO_pin_write(qt.cs, GPIO_HIGH);
}


int     QTouch_initialize(SPI_Channel channel, GPIO_PinMap cs, GPIO_PinMap rst, GPIO_PinMap change, GPIO_PinMap drdy)
{
    qt.spi = channel;
    qt.change = change;
    qt.cs = cs;
    qt.drdy = drdy;
    qt.rst = rst;

    GPIO_pin_write(qt.rst, GPIO_LOW);
    vTaskDelay(10);
    GPIO_pin_write(qt.rst, GPIO_HIGH);
    vTaskDelay(200);
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

    return key.key;
}
int     QTouch_calibrate()
{
    GPIO_pin_write(qt.cs, GPIO_LOW);
    SPI_byte_transfer(qt.spi,QT_CALIBRATE);
    GPIO_pin_write(qt.cs, GPIO_HIGH);
    vTaskDelay(150);
    return 0;
}