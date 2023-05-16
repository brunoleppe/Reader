#include "StateTest.h"
#include "StateMenu.h"
#include "input.h"
#include <cstdio>

//
// Created by bleppe on 16/05/23.
//
Status StateTest::on_event(StateEvent *evt) {
    Status status;
    switch(evt->signal){
        case EVENT_SIGNAL_ENTER:
            printf("On Enter StateTest\n");
            status = STATUS_INIT;
            break;
        case EVENT_SIGNAL_EXIT:
            printf("On Exit StateTest\n");
            status = STATUS_HANDLED;
            break;
        case EVENT_SIGNAL_SELECT:
            printf("StateTest On Select: %d\n", evt->value);
            if(evt->value == INPUT_EVENT_CLICKED)
                context->transition(new StateMenu());
            status = STATUS_TRANSITION;
            break;
        default:
            printf("Ignored Event: %d\n", evt->signal);
            status = State::on_event(evt);
    }
    return status;
}
