//
// Created by bruno on 17/05/23.
//

#ifndef LCDTEST_INPUTVIEWTEST_H
#define LCDTEST_INPUTVIEWTEST_H


#include "MVC/ViewModels/InputViewModel.h"
#include "Test_MVC/DataTypes/ControllerInputEvent.h"
#include "debug_bsp.h"
#include "MVC/Views/View.h"


class InputViewTest : public View{
private:
    InputViewModel* viewModel;
public:
    explicit InputViewTest(InputViewModel *viewModel) : View(viewModel), viewModel(viewModel){}

    bool set_input(ControllerInputEvent& evt) override{
        if(evt.type == INPUT_EVENT_TYPE_ALPHA && evt.event == INPUT_EVENT_PRESSED){
            viewModel->add_char((char)evt.code);
            ERROR_PRINT("%c",(char)evt.code);
            return true;
        }
        else if(evt.type == INPUT_EVENT_TYPE_CONTROL){
            if(evt.code == CONTROL_TYPE_RETURN && evt.event == INPUT_EVENT_PRESSED){
                viewModel->delete_char();
                return true;
            }
            else if(evt.code == CONTROL_TYPE_SPACE && evt.event == INPUT_EVENT_PRESSED){
                viewModel->add_char(' ');
                ERROR_PRINT("%c", ' ');
                return true;
            }
        }
        return false;
    }
    static InputViewTest instance;
};


#endif //LCDTEST_INPUTVIEWTEST_H
