//
// Created by bleppe on 09/05/23.
//

#ifndef LCDTEST_BOX_H
#define LCDTEST_BOX_H

#include "Figure.h"

class Box : public Figure{
public:
    Box(int x, int y, int width, int height, uint8_t back, uint8_t fore);
    void draw() override;
};


#endif //LCDTEST_BOX_H
