#ifndef HAL_DEFS_H
#define HAL_DEFS_H

#if defined (__LANGUAGE_C__) || defined (__LANGUAGE_C_PLUS_PLUS)

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "hal_config.h"

typedef uint32_t WORD;

#define HAL_WEAK_FUNCTION               __attribute__(( weak ))
#endif
#endif //HAL_DEFS_H
