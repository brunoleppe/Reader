//
// Created by bruno on 14/05/23.
//

#include "LogoView.h"

void LogoView::draw() {
    LCD_draw_bitmap(0,0,item->bitmap, item->height * item->width);
}

void LogoView::set_items(ItemList &items) {
    item = (LogoItem*)items.items.front();
}

void LogoView::on_control_key(INPUT_EVENTS evt, ControlType c) {
    subject->notify();
}

LogoView LogoView::instance;