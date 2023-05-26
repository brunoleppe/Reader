/**
 * @file timer.h
 * @brief Timer Module
 * @author Bruno Leppe (bruno.leppe.dev\@gmail.com)
 * This module provides functions for initializing and controlling hardware timers.
 * @version 0.1
 * @date 2022-09-29
 *
 * @copyright (c) 2023
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef TIMER_H
#define TIMER_H

/**********************************************************************
 * Includes
 **********************************************************************/

#include "hal_defs.h"

/**********************************************************************
 * Preprocessor Constants
 **********************************************************************/

#define TMR_CHANNEL_2                   (0)
#define TMR_CHANNEL_3                   (1)
#define TMR_CHANNEL_4                   (2)
#define TMR_CHANNEL_5                   (3)
#define TMR_CHANNEL_6                   (4)
#define TMR_CHANNEL_7                   (5)
#define TMR_CHANNEL_8                   (6)
#define TMR_CHANNEL_9                   (7)

#define TMR_TCKPS_MASK                  (0x07)

/*FLAGS*/
#define TMR_PRESCALER_1                 (0x0000)
#define TMR_PRESCALER_2                 (0x0001)
#define TMR_PRESCALER_4                 (0x0002)
#define TMR_PRESCALER_8                 (0x0003)
#define TMR_PRESCALER_16                (0x0004)
#define TMR_PRESCALER_32                (0x0005)
#define TMR_PRESCALER_64                (0x0006)
#define TMR_PRESCALER_256               (0x0007)
#define TMR_GATED                       (0x0008)
#define TMR_EXTERNAL_SOURCE             (0x0010)
#define TMR_MODE_32                     (0x0020)

/**********************************************************************
 * Typedefs
 **********************************************************************/

/**********************************************************************
 * Function Prototypes
 **********************************************************************/

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Initializes the specified timer channel with the given configuration flags and period.
 *
 * This function initializes the specified timer channel with the provided configuration flags and period value.
 *
 * @param channel The timer channel to initialize.
 * @param flags The configuration flags for the timer channel.
 * @param period The period value for the timer channel.
 */
void TMR_initialize(uint32_t channel, uint32_t flags, uint32_t period);

/**
 * @brief Starts the specified timer channel.
 *
 * This function starts the specified timer channel.
 *
 * @param channel The timer channel to start.
 */
void TMR_start(uint32_t channel);

/**
 * @brief Stops the specified timer channel.
 *
 * This function stops the specified timer channel.
 *
 * @param channel The timer channel to stop.
 */
void TMR_stop(uint32_t channel);

/**
 * @brief Sets the period value for the specified timer channel.
 *
 * This function sets the period value for the specified timer channel.
 *
 * @param channel The timer channel to set the period value for.
 * @param period The period value to set.
 */
void TMR_period_set(uint32_t channel, uint16_t period);

/**
 * @brief Sets the prescaler value for the specified timer channel.
 *
 * This function sets the prescaler value for the specified timer channel.
 *
 * @param channel The timer channel to set the prescaler value for.
 * @param prescaler The prescaler value to set.
 */
void TMR_prescaler_set(uint32_t channel, uint16_t prescaler);

/**
 * @brief Retrieves the count value of the specified timer channel.
 *
 * This function retrieves the count value of the specified timer channel.
 *
 * @param channel The timer channel to retrieve the count value from.
 * @return The count value of the specified timer channel.
 */
uint32_t TMR_count_get(uint32_t channel);

/**
 * @brief Retrieves the frequency of the specified timer channel.
 *
 * This function retrieves the frequency of the specified timer channel.
 *
 * @param channel The timer channel to retrieve the frequency from.
 * @return The frequency of the specified timer channel.
 */
uint32_t TMR_frequency_get(uint32_t channel);

/**
 * @brief Sets the frequency for the specified timer channel.
 *
 * This function sets the frequency for the specified timer channel.
 *
 * @param channel The timer channel to set the frequency for.
 * @param frequency The frequency to set.
 */
void TMR_frequency_set(uint32_t channel, uint32_t frequency);

/**
 * @brief Interrupt handler for the specified timer channel.
 *
 * This function is the interrupt handler for the specified timer channel.
 *
 * @param channel The timer channel that triggered the interrupt.
 */
void TMR_interrupt_handler(uint32_t channel);

/**
 * @brief Callback function for the timer channel interrupt.
 *
 * This function is a callback function for the timer channel interrupt.
 *
 * @param channel The timer channel that triggered the interrupt.
 */
void TMR_channel_interrupt_callback(uint32_t channel);

#ifdef __cplusplus
}
#endif

#endif // TIMER_H
