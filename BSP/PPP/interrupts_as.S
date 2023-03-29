#include <xc.h>
#include "ISR_Support.h"
#include "../bsp.h"
#include "../../HAL/gpio.h"
#include "../../HAL/timer.h"
#include "../../HAL/spi.h"
#include "../../HAL/dma.h"
#include "../../HAL/uart.h"

    .global DMA0_IRQ
    .extern DMA_0_HANDLER
    .set nomicromips
    .set nomips16
    .set noreorder
    .set noat
    .ent DMA0_IRQ
DMA0_IRQ:
    la $26, _DMA_0_HANDLER
    jr $26
    nop
    .end DMA0_IRQ

_DMA_0_HANDLER:
    portSAVE_CONTEXT
    la s6, DMA_0_HANDLER
    jalr s6
    nop
    portRESTORE_CONTEXT
    .end _DMA_0_HANDLER

    .global UART1_IRQ
    .extern UART_1_HANDLER
    .set nomicromips
    .set nomips16
    .set noreorder
    .set noat
    .ent UART1_IRQ
UART1_IRQ:
    la $26, _UART_1_HANDLER
    jr $26
    nop
    .end UART1_IRQ

_UART_1_HANDLER:
    portSAVE_CONTEXT
    la    s6,  UART_1_HANDLER
    jalr  s6
    nop
    portRESTORE_CONTEXT
    .end    _UART_1_Handler



