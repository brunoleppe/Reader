//
// Created by bleppe on 19/5/2023.
//

#ifndef LCDTEST_VIEWMODEL_H
#define LCDTEST_VIEWMODEL_H


#include "MVC/States/StateMachine.h"

class ViewModel {
protected:
    ViewModel(State *s) : state(s){}
    State *state;
public:
    virtual ~ViewModel() = default;
    void set_state(State *s){
        state = s;
    }
};


#endif //LCDTEST_VIEWMODEL_H
