//
// Created by bleppe on 10/05/23.
//

#ifndef LCDTEST_MODELSTATESERVICE_H
#define LCDTEST_MODELSTATESERVICE_H

#include "Model.h"

class ModelStateService : public StateMachine {

public:

    bool on_event(ControllerInputEvent& evt){
        return ((Model *) state)->on_event(evt);
    }
    MessagePacket* get_data(){
        return ((Model*)state)->get_data();
    }
};


#endif //LCDTEST_MODELSTATESERVICE_H
