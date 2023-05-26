#include <xc.h>
#include "ISR_Support.h"

    .global PORTE_Change_Notice_IRQ
    .extern PORTE_CHANGE_NOTICE_HANDLER
    .set nomips16
    .set noreorder
    .set noat
    .ent PORTE_Change_Notice_IRQ
PORTE_Change_Notice_IRQ:
    portSAVE_CONTEXT
    jal PORTE_CHANGE_NOTICE_HANDLER
    nop
    portRESTORE_CONTEXT
    .end PORTE_Change_Notice_IRQ

    .global DMA0_IRQ
    .extern DMA0_HANDLER
    .set nomips16
    .set noreorder
    .set noat
    .ent DMA0_IRQ
DMA0_IRQ:
    portSAVE_CONTEXT
    jal DMA0_HANDLER
    nop
    portRESTORE_CONTEXT
    .end DMA0_IRQ

    .global DMA1_IRQ
    .extern DMA1_HANDLER
    .set nomips16
    .set noreorder
    .set noat
    .ent DMA1_IRQ
DMA1_IRQ:
    portSAVE_CONTEXT
    jal DMA1_HANDLER
    nop
    portRESTORE_CONTEXT
    .end DMA1_IRQ

    .global DMA2_IRQ
    .extern DMA2_HANDLER
    .set nomips16
    .set noreorder
    .set noat
    .ent DMA2_IRQ
DMA2_IRQ:
    portSAVE_CONTEXT
    jal DMA2_HANDLER
    nop
    portRESTORE_CONTEXT
    .end DMA2_IRQ

    .global UART1_FAULT_IRQ
    .extern UART1_FAULT_HANDLER
    .set nomips16
    .set noreorder
    .set noat
    .ent UART1_FAULT_IRQ
UART1_FAULT_IRQ:
    portSAVE_CONTEXT
    jal UART1_FAULT_HANDLER
    nop
    portRESTORE_CONTEXT
    .end UART1_FAULT_IRQ

    .global UART1_RX_IRQ
    .extern UART1_RX_HANDLER
    .set nomips16
    .set noreorder
    .set noat
    .ent UART1_RX_IRQ
UART1_RX_IRQ:
    portSAVE_CONTEXT
    jal UART1_RX_HANDLER
    nop
    portRESTORE_CONTEXT
    .end UART1_RX_IRQ

    .global ETHERNET_IRQ
    .extern ETHERNET_HANDLER
    .set nomips16
    .set noreorder
    .set noat
    .ent ETHERNET_IRQ
ETHERNET_IRQ:
    portSAVE_CONTEXT
    la    s6,  ETHERNET_HANDLER
    jalr  s6
    nop
    portRESTORE_CONTEXT
    .end   ETHERNET_IRQ
