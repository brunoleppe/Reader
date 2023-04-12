//
// Created by bleppe on 20/03/23.
//
/**********************************************************************
* Includes
**********************************************************************/
#include "keypad.h"
#include "FreeRTOS.h"
#include "task.h"
#include "qt1245.h"
#include "linux_keys.h"
#include "lcd.h"
#include "board_defs.h"
#include "led_matrix.h"
#include "input.h"

/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/
/**********************************************************************
* Module Preprocessor Macros
**********************************************************************/
/**********************************************************************
* Module Typedefs
**********************************************************************/
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
};

typedef struct KeyObject{
    int         *characters;
    int         number;
    int         *symbols;
    int         alternate;
    int         option;
}KeyObject;

/*********************************************************************
* Module Variable Definitions
**********************************************************************/
static uint32_t mode = KEYPAD_CONTROLS | KEYPAD_ALTERNATE;
static KeyObject keys[] = {
        {NULL, KEY_1, NULL, 0},
        {(int[]){KEY_A, KEY_B, KEY_C, KEY_TILDE_A, 0}, KEY_2, NULL, KEY_UP},
        {(int[]){KEY_D, KEY_E, KEY_F, KEY_TILDE_E, 0}, KEY_3, NULL, 0},
        {(int[]){KEY_G, KEY_H, KEY_I, KEY_TILDE_I, 0}, KEY_4, NULL, KEY_LEFT},
        {(int[]){KEY_J, KEY_K, KEY_L, 0}, KEY_5, NULL, KEY_ENTER},
        {(int[]){KEY_M, KEY_N, KEY_O, KEY_TILDE_O, 0}, KEY_6, NULL, KEY_RIGHT},
        {(int[]){KEY_P, KEY_Q, KEY_R, KEY_S, 0}, KEY_7, NULL, 0},
        {(int[]){KEY_T, KEY_U, KEY_V, KEY_TILDE_U, 0}, KEY_8, NULL, KEY_DOWN},
        {(int[]){KEY_W, KEY_X, KEY_Y, KEY_Z, 0}, KEY_9, NULL, 0},
        {NULL, 0, (int[]){KEY_KPASTERISK, 0}, 0, KEY_ENTER},
        {(int[]){KEY_SPACE, 0}, KEY_0, NULL, 0},
        {(int[]){KEY_DOT, 0},KEY_DOT, (int[]){KEY_HASH, KEY_ASPERAND, KEY_MINUS, KEY_UNDERSCORE, KEY_SLASH, 0}, 0},
        {NULL, 0, NULL, 0, KEY_ESC},
        {NULL, 0, NULL, 0, KEY_DELETE},
        {NULL, 0, NULL, 0, KEY_BACKSPACE},
        {NULL, 0, NULL, 0, KEY_F1},
        {NULL, 0, NULL, 0, KEY_F2}
};
/**********************************************************************
* Function Prototypes
**********************************************************************/
static int qt_key_map(enum QT_KEY qtKey);
static void qt_process_key(int key);
/**********************************************************************
* Function Definitions
**********************************************************************/

_Noreturn void keypad_task(void *params)
{
    (void)params;
    QTouch_initialize(QT_SPI_DRIVER_INDEX, QT_SS_PIN, QT_RST_PIN, QT_CHANGE_PIN, QT_DRDY_PIN);
    int key = 0;
    int currentKey = 0;
    int prevKey = -1;
    bool handled = false;
    while(true) {
        vTaskDelay(20);
        if(GPIO_pin_read(QT_CHANGE_PIN) == GPIO_LOW && QTouch_get_key(&key)) {
            led_matrix_led_clr_all();
            currentKey = qt_key_map(key);
            if(currentKey != -1)
                led_matrix_led_number_set(currentKey);

            if(currentKey != -1) {
                KeyObject *keyObj = &keys[currentKey];
                if(keyObj->number != 0) {
                    input_report_key(keyObj->number, INPUT_EVENT_PRESSED);
                }
                else if(keyObj->option != 0) {
                    input_report_key(keyObj->option, INPUT_EVENT_PRESSED);
                }
                prevKey = currentKey;
            }
            else{
                KeyObject *keyObj = &keys[prevKey];
                if(keyObj->number != 0) {
                    input_report_key(keyObj->number, INPUT_EVENT_RELEASED);
                    input_report_key(keyObj->number, INPUT_EVENT_CLICKED);

                }
                else if(keyObj->option != 0) {
                    input_report_key(keyObj->option, INPUT_EVENT_PRESSED);
                    input_report_key(keyObj->option, INPUT_EVENT_CLICKED);
                }
            }
        }
    }
}

int qt_key_map(enum QT_KEY qtKey)
{
    switch (qtKey) {
        case QT_KEY_1           : return KEYS_1        ;
        case QT_KEY_2           : return KEYS_2        ;
        case QT_KEY_3           : return KEYS_3        ;
        case QT_KEY_4           : return KEYS_4        ;
        case QT_KEY_5           : return KEYS_5        ;
        case QT_KEY_6           : return KEYS_6        ;
        case QT_KEY_7           : return KEYS_7        ;
        case QT_KEY_8           : return KEYS_8        ;
        case QT_KEY_9           : return KEYS_9        ;
        case QT_KEY_0           : return KEYS_0        ;
        case QT_KEY_DOT         : return KEYS_DOT      ;
        case QT_KEY_ENTER       : return KEYS_ENTER    ;
        case QT_KEY_OPTION      : return KEYS_OPTION   ;
        case QT_KEY_RETURN      : return KEYS_RETURN   ;
        case QT_KEY_CANCEL      : return KEYS_CANCEL   ;
        case QT_KEY_CLEAR       : return KEYS_CLEAR    ;
        case QT_KEY_PUMP        : return KEYS_PUMP     ;
        case 0                  : return -1;
    }
    return 0;
}