/**
 * @file gpio.h
 * @author Bruno Leppe (bruno.leppe.dev\@gmail.com)
 * @brief GPIO Interface.
 * This file contains the interface for GPIO (General Purpose Input/Output) operations.
 * @version 0.1
 * @date 2022-10-05
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

#ifndef GPIO_H
#define GPIO_H

/**********************************************************************
* Includes
**********************************************************************/
#include "hal_defs.h"
/**********************************************************************
* Preprocessor Constants
**********************************************************************/
#define GPIO_PORT_SHIFT             (16)
#define GPIO_PORT_MASK              (0xF0000)

#define GPIO_PORT_A                 (0x0)
#define GPIO_PORT_B                 (0x1)
#define GPIO_PORT_C                 (0x2)
#define GPIO_PORT_D                 (0x3)
#define GPIO_PORT_E                 (0x4)
#define GPIO_PORT_F                 (0x5)
#define GPIO_PORT_G                 (0x6)
#define GPIO_PORT_H                 (0x7)
#define GPIO_PORT_J                 (0x8)
#define GPIO_PORT_K                 (0x9)

#define GPIO_INPUT                  (0x0000)
#define GPIO_OUTPUT                 (0x0001)
#define GPIO_ANALOG                 (0x0002)
#define GPIO_PULLUP                 (0x0004)
#define GPIO_PULLDOWN               (0x0008)
#define GPIO_OPENDRAIN              (0x0010)
#define GPIO_SLOWEST                (0x0020)
#define GPIO_SLOW                   (0x0040)
#define GPIO_FAST                   (0x0080)
#define GPIO_FASTEST                (0x0100)
#define GPIO_IRQ                    (0x0200)

#define GPIO_INPUT_PULLUP           (GPIO_PULLUP)
#define GPIO_INPUT_PULLDOWN         (GPIO_PULLDOWN)
#define GPIO_OUTPUT_OD              (GPIO_OUTPUT | GPIO_OPENDRAIN)


#define GPIO_PIN_MASK               (0xFFFF)
#define GPIO_PIN_0                  (0x0001)  /* Pin 0 selected    */
#define GPIO_PIN_1                  (0x0002)  /* Pin 1 selected    */
#define GPIO_PIN_2                  (0x0004)  /* Pin 2 selected    */
#define GPIO_PIN_3                  (0x0008)  /* Pin 3 selected    */
#define GPIO_PIN_4                  (0x0010)  /* Pin 4 selected    */
#define GPIO_PIN_5                  (0x0020)  /* Pin 5 selected    */
#define GPIO_PIN_6                  (0x0040)  /* Pin 6 selected    */
#define GPIO_PIN_7                  (0x0080)  /* Pin 7 selected    */
#define GPIO_PIN_8                  (0x0100)  /* Pin 8 selected    */
#define GPIO_PIN_9                  (0x0200)  /* Pin 9 selected    */
#define GPIO_PIN_10                 (0x0400)  /* Pin 10 selected   */
#define GPIO_PIN_11                 (0x0800)  /* Pin 11 selected   */
#define GPIO_PIN_12                 (0x1000)  /* Pin 12 selected   */
#define GPIO_PIN_13                 (0x2000)  /* Pin 13 selected   */
#define GPIO_PIN_14                 (0x4000)  /* Pin 14 selected   */
#define GPIO_PIN_15                 (0x8000)  /* Pin 15 selected   */
#define GPIO_ALL                    (0xFFFF)

#define GPIO_PIN_INVALID            (0xFFFFFFFF)

#define GPIO_LOW                    (0)
#define GPIO_HIGH                   (1)
/*********************************************************************
* Preprocessor Macros
**********************************************************************/
#define GPIO_PIN_MAP(port, pin)     ((port << GPIO_PORT_SHIFT) | pin)
/**********************************************************************
* Typedefs
**********************************************************************/
/**
 * @brief Represents the state of a GPIO pin.
 */
typedef bool GPIO_STATE;

/**
 * @brief Represents the state of a GPIO interrupt request (IRQ).
 */
typedef bool GPIO_IRQ_STATE;

/**
 * @brief Represents a GPIO pin number.
 */
typedef uint32_t GPIO_Pin;

/**
 * @brief Represents a GPIO port number.
 */
typedef uint32_t GPIO_Port;

/**
 * @brief Represents a mapping of a pin to a GPIO function.
 */
typedef uint32_t GPIO_PinMap;

/**
 * @brief Represents an alternate function of a GPIO pin.
 */
typedef uint32_t GPIO_ALTERNATE_FUNCTION;

/**
 * @brief Represents a callback function for a GPIO pin.
 *
 * This callback function is invoked when a specific GPIO pin triggers an interrupt.
 *
 * @param pin The pin that triggered the interrupt.
 * @param context A user-defined context value associated with the callback.
 */
typedef void (*GPIO_Callback)(GPIO_PinMap pin, uintptr_t context);

/**
 * @brief Represents a GPIO callback object.
 *
 * This object associates a GPIO pin with a callback function and a user-defined context.
 */
typedef struct {
    GPIO_PinMap pin;       /**< The pin associated with the callback. */
    GPIO_Callback callback; /**< The callback function. */
    uintptr_t context;     /**< A user-defined context value. */
} GPIO_CALLBACK_OBJECT;

/**********************************************************************
* Function Prototypes
**********************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Initializes a GPIO pin with the specified configuration flags.
 *
 * @param pin The pin to be initialized.
 * @param flags The configuration flags for the pin.
 */
void GPIO_pin_initialize(GPIO_PinMap pin, int flags);

/**
 * @brief Deinitializes a GPIO pin.
 *
 * @param pin The pin to be deinitialized.
 */
void GPIO_pin_deinitialize(GPIO_PinMap pin);

/**
 * @brief Reads the state of a GPIO pin.
 *
 * @param pin The pin to read.
 * @return The state of the pin (true if high, false if low).
 */
bool GPIO_pin_read(GPIO_PinMap pin);

/**
 * @brief Writes a value to a GPIO pin.
 *
 * @param pin The pin to write to.
 * @param value The value to write (true for high, false for low).
 */
void GPIO_pin_write(GPIO_PinMap pin, bool value);

/**
 * @brief Toggles the state of a GPIO pin.
 *
 * @param pin The pin to toggle.
 */
void GPIO_pin_toggle(GPIO_PinMap pin);

/**
 * @brief Sets the interrupt state for a GPIO pin.
 *
 * @param pin The pin to set the interrupt state for.
 * @param state The interrupt state (true for enabled, false for disabled).
 */
void GPIO_pin_interrupt_set(GPIO_PinMap pin, bool state);

/**
 * @brief Writes a value to a GPIO port.
 *
 * @param port The port to write to.
 * @param value The value to write.
 * @param mask The mask specifying which pins to write.
 */
void GPIO_port_write(GPIO_Port port, uint32_t value, uint32_t mask);

/**
 * @brief Reads the value of a GPIO port.
 *
 * @param port The port to read from.
 * @param mask The mask specifying which pins to read.
 * @return The value read from the port.
 */
uint32_t GPIO_port_read(GPIO_Port port, uint32_t mask);

/**
 * @brief Toggles the state of multiple pins in a GPIO port.
 *
 * @param port The port to toggle pins in.
 * @param mask The mask specifying which pins to toggle.
 */
void GPIO_port_toggle(GPIO_Port port, uint32_t mask);

/**
 * @brief Callback function for GPIO pin interrupts.
 *
 * This function is called when a GPIO pin interrupt is triggered.
 *
 * @param pin The pin for which the interrupt occurred.
 */
void GPIO_pin_interrupt_callback(GPIO_PinMap pin);

/**
 * @brief Interrupt handler for GPIO ports.
 *
 * This function is the interrupt handler for GPIO ports and is called when any of the GPIO pins in the port trigger an interrupt.
 *
 * @param port The port for which the interrupt occurred.
 */
void GPIO_interrupt_handler(GPIO_Port port);

#ifdef __cplusplus
}
#endif

#endif