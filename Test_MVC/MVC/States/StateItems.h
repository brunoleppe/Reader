//
// Created by bleppe on 16/05/23.
//

#ifndef READER_STATEITEMS_H
#define READER_STATEITEMS_H


#include "DataTypes/StateMachine.h"

class StateItems : public State{
public:
    Status on_event(StateEvent *evt) override;

};


#endif //READER_STATEITEMS_H
