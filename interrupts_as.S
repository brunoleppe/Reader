#include <xc.h>
#include "ISR_Support.h"
#include "BSP/bsp.h"
#include "gpio.h"
#include "timer.h"
#include "spi.h"
#include "dma.h"
#include "uart.h"

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
UART1_FAULT_IRQ:
    portSAVE_CONTEXT
    li a0, UART_CHANNEL_1
    jal UART_fault_interrupt_handler
    nop
    portRESTORE_CONTEXT
    .end UART1_FAULT_IRQ

    .global UART1_RX_IRQ
    .extern UART_rx_interrupt_handler
    .set nomips16
    .set noreorder
    .set noat
    .ent UART1_RX_IRQ
UART1_RX_IRQ:
    portSAVE_CONTEXT
    li a0, UART_CHANNEL_1
    jal UART_rx_interrupt_handler
    nop
    portRESTORE_CONTEXT
    .end UART1_RX_IRQ
//    .global SPI2_RX_IRQ
//    .extern SPI_rx_interrupt_handler
//    .set nomips16
//    .set noreorder
//    .set noat
//    .ent SPI2_RX_IRQ
//SPI2_RX_IRQ:
//    portSAVE_CONTEXT
//    li a0, SPI_CHANNEL_2
//    jal SPI_rx_interrupt_handler
//    nop
//    portRESTORE_CONTEXT
//    .end SPI2_RX_IRQ
//
//    .global SPI2_TX_IRQ
//    .extern SPI_tx_interrupt_handler
//    .set nomips16
//    .set noreorder
//    .set noat
//    .ent SPI2_TX_IRQ
//SPI2_TX_IRQ:
//    portSAVE_CONTEXT
//    li a0, SPI_CHANNEL_2
//    jal SPI_tx_interrupt_handler
//    nop
//    portRESTORE_CONTEXT
//    .end SPI2_TX_IRQ