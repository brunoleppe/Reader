//
// Created by bruno on 14/05/23.
//

#ifndef LCDTEST_STATELOGOSCREEN_H
#define LCDTEST_STATELOGOSCREEN_H


#include "MVC/Model.h"
#if defined(PIC32) || defined(__PIC32) || defined(__PIC32__)
#include "FreeRTOS.h"
#include "timers.h"
#else
#include <SDL_thread.h>
#endif

class StateLogoScreen : public Model{
public:
    StateLogoScreen();
    bool on_event(ControllerInputEvent &evt) override;
    static StateLogoScreen instance;
    void on_enter() override;
    void on_exit() override;

    bool running;
    static int task(void *data);



#if defined(PIC32) || defined(__PIC32) || defined(__PIC32__)
    TimerHandle_t timer;
#else
    SDL_Thread* thread;
#endif
private:
#if defined(PIC32) || defined(__PIC32) || defined(__PIC32__)
    bool flag;
    static void TimerCallback(TimerHandle_t timer);
    uint8_t *buffer;
#endif

};


#endif //LCDTEST_STATELOGOSCREEN_H
