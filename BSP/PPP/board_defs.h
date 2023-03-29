//
// Created by bleppe on 28/03/23.
//

#ifndef BOARD_DEFS_H
#define BOARD_DEFS_H



#define SPI_SCK_PIN                             GPIO_PIN_MAP(GPIO_PORT_G, GPIO_PIN_6)
#define SPI_SDI_PIN                             GPIO_PIN_MAP(GPIO_PORT_G, GPIO_PIN_7)
#define SPI_SDO_PIN                             GPIO_PIN_MAP(GPIO_PORT_G, GPIO_PIN_8)
#define SPI_CHANNEL                             SPI_CHANNEL_2
/*QTOUCH*/
#define QT_SS_PIN                               GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_1)
#define QT_RESET_PIN                            GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_0)
#define QT_DRDY_PIN                             GPIO_PIN_MAP(GPIO_PORT_D, GPIO_PIN_10)

/*LED MATRIX*/
#define LED_M_COL0_PIN                          GPIO_PIN_MAP(GPIO_PORT_F, GPIO_PIN_0)
#define LED_M_COL1_PIN                          GPIO_PIN_MAP(GPIO_PORT_F, GPIO_PIN_1)
#define LED_M_COL2_PIN                          GPIO_PIN_MAP(GPIO_PORT_D, GPIO_PIN_11)
#define LED_M_COL3_PIN                          GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_13)
#define LED_M_ROW0_PIN                          GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_12)
#define LED_M_ROW1_PIN                          GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_11)
#define LED_M_ROW2_PIN                          GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_10)
#define LED_M_ROW3_PIN                          GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_9)
#define LED_M_ROW4_PIN                          GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_8)

/*LCD*/
#define LCD_DC_PIN                              GPIO_PIN_MAP(GPIO_PORT_D, GPIO_PIN_4)
#define LCD_BLA_PIN                             GPIO_PIN_MAP(GPIO_PORT_D, GPIO_PIN_7)
#define LCD_RST_PIN                             GPIO_PIN_MAP(GPIO_PORT_D, GPIO_PIN_5)
#define LCD_SS_PIN                              GPIO_PIN_MAP(GPIO_PORT_D, GPIO_PIN_6)
#define LCD_DMA_CHANNEL                         DMA_CHANNEL_0

/*UART*/
#define DEBUG_UART                              UART_CHANNEL_1

/*SPI DRIVER*/
#define SPI_DRIVER_INSTANCES    1

#define SPI_DRIVER_INSTANCE_0   0
#define SPI_DRIVER_INSTANCE_0_CLIENTS   3
#endif //BOARD_DEFS_H
