//
// Created by bleppe on 30/03/23.
//

#include "led_matrix.h"
#include "board_defs.h"
#include "gpio.h"

static GPIO_PinMap colPins[COLS] = {
        LED_M_COL0_PIN,
        LED_M_COL1_PIN,
        LED_M_COL2_PIN,
        LED_M_COL3_PIN,
};
static GPIO_PinMap rowPins[ROWS] = {
        LED_M_ROW0_PIN,
        LED_M_ROW1_PIN,
        LED_M_ROW2_PIN,
        LED_M_ROW3_PIN,
        LED_M_ROW4_PIN,
};

void led_matrix_led_set(int col, int row)
{
    GPIO_pin_write(rowPins[col], GPIO_HIGH);
    GPIO_pin_write(colPins[col], GPIO_LOW);
}
void led_matrix_led_clr(int col, int row)
{
    GPIO_pin_write(rowPins[col], GPIO_LOW);
    GPIO_pin_write(colPins[col], GPIO_HIGH);
}
void led_matrix_led_toggle(int col, int row)
{
    GPIO_pin_toggle(rowPins[col]);
    GPIO_pin_write(colPins[col], GPIO_LOW);
}

void led_matrix_led_number_set(int number)
{
    led_matrix_led_set(number%4, number/4);
}
void led_matrix_led_number_clr(int number)
{
    led_matrix_led_clr(number%4, number/4);
}
void led_matrix_led_number_toggle(int number)
{
    led_matrix_led_toggle(number%4, number/4);
}
void led_matrix_led_clr_all()
{
    GPIO_pin_initialize(LED_M_COL0_PIN, GPIO_HIGH);
    GPIO_pin_initialize(LED_M_COL1_PIN, GPIO_HIGH);
    GPIO_pin_initialize(LED_M_COL2_PIN, GPIO_HIGH);
    GPIO_pin_initialize(LED_M_COL3_PIN, GPIO_HIGH);
    GPIO_pin_initialize(LED_M_ROW0_PIN, GPIO_LOW);
    GPIO_pin_initialize(LED_M_ROW1_PIN, GPIO_LOW);
    GPIO_pin_initialize(LED_M_ROW2_PIN, GPIO_LOW);
    GPIO_pin_initialize(LED_M_ROW3_PIN, GPIO_LOW);
    GPIO_pin_initialize(LED_M_ROW4_PIN, GPIO_LOW);
}