//
// Created by bleppe on 11/05/23.
//

#ifndef LCDTEST_VIEWSERVICE_H
#define LCDTEST_VIEWSERVICE_H

#include "View.h"
#include "Test_MVC/MVC/MessagePacket.h"
#include "Test_MVC/MVC/ControllerInputEvent.h"
#include "Test_MVC/DataTypes/Observer.h"
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
    Subject subject;

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
    void attach(Observer* observer);



#if !defined(PIC32) && !defined(__PIC32) && !defined(__PIC32__)
    void start();
    void stop();
#endif
};


#endif //LCDTEST_VIEWSERVICE_H
