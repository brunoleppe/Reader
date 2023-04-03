//
// Created by bleppe on 20/03/23.
//

#include "keypad.h"
#include "FreeRTOS.h"
#include "task.h"
#include "qt1245.h"

#include "lcd.h"
#include "board_defs.h"
#include "led_matrix.h"
#include "input.h"

enum  KEYS{
    KEYS_1          = 0,
    KEYS_2          = 1,
    KEYS_3          = 2,
    KEYS_4          = 3,
    KEYS_5          = 4,
    KEYS_6          = 5,
    KEYS_7          = 6,
    KEYS_8          = 7,
    KEYS_9          = 8,
    KEYS_0          = 10,
    KEYS_DOT        = 11,
    KEYS_ENTER      = 9,
    KEYS_OPTION     = 15,
    KEYS_RETURN     = 14,
    KEYS_CANCEL     = 12,
    KEYS_CLEAR      = 13,
    KEYS_PUMP       = 16,
    KEYS_RELEASE    = -1,
};

static int qt_key_map(enum QT_KEY qtKey)
{
    switch (qtKey) {
        case QT_KEY_1           : return KEYS_1;
        case QT_KEY_2           : return KEYS_2;
        case QT_KEY_3           : return KEYS_3;
        case QT_KEY_4           : return KEYS_4;
        case QT_KEY_5           : return KEYS_5;
        case QT_KEY_6           : return KEYS_6;
        case QT_KEY_7           : return KEYS_7;
        case QT_KEY_8           : return KEYS_8;
        case QT_KEY_9           : return KEYS_9;
        case QT_KEY_0           : return KEYS_0;
        case QT_KEY_DOT         : return KEYS_DOT;
        case QT_KEY_ENTER       : return KEYS_ENTER;
        case QT_KEY_OPTION      : return KEYS_OPTION;
        case QT_KEY_RETURN      : return KEYS_RETURN;
        case QT_KEY_CANCEL      : return KEYS_CANCEL;
        case QT_KEY_CLEAR       : return KEYS_CLEAR;
        case QT_KEY_PUMP        : return KEYS_PUMP;
        case QT_KEY_RELEASE     : return KEYS_RELEASE;
    }
    return 0;
}

void keypad_task(void *params)
{
    (void)params;
    QTouch_initialize(QT_SPI_DRIVER_INDEX, QT_SS_PIN, QT_RST_PIN, QT_CHANGE_PIN, QT_DRDY_PIN);
    int key = 0;
    int currentKey = 0;
    while(true) {
        vTaskDelay(20);
        if(GPIO_pin_read(QT_CHANGE_PIN) == GPIO_LOW && QTouch_get_key(&key)) {
            led_matrix_led_clr_all();
            if(key != 0) {
                currentKey = key;
                led_matrix_led_number_set(qt_key_map(currentKey));
                input_report_key(currentKey, 1);
            }
            else{
                input_report_key(currentKey, 0);
                currentKey = 0;
            }
        }
    }
}