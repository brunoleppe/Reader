//
// Created by bruno on 14/05/23.
//

#ifndef LCDTEST_LOGOITEM_H
#define LCDTEST_LOGOITEM_H


#include "Item.h"
#include <cstdint>

class LogoItem : public Item {
public:

    LogoItem(int index, int x, int y, int width, int height, uint8_t *bitmap);

    int x;
    int y;
    int width;
    int height;
    uint8_t* bitmap;
};


#endif //LCDTEST_LOGOITEM_H
