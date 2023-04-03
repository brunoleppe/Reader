//
// Created by bleppe on 03/04/23.
//

#include "StateMainMenu.h"
#include "lcd.h"
#include "sst26.h"
#include <cstdio>

void StateMainMenu::on_enter() {
    LCD_clear();
    LCD_draw_string(0, 0, "MainMenu", LCD_FONT_MEDIUM, LCD_COLOR_BLACK);

    unsigned int a = 0xaabbccdd;
    sst26_write(&a, 4, 0x10000);
    unsigned int b;
    sst26_read(&b, 4, 0x10000);
    char s[16];
    snprintf(s,15,"%08x", b);
    LCD_draw_string(10, 38, s, LCD_FONT_SMALL, LCD_COLOR_BLACK);
}

void StateMainMenu::on_input(InputEvent &evt) {
    char s[32];
    snprintf(s,31,"key = %x, val = %x", evt.code, evt.value);
    LCD_draw_string(10, 50, s, LCD_FONT_SMALL, LCD_COLOR_BLACK);
}

void StateMainMenu::on_exit() {

}

StateMainMenu StateMainMenu::instance;

StateMainMenu *StateMainMenu::state() {
   return &instance;
}

