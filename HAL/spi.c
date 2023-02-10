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
#include "hal_delay.h"
#include "evic.h"
#include <xc.h>
/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/
#define SPI_BASE                            _SPI1_BASE_ADDRESS
#define SPI_NUMBER_OF_CHANNELS              (6)
#define SPI_IRQ_RX_CHANNEL(base)            ((base) + 1)
#define SPI_IRQ_TX_CHANNEL(base)            ((base) + 1)

/**********************************************************************
* Module Preprocessor Macros
**********************************************************************/
#define SPI_DESCRIPTOR(channel)             ((SPI_Descriptor)(((uint8_t*)(SPI_BASE)) + 0x200*(channel)))
/**********************************************************************
* Module Typedefs
**********************************************************************/

/*********************************************************************
* Module Variable Definitions
**********************************************************************/
static SPI_Object spiObjects[SPI_NUMBER_OF_CHANNELS];
//static const EVIC_CHANNEL spiIRQBase[SPI_NUMBER_OF_CHANNELS]={
//        EVIC_CHANNEL_SPI1_FAULT,
//        EVIC_CHANNEL_SPI2_FAULT,
//        EVIC_CHANNEL_SPI3_FAULT,
//        EVIC_CHANNEL_SPI4_FAULT,
//        EVIC_CHANNEL_SPI5_FAULT,
//        EVIC_CHANNEL_SPI6_FAULT,
//};
/**********************************************************************
* Function Prototypes
**********************************************************************/
static uint32_t SPI_Baudrate_Get_(uint32_t baudrate);
/**********************************************************************
* Function Definitions
**********************************************************************/

int SPI_initialize(uint32_t spiChannel, uint32_t configFlags, uint32_t baudrate)
{

    /*Clear Control register*/
    SPI_DESCRIPTOR(spiChannel)->spicon1.reg = 0;
    /*Clear RX FIFO*/
    uint32_t data = SPI_DESCRIPTOR(spiChannel)->spibuf.reg;
    (void)data;
    /*Configure Baudrate Generator*/
    uint32_t brg = SPI_Baudrate_Get_(baudrate);
//    if (brg > 0x1FF) {
//        /*ERROR*/
//        return -1;
//    }
    SPI_DESCRIPTOR(spiChannel)->spibrg.reg = brg;
    SPI_DESCRIPTOR(spiChannel)->spistat.clr = _SPI1STAT_SPIROV_MASK;
    /*Configure SPI as master*/
    if((configFlags & SPI_MASTER))//master
        SPI_DESCRIPTOR(spiChannel)->spicon1.set = _SPI1CON_MSTEN_MASK;
    /*Configure input sample phase bit*/
    if(configFlags & SPI_SAMPLE_END)
        SPI_DESCRIPTOR(spiChannel)->spicon1.set = _SPI1CON_SMP_MASK;

    /*SPI MODE Configuration*/
    uint32_t cke = 1, ckp = 0;/*SPI_MODE_0*/
    if(configFlags & SPI_MODE_1) {
        cke = ckp = 0;
    }
    else if(configFlags & SPI_MODE_2){
        cke = ckp = 1;
    }
    else if(configFlags & SPI_MODE_3){
        cke = 0;
        ckp = 1;
    }
    SPI_DESCRIPTOR(spiChannel)->spicon1.clr = _SPI1CON_CKP_MASK | _SPI1CON_CKE_MASK;
    SPI_DESCRIPTOR(spiChannel)->spicon1.set = (cke << _SPI1CON_CKE_POSITION) | (ckp << _SPI1CON_CKP_POSITION);
    /*SPI data bits configuration*/
    if(configFlags & SPI_DATA_BITS_16)
        SPI_DESCRIPTOR(spiChannel)->spicon1.set = _SPI1CON_MODE16_MASK;
    else if(configFlags & SPI_DATA_BITS_32)
        SPI_DESCRIPTOR(spiChannel)->spicon1.set = _SPI1CON_MODE32_MASK;
//    /*SPI SDO disable configuration*/
//    if(configFlags & SPI_SDO_DISABLE)
//        SPI_DESCRIPTOR(spiChannel)->spicon1.set = _SPI1CON_DISSDO_MASK;
//    /*SPI SDI disable configuration*/
//    if(configFlags & SPI_SDI_DISABLE)
//        SPI_DESCRIPTOR(spiChannel)->spicon1.set = _SPI1CON_DISSDI_MASK;
    /*SPI SS enable configuration*/
    if(configFlags & SPI_SS_ENABLE)
        SPI_DESCRIPTOR(spiChannel)->spicon1.set = _SPI1CON_SSEN_MASK;
    /*Turn on SPI peripheral*/
    SPI_DESCRIPTOR(spiChannel)->spicon1.set = _SPI1CON_ON_MASK;
    return 0;
}

size_t SPI_transfer(uint32_t spiChannel, const SPI_TransferSetup *setup, void *txBuffer, void *rxBuffer, size_t size)
{
    uint32_t receivedData;

    if(spiObjects[spiChannel].busy)
        return 0;

    if(txBuffer == NULL && rxBuffer == NULL){
        return -1;
    }
    if(size == 0){
        return 0;
    }

    spiObjects[spiChannel].busy = true;
    spiObjects[spiChannel].rxBuffer = rxBuffer;
    spiObjects[spiChannel].txBuffer = txBuffer;
    spiObjects[spiChannel].count = 0;
    /*Transfer*/

    /*Overflow-bit clear*/
    SPI_DESCRIPTOR(spiChannel)->spistat.clr = _SPI1STAT_SPIROV_MASK;

    /*Empty RX FIFO*/
    while ((bool)(SPI_DESCRIPTOR(spiChannel)->spistat.reg & _SPI1STAT_SPIRBE_MASK) == false) {
        receivedData = SPI_DESCRIPTOR(spiChannel)->spibuf.reg;
        (void)receivedData;
    }


    /*Wait for TX FIFO to empty*/
    while((bool)(SPI_DESCRIPTOR(spiChannel)->spistat.reg & _SPI1STAT_SPITBE_MASK) == false);

    if(SPI_DESCRIPTOR(spiChannel)->spicon1.reg & _SPI1CON_MODE32_MASK){
        size >>= 2;
    }
    else if(SPI_DESCRIPTOR(spiChannel)->spicon1.reg & _SPI1CON_MODE16_MASK){
        size >>= 1;
    }

    while(size--){

        /*Write Byte*/
        if(spiObjects[spiChannel].txBuffer != NULL){
            if(SPI_DESCRIPTOR(spiChannel)->spicon1.reg & _SPI1CON_MODE32_MASK){
                SPI_DESCRIPTOR(
                    spiChannel)->spibuf.reg = ((uint32_t*)spiObjects[spiChannel].txBuffer)[spiObjects[spiChannel].count];
            }
            else if(SPI_DESCRIPTOR(spiChannel)->spicon1.reg & _SPI1CON_MODE16_MASK){
                SPI_DESCRIPTOR(
                    spiChannel)->spibuf.reg = ((uint16_t*)spiObjects[spiChannel].txBuffer)[spiObjects[spiChannel].count];
            }
            else {
                SPI_DESCRIPTOR(
                    spiChannel)->spibuf.reg = ((uint8_t*)spiObjects[spiChannel].txBuffer)[spiObjects[spiChannel].count];
            }
        }
        else{
            SPI_DESCRIPTOR(spiChannel)->spibuf.reg = 0xFFFFFFFF;/*DUMMY*/
        }

        /*Recepción*/

        /*Wait for RX FIFO*/
        while((SPI_DESCRIPTOR(spiChannel)->spistat.reg & _SPI1STAT_SPIRBE_MASK) == _SPI1STAT_SPIRBE_MASK);

        /*Read RX FIFO*/
        receivedData = SPI_DESCRIPTOR(spiChannel)->spibuf.reg;
        if(rxBuffer != NULL){
            if(SPI_DESCRIPTOR(spiChannel)->spicon1.reg & _SPI1CON_MODE32_MASK){
                ((uint32_t*)spiObjects[spiChannel].rxBuffer)[spiObjects[spiChannel].count] = receivedData;
            }
            else if(SPI_DESCRIPTOR(spiChannel)->spicon1.reg & _SPI1CON_MODE16_MASK){
                ((uint16_t*)spiObjects[spiChannel].rxBuffer)[spiObjects[spiChannel].count] = receivedData;
            }
            else {
                ((uint8_t*)spiObjects[spiChannel].rxBuffer)[spiObjects[spiChannel].count] = receivedData;
            }
        }
        if(setup->stopCharEnable && (receivedData == setup->stopChar))
            return spiObjects[spiChannel].count;

        if(setup->usDelay != 0)
            HAL_delay_us(setup->usDelay);
        spiObjects[spiChannel].count++;
    }

    /*Wait for TX FIFO to empty*/
    while ((bool)((SPI_DESCRIPTOR(spiChannel)->spistat.reg & _SPI1STAT_SRMT_MASK) == false));
    spiObjects[spiChannel].busy = false;
    return spiObjects[spiChannel].count;
}
//size_t      SPI_transfer_isr    (uint32_t spiChannel, const SPI_TransferSetup *setup, void *txBuffer, void *rxBuffer, size_t size)
//{
//    uint32_t receivedData;
//
//    if(spiObjects[spiChannel].busy)
//        return 0;
//    if(txBuffer == NULL && rxBuffer == NULL)
//        return -1;
//    if(size == 0)
//        return 0;
//
//    spiObjects[spiChannel].busy = true;
//    spiObjects[spiChannel].rxBuffer = rxBuffer;
//    spiObjects[spiChannel].txBuffer = txBuffer;
//    spiObjects[spiChannel].count = 0;
//    spiObjects[spiChannel].rxSize = size;
//    spiObjects[spiChannel].txSize = size;
//
//    /*Overflow-bit clear*/
//    SPI_DESCRIPTOR(spiChannel)->spistat.clr = _SPI1STAT_SPIROV_MASK;
//
//    /*Empty RX FIFO*/
//    while ((bool)(SPI_DESCRIPTOR(spiChannel)->spistat.reg & _SPI1STAT_SPIRBE_MASK) == false) {
//        receivedData = SPI_DESCRIPTOR(spiChannel)->spibuf.reg;
//        (void)receivedData;
//    }
//
//    SPI_DESCRIPTOR(spiChannel)->spicon1.clr = _SPI1CON_SRXISEL_MASK | _SPI1CON_STXISEL_MASK;
//    SPI_DESCRIPTOR(spiChannel)->spicon1.set = 0x00000001;
//    EVIC_channel_clr(SPI_IRQ_RX_CHANNEL(spiIRQBase[spiChannel]));
//    EVIC_channel_clr(SPI_IRQ_TX_CHANNEL(spiIRQBase[spiChannel]));
//    EVIC_channel_pending_clear(SPI_IRQ_RX_CHANNEL(spiIRQBase[spiChannel]));
//    EVIC_channel_pending_clear(SPI_IRQ_TX_CHANNEL(spiIRQBase[spiChannel]));
//
//    spi
//}
uint8_t SPI_byte_transfer(uint32_t spiChannel, uint8_t data)
{
    uint8_t receivedData;

    /*Limpiar bandera de overflow*/
    SPI_DESCRIPTOR(spiChannel)->spistat.clr = _SPI1STAT_SPIROV_MASK;

    /*Vaciar FIFO de recepción*/
    while ((bool)(SPI_DESCRIPTOR(spiChannel)->spistat.reg & _SPI1STAT_SPIRBE_MASK) == false) {
        receivedData = SPI_DESCRIPTOR(spiChannel)->spibuf.reg;
        (void)receivedData;
    }

    /*Esperar que el FIFO de transmisión esté vacío*/
    while((bool)(SPI_DESCRIPTOR(spiChannel)->spistat.reg & _SPI1STAT_SPITBE_MASK) == false);

    /*Enviar el byte*/
    SPI_DESCRIPTOR(spiChannel)->spibuf.reg = data;

    /*Esperar a que el buffer de RX se llene con bytes*/
    while((SPI_DESCRIPTOR(spiChannel)->spistat.reg & _SPI1STAT_SPIRBE_MASK) == _SPI1STAT_SPIRBE_MASK);

    /*Leer el FIFO RX*/
    receivedData = SPI_DESCRIPTOR(spiChannel)->spibuf.reg;

    return receivedData;
}

static uint32_t SPI_Baudrate_Get_(uint32_t baudrate){
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