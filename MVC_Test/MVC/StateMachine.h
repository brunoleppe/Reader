//
// Created by bleppe on 10/05/23.
//

#ifndef LCDTEST_STATEMACHINE_H
#define LCDTEST_STATEMACHINE_H

#include "ControllerInputEvent.h"

class StateMachine;

class State{
protected:
    StateMachine *context;
    friend class StateMachine;
public:
    virtual void on_enter(){};
    virtual void on_exit(){};
    virtual bool on_event(ControllerInputEvent &evt) {return false;};
    virtual ~State() = default;

};

class StateMachine{
protected:
    State *state = nullptr;
public:
    void set_state(State *next){
        next->on_enter();
        state = next;
        state->context = this;
    }
    void transition(State *next){
        state->on_exit();
        next->on_enter();
        state = next;
        state->context = this;

    }
};
#endif //LCDTEST_STATEMACHINE_H
