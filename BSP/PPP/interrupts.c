//
// Created by bleppe on 28/03/23.
//
#include <xc.h>
#include <sys/attribs.h>

void UART_interrupt_handler(uint32_t channel);
void DMA_interrupt_handler(uint32_t channel);

void __ISR(_DMA_0_VECTOR, ipl0AUTO) DMA0_IRQ( void );
void __ISR(_DMA_1_VECTOR, ipl0AUTO) DMA1_IRQ( void );
void __ISR(_UART_1_VECTOR, ipl0AUTO) UART1_IRQ( void );

void UART_1_HANDLER(void){
    UART_interrupt_handler(0);
}

void DMA_0_HANDLER(void){
    DMA_interrupt_handler(0);
}

void DMA_1_HANDLER(void){
    DMA_interrupt_handler(1);
}