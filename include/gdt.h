#ifndef INCLUDE_GDT_H_
#define INCLUDE_GDT_H_

#include "types.h"

//GDT表项
typedef struct gdt_entry_t
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access; //权限
    uint8_t granularity; //其他标志
    uint8_t base_high;
} __attribute__((packed)) gdt_entry_t;

//GDTR
typedef struct gdt_ptr_t
{
    uint16_t limit; //GDT大小
    uint32_t base; 
} __attribute__((packed)) gdt_ptr_t;

void init_gdt();

//GDT->GDTR
extern void gdt_flush(uint32_t);


#endif //INCLUDE_GDT_H_