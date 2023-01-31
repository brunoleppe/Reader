//
// Created by bruno on 25/01/23.
//

#ifndef READER_BSP_H
#define READER_BSP_H

#define STRGIZE(x)              #x
#define STR(x)                  STRGIZE(x)
#define STR_CONCAT(x,y)         x##y
#define CONCAT(x,y)             STR_CONCAT(x,y)

/*LEDs*/
#ifdef __READER_V2__
#define LED1                GPIO_PORTB_6
#define LED2                GPIO_PORTB_7
#define LED3                GPIO_PORTB_8
#define LED4                GPIO_PORTB_9
/*LCD*/
#define LCD_BLA             GPIO_PORTE_6
#define LCD_SS              GPIO_PORTE_7
#define LCD_RST             GPIO_PORTC_3
#define LCD_DC              GPIO_PORTC_4
#define LCD_SDO             GPIO_PORTG_7
#define LCD_SCK             GPIO_PORTG_6
#define LCD_SDO_AF          GPIO_AF_6
#define LCD_SPI_CHANNEL     SPI_CHANNEL_2
/*QTOUCH*/
#define QT_CHANGE           GPIO_PORTE_9
#define QT_RST              GPIO_PORTE_8
#define QT_SDO              GPIO_PORTB_3
#define QT_SS               GPIO_PORTB_4
#define QT_SDI              GPIO_PORTB_5
#define QT_SCK              GPIO_PORTB_14
#define QT_SDO_AF           GPIO_AF_7
#define QT_SDI_AF           GPIO_AF_8
#define QT_SPI_CHANNEL      SPI_CHANNEL_3
#define QT_INTERRUPT_VECTOR EVIC_CHANNEL_CHANGE_NOTICE_E

/*Interrupts*/
#define PORT_VECTOR 122

#else
/*LEDs*/
#define LED1                GPIO_PORTB_6
#define LED2                GPIO_PORTB_7
#define LED3                GPIO_PORTB_8
#define LED4                GPIO_PORTB_9
/*LCD*/
#define LCD_DC              GPIO_PORTC_14
#define LCD_BLA             GPIO_PORTD_13
#define LCD_RST             GPIO_PORTD_12
#define LCD_SS              GPIO_PORTA_6
#define LCD_SDO             GPIO_PORTD_3
#define LCD_SCK             GPIO_PORTD_1
#define LCD_SDO_AF          GPIO_AF_5
#define LCD_SPI_CHANNEL     SPI_CHANNEL_1
/*QTOUCH*/
#define QT_CHANGE           GPIO_PORTE_9
#define QT_RST              GPIO_PORTB_2
#define QT_SDO              GPIO_PORTB_3
#define QT_SS               GPIO_PORTB_4
#define QT_SDI              GPIO_PORTB_5
#define QT_SCK              GPIO_PORTB_14
#define QT_SDO_AF           GPIO_AF_7
#define QT_SDI_AF           GPIO_AF_8
#define QT_SPI_CHANNEL      SPI_CHANNEL_3
#define QT_INTERRUPT_VECTOR EVIC_CHANNEL_CHANGE_NOTICE_E

/*Interrupts*/

#endif /*__READER_V2__*/

#define QTOUCH_VECTOR   .vector_122
#define QTOUCH_VECTOR_DISPATCH   __vector_dispatch_122


#if defined (__LANGUAGE_C__) || defined (__LANGUAGE_C_PLUS_PLUS)
void gpio_initialize( void );
void interrupts_initialize( void );
#endif
#endif //READER_BSP_H
