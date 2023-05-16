//
// Created by bleppe on 16/05/23.
//

#ifndef READER_STATELOGOS_H
#define READER_STATELOGOS_H


#include "DataTypes/StateMachine.h"

class StateLogos : public State{
public:
    Status on_event(StateEvent *evt) override;

};


#endif //READER_STATELOGOS_H
