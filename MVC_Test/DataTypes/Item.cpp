//
// Created by bruno on 11/05/23.
//

#include "Item.h"

int Item::get_index() const {
    return index;
}

bool Item::get_selected() const {
    return selected;
}

Item::~Item() = default;

