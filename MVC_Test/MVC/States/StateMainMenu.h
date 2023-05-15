//
// Created by bleppe on 10/05/23.
//

#ifndef LCDTEST_STATEMAINMENU_H
#define LCDTEST_STATEMAINMENU_H

#include "MVC/Model.h"
#include "MVC/ControllerInputEvent.h"


class StateMainMenu : public Model{
public:
    StateMainMenu();
    bool on_event(ControllerInputEvent &evt) override;
    void on_enter() override;
    void on_exit() override;

    static StateMainMenu instance;
};


#endif //LCDTEST_STATEMAINMENU_H
