//
// Created by bruno on 21/05/23.
//

#ifndef LCDTEST_LOGOVIEW_H
#define LCDTEST_LOGOVIEW_H


#include "View.h"
#include "DataTypes/Bitmap.h"
#include "MVC/ViewModels/LogoViewModel.h"
#include "debug_bsp.h"

class LogoView : public View{
private:
    Bitmap* bmp;
public:
    explicit LogoView(LogoViewModel *viewModel) : View(viewModel), bmp() {}

    bool set_input(ControllerInputEvent &evt) override{
        return false;
    }

    void draw() override{
        bmp = ((LogoViewModel*)vm)->get_bitmap();
        LCD_draw_bitmap(0,0,bmp->width,bmp->height,bmp->bitmap);
    }
};


#endif //LCDTEST_LOGOVIEW_H
