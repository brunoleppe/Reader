//
// Created by bruno on 11/05/23.
//

#ifndef LCDTEST_ITEM_H
#define LCDTEST_ITEM_H


class Item{
protected:
    Item(int index) : selected(false), focused(selected){
        this->index = index;
    }
    int index;
    bool selected;
    bool focused;
public:
    int get_index() const;
    bool get_selected() const;
    void set_selected(bool s){
        selected = s;
    }
    void set_focus(bool f){
        focused = f;
    }
    bool get_focus(){
        return focused;
    }

    virtual ~Item();
};


#endif //LCDTEST_ITEM_H
