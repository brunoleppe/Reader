//
// Created by bruno on 13/05/23.
//

#include "BitmapItem.h"


BitmapItem::BitmapItem(int index, uint8_t *bitmap, int x, int y, int width, int height)
        : Item(index), bitmap(bitmap), x(x), y(y), width(width), height(height) {}
