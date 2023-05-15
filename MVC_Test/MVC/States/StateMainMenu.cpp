//
// Created by bleppe on 10/05/23.
//

#include "StateMainMenu.h"
#include "StateOptionMenu.h"
#include "MVC/ControllerInputEvent.h"
#include "input.h"
#include "DataTypes/Item.h"
#include "DataTypes/LabelItem.h"
#if !defined(PIC32) && !defined(__PIC32) && !defined(__PIC32__)
#include <cstdint>
#endif

StateMainMenu::StateMainMenu()
{

}




bool StateMainMenu::on_event(ControllerInputEvent &evt) {

    if(evt.event == INPUT_EVENT_CLICKED && evt.code == CONTROL_TYPE_ENTER) {
        auto item = (LabelItem*)data.items.get_selected();
        if(item != nullptr){
#if !defined(PIC32) && !defined(__PIC32) && !defined(__PIC32__)
            printf("Item: %s, %d\n", item->get_cstring(), item->get_index());
#endif
        }
        context->transition(&StateOptionMenu::instance);
        return true;
    }
    else if(evt.event == INPUT_EVENT_CLICKED && evt.code == CONTROL_TYPE_RETURN) {
        data.items.add(new LabelItem((int)data.items.size(), "test"));
        return true;
    }
    return false;
}

void StateMainMenu::on_enter() {

    const char *items[] = {
            "1. item1",
            "2. item2",
    };
    data.title = "Main Menu";
    for(int i=0;i<(int)(sizeof(items)/sizeof(items[0]));i++){
        data.items.add(new LabelItem(i, items[i]));
    }

#if !defined(PIC32) && !defined(__PIC32) && !defined(__PIC32__)
    printf("On enter\n");
#endif
}

void StateMainMenu::on_exit() {
#if !defined(PIC32) && !defined(__PIC32) && !defined(__PIC32__)
    printf("On exit\n");
#endif
    data.items.clear();
}

StateMainMenu StateMainMenu::instance;
