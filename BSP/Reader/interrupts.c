//
// Created by bruno on 28/01/23.
//
#include <xc.h>
#include <sys/attribs.h>

//void ETHERNET_handler_bsp(void);

void __ISR(_CHANGE_NOTICE_E_VECTOR, ipl0AUTO) PORTE_Change_Notice_IRQ( void );
void __ISR(_DMA0_VECTOR, ipl2AUTO) DMA0_IRQ( void );
void __ISR(_DMA1_VECTOR, ipl2AUTO) DMA1_IRQ( void );
void __ISR(_DMA2_VECTOR, ipl2AUTO) DMA2_IRQ( void );
void __ISR(_UART1_FAULT_VECTOR, ipl4AUTO) UART1_FAULT_IRQ( void );
void __ISR(_UART1_RX_VECTOR, ipl4AUTO) UART1_RX_IRQ( void );

void __ISR(_ETHERNET_VECTOR, ipl1AUTO) ETHERNET_IRQ(void);



//void ETHERNET_handler(void)
//{
//    ETHERNET_handler_bsp();
//}

//void __ISR(_SPI2_RX_VECTOR, ipl2AUTO) SPI2_RX_IRQ( void );
//void __ISR(_SPI2_TX_VECTOR, ipl2AUTO) SPI2_TX_IRQ( void );
