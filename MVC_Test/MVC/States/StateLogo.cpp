//
// Created by bleppe on 15/05/23.
//

#include <cstring>
#include "StateLogo.h"
#include "DataTypes/LogoItem.h"
#include "linux_keys.h"

bool StateLogo::on_event(ControllerInputEvent &evt) {
    static bool flag = false;
    if(evt.code == CONTROL_TYPE_TICK){
        if(!flag) {
            memset(StateLogo::instance.bmp, 0xF0, 800);
        }
        else{
            memset(StateLogo::instance.bmp, 0xFF, 800);
        }
        flag = !flag;
        return true;
    }
    return false;
}

StateLogo::StateLogo() {
    data.title = "";
    data.messageType = MESSAGE_TYPE_LOGO;
}

void StateLogo::on_enter() {
    bmp = new uint8_t[800];
    memset(bmp,0xFF,800);

    data.items.add(new LogoItem(0,20,20,40,20,bmp));
    timer = xTimerCreate("",2000,true,nullptr,StateLogo::timer_callback);
    xTimerStart(timer,0);
}

void StateLogo::on_exit() {
    xTimerStop(timer,0);
    xTimerDelete(timer,0);
    data.items.clear();
    delete bmp;
}

void StateLogo::timer_callback(TimerHandle_t timer) {
    input_report_key(KEY_F3, INPUT_EVENT_CLICKED);
}

StateLogo StateLogo::instance;