#include "tcp_port.h"
#include "core/net.h"
#include "core/socket.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "input.h"

typedef struct TcpSocket{
    Socket *socket;
    bool connected;
    uint8_t *rxBuffer;
    SemaphoreHandle_t mutex;
}TcpSocket;

static TcpSocket obj;

_Noreturn void tcp_port_task(void *params)
{
    uint8_t rxBuffer[1024];
    obj.mutex = xSemaphoreCreateMutex();
    obj.rxBuffer = rxBuffer;
    Socket *sock = socketOpen(SOCKET_TYPE_STREAM, SOCKET_IP_PROTO_TCP);
    socketBind(sock, &IP_ADDR_ANY, 1236);
    socketListen(sock, 1);
    while(1){
        Socket *remote = socketAccept(sock, NULL, NULL);
        obj.socket = remote;
        obj.connected = true;
        if(remote){
            for(;;){
                size_t len;
                error_t err = socketReceive(remote, obj.rxBuffer, 128, &len, 0);
                if(err == NO_ERROR) {
//                    socketSend(remote, "Recibido: ", 10, NULL, 0);
//                    socketSend(remote, obj.rxBuffer, len, NULL, 0);

                    if(rxBuffer[1] == 1){
                        input_report_key(rxBuffer[3], rxBuffer[4]);
                    }


                }
                else if(err == ERROR_END_OF_STREAM) {
                    obj.connected = false;
                    break;
                }
            }
        }

    }
}

bool tcp_port_is_connected( void )
{
    return obj.connected;
}

size_t tcp_port_send(uint8_t *buffer, size_t size)
{
    xSemaphoreTake(obj.mutex, portMAX_DELAY);
    size_t written = 0;
    if(obj.connected) {
        error_t res = socketSend(obj.socket, buffer, size, &written, 0);
        if (res != NO_ERROR)
            written = 0;
    }
    xSemaphoreGive(obj.mutex);
    return written;
}
size_t tcp_port_recv(uint8_t *buffer, size_t size)
{
    xSemaphoreTake(obj.mutex, portMAX_DELAY);
    size_t len = 0;
    if(obj.connected) {
        uint8_t *ptr = obj.rxBuffer;
        if (size > 1024)
            size = 1024;
        len = size;
        while (size--) {
            *buffer++ = *ptr++;
        }
    }
    xSemaphoreGive(obj.mutex);
    return len;
}