//
// Created by bleppe on 28/03/23.
//

#ifndef BOARD_DEFS_H
#define BOARD_DEFS_H

#ifdef __READER_V2__
/*LEDs*/
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

/*FLASH MEM*/
#define FLASH_SDO               GPIO_PIN_MAP(GPIO_PORT_F, GPIO_PIN_5)
#define FLASH_SDI               GPIO_PIN_MAP(GPIO_PORT_A, GPIO_PIN_15)
#define FLASH_SCK
#define FLASH_SS                GPIO_PIN_MAP(GPIO_PORT_F, GPIO_PIN_4)
#define FLASH_SPI_CHANNEL       SPI_CHANNEL_4
#define FLASH_SPI_INPUT_REG     PPS_INPUT_REG_SDI4
#define FLASH_SPI_INPUT_MAP     PPS_SDI4_RPA15
#define FLASH_SPI_OUTPUT_REG    PPS_OUTPUT_REG_RPF5
#define FLASH_SPI_OUTPUT_MAP    PPS_RPF5_SDO4


#define BUZZER                  GPIO_PIN_MAP(GPIO_PORT_F, GPIO_PIN_2)
#define BUZZER_OUTPUT_REG       PPS_OUTPUT_REG_RPF2
#define BUZZER_OUTPUT_MAP       PPS_RPF2_OC1

/*SPI Driver*/
//#define SPI_DRIVER_INSTANCES    2

#define SPI_DRIVER_INSTANCE_0   0
#define SPI_DRIVER_INSTANCE_0_CLIENTS   1

#define SPI_DRIVER_INSTANCE_1   1
#define SPI_DRIVER_INSTANCE_1_CLIENTS   1

#define SPI_DRIVER_INSTANCE_2   2
#define SPI_DRIVER_INSTANCE_2_CLIENTS   1

#define UART                    UART_CHANNEL_1
#define UART_RX_PIN             GPIO_PIN_MAP(GPIO_PORT_G, GPIO_PIN_1)
#define UART_TX_PIN             GPIO_PIN_MAP(GPIO_PORT_G, GPIO_PIN_0)
#define UART_RX_INPUT_REG       PPS_INPUT_REG_U1RX
#define UART_RX_INPUT_MAP       PPS_U1RX_RPG1
#define UART_TX_OUTPUT_REG      PPS_OUTPUT_REG_RPG0
#define UART_TX_OUTPUT_MAP      PPS_RPG0_U1TX

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

/*FLASH MEM*/
#define FLASH_SDO               GPIO_PIN_MAP(GPIO_PORT_G, GPIO_PIN_7)
#define FLASH_SDI               GPIO_PIN_MAP(GPIO_PORT_C, GPIO_PIN_4)
#define FLASH_SCK
#define FLASH_SS                GPIO_PIN_MAP(GPIO_PORT_C, GPIO_PIN_3)
#define FLASH_SPI_CHANNEL       SPI_CHANNEL_2
#define FLASH_SPI_INPUT_REG     PPS_INPUT_REG_SDI2
#define FLASH_SPI_INPUT_MAP     PPS_SDI2_RPC4
#define FLASH_SPI_OUTPUT_REG    PPS_OUTPUT_REG_RPG7
#define FLASH_SPI_OUTPUT_MAP    PPS_RPG7_SDO2

/*Interrupts*/

#define BUZZER                  GPIO_PIN_MAP(GPIO_PORT_F, GPIO_PIN_2)
#define BUZZER_OUTPUT_REG       PPS_OUTPUT_REG_RPF2
#define BUZZER_OUTPUT_MAP       PPS_RPF2_OC1
/*SPI Driver*/
//#define SPI_DRIVER_INSTANCES    2

#define SPI_DRIVER_INSTANCE_0   0
#define SPI_DRIVER_INSTANCE_0_CLIENTS   1

#define SPI_DRIVER_INSTANCE_1   1
#define SPI_DRIVER_INSTANCE_1_CLIENTS   1

#define SPI_DRIVER_INSTANCE_2   2
#define SPI_DRIVER_INSTANCE_2_CLIENTS   1

#define UART                    UART_CHANNEL_1
#define UART_RX_PIN             GPIO_PIN_MAP(GPIO_PORT_G, GPIO_PIN_1)
#define UART_TX_PIN             GPIO_PIN_MAP(GPIO_PORT_G, GPIO_PIN_0)
#define UART_RX_INPUT_REG       PPS_INPUT_REG_U1RX
#define UART_RX_INPUT_MAP       PPS_U1RX_RPG1
#define UART_TX_OUTPUT_REG      PPS_OUTPUT_REG_RPG0
#define UART_TX_OUTPUT_MAP      PPS_RPG0_U1TX

#endif /*__READER_V2__*/


/*ETHERNET*/
#define ETXD0_PIN                               GPIO_PIN_MAP(GPIO_PORT_F, GPIO_PIN_1)
#define ETXD1_PIN                               GPIO_PIN_MAP(GPIO_PORT_F, GPIO_PIN_0)
#define ERXD0_PIN                               GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_12)
#define ERXD1_PIN                               GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_13)
#define ETXEN_PIN                               GPIO_PIN_MAP(GPIO_PORT_D, GPIO_PIN_2)
#define ECRSDV_PIN                              GPIO_PIN_MAP(GPIO_PORT_G, GPIO_PIN_8)
#define ERXERR_PIN                              GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_8)
#define EREFCLK_PIN                             GPIO_PIN_MAP(GPIO_PORT_G, GPIO_PIN_9)
#define EMDC_PIN                                GPIO_PIN_MAP(GPIO_PORT_D, GPIO_PIN_11)
#define EMDIO_PIN                               GPIO_PIN_MAP(GPIO_PORT_D, GPIO_PIN_0)

#define LCD_TX_DMA_CHANNEL          DMA_CHANNEL_0
#define FLASH_TX_DMA_CHANNEL        DMA_CHANNEL_1
#define FLASH_RX_DMA_CHANNEL        DMA_CHANNEL_2
#endif //BOARD_DEFS_H
