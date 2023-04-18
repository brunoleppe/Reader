//
// Created by bleppe on 06/04/23.
//

#include "StateDeviceEnter.h"
#include "lcd.h"
#include "StateMainMenu.h"
#include "linux_keys.h"

static int unlockKey[] = {1,1, 2, 3, 1, 5, 5 , 4};
static const int unlockKeyLength = sizeof(unlockKey)/sizeof(int);
static int *ptr = unlockKey;
static int keyCount = 0;

void StateDeviceEnter::on_enter() {
    LCD_clear();
    ptr = unlockKey;
    keyCount = 0;
    LCD_draw_string(0,0,"HOLA MUNDO", LCD_FONT_MEDIUM, LCD_COLOR_BLACK);
}

void StateDeviceEnter::on_exit() {
    State::on_exit();
}

void StateDeviceEnter::on_input(InputEvent &evt) {

    if(evt.code == KEY_ENTER && evt.value == INPUT_EVENT_CLICKED){
        machine->transition(StateMainMenu::get_state());
    }

//    if(evt.value == INPUT_EVENT_CLICKED){
//        if(*ptr == evt.code){
//            ptr++;
//            keyCount++;
//        }
//        else{
//            ptr = unlockKey;
//            keyCount = 0;
//        }
//    }
//
//    if(keyCount == unlockKeyLength){
//        machine->transition(StateMainMenu::get_state());
//    }

}

StateDeviceEnter StateDeviceEnter::instance;

State *StateDeviceEnter::get_state() {
    return &instance;
}