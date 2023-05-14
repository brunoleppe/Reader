//
// Created by bleppe on 09/05/23.
//

#ifndef LCDTEST_MENUWINDOW_H
#define LCDTEST_MENUWINDOW_H

#include "Window.h"
#include "TextBox.h"
#include "ItemBox.h"

class MenuWindow : public Window {
public:
    explicit MenuWindow(const char *title);
    void set_title(const char *title);

    ~MenuWindow() override;

    void add_items(ItemList &items);
    void clear_items();

    void focus(int i);
    void focus_next();
    void focus_prev();

private:
    TextBox titleBox;
    ListItemBox listBox;
    Window optionBox;
};


#endif //LCDTEST_MENUWINDOW_H
