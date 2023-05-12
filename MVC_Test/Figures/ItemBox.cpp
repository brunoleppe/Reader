//
// Created by bleppe on 11/05/23.
//

#include "ItemBox.h"

ItemBox::~ItemBox() {
    if(items == nullptr)
        return;

    for(auto i : *items)
        delete i;
}

void ItemBox::add(Item *i) {
    items->push_back(i);
}

ItemBox::ItemBox(int x, int y, int width, int height, uint8_t back, uint8_t fore) :
        Figure(x, y, width, height, back, fore)
{}

void ItemBox::clear() {
    if(items == nullptr)
        return;

    while(!items->empty()){
        items->pop_back();
    }

}

void ListItemBox::draw() {
    if(items == nullptr)
        return;

    int startPos = y;
    int limit = (int)items->size() > maxItemsInView ? maxItemsInView : (int)items->size();
    for( int i=0; i<limit; i++){
        ListItem *item = (ListItem*)(*items)[i];
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
    count = 0;
    startIndex = 0;

}

void ListItemBox::add(std::vector<Item*>& _items) {
    items = &_items;
    count = _items.size();
}

void ListItemBox::focus(int i) {
    if(items == nullptr)
        return;
    if(i < (int)items->size()){
        for(auto item : *items){
            if(item->get_index() == i){
                item->set_focus(true);
            }
            else{
                item->set_focus(false);
            }
        }
    }
}

void ListItemBox::focus_next() {
    if(++startIndex > items->size()-1)
        startIndex = 0;
    focus(startIndex);
}

void ListItemBox::focus_prev() {
    if(--startIndex < 0)
        startIndex = items->size()-1;
    focus(startIndex);
}
