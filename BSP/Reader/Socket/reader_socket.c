#include <features.h>
//
// Created by bleppe on 27/04/23.
//

#include "reader_socket.h"
#include "core/net.h"
#include "core/socket.h"


_Noreturn void reader_socket_task(void *params)
{
    Socket *sock = socketOpen(SOCKET_TYPE_STREAM, SOCKET_IP_PROTO_TCP);
    socketBind(sock, &IP_ADDR_ANY, 1236);
    socketListen(sock, 1);
    while(1){
        Socket *remote = socketAccept(sock, NULL, NULL);
        char buffer[128];
        if(remote){
            for(;;){
                size_t len;
                socketReceive(remote, buffer, 128, &len, 0);
                socketSend(remote, "Recibido: ", 10, NULL, 0);
                socketSend(remote, buffer, len, NULL, 0);
            }
        }

    }
}