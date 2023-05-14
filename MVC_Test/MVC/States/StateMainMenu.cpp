//
// Created by bleppe on 10/05/23.
//

#include "StateMainMenu.h"
#include "StateOptionMenu.h"
#include "MVC/ControllerInputEvent.h"
#include "input.h"
#include "DataTypes/Item.h"

StateMainMenu::StateMainMenu()
{
    const char *items[] = {
            "item1",
            "item2",
    };
    data.title = "Main Menu";
    for(int i=0;i<(int)(sizeof(items)/sizeof(items[0]));i++){
        data.itemList.items.push_back(new MenuItem(i, items[i]));
    }
}

bool StateMainMenu::on_event(ControllerInputEvent &evt) {

    if(evt.event == INPUT_EVENT_CLICKED && evt.type == INPUT_EVENT_TYPE_CONTROL && evt.code == CONTROL_TYPE_ENTER) {
        context->transition(&StateOptionMenu::instance);
        return true;
    }
    else if(evt.event == INPUT_EVENT_CLICKED && evt.type == INPUT_EVENT_TYPE_CONTROL && evt.code == CONTROL_TYPE_RETURN) {
        data.itemList.items.push_back(new MenuItem((int)data.itemList.items.size(), "test"));
        return true;
    }
    return false;
}

StateMainMenu StateMainMenu::instance;
