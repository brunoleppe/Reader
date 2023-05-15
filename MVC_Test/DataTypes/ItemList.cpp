//
// Created by bruno on 13/05/23.
//

#include "ItemList.h"

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
    for(auto item:items){
        delete item;
    }
    items.clear();
}

size_t ItemList::size() const {
    return items.size();
}

Item *ItemList::operator[](int i) {
    return items[i];
}

Item *ItemList::get_selected() {
    for(auto item : items){
        if(item->get_selected())
            return item;
    }
    return nullptr;
}

void ItemList::set_current(int i) {
    currentIndex = i;
}
