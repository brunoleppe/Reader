//
// Created by bleppe on 14/04/23.
//

#include "virtual_term.h"
#include "linux_keys.h"
#include "input.h"

static const char buffer[] = {
        [KEY_1]                 = '1',
        [KEY_2]                 = '2',
        [KEY_3]                 = '3',
        [KEY_4]                 = '4',
        [KEY_5]                 = '5',
        [KEY_6]                 = '6',
        [KEY_7]                 = '7',
        [KEY_8]                 = '8',
        [KEY_9]                 = '9',
        [KEY_0]                 = '0',
        [KEY_MINUS]             = '-',
        [KEY_EQUAL]             = '=',
        [KEY_Q]                 = 'Q',
        [KEY_W]                 = 'W',
        [KEY_E]                 = 'E',
        [KEY_R]                 = 'R',
        [KEY_T]                 = 'T',
        [KEY_Y]                 = 'Y',
        [KEY_U]                 = 'U',
        [KEY_I]                 = 'I',
        [KEY_O]                 = 'O',
        [KEY_P]                 = 'P',
        [KEY_LEFTBRACE]         = '{',
        [KEY_RIGHTBRACE]        = '}',
        [KEY_A]                 = 'A',
        [KEY_S]                 = 'S',
        [KEY_D]                 = 'D',
        [KEY_F]                 = 'F',
        [KEY_G]                 = 'G',
        [KEY_H]                 = 'H',
        [KEY_J]                 = 'J',
        [KEY_K]                 = 'K',
        [KEY_L]                 = 'L',
        [KEY_SEMICOLON]         = ';',
        [KEY_HASH]              = '#',
        [KEY_Z]                 = 'Z',
        [KEY_X]                 = 'X',
        [KEY_C]                 = 'C',
        [KEY_V]                 = 'V',
        [KEY_B]                 = 'B',
        [KEY_N]                 = 'N',
        [KEY_M]                 = 'M',
        [KEY_COMMA]             = ',',
        [KEY_DOT]               = '.',
        [KEY_SLASH]             = '/',
        [KEY_KPASTERISK]        = '*',
        [KEY_SPACE]             = ' ',
        [KEY_TILDE_A]           = (char) L'Á',
        [KEY_TILDE_E]           = (char)(L'É'),
        [KEY_TILDE_I]           = (char)(L'Í'),
        [KEY_TILDE_O]           = (char)(L'Ó'),
        [KEY_TILDE_U]           = (char)(L'Ú'),
        [KEY_TILDE_N]           = (char)(L'Ñ'),
        [KEY_DOTTED_U]          = (char)(L'Ü'),
        [KEY_UNDERSCORE]        = '_',
        [KEY_ASPERAND]          = '@',
};


char get_char(int key_code)
{
    return (char)buffer[key_code];
}

char get_char_to_upper(int key_code){
    return (char)buffer[key_code];
}

char get_char_to_lower(int key_code){
    char c = (char)buffer[key_code];
    if((c >= 'A' && c <= 'Z' )|| c > 127)
        c += 32; //'a' - 'A' = 32
    return c;
}


int is_alpha(int code)
{
    return 0;
}
int is_numeric(int code)
{
    return 0;
}
int is_symbol(int code)
{
    return 0;
}
int is_control(int code)
{
    switch(code){
        case KEY_RESERVED: return CONTROL_TYPE_INVALID;
        case KEY_F1: return CONTROL_TYPE_OPTION;
        case KEY_BACKSPACE: return CONTROL_TYPE_RETURN;
        case KEY_ENTER: return CONTROL_TYPE_ENTER;
        case KEY_DOWN: return CONTROL_TYPE_DOWN;
        case KEY_UP: return CONTROL_TYPE_UP;
        case KEY_F2: return CONTROL_TYPE_PUMP;
        case KEY_F3: return CONTROL_TYPE_TICK;
    }
    return CONTROL_TYPE_INVALID;
}
