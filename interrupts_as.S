#include <xc.h>
#include "ISR_Support.h"
#include "Reader_bsp.h"
#include "gpio.h"

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
