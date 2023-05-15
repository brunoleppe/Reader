//
// Created by bruno on 13/05/23.
//

#ifndef LCDTEST_BITMAP_H
#define LCDTEST_BITMAP_H

#include <cstdint>

class Bitmap {
public:
    uint8_t *bitmap = nullptr;
    int width;
    int height;

    Bitmap(uint8_t *bitmap, int width, int height);
};


#endif //LCDTEST_BITMAP_H
