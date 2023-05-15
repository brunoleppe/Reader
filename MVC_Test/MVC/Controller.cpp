//
// Created by bruno on 09/05/23.
//

#include "Controller.h"
#include "ControllerInputEvent.h"
#if defined(PIC32) || defined(__PIC32) || defined(__PIC32__)
#include "virtual_term.h"
#else
#include "Input/virtual_term.h"
#endif

void Controller::update() {
#if defined(PIC32) || defined(__PIC32) || defined(__PIC32__)
    xQueueSend(queue, &inputSubject->get_data(),portMAX_DELAY);
#else
    queue.push(inputSubject->get_data());
#endif
}

Controller::Controller(ModelStateService* s, ViewService* v) : model(s), view(v), running(true)
{
#if defined(PIC32) || defined(__PIC32) || defined(__PIC32__)
        queue = xQueueCreate(5, sizeof(InputEvent));
#endif
    v->attach(this);
}
#if defined(PIC32) || defined(__PIC32) || defined(__PIC32__)
void
#else
int
#endif
Controller::controller_task(void *data) {
    auto c = (Controller*)data;
    c->view->set_message(c->model->get_data());
    c->view->update();
    while(c->running){
        InputEvent evt;
#if defined(PIC32) || defined(__PIC32) || defined(__PIC32__)
        if(xQueueReceive(c->queue, &evt, portMAX_DELAY)){
#else
        SDL_Delay(20);
//        if(!c->queue.empty()){
//            evt = c->queue.front();
//            c->queue.pop();
        if(true){
            evt = c->queue.pop();
#endif
            ControllerInputEvent cEvt = {.event = (INPUT_EVENTS)evt.value};
            cEvt.type = INPUT_EVENT_TYPE_CONTROL;
            cEvt.code = is_control(evt.code);

            if(c->model->on_event(cEvt)) {
                c->view->set_message(c->model->get_data());
                c->view->update();
            }
        }
    }
#if !defined(PIC32) && !defined(__PIC32) & !defined(__PIC32__)
    c->model->stop();
    return 0;
#endif
}
#if !defined(PIC32) && !defined(__PIC32) & !defined(__PIC32__)
void Controller::Stop() {
    running = false;
    InputEvent evt = {
            .code = 0,
            .value = INPUT_EVENT_RELEASED
    };
    queue.push(evt);
}
#endif