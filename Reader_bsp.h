//
// Created by bruno on 25/01/23.
//

#ifndef READER_BSP_H
#define READER_BSP_H

#ifdef __READER_V2__
#define LED1                GPIO_PORTB_6
#define LED2                GPIO_PORTB_7
#define LED3                GPIO_PORTB_8
#define LED4                GPIO_PORTB_9

#define LCD_BLA             GPIO_PORTE_6
#define LCD_SS              GPIO_PORTE_7
#define LCD_RST             GPIO_PORTC_3
#define LCD_DC              GPIO_PORTC_4
#define LCD_SDO             GPIO_PORTG_7
#define LCD_SCK             GPIO_PORTG_6

#define LCD_SDO_AF          GPIO_AF_6
#define LCD_SPI_CHANNEL     SPI_CHANNEL_2


#else

#define LED1                GPIO_PORTB_6
#define LED2                GPIO_PORTB_7
#define LED3                GPIO_PORTB_8
#define LED4                GPIO_PORTB_9

#define LCD_DC              GPIO_PORTC_14
#define LCD_BLA             GPIO_PORTD_13
#define LCD_RST             GPIO_PORTD_12
#define LCD_SS              GPIO_PORTA_6
#define LCD_SDO             GPIO_PORTD_3
#define LCD_SCK             GPIO_PORTD_1

#define LCD_SDO_AF          GPIO_AF_5
#define LCD_SPI_CHANNEL     SPI_CHANNEL_1

#endif /*__READER_V2__*/


void PORTS_Initialize();

#endif //READER_BSP_H
