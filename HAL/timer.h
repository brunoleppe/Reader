#ifndef TIMER_H
#define TIMER_H

/**********************************************************************
* Includes
**********************************************************************/
#include "hal_defs.h"
/**********************************************************************
* Preprocessor Constants
**********************************************************************/
#define TIMER_CHANNEL_2                 (0)
#define TIMER_CHANNEL_3                 (1)
#define TIMER_CHANNEL_4                 (2)
#define TIMER_CHANNEL_5                 (3)
#define TIMER_CHANNEL_6                 (4)
#define TIMER_CHANNEL_7                 (5)
#define TIMER_CHANNEL_8                 (6)
#define TIMER_CHANNEL_9                 (7)
/**********************************************************************
* Typedefs
**********************************************************************/

/**********************************************************************
* Function Prototypes
**********************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

void        TMR_initialize(uint32_t channel, uint32_t flags, uint32_t frequency);
void        TMR_start(uint32_t channel);
void        TMR_stop(uint32_t channel);
uint32_t    TMR_count_get(uint32_t channel);
uint32_t    TMR_frequency_get(uint32_t channel);

#ifdef __cplusplus
}
#endif
#endif //TIMER_H
