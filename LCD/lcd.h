//
// Created by bruno on 26/01/23.
//

#ifndef LCD_H
#define LCD_H

#include "spi.h"
#include "gpio.h"

typedef enum{
    LCD_COLOR_BLACK,
    LCD_COLOR_WHITE,
    LCD_COLOR_MIX,
}LCD_COLOR;

int     LCD_init        (SPI_Handler handler, GPIO_PIN cs, GPIO_PIN bla, GPIO_PIN dc, GPIO_PIN rst);
void    LCD_draw_point  (int x, int y, LCD_COLOR color);
void    LCD_draw_hline  (int x, int y, int length, LCD_COLOR color);
void    LCD_draw_vline  (int x, int y, int length, LCD_COLOR color);
void    LCD_draw_rect   (int x, int y, int height, int width, LCD_COLOR color);
void    LCD_print       ( void );
#endif //LCD_H
