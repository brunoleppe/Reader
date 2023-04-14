//
// Created by bleppe on 14/04/23.
//

#include "virtual_term.h"
#include "linux_keys.h"

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
        [KEY_TILDE_A]           = (char)'Á',
        [KEY_TILDE_E]           = (char)'É',
        [KEY_TILDE_I]           = (char)'Í',
        [KEY_TILDE_O]           = (char)'Ó',
        [KEY_TILDE_U]           = (char)'Ú',
        [KEY_TILDE_N]           = (char)'Ñ',
        [KEY_DOTTED_U]          = (char)'Ü',
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
    if(c >= 'A' && c <= 'Z')
        c += 'a' - 'A';
    else if((int)c > 127)
        c += 32;

    return c;
}