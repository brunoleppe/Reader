//
// Created by bruno on 28/01/23.
//
#include "gpio.h"




void QTOUCH_CHANGE_Handler(void){
    GPIO_interrupt_handler(GPIO_PORT_E);
}

void CORE_TIMER_Handler (void)
{

}