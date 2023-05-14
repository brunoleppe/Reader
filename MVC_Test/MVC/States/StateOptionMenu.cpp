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
    data.itemList.items.push_back(new MenuItem(0, "Hola1"));
    data.itemList.items.push_back(new MenuItem(1, "Hola2"));
    data.itemList.items.push_back(new MenuItem(2, "Hola3"));
}

bool StateOptionMenu::on_event(ControllerInputEvent &evt) {

    if(evt.event == INPUT_EVENT_CLICKED && evt.type == INPUT_EVENT_TYPE_CONTROL && evt.code == CONTROL_TYPE_ENTER) {
        context->transition(&StateMainMenu::instance);
        return true;
    }
    return false;

}

StateOptionMenu StateOptionMenu::instance;
