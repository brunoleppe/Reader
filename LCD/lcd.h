/**
 * @file lcd.h
 * @author Bruno Leppe (bruno.leppe.dev\@gmail.com)
 * @brief LCD Module.
 * This file contains the definitions and function prototypes for the LCD module, which provides functionality to draw
 * primitives onto the LCD screen.
 * @version 0.1
 * @date 2022-09-29
 *
 * @copyright (c) 2023
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
/**
 * @brief Enumeration for different font sizes.
 */
typedef enum {
    LCD_FONT_EXTRA_SMALL = 0,
    LCD_FONT_SMALL,
    LCD_FONT_MEDIUM,
} LCD_Fonts;

/**
 * @brief Structure representing the font information.
 */
typedef struct {
    uint8_t     bytes;      ///< Number of bytes per character.
    uint8_t     bpr;        ///< Number of bytes per row. Each pixel is a bit.
    int         cols;       ///< Number of columns.
    int         rows;       ///< Number of rows.
    uint8_t     *font;      ///< Pointer to the character table.
    uint8_t     *special;   ///< Pointer to the special character table.
} LCD_Font;

/**
 * @brief Enumeration for different LCD colors.
 */
typedef enum {
    LCD_COLOR_BLACK = 0xF,   ///< Black color.
    LCD_COLOR_GRAY  = 7,     ///< Gray color.
    LCD_COLOR_WHITE = 0,     ///< White color.
} LCD_COLOR;
/**********************************************************************
* Function Prototypes
**********************************************************************/
#ifdef __cplusplus
extern "C"{
#endif
/**
 * @brief Initializes the LCD screen.
 *
 * @param spiChannel  SPI channel number.
 * @param dmaChannel  DMA channel number. Not used.
 * @param cs          Chip select pin.
 * @param bla         Backlight pin.
 * @param dc          Data/command pin.
 * @param rst         Reset pin.
 *
 * @return 0 on success, non-zero on failure.
 */
int LCD_init(uint32_t spiChannel, uint32_t dmaChannel, GPIO_PinMap cs, GPIO_PinMap bla, GPIO_PinMap dc, GPIO_PinMap rst);

/**
 * @brief Configures the LCD screen.
 */
void LCD_configure();

/**
 * @brief Draws a point on the LCD screen.
 *
 * @param x      X-coordinate of the point.
 * @param y      Y-coordinate of the point.
 * @param color  Color of the point.
 */
void LCD_draw_point(int x, int y, LCD_COLOR color);

/**
 * @brief Draws a horizontal line on the LCD screen.
 *
 * @param x       X-coordinate of the starting point.
 * @param y       Y-coordinate of the starting point.
 * @param length  Length of the line.
 * @param color   Color of the line.
 */
void LCD_draw_hline(int x, int y, int length, LCD_COLOR color);

/**
 * @brief Draws a vertical line on the LCD screen.
 *
 * @param x       X-coordinate of the starting point.
 * @param y       Y-coordinate of the starting point.
 * @param length  Length of the line.
 * @param color   Color of the line.
 */
void LCD_draw_vline(int x, int y, int length, LCD_COLOR color);

/**
 * @brief Draws a rectangle on the LCD screen.
 *
 * @param x       X-coordinate of the top-left corner.
 * @param y       Y-coordinate of the top-left corner.
 * @param height  Height of the rectangle.
 * @param width   Width of the rectangle.
 * @param color   Color of the rectangle.
 */
void LCD_draw_rect(int x, int y, int height, int width, LCD_COLOR color);

/**
 * @brief Draws a filled rectangle on the LCD screen.
 *
 * @param x       X-coordinate of the top-left corner.
 * @param y       Y-coordinate of the top-left corner.
 * @param height  Height of the rectangle.
 * @param width   Width of the rectangle.
 * @param color   Color of the rectangle.
 */
void LCD_draw_fill(int x, int y, int height, int width, LCD_COLOR color);

/**
 * @brief Draws a character on the LCD screen.
 *
 * @param x      X-coordinate of the top-left corner of the character.
 * @param y      Y-coordinate of the top-left corner of the character.
 * @param c      Character to draw.
 * @param font   Font size.
 * @param color  Color of the character.
 */
void LCD_draw_char(int x, int y, char c, LCD_Fonts font, LCD_COLOR color);

/**
 * @brief Draws a string on the LCD screen.
 *
 * @param x       X-coordinate of the top-left corner of the string.
 * @param y       Y-coordinate of the top-left corner of the string.
 * @param str     String to draw.
 * @param font    Font size.
 * @param color   Color of the string.
 */
void LCD_draw_string(int x, int y, const char *str, LCD_Fonts font, LCD_COLOR color);

/**
 * @brief Draws a bitmap on the LCD screen.
 *
 * @param x        X-coordinate of the top-left corner of the bitmap.
 * @param y        Y-coordinate of the top-left corner of the bitmap.
 * @param width    Width of the bitmap.
 * @param height   Height of the bitmap.
 * @param bitmap   Pointer to the bitmap data.
 */
void LCD_draw_bitmap(int x, int y, int width, int height, const uint8_t *bitmap);

/**
 * @brief Clears the LCD screen.
 */
void LCD_clear();

/**
 * @brief Prints the LCD screen.
 */
void LCD_print();

/**
 * @brief Retrieves the font information for the specified font size.
 *
 * @param font  Font size.
 *
 * @return Pointer to the LCD_Font structure for the specified font size.
 */
const LCD_Font* LCD_get_font(LCD_Fonts font);

/**
 * @brief Inverts the specified color.
 *
 * @param color  Color to invert.
 *
 * @return Inverted color.
 */
LCD_COLOR LCD_invert_color(LCD_COLOR color);
#ifdef __cplusplus
}
#endif
#endif //LCD_H
