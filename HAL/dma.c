//
// Created by bleppe on 30/01/23.
//
/**********************************************************************
* Includes
**********************************************************************/
#include "dma.h"
#include "pic32mz_registers.h"
#include <xc.h>
/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/
#define MAX_DMA_CHANNELS    8
/*********************************************************************
* Module Preprocessor Macros
**********************************************************************/

/**********************************************************************
* Module Typedefs
**********************************************************************/

/**********************************************************************
* Module Variable Definitions
**********************************************************************/
static DMA_CHANNEL channel = 0;
static DMA_Descriptor dmaDescriptors[] = {
        (DMA_Descriptor)&DCH0CON, (DMA_Descriptor)&DCH1CON, (DMA_Descriptor)&DCH2CON,
        (DMA_Descriptor)&DCH3CON, (DMA_Descriptor)&DCH4CON, (DMA_Descriptor)&DCH5CON,
        (DMA_Descriptor)&DCH6CON, (DMA_Descriptor)&DCH7CON,
};
/**********************************************************************
* Function Prototypes
**********************************************************************/

/**********************************************************************
* Function Definitions
**********************************************************************/
int DMA_init()
{
    DMACONSET = _DMACON_ON_MASK;
    return 0;
}
DMA_CHANNEL DMA_free_channel_get()
{
    if(channel >= MAX_DMA_CHANNELS)
        return -1;
    return channel++;
    return 0;
}
int DMA_channel_init(DMA_CHANNEL channel)
{
    dmaDescriptors[channel]->dchcon.reg = 0x03;
    dmaDescriptors[channel]->dchecon.reg = 0;
    dmaDescriptors[channel]->dchint.clr = 0x00ff00ff;
    return 0;
}
int DMA_channel_config(DMA_CHANNEL channel, DMA_CHANNEL_Config *config)
{
    dmaDescriptors[channel]->dchssa.reg = config->src_phy_address;
    dmaDescriptors[channel]->dchdsa.reg = config->dst_phy_address;
    dmaDescriptors[channel]->dchssiz.reg = config->src_size;
    dmaDescriptors[channel]->dchdsiz.reg = config->dst_size;
    dmaDescriptors[channel]->dchecon.set = (144) << _DCH0ECON_CHSIRQ_POSITION;
    dmaDescriptors[channel]->dchecon.set = _DCH0ECON_SIRQEN_MASK;
    dmaDescriptors[channel]->dchcsiz.reg = 1;

//    dmaDescriptors[channel]->dchecon.set = ((config->interrupt_vector) << _DCH0ECON_CHSIRQ_POSITION) |
//            _DCH0ECON_SIRQEN_MASK;
    dmaDescriptors[channel]->dchcon.set = _DCH0CON_CHEN_MASK;
    return 0;
}
int DMA_channel_transfer(DMA_CHANNEL channel)
{
//    dmaDescriptors[channel]->dchecon.set = _DCH0ECON_CFORCE_MASK;
    return 0;
}