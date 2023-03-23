//
// Created by bruno on 25/01/23.
//

#ifndef READER_BSP_H
#define READER_BSP_H


#if defined (__LANGUAGE_C__) || defined (__LANGUAGE_C_PLUS_PLUS)
//#include "hal.h"
#include "gpio.h"
#include "dma.h"
#endif

#define STRGIZE(x)              #x
#define STR(x)                  STRGIZE(x)
#define STR_CONCAT(x,y)         x##y
#define CONCAT(x,y)             STR_CONCAT(x,y)

/*LEDs*/
#ifdef __READER_V2__
#define LED1                    GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_6)
#define LED2                    GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_7)
#define LED3                    GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_8)
#define LED4                    GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_9)
/*LCD*/
#define LCD_BLA                 GPIO_PIN_MAP(GPIO_PORT_E, GPIO_PIN_6)
#define LCD_SS                  GPIO_PIN_MAP(GPIO_PORT_E, GPIO_PIN_7)
#define LCD_RST                 GPIO_PIN_MAP(GPIO_PORT_C, GPIO_PIN_3)
#define LCD_DC                  GPIO_PIN_MAP(GPIO_PORT_C, GPIO_PIN_4)
#define LCD_SDO                 GPIO_PIN_MAP(GPIO_PORT_G, GPIO_PIN_7)
#define LCD_SCK                 GPIO_PIN_MAP(GPIO_PORT_G, GPIO_PIN_6)
#define LCD_SPI_CHANNEL         SPI_CHANNEL_2
#define LCD_SPI_OUTPUT_REG      PPS_OUTPUT_REG_RPG7
#define LCD_SPI_OUTPUT_MAP      PPS_RPG7_SDO2
/*QTOUCH*/
#define QT_CHANGE               GPIO_PIN_MAP(GPIO_PORT_E, GPIO_PIN_9)
#define QT_RST                  GPIO_PIN_MAP(GPIO_PORT_E, GPIO_PIN_8)
#define QT_SDO                  GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_3)
#define QT_SS                   GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_4)
#define QT_SDI                  GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_5)
#define QT_SCK                  GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_14)
#define QT_SPI_CHANNEL          SPI_CHANNEL_3
#define QT_SPI_OUTPUT_REG       PPS_OUTPUT_REG_RPB3
#define QT_SPI_INPUT_REG        PPS_INPUT_REG_SDI3
#define QT_SPI_OUTPUT_MAP       PPS_RPB3_SDO3
#define QT_SPI_INPUT_MAP        PPS_SDI3_RPB5

#define QT_INTERRUPT_VECTOR     EVIC_CHANNEL_CHANGE_NOTICE_E

/*Interrupts*/
#define PORT_VECTOR 122

#define BUZZER                  GPIO_PIN_MAP(GPIO_PORT_F, GPIO_PIN_2)
#define BUZZER_OUTPUT_REG       PPS_OUTPUT_REG_RPF2
#define BUZZER_OUTPUT_MAP       PPS_RPF2_OC1

/*SPI Driver*/
#define SPI_DRIVER_INSTANCES    2

#define SPI_DRIVER_INSTANCE_0   0
#define SPI_DRIVER_INSTANCE_0_CLIENTS   1

#define SPI_DRIVER_INSTANCE_1   1
#define SPI_DRIVER_INSTANCE_1_CLIENTS   1

#else
/*LEDs*/
#define LED1                    GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_6)
#define LED2                    GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_7)
#define LED3                    GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_8)
#define LED4                    GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_9)
/*LCD*/
#define LCD_DC                  GPIO_PIN_MAP(GPIO_PORT_C, GPIO_PIN_14)
#define LCD_BLA                 GPIO_PIN_MAP(GPIO_PORT_D, GPIO_PIN_13)
#define LCD_RST                 GPIO_PIN_MAP(GPIO_PORT_D, GPIO_PIN_12)
#define LCD_SS                  GPIO_PIN_MAP(GPIO_PORT_A, GPIO_PIN_6)
#define LCD_SDO                 GPIO_PIN_MAP(GPIO_PORT_D, GPIO_PIN_3)
#define LCD_SCK                 GPIO_PIN_MAP(GPIO_PORT_D, GPIO_PIN_1)
#define LCD_SPI_CHANNEL         SPI_CHANNEL_1
#define LCD_SPI_OUTPUT_REG      PPS_OUTPUT_REG_RPD3
#define LCD_SPI_OUTPUT_MAP      PPS_RPD3_SDO1
/*QTOUCH*/
#define QT_CHANGE               GPIO_PIN_MAP(GPIO_PORT_E, GPIO_PIN_9)
#define QT_RST                  GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_2)
#define QT_SDO                  GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_3)
#define QT_SS                   GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_4)
#define QT_SDI                  GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_5)
#define QT_SCK                  GPIO_PIN_MAP(GPIO_PORT_E, GPIO_PIN_14)
#define QT_SPI_CHANNEL          SPI_CHANNEL_3
#define QT_SPI_OUTPUT_REG       PPS_OUTPUT_REG_RPB3
#define QT_SPI_INPUT_REG        PPS_INPUT_REG_SDI3
#define QT_SPI_OUTPUT_MAP       PPS_RPB3_SDO3
#define QT_SPI_INPUT_MAP        PPS_SDI3_RPB5
#define QT_INTERRUPT_VECTOR     EVIC_CHANNEL_CHANGE_NOTICE_E

/*Interrupts*/

#define BUZZER                  GPIO_PIN_MAP(GPIO_PORT_F, GPIO_PIN_2)
#define BUZZER_OUTPUT_REG       PPS_OUTPUT_REG_RPF2
#define BUZZER_OUTPUT_MAP       PPS_RPF2_OC1

#endif /*__READER_V2__*/

#define LCD_DMA_CHANNEL         DMA_CHANNEL_0


#if defined (__LANGUAGE_C__) || defined (__LANGUAGE_C_PLUS_PLUS)
#ifdef __cplusplus
extern "C"{
#endif
void BSP_gpio_initialize(void );
void BSP_interrupts_initialize(void );
void BSP_gpio_callback_register(GPIO_PinMap pinMap, GPIO_Callback callback, uintptr_t context);


#ifdef __cplusplus
}
#endif
#endif
#endif //READER_BSP_H
