//
// Created by bleppe on 09/05/23.
//

#ifndef LCDTEST_TEXTBOX_H
#define LCDTEST_TEXTBOX_H


#include "Composite.h"
#include "Figure.h"
#include "Label.h"
#include "Box.h"



class TextBox : public Composite{
public:
    TextBox(int x, int y, int width, int height, uint8_t back, uint8_t fore, const char *str, LCD_Fonts font);
    TextBox(int x, int y, int width, int height, uint8_t back, uint8_t fore, const char *str, LCD_Fonts font, TextAlignment align);
    TextBox(int x, int y, int width, int height, uint8_t back, uint8_t fore, const char *str, LCD_Fonts font, TextAlignment align, bool border);
    void set_text(const char *str);
    void align_text(TextAlignment);
private:
    TextAlignment alignment;
    Box box;
    Label label;
};


#endif //LCDTEST_TEXTBOX_H
