//
// Created by bleppe on 11/05/23.
//

#ifndef LCDTEST_VIEWSERVICE_H
#define LCDTEST_VIEWSERVICE_H

#include "View.h"
#include "MVC/MessagePacket.h"
#include "MVC/ControllerInputEvent.h"
#include "DataTypes/Observer.h"
#if defined(PIC32) || defined(__PIC32) || defined(__PIC32__)
#include "FreeRTOS.h"
#include "queue.h"
#else
#include <queue>
#include <cstdio>
#endif

class ViewService{
private:
    View *v;
    MessagePacket *mss = nullptr;
    ViewService();
    Subject<InputEvent> subject;

    static void task(void *);
#if defined(PIC32) || defined(__PIC32) || defined(__PIC32__)
    QueueHandle_t queue;
#else
    std::queue<InputEvent> queue;
    bool running = true;
    SDL_Thread* thread;
#endif
public:

    static ViewService instance;

    void update();
    void set_message(MessagePacket *m);
    void set_event(InputEvent& evt);
    void attach(InputEventObserver* observer);



#if !defined(PIC32) && !defined(__PIC32) && !defined(__PIC32__)
    void start();
    void stop();
#endif
};


#endif //LCDTEST_VIEWSERVICE_H
