//
// Created by bruno on 28/01/23.
//

#include <xc.h>
#include "hal_delay.h"

static const uint32_t _usec = (HAL_SYSTEM_CLOCK/2)*MICRO_SECONDS;
static const uint32_t _msec = (HAL_SYSTEM_CLOCK/2)*MILI_SECONDS;

void HAL_delay_ms(uint32_t ms)
{
    uint32_t t_wait = _msec * ms;
    uint32_t t_start = _CP0_GET_COUNT();
    t_start=_CP0_GET_COUNT();
    while((_CP0_GET_COUNT()-t_start)<t_wait);
}
void HAL_delay_us(uint32_t us)
{
    uint32_t t_wait = _usec * us;
    uint32_t t_start = _CP0_GET_COUNT();
    t_start=_CP0_GET_COUNT();
    while((_CP0_GET_COUNT()-t_start)<t_wait);
}
void HAL_delay_cy(uint32_t cy)
{
    uint32_t tStart;
    tStart=_CP0_GET_COUNT();
    while((_CP0_GET_COUNT()-tStart)<cy);
}