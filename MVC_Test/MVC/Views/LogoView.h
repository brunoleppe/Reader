//
// Created by bruno on 14/05/23.
//

#ifndef LCDTEST_LOGOVIEW_H
#define LCDTEST_LOGOVIEW_H


#include "View.h"
#include "DataTypes/LogoItem.h"

class LogoView : public View {
public:
    LogoView();

    void draw() override;
//    void set_items(ItemList &items) override;
    void on_control_key(INPUT_EVENTS evt, ControlType c) override;

void update() override;
    LogoItem* item;
    static LogoView instance;
};


#endif //LCDTEST_LOGOVIEW_H
