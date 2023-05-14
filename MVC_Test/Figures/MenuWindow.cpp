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
