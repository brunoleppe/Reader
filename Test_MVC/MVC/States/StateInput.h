//
// Created by bruno on 17/05/23.
//

#ifndef LCDTEST_STATEINPUT_H
#define LCDTEST_STATEINPUT_H


#include "StateMachine.h"
#include "DataTypes/string.h"

class StateInput : public State{
protected:
    bru::string string;
    bru::string title;
    StateInput(){
        type = STATE_TYPE_INPUT;
    }
public:
    bru::string* get_string(){
        return &string;
    }
    bru::string* get_title(){
        return &title;
    }
};


#endif //LCDTEST_STATEINPUT_H
