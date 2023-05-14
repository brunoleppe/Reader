//
// Created by bleppe on 11/05/23.
//
#include <SDL2/SDL.h>
#include "MVC/ControllerInputEvent.h"

int is_alpha(int code)
{
    if(code >= SDL_SCANCODE_A && code <= SDL_SCANCODE_Z)
        return (int)SDL_GetKeyFromScancode((SDL_Scancode)code);
    return 0;
}
int is_numeric(int code)
{
    if(code <= SDL_SCANCODE_0 && code >= SDL_SCANCODE_1)
        return (int)SDL_GetKeyFromScancode((SDL_Scancode)code);
    return 0;
}
int is_symbol(int code)
{

    return 0;
}
int is_control(int code)
{
    const int keys[] = {
            CONTROL_TYPE_ENTER,
            CONTROL_TYPE_CANCEL,
            CONTROL_TYPE_RETURN,
            CONTROL_TYPE_OPTION,
            CONTROL_TYPE_SPACE,
            CONTROL_TYPE_DOWN,
            CONTROL_TYPE_UP,
            CONTROL_TYPE_PUMP
    };
    int k = 0;

    if(code >= SDL_SCANCODE_RETURN && code <= SDL_SCANCODE_SPACE) {
        k = code - SDL_SCANCODE_RETURN;
    }
    else if(code == SDL_SCANCODE_DOWN || code == SDL_SCANCODE_UP){
        k = code - SDL_SCANCODE_DOWN + 5;
    }
    else if(code == 58){
        k = 7;
    }
    else{
        return 0;
    }
    return keys[k];
}
//
//
//char get_char(int key_code);
//char get_char_to_upper(int key_code);
//char get_char_to_lower(int key_code);