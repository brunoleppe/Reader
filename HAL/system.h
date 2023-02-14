//
// Created by bruno on 25/01/23.
//

#ifndef READER_SYSTEM_H
#define READER_SYSTEM_H
/**********************************************************************
* Includes
**********************************************************************/
#include "hal_defs.h"
/**********************************************************************
* Preprocessor Constants
**********************************************************************/
#define SYS_PERIPHERAL_CLOCK_1              (0)
#define SYS_PERIPHERAL_CLOCK_2              (1)
#define SYS_PERIPHERAL_CLOCK_3              (2)
#define SYS_PERIPHERAL_CLOCK_4              (3)
#define SYS_PERIPHERAL_CLOCK_5              (4)
#define SYS_PERIPHERAL_CLOCK_6              (5)
#define SYS_PERIPHERAL_CLOCK_7              (6)

/**********************************************************************
* Typedefs
**********************************************************************/
#if defined (__LANGUAGE_C__) || defined (__LANGUAGE_C_PLUS_PLUS)

/**********************************************************************
* Function Prototypes
**********************************************************************/


#ifdef __cplusplus
extern "C"{
#endif
void SYS_Unlock();
void SYS_Lock();

void SYS_peripheral_clock_config(uint32_t clockChannel, uint32_t flags);


#ifdef __cplusplus
}
#endif
#endif
#endif //READER_SYSTEM_H
