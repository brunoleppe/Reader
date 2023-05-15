//
// Created by bruno on 14/05/23.
//

#ifndef LCDTEST_MENUVIEW_H
#define LCDTEST_MENUVIEW_H


#include "View.h"

class MenuView : public View{
public:
    MenuView();

    void draw() override;

//    void set_title(const char *str) override;
//    void set_items(ItemList& items) override;

    void on_alpha_key(INPUT_EVENTS evt, char alpha) override;
    void on_numeric_key(INPUT_EVENTS evt, char num) override;
    void on_symbol_key(INPUT_EVENTS evt) override;
    void on_control_key(INPUT_EVENTS evt, ControlType c) override;

    void update() override;

    static MenuView instance;
private:
    MenuWindow window;
};


#endif //LCDTEST_MENUVIEW_H
