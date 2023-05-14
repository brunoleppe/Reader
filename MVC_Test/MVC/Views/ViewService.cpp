//
// Created by bleppe on 12/05/23.
//

#include "ViewService.h"

void ViewService::set_message(MessagePacket *m) {
    if(m->messageType == MESSAGE_TYPE_MENU) {
        MenuView::instance.set_title(m->title);
        MenuView::instance.set_items(m->itemList);
        v = &MenuView::instance;
        v->set_subject(&subject);
    }
}

ViewService::ViewService() : mss(nullptr){
    v = &MenuView::instance;
#if defined(PIC32) || defined(__PIC32) || defined(__PIC32__)
    queue = xQueueCreate(5,sizeof(InputEvent));
    xTaskCreate(ViewService::task, "view_task", 1024, nullptr, 2, nullptr);
#endif
}

void ViewService::update() {
    v->draw();
}

ViewService ViewService::instance;

void ViewService::set_event(InputEvent &evt) {
//    v->on_event(evt);
#if defined(PIC32) || defined(__PIC32) || defined(__PIC32__)
    xQueueSend(queue, &evt, portMAX_DELAY);
#else
    queue.push(evt);
#endif
}

void ViewService::attach(InputEventObserver *observer) {
    observer->inputSubject = &subject;
    subject.attach(observer);
}

void ViewService::task(void *) {
    ViewService* vs = &ViewService::instance;
    LCD_configure();
    InputEvent evt;


#if defined(PIC32) || defined(__PIC32) || defined(__PIC32__)
    while(true){
        if(xQueueReceive(vs->queue, &evt, 10)){
            vs->v->on_event(evt);
        }
        LCD_print();
        vTaskDelay(17);
    }
#else
    while(vs->running) {
        if(!vs->queue.empty()){
            evt = vs->queue.front();
            vs->queue.pop();
            vs->v->on_event(evt);
        }
        LCD_print();
        SDL_Delay(17);
    }
    printf("Finalizado\n");
#endif
}


#if defined(PIC32) || defined(__PIC32) || defined(__PIC32__)

#else
void ViewService::start() {
    thread =  SDL_CreateThread((int (*)(void *))ViewService::task, "view_task", nullptr);
}

void ViewService::stop() {
    running = false;
    SDL_WaitThread(thread, nullptr);
}

#endif

