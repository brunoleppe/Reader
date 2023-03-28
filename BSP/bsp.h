//
// Created by bruno on 25/01/23.
//

#ifndef READER_BSP_H
#define READER_BSP_H


#if defined (__LANGUAGE_C__) || defined (__LANGUAGE_C_PLUS_PLUS)
//#include "hal.h"
#include "gpio.h"
#include "dma.h"
#include "uart.h"
#include "pps.h"
#include "spi.h"
#endif

#define STRGIZE(x)              #x
#define STR(x)                  STRGIZE(x)
#define STR_CONCAT(x,y)         x##y
#define CONCAT(x,y)             STR_CONCAT(x,y)

#if defined (__LANGUAGE_C__) || defined (__LANGUAGE_C_PLUS_PLUS)
#ifdef __cplusplus
extern "C"{
#endif

void BSP_gpio_initialize(void );
void BSP_interrupts_initialize(void );
void BSP_gpio_callback_register(GPIO_PinMap pinMap, GPIO_Callback callback, uintptr_t context);
void BSP_drivers_initialize( void );
void BSP_task_initialize(void);
void BSP_system_initialize(void);

#ifdef __cplusplus
}
#endif
#endif
#endif //READER_BSP_H
