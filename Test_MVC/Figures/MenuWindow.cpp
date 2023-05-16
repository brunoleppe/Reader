//
// Created by bleppe on 09/05/23.
//

#include "MenuWindow.h"

MenuWindow::MenuWindow(const char *title) :
        titleBox(0,0,w,20,foreColor,backColor,title,LCD_FONT_SMALL, Text_Left, false),
        listBox(0,20,w,88,backColor,foreColor),
        optionBox(w,20,WindowHor_Center, WindowVer_Bottom)
{

    add(&titleBox);
    add(&optionBox);
    add(&listBox);
}

void MenuWindow::set_title(const char *title) {
    titleBox.set_text(title);
}

MenuWindow::~MenuWindow() {

}

void MenuWindow::add_items(ItemList &items) {
    listBox.add(items);
}

void MenuWindow::clear_items() {
    listBox.clear();
}

void MenuWindow::focus(int i) {
    listBox.focus(i);
}

void MenuWindow::focus_next() {
    listBox.focus_next();
}

void MenuWindow::focus_prev() {
    listBox.focus_prev();
}

bool MenuWindow::get_valid_item(int i) {
    return listBox.items->get_current()->get_index() == i;
}

void MenuWindow::select_item(int i) {
    for(auto item : listBox.items->items){
        if(item->get_index() == i){
            item->set_selected(true);
            continue;
        }
        item->set_selected(false);
    }
    (*listBox.items)[i]->set_selected(true);
}

void MenuWindow::select_item() {
    if(listBox.items->size() == 0){
        return;
    }
    for(auto item : listBox.items->items){
        item->set_selected(false);
    }
    listBox.items->get_current()->set_selected(true);
}
