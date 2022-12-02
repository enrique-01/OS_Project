#include "input.h"

uint8_t get_keyboard_input()
{
    uint8_t keyboard_code = 0;
    
    while(!(keyboard_code)){
    keyboard_code = inb(KEYBOARD_PORT);
    }
    return keyboard_code;
}

bool input_str(char* str, int max_len) {
    bool capslock = false;
    bool shift = false;
    bool alt = false;
    bool ctrl = false;
    bool numlock = true;
    bool scrolllock = false;
    uint32_t repeats = 0;

    uint32_t last_keycode = 0;
    int pos = 0;
    while (true) {
        uint8_t c = get_keyboard_input();
        // Skip repeating keys
        if (c == last_keycode) {
            ++repeats;
            if (repeats < 40 || repeats % 8 != 0) {
                continue;
            }
        } else {
            repeats = 0;
        }
        last_keycode = c;
        if (c == KEY_LEFT_SHIFT_RELEASE) {
            shift = false;
        }
        if (c == KEY_RIGHT_SHIFT_RELEASE) {
            shift = false;
        }
        // Skip depressing other keys
        if (c > 127) {
            continue;
        }
        if (c == KEY_ENTER) {
            str[pos] = '\0';
            return true;
        } else if (c == KEY_ESC) {
            str[pos] = '\0';
            return false;
        } else if (c == KEY_BACKSPACE) {
            if (pos) {
                pos--;
                clear_col();
            }
        } else if (c == KEY_LEFT_SHIFT_PRESS) {
            shift = true;
        } else if (c == KEY_CAPS_LOCK_PRESS) {
            capslock = !capslock;
        } else if ((c >=2 && c <= 13) || (c >= 16 && c <= 27) || (c >= 30 && c <= 41) || (c >= 43 && c <= 53) || c == 57) {
            if (pos + 1 < max_len) {
                char ch;
                if (capslock || shift) {
                    ch = get_ascii_char(c);
                } else {
                    ch = get_ascii_char_lower(c);
                }
                str[pos] = ch;
                print_char(ch);
                pos++;
            }
        }
    }
}