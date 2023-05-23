//
// Created by bleppe on 17/05/23.
//

#ifndef LCDTEST_STATEMENU_H
#define LCDTEST_STATEMENU_H


#include "StateMachine.h"
#include "DataTypes/vector.h"


class StateMenu : public State{
protected:
    bru::vector<const char *> items;
    int index;
    StateMenu() : index(0){
        type = STATE_TYPE_MENU;
    }
public:
    bru::vector<const char *>* get_items(){
        return &items;
    }

    void set_index(int i){
        index = i;
    }
};


#endif //LCDTEST_STATEMENU_H
