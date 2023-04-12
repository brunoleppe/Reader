//
// Created by bleppe on 03/04/23.
//

#include "ui.h"

#include "ui.h"
#include "input.h"

#include "FreeRTOS.h"
#include "queue.h"
#include "lcd.h"
#include "State.h"
#include "StateDeviceEnter.h"

static QueueHandle_t inputQueue = nullptr;
static StateMachine machine;
static bool initialized = false;

void ui_initialize(State *initial)
{
    machine.initialize(initial);
    initialized = true;
}


void ui_task(void *params)
{

    inputQueue = xQueueCreate(10, sizeof(InputEvent));
    machine.initialize(StateDeviceEnter::get_state());

    while(1){

        InputEvent evt;
        xQueueReceive(inputQueue, &evt, portMAX_DELAY);
        /*Update UI*/
        machine.on_input(evt);
    }
}

bool input_report_key(int code, int value)
{
    if(inputQueue == NULL)
        return false;
    return xQueueSend(inputQueue, &((InputEvent){.code = code, .value = value}), 10) == pdPASS;
}