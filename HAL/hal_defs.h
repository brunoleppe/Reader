/**@author [Your Name]
 * @file hal_defs.h
 * @author Bruno Leppe (bruno.leppe.dev\@gmail.com)
 * @brief HAL global definitions
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


#ifndef HAL_DEFS_H
#define HAL_DEFS_H


#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "hal_config.h"

#define HAL_SPI_PERIPHERAL_CLOCK            (HAL_SYSTEM_CLOCK/2)
#define HAL_UART_PERIPHERAL_CLOCK           (HAL_SYSTEM_CLOCK/2)
#define HAL_GPIO_PERIPHERAL_CLOCK           (HAL_SYSTEM_CLOCK/2)
#define HAL_PWM_PERIPHERAL_CLOCK            (HAL_SYSTEM_CLOCK/2)
#define HAL_TMR_PERIPHERAL_CLOCK            (HAL_SYSTEM_CLOCK/2)

typedef uint32_t WORD;

#define HAL_WEAK_FUNCTION               __attribute__(( weak ))
#endif //HAL_DEFS_H
