#include <features.h>
//
// Created by bleppe on 27/04/23.
//

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef READER_READER_SOCKET_H
#define READER_READER_SOCKET_H


_Noreturn void tcp_port_task(void *params);

#ifdef __cplusplus
extern "C"{
#endif

bool tcp_port_is_connected(void);

size_t tcp_port_send(uint8_t *buffer, size_t size);

size_t tcp_port_recv(uint8_t *buffer, size_t size);

#ifdef __cplusplus
}
#endif

#endif //READER_READER_SOCKET_H
