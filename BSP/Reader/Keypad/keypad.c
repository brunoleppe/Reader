#include <features.h>
//
// Created by bleppe on 20/03/23.
//

#include "keypad.h"

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

#include "BSP/bsp.h"
#include "Reader/QTouch/qt1110.h"

#include <stdio.h>
#include <string.h>
#include "lcd.h"
#include "debug_bsp.h"
#include "Reader/board_defs.h"
#include "input.h"

#include "linux_keys.h"

static TaskHandle_t thisTask;
static int counter = 0;

static void click_timer_callback(xTimerHandle timer)
{
    counter++;
}

static void qt_change_handler(GPIO_PinMap pin, uintptr_t context)
{
    BaseType_t xHigherPriorityTaskWoken;
    bool val;
    val = GPIO_pin_read(QT_CHANGE);
    if(val == false)
    {
        xHigherPriorityTaskWoken = pdFALSE;
        xTaskNotifyFromISR(thisTask,0,eNoAction,&xHigherPriorityTaskWoken);
        portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
    }
}

static int qtkey_map(int key){
    const int keys[] = {
            KEY_RESERVED, KEY_F1, KEY_BACKSPACE, KEY_ENTER, KEY_DOWN, KEY_UP, KEY_F2
    };
    return keys[key];
}


_Noreturn void keypad_task(void *params)
{
    (void)params;
    thisTask = xTaskGetCurrentTaskHandle();
    BSP_gpio_callback_register(QT_CHANGE, qt_change_handler, 0);
    QTouch_initialize(QT_SPI_CHANNEL, QT_SS, QT_RST, QT_CHANGE, 0);

    xTimerHandle clickTimer = xTimerCreate(NULL, 1000, true, NULL, click_timer_callback);

    int key = 0;
    int prev_key = 0;

    while(true) {

        xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);
        GPIO_pin_toggle(LED4);
        key = QTouch_get_key();
        if(key != 0) {
            prev_key = key;
            input_report_key(qtkey_map(prev_key), INPUT_EVENT_PRESSED);
            counter = 0;
            xTimerStart(clickTimer, 0);
        }
        else{
            xTimerStop(clickTimer, 0);
            input_report_key(qtkey_map(prev_key), INPUT_EVENT_RELEASED);
            input_report_key(qtkey_map(prev_key), INPUT_EVENT_CLICKED);
            if(counter >= 2 && counter < 4)
                input_report_key(qtkey_map(prev_key), INPUT_EVENT_LONG_CLICKED);
            else if(counter >= 4)
                input_report_key(qtkey_map(prev_key), INPUT_EVENT_LONG_LONG_CLICKED);
            prev_key = 0;
        }
    }
}
void keypad_set_mode(uint32_t mode)
{


}