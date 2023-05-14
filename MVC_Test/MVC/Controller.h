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
#else
#include <queue>
#endif

class Controller : public InputEventObserver{
public:

    Controller(ModelStateService* s, ViewService* v);

    void Stop();

    void update() override;
    static
#if defined(PIC32) || defined(__PIC32) || defined(__PIC32__)
    void
#else
    int
#endif
    controller_task(void *data);

private:
    ModelStateService *model;
    ViewService *view;
#if defined(PIC32) || defined(__PIC32) || defined(__PIC32__)
    QueueHandle_t queue;
#else
    std::queue<InputEvent> queue;
#endif

    bool running;
};


#endif //LCDTEST_CONTROLLER_H
