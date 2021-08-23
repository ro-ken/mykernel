#include "timer.h"
#include "debug.h"
#include "common.h"
#include "idt.h"
#include "sched.h"

void timer_callback(pt_regs * reg){
    schedule();
}

void init_timer(){
    register_interrupt_handler(IRQ0,timer_callback);
    //1193181/65535 = 18.2次/s，最慢产生的中断数
    uint16_t cycle = 0xFFFF;

    outb(0x43,0x36);

    uint8_t low = (uint8_t)(cycle&0xFF);
    uint8_t high = (uint8_t)((cycle >> 8) & 0xFF);
    outb(0x40,low);
    outb(0x40,high);
}
