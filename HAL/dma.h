//
// Created by bleppe on 30/01/23.
//

#ifndef DMA_H
#define DMA_H

/**********************************************************************
* Includes
**********************************************************************/
#include "hal.h"

/**********************************************************************
* Preprocessor Constants
**********************************************************************/

/**********************************************************************
* Typedefs
**********************************************************************/
typedef enum{
    DMA_CHANNEL_0,
    DMA_CHANNEL_1,
    DMA_CHANNEL_2,
    DMA_CHANNEL_3,
    DMA_CHANNEL_4,
    DMA_CHANNEL_5,
    DMA_CHANNEL_6,
    DMA_CHANNEL_7,
}DMA_CHANNEL;

typedef struct{
    uint32_t                src_phy_address;
    size_t                  src_size;
    uint32_t                dst_phy_address;
    size_t                  dst_size;
    size_t                  transfer_size;
    uint8_t                 interrupt_vector;
}DMA_CHANNEL_Config;

/**********************************************************************
* Function Prototypes
**********************************************************************/
int DMA_init();
DMA_CHANNEL DMA_free_channel_get();
int DMA_channel_init(DMA_CHANNEL channel);
int DMA_channel_config(DMA_CHANNEL channel, DMA_CHANNEL_Config *config);
int DMA_channel_transfer(DMA_CHANNEL channel);
#endif //DMA_H
