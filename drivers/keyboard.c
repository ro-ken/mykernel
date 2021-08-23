#include "timer.h"
#include "debug.h"
#include "common.h"
#include "idt.h"

static uint8_t keytable[0x54] = {
    0,   0,   '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '^', 0,   0,
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '@', '[', 0,   0,   'A', 'S',
    'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', ':', 0,   0,   ']', 'Z', 'X', 'C', 'V',
    'B', 'N', 'M', ',', '.', '/', 0,   '*', 0,   ' ', 0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   '7', '8', '9', '-', '4', '5', '6', '+', '1',
    '2', '3', '0', '.'
};

void keyboard_callback(pt_regs * regs){
    uint8_t data;
    data = inb(0x0060);
    if (data < 0x54)
    {
        printk("%c",keytable[data]);
    }
    
}


void init_keyboard(){
    register_interrupt_handler(IRQ1,keyboard_callback);
}