//
// Created by bruno on 17/05/23.
//

#include "StateInputTest2.h"
#include "StateInputTest1.h"
#include "debug_bsp.h"
#include "input.h"

Status StateInputTest2::on_event(StateEvent *evt) {
    Status status;
    switch(evt->signal){
        case EVENT_SIGNAL_ENTER:
            status = STATUS_INIT;
            title.assign("InputTest2");
            string.assign("Hola");
            DEBUG_PRINT("Input 2\n");
            break;
        case EVENT_SIGNAL_SELECT:
            status = STATUS_HANDLED;
            if(evt->value == INPUT_EVENT_CLICKED) {
                status = STATUS_TRANSITION;
                DEBUG_PRINT("%s\n", string.c_str());
                context->transition(new StateInputTest1());
            }
            break;
        default: status = State::on_event(evt);
    }
    return status;
}
