//
// Created by bleppe on 20/03/23.
//

#include "hal.h"

#ifndef QTOUCH_H
#define QTOUCH_H

int     QTouch_initialize(SPI_Channel channel, GPIO_PinMap cs, GPIO_PinMap rst, GPIO_PinMap change, GPIO_PinMap drdy);

int     QTouch_calibrate_all();
int     QTouch_calibrate_key(int key);
int     QTouch_reset();
int     QTouch_sleep();
int     QTouch_set_setups(uint8_t *setups, int setupsSize);
int     QTouch_eeprom_store();
int     QTouch_eeprom_erase();
int     QTouch_eeprom_recover();
int     QTouch_get_key();
int     QTouch_get_status();
int     QTouch_get_eeprom_crc();
int     QTouch_get_ram_crc();
int     QTouch_get_error_keys();
int     QTouch_get_key_signal(int key);
int     QTouch_get_key_reference(int key);
int     QTouch_get_key_status(int key);
int     QTouch_get_detect_output_states();
int     QTouch_get_last_command();
uint8_t* QTouch_get_setups(int* setupsSize);
int     QTouch_get_device_id();
int     QTouch_get_firmware_version();

#endif //QTOUCH_H
