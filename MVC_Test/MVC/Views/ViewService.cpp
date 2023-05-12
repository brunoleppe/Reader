//
// Created by bleppe on 12/05/23.
//

#include "ViewService.h"

void ViewService::set_message(MessagePacket *m) {
    if(m->messageType == MESSAGE_TYPE_MENU) {
        MenuView::instance.set_title(m->title);
        MenuView::instance.set_items(m->items);
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
    xQueueSend(queue, &evt, portMAX_DELAY);
}

void ViewService::attach(InputEventObserver *observer) {
    observer->inputSubject = &subject;
    subject.attach(observer);
}

void ViewService::task(void *) {
    ViewService* vs = &ViewService::instance;
    LCD_configure();
    while(true){
#if defined(PIC32) || defined(__PIC32) || defined(__PIC32__)
        InputEvent evt;
        if(xQueueReceive(vs->queue, &evt, 10)){
            vs->v->on_event(evt);
        }
        LCD_print();
        vTaskDelay(17);
#endif
    }
}
