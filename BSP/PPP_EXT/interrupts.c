
#include <xc.h>
#include <sys/attribs.h>

void DMA_interrupt_handler(uint32_t channel);

void __ISR(_DMA0_VECTOR, ipl0AUTO) DMA0_IRQ( void );
void __ISR(_DMA1_VECTOR, ipl0AUTO) DMA1_IRQ( void );

void DMA_0_HANDLER(void){
    DMA_interrupt_handler(0);
}

void DMA_1_HANDLER(void){
    DMA_interrupt_handler(1);
}