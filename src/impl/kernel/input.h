#pragma once

#include <stdbool.h>
#include "keyboard.h"
#include "print.h"
#include "utility.h"
#include "chars.h"

uint8_t get_keyboard_input();
bool input_str(char* str, int max_len);
