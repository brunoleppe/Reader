//
// Created by bleppe on 30/03/23.
//

#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#define COLS        4
#define ROWS        5

#define LED1_SET()          led_matrix_led_set(0,0)
#define LED2_SET()          led_matrix_led_set(1,0)
#define LED3_SET()          led_matrix_led_set(2,0)
#define LED4_SET()          led_matrix_led_set(3,0)
#define LED5_SET()          led_matrix_led_set(0,1)
#define LED6_SET()          led_matrix_led_set(1,1)
#define LED7_SET()          led_matrix_led_set(2,1)
#define LED8_SET()          led_matrix_led_set(3,1)
#define LED9_SET()          led_matrix_led_set(0,2)
#define LED10_SET()         led_matrix_led_set(1,2)
#define LED11_SET()         led_matrix_led_set(2,2)
#define LED12_SET()         led_matrix_led_set(3,2)
#define LED13_SET()         led_matrix_led_set(0,3)
#define LED14_SET()         led_matrix_led_set(1,3)
#define LED15_SET()         led_matrix_led_set(2,3)
#define LED16_SET()         led_matrix_led_set(3,3)
#define LED17_SET()         led_matrix_led_set(0,4)

#define LED1_CLR()          led_matrix_led_clr(0,0)
#define LED2_CLR()          led_matrix_led_clr(1,0)
#define LED3_CLR()          led_matrix_led_clr(2,0)
#define LED4_CLR()          led_matrix_led_clr(3,0)
#define LED5_CLR()          led_matrix_led_clr(0,1)
#define LED6_CLR()          led_matrix_led_clr(1,1)
#define LED7_CLR()          led_matrix_led_clr(2,1)
#define LED8_CLR()          led_matrix_led_clr(3,1)
#define LED9_CLR()          led_matrix_led_clr(0,2)
#define LED10_CLR()         led_matrix_led_clr(1,2)
#define LED11_CLR()         led_matrix_led_clr(2,2)
#define LED12_CLR()         led_matrix_led_clr(3,2)
#define LED13_CLR()         led_matrix_led_clr(0,3)
#define LED14_CLR()         led_matrix_led_clr(1,3)
#define LED15_CLR()         led_matrix_led_clr(2,3)
#define LED16_CLR()         led_matrix_led_clr(3,3)
#define LED17_CLR()         led_matrix_led_clr(0,4)

#define LED1_TOGGLE()       led_matrix_led_toggle(0,0)
#define LED2_TOGGLE()       led_matrix_led_toggle(1,0)
#define LED3_TOGGLE()       led_matrix_led_toggle(2,0)
#define LED4_TOGGLE()       led_matrix_led_toggle(3,0)
#define LED5_TOGGLE()       led_matrix_led_toggle(0,1)
#define LED6_TOGGLE()       led_matrix_led_toggle(1,1)
#define LED7_TOGGLE()       led_matrix_led_toggle(2,1)
#define LED8_TOGGLE()       led_matrix_led_toggle(3,1)
#define LED9_TOGGLE()       led_matrix_led_toggle(0,2)
#define LED10_TOGGLE()      led_matrix_led_toggle(1,2)
#define LED11_TOGGLE()      led_matrix_led_toggle(2,2)
#define LED12_TOGGLE()      led_matrix_led_toggle(3,2)
#define LED13_TOGGLE()      led_matrix_led_toggle(0,3)
#define LED14_TOGGLE()      led_matrix_led_toggle(1,3)
#define LED15_TOGGLE()      led_matrix_led_toggle(2,3)
#define LED16_TOGGLE()      led_matrix_led_toggle(3,3)
#define LED17_TOGGLE()      led_matrix_led_toggle(0,4)

void led_matrix_led_set(int col, int row);
void led_matrix_led_clr(int col, int row);
void led_matrix_led_toggle(int col, int row);
void led_matrix_led_number_set(int number);
void led_matrix_led_number_clr(int number);
void led_matrix_led_number_toggle(int number);
void led_matrix_led_clr_all();

#endif //LED_MATRIX_H
