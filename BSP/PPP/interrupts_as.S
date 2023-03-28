#include "../../../../../../opt/microchip/xc32/v4.21/pic32mx/include/xc.h"
#include "../../FreeRTOS/Source/portable/MPLAB/PIC32MZ/ISR_Support.h"
#include "../bsp.h"
#include "../../HAL/gpio.h"
#include "../../HAL/timer.h"
#include "../../HAL/spi.h"
#include "../../HAL/dma.h"
#include "../../HAL/uart.h"

    .global DMA0_IRQ
    .extern DMA_interrupt_handler
    .set nomips16
    .set noreorder
    .set noat
    .ent DMA0_IRQ
DMA0_IRQ:
    portSAVE_CONTEXT
    li a0, DMA_CHANNEL_0
    jal DMA_interrupt_handler
    nop
    portRESTORE_CONTEXT
    .end DMA0_IRQ

    .global UART1_FAULT_IRQ
    .extern UART_fault_interrupt_handler
    .set nomips16
    .set noreorder
    .set noat
    .ent UART1_FAULT_IRQ