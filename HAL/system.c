/**********************************************************************
* Includes
**********************************************************************/
#include "system.h"
#include <xc.h>
#include "pic32mz_registers.h"
/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/
#define SYS_PBCLK_BASE                          ((uint8_t*)&PB1DIV)
/**********************************************************************
* Module Preprocessor Macros
**********************************************************************/
#define SYS_PBCLK(channel)                      ((PBCLK_Descriptor)(SYS_PBCLK_BASE + channel*0x10))
/**********************************************************************
* Module Typedefs
**********************************************************************/

/*********************************************************************
* Module Variable Definitions
**********************************************************************/

/**********************************************************************
* Function Prototypes
**********************************************************************/

/**********************************************************************
* Function Definitions
**********************************************************************/
void SYS_initialize()
{
    PRECONbits.PREFEN = 3;
    PRECONbits.PFMWS = 3;
    CFGCONbits.ECCCON = 3;
}

void SYS_Unlock()
{
    SYSKEY = 0x00000000;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    CFGCONbits.IOLOCK = 0;
}
void SYS_Lock()
{
    CFGCONbits.IOLOCK = 1;
    SYSKEY = 0x00000000;
}

void SYS_peripheral_clock_config(uint32_t clockChannel, uint32_t flags)
{
    if(clockChannel > 7)
        return;
    if((flags & SYS_PBCLK_DISABLED) && clockChannel > 1)
        SYS_PBCLK(clockChannel)->pbxdiv.clr = _PB2DIV_ON_MASK;
    
    while(!(SYS_PBCLK(clockChannel)->pbxdiv.reg & _PB1DIV_PBDIVRDY_POSITION));

}