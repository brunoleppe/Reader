//
// Created by bleppe on 28/03/23.
//

#ifndef BOARD_DEFS_H
#define BOARD_DEFS_H



#define SPI_SCK_PIN                             GPIO_PIN_MAP(GPIO_PORT_D, GPIO_PIN_1)
#define SPI_SDI_PIN                             GPIO_PIN_MAP(GPIO_PORT_D, GPIO_PIN_2)
#define SPI_SDO_PIN                             GPIO_PIN_MAP(GPIO_PORT_D, GPIO_PIN_3)
#define SPI_CHANNEL                             SPI_CHANNEL_1
#define SPI_INPUT_REG                           PPS_INPUT_REG_SDI1
#define SPI_INPUT_MAP                           PPS_SDI1_RPD2
#define SPI_OUTPUT_REG                          PPS_OUTPUT_REG_RPD3
#define SPI_OUTPUT_MAP                          PPS_RPD3_SDO1


/*QTOUCH*/
#define QT_SS_PIN                               GPIO_PIN_MAP(GPIO_PORT_D, GPIO_PIN_12)
#define QT_RST_PIN                              GPIO_PIN_MAP(GPIO_PORT_C, GPIO_PIN_14)
#define QT_DRDY_PIN                             GPIO_PIN_MAP(GPIO_PORT_J, GPIO_PIN_2)
#define QT_CHANGE_PIN                           GPIO_PIN_MAP(GPIO_PORT_D, GPIO_PIN_13)

/*LED MATRIX*/
#define LED_M_COL0_PIN                          GPIO_PIN_MAP(GPIO_PORT_E, GPIO_PIN_5)
#define LED_M_COL1_PIN                          GPIO_PIN_MAP(GPIO_PORT_E, GPIO_PIN_6)
#define LED_M_COL2_PIN                          GPIO_PIN_MAP(GPIO_PORT_E, GPIO_PIN_7)
#define LED_M_COL3_PIN                          GPIO_PIN_MAP(GPIO_PORT_E, GPIO_PIN_8)
#define LED_M_ROW0_PIN                          GPIO_PIN_MAP(GPIO_PORT_E, GPIO_PIN_0)
#define LED_M_ROW1_PIN                          GPIO_PIN_MAP(GPIO_PORT_E, GPIO_PIN_1)
#define LED_M_ROW2_PIN                          GPIO_PIN_MAP(GPIO_PORT_E, GPIO_PIN_2)
#define LED_M_ROW3_PIN                          GPIO_PIN_MAP(GPIO_PORT_E, GPIO_PIN_3)
#define LED_M_ROW4_PIN                          GPIO_PIN_MAP(GPIO_PORT_E, GPIO_PIN_4)

/*LCD*/
#define LCD_DC_PIN                              GPIO_PIN_MAP(GPIO_PORT_C, GPIO_PIN_15)
#define LCD_BLA_PIN                             GPIO_PIN_MAP(GPIO_PORT_D, GPIO_PIN_15)
#define LCD_RST_PIN                             GPIO_PIN_MAP(GPIO_PORT_C, GPIO_PIN_12)
#define LCD_SS_PIN                              GPIO_PIN_MAP(GPIO_PORT_H, GPIO_PIN_7)
#define LCD_TX_DMA_CHANNEL                      DMA_CHANNEL_0
#define LCD_RX_DMA_CHANNEL                      DMA_CHANNEL_1

/*FLASH*/
#define FLASH_SS_PIN                            GPIO_PIN_MAP(GPIO_PORT_C, GPIO_PIN_4)

/*UART*/
#define DEBUG_UART                              UART_CHANNEL_2


/*SPI DRIVER*/
#define SPI_DRIVER_INSTANCE_0   0
#define SPI_DRIVER_INSTANCE_0_CLIENTS   3

#define QT_SPI_DRIVER_INDEX             0
#define LCD_SPI_DRIVER_INDEX            0
#define FLASH_SPI_DRIVER_INDEX          0

#endif //BOARD_DEFS_H
