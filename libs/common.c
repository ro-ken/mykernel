
#include "common.h"

//一次传输一个字节,从CPU出去，out地址为第二个参数
inline void outb(uint16_t port,uint8_t value){
    asm volatile("outb %1,%0"::"d"(port),"a"(value));
    //asm volatile("outb %%eax,%%edx"::"d"(port),"a"(value));
}

//in 和out 地址顺序相反，in地址为第一个参数
inline uint8_t inb(uint16_t port){
    uint8_t ret;

    asm volatile("inb %%edx,%%eax":"=a"(ret):"d"(port));

    return ret;
}


inline uint16_t inw(uint16_t port){
    uint16_t ret;

    asm volatile("inw %%edx,%%eax":"=a"(ret) : "d"(port));

    return ret;
}