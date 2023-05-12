//
// Created by bruno on 11/05/23.
//

#ifndef LCDTEST_ITEM_H
#define LCDTEST_ITEM_H


#include <string>

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

class ListItem : public Item{
private:
    std::string s;
public:
    ListItem(int index, const char* s) : Item(index), s(s){}
    const char* get_cstring();
};

#endif //LCDTEST_ITEM_H
