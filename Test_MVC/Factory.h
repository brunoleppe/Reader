//
// Created by bruno on 20/05/23.
//

#ifndef LCDTEST_FACTORY_H
#define LCDTEST_FACTORY_H


#include "MVC/States/StateMachine.h"
#include "Test/Views/LogoViewTest.h"
#include "Test/Views/InputViewTest.h"
#include "MVC/Views/LogoView.h"
#include "MVC/Views/InputView.h"

class Factory {
private:
    Factory() = default;
public:
    static View* create(State* state){
        View* view = nullptr;
        switch (state->get_type()) {
            case STATE_TYPE_BASE:
                view = nullptr;
                break;
            case STATE_TYPE_LOGO:
            {
                auto model = new LogoViewModel((StateLogo*)state);
                view = new LogoView(model);
            }
                break;
            case STATE_TYPE_MENU:
                break;
            case STATE_TYPE_INPUT:
            {
                auto model = new InputViewModel((StateInput*)state);
                view = new InputView(model);
            }
                break;
            case STATE_TYPE_DATA:
                break;
            case STATE_TYPE_NETCONFIG:
                break;
        }
        return view;
    }
};


#endif //LCDTEST_FACTORY_H
