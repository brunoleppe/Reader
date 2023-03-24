//
// Created by bleppe on 24/03/23.
//

#include "debug.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

static UART_Channel  channel_;
static uint8_t buffer[256];
void debug_init(UART_Channel channel)
{
    channel_ = channel;
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
