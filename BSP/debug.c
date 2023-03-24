//
// Created by bleppe on 24/03/23.
//

#include "debug.h"
#include "HAL/system.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

static UART_Channel  channel_;
static uint8_t buffer[256];
static uint8_t rxBuffer[256];
static void uart_callback(UART_Channel channel, UART_CHANNEL_EVENT event, uintptr_t context){
    UART_read(channel, rxBuffer, 256);
    if(rxBuffer[0] == 'R')
        SYS_soft_reset(0);
    UART_write_byte(channel, *rxBuffer);
}
void debug_init(UART_Channel channel)
{
    channel_ = channel;
    UART_callback_register(channel, uart_callback, 0);
    UART_read_start(channel);
}
void debug_write(void *buffer, size_t len)
{
    UART_write(channel_, (uint8_t*)buffer, len);
}
void debug_write_string(char *s)
{
    uint32_t len = strlen(s);
    UART_write(channel_, (uint8_t*)s, len);
}

void debug_printf(const char *fmt, ...)
{
    va_list list;
    va_start(list,fmt);
    int ret = vsnprintf((char*)buffer, 256, fmt, list);
    va_end(list);
    debug_write(buffer, ret);
}
