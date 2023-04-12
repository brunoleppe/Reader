#include <features.h>
//
// Created by bleppe on 20/03/23.
//

#ifndef KEYPAD_H
#define KEYPAD_H

#include <stdint.h>

#define KEYPAD_NUMERIC                  0x0001
#define KEYPAD_ALPHA                    0x0002
#define KEYPAD_CONTROLS                 0x0004
#define KEYPAD_ALTERNATE                0x0008
#define KEYPAD_ALPHANUMERIC             (KEYPAD_ALPHA | KEYPAD_NUMERIC)

_Noreturn void keypad_task(void *params);
void keypad_set_mode(uint32_t mode);

#endif //KEYPAD_H
