//
// Created by bleppe on 24/03/23.
//

#ifndef READER_DEBUG_H
#define READER_DEBUG_H

#ifdef HAL_DEBUG
    #define DEBUG_INIT(channel)     debug_init(channel)
#else
    #define DEBUG_INIT(channel)
#endif

#ifdef HAL_DEBUG
    #define DEBUG_PRINT(...)     debug_printf(__VA_ARGS__)
#else
    #define DEBUG_PRINT(...)
#endif


#include "uart.h"
#ifdef __cplusplus
extern "C"{
#endif

void debug_init(UART_Channel channel);

void debug_write(void *buffer, size_t len);

void debug_write_string(char *s);

void debug_printf(const char *fmt, ...);

#ifdef __cplusplus
}
#endif
#endif //READER_DEBUG_H
