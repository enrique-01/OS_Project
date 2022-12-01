#include "print.h"
#include "cursor.h"
#include "input.h"
#include <stdbool.h>



static inline bool are_interrupts_enabled()
{
    unsigned long flags;
    asm volatile ( "pushf\n\t"
                   "pop %0"
                   : "=g"(flags) );
    return flags & (1 << 9);
}

void kernel_main()
{
    print_clear();

    enable_cursor(0,0);

    print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
    print_str("Welcome to our 64bit OS!\n");

    if(!(are_interrupts_enabled)){
        //print_clear();
        print_str("Interrupts are Disabled");
    }

    print_clear();
    print_str("Enter some string: ");
    
    while(1){
        print_char((get_keyboard_input()));
    }

}