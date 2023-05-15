//
// Created by bruno on 13/05/23.
//

#include "BitmapItem.h"


BitmapItem::BitmapItem(int index, uint8_t *bitmap, int width, int height) : Item(index) ,bmp(bitmap,width,height) {}
