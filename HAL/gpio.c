
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
    uint32_t pins = 1 << (pin & GPIO_PIN_MASK);

    if(flags & GPIO_ANALOG) {
        GPIO_PORT(pin>>GPIO_PORT_SHIFT)->ansel.set = pins;
        return;
    }

    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->ansel.clr = pins;
    if(flags & GPIO_OUTPUT){
        GPIO_PORT(pin>>GPIO_PORT_SHIFT)->tris.clr = pins;
        if(flags & GPIO_OPENDRAIN)
            GPIO_PORT(pin>>GPIO_PORT_SHIFT)->odc.set = pins;
        if(flags & GPIO_SLOWEST) {
            GPIO_PORT(pin>>GPIO_PORT_SHIFT)->srcon0.set = pins;
            GPIO_PORT(pin>>GPIO_PORT_SHIFT)->srcon1.set = pins;
        }
        else if(flags & GPIO_SLOW) {
            GPIO_PORT(pin>>GPIO_PORT_SHIFT)->srcon0.clr = pins;
            GPIO_PORT(pin>>GPIO_PORT_SHIFT)->srcon1.set = pins;
        }
        else if(flags & GPIO_FAST) {
            GPIO_PORT(pin>>GPIO_PORT_SHIFT)->srcon0.set = pins;
            GPIO_PORT(pin>>GPIO_PORT_SHIFT)->srcon1.clr = pins;
        }
        return;
    }

    if(flags & GPIO_PULLUP)
        GPIO_PORT(pin>>GPIO_PORT_SHIFT)->cnpu.set = pins;
    else if(flags & GPIO_PULLDOWN)
        GPIO_PORT(pin>>GPIO_PORT_SHIFT)->cnpd.set = pins;

    if(flags & GPIO_IRQ) {
        GPIO_PORT(pin>>GPIO_PORT_SHIFT)->cnen.set = pins;
        GPIO_PORT(pin>>GPIO_PORT_SHIFT)->cncon.set = _CNCONA_ON_MASK;
    }
}
void    GPIO_pin_deinitialize           (uint32_t pin)
{
    uint32_t pins = 1 << (pin & GPIO_PIN_MASK);
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->ansel.set = pins;
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->tris.set = pins;
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->lat.clr = pins;
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->port.clr = pins;
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->srcon1.clr = pins;
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->srcon0.clr = pins;
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->cnpd.clr = pins;
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->cnpu.clr = pins;
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->odc.clr = pins;
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->cnen.clr = pins;
    if((GPIO_PORT(pin>>GPIO_PORT_SHIFT)->cnen.reg & pins) == 0)
        GPIO_PORT(pin>>GPIO_PORT_SHIFT)->cncon.clr = _CNCONA_ON_MASK;
}
bool    GPIO_pin_read              (uint32_t pin)
{
    uint32_t pins = 1 << (pin & GPIO_PIN_MASK);
    return (GPIO_PORT(pin>>GPIO_PORT_SHIFT)->port.reg & pins) == pins;
}
void    GPIO_pin_write             (uint32_t pin, bool value)
{
    uint32_t pins = 1 << (pin & GPIO_PIN_MASK);
    if(value){
        GPIO_PORT(pin>>GPIO_PORT_SHIFT)->lat.set = pins;
    }
    else{
        GPIO_PORT(pin>>GPIO_PORT_SHIFT)->lat.clr = pins;
    }
}
void    GPIO_pin_toggle            (uint32_t pin)
{
    uint32_t pins = 1 << (pin & GPIO_PIN_MASK);
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->lat.inv = pins;
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