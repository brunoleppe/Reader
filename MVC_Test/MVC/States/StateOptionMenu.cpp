//
// Created by bleppe on 10/05/23.
//
#include "StateMainMenu.h"
#include "StateOptionMenu.h"
#include "MVC/ControllerInputEvent.h"
#include "input.h"
#include "DataTypes/LabelItem.h"

StateOptionMenu::StateOptionMenu()
{
    data.title = "Option Menu";

}

bool StateOptionMenu::on_event(ControllerInputEvent &evt) {

    if(evt.event == INPUT_EVENT_CLICKED && evt.type == INPUT_EVENT_TYPE_CONTROL && evt.code == CONTROL_TYPE_ENTER) {
        context->transition(&StateMainMenu::instance);
        return true;
    }
    return false;

}

void StateOptionMenu::on_exit() {
    data.items.clear();
}

void StateOptionMenu::on_enter() {
    data.items.add(new LabelItem(0, "Hola1"));
    data.items.add(new LabelItem(1, "Hola2"));
    data.items.add(new LabelItem(2, "Hola3"));
}

StateOptionMenu StateOptionMenu::instance;
