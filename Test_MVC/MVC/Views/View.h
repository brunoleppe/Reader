//
// Created by bleppe on 10/05/23.
//

#ifndef LCDTEST_VIEW_H
#define LCDTEST_VIEW_H


#include "Test_MVC/DataTypes/ControllerInputEvent.h"
#include "MVC/ViewModels/ViewModel.h"
#include "lcd.h"


class View {
protected:
    View(ViewModel *viewModel) : vm(viewModel){}
    ViewModel* vm;
public:

    virtual void draw(){}

    virtual ~View(){
        delete vm;
    }
    ViewModel* get_viewModel(){
        return vm;
    }
    virtual bool set_input(ControllerInputEvent& evt) = 0;
};


#endif //LCDTEST_VIEW_H
