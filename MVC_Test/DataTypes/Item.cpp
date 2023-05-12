//
// Created by bruno on 11/05/23.
//

#include "Item.h"

int Item::get_index() {
    return index;
}

bool Item::get_selected() {
    return selected;
}

const char *ListItem::get_cstring() {
    return s.c_str();
}
