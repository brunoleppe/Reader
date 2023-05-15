//
// Created by bruno on 09/05/23.
//

#ifndef LCDTEST_MODEL_H
#define LCDTEST_MODEL_H

#include <vector>
#include <string>
#include "MessagePacket.h"
#include "StateMachine.h"


class Model : public State{
protected:
    explicit Model(){}
    MessagePacket data;

public:
    MessagePacket* get_data(){
        return &data;
    }
};

#endif //LCDTEST_MODEL_H
