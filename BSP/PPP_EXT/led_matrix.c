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
    GPIO_pin_write(rowPins[row], GPIO_HIGH);
    GPIO_pin_write(colPins[col], GPIO_LOW);
}
void led_matrix_led_clr(int col, int row)
{
    GPIO_pin_write(rowPins[row], GPIO_LOW);
    GPIO_pin_write(colPins[col], GPIO_HIGH);
}
void led_matrix_led_toggle(int col, int row)
{
    GPIO_pin_toggle(rowPins[row]);
    GPIO_pin_write(colPins[col], GPIO_LOW);
}

void led_matrix_led_number_set(int number)
{
    int q,r;
    q = number >> 2;
    r = number - (q << 2);
    led_matrix_led_set(r, q);
}
void led_matrix_led_number_clr(int number)
{
    int q,r;
    q = number >> 2;
    r = number - (q << 2);
    led_matrix_led_clr(r, q);
}
void led_matrix_led_number_toggle(int number)
{
    int q,r;
    q = number >> 2;
    r = number - (q << 2);
    led_matrix_led_toggle(r, q);
}
void led_matrix_led_clr_all()
{
    GPIO_pin_write(LED_M_COL0_PIN, GPIO_HIGH);
    GPIO_pin_write(LED_M_COL1_PIN, GPIO_HIGH);
    GPIO_pin_write(LED_M_COL2_PIN, GPIO_HIGH);
    GPIO_pin_write(LED_M_COL3_PIN, GPIO_HIGH);
    GPIO_pin_write(LED_M_ROW0_PIN, GPIO_LOW);
    GPIO_pin_write(LED_M_ROW1_PIN, GPIO_LOW);
    GPIO_pin_write(LED_M_ROW2_PIN, GPIO_LOW);
    GPIO_pin_write(LED_M_ROW3_PIN, GPIO_LOW);
    GPIO_pin_write(LED_M_ROW4_PIN, GPIO_LOW);
}