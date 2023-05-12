//
// Created by bleppe on 09/05/23.
//

#include "Box.h"
#include "lcd.h"

void Box::draw() {
    LCD_draw_fill(x,y,h,w,(LCD_COLOR)backColor);
    LCD_draw_rect(x,y,h,w,(LCD_COLOR)foreColor);
}

Box::Box(int x, int y, int width, int height, uint8_t back, uint8_t fore) : Figure(x, y, width, height, back, fore) {}
