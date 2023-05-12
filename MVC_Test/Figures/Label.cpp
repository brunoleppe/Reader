//
// Created by bleppe on 08/05/23.
//

#include "Label.h"


Label::Label(int x, int y, uint8_t back, uint8_t fore, const char *str, LCD_Fonts font)
    : Figure(x, y, back, fore), font(font), s(str)
{
    h = LCD_get_font(font)->rows;
    w = s.length() * (LCD_get_font(font)->cols + 1);
}

void Label::draw() {
    LCD_draw_fill(x,y,h,w,(LCD_COLOR)backColor);
    LCD_draw_string(x,y,s.c_str(),font,(LCD_COLOR)foreColor);
}

void Label::crop_to_width(int width) {
    int erase = width/(LCD_get_font(font)->cols + 1);

    s.erase(erase);
    this->w = s.length() * (LCD_get_font(font)->cols + 1);
}

void Label::set_text(const char *str) {
    s.assign(str);
    w = s.length() * (LCD_get_font(font)->cols + 1);
}
