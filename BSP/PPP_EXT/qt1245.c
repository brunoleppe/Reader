//
// Created by bleppe on 29/03/23.
//
/***********************************************************************************************************************
* Includes
***********************************************************************************************************************/
#include "qt1245.h"
#include "FreeRTOS.h"
#include "task.h"
#include "hal.h"
#include "lcd.h"
#include "Drivers/SPI/spi_driver.h"
#include "debug_bsp.h"
/***********************************************************************************************************************
* Module Preprocessor Constants
***********************************************************************************************************************/

/***********************************************************************************************************************
* Module Preprocessor Macros
***********************************************************************************************************************/

/***********************************************************************************************************************
* Module Typedefs
***********************************************************************************************************************/
typedef struct{
    uint8_t*        txBuffer;
    uint8_t*        rxBuffer;
    size_t          size;
}QTouch_TransferObject;

typedef struct{
    DriverHandle    handle;
    SpiClientObject *spiObj;
    GPIO_PinMap     cs;
    GPIO_PinMap     rst;
    GPIO_PinMap     change;
    GPIO_PinMap     drdy;
    QTouch_TransferObject transfer;
}QTouch;

union QTouchKeyUnion{
    struct{
        uint8_t key_0;
        uint8_t key_1;
        uint8_t key_2;
    };
    int key;
};
/**********************************************************************************************************************
* Module Variable Definitions
***********************************************************************************************************************/
static QTouch qt;
/***********************************************************************************************************************
* Function Prototypes
***********************************************************************************************************************/
static void QTouch_write(uint8_t *txBuffer, uint8_t *rxBuffer, size_t size);
static void QTouch_transfer();
static uint16_t sixteen_bit_crc(uint16_t crc, uint8_t data);
/***********************************************************************************************************************
* Function Definitions
***********************************************************************************************************************/
int     QTouch_initialize(int spiDriverIndex, GPIO_PinMap cs, GPIO_PinMap rst, GPIO_PinMap change, GPIO_PinMap drdy)
{
    qt.cs = cs;
    qt.rst = rst;
    qt.change = change;
    qt.drdy = drdy;

    qt.handle = SpiDriver_open(spiDriverIndex);
    qt.spiObj = SpiDriver_get_object(qt.handle);

    SpiDriverSetup setup = {
            .csPin = cs,
            .spiMode = SPI_MODE_3,
            .baudRate = 1000000,
            .sample = SPI_SAMPLE_END
    };
    int r = SpiDriver_setup(qt.handle, &setup);
    (void)r;
    GPIO_pin_write(qt.rst, GPIO_LOW);
    vTaskDelay(10);
    GPIO_pin_write(qt.rst, GPIO_HIGH);
    vTaskDelay(300);
//
//    uint8_t buff[] = {140, 1, 0xFE};
//    QTouch_transfer(buff,NULL,3);
//    uint8_t buffer[] = {182, 7, 0, 0 ,0 ,0 ,0 ,0, 0};
//    QTouch_transfer(buffer, NULL, 9);


    QTouch_calibrate_all();
    vTaskDelay(1000);
    return 0;
}

int     QTouch_calibrate_all()
{
    uint8_t data[] = {140, 1, 0xFF};
    QTouch_write(data, NULL, sizeof(data));
    return 0;
}
bool     QTouch_get_key(int *outKey)
{
    uint8_t  data[] = {6, 128+3, 0, 0 ,0, 0, 0};
    uint8_t rxBuffer[sizeof(data)];
    QTouch_write(data, rxBuffer, sizeof(data));


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

void    QTouch_calibrate_key(int key)
{
    uint8_t data[] = {140, 1, key};
    QTouch_write(data, NULL, sizeof(data));
}
void    QTouch_low_level_cal( void )
{
    uint8_t data[] = {140, 1, 0xFD};
    QTouch_write(data, NULL, sizeof(data));
}
uint8_t QTouch_report_status( void )
{
    uint8_t data[] = {5, 1+128, 0};
    uint8_t rx[3];
    QTouch_write(data, rx, 3);
    return rx[2];
}
uint16_t QTouch_key_data(int key)
{
    int address = 14 + 4*key;
    uint8_t data[] = {address, 2+128, 0, 0};
    int rxBuffer;
    QTouch_write(data, (uint8_t*)&rxBuffer, 4);
    return (uint16_t)(rxBuffer >> 16);
}

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

void QTouch_transfer()
{
    uint8_t receivedData;
    while(qt.transfer.size--){
        receivedData = SPI_byte_transfer(qt.spiObj->driverObject->spiChannel, *qt.transfer.txBuffer);
        HAL_delay_us(40);
        while(!GPIO_pin_read(qt.drdy));
        if(qt.transfer.rxBuffer != NULL)
            *qt.transfer.rxBuffer++ = receivedData;
        qt.transfer.txBuffer++;
    }
}

static void QTouch_write(uint8_t *txBuffer, uint8_t *rxBuffer, size_t size)
{
    qt.transfer.txBuffer = txBuffer;
    qt.transfer.rxBuffer = rxBuffer;
    qt.transfer.size = size;
    SpiDriver_transfer_custom(qt.handle, QTouch_transfer);
}