//
// Created by bruno on 17/05/23.
//

#include "StateInputTest1.h"
#include "debug_bsp.h"
#include "StateInputTest2.h"
#include "input.h"

Status StateInputTest1::on_event(StateEvent *evt) {
    Status status;
    switch(evt->signal){
        case EVENT_SIGNAL_ENTER: {
            status = STATUS_INIT;
            title.assign("InputTest1");
            string.assign("Mundo");
            DEBUG_PRINT("Input 1\n");
            break;
        }
        case EVENT_SIGNAL_SELECT:
            status = STATUS_HANDLED;
            if(evt->value == INPUT_EVENT_CLICKED) {
                status = STATUS_TRANSITION;
                DEBUG_PRINT("%s\n", string.c_str());
                context->transition(new StateInputTest2());
            }
            break;
        default: status = State::on_event(evt);
    }
    return status;
}
