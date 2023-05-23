//
// Created by bruno on 17/05/23.
//

#ifndef LCDTEST_STATEINPUTTEST2_H
#define LCDTEST_STATEINPUTTEST2_H


#include "MVC/States/StateInput.h"

class StateInputTest2 : public StateInput{
public:
    Status on_event(StateEvent *evt) override;
};


#endif //LCDTEST_STATEINPUTTEST2_H
