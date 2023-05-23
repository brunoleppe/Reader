//
// Created by bleppe on 17/05/23.
//

#ifndef LCDTEST_STATETRANSACTIONTYPEMENU_H
#define LCDTEST_STATETRANSACTIONTYPEMENU_H


#include "MVC/States/StateMenu.h"

class StateTransactionTypeMenu : public StateMenu {
public:
    StateTransactionTypeMenu();
    Status on_event(StateEvent *evt) override;
};


#endif //LCDTEST_STATETRANSACTIONTYPEMENU_H
