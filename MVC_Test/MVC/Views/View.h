//
// Created by bleppe on 10/05/23.
//

#ifndef LCDTEST_VIEW_H
#define LCDTEST_VIEW_H


#include "Figures/MenuWindow.h"
#include "MVC/MessagePacket.h"
#include "input.h"
#include "DataTypes/Item.h"
#include "MVC/ControllerInputEvent.h"
#include "DataTypes/Observer.h"
#include "virtual_term.h"
#include "linux_keys.h"

class View {
public:
    virtual void draw() = 0;
    virtual ~View() = default;

    virtual void on_alpha_key(INPUT_EVENTS evt, char alpha) = 0;
    virtual void on_numeric_key(INPUT_EVENTS evt, char num) = 0;
    virtual void on_symbol_key(INPUT_EVENTS evt) = 0;
    virtual void on_control_key(INPUT_EVENTS evt, ControlType c)=0;

    virtual void clean() = 0;

    void set_message(MessagePacket *msg);

    void set_subject(Subject<InputEvent> *s){
        subject = s;
    }

    void on_event(InputEvent& evt){
        subject->set_data(evt);
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
    Subject<InputEvent> *subject;
};

class MenuView : public View{
public:
    MenuView() : window("")
    {

    }

    void draw() override {
        window.draw();
    }

    void set_title(const char *str){
        window.set_title(str);
    }
    void set_items(std::vector<Item*>& items){
        window.add_item(items);


    }

    void clean() override {
        window.clear_items();
    }

    void on_alpha_key(INPUT_EVENTS evt, char alpha) override {
        (void)evt;

    }

    void on_numeric_key(INPUT_EVENTS evt, char num) override {
        if(evt == INPUT_EVENT_PRESSED) {
            window.focus(num - '0');
        }
        else if(evt == INPUT_EVENT_CLICKED){
            InputEvent  i = {
                    .code = KEY_ENTER,
                    .value = evt,
            };
            subject->set_data(i);
            subject->notify();
        }
        draw();

    }

    void on_symbol_key(INPUT_EVENTS evt) override {
        (void)evt;
    }

    void on_control_key(INPUT_EVENTS evt, ControlType c) override {
        if(c == CONTROL_TYPE_DOWN && evt == INPUT_EVENT_PRESSED){
            window.focus_next();
            draw();
            return;
        }
        else if(c == CONTROL_TYPE_UP && evt == INPUT_EVENT_PRESSED){
            window.focus_prev();
            draw();
            return;
        }
        else {
            subject->notify();
        }
    }


    static MenuView instance;
private:
    MenuWindow window;
};


#endif //LCDTEST_VIEW_H
