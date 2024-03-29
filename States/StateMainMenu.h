//
// Created by bleppe on 03/04/23.
//

#ifndef STATE_MAIN_MENU_H
#define STATE_MAIN_MENU_H

#include "State.h"

class StateMainMenu : public State{
public:
    static State* get_state();
private:

    static StateMainMenu instance;

    void on_enter() override;
    void on_exit() override;
    void on_input(InputEvent &evt) override;
};


#endif //STATE_MAIN_MENU_H
