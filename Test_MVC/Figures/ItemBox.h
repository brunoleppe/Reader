//
// Created by bleppe on 11/05/23.
//

#ifndef LCDTEST_ITEMBOX_H
#define LCDTEST_ITEMBOX_H

#include <vector>
#include <string>
#include "Figure.h"
#include "Test_MVC/DataTypes/Item.h"
#include "Test_MVC/DataTypes/ItemList.h"

class ItemBox : public Figure{
protected:
public:
    ItemList *items = nullptr;
    ItemBox(int x, int y, int width, int height, uint8_t back, uint8_t fore);
    ~ItemBox() override;
    void add(Item* i);
    void clear();
};



class ListItemBox : public ItemBox{
public:
    void draw() override;
    void add(ItemList& items);
    ListItemBox(int x, int y, int width, int height, uint8_t back, uint8_t fore);

    void focus(int i);
    void focus_next();
    void focus_prev();


private:
    int count;
    int maxItemsInView;
    int startIndex;
};

#endif //LCDTEST_ITEMBOX_H
