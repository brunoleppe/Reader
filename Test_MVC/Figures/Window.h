//
// Created by bleppe on 09/05/23.
//

#ifndef LCDTEST_WINDOW_H
#define LCDTEST_WINDOW_H

#include "Composite.h"
#include "Box.h"
#include "lcd.h"

enum WindowHorAlignment{
    WindowHor_Center, WindowHor_Left, WindowHor_Right
};
enum WindowVerAlignment{
    WindowVer_Center, WindowVer_Top, WindowVer_Bottom,
};

class Window : public Composite{
public:
    Window() : Composite(0,0,LCD_WIDTH, LCD_HEIGHT), rect(x,y,w,h, LCD_COLOR_WHITE, LCD_COLOR_BLACK),
               hor(WindowHor_Center), ver(WindowVer_Center)
    {
        add(&rect);
    }

    Window(int width, int height) : Composite(0,0, width, height),
            rect(x,y,width,height, LCD_COLOR_WHITE, LCD_COLOR_BLACK) , hor(WindowHor_Center), ver(WindowVer_Center)
    {
        add(&rect);
        Composite::set_position((LCD_WIDTH>>1) - (width>>1), (LCD_HEIGHT >> 1) - (height >> 1));
    }

    Window(int width, int height, WindowHorAlignment horizontal, WindowVerAlignment vertical)
            : Composite(0, 0, width, height), rect(x,y,width,height, LCD_COLOR_WHITE, LCD_COLOR_BLACK)
            , hor(horizontal), ver(vertical)
    {
        add(&rect);

        int x0 = x, y0 = y;
        if(hor == WindowHor_Center)
            x0 = (LCD_WIDTH>>1) - (width>>1);
        else if(hor == WindowHor_Right)
            x0 = LCD_WIDTH - width;

        if(ver == WindowVer_Center)
            y0 = (LCD_HEIGHT >> 1) - (height >> 1);
        else if(ver == WindowVer_Bottom)
            y0 = LCD_HEIGHT - height;

        Composite::set_position(x0,y0);
    }
private:
    Box rect;
    WindowHorAlignment hor = WindowHor_Center;
    WindowVerAlignment ver = WindowVer_Center;

};


#endif //LCDTEST_WINDOW_H
