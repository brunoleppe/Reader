//
// Created by bleppe on 11/05/23.
//

#ifndef LCDTEST_CONTROLLERINPUTEVENT_H
#define LCDTEST_CONTROLLERINPUTEVENT_H

#include "input.h"

enum InputEventType {
    INPUT_EVENT_TYPE_ALPHA = 0,
    INPUT_EVENT_TYPE_NUMERIC,
    INPUT_EVENT_TYPE_SYMBOL,
    INPUT_EVENT_TYPE_CONTROL,
};

struct ControllerInputEvent {
    InputEventType type;
    int code;
    INPUT_EVENTS event;
};


#endif //LCDTEST_CONTROLLERINPUTEVENT_H
