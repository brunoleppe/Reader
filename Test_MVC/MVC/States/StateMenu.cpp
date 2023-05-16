//
// Created by bleppe on 16/05/23.
//
#include "StateMenu.h"
#include "input.h"
#include "debug_bsp.h"
#include "StateItems.h"

#if !defined(PIC32) && !defined(__PIC32) && !defined(__PIC32__)
#include <cstdio>
#endif

Status StateMenu::on_event(StateEvent *evt) {
    Status status;
    switch(evt->signal){
        case EVENT_SIGNAL_ENTER:
            DEBUG_PRINT("On Enter StateMenu\n");
            status = STATUS_INIT;
            break;
        case EVENT_SIGNAL_EXIT:
            DEBUG_PRINT("On Exit StateMenu\n");
            status = STATUS_HANDLED;
            break;
        case EVENT_SIGNAL_SELECT:{
            DEBUG_PRINT("StateMenu On Select: %d\n", evt->value);
            if(evt->value == INPUT_EVENT_CLICKED)
                context->transition(new StateItems());
            status = STATUS_HANDLED;
            break;
        }
        default:
            DEBUG_PRINT("Ignored Event: %d\n", evt->signal);
            status = State::on_event(evt);
    }
    return status;
}
