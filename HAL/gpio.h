/**
 * @file gpio.h
 * @author Bruno Leppe (bleppe@solintece.com)
 * @brief GPIO Interface.
 * @version 0.1
 * @date 2022-10-05
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef GPIO_H
#define GPIO_H

/**********************************************************************
* Includes
**********************************************************************/
#include "hal.h"
#include "gpio_config.h"

/**********************************************************************
* Preprocessor Constants
**********************************************************************/
#define _GPIO_PA         (GPIO_Descriptor)(&ANSELA)
#define _GPIO_PB         (GPIO_Descriptor)(&ANSELB)
#define _GPIO_PC         (GPIO_Descriptor)(&ANSELC)
#define _GPIO_PD         (GPIO_Descriptor)(&ANSELD)
#define _GPIO_PE         (GPIO_Descriptor)(&ANSELE)
#define _GPIO_PF         (GPIO_Descriptor)(&ANSELF)
#define _GPIO_PG         (GPIO_Descriptor)(&ANSELG)
#define _GPIO_PH         (GPIO_Descriptor)(&ANSELH)
#define _GPIO_PJ         (GPIO_Descriptor)(&ANSELJ)
#define _GPIO_PK         (GPIO_Descriptor)(&ANSELK)

#define _GPIO_INPUT      0x0000
#define _GPIO_OUTPUT     0x0001
#define _GPIO_ANALOG     0x0002
#define _GPIO_PULLUP     0x0004
#define _GPIO_PULLDOWN   0x0008
#define _GPIO_OPENDRAIN  0x0010
#define _GPIO_SLOWEST    0x0020
#define _GPIO_SLOW       0x0040
#define _GPIO_FAST       0x0080
#define _GPIO_FASTEST    0x0100
#define _GPIO_IRQ        0x0200

#define _GPIO_INPUT_PULLUP       (_GPIO_PULLUP)
#define _GPIO_INPUT_PULLDOWN     (_GPIO_PULLDOWN)
#define _GPIO_OUTPUT_OD          (_GPIO_OUTPUT | _GPIO_OPENDRAIN)


#define _GPIO_PIN_0                 ((uint16_t)0x0001)  /* Pin 0 selected    */
#define _GPIO_PIN_1                 ((uint16_t)0x0002)  /* Pin 1 selected    */
#define _GPIO_PIN_2                 ((uint16_t)0x0004)  /* Pin 2 selected    */
#define _GPIO_PIN_3                 ((uint16_t)0x0008)  /* Pin 3 selected    */
#define _GPIO_PIN_4                 ((uint16_t)0x0010)  /* Pin 4 selected    */
#define _GPIO_PIN_5                 ((uint16_t)0x0020)  /* Pin 5 selected    */
#define _GPIO_PIN_6                 ((uint16_t)0x0040)  /* Pin 6 selected    */
#define _GPIO_PIN_7                 ((uint16_t)0x0080)  /* Pin 7 selected    */
#define _GPIO_PIN_8                 ((uint16_t)0x0100)  /* Pin 8 selected    */
#define _GPIO_PIN_9                 ((uint16_t)0x0200)  /* Pin 9 selected    */
#define _GPIO_PIN_10                ((uint16_t)0x0400)  /* Pin 10 selected   */
#define _GPIO_PIN_11                ((uint16_t)0x0800)  /* Pin 11 selected   */
#define _GPIO_PIN_12                ((uint16_t)0x1000)  /* Pin 12 selected   */
#define _GPIO_PIN_13                ((uint16_t)0x2000)  /* Pin 13 selected   */
#define _GPIO_PIN_14                ((uint16_t)0x4000)  /* Pin 14 selected   */
#define _GPIO_PIN_15                ((uint16_t)0x8000)  /* Pin 15 selected   */
#define _GPIO_PIN_All               ((uint16_t)0xFFFF)  /* All pins selected */
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
 * @brief GPIO Peripheral initialization function.
 *
 * @param config Configuration table.
 * @code
 * const GPIO_Config *config = GPIO_GetConfig();
 *
 * GPIO_init(config);
 * @endcode
 * @see GPIO_GetConfig
 */
void GPIO_init(const GPIO_Config* config);

void GPIO_port_direction_set(GPIO_PORT port, WORD mask, GPIO_DIRECTION direction);
void GPIO_port_write(GPIO_PORT port, WORD mask, WORD value);
void GPIO_output_mapping(GPIO_PIN pin, GPIO_ALTERNATE_FUNCTION alternate_unction);

WORD GPIO_port_read(GPIO_PORT port, WORD mask);

/**
 * @brief Function used to enable or disable internal pull-up resistors on current pin.
 * Pull-up resistors can only be used when pin is configured as igital input.
 *
 * @param pin Current pin.
 * @param state PULLUP_ENABLE or PULLUP_DISABLE to enable or disable internal pull-up resistors.
 */
void GPIO_pin_pullup_set(GPIO_PIN pin, GPIO_PULLUP state);
/**
 * @brief Function used to enable or disable internal pull-down resistors on current pin.
 * Pull-down resistors can only be used when pin is configured as igital input.
 *
 * @param pin Current pin.
 * @param state PULLDOWN_ENABLE or PULLDOWN_DISABLE to enable or disable internal pull-up resistors.
 */
void GPIO_pin_pulldown_set(GPIO_PIN pin, GPIO_PULLDOWN state);
/**
 * @brief Function used to enable or disable state change interrupt on current pin.
 * This function configures GPIO peripheral IRQ registers only, aditional configuration
 * of processor's interrupt controller may be required.
 *
 * @param pin Current pin.
 * @param state GPIO_IRQ_ENABLE or GPIO_IRQ_DISABLE to modify interrupt registers
 */
void GPIO_pin_irq_set(GPIO_PIN pin, GPIO_INTERRUPT state);
/**
 * @brief Funtion used to read the current pin state.
 * This function can be used to read a pin configured as digital input or digital output.
 *
 * @param Current pin.
 * @return GPIO_HIGH on high level, GPIO_LOW on low level.
 */
GPIO_STATE GPIO_pin_read(GPIO_PIN pin);
/**
 * @brief Function used to write a desired level on the current pin.
 * This function only affects pins configured as digital outputs. Input pins are silently ingonred.
 *
 * @param pin  Current pin
 * @param state GPIO_HIGH or GPIO_LOW to modify pin level.
 */
void GPIO_pin_write(GPIO_PIN pin, GPIO_STATE state);
/**
 * @brief Function used to toggle pin state.
 * This function only affects pins configured as digital outputs. Input pins are silently ingonred.
 *
 */
void GPIO_pin_toggle(GPIO_PIN pin);
/**
 * @brief Function used to set pin direction.
 *
 * @param pin Current pin.
 * @param direction GPIO_INPUT, GPIO_OUTPUT or GPIO_ANALOG to modify pin as digital input, digital output or
 * analog input.
 */
void GPIO_pin_direction_set(GPIO_PIN pin, GPIO_DIRECTION direction);
/**
 * @brief Function used to write to specific GPIO registers.
 * Use this function to modify special registers that aren't managed by the HAL.
 * This function is considered "expert mode".
 * @param address Memory address of register to be modified.
 * @param val Value to be written to the register.
 */
void GPIO_register_write(uintptr_t address, WORD val);
/**
 * @brief Function used to read a specific GPIO register state.
 * Use this function to read special registers that aren't managed by the HAL.
 * This function is considered "expert mode".
 *
 * @param address Memory address of register to be read.
 * @return WORD Value read form register.
 */
WORD GPIO_RegisterRead(uintptr_t address);
/**
 * @brief Function used to register a callback function for stata change interrupts.
 * The callback function will be executed whenever a state change interrupt is triggered on
 * the specified PIN. User can register data to be passed to the callback function.
 *
 * @param pin Specified pin of the callback function.
 * @param callback Callback function.
 * @param context User defined data to be passed to the callback function.
 */
void GPIO_CallbackRegister(
        GPIO_PIN pin,
        GPIO_CallbackFunction callback,
        uintptr_t context
);

#ifdef __cplusplus
}
#endif

#endif