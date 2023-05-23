//
// Created by bruno on 17/05/23.
//

#ifndef LCDTEST_STATEINPUTTEST1_H
#define LCDTEST_STATEINPUTTEST1_H


#include "MVC/States/StateInput.h"

class StateInputTest1 : public StateInput{
public:
    Status on_event(StateEvent *evt) override;
};


#endif //LCDTEST_STATEINPUTTEST1_H
