#include "input.h"

uint8_t get_keyboard_input()
{
    uint8_t keyboard_code = 0;
    while(!(keyboard_code)){
    keyboard_code = inb(KEYBOARD_PORT);
    }
    return keyboard_code;
}