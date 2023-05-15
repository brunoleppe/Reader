//
// Created by bruno on 14/05/23.
//

#include "MenuView.h"

MenuView::MenuView() : window("")
{

}

void MenuView::draw() {
    window.draw();
}

//void MenuView::set_title(const char *str) {
//    window.set_title(str);
//}
//
//void MenuView::set_items(ItemList &items) {
//    window.add_items(items);
//}

void MenuView::on_alpha_key(INPUT_EVENTS evt, char alpha) {
    (void)evt;

}

void MenuView::on_numeric_key(INPUT_EVENTS evt, char num) {
    int index = num-'0' - 1;
    if(evt == INPUT_EVENT_PRESSED) {
        window.focus(index);
    }
    else if(evt == INPUT_EVENT_CLICKED){
        InputEvent  i = {
#if defined(PIC32) || defined(__PIC32) || defined(__PIC32__)
                .code = KEY_ENTER,
#else
                .code = SDL_SCANCODE_RETURN,
#endif
                .value = evt,
        };
        if(window.get_valid_item(index)) {
            window.select_item(index);
            subject->set_data(i);
            subject->notify();
        }

    }
    draw();

}

void MenuView::on_symbol_key(INPUT_EVENTS evt) {
    (void)evt;
}

void MenuView::on_control_key(INPUT_EVENTS evt, ControlType c) {
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
    else if(c == CONTROL_TYPE_ENTER && evt == INPUT_EVENT_PRESSED){
        window.select_item();
    }
    else {
        subject->notify();
    }
}

void MenuView::update() {
    window.set_title(title);
    window.add_items(*list);
}

MenuView MenuView::instance;
