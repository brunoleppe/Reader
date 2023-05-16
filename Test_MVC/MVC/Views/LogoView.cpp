//
// Created by bruno on 14/05/23.
//

#include <cstring>
#include "LogoView.h"

void LogoView::draw() {
    LCD_draw_bitmap(item->x,item->y,item->width,item->height,item->bitmap);
}

void LogoView::on_control_key(INPUT_EVENTS evt, ControlType c) {
    subject->notify();
}

void LogoView::update() {
    item = (LogoItem*)list->items.front();
}

LogoView::LogoView() {

}

LogoView LogoView::instance;