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
#include "hal_defs.h"
/**********************************************************************
* Preprocessor Constants
**********************************************************************/
#define GPIO_PORT_SHIFT             (4)
#define GPIO_PORT_MASK              (0xF0000)

#define GPIO_PORT_A                  (0x0)
#define GPIO_PORT_B                  (0x1)
#define GPIO_PORT_C                  (0x2)
#define GPIO_PORT_D                  (0x3)
#define GPIO_PORT_E                  (0x4)
#define GPIO_PORT_F                  (0x5)
#define GPIO_PORT_G                  (0x6)
#define GPIO_PORT_H                  (0x7)
#define GPIO_PORT_J                  (0x8)
#define GPIO_PORT_K                  (0x9)

#define GPIO_INPUT                  0x0000
#define GPIO_OUTPUT                 0x0001
#define GPIO_ANALOG                 0x0002
#define GPIO_PULLUP                 0x0004
#define GPIO_PULLDOWN               0x0008
#define GPIO_OPENDRAIN              0x0010
#define GPIO_SLOWEST                0x0020
#define GPIO_SLOW                   0x0040
#define GPIO_FAST                   0x0080
#define GPIO_FASTEST                0x0100
#define GPIO_IRQ                    0x0200

#define GPIO_INPUT_PULLUP          (GPIO_PULLUP)
#define GPIO_INPUT_PULLDOWN        (GPIO_PULLDOWN)
#define GPIO_OUTPUT_OD             (GPIO_OUTPUT | GPIO_OPENDRAIN)


#define GPIO_PIN_MASK               (0xF)
#define GPIO_PIN_0                  (0x0)  /* Pin 0 selected    */
#define GPIO_PIN_1                  (0x1)  /* Pin 1 selected    */
#define GPIO_PIN_2                  (0x2)  /* Pin 2 selected    */
#define GPIO_PIN_3                  (0x3)  /* Pin 3 selected    */
#define GPIO_PIN_4                  (0x4)  /* Pin 4 selected    */
#define GPIO_PIN_5                  (0x5)  /* Pin 5 selected    */
#define GPIO_PIN_6                  (0x6)  /* Pin 6 selected    */
#define GPIO_PIN_7                  (0x7)  /* Pin 7 selected    */
#define GPIO_PIN_8                  (0x8)  /* Pin 8 selected    */
#define GPIO_PIN_9                  (0x9)  /* Pin 9 selected    */
#define GPIO_PIN_10                 (0xa)  /* Pin 10 selected   */
#define GPIO_PIN_11                 (0xb)  /* Pin 11 selected   */
#define GPIO_PIN_12                 (0xc)  /* Pin 12 selected   */
#define GPIO_PIN_13                 (0xd)  /* Pin 13 selected   */
#define GPIO_PIN_14                 (0xe)  /* Pin 14 selected   */
#define GPIO_PIN_15                 (0xf)  /* Pin 15 selected   */

#define GPIO_LOW                    (0)
#define GPIO_HIGH                   (1)
/*********************************************************************
* Preprocessor Macros
**********************************************************************/
#define GPIO_PIN_MAP(port, pin)     ((port << GPIO_PORT_SHIFT) | pin)
/**********************************************************************
* Typedefs
**********************************************************************/
typedef bool GPIO_STATE;
typedef bool GPIO_IRQ_STATE;
typedef uint32_t GPIO_PIN;
typedef uint32_t GPIO_ALTERNATE_FUNCTION;
typedef void (*GPIO_CALLBACK)(GPIO_PIN);

typedef struct{
    uint8_t pin;
    GPIO_CALLBACK  callback;
}GPIO_CALLBACK_OBJECT;

/**********************************************************************
* Function Prototypes
**********************************************************************/
#ifdef __cplusplus
extern "C"{
#endif
    
void    GPIO_pin_initialize             (uint32_t pin, int flags);
void    GPIO_pin_deinitialize           (uint32_t pin);
bool    GPIO_pin_read                   (uint32_t pin);
void    GPIO_pin_write                  (uint32_t pin, bool value);
void    GPIO_pin_toggle                 (uint32_t pin);
void    GPIO_pin_interrupt_set          (uint32_t pin, bool state);

void    GPIO_pin_interrupt_callback     (uint32_t pin);
void    GPIO_interrupt_handler          (uint32_t port);


#ifdef __cplusplus
}
#endif




#endif