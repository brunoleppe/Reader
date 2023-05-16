//
// Created by bleppe on 10/05/23.
//

#ifndef LCDTEST_MESSAGEPACKET_H
#define LCDTEST_MESSAGEPACKET_H

#include <vector>
#include <string>
#include "Test_MVC/DataTypes/Item.h"
#include "Test_MVC/DataTypes/ItemList.h"

enum MessageType{
    MESSAGE_TYPE_LOGO,
    MESSAGE_TYPE_MENU,
    MESSAGE_TYPE_DASHBOARD,
    MESSAGE_TYPE_INPUT,
    MESSAGE_TYPE_DISPLAY,
};

class MessagePacket {
public:
    MessageType messageType;
    const char *title;
    std::vector<const char*> options;
//    std::vector<Item*> items;
    ItemList items;


    explicit MessagePacket() : messageType(MESSAGE_TYPE_MENU), title("") {}
};

#endif //LCDTEST_MESSAGEPACKET_H
