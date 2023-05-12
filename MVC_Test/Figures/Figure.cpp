//
// Created by bleppe on 08/05/23.
//

#include "Figure.h"

Figure::Figure(int x, int y, uint8_t back, uint8_t fore)
        : Drawable(x,y,0,0,back,fore)
{

}
Figure::Figure(int x, int y, int width, int height, uint8_t back, uint8_t fore)
        : Drawable(x,y,width,height,back,fore)
{

}

void Figure::set_position(int x_, int y_) {
    this->x = x_;
    this->y = y_;
}

Position Figure::get_position() {
    return {x,y};
}

Size Figure::get_size() {
    return {w, h};
}

void Figure::invert_colors() {
    backColor = LCD_invert_color(static_cast<LCD_COLOR>(backColor));
    foreColor = LCD_invert_color(static_cast<LCD_COLOR>(foreColor));
}

Figure::~Figure() = default;
