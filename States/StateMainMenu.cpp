//
// Created by bleppe on 03/04/23.
//

#include "StateMainMenu.h"
#include "lcd.h"
#include "sst26.h"
#include "printf.h"



void StateMainMenu::on_enter() {


    LCD_clear();
    LCD_draw_string(0, 0, "MainMenu", LCD_FONT_MEDIUM, LCD_COLOR_BLACK);

    unsigned int b;
    b = sst26_read_id()->jedecWord;

    unsigned int key = 0x54321000;

    sst26_write(&key, 4, 0x10000);
    sst26_read(&b, 4, 0x10000);

    char s[16];
    snprintf(s, 15, "0x%08x",b);
    LCD_draw_string(10,30, s, LCD_FONT_SMALL, LCD_COLOR_BLACK);


}

void StateMainMenu::on_input(InputEvent &evt) {

}

void StateMainMenu::on_exit() {

}

StateMainMenu StateMainMenu::instance;

StateMainMenu *StateMainMenu::state() {
   return &instance;
}

