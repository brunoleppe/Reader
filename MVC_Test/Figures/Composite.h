//
// Created by bleppe on 09/05/23.
//

#ifndef LCDTEST_COMPOSITE_H
#define LCDTEST_COMPOSITE_H

#include <vector>
#include "Figure.h"

class Composite : public Drawable{
public:
    void add(Drawable *drawable){
        drawables.push_back(drawable);
    }

    void draw() override {
        for(auto& d : drawables)
            d->draw();
    }

    void set_position(int x_, int y_) override {
        for(auto& d : drawables)
            d->set_position(x_,y_);
    }

    Position get_position() override {
        return {x,y};
    }

    Size get_size() override {
        return {w,h};
    }

    void invert_colors() override {
        for(auto& d : drawables)
            d->invert_colors();
    }

protected:
    std::vector<Drawable*> drawables;
    Composite() : Drawable(0,0,0,0,LCD_COLOR_WHITE, LCD_COLOR_BLACK)
    {
    }

    Composite(int x, int y, int w, int h) : Drawable(x,y,w,h,LCD_COLOR_WHITE, LCD_COLOR_BLACK)
    {}
};


#endif //LCDTEST_COMPOSITE_H
