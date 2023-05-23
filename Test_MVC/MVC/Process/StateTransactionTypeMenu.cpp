//
// Created by bleppe on 17/05/23.
//

#include "StateTransactionTypeMenu.h"
#include "debug_bsp.h"
#include "StateMainLogo.h"

StateTransactionTypeMenu::StateTransactionTypeMenu() {
    items.push_back("item1");
    items.push_back("item2");
    items.push_back("item3");
    items.push_back("item4");
}

Status StateTransactionTypeMenu::on_event(StateEvent *evt) {
    Status status;
    switch(evt->signal){
        case EVENT_SIGNAL_ENTER:
            status = STATUS_HANDLED;
            for(auto item : items){
                DEBUG_PRINT("%s\n",item);
            }
            break;
        case EVENT_SIGNAL_RETURN:
            status = STATUS_HANDLED;
            context->transition(new StateMainLogo());
            break;
        default: status = State::on_event(evt);
    }
    return status;
}
