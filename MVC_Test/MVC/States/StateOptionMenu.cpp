//
// Created by bleppe on 10/05/23.
//
#include "StateMainMenu.h"
#include "StateOptionMenu.h"
#include "MVC/ControllerInputEvent.h"
#include "input.h"

StateOptionMenu::StateOptionMenu()
{
    data.title = "Option Menu";
    data.items.push_back(new ListItem(0,"Hola1"));
    data.items.push_back(new ListItem(1,"Hola2"));
    data.items.push_back(new ListItem(2,"Hola3"));
}

bool StateOptionMenu::on_event(ControllerInputEvent &evt) {

    if(evt.event == INPUT_EVENT_CLICKED) {
        context->transition(&StateMainMenu::instance);
        return true;
    }
    return false;

}

StateOptionMenu StateOptionMenu::instance;
