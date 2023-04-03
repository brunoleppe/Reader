//
// Created by bleppe on 03/04/23.
//

#ifndef STATEMAINMENU_H
#define STATEMAINMENU_H

#include "State.h"

class StateMainMenu : public State{
public:
    static StateMainMenu* state();
private:

    static StateMainMenu instance;

    void on_enter() override;
    void on_exit() override;
    void on_input(InputEvent &evt) override;
};


#endif //STATEMAINMENU_H
