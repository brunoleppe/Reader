#ifndef LCD_H
#define LCD_H
/**********************************************************************
* Includes
**********************************************************************/
#include "spi.h"
#include "gpio.h"
/**********************************************************************
* Preprocessor Constants
**********************************************************************/

/**********************************************************************
* Typedefs
**********************************************************************/
typedef enum{
    LCD_FONT_EXTRA_SMALL = 0,
    LCD_FONT_SMALL,
    LCD_FONT_MEDIUM,
}LCD_Fonts;
/**********************************************************************
* Function Prototypes
**********************************************************************/
typedef enum{
    LCD_COLOR_BLACK = 0xF,
    LCD_COLOR_GRAY  = 7,
    LCD_COLOR_WHITE = 0,
}LCD_COLOR;
#ifdef __cplusplus
extern "C"{
#endif
int     LCD_init        (SPI_Handler handler, GPIO_PIN cs, GPIO_PIN bla, GPIO_PIN dc, GPIO_PIN rst);
void    LCD_draw_point  (int x, int y, LCD_COLOR color);
void    LCD_draw_hline  (int x, int y, int length, LCD_COLOR color);
void    LCD_draw_vline  (int x, int y, int length, LCD_COLOR color);
void    LCD_draw_rect   (int x, int y, int height, int width, LCD_COLOR color);
void    LCD_draw_fill   (int x, int y, int height, int width, LCD_COLOR color);
void    LCD_draw_char   (int x, int y, char c, LCD_Fonts font, LCD_COLOR color);
void    LCD_draw_string (int x, int y, char *str, LCD_Fonts font, LCD_COLOR color);
void    LCD_draw_bitmap (int x, int y, const uint8_t *bitmap, size_t bitmap_size);
void    LCD_print       ( void );
#ifdef __cplusplus
}
#endif
#endif //LCD_H
