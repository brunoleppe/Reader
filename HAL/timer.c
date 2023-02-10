
/**********************************************************************
* Includes
**********************************************************************/
#include "timer.h"
#include "pic32mz_registers.h"
#include "evic.h"
#include <xc.h>
/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/
#define TMR_BASE                            _TMR2_BASE_ADDRESS
#define TMR_NUMBER_OF_CHANNELS              (8)

/**********************************************************************
* Module Preprocessor Macros
**********************************************************************/
#define TMR_DESCRIPTOR(channel)             ((TMR_Descriptor)(((uint8_t*)(TMR_BASE)) + 0x200*(channel)))
/**********************************************************************
* Module Typedefs
**********************************************************************/

/*********************************************************************
* Module Variable Definitions
**********************************************************************/
static const uint32_t prescalerTable[] = {
    1,2,4,8,16,32,64,256
};
/**********************************************************************
* Function Prototypes
**********************************************************************/
static uint16_t TMR_period_get(uint32_t frequency, uint32_t prescaler);
/**********************************************************************
* Function Definitions
**********************************************************************/
void        TMR_initialize(uint32_t channel, uint32_t flags, uint32_t frequency)
{
    TMR_DESCRIPTOR(channel)->txcon.reg = 0;
    TMR_DESCRIPTOR(channel)->txcon.set = (TIMER_TCKPS_MASK & flags) << _T1CON_TCKPS0_POSITION;
    if(flags & TIMER_GATED)
        TMR_DESCRIPTOR(channel)->txcon.set = _T2CON_TGATE_MASK;
    if(flags & TIMER_MODE_32)
        TMR_DESCRIPTOR(channel)->txcon.set = _T2CON_T32_MASK;

    TMR_DESCRIPTOR(channel)->tmrx.reg = 0;
    TMR_DESCRIPTOR(channel)->prx.reg = TMR_period_get(frequency, prescalerTable[TIMER_TCKPS_MASK & flags]);
}
void        TMR_start(uint32_t channel)
{
    TMR_DESCRIPTOR(channel)->tmrx.reg = 0;
    TMR_DESCRIPTOR(channel)->txcon.set = _T2CON_ON_MASK;
}
void        TMR_stop(uint32_t channel)
{
    TMR_DESCRIPTOR(channel)->txcon.clr = _T2CON_ON_MASK;
}
uint32_t    TMR_count_get(uint32_t channel)
{
    return TMR_DESCRIPTOR(channel)->tmrx.reg;
}
uint32_t    TMR_frequency_get(uint32_t channel)
{
    uint32_t pre = prescalerTable[(TMR_DESCRIPTOR(channel)->txcon.reg & _T2CON_TCKPS_MASK) >> _T2CON_TCKPS0_POSITION];
    return (HAL_TMR_PERIPHERAL_CLOCK)/((TMR_DESCRIPTOR(channel)->prx.reg + 1)*pre);
}

static uint16_t TMR_period_get(uint32_t frequency, uint32_t prescaler)
{
    uint16_t period = (HAL_TMR_PERIPHERAL_CLOCK)/(prescaler * frequency) - 1;
    return period;
}
