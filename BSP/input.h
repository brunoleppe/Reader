//
// Created by bleppe on 31/03/23.
//

#ifndef READER_INPUT_H
#define READER_INPUT_H

#include <stdbool.h>

typedef struct{
    int code;
    int value;
}InputEvent;

bool input_report_key(int code, int value);

#endif //READER_INPUT_H
