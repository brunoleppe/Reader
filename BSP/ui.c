//
// Created by bleppe on 31/03/23.
//

#include "ui.h"
#include "input.h"

#include "FreeRTOS.h"
#include "queue.h"
#include "lcd.h"

#include <stdio.h>

QueueHandle_t inputQueue = NULL;


void ui_task(void *params)
{

    inputQueue = xQueueCreate(10, sizeof(InputEvent));

    while(1){
        InputEvent evt;
        xQueueReceive(inputQueue, &evt, portMAX_DELAY);
        /*Update UI*/
#if HAL_DEBUG
        char s[32];
        snprintf(s, 31, "key = %02x, val = %02x", evt.code, evt.value);
        LCD_draw_string(10,50, s, LCD_FONT_SMALL, LCD_COLOR_BLACK);
#endif
    }
}

bool input_report_key(int code, int value)
{
    if(inputQueue == NULL)
        return false;
    return xQueueSend(inputQueue, &((InputEvent){.code = code, .value = value}), 10) == pdPASS;
}

