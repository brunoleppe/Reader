//
// Created by bruno on 13/05/23.
//

#include "LabelItem.h"

const char *LabelItem::get_cstring() {
    return s.c_str();
}

LabelItem::LabelItem(int index, const char *s) : Item(index), s(s){}
