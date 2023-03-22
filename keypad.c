//
// Created by bleppe on 20/03/23.
//

#include "keypad.h"
#include "hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "BSP/bsp.h"
#include "qtouch.h"

#include <stdio.h>
#include <string.h>
#include "lcd.h"

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

    while(true) {

        xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);

        key = QTouch_get_key();

        char s[17];
        sprintf(s,"%4x",key);
        LCD_draw_string(0,48, s, LCD_FONT_SMALL, LCD_COLOR_BLACK);
    }
}