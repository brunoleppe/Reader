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
#define KEYPAD_ALPHANUMERIC             0x0010

#ifdef __cplusplus
extern "C"{
#endif

_Noreturn void keypad_task(void *params);
void keypad_set_mode(uint32_t mode);
void keypad_calibrate( void );
void keypad_calibrate_key(int key);
void keypad_get_key_signal(int key);

#ifdef __cplusplus
}
#endif
#endif //KEYPAD_H
