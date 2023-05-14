//
// Created by bruno on 11/05/23.
//

#ifndef LCDTEST_ITEM_H
#define LCDTEST_ITEM_H


#include <string>
#include <list>
#include <vector>

class Item{
protected:
    Item(int index) : selected(false), focused(selected){
        this->index = index;
    }
    int index;
    bool selected;
    bool focused;
public:
    int get_index();
    bool get_selected();
    void set_selected(bool s){
        selected = s;
    }
    void set_focus(bool f){
        focused = f;
    }
    bool get_focus(){
        return focused;
    }
};

class ItemList{
private:
    int currentIndex;
public:
    std::vector<Item*> items;

    ItemList();
    Item* get_current();
    void move_up();
    void move_down();
    void add(Item *item);
    void remove(Item *item);
    void clear();
    size_t size();
    Item* operator[](int);

};

class MenuItem : public Item{
private:
    std::string s;
public:
    MenuItem(int index, const char* s) : Item(index), s(s){}
    const char* get_cstring();
};

#endif //LCDTEST_ITEM_H
