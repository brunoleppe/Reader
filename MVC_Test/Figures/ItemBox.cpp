//
// Created by bleppe on 11/05/23.
//

#include "ItemBox.h"

ItemBox::~ItemBox() = default;

void ItemBox::add(Item *i) {
    itemList->items.push_back(i);
}

ItemBox::ItemBox(int x, int y, int width, int height, uint8_t back, uint8_t fore) :
        Figure(x, y, width, height, back, fore)
{}

void ItemBox::clear() {
    itemList->items.clear();
}

void ListItemBox::draw() {
    if(itemList == nullptr)
        return;

    int startPos = y;
    int limit = (int)itemList->items.size() > maxItemsInView ? maxItemsInView : (int)itemList->items.size();
    for( int i=0; i<limit; i++){
        MenuItem *item = (MenuItem*)(itemList)->items[i];
        uint8_t fcolor = foreColor;
        uint8_t bcolor = backColor;
        if(item->get_focus()) {
            fcolor = LCD_invert_color(static_cast<LCD_COLOR>(fcolor));
            bcolor = LCD_invert_color(static_cast<LCD_COLOR>(bcolor));
        }
        LCD_draw_fill(x+2, startPos+2, 16, w - 4, static_cast<LCD_COLOR>(bcolor));
        LCD_draw_string(x+4, startPos+4, item->get_cstring(), LCD_FONT_SMALL, static_cast<LCD_COLOR>(fcolor));
        startPos += 20;
    }
}

ListItemBox::ListItemBox(int x, int y, int width, int height, uint8_t back, uint8_t fore) :
        ItemBox(x, y, width, height, back, fore)
{
    maxItemsInView = h/20;
}

void ListItemBox::add(ItemList& _items) {
    itemList = &_items;
}

void ListItemBox::focus(int _index) {
    if(itemList == nullptr)
        return;
    for(int i=0; i < itemList->items.size(); i++){
        if(i == _index){
            itemList->items[i]->set_focus(true);
            continue;
        }
        itemList->items[i]->set_focus(false);
    }
}

void ListItemBox::focus_next() {
    itemList->move_up();
    focus(itemList->get_current()->get_index());
}

void ListItemBox::focus_prev() {
    itemList->move_down();
    focus(itemList->get_current()->get_index());
}
