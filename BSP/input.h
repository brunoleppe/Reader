//
// Created by bleppe on 31/03/23.
//

#ifndef READER_INPUT_H
#define READER_INPUT_H

#include <stdbool.h>

enum ControlType {
    CONTROL_TYPE_INVALID = 0,
    CONTROL_TYPE_ENTER,
    CONTROL_TYPE_RETURN,
    CONTROL_TYPE_CANCEL,
    CONTROL_TYPE_OPTION,
    CONTROL_TYPE_UP,
    CONTROL_TYPE_DOWN,
    CONTROL_TYPE_PUMP,
    CONTROL_TYPE_SPACE,
    CONTROL_TYPE_TICK,
};

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
