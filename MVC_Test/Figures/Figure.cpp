//
// Created by bleppe on 08/05/23.
//

#include "Figure.h"

Figure::Figure(int x, int y, uint8_t back, uint8_t fore)
        : Drawable(x,y,0,0,back,fore)
{

}
Figure::Figure(int x, int y, int width, int height, uint8_t back, uint8_t fore)
        : Drawable(x,y,width,height,back,fore)
{

}

Figure::~Figure() = default;
