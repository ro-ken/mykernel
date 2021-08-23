#include "gdt.h"
#include "string.h"
//#include "debug"
#define GDT_LENGTH 5

gdt_entry_t gdt_entries[GDT_LENGTH];

gdt_ptr_t gdt_ptr;
static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);


void init_gdt(){
    gdt_ptr.limit = sizeof(gdt_entry_t) * GDT_LENGTH -1;
    gdt_ptr.base = (uint32_t)gdt_entries;//

    //printK()
    // Inter平坦模型
    gdt_set_gate(0,0,0,0,0);    //Inter要求第一项必须为零
    gdt_set_gate(1,0,0xFFFFFFFF,0x9A,0xCF);     //指令段 0x08
    gdt_set_gate(2,0,0xFFFFFFFF,0x92,0xCF);     //数据段 0x10
    gdt_set_gate(3,0,0xFFFFFFFF,0x9A,0xCF);     //用户模式代码段 0x18
    gdt_set_gate(4,0,0xFFFFFFFF,0x9A,0xCF);     //用户模式数据段 0x20


    gdt_flush((uint32_t)&gdt_ptr);
}


static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
	gdt_entries[num].base_low     = (base & 0xFFFF);
	gdt_entries[num].base_middle  = (base >> 16) & 0xFF;
	gdt_entries[num].base_high    = (base >> 24) & 0xFF;

	gdt_entries[num].limit_low    = (limit & 0xFFFF);
	gdt_entries[num].granularity  = (limit >> 16) & 0x0F;

	gdt_entries[num].granularity |= gran & 0xF0;
	gdt_entries[num].access       = access;
}