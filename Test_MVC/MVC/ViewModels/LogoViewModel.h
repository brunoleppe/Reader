//
// Created by bleppe on 19/5/2023.
//

#ifndef LCDTEST_LOGOVIEWMODEL_H
#define LCDTEST_LOGOVIEWMODEL_H


#include "ViewModel.h"
#include "MVC/States/StateLogo.h"
#include "DataTypes/Bitmap.h"

class LogoViewModel : public ViewModel {
private:
    Bitmap bmp;
public:
    explicit LogoViewModel(StateLogo *state) : ViewModel(state) {}
    Bitmap* get_bitmap(){
        bmp.bitmap = ((StateLogo*)state)->get_bitmap();
        bmp.height = 128;
        bmp.width = 240;
        return &bmp;
    }

};


#endif //LCDTEST_LOGOVIEWMODEL_H
