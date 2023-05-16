//
// Created by bleppe on 09/05/23.
//

#include "TextBox.h"

TextBox::TextBox(int x, int y, int width, int height, uint8_t back, uint8_t fore, const char *str, LCD_Fonts font)
        : Composite(x,y,width, height), alignment(Text_Center),
        box(x, y, width, height, back, fore),
        label(x+1, y+1, back, fore, str, font)
{
    add(&box);
    add(&label);
    if(label.get_size().width > (width - 2))
        label.crop_to_width(width-2);

    align_text(alignment);
}

TextBox::TextBox(int x, int y, int width, int height, uint8_t back, uint8_t fore, const char *str, LCD_Fonts font,
        TextAlignment align) : Composite(x,y,width, height), alignment(align),
        box(x, y, width, height, back, fore),
        label(x+2, y+2, back, fore, str, font)
{
    add(&box);
    add(&label);
    if(label.get_size().width > (width - 2))
        label.crop_to_width(width-2);

    align_text(alignment);
}

TextBox::TextBox(int x, int y, int width, int height, uint8_t back, uint8_t fore, const char *str, LCD_Fonts font,
                 TextAlignment align, bool border) :
        Composite(x,y,width, height), alignment(align),
        box(x, y, width, height, back, border? fore:back),
        label(x+2, y+2, back, fore, str, font)
{
    add(&box);
    add(&label);
    if(label.get_size().width > (width - 2))
        label.crop_to_width(width-2);

    align_text(alignment);
}

void TextBox::align_text(TextAlignment align) {
    int x0 = x+2, y0 = y + (h>>1) - label.get_size().height/2;
    if(align == Text_Center){
        x0 = x + (w>>1) - label.get_size().width/2;
    }
    else if(align == Text_Right){
        x0 = x+w-label.get_size().width-2;
    }
    label.set_position(x0,y0);

}

void TextBox::set_text(const char *str) {
    label.set_text(str);
    if(label.get_size().width > (w - 2))
        label.crop_to_width(w-2);
    align_text(alignment);
}


