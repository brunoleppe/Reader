//
// Created by bleppe on 03/04/23.
//

#include "StateMainMenu.h"
#include "lcd.h"
#include "sst26.h"
#include <cstdio>
#include "debug.h"



void StateMainMenu::on_enter() {


    LCD_clear();
    LCD_draw_string(0, 0, "MainMenu", LCD_FONT_MEDIUM, LCD_COLOR_BLACK);

    sst26_read_id();

    unsigned int key = 0x11223344;
    sst26_sector_erase(0x10000);
    sst26_page_program(&key, 4, 0x10000);
    unsigned int b;
    sst26_read(&b, 4, 0x10000);
    DEBUG_PRINT("%08x", b);
    char s[16];
    snprintf(s,15,"%08x", b);
    LCD_draw_string(10, 38, s, LCD_FONT_SMALL, LCD_COLOR_BLACK);

    LCD_print();

}

void StateMainMenu::on_input(InputEvent &evt) {
    char s[32];
    snprintf(s,31,"key = %x, val = %x", evt.code, evt.value);
    LCD_draw_string(10, 50, s, LCD_FONT_SMALL, LCD_COLOR_BLACK);
    LCD_print();

}

void StateMainMenu::on_exit() {

}

StateMainMenu StateMainMenu::instance;

StateMainMenu *StateMainMenu::state() {
   return &instance;
}

