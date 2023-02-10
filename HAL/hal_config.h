//
// Created by bruno on 09/02/23.
//

#ifndef READER_HAL_CONFIG_H
#define READER_HAL_CONFIG_H

/**********************************************************************
* FreeRTOS
**********************************************************************/
#define HAL_USE_FREERTOS                    1
/**********************************************************************
* GPIO
**********************************************************************/
#define GPIO_USE_IRQ_PORT_A                 0
#define GPIO_USE_IRQ_PORT_B                 0
#define GPIO_USE_IRQ_PORT_C                 0
#define GPIO_USE_IRQ_PORT_D                 0
#define GPIO_USE_IRQ_PORT_E                 1
#define GPIO_USE_IRQ_PORT_F                 0
#define GPIO_USE_IRQ_PORT_G                 0
#define GPIO_USE_IRQ_PORT_H                 0
#define GPIO_USE_IRQ_PORT_J                 0
#define GPIO_USE_IRQ_PORT_K                 0
/**********************************************************************
* SPI
**********************************************************************/
#define SPI_USE_IRQ_CHANNEL_1               0
#define SPI_USE_IRQ_CHANNEL_2               0
#define SPI_USE_IRQ_CHANNEL_3               0
#define SPI_USE_IRQ_CHANNEL_4               0
#define SPI_USE_IRQ_CHANNEL_5               0
#define SPI_USE_IRQ_CHANNEL_6               0


#endif //READER_HAL_CONFIG_H
