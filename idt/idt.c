#include "common.h"
#include "string.h"
#include "debug.h"
#include "idt.h"

idt_entry_t idt_entries[256];

idt_ptr_t idt_ptr;
 
interrupt_handler_t interrupt_handlers[256];

static void idt_set_gate(uint8_t num,uint32_t offset,uint16_t selector,uint8_t flags);

extern void idt_flush(uint32_t);
void initPIC();
void initIDT();
void initIDTR();

void init_idt()
{
	initPIC();
	initIDT();
	initIDTR();
}

void idt_set_gate(uint8_t num,uint32_t offset,uint16_t selector,uint8_t flags){
    idt_entries[num].offset_low = offset & 0xFFFF;
    idt_entries[num].offset_high = (offset >> 16) & 0xFFFF;

    idt_entries[num].selector = selector;
    idt_entries[num].always0 = 0;
    idt_entries[num].flags = flags;
}

void isr_handler(pt_regs *regs)
{
    if (interrupt_handlers[regs->int_no])
    {
        interrupt_handlers[regs->int_no](regs);
    }else{
		printk_color(rc_black, rc_white, "Unhandled interrupt: %d\n", regs->int_no);
    }
	// 查看寄存器
	// for (int i = 0; i < sizeof(pt_regs)/4; i++)
	// {
	// 	printk("reg %d = %d\t",i,((uint32_t *)regs)[i]);
	// }
	// printk("\n=======================================================\n");
	
}

void irq_handler(pt_regs *regs){

	if (regs->int_no >= 40)
	{
		//回复从PIC
		outb(0xA0,0x20);
	}
	//回复主PIC
	outb(0x20,0x20);

	if (interrupt_handlers[regs->int_no])
	{
		interrupt_handlers[regs->int_no](regs);
	}
}

void register_interrupt_handler(uint8_t n,interrupt_handler_t h){
    interrupt_handlers[n] = h;
}

void initIDTR(){
    idt_ptr.limit = sizeof(idt_entry_t)*256 -1;
    idt_ptr.base = (uint32_t)&idt_entries;
    idt_flush((uint32_t)&idt_ptr);
}

void initPIC(){
	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20);
	outb(0xA1, 0x28);
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	outb(0x21, 0x0);
	outb(0xA1, 0x0);
}

void initIDT(){
	bzero((uint8_t *)interrupt_handlers,sizeof(interrupt_handler_t) *256 );
	bzero((uint8_t *)idt_entries,sizeof(idt_entry_t)*256 );
    	// 0-32:  用于 CPU 的中断处理
	idt_set_gate( 0, (uint32_t)isr0,  0x08, 0x8E);
	idt_set_gate( 1, (uint32_t)isr1,  0x08, 0x8E);
	idt_set_gate( 2, (uint32_t)isr2,  0x08, 0x8E);
	idt_set_gate( 3, (uint32_t)isr3,  0x08, 0x8E);
	idt_set_gate( 4, (uint32_t)isr4,  0x08, 0x8E);
	idt_set_gate( 5, (uint32_t)isr5,  0x08, 0x8E);
	idt_set_gate( 6, (uint32_t)isr6,  0x08, 0x8E);
	idt_set_gate( 7, (uint32_t)isr7,  0x08, 0x8E);
	idt_set_gate( 8, (uint32_t)isr8,  0x08, 0x8E);
	idt_set_gate( 9, (uint32_t)isr9,  0x08, 0x8E);
	idt_set_gate(10, (uint32_t)isr10, 0x08, 0x8E);
	idt_set_gate(11, (uint32_t)isr11, 0x08, 0x8E);
	idt_set_gate(12, (uint32_t)isr12, 0x08, 0x8E);
	idt_set_gate(13, (uint32_t)isr13, 0x08, 0x8E);
	idt_set_gate(14, (uint32_t)isr14, 0x08, 0x8E);
	idt_set_gate(15, (uint32_t)isr15, 0x08, 0x8E);
	idt_set_gate(16, (uint32_t)isr16, 0x08, 0x8E);
	idt_set_gate(17, (uint32_t)isr17, 0x08, 0x8E);
	idt_set_gate(18, (uint32_t)isr18, 0x08, 0x8E);
	idt_set_gate(19, (uint32_t)isr19, 0x08, 0x8E);
	idt_set_gate(20, (uint32_t)isr20, 0x08, 0x8E);
	idt_set_gate(21, (uint32_t)isr21, 0x08, 0x8E);
	idt_set_gate(22, (uint32_t)isr22, 0x08, 0x8E);
	idt_set_gate(23, (uint32_t)isr23, 0x08, 0x8E);
	idt_set_gate(24, (uint32_t)isr24, 0x08, 0x8E);
	idt_set_gate(25, (uint32_t)isr25, 0x08, 0x8E);
	idt_set_gate(26, (uint32_t)isr26, 0x08, 0x8E);
	idt_set_gate(27, (uint32_t)isr27, 0x08, 0x8E);
	idt_set_gate(28, (uint32_t)isr28, 0x08, 0x8E);
	idt_set_gate(29, (uint32_t)isr29, 0x08, 0x8E);
	idt_set_gate(30, (uint32_t)isr30, 0x08, 0x8E);
	idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8E);

	idt_set_gate(32, (uint32_t)irq0, 0x08, 0x8E);
	idt_set_gate(33, (uint32_t)irq1, 0x08, 0x8E);
	idt_set_gate(34, (uint32_t)irq2, 0x08, 0x8E);
	idt_set_gate(35, (uint32_t)irq3, 0x08, 0x8E);
	idt_set_gate(36, (uint32_t)irq4, 0x08, 0x8E);
	idt_set_gate(37, (uint32_t)irq5, 0x08, 0x8E);
	idt_set_gate(38, (uint32_t)irq6, 0x08, 0x8E);
	idt_set_gate(39, (uint32_t)irq7, 0x08, 0x8E);
	idt_set_gate(40, (uint32_t)irq8, 0x08, 0x8E);
	idt_set_gate(41, (uint32_t)irq9, 0x08, 0x8E);
	idt_set_gate(42, (uint32_t)irq10, 0x08, 0x8E);
	idt_set_gate(43, (uint32_t)irq11, 0x08, 0x8E);
	idt_set_gate(44, (uint32_t)irq12, 0x08, 0x8E);
	idt_set_gate(45, (uint32_t)irq13, 0x08, 0x8E);
	idt_set_gate(46, (uint32_t)irq14, 0x08, 0x8E);
	idt_set_gate(47, (uint32_t)irq15, 0x08, 0x8E);

    idt_set_gate(255,(uint32_t)isr255,0x08,0x8E);
}