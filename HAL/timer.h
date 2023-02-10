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

#define TIMER_TCKPS_MASK                (0x07)

/*FLAGS*/
#define TIMER_PRESCALER_1               (0x0000)
#define TIMER_PRESCALER_2               (0x0001)
#define TIMER_PRESCALER_4               (0x0002)
#define TIMER_PRESCALER_8               (0x0003)
#define TIMER_PRESCALER_16              (0x0004)
#define TIMER_PRESCALER_32              (0x0005)
#define TIMER_PRESCALER_64              (0x0006)
#define TIMER_PRESCALER_256             (0x0007)
#define TIMER_GATED                     (0x0008)
#define TIMER_EXTERNAL_SOURCE           (0x0010)
#define TIMER_MODE_32                   (0x0020)
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
