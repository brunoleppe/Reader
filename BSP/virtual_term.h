//
// Created by bleppe on 14/04/23.
//

#ifndef READER_VIRTUAL_TERM_H
#define READER_VIRTUAL_TERM_H

#ifdef __cplusplus
extern "C"{
#endif

char get_char(int key_code);
char get_char_to_upper(int key_code);
char get_char_to_lower(int key_code);

#ifdef __cplusplus
}
#endif

#endif //READER_VIRTUAL_TERM_H
