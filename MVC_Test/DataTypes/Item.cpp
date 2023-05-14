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

const char *MenuItem::get_cstring() {
    return s.c_str();
}

ItemList::ItemList() : currentIndex(0){

}

Item *ItemList::get_current() {
    if((int)items.size() > 0)
        return items[currentIndex];
    return nullptr;
}

void ItemList::move_up() {
    if(++currentIndex >= items.size()) {
        currentIndex = 0;
    }
}

void ItemList::move_down() {
    if(--currentIndex < 0){
        currentIndex = (int)items.size()-1;
    }
}

void ItemList::add(Item *item) {
    items.push_back(item);
}

void ItemList::remove(Item *item) {
    int index = item->get_index();
    if(index > 0 && index < items.size()){
        Item* i = items[index];
        if(i==item)
            items.erase(items.begin()+index);
    }
}

void ItemList::clear() {
    items.clear();
}

size_t ItemList::size() {
    return items.size();
}

Item *ItemList::operator[](int i) {
    return items[i];
}