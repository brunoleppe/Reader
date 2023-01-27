//
// Created by bruno on 26/01/23.
//
#include "lcd.h"
#include "spi.h"
#include "FreeRTOS.h"
#include "task.h"
#include "gpio.h"

struct _LCD{
    SPI_Handler handler;
    uint8_t lcd_buffer[15360];
    GPIO_PIN cs_pin;
    GPIO_PIN bla_pin;
    GPIO_PIN dc_pin;
    GPIO_PIN rst_pin;

}lcd;


int     LCD_init        (SPI_Handler handler, GPIO_PIN cs, GPIO_PIN bla, GPIO_PIN dc, GPIO_PIN rst)
{
    lcd.handler = handler;
    lcd.bla_pin = bla;
    lcd.cs_pin = cs;
    lcd.dc_pin = dc;
    lcd.rst_pin = rst;

    static uint8_t config_buffer[]={
            0x2a,0x27,0xc2,0xa1,0xd0,0xd5,0xc8,0x10,0xeb,0xa6,0xa4,0x81,0x35,0xd8,0xf1,
            0x7f,0xf2,0x00,0xf3,0x7f,0x85,0xaf,0xf4,0,0xf5,0,0xf6,79,0xf7,127,0xf8,0x00,
            0x10,0x60,0x70
    };

    GPIO_PinWrite(lcd.rst_pin, GPIO_LOW);
    vTaskDelay(10);
    GPIO_PinWrite(lcd.rst_pin, GPIO_HIGH);
    vTaskDelay(100);
    GPIO_PinWrite(lcd.bla_pin, GPIO_LOW);
    vTaskDelay(10);

    GPIO_PinWrite(lcd.dc_pin, GPIO_LOW);
    GPIO_PinWrite(lcd.cs_pin, GPIO_LOW);
    SPI_Transfer(lcd.handler,config_buffer,NULL,sizeof(config_buffer));
    GPIO_PinWrite(lcd.cs_pin, GPIO_HIGH);

    vTaskDelay(10);
    return 0;
}
void    LCD_draw_point  (int x, int y, LCD_COLOR color)
{
    uint8_t *p = lcd.lcd_buffer + x/2 + 120*y;
    if(color == LCD_COLOR_BLACK)
        *p |= 0xf << ((x%2) * 4);
    else
        *p &= 0xff ^ (0xf << ((x%2) * 4));
}
void    LCD_draw_hline  (int x, int y, int length, LCD_COLOR color)
{
    int i;
    for(i=0;i<length;i++){
        LCD_draw_point(x+i,y,color);
    }
}
void    LCD_draw_vline  (int x, int y, int length, LCD_COLOR color)
{
    int i;
    for(i=0;i<length;i++){
        LCD_draw_point(x,y+i,color);
    }
}
void    LCD_draw_rect   (int x, int y, int height, int width, LCD_COLOR color)
{

}
void    LCD_print       ( void )
{
    GPIO_PinWrite(lcd.dc_pin, GPIO_HIGH);
    GPIO_PinWrite(lcd.cs_pin, GPIO_LOW);
    SPI_Transfer(lcd.handler, lcd.lcd_buffer, NULL, 15360);
    GPIO_PinWrite(lcd.cs_pin, GPIO_HIGH);
}