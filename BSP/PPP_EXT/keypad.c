//
// Created by bleppe on 20/03/23.
//
/**********************************************************************
* Includes
**********************************************************************/
#include "keypad.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
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
    KEYS_RELEASE    = -1,
    KEYS_INVALID    = -2,
};

typedef struct KeyObject{
    int         *characters;
    int         number;
    int         *symbols;
    int         alternate;
    int         option;
}KeyObject;

typedef struct KeyHandler{
    int prevKey;
    int currentKey;
    int *ptr;
}KeyHandler;

/*********************************************************************
* Module Variable Definitions
**********************************************************************/
static uint32_t mode = KEYPAD_ALTERNATE;
static TimerHandle_t timer;
static KeyHandler keyHandler = {KEYS_INVALID, KEYS_RELEASE};
static KeyObject keys[] = {
        {(int[]){KEY_DOT, KEY_COMMA, KEY_SEMICOLON, 0}, KEY_1,
         (int[]){KEY_DOT, KEY_COMMA, KEY_SEMICOLON, KEY_1, 0}, 0},

        {(int[]){KEY_A, KEY_B, KEY_C, KEY_TILDE_A, 0}, KEY_2,
         (int[]){KEY_A, KEY_B, KEY_C, KEY_2, KEY_TILDE_A, 0}, KEY_UP},

        {(int[]){KEY_D, KEY_E, KEY_F, KEY_TILDE_E, 0}, KEY_3,
         (int[]){KEY_D, KEY_E, KEY_F, KEY_3, KEY_TILDE_E, 0}, 0},

        {(int[]){KEY_G, KEY_H, KEY_I, KEY_TILDE_I, 0}, KEY_4,
         (int[]){KEY_G, KEY_H, KEY_I, KEY_4, KEY_TILDE_I, 0}, KEY_LEFT},

        {(int[]){KEY_J, KEY_K, KEY_L, 0}, KEY_5,
         (int[]){KEY_J, KEY_K, KEY_L, KEY_5, 0}, KEY_ENTER},

        {(int[]){KEY_M, KEY_N, KEY_O, KEY_TILDE_O, KEY_TILDE_N, 0}, KEY_6,
         (int[]){KEY_M, KEY_N, KEY_O, KEY_6, KEY_TILDE_O, KEY_TILDE_N, 0}, KEY_RIGHT},

        {(int[]){KEY_P, KEY_Q, KEY_R, KEY_S, 0}, KEY_7,
         (int[]){KEY_P, KEY_Q, KEY_R, KEY_S, KEY_7, 0}, 0},

        {(int[]){KEY_T, KEY_U, KEY_V, KEY_TILDE_U, KEY_DOTTED_U, 0}, KEY_8,
         (int[]){KEY_T, KEY_U, KEY_V, KEY_8, KEY_TILDE_U, KEY_DOTTED_U, 0}, KEY_DOWN},

        {(int[]){KEY_W, KEY_X, KEY_Y, KEY_Z, 0}, KEY_9,
         (int[]){KEY_W, KEY_X, KEY_Y, KEY_Z, KEY_9, 0}, 0},

        {(int[]){KEY_KPASTERISK, 0}, 0, (int[]){KEY_KPASTERISK, 0}, 0, KEY_ENTER},

        {(int[]){KEY_SPACE, 0}, KEY_0, (int[]){KEY_SPACE, KEY_0, 0}, 0},

        {(int[]){KEY_DOT, KEY_HASH, KEY_ASPERAND, KEY_MINUS, KEY_UNDERSCORE, KEY_SLASH, 0},KEY_DOT,
         (int[]){KEY_DOT, KEY_HASH, KEY_ASPERAND, KEY_MINUS, KEY_UNDERSCORE, KEY_SLASH, 0}, 0},

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
static void timer_callback(TimerHandle_t timer);
/**********************************************************************
* Function Definitions
**********************************************************************/

_Noreturn void keypad_task(void *params)
{
    (void)params;
    QTouch_initialize(QT_SPI_DRIVER_INDEX, QT_SS_PIN, QT_RST_PIN, QT_CHANGE_PIN, QT_DRDY_PIN);
    int key = 0;
    int currentKey;
    int oldKey = KEYS_RELEASE;
    timer = xTimerCreate("t1", 2000, false, NULL, timer_callback);
    while(true) {
        vTaskDelay(20);
        if(GPIO_pin_read(QT_CHANGE_PIN) == GPIO_LOW && QTouch_get_key(&key)) {
            if(key != oldKey){
                led_matrix_led_clr_all();
                currentKey = qt_key_map(key);
                if(currentKey != KEYS_RELEASE)
                    led_matrix_led_number_set(currentKey);

                qt_process_key(currentKey);
                oldKey = key;
            }
        }
    }
}

static void timer_callback(TimerHandle_t t)
{
    (void)t;
    input_report_key(*keyHandler.ptr, INPUT_EVENT_CLICKED);
    keyHandler.prevKey = KEYS_INVALID;
}

static void qt_process_key(int key)
{
    keyHandler.currentKey = key;

    if(keyHandler.currentKey != KEYS_RELEASE) {
        KeyObject *keyObj = &keys[keyHandler.currentKey];

        if(keyObj->option != 0) {
            input_report_key(keyObj->option, INPUT_EVENT_PRESSED);
        }
        else if((mode & KEYPAD_ALTERNATE) == KEYPAD_ALTERNATE){
            if((keyObj->alternate != 0))
                input_report_key(keyObj->alternate, INPUT_EVENT_PRESSED);
        }
        else if((mode & KEYPAD_NUMERIC) == KEYPAD_NUMERIC){
            if((keyObj->number != 0))
                input_report_key(keyObj->number, INPUT_EVENT_PRESSED);
        }
        else {
            if(((mode & KEYPAD_ALPHANUMERIC) == KEYPAD_ALPHANUMERIC && keyObj->symbols == NULL) ||
                    ((mode & KEYPAD_ALPHA) == KEYPAD_ALPHA && keyObj->characters == NULL)) {
                goto EXIT;
            }

            if(keyHandler.currentKey != keyHandler.prevKey){
                if(keyHandler.prevKey >= 0 && keyHandler.ptr != NULL){
                    xTimerStop(timer, 0);
                    input_report_key(*keyHandler.ptr, INPUT_EVENT_CLICKED);
                }
                keyHandler.ptr =  ((mode & KEYPAD_ALPHA) == KEYPAD_ALPHA)?keyObj->characters:keyObj->symbols;
            }
            else{
                keyHandler.ptr++;
                if(*keyHandler.ptr == 0)
                    keyHandler.ptr =  ((mode & KEYPAD_ALPHA) == KEYPAD_ALPHA)?keyObj->characters:keyObj->symbols;
            }
            xTimerReset(timer,0);
            input_report_key(*keyHandler.ptr, INPUT_EVENT_PRESSED);
        }
EXIT:
        keyHandler.prevKey = keyHandler.currentKey;
    }
    else{
        if(keyHandler.prevKey < 0)
            return;
        KeyObject *keyObj = &keys[keyHandler.prevKey];

        if(keyObj->option != 0) {
            input_report_key(keyObj->option, INPUT_EVENT_RELEASED);
            input_report_key(keyObj->option, INPUT_EVENT_CLICKED);
        }
        else if((mode & KEYPAD_ALTERNATE) == KEYPAD_ALTERNATE){
            if((keyObj->alternate != 0)) {
                input_report_key(keyObj->alternate, INPUT_EVENT_RELEASED);
                input_report_key(keyObj->alternate, INPUT_EVENT_CLICKED);
            }
        }
        else if((mode & KEYPAD_NUMERIC) == KEYPAD_NUMERIC){
            if((keyObj->number != 0)) {
                input_report_key(keyObj->number, INPUT_EVENT_RELEASED);
                input_report_key(keyObj->number, INPUT_EVENT_CLICKED);
            }
        }
        else if(keyHandler.ptr != NULL && *keyHandler.ptr != 0) {
            input_report_key(*keyHandler.ptr, INPUT_EVENT_RELEASED);
        }
    }

}

void keypad_set_mode(uint32_t _mode)
{
    mode = _mode;
}

void keypad_calibrate( void )
{
    QTouch_calibrate_all();
}
void keypad_calibrate_key(int key)
{
    QTouch_calibrate_key(key);
}
void keypad_get_key_signal(int key)
{

}

int qt_key_map(enum QT_KEY qtKey)
{
    switch (qtKey) {
        case QT_KEY_1           : return KEYS_1         ;
        case QT_KEY_2           : return KEYS_2         ;
        case QT_KEY_3           : return KEYS_3         ;
        case QT_KEY_4           : return KEYS_4         ;
        case QT_KEY_5           : return KEYS_5         ;
        case QT_KEY_6           : return KEYS_6         ;
        case QT_KEY_7           : return KEYS_7         ;
        case QT_KEY_8           : return KEYS_8         ;
        case QT_KEY_9           : return KEYS_9         ;
        case QT_KEY_0           : return KEYS_0         ;
        case QT_KEY_DOT         : return KEYS_DOT       ;
        case QT_KEY_ENTER       : return KEYS_ENTER     ;
        case QT_KEY_OPTION      : return KEYS_OPTION    ;
        case QT_KEY_RETURN      : return KEYS_RETURN    ;
        case QT_KEY_CANCEL      : return KEYS_CANCEL    ;
        case QT_KEY_CLEAR       : return KEYS_CLEAR     ;
        case QT_KEY_PUMP        : return KEYS_PUMP      ;
        case QT_KEY_RELEASE     : return KEYS_RELEASE   ;
    }
    return 0;
}