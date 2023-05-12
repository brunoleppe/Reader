//
// Created by bruno on 09/05/23.
//
#include "input_cpp.h"
#include "input.h"
#include "MVC/Views/ViewService.h"


void input_register(InputEventObserver* observer)
{
    ViewService::instance.attach(observer);
}
bool input_report_key(int scancode, int eventType)
{
    InputEvent evt ={
            .code = scancode,
            .value = (enum INPUT_EVENTS)eventType
    };
    ViewService::instance.set_event(evt);
    return true;
}