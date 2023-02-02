
/**********************************************************************
* Includes
**********************************************************************/
#include "gpio.h"
#include "pic32mz_registers.h"
#include <xc.h>
#include <sys/attribs.h>

/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/


/*********************************************************************
* Module Preprocessor Macros
**********************************************************************/


/**********************************************************************
* Module Typedefs
**********************************************************************/

/**********************************************************************
* Module Variable Definitions
**********************************************************************/
static volatile uint32_t * const ppsinit = &RPA14R - 14;

static GPIO_Descriptor ports[NUMBER_OF_PORTS] = {
        (GPIO_Descriptor)&ANSELA,
        (GPIO_Descriptor)&ANSELB,
        (GPIO_Descriptor)&ANSELC,
        (GPIO_Descriptor)&ANSELD,
        (GPIO_Descriptor)&ANSELE,
        (GPIO_Descriptor)&ANSELF,
        (GPIO_Descriptor)&ANSELG
};


/**
 * @brief Arreglo de interrupciones, depende de la cantidad de interrupciones
 * definidos para la aplicaci�n.
 * 
 */
static GPIO_InterruptCallback callbackArray[NUMBER_OF_INTERRUPTS];
//static int cn_interrupt_enable[NUMBER_OF_PORTS]={0,0,0,0,0,0,0};

/**********************************************************************
* Function Prototypes
**********************************************************************/

static void _register_config(MemRegister reg, uint32_t val, uint32_t compare, uint32_t bitNum);
static inline void _GPIO_port_clear(GPIO_Descriptor port, uint32_t pins);
static inline void _GPIO_port_set(GPIO_Descriptor port, uint32_t pins);

/**********************************************************************
* Function Definitions
**********************************************************************/
void GPIO_output_mapping(GPIO_PIN pin, GPIO_ALTERNATE_FUNCTION alternate_unction)
{
    int portNumber = pin >> 4;
    volatile uint32_t *reg = ppsinit + (16 * portNumber) + (pin & 0x0f);
    *reg = alternate_unction;
}

void GPIO_initialize(GPIO_Descriptor port, uint16_t pins, int flags)
{
    if(flags & _GPIO_ANALOG) {
        port->ansel.set = pins;
        return;
    }

    port->ansel.clr = pins;
    if(flags & _GPIO_OUTPUT){
        port->tris.clr = pins;
        if(flags & _GPIO_OPENDRAIN)
            port->odc.set = pins;
        if(flags & _GPIO_SLOWEST) {
            port->srcon0.set = pins;
            port->srcon1.set = pins;
        }
        else if(flags & _GPIO_SLOW) {
            port->srcon0.clr = pins;
            port->srcon1.set = 1;
        }
        else if(flags & _GPIO_FAST) {
            port->srcon0.set = pins;
            port->srcon1.clr = pins;
        }
        return;
    }

    if(flags & _GPIO_PULLUP)
        port->cnpu.set = pins;
    else if(flags & _GPIO_PULLDOWN)
        port->cnpd.set = pins;

    if(flags & _GPIO_IRQ)
        port->cnen.set = pins;
}
void GPIO_deinitialize(GPIO_Descriptor port, uint16_t pins)
{
    port->ansel.set = pins;
    port->tris.set = pins;
    port->lat.clr = pins;
    port->port.clr = pins;
    port->srcon1.clr = pins;
    port->srcon0.clr = pins;
    port->cnpd.clr = pins;
    port->cnpu.clr = pins;
    port->odc.clr = pins;
}
void GPIO_port_write(GPIO_Descriptor port, WORD value, int pins)
{
    _GPIO_port_clear(port,(~value) & pins);
    _GPIO_port_set(port,value & pins);
}
WORD GPIO_port_read(GPIO_Descriptor port, int pins)
{
    return port->port.reg & pins;
}
void GPIO_port_toggle(GPIO_Descriptor port, int pins)
{
    port->lat.inv = pins;
}
void GPIO_port_interrupt_set(GPIO_Descriptor port, GPIO_INTERRUPT state)
{
    if(state == GPIO_IRQ_ENABLE)
        port->cncon.set = _CNCONA_ON_MASK;
    else
        port->cncon.clr = _CNCONA_ON_MASK;
}

void GPIO_CallbackRegister(
        GPIO_PIN pin,
        GPIO_CallbackFunction callback,
        uintptr_t context
)
{
    static int counter = 0;
    if(counter >= NUMBER_OF_INTERRUPTS)
        return;

    callbackArray[counter].callback = callback;
    callbackArray[counter].context = context;
    callbackArray[counter].pin = pin;

    counter++;
}

static inline void _GPIO_port_clear(GPIO_Descriptor port, uint32_t pins)
{
    port->lat.clr = pins;
}
static inline void _GPIO_port_set(GPIO_Descriptor port, uint32_t pins)
{
    port->lat.set = pins;
}

void _register_config(MemRegister reg, uint32_t val, uint32_t compare, uint32_t bitNum){
    if(val == compare)
        reg->set = bitNum;
    else
        reg->clr = bitNum;
}