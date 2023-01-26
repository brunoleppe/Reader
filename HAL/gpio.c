
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

GPIO_Descriptor ports[NUMBER_OF_PORTS] = {
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
static void _interrupt_handler(int portNumber);

/**********************************************************************
* Function Definitions
**********************************************************************/

void GPIO_Init(const GPIO_Config* config)
{
//    int i;
//    /* Unlock system for PPS configuration */
//
//    for(i=0;i<config->tableSize;i++){
//        /*Obtener el puerto desde el valor del pin*/
//        int portNumber = config->table[i].pin >> 4;
//        int bitNum = 1<<(config->table[i].pin&0xf);
//
//        GPIO_Descriptor portx = ports[portNumber];
//
//        /*Configuraci�n de modo anal�gico-digital*/
//        _register_config((MemRegister)&portx->ansel,config->table[i].direction,GPIO_ANALOG,bitNum);
//
//        /*Configuraci�n de direcci�n del pin*/
//        _register_config((MemRegister)&portx->tris,config->table[i].direction,GPIO_INPUT,bitNum);
//
//        /*Valor inicial del pin*/
//        _register_config((MemRegister)&portx->lat,config->table[i].state,GPIO_HIGH,bitNum);
//
//        /*pullup condifuration*/
//        _register_config((MemRegister)&portx->cnpu,config->table[i].pullup,true,bitNum);
//
//        /*pulldown configuration*/
//        _register_config((MemRegister)&portx->cnpd,config->table[i].pulldown,true,bitNum);
//
//        /*irq configuration*/
//        _register_config((MemRegister)&portx->cnen,config->table[i].irqState,true,bitNum);
//        if(config->table[i].irqState){
//            if( (portx->cncon.reg & _CNCONA_ON_MASK) == 0 ){
//                portx->cncon.set = _CNCONA_ON_MASK;
//            }
//        }


//    }

//    /*Remapeo de pines*/
//
//    /*Desbloquear sistema para remapeo*/
//    SYSKEY = 0x00000000;
//    SYSKEY = 0xAA996655;
//    SYSKEY = 0x556699AA;
//    CFGCONbits.IOLOCK = 0;
//
//    /*Configurar registros*/
//    for(i=0;i<config->tableSize;i++){
//        if(config->table[i].mode.function != AF_NONE)
//            *(volatile uint32_t*)(0xBF800000+(config->table[i].mode.reg&0xFFFF)) =
//                    config->table[i].mode.function;
//    }
//
//    /*Bloquear sistema*/
//    CFGCONbits.IOLOCK = 1;
//    SYSKEY = 0x00000000;
}
void GPIO_PortDirectionSet(GPIO_PORT port, WORD mask, GPIO_DIRECTION direction)
{
    if(direction == GPIO_OUTPUT)
        ports[port]->tris.clr = mask;
    else
        ports[port]->tris.set = mask;
}
void GPIO_PortWrite(GPIO_PORT port, WORD mask, WORD value)
{
    ports[port]->lat.reg = mask & value;
}
WORD GPIO_PortRead(GPIO_PORT port, WORD mask)
{
    return ports[port]->port.reg & mask;
}
void GPIO_PinPullupSet(GPIO_PIN pin, GPIO_PULLUP state)
{
    int portNumber = pin >> 4;
    int bitNum = 1 << ( pin & 0xf );
    _register_config((MemRegister)&ports[portNumber]->cnpu,state,true,bitNum);
}

void GPIO_PinPulldownSet(GPIO_PIN pin, GPIO_PULLDOWN state)
{
    int portNumber = pin >> 4;
    int bitNum = 1 << ( pin & 0xf );
    _register_config((MemRegister)&ports[portNumber]->cnpd,state,true,bitNum);
}

void GPIO_PinIrqSet(GPIO_PIN pin, GPIO_INTERRUPT state)
{
    int portNumber = pin >> 4;
    int bitnum = 1 << ( pin & 0xf );
    /*Enable or disable interrupt for desired pin*/
    _register_config((MemRegister)&ports[portNumber]->cnen,state,true,bitnum);

    if(!state){
        if(ports[portNumber]->cnen.reg == 0){
            /*Clear cncon register only if no interrupts are enabled for anymore pins*/
            ports[portNumber]->cncon.clr = _CNCONA_ON_MASK;
        }
    }
    else{
        /*Enable interrupt*/
        ports[portNumber]->cncon.set = _CNCONA_ON_MASK;
    }
    ports[portNumber]->port.reg;
}

GPIO_STATE GPIO_PinRead(GPIO_PIN pin)
{
    int portNumber = pin >> 4;
    int bitNum = 1 << ( pin & 0xf );
    WORD status = ports[portNumber]->port.reg;
    if(status & bitNum)
        return GPIO_HIGH;
    else
        return GPIO_LOW;
}

void GPIO_PinWrite(GPIO_PIN pin, GPIO_STATE state){
    int portNumber = pin >> 4;
    int bitNum = 1 << ( pin & 0xf );
    if(state == GPIO_HIGH)
        ports[portNumber]->lat.set = bitNum;
    else
        ports[portNumber]->lat.clr = bitNum;
}

void GPIO_PinToggle(GPIO_PIN pin)
{
    int portNumber = pin >> 4;
    int bitNum = 1 << ( pin & 0xf );
    ports[portNumber]->lat.inv = bitNum;
}

void GPIO_PinDirectionSet(GPIO_PIN pin, GPIO_DIRECTION direction)
{
    int portNumber = pin >> 4;
    int bitNum = 1 << ( pin & 0xf );
    if(direction == GPIO_INPUT)
        ports[portNumber]->tris.set = bitNum;
    else
        ports[portNumber]->tris.clr = bitNum;
}

void GPIO_RegisterWrite(uintptr_t address, WORD val)
{
    volatile WORD *reg = (volatile WORD*)address;
    *reg = val;
}

WORD GPIO_RegisterRead(uintptr_t address)
{
    volatile WORD *reg = (volatile WORD*)address;
    return *reg;
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


void _register_config(MemRegister reg, uint32_t val, uint32_t compare, uint32_t bitNum){
    if(val == compare)
        reg->set = bitNum;
    else
        reg->clr = bitNum;
}

void _interrupt_handler(int portNumber)
{
    WORD status = ports[portNumber]->cnstat.reg;
    status &= ports[portNumber]->cnen.reg;
    ports[portNumber]->port.reg;

    int i;
    for(i=0;i<NUMBER_OF_INTERRUPTS;i++){
        int portNum = callbackArray[i].pin >> 4;
        int bitNum = 1 << (callbackArray[i].pin & 0xf);
        if(portNum != portNumber)
            continue;
        if((status & bitNum) && (callbackArray[i].callback != NULL)){
            callbackArray[i].callback(callbackArray[i].pin,callbackArray[i].context);
        }
    }
}

/**********************************************************************
* Interrupt Handlers
**********************************************************************/
void CHANGE_NOTICE_E_InterruptHandler(void);

void
#ifndef INC_FREERTOS_H
__ISR(_CHANGE_NOTICE_E_VECTOR, ipl1SRS)
#endif
CHANGE_NOTICE_E_Handler (void)
{
    CHANGE_NOTICE_E_InterruptHandler();
}

void CHANGE_NOTICE_E_InterruptHandler(void)
{
    _interrupt_handler(GPIO_PORTE);
    IFS3CLR = _IFS3_CNEIF_MASK;
}