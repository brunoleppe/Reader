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
#include "pic32mz_registers.h"
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
    
void GPIO_initialize(GPIO_Descriptor port, uint16_t pins, int flags);
void GPIO_deinitialize(GPIO_Descriptor port, uint16_t pins);

WORD GPIO_port_read(GPIO_Descriptor port, int pins);
void GPIO_port_write(GPIO_Descriptor port, WORD value, int pins);
void GPIO_port_toggle(GPIO_Descriptor port, int pins);
void GPIO_port_interrupt_set(GPIO_Descriptor port, GPIO_INTERRUPT state);

void GPIO_output_mapping(GPIO_PIN pin, GPIO_ALTERNATE_FUNCTION alternate_unction);
void GPIO_CallbackRegister(
        GPIO_PIN pin,
        GPIO_CallbackFunction callback,
        uintptr_t context
);

static inline
GPIO_STATE GPIO_pin_read(GPIO_Descriptor port, uint16_t pin)
{
    return GPIO_port_read(port, pin) == pin;
}
static inline
void GPIO_pin_write(GPIO_Descriptor port, GPIO_STATE state, uint16_t pin)
{
    GPIO_port_write(port, (state)<<pin, pin);
}
static inline
void GPIO_pin_toggle(GPIO_Descriptor port, uint16_t pin)
{
    GPIO_port_toggle(port, pin);
}
#ifdef __cplusplus
}
#endif

#endif