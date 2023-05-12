//
// Created by bruno on 09/05/23.
//

#ifndef LCDTEST_CONTROLLER_H
#define LCDTEST_CONTROLLER_H


#include "Input/input_cpp.h"
#include "Model.h"
#include "ModelStateService.h"
#include "MVC/Views/ViewService.h"
#if defined(PIC32) || defined(__PIC32) || defined(__PIC32__)

#include "FreeRTOS.h"
#include "queue.h"
#endif

class Controller : public InputEventObserver{
public:

    Controller(ModelStateService* s, ViewService* v);

    void Stop();

    void update() override;
    static void controller_task(void *data);

private:
    ModelStateService *model;
    ViewService *view;
#if defined(PIC32) || defined(__PIC32) || defined(__PIC32__)
    QueueHandle_t queue;
#endif

    bool running;
};


#endif //LCDTEST_CONTROLLER_H
