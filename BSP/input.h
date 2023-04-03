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

#ifdef __cplusplus
extern "C" {
#endif

bool input_report_key(int code, int value);

#ifdef __cplusplus
}
#endif

#endif //READER_INPUT_H
