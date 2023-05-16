//
// Created by bruno on 13/05/23.
//

#ifndef LCDTEST_BITMAPITEM_H
#define LCDTEST_BITMAPITEM_H

#include "Item.h"
#include "Bitmap.h"

class BitmapItem : public Item{
public:
    uint8_t *bitmap = nullptr;
    int x;
    int y;
    int width;
    int height;
    explicit BitmapItem(int index, uint8_t *bitmap, int x, int y, int width, int height);
};


#endif //LCDTEST_BITMAPITEM_H
