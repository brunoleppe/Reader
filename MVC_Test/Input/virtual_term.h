//
// Created by bleppe on 14/04/23.
//

#ifndef READER_VIRTUAL_TERM_H
#define READER_VIRTUAL_TERM_H



int is_alpha(int code);
int is_numeric(int code);
int is_symbol(int code);
int is_control(int code);


char get_char(int key_code);
char get_char_to_upper(int key_code);
char get_char_to_lower(int key_code);


#endif //READER_VIRTUAL_TERM_H
