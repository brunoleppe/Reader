//
// Created by bleppe on 10/05/23.
//

#ifndef LCDTEST_VIEW_H
#define LCDTEST_VIEW_H


#include "Test_MVC/Figures/MenuWindow.h"
#include "Test_MVC/MVC/MessagePacket.h"
#include "input.h"
#include "Test_MVC/DataTypes/Item.h"
#include "Test_MVC/MVC/ControllerInputEvent.h"
#include "Test_MVC/DataTypes/Observer.h"
#if defined(PIC32) || defined(__PIC32) || defined(__PIC32__)
#include "virtual_term.h"
#include "linux_keys.h"
#else
#include "virtual_term.h"
#endif


class View {
public:
    virtual void draw() = 0;
    virtual ~View() = default;

    virtual void on_alpha_key(INPUT_EVENTS evt, char alpha) {};
    virtual void on_numeric_key(INPUT_EVENTS evt, char num) {};
    virtual void on_symbol_key(INPUT_EVENTS evt) {};
    virtual void on_control_key(INPUT_EVENTS evt, ControlType c){};

    void set_items(ItemList& items){
        list = &items;
    }
    void set_title(const char *str){
        title = str;
    }
    void set_options(std::vector<const char*>& _options){
        options = &_options;
    }

    virtual void update() = 0;


    void set_subject(Subject *s){
        subject = s;
    }

    void on_event(InputEvent& evt){
//        subject->set_data(&evt);
        int res;
        if((res = is_alpha(evt.code))){
            on_alpha_key((INPUT_EVENTS)evt.value, char(res));
        }
        else if((res = is_numeric(evt.code))){
            on_numeric_key((INPUT_EVENTS)evt.value, (char)res);
        }
        else if((res = is_control(evt.code))){
            on_control_key((INPUT_EVENTS)evt.value, (ControlType)res);
        }
    }

protected:
    MessagePacket *msg;
    Subject *subject;
    const char* title;
    ItemList *list;
    std::vector<const char*> *options;
};


#endif //LCDTEST_VIEW_H
