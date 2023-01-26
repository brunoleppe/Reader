//
// Created by bruno on 25/01/23.
//

#include "system.h"
#include <xc.h>

void SYS_Lock()
{
    SYSKEY = 0x00000000;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    CFGCONbits.IOLOCK = 0;
}
void SYS_Unlock()
{
    CFGCONbits.IOLOCK = 1;
    SYSKEY = 0x00000000;
}