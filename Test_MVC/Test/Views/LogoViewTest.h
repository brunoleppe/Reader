//
// Created by bleppe on 19/5/2023.
//

#ifndef LCDTEST_LOGOVIEWTEST_H
#define LCDTEST_LOGOVIEWTEST_H


#include "MVC/ViewModels/LogoViewModel.h"
#include "Test_MVC/DataTypes/ControllerInputEvent.h"
#include "debug_bsp.h"
#include "MVC/Views/View.h"

class LogoViewTest : public View{
private:
    Bitmap* bmp;
public:
    explicit LogoViewTest(LogoViewModel *viewModel) : View(viewModel) {
        bmp = viewModel->get_bitmap();
        DEBUG_PRINT("%d, %d", bmp->height, bmp->width);
    }
    bool set_input(ControllerInputEvent& evt) override{
        return false;
    }

    static LogoViewTest instance;
};


#endif //LCDTEST_LOGOVIEWTEST_H
