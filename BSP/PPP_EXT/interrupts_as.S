#include <xc.h>
#include "ISR_Support.h"


//    .global DMA0_IRQ
//    .extern DMA_0_HANDLER
//    .set nomicromips
//    .set nomips16
//    .set noreorder
//    .set noat
//    .ent DMA0_IRQ
//DMA0_IRQ:
//    la $26, _DMA_0_HANDLER
//    jr $26
//    nop
//    .end DMA0_IRQ
//
//_DMA_0_HANDLER:
//    portSAVE_CONTEXT
//    la s6, DMA_0_HANDLER
//    jalr s6
//    nop
//    portRESTORE_CONTEXT
//    .end _DMA_0_HANDLER
//
//    .global DMA1_IRQ
//    .extern DMA_q_HANDLER
//    .set nomicromips
//    .set nomips16
//    .set noreorder
//    .set noat
//    .ent DMA1_IRQ
//DMA1_IRQ:
//    la $26, _DMA_1_HANDLER
//    jr $26
//    nop
//    .end DMA1_IRQ
//
//_DMA_1_HANDLER:
//    portSAVE_CONTEXT
//    la s6, _DMA_1_HANDLER
//    jalr s6
//    nop
//    portRESTORE_CONTEXT
//    .end _DMA_1_HANDLER

    .global DMA0_IRQ
    .extern  DMA_0_HANDLER
    .set     nomicromips
    .set     noreorder
    .set     nomips16
    .set     noat
    .ent  DMA0_IRQ

DMA0_IRQ:
    portSAVE_CONTEXT
    la    s6,  DMA_0_HANDLER
    jalr  s6
    nop
    portRESTORE_CONTEXT
    .end	DMA0_IRQ


    /* Sytem DMA Instance 1 Interrupt */
    .global  DMA1_IRQ
    .extern  DMA_1_HANDLER
    .set     nomicromips
    .set     noreorder
    .set     nomips16
    .set     noat
    .ent  DMA1_IRQ

DMA1_IRQ:
    portSAVE_CONTEXT
    la    s6,  DMA_1_HANDLER
    jalr  s6
    nop
    portRESTORE_CONTEXT
    .end	DMA1_IRQ

    .global ETHERNET_IRQ
    .extern ETHERNET_HANDLER
    .set    nomicromips
    .set    noreorder
    .set    nomips16
    .set    noat
    .ent    ETHERNET_IRQ
ETHERNET_IRQ:
    portSAVE_CONTEXT
    la      s6, ETHERNET_HANDLER
    jalr    s6
    nop
    portRESTORE_CONTEXT
    .end    ETHERNET_IRQ
