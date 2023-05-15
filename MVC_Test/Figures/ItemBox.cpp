//
// Created by bleppe on 11/05/23.
//

#include "ItemBox.h"
#include "DataTypes/LabelItem.h"

ItemBox::~ItemBox() = default;

void ItemBox::add(Item *i) {
    items->add(i);
}

ItemBox::ItemBox(int x, int y, int width, int height, uint8_t back, uint8_t fore) :
        Figure(x, y, width, height, back, fore)
{}

void ItemBox::clear() {
    items->clear();
}

void ListItemBox::draw() {
    if(items == nullptr)
        return;

    int startPos = y;
    int limit = (int)items->size() > maxItemsInView ? maxItemsInView : (int)items->size();
    for( int i=0; i<limit; i++){
        LabelItem *item = (LabelItem*)(*items)[i];
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

void ListItemBox::add(ItemList& _items) {
    items = &_items;
    count = (int)_items.size();
}

void ListItemBox::focus(int _index) {
    if(items == nullptr)
        return;
    for(auto item : items->items){
        if(item->get_index() == _index){
            item->set_focus(true);
            items->set_current(_index);
            continue;
        }
        item->set_focus(false);
    }
}

void ListItemBox::focus_next() {
    items->move_up();
    focus(items->get_current()->get_index());
}

void ListItemBox::focus_prev() {
    items->move_down();
    focus(items->get_current()->get_index());
}
