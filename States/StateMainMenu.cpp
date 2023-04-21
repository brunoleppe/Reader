//
// Created by bleppe on 03/04/23.
//

#include "StateMainMenu.h"
#include "lcd.h"
#include "sst26.h"
#include "printf.h"

#include "vector"
#include "list"
#include "StateIdle.h"
#include "linux_keys.h"

#include "FreeRTOS.h"
#include "task.h"

static uint8_t *bitmap;

void StateMainMenu::on_enter() {


    unsigned int b;
    b = sst26_read_id()->jedecWord;
    (void)b;

//    bitmap = new uint8_t[15360];
//    sst26_write((void*)bitmap, sizeof(bitmap), 0x10000);
//    sst26_read((void*)bitmap, 15360, 0x10000);
//    LCD_draw_bitmap(0,0,bitmap,15360);

    LCD_clear();
    LCD_draw_string(0, 0, "MainMenu", LCD_FONT_MEDIUM, LCD_COLOR_BLACK);


}

void StateMainMenu::on_input(InputEvent &evt) {
    if(evt.code == KEY_F1 && evt.value == INPUT_EVENT_CLICKED){
        machine->transition(StateIdle::get_state());
    }
    if(evt.code == KEY_BACKSPACE && evt.value == INPUT_EVENT_CLICKED){
        machine->get_back();
    }
}

void StateMainMenu::on_exit() {
//    delete[] bitmap;
}

StateMainMenu StateMainMenu::instance;

State* StateMainMenu::get_state() {
   return (State*)&instance;
}

