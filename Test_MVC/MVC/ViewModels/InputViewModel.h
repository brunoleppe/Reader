//
// Created by bruno on 17/05/23.
//

#ifndef LCDTEST_INPUTVIEWMODEL_H
#define LCDTEST_INPUTVIEWMODEL_H


#include "MVC/States/StateInput.h"
#include "ViewModel.h"

class InputViewModel : public ViewModel{
private:
public:
    explicit InputViewModel(StateInput *state) : ViewModel(state){}

    void add_char(char a){
        if(state == nullptr)
            return;
        ((StateInput*)state)->get_string()->push_back(a);
    }

    void delete_char(){
        if(!((StateInput*)state)->get_string()->empty())
            ((StateInput*)state)->get_string()->pop_back();
    }
    bru::string* get_string(){
        return  ((StateInput*)state)->get_string();
    }
    bru::string* get_title(){
        return ((StateInput*)state)->get_title();
    }
};


#endif //LCDTEST_INPUTVIEWMODEL_H
