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
#include <system.h>
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
//bool SPI1_WriteRead (void* pTransmitData, size_t txSize, void* pReceiveData, size_t rxSize)
//{
//    bool isRequestAccepted = false;
//    uint32_t dummyData = 0U;
//
//    /* Verify the request */
//    if((((txSize > 0) && (pTransmitData != NULL)) || ((rxSize > 0) && (pReceiveData != NULL))) && (spi1Obj.transferIsBusy == false))
//    {
//        isRequestAccepted = true;
//        spi1Obj.txBuffer = pTransmitData;
//        spi1Obj.rxBuffer = pReceiveData;
//        spi1Obj.rxCount = 0;
//        spi1Obj.txCount = 0;
//        spi1Obj.dummySize = 0;
//
//        if (pTransmitData != NULL)
//        {
//            spi1Obj.txSize = txSize;
//        }
//        else
//        {
//            spi1Obj.txSize = 0;
//        }
//
//        if (pReceiveData != NULL)
//        {
//            spi1Obj.rxSize = rxSize;
//        }
//        else
//        {
//            spi1Obj.rxSize = 0;
//        }
//
//        spi1Obj.transferIsBusy = true;
//
//        if (spi1Obj.rxSize > spi1Obj.txSize)
//        {
//            spi1Obj.dummySize = spi1Obj.rxSize - spi1Obj.txSize;
//        }
//
//        /* Clear the receive overflow error if any */
//        SPI1STATCLR = _SPI1STAT_SPIROV_MASK;
//
//        /* Make sure there is no data pending in the RX FIFO */
//        /* Depending on 8/16/32 bit mode, there may be 16/8/4 bytes in the FIFO */
//        while ((bool)(SPI1STAT & _SPI1STAT_SPIRBE_MASK) == false)
//        {
//            dummyData = SPI1BUF;
//            (void)dummyData;
//        }
//
//        /* Configure SPI to generate receive interrupt when receive buffer is empty (SRXISEL = '01') */
//        SPI1CONCLR = _SPI1CON_SRXISEL_MASK;
//        SPI1CONSET = 0x00000001;
//
//        /* Configure SPI to generate transmit interrupt when the transmit shift register is empty (STXISEL = '00')*/
//        SPI1CONCLR = _SPI1CON_STXISEL_MASK;
//
//        /* Disable the receive interrupt */
//        IEC3CLR = 0x4000;
//
//        /* Disable the transmit interrupt */
//        IEC3CLR = 0x8000;
//
//        /* Clear the receive interrupt flag */
//        IFS3CLR = 0x4000;
//
//        /* Clear the transmit interrupt flag */
//        IFS3CLR = 0x8000;
//
//        /* Start the first write here itself, rest will happen in ISR context */
//        if((_SPI1CON_MODE32_MASK) == (SPI1CON & (_SPI1CON_MODE32_MASK)))
//        {
//            spi1Obj.txSize >>= 2;
//            spi1Obj.dummySize >>= 2;
//            spi1Obj.rxSize >>= 2;
//
//            if(spi1Obj.txCount < spi1Obj.txSize)
//            {
//                SPI1BUF = *((uint32_t*)spi1Obj.txBuffer);
//                spi1Obj.txCount++;
//            }
//            else if (spi1Obj.dummySize > 0)
//            {
//                SPI1BUF = (uint32_t)(0xff);
//                spi1Obj.dummySize--;
//            }
//        }
//        else if((_SPI1CON_MODE16_MASK) == (SPI1CON & (_SPI1CON_MODE16_MASK)))
//        {
//            spi1Obj.txSize >>= 1;
//            spi1Obj.dummySize >>= 1;
//            spi1Obj.rxSize >>= 1;
//
//            if (spi1Obj.txCount < spi1Obj.txSize)
//            {
//                SPI1BUF = *((uint16_t*)spi1Obj.txBuffer);
//                spi1Obj.txCount++;
//            }
//            else if (spi1Obj.dummySize > 0)
//            {
//                SPI1BUF = (uint16_t)(0xff);
//                spi1Obj.dummySize--;
//            }
//        }
//        else
//        {
//            if (spi1Obj.txCount < spi1Obj.txSize)
//            {
//                SPI1BUF = *((uint8_t*)spi1Obj.txBuffer);
//                spi1Obj.txCount++;
//            }
//            else if (spi1Obj.dummySize > 0)
//            {
//                SPI1BUF = (uint8_t)(0xff);
//                spi1Obj.dummySize--;
//            }
//        }
//
//        if (rxSize > 0)
//        {
//            /* Enable receive interrupt to complete the transfer in ISR context.
//             * Keep the transmit interrupt disabled. Transmit interrupt will be
//             * enabled later if txCount < txSize, when rxCount = rxSize.
//             */
//            IEC3SET = 0x4000;
//        }
//        else
//        {
//            if (spi1Obj.txCount != spi1Obj.txSize)
//            {
//                /* Configure SPI to generate transmit buffer empty interrupt only if more than
//                 * data is pending (STXISEL = '01')  */
//                SPI1CONSET = 0x00000004;
//            }
//            /* Enable transmit interrupt to complete the transfer in ISR context */
//            IEC3SET = 0x8000;
//        }
//    }
//
//    return isRequestAccepted;
//}
//
//bool SPI1_IsBusy (void)
//{
//    return ( (spi1Obj.transferIsBusy) || ((SPI1STAT & _SPI1STAT_SRMT_MASK) == 0));
//}
//
//void SPI1_CallbackRegister (SPI_CALLBACK callback, uintptr_t context)
//{
//    spi1Obj.callback = callback;
//
//    spi1Obj.context = context;
//}
//
//void SPI1_RX_InterruptHandler (void)
//{
//    uint32_t receivedData = 0;
//
//    /* Check if the receive buffer is empty or not */
//    if ((bool)(SPI1STAT & _SPI1STAT_SPIRBE_MASK) == false)
//    {
//        /* Receive buffer is not empty. Read the received data. */
//        receivedData = SPI1BUF;
//
//        if (spi1Obj.rxCount < spi1Obj.rxSize)
//        {
//            /* Copy the received data to the user buffer */
//            if((_SPI1CON_MODE32_MASK) == (SPI1CON & (_SPI1CON_MODE32_MASK)))
//            {
//                ((uint32_t*)spi1Obj.rxBuffer)[spi1Obj.rxCount++] = receivedData;
//            }
//            else if((_SPI1CON_MODE16_MASK) == (SPI1CON & (_SPI1CON_MODE16_MASK)))
//            {
//                ((uint16_t*)spi1Obj.rxBuffer)[spi1Obj.rxCount++] = receivedData;
//            }
//            else
//            {
//                ((uint8_t*)spi1Obj.rxBuffer)[spi1Obj.rxCount++] = receivedData;
//            }
//            if ((spi1Obj.rxCount == spi1Obj.rxSize) && (spi1Obj.txCount < spi1Obj.txSize))
//            {
//                /* Reception of all bytes is complete. However, there are few more
//                 * bytes to be transmitted as txCount != txSize. Finish the
//                 * transmission of the remaining bytes from the transmit interrupt. */
//
//                /* Disable the receive interrupt */
//                IEC3CLR = 0x4000;
//
//                /* Generate TX interrupt when buffer is completely empty (STXISEL = '00') */
//                SPI1CONCLR = _SPI1CON_STXISEL_MASK;
//                SPI1CONSET = 0x00000004;
//
//                /* Enable the transmit interrupt. Callback will be given from the
//                 * transmit interrupt, when all bytes are shifted out. */
//                IEC3SET = 0x8000;
//            }
//        }
//        if (spi1Obj.rxCount < spi1Obj.rxSize)
//        {
//            /* More bytes pending to be received .. */
//            if((_SPI1CON_MODE32_MASK) == (SPI1CON & (_SPI1CON_MODE32_MASK)))
//            {
//                if (spi1Obj.txCount < spi1Obj.txSize)
//                {
//                    SPI1BUF = ((uint32_t*)spi1Obj.txBuffer)[spi1Obj.txCount++];
//                }
//                else if (spi1Obj.dummySize > 0)
//                {
//                    SPI1BUF = (uint32_t)(0xff);
//                    spi1Obj.dummySize--;
//                }
//            }
//            else if((_SPI1CON_MODE16_MASK) == (SPI1CON & (_SPI1CON_MODE16_MASK)))
//            {
//                if (spi1Obj.txCount < spi1Obj.txSize)
//                {
//                    SPI1BUF = ((uint16_t*)spi1Obj.txBuffer)[spi1Obj.txCount++];
//                }
//                else if (spi1Obj.dummySize > 0)
//                {
//                    SPI1BUF = (uint16_t)(0xff);
//                    spi1Obj.dummySize--;
//                }
//            }
//            else
//            {
//                if (spi1Obj.txCount < spi1Obj.txSize)
//                {
//                    SPI1BUF = ((uint8_t*)spi1Obj.txBuffer)[spi1Obj.txCount++];
//                }
//                else if (spi1Obj.dummySize > 0)
//                {
//                    SPI1BUF = (uint8_t)(0xff);
//                    spi1Obj.dummySize--;
//                }
//            }
//        }
//        else
//        {
//            if((spi1Obj.rxCount == spi1Obj.rxSize) && (spi1Obj.txCount == spi1Obj.txSize))
//            {
//                /* Clear receiver overflow error if any */
//                SPI1STATCLR = _SPI1STAT_SPIROV_MASK;
//
//                /* Disable receive interrupt */
//                IEC3CLR = 0x4000;
//
//                /* Transfer complete. Give a callback */
//                spi1Obj.transferIsBusy = false;
//
//                if(spi1Obj.callback != NULL)
//                {
//                    spi1Obj.callback(spi1Obj.context);
//                }
//            }
//        }
//    }
//
//    /* Clear SPI1 RX Interrupt flag */
//    /* This flag should cleared only after reading buffer */
//    IFS3CLR = 0x4000;
//}
//
//void SPI1_TX_InterruptHandler (void)
//{
//    /* If there are more words to be transmitted, then transmit them here and keep track of the count */
//    if((SPI1STAT & _SPI1STAT_SPITBE_MASK) == _SPI1STAT_SPITBE_MASK)
//    {
//        if (spi1Obj.txCount < spi1Obj.txSize)
//        {
//            if((_SPI1CON_MODE32_MASK) == (SPI1CON & (_SPI1CON_MODE32_MASK)))
//            {
//                SPI1BUF = ((uint32_t*)spi1Obj.txBuffer)[spi1Obj.txCount++];
//            }
//            else if((_SPI1CON_MODE16_MASK) == (SPI1CON & (_SPI1CON_MODE16_MASK)))
//            {
//                SPI1BUF = ((uint16_t*)spi1Obj.txBuffer)[spi1Obj.txCount++];
//            }
//            else
//            {
//                SPI1BUF = ((uint8_t*)spi1Obj.txBuffer)[spi1Obj.txCount++];
//            }
//
//            if (spi1Obj.txCount == spi1Obj.txSize)
//            {
//                /* All bytes are submitted to the SPI module. Now, enable transmit
//                 * interrupt when the shift register is empty (STXISEL = '00')*/
//                SPI1CONCLR = _SPI1CON_STXISEL_MASK;
//            }
//        }
//        else if ((spi1Obj.txCount == spi1Obj.txSize) && (SPI1STAT & _SPI1STAT_SRMT_MASK))
//        {
//            /* This part of code is executed when the shift register is empty. */
//
//            /* Clear receiver overflow error if any */
//            SPI1STATCLR = _SPI1STAT_SPIROV_MASK;
//
//            /* Disable transmit interrupt */
//            IEC3CLR = 0x8000;
//
//            /* Transfer complete. Give a callback */
//            spi1Obj.transferIsBusy = false;
//
//            if(spi1Obj.callback != NULL)
//            {
//                spi1Obj.callback(spi1Obj.context);
//            }
//        }
//    }
//    /* Clear the transmit interrupt flag */
//    IFS3CLR = 0x8000;
//}



static uint32_t SPI_Baudrate_Get_(uint32_t baudrate){
    uint32_t clock;
    uint32_t brg;
    uint32_t error;

    clock = SYS_peripheral_clock_frequency_get(SYS_PERIPHERAL_CLOCK_2);
    brg = ((clock/baudrate)/2)-1;

    error = (clock / (2 * (brg + 1)));
    if(error > baudrate)
        brg++;

    return brg;
}
