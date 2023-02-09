
/**********************************************************************
* Includes
**********************************************************************/
#include "gpio.h"
#include <xc.h>
#include "pic32mz_registers.h"
#include "evic.h"
#include "gpio_config.h"

/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/
#define GPIO_BASE_PORT                  (GPIO_Descriptor)&ANSELA
#define GPIO_PORT(port)                 ((GPIO_Descriptor)(((uint8_t*)&ANSELA)+0x100*(port)))
#define GPIO_PORT_IRQ_CHANNEL(port)     (EVIC_CHANNEL_CHANGE_NOTICE_A+(port))
/*********************************************************************
* Module Preprocessor Macros
**********************************************************************/


/**********************************************************************
* Module Typedefs
**********************************************************************/

/**********************************************************************
* Module Variable Definitions
**********************************************************************/

/**********************************************************************
* Function Prototypes
**********************************************************************/

/**********************************************************************
* Function Definitions
**********************************************************************/
void    GPIO_pin_initialize             (uint32_t pin, int flags)
{

    if(flags & GPIO_ANALOG) {
        GPIO_PORT(pin>>GPIO_PORT_SHIFT)->ansel.set = pin;
        return;
    }

    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->ansel.clr = pin;
    if(flags & GPIO_OUTPUT){
        GPIO_PORT(pin>>GPIO_PORT_SHIFT)->tris.clr = pin;
        if(flags & GPIO_OPENDRAIN)
            GPIO_PORT(pin>>GPIO_PORT_SHIFT)->odc.set = pin;
        if(flags & GPIO_SLOWEST) {
            GPIO_PORT(pin>>GPIO_PORT_SHIFT)->srcon0.set = pin;
            GPIO_PORT(pin>>GPIO_PORT_SHIFT)->srcon1.set = pin;
        }
        else if(flags & GPIO_SLOW) {
            GPIO_PORT(pin>>GPIO_PORT_SHIFT)->srcon0.clr = pin;
            GPIO_PORT(pin>>GPIO_PORT_SHIFT)->srcon1.set = pin;
        }
        else if(flags & GPIO_FAST) {
            GPIO_PORT(pin>>GPIO_PORT_SHIFT)->srcon0.set = pin;
            GPIO_PORT(pin>>GPIO_PORT_SHIFT)->srcon1.clr = pin;
        }
        return;
    }

    if(flags & GPIO_PULLUP)
        GPIO_PORT(pin>>GPIO_PORT_SHIFT)->cnpu.set = pin;
    else if(flags & GPIO_PULLDOWN)
        GPIO_PORT(pin>>GPIO_PORT_SHIFT)->cnpd.set = pin;

    if(flags & GPIO_IRQ) {
        GPIO_PORT(pin>>GPIO_PORT_SHIFT)->cnen.set = pin;
        GPIO_PORT(pin>>GPIO_PORT_SHIFT)->cncon.set = _CNCONA_ON_MASK;
    }
}
void    GPIO_pin_deinitialize           (uint32_t pin)
{

    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->ansel.set = pin;
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->tris.set = pin;
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->lat.clr = pin;
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->port.clr = pin;
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->srcon1.clr = pin;
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->srcon0.clr = pin;
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->cnpd.clr = pin;
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->cnpu.clr = pin;
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->odc.clr = pin;
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->cnen.clr = pin;
    if((GPIO_PORT(pin>>GPIO_PORT_SHIFT)->cnen.reg & pin) == 0)
        GPIO_PORT(pin>>GPIO_PORT_SHIFT)->cncon.clr = _CNCONA_ON_MASK;
}
bool    GPIO_pin_read              (uint32_t pin)
{

    return (GPIO_PORT(pin>>GPIO_PORT_SHIFT)->port.reg & pin) == pin;
}
void    GPIO_pin_write             (uint32_t pin, bool value)
{

    if(value){
        GPIO_PORT(pin>>GPIO_PORT_SHIFT)->lat.set = pin;
    }
    else{
        GPIO_PORT(pin>>GPIO_PORT_SHIFT)->lat.clr = pin;
    }
}
void    GPIO_pin_toggle            (uint32_t pin)
{
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->lat.inv = pin;
}
void    GPIO_pin_interrupt_set     (uint32_t pin, bool state)
{

}

HAL_WEAK_FUNCTION void    GPIO_pin_interrupt_callback     (uint32_t pin)
{
    (void)pin;
}

void GPIO_interrupt_handler(uint32_t port)
{
    uint32_t status;

    status  = GPIO_PORT(port)->cnstat.reg;
    status &= GPIO_PORT(port)->cnen.reg;

    GPIO_PORT(port)->port.reg;

    EVIC_channel_pending_clear(GPIO_PORT_IRQ_CHANNEL(port));
    GPIO_pin_interrupt_callback(status);
}