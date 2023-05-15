//
// Created by bleppe on 09/05/23.
//

#ifndef LCDTEST_DRAWABLE_H
#define LCDTEST_DRAWABLE_H

#include "lcd.h"

struct Size{
    int width;
    int height;
    Size(int w, int h){
        width = w;
        height = h;
    }
};

struct Position{
    int x;
    int y;
};

class Drawable {
public:
    virtual void draw() = 0;
    virtual void set_position(int _x, int _y){
        this->x = _x;
        this->y = _y;
    }
    Position get_position(){
        return {x,y};
    }
    Size get_size(){
        return {w,h};
    }
    virtual void invert_colors(){
        backColor = LCD_invert_color(static_cast<LCD_COLOR>(backColor));
        foreColor = LCD_invert_color(static_cast<LCD_COLOR>(foreColor));
    };
    virtual ~Drawable() = default;



protected:
    int x,y,w,h;
    uint8_t backColor;
    uint8_t foreColor;

    Drawable(int x, int y, int w, int h, uint8_t backcolor, uint8_t forecolor)
    : x(x), y(y), w(w), h(h), backColor(backcolor), foreColor(forecolor)
    {
    }

};


#endif //LCDTEST_DRAWABLE_H
