//
// Created by bruno on 13/05/23.
//

#ifndef LCDTEST_BITMAPITEM_H
#define LCDTEST_BITMAPITEM_H

#include "Item.h"
#include "Bitmap.h"

class BitmapItem : public Item{
public:
    Bitmap bmp;
    explicit BitmapItem(int index, uint8_t *bitmap, int width, int height);
};


#endif //LCDTEST_BITMAPITEM_H
