//
// Created by bleppe on 16/05/23.
//

#ifndef LCDTEST_TESTSTATEMACHINE_H
#define LCDTEST_TESTSTATEMACHINE_H


#include "DataTypes/Observer.h"
#include "DataTypes/StateMachine.h"
#include "MVC/ControllerInputEvent.h"

class TestStateMachine : public StateMachine, public Observer{

private:
     static StateEventSignal signals[10];

public:
    void update(Subject *subject) override{
        auto evt = (ControllerInputEvent*)subject->get_data();
        if(evt->type == INPUT_EVENT_TYPE_CONTROL){
            if(state == nullptr)
                return;
            StateEvent stateEvt = {
                    .signal = signals[evt->code],
                    .value = evt->event,
            };
            state->on_event(&stateEvt);
        }
    }
};


#endif //LCDTEST_TESTSTATEMACHINE_H
