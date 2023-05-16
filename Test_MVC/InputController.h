//
// Created by bleppe on 16/05/23.
//

#ifndef LCDTEST_INPUTCONTROLLER_H
#define LCDTEST_INPUTCONTROLLER_H


#include "DataTypes/Observer.h"
#include "MVC/ControllerInputEvent.h"
#include "virtual_term.h"

class InputController : public Subject {
public:
    static InputController instance;

    void set_data(void* d){
        auto evt = (InputEvent*)d;
        ControllerInputEvent cEvt = {.event = (INPUT_EVENTS)evt->value};
        int res = 0;
        if((res = is_control(evt->code)))
            cEvt.type = INPUT_EVENT_TYPE_CONTROL;
        else if((res = is_alpha(evt->code))){
            cEvt.type = INPUT_EVENT_TYPE_ALPHA;
        }
        else if((res = is_numeric(evt->code))){
            cEvt.type = INPUT_EVENT_TYPE_NUMERIC;
        }
        else if((res = is_symbol(evt->code))){
            cEvt.type = INPUT_EVENT_TYPE_SYMBOL;
        }
        cEvt.code = res;

        data = &cEvt;
        notify();
    }
};


#endif //LCDTEST_INPUTCONTROLLER_H
