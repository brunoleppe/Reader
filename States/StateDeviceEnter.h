//
// Created by bleppe on 06/04/23.
//

#ifndef READER_STATEDEVICEENTER_H
#define READER_STATEDEVICEENTER_H

#include "State.h"

class StateDeviceEnter : State{
public:
    static State* get_state();
private:
    static StateDeviceEnter instance;

    void on_enter() override;

    void on_exit() override;

    void on_input(InputEvent &evt) override;
};


#endif //READER_STATEDEVICEENTER_H
