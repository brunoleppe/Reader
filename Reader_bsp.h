//
// Created by bruno on 25/01/23.
//

#ifndef READER_BSP_H
#define READER_BSP_H

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

#define LCD_SPI_CHANNEL     SPI_CHANNEL_1

void PORTS_Initialize();

#endif //READER_BSP_H
