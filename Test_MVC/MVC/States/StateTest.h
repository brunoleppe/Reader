//
// Created by bleppe on 16/05/23.
//

#ifndef LCDTEST_STATETEST_H
#define LCDTEST_STATETEST_H


#include "Test_MVC/DataTypes/StateMachine.h"

class StateTest : public State{
public:
    Status on_event(StateEvent *evt) override;


};


#endif //LCDTEST_STATETEST_H
