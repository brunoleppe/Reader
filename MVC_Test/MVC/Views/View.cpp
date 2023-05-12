//
// Created by bleppe on 11/05/23.
//

#include "View.h"

MenuView MenuView::instance;

void View::set_message(MessagePacket *_msg) {
    msg = _msg;
}
