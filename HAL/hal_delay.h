/**
 * @file hal_delay.h
 * @author Bruno Leppe (bruno.leppe.dev\@gmail.com)
 * @brief HAL delay implementation using microcontroller's core timer.
 * @version 0.1
 * @date 2022-10-08
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


#ifndef HAL_DELAY_H
#define HAL_DELAY_H

/**********************************************************************
* Includes
**********************************************************************/
#include "hal_defs.h"

/**********************************************************************
* Preprocessor Constants
**********************************************************************/
#define MICRO_SECONDS   (1000000)
#define MILI_SECONDS    (1000)
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
 * @brief Delay the execution for a specified number of milliseconds.
 *
 * @param ms The number of milliseconds to delay.
 */
void HAL_delay_ms(uint32_t ms);

/**
 * @brief Delay the execution for a specified number of microseconds.
 *
 * @param us The number of microseconds to delay.
 */
void HAL_delay_us(uint32_t us);

/**
 * @brief Delay the execution for a specified number of clock cycles.
 *
 * @param cy The number of clock cycles to delay.
 */
void HAL_delay_cy(uint32_t cy);

#ifdef __cplusplus
}
#endif

#endif //HAL_DELAY_H
