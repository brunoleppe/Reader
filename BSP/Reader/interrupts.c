//
// Created by bruno on 28/01/23.
//
#include <xc.h>
#include <sys/attribs.h>
#include "HAL/hal.h"
//void ETHERNET_handler_bsp(void);

void UART_rx_interrupt_handler(uint32_t channel);
void UART_fault_interrupt_handler(uint32_t channel);
void DMA_interrupt_handler(uint32_t channel);

void __ISR(_CHANGE_NOTICE_E_VECTOR, ipl0AUTO) PORTE_Change_Notice_IRQ( void );
void __ISR(_DMA0_VECTOR, ipl2AUTO) DMA0_IRQ( void );
void __ISR(_DMA1_VECTOR, ipl2AUTO) DMA1_IRQ( void );
void __ISR(_DMA2_VECTOR, ipl2AUTO) DMA2_IRQ( void );
void __ISR(_UART1_FAULT_VECTOR, ipl4AUTO) UART1_FAULT_IRQ( void );
void __ISR(_UART1_RX_VECTOR, ipl4AUTO) UART1_RX_IRQ( void );

void __ISR(_ETHERNET_VECTOR, ipl1AUTO) ETHERNET_IRQ(void);

void PORTE_CHANGE_NOTICE_HANDLER(void)
{
    GPIO_interrupt_handler(GPIO_PORT_E);
}
void DMA0_HANDLER( void )
{
    DMA_interrupt_handler(DMA_CHANNEL_0);
}
void DMA1_HANDLER( void )
{
    DMA_interrupt_handler(DMA_CHANNEL_0);
}
void DMA2_HANDLER( void )
{
    DMA_interrupt_handler(DMA_CHANNEL_0);
}
void UART1_FAULT_HANDLER( void )
{
    UART_fault_interrupt_handler(UART_CHANNEL_1);
}
void UART1_RX_HANDLER( void )
{
    UART_rx_interrupt_handler(UART_CHANNEL_1);
}

