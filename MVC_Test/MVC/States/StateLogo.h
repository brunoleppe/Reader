//
// Created by bleppe on 15/05/23.
//

#ifndef READER_STATELOGO_H
#define READER_STATELOGO_H


#include "MVC/Model.h"
#include "FreeRTOS.h"
#include "timers.h"

class StateLogo : public Model{

public:
    StateLogo();
    bool on_event(ControllerInputEvent &evt) override;
    void on_enter() override;
    void on_exit() override;
    static StateLogo instance;
    uint8_t *bmp{};
    TimerHandle_t timer{};

    static void timer_callback(TimerHandle_t timer);
};


#endif //READER_STATELOGO_H
