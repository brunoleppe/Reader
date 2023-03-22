//
// Created by bleppe on 20/03/23.
//

#include "hal.h"

#ifndef QTOUCH_H
#define QTOUCH_H

int     QTouch_initialize(SPI_Channel channel, GPIO_PinMap cs, GPIO_PinMap rst, GPIO_PinMap change, GPIO_PinMap drdy);
int     QTouch_get_key();
int     QTouch_calibrate();

#endif //QTOUCH_H
