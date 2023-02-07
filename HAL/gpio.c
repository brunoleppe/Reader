
/**********************************************************************
* Includes
**********************************************************************/
#include "gpio.h"
#include <xc.h>
#include "pic32mz_registers.h"

/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/
#define GPIO_BASE_PORT          (GPIO_Descriptor)&ANSELA
#define GPIO_DESCRIPTOR(port)   (GPIO_Descriptor)(((uint8_t*)&ANSELA)+0x100*(port))
/*********************************************************************
* Module Preprocessor Macros
**********************************************************************/


/**********************************************************************
* Module Typedefs
**********************************************************************/

/**********************************************************************
* Module Variable Definitions
**********************************************************************/
static const GPIO_Descriptor ports[]={
        (GPIO_Descriptor)&ANSELA,
        (GPIO_Descriptor)&ANSELB,
        (GPIO_Descriptor)&ANSELC,
        (GPIO_Descriptor)&ANSELD,
        (GPIO_Descriptor)&ANSELE,
        (GPIO_Descriptor)&ANSELF,
        (GPIO_Descriptor)&ANSELG
};
/**********************************************************************
* Function Prototypes
**********************************************************************/

/**********************************************************************
* Function Definitions
**********************************************************************/
//void GPIO_output_mapping(GPIO_PIN pin, GPIO_ALTERNATE_FUNCTION alternate_unction)
//{
//    int portNumber = pin >> 4;
//    volatile uint32_t *reg = ppsinit + (16 * portNumber) + (pin & 0x0f);
//    *reg = alternate_unction;
//}
void    GPIO_pin_initialize             (uint32_t pin, int flags)
{
//    GPIO_Descriptor port = GPIO_DESCRIPTOR((pin >> GPIO_PORT_SHIFT));
    uint32_t pins = 1 << (pin & 0xf);

    if(flags & GPIO_ANALOG) {
        ports[pin>>GPIO_PORT_SHIFT]->ansel.set = pins;
        return;
    }

    ports[pin>>GPIO_PORT_SHIFT]->ansel.clr = pins;
    if(flags & GPIO_OUTPUT){
        ports[pin>>GPIO_PORT_SHIFT]->tris.clr = pins;
        if(flags & GPIO_OPENDRAIN)
            ports[pin>>GPIO_PORT_SHIFT]->odc.set = pins;
        if(flags & GPIO_SLOWEST) {
            ports[pin>>GPIO_PORT_SHIFT]->srcon0.set = pins;
            ports[pin>>GPIO_PORT_SHIFT]->srcon1.set = pins;
        }
        else if(flags & GPIO_SLOW) {
            ports[pin>>GPIO_PORT_SHIFT]->srcon0.clr = pins;
            ports[pin>>GPIO_PORT_SHIFT]->srcon1.set = 1;
        }
        else if(flags & GPIO_FAST) {
            ports[pin>>GPIO_PORT_SHIFT]->srcon0.set = pins;
            ports[pin>>GPIO_PORT_SHIFT]->srcon1.clr = pins;
        }
        return;
    }

    if(flags & GPIO_PULLUP)
        ports[pin>>GPIO_PORT_SHIFT]->cnpu.set = pins;
    else if(flags & GPIO_PULLDOWN)
        ports[pin>>GPIO_PORT_SHIFT]->cnpd.set = pins;

    if(flags & GPIO_IRQ) {
        ports[pin>>GPIO_PORT_SHIFT]->cnen.set = pins;
        ports[pin>>GPIO_PORT_SHIFT]->cncon.set = _CNCONA_ON_MASK;
    }
}
void    GPIO_pin_deinitialize           (uint32_t pin)
{
//    GPIO_Descriptor port = GPIO_DESCRIPTOR((pin >> GPIO_PORT_SHIFT));
    uint32_t pins = 1 << (pin & 0xf);
    ports[pin>>GPIO_PORT_SHIFT]->ansel.set = pins;
    ports[pin>>GPIO_PORT_SHIFT]->tris.set = pins;
    ports[pin>>GPIO_PORT_SHIFT]->lat.clr = pins;
    ports[pin>>GPIO_PORT_SHIFT]->port.clr = pins;
    ports[pin>>GPIO_PORT_SHIFT]->srcon1.clr = pins;
    ports[pin>>GPIO_PORT_SHIFT]->srcon0.clr = pins;
    ports[pin>>GPIO_PORT_SHIFT]->cnpd.clr = pins;
    ports[pin>>GPIO_PORT_SHIFT]->cnpu.clr = pins;
    ports[pin>>GPIO_PORT_SHIFT]->odc.clr = pins;
    ports[pin>>GPIO_PORT_SHIFT]->cnen.clr = pins;
    if((ports[pin>>GPIO_PORT_SHIFT]->cnen.reg & pins) == 0)
        ports[pin>>GPIO_PORT_SHIFT]->cncon.clr = _CNCONA_ON_MASK;
}
bool    GPIO_pin_read              (uint32_t pin)
{
//    GPIO_Descriptor port = GPIO_DESCRIPTOR((pin >> GPIO_PORT_SHIFT));
    uint32_t pins = 1 << (pin & 0xf);
    return (ports[pin>>GPIO_PORT_SHIFT]->port.reg & pins) == pins;
}
void    GPIO_pin_write             (uint32_t pin, bool value)
{
//    GPIO_Descriptor port = GPIO_DESCRIPTOR((pin >> GPIO_PORT_SHIFT));
    uint32_t pins = 1 << (pin & 0xf);
    if(value){
        ports[pin>>GPIO_PORT_SHIFT]->lat.set = pins;
    }
    else{
        ports[pin>>GPIO_PORT_SHIFT]->lat.clr = pins;
    }
}
void    GPIO_pin_toggle            (uint32_t pin)
{
//    GPIO_Descriptor port = GPIO_DESCRIPTOR((pin >> GPIO_PORT_SHIFT));
    uint32_t pins = 1 << (pin & 0xf);
    ports[pin>>GPIO_PORT_SHIFT]->lat.inv = pins;
}
void    GPIO_pin_interrupt_set     (uint32_t pin, bool state)
{

}
