/**
* @file spi.c
* @author Bruno Leppe (bleppe@solintece.com)
* @brief
* @version 0.1
* @date 2022-09-28
*
* @copyright Copyright (c) 2022
*
*/

/**********************************************************************
* Includes
**********************************************************************/
#include "spi.h"
#include "pic32mz_registers.h"
#include <xc.h>

/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/

/**********************************************************************
* Module Preprocessor Macros
**********************************************************************/

/**********************************************************************
* Module Typedefs
**********************************************************************/

/*********************************************************************
* Module Variable Definitions
**********************************************************************/
SPI_Descriptor spiDescriptors[] = {
        (SPI_Descriptor)&SPI1CON, (SPI_Descriptor)&SPI2CON, (SPI_Descriptor)&SPI3CON,
        (SPI_Descriptor)&SPI4CON, (SPI_Descriptor)&SPI5CON, (SPI_Descriptor)&SPI6CON
};
/**********************************************************************
* Function Prototypes
**********************************************************************/
static uint32_t _SPI_Baudrate_Get(uint32_t baudrate);
/**********************************************************************
* Function Definitions
**********************************************************************/

int SPI_Init(SPI_Handler handler, SPI_CHANNEL channel, SPI_Setup *setup) {
    if (handler == NULL)
        return -1;
    if (setup == NULL)
        return -1;
    handler->setup = *setup;
    handler->channel = channel;

    /*Apagar SPI y resetear registro*/
    spiDescriptors[channel]->spicon1.reg = 0;

    /*Vaciar el buffer de recepción*/
    uint32_t data = spiDescriptors[channel]->spibuf.reg;
    data = data;

    /*Establecer el generador de baudios*/
    uint32_t brg = _SPI_Baudrate_Get(handler->setup.baudrate);
    if (brg > 0x1FF) {
        /*ERROR*/
        handler->error = SPI_ERROR_BAUDRATE_TOO_LOW;
        return -1;
    }
    spiDescriptors[channel]->spibrg.reg = brg;

    /*Limpiar la bandera de overflow*/
    spiDescriptors[channel]->spistat.clr = _SPI1STAT_SPIROV_MASK;

    /*Configurar registros de control*/
    if (handler->setup.mastermode == SPI_MASTER)
        spiDescriptors[channel]->spicon1.set = _SPI1CON_MSTEN_MASK;
    if (handler->setup.sample == SPI_SAMPLE_END)
        spiDescriptors[channel]->spicon1.set = _SPI1CON_SMP_MASK;

    /*SPI MODE Configuration*/
    uint32_t cke = 1, ckp = 0;/*SPI_MODE_0*/
    switch (handler->setup.mode) {
        case SPI_MODE_0:
            cke = 1;
            ckp = 0;
            break;
        case SPI_MODE_1:
            cke = ckp = 0;
            break;
        case SPI_MODE_2:
            cke = ckp = 1;
            break;
        case SPI_MODE_3:
            cke = 0;
            ckp = 1;
            break;
    }
    spiDescriptors[channel]->spicon1.clr = _SPI1CON_CKP_MASK | _SPI1CON_CKE_MASK;
    spiDescriptors[channel]->spicon1.set = (cke << _SPI1CON_CKE_POSITION) |
                                           (ckp << _SPI1CON_CKP_POSITION);


    /*Encender SPI*/
    spiDescriptors[channel]->spicon1.set = _SPI1CON_ON_MASK;


    return 0;
}

int SPI_Transfer(SPI_Handler handler, void *txBuffer, void *rxBuffer, size_t size)
{
    size_t txCount = 0;
    size_t rxCount = 0;
    uint8_t receivedData;

//    spiDescriptors[handler->setup.channel];

    /*Error handling*/
    if(handler == NULL)
        return -1;
    if(txBuffer == NULL && rxBuffer == NULL){
        /*ERROR NULL buffers*/
        handler->error = SPI_ERROR_NULL_BUFFERS;
        if(handler->errorCallback != NULL){
            handler->errorCallback(handler);
        }
        return -1;
    }
    if(size == 0){
        /*ERROR size is 0*/
        return 0;
    }

    /*Transferencia*/

    /*Limpiar bandera de overflow*/
    spiDescriptors[handler->channel]->spistat.clr = _SPI1STAT_SPIROV_MASK;

    /*Vaciar FIFO de recepción*/
    while ((bool)(spiDescriptors[handler->channel]->spistat.reg & _SPI1STAT_SPIRBE_MASK) == false)
        receivedData = spiDescriptors[handler->channel]->spibuf.reg;


    /*Esperar que el FIFO de transmisión esté vacío*/
    while((bool)(spiDescriptors[handler->channel]->spistat.reg & _SPI1STAT_SPITBE_MASK) == false);

    while(size--){

        /*Escritura de bytes*/
        if(txBuffer != NULL){
            spiDescriptors[handler->channel]->spibuf.reg = ((uint8_t*)txBuffer)[txCount++];
        }
        else{
            spiDescriptors[handler->channel]->spibuf.reg = handler->dummyByte;/*DUMMY*/
        }

        /*Recepción*/

        /*Esperar a que el buffer de RX se llene con bytes*/
        while((spiDescriptors[handler->channel]->spistat.reg & _SPI1STAT_SPIRBE_MASK) == _SPI1STAT_SPIRBE_MASK);

        /*Leer el FIFO RX*/
        receivedData = spiDescriptors[handler->channel]->spibuf.reg;
        if(rxBuffer != NULL){
            ((uint8_t*)rxBuffer)[rxCount++] = receivedData;
        }

        /*Byte transmit delay, useful for QTouch comms*/
//        if(handler->usDelay != 0){
//            _delay_us(handler->usDelay);
//        }

    }

    /*Esperar que el registro de desplazamiento esté vacío*/
    while ((bool)((spiDescriptors[handler->channel]->spistat.reg & _SPI1STAT_SRMT_MASK) == false));
    return txCount;
}

uint8_t SPI_TransferByte(SPI_Handler handler, uint8_t data)
{
    uint8_t receivedData;

    if(handler == NULL)
        return 0;

    SPI_Descriptor instance = spiDescriptors[handler->channel];

    /*Limpiar bandera de overflow*/
    instance->spistat.clr = _SPI1STAT_SPIROV_MASK;

    /*Vaciar FIFO de recepción*/
    while ((bool)(instance->spistat.reg & _SPI1STAT_SPIRBE_MASK) == false)
        receivedData = instance->spibuf.reg;

    /*Esperar que el FIFO de transmisión esté vacío*/
    while((bool)(instance->spistat.reg & _SPI1STAT_SPITBE_MASK) == false);

    /*Enviar el byte*/
    instance->spibuf.reg = data;

    /*Esperar a que el buffer de RX se llene con bytes*/
    while((instance->spistat.reg & _SPI1STAT_SPIRBE_MASK) == _SPI1STAT_SPIRBE_MASK);

    /*Leer el FIFO RX*/
    receivedData = instance->spibuf.reg;

    return receivedData;
}

static uint32_t _SPI_Baudrate_Get(uint32_t baudrate){
    uint32_t clock;
    uint32_t brg;
    uint32_t error;

    clock = HAL_SPI_PERIPHERAL_CLOCK;
    brg = ((clock/baudrate)/2)-1;

    error = (clock / (2 * (brg + 1)));
    if(error > baudrate)
        brg++;

    return brg;

}