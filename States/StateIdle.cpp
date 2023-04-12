//
// Created by bleppe on 05/04/23.
//

#include "StateIdle.h"
#include "lcd.h"
#include "printf.h"
#include "linux_keys.h"

State *StateIdle::get_state() {
    return &instance;
}

void StateIdle::on_enter() {
    LCD_clear();
    LCD_draw_string(10,10, "hola mundo", LCD_FONT_MEDIUM, LCD_COLOR_BLACK);
}

void StateIdle::on_exit() {
    State::on_exit();
}

void StateIdle::on_input(InputEvent &evt) {
    if(evt.code == KEY_BACKSPACE && evt.value == INPUT_EVENT_CLICKED){
        machine->get_back();
    }
    else{
        char s[32] = {0};
        sprintf(s,"key = %3d, evt = %2d", evt.code, evt.value);
        LCD_draw_string(10, 40, s, LCD_FONT_SMALL, LCD_COLOR_BLACK);
    }

}

StateIdle StateIdle::instance;