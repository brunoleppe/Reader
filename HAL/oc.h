/**
 * @file oc.h
 * @brief Header file for the OC (Output Compare) module.
 *
 * This file contains the definitions and function prototypes for the OC module, which provides
 * functionality for output compare operations.
 *
 * @author Bruno Leppe (bruno.leppe.dev\@gmail.com)
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

#ifndef OC_H
#define OC_H

/**********************************************************************
* Includes
**********************************************************************/
#include "hal_defs.h"

/**********************************************************************
* Preprocessor Constants
**********************************************************************/

/**
 * @brief Defines the channel number for OC.
 */
#define OC_CHANNEL_1                        (0)
#define OC_CHANNEL_2                        (1)
#define OC_CHANNEL_3                        (2)
#define OC_CHANNEL_4                        (3)
#define OC_CHANNEL_5                        (4)
#define OC_CHANNEL_6                        (5)
#define OC_CHANNEL_7                        (6)
#define OC_CHANNEL_8                        (7)
#define OC_CHANNEL_9                        (8)

/**
 * @brief Defines the OC mode flags.
 */
#define OC_MDOE_PWM_FAULT_ENABLED           (0x0007)
#define OC_MODE_PWM                         (0x0006)
#define OC_MODE_32                          (0x0020)
#define OC_MODE_USE_TMR3                    (0x0008)
#define OC_MODE_USE_TMR2                    (0)

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

/**
 * @brief Initializes the Output Compare module.
 *
 * This function initializes the specified output compare channel with the provided flags and compare value.
 *
 * @param ocChannel The output compare channel number.
 * @param flags The flags to configure the output compare mode.
 * @param compareValue The initial compare value for the output compare channel.
 */
void        OC_initialize   (uint32_t ocChannel, uint32_t flags, uint32_t compareValue);

/**
 * @brief Enables the specified output compare channel.
 *
 * This function enables the specified output compare channel for operation.
 *
 * @param ocChannel The output compare channel number.
 */
void        OC_enable       (uint32_t ocChannel);

/**
 * @brief Disables the specified output compare channel.
 *
 * This function disables the specified output compare channel.
 *
 * @param ocChannel The output compare channel number.
 */
void        OC_disable      (uint32_t ocChannel);

/**
 * @brief Sets the compare value for the specified output compare channel.
 *
 * This function sets the compare value for the specified output compare channel.
 *
 * @param ocChannel The output compare channel number.
 * @param compareValue The new compare value for the output compare channel.
 */
void        OC_compare_set  (uint32_t ocChannel, uint32_t compareValue);

/**
 * @brief Retrieves the compare value for the specified output compare channel.
 *
 * This function retrieves the current compare value for the specified output compare channel.
 *
 * @param ocChannel The output compare channel number.
 * @return The current compare value for the output compare channel.
 */
uint32_t    OC_compare_get  (uint32_t ocChannel);

#ifdef __cplusplus
}
#endif
#endif

#endif //OC_H
