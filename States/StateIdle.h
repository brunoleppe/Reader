//
// Created by bleppe on 05/04/23.
//

#ifndef STATE_IDLE_H
#define STATE_IDLE_H

#include "State.h"

class StateIdle : State{
public:
    static State* get_state();
private:
    static StateIdle instance;

    void on_enter() override;
    void on_exit() override;
    void on_input(InputEvent &evt) override;
};


#endif //STATE_IDLE_H
