//
// Created by bruno on 28/01/23.
//
#include "gpio.h"
#include <xc.h>
#include <sys/attribs.h>

void __ISR(_CHANGE_NOTICE_E_VECTOR, ipl0AUTO) PORTE_Change_Notice_IRQ( void );