//
// Created by bruno on 09/05/23.
//
#include "input_cpp.h"
#include "Test_MVC/InputController.h"


void input_register(Observer* observer)
{
    InputController::instance.attach(observer);
}
bool input_report_key(int scancode, int eventType)
{
    InputEvent evt ={
            .code = scancode,
            .value = (enum INPUT_EVENTS)eventType
    };
    InputController::instance.set_data(&evt);
    return true;
}