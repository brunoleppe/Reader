//
// Created by bleppe on 29/03/23.
//

#include "hal.h"

#ifndef QTOUCH_H
#define QTOUCH_H




enum QT_KEY{
    QT_KEY_1        = 0x000100,
    QT_KEY_2        = 0x000001,
    QT_KEY_3        = 0x000200,
    QT_KEY_4        = 0x000002,
    QT_KEY_5        = 0x000400,
    QT_KEY_6        = 0x000004,
    QT_KEY_7        = 0x000800,
    QT_KEY_8        = 0x000008,
    QT_KEY_9        = 0x001000,
    QT_KEY_0        = 0x002000,
    QT_KEY_DOT      = 0x000020,
    QT_KEY_ENTER    = 0x000010,
    QT_KEY_OPTION   = 0x008000,
    QT_KEY_RETURN   = 0x000080,
    QT_KEY_CANCEL   = 0x004000,
    QT_KEY_CLEAR    = 0x000040,
    QT_KEY_PUMP     = 0x010000,
    QT_KEY_RELEASE  = 0,
};

int     QTouch_initialize(int spiDriverIndex, GPIO_PinMap cs, GPIO_PinMap rst, GPIO_PinMap change, GPIO_PinMap drdy);

int     QTouch_calibrate_all();
bool     QTouch_get_key(int *key);

#endif //QTOUCH_H
