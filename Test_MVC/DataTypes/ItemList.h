//
// Created by bruno on 13/05/23.
//

#ifndef LCDTEST_ITEMLIST_H
#define LCDTEST_ITEMLIST_H


#include <cstddef>
#include "Item.h"
#include "vector.h"

class ItemList{
private:
    int currentIndex;
public:
    bru::vector<Item*> items;

    ItemList();
    Item* get_current();
    void move_up();
    void move_down();
    void add(Item *item);
    void remove(Item *item);
    void clear();
    size_t size() const;
    Item* operator[](int);
    Item* get_selected();
    void set_current(int i);
};


#endif //LCDTEST_ITEMLIST_H
