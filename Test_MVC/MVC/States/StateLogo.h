//
// Created by bleppe on 16/05/23.
//

#ifndef LCDTEST_STATELOGO_H
#define LCDTEST_STATELOGO_H


#include <cstdint>
#include "StateMachine.h"
#include "lcd.h"

class StateLogo : public State{
protected:
    uint8_t *bitmap;
public:
    StateLogo(){
        type = STATE_TYPE_LOGO;
        bitmap = new uint8_t[LCD_WIDTH * LCD_HEIGHT / 2];
    }

    Status on_event(StateEvent *evt) override{
        Status status = STATUS_IGNORED;
        if(evt->signal == EVENT_SIGNAL_EXIT){
            delete[] bitmap;
            status = STATUS_HANDLED;
        }
        return status;
    }

    uint8_t* get_bitmap(){
        return bitmap;
    }
};


#endif //LCDTEST_STATELOGO_H
