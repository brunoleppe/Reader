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
        if(!c->queue.empty()){
            evt = c->queue.front();
            c->queue.pop();
#endif
            ControllerInputEvent cEvt = {.event = (INPUT_EVENTS)evt.value};
            int res;
            if((res = is_alpha(evt.code))){
                cEvt.type = INPUT_EVENT_TYPE_ALPHA;
                cEvt.code = res;
            }
            else if((res = is_numeric(evt.code))){
                cEvt.type = INPUT_EVENT_TYPE_NUMERIC;
                cEvt.code = res;
            }
            else if((res = is_control(evt.code))){
                cEvt.type = INPUT_EVENT_TYPE_CONTROL;
                cEvt.code = res;
            }
//            c->view->set_event(cEvt);
            if(c->model->on_event(cEvt)) {
                c->view->set_message(c->model->get_data());
                c->view->update();
            }
        }
    }
}

void Controller::Stop() {
    running = false;
}
