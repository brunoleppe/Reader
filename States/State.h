//
// Created by bleppe on 03/04/23.
//

#ifndef READER_STATE_H
#define READER_STATE_H

#include "input.h"

class StateMachine;

class State {
public:

protected:
    State *prev;
    StateMachine *machine;

    virtual void on_enter();
    virtual void on_exit();
    virtual void on_input(InputEvent &evt);
    friend StateMachine;

};

class StateMachine{
public:
    void initialize(State *state);
    void transition(State *State);
    void get_back();
    void on_input(InputEvent &evt);
private:
    State *current;
};

#endif //READER_STATE_H
