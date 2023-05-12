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
#define LCD_WIDTH   240
#define LCD_HEIGHT  128
/**********************************************************************
* Typedefs
**********************************************************************/
typedef enum{
    LCD_FONT_EXTRA_SMALL = 0,
    LCD_FONT_SMALL,
    LCD_FONT_MEDIUM,
}LCD_Fonts;

typedef struct{
    uint8_t     bytes;      ///< Cantidad de bytes por caracter.
    uint8_t     bpr;        ///< Cantidad de bytes por fila. Un pixel es un bit.
    int         cols;
    int         rows;
    uint8_t     *font;      ///< Puntero a la tabla de caracteres.
    uint8_t     *special;   ///< Puntero a la tabla de caracteres especiales.
}LCD_Font;
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
int     LCD_init        (uint32_t spiChannel, uint32_t dmaChannel, GPIO_PinMap cs, GPIO_PinMap bla, GPIO_PinMap dc, GPIO_PinMap rst);
void    LCD_configure   ();
void    LCD_draw_point  (int x, int y, LCD_COLOR color);
void    LCD_draw_hline  (int x, int y, int length, LCD_COLOR color);
void    LCD_draw_vline  (int x, int y, int length, LCD_COLOR color);
void    LCD_draw_rect   (int x, int y, int height, int width, LCD_COLOR color);
void    LCD_draw_fill   (int x, int y, int height, int width, LCD_COLOR color);
void    LCD_draw_char   (int x, int y, char c, LCD_Fonts font, LCD_COLOR color);
void    LCD_draw_string (int x, int y, const char *str, LCD_Fonts font, LCD_COLOR color);
void    LCD_draw_bitmap (int x, int y, const uint8_t *bitmap, size_t bitmap_size);
void    LCD_clear       ();
void    LCD_print       ( void );
const LCD_Font* LCD_get_font(LCD_Fonts font);
LCD_COLOR LCD_invert_color(LCD_COLOR color);
#ifdef __cplusplus
}
#endif
#endif //LCD_H
