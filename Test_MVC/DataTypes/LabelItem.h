//
// Created by bruno on 13/05/23.
//

#ifndef LCDTEST_LABELITEM_H
#define LCDTEST_LABELITEM_H


#include "Item.h"
#include "string.h"

class LabelItem : public Item{
private:
    bru::string s;
public:
    LabelItem(int index, const char* s);
    const char* get_cstring();
};


#endif //LCDTEST_LABELITEM_H
