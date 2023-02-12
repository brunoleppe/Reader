//
// Created by bruno on 28/01/23.
//
#include "gpio.h"
#include <xc.h>
#include <sys/attribs.h>

void __ISR(_TIMER_2_VECTOR, IPL1AUTO)   TIMER2_Interrupt_Handler(void);