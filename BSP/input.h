//
// Created by bleppe on 31/03/23.
//

#ifndef READER_INPUT_H
#define READER_INPUT_H

#include <stdbool.h>

enum INPUT_EVENTS{
    INPUT_EVENT_PRESSED = 1,
    INPUT_EVENT_RELEASED = 0,
    INPUT_EVENT_CLICKED = 2,
    INPUT_EVENT_LONG_CLICKED = 3,
    INPUT_EVENT_LONG_LONG_CLICKED = 4,
};

typedef struct{
    int code;
    int value;
}InputEvent;

#ifdef __cplusplus
extern "C" {
#endif

bool input_report_key(int code, int value);

#ifdef __cplusplus
}
#endif

#endif //READER_INPUT_H
