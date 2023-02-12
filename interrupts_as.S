#include <xc.h>
#include "ISR_Support.h"
#include "Reader_bsp.h"
#include "gpio.h"
#include "timer.h"

    .global PORTE_Change_Notice_IRQ
    .extern GPIO_interrupt_handler
    .set nomips16
    .set noreorder
    .set noat
    .ent PORTE_Change_Notice_IRQ
PORTE_Change_Notice_IRQ:
    portSAVE_CONTEXT
    li a0, GPIO_PORT_E
    jal GPIO_interrupt_handler
    nop
    portRESTORE_CONTEXT
    .end PORTE_Change_Notice_IRQ

    .global TIMER2_Interrupt_Handler
    .extern GPIO_interrupt_handler
    .set nomips16
    .set noreorder
    .set noat
    .ent TIMER2_Interrupt_Handler
TIMER2_Interrupt_Handler:
    portSAVE_CONTEXT
    li a0, TMR_CHANNEL_2
    jal TMR_interrupt_handler
    nop
    portRESTORE_CONTEXT
    .end TIMER2_Interrupt_Handler