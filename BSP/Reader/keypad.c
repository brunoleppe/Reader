//
// Created by bleppe on 20/03/23.
//

#include "keypad.h"
#include "FreeRTOS.h"
#include "task.h"
#include "BSP/bsp.h"
#include "qt1110.h"

#include <stdio.h>
#include <string.h>
#include "lcd.h"
#include "debug.h"
#include "Reader/board_defs.h"
#include "input.h"

static TaskHandle_t thisTask;

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

void keypad_task(void *params)
{
    (void)params;
    thisTask = xTaskGetCurrentTaskHandle();
    BSP_gpio_callback_register(QT_CHANGE, qt_change_handler, 0);
    QTouch_initialize(QT_SPI_CHANNEL, QT_SS, QT_RST, QT_CHANGE, 0);

    int key = 0;
    int prev_key = 0;

    while(true) {

        xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);
        GPIO_pin_toggle(LED4);
        key = QTouch_get_key();
        if(key != 0) {
            prev_key = key;
            input_report_key(prev_key, 1);
        }
        else{
            input_report_key(prev_key, 0);
            prev_key = 0;
        }
    }
}