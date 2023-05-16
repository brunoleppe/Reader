//
// Created by bruno on 14/05/23.
//

#include "LogoItem.h"

LogoItem::LogoItem(int index, int x, int y, int width, int height, uint8_t *bitmap) :
        Item(index), x(x), y(y), width(width), height(height), bitmap(bitmap) {}
