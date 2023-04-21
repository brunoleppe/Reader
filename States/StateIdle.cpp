//
// Created by bleppe on 05/04/23.
//

#include "StateIdle.h"
#include "lcd.h"
#include "printf.h"
#include "linux_keys.h"
#include "virtual_term.h"
#include "keypad.h"

State *StateIdle::get_state() {
    return &instance;
}

void StateIdle::on_enter() {
    LCD_clear();
    LCD_draw_string(10,10, "hola mundo", LCD_FONT_MEDIUM, LCD_COLOR_BLACK);
    for(int i=0; i<=size; i++)
        buffer[i] = 0;

    keypad_set_mode(KEYPAD_ALPHA);
    counter = 0;
}

void StateIdle::on_exit() {
    State::on_exit();
}

void StateIdle::on_input(InputEvent &evt) {

    if(evt.value == INPUT_EVENT_PRESSED){
        char c = get_char(evt.code);
        sprintf_(buffer,"%c",c);
        LCD_draw_string(0,40,buffer,LCD_FONT_SMALL, LCD_COLOR_BLACK);
//        if(c >= ' '){
//            buffer[counter] = c;
//            LCD_draw_string(0,40,buffer,LCD_FONT_SMALL, LCD_COLOR_BLACK);
//        }
//        else if(evt.code == KEY_BACKSPACE){
//            buffer[counter] = ' ';
//            LCD_draw_string(0,40,buffer,LCD_FONT_SMALL, LCD_COLOR_BLACK);
//            if(counter > 0)
//                counter--;
//        }
    }
//    else if(evt.value == INPUT_EVENT_CLICKED){
//        char c = get_char(evt.code);
//        if(c >= ' ') {
//            if (++counter == size)
//                counter = 0;
//        }
//    }


    if(evt.code == KEY_ESC && evt.value == INPUT_EVENT_CLICKED){
        machine->get_back();
    }
//    else{
//        char s[32] = {0};
//        sprintf(s,"key = %3d, evt = %2d", evt.code, evt.value);
//        LCD_draw_string(10, 40, s, LCD_FONT_SMALL, LCD_COLOR_BLACK);
//    }

}

StateIdle StateIdle::instance;