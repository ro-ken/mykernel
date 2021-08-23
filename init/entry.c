
#include "console.h"
#include "string.h"
#include "debug.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "pmm.h"
#include "vmm.h"
#include "heap.h"
#include "task.h"
#include "sched.h"

multiboot_t *glb_mboot_ptr;
//待会把数组换成指针
char kern_stack[STACK_SIZE];

void kern_init();

//临时页目录和页表，这块空间为什么是空闲的
__attribute__((section(".init.data")))pgd_t *pgd_tmp = (pgd_t *)0x1000;
__attribute__((section(".init.data")))pgd_t *pte_low = (pgd_t *)0x2000;
__attribute__((section(".init.data")))pgd_t *pte_high = (pgd_t *)0x3000;

// 内核栈的栈顶
uint32_t kern_stack_top;

__attribute__((section(".init.text"))) void kern_entry(){
	pgd_tmp[0] = (uint32_t)pte_low | PAGE_PRESENT | PAGE_WRITE;
	pgd_tmp[PGD_INDEX(PAGE_OFFSET)] = (uint32_t)pte_high|PAGE_PRESENT | PAGE_WRITE;

	int i;
	for (i = 0; i < 1024; i++)
	{
		pte_low[i] = (i<<12) | PAGE_PRESENT | PAGE_WRITE;
		pte_high[i] = (i<<12) | PAGE_PRESENT | PAGE_WRITE;
	}

	asm volatile("mov %0,%%cr3"::"r"(pgd_tmp));

	uint32_t cr0;

	// 启用分页，将 cr0 寄存器的分页位置为 1 就好
	asm volatile ("mov %%cr0, %0" : "=r" (cr0));
	cr0 |= 0x80000000;
	asm volatile ("mov %0, %%cr0" : : "r" (cr0));

	kern_stack_top = ((uint32_t)kern_stack + STACK_SIZE ) & 0xFFFFFFF0;
	asm volatile("mov %0,%%esp\n"
				"xor %%ebp,%%ebp"::"r"(kern_stack_top));

	glb_mboot_ptr = (multiboot_t *)((uint32_t)mboot_ptr_tmp + PAGE_OFFSET);

	kern_init();

}

int flag = 0;

int thread(void *args){
	while (1)
	{
		if (flag == 1)
		{
			printk_color(rc_black,rc_green,"B");
			flag = 0;
		}
	}
	return 0;
}

void kern_init()
{
	// 从 GRUB 中获取elf内核符号表和代码地址信息
	init_debug();
	console_clear();

	init_gdt();
	init_idt();
	//printk("test = %d = %x \n",12,20);
	console_write("hello ro_ken's kernel!\n");
	console_write("======================\n");
	//asm volatile ("int $0x08");
	asm volatile ("int $0x09");
	//asm volatile ("int $0x0a");
	console_write("======================\n");
	init_keyboard();
	//init_timer();
	//asm volatile("sti");

	printk("kernel in memory start: 0x%08X\n",kern_start);
	printk("kernel in memory end: 0x%08X\n",kern_end);
	printk("kernel in memory used %d KB\n\n",(kern_end - kern_start)/1024);

	show_memory_map();
	
	init_pmm();

	printk_color(rc_black, rc_red, "\nThe Count of Physical Memory Page is: %u\n\n", phy_page_count);

	uint32_t allc_addr = NULL;
	printk_color(rc_black, rc_light_brown, "Test Physical Memory Alloc :\n");
	allc_addr = pmm_alloc_page();
	printk_color(rc_black, rc_light_brown, "Alloc Physical Addr: 0x%08X\n", allc_addr);
	allc_addr = pmm_alloc_page();
	printk_color(rc_black, rc_light_brown, "Alloc Physical Addr: 0x%08X\n", allc_addr);
	allc_addr = pmm_alloc_page();
	printk_color(rc_black, rc_light_brown, "Alloc Physical Addr: 0x%08X\n", allc_addr);
	allc_addr = pmm_alloc_page();
	printk_color(rc_black, rc_light_brown, "Alloc Physical Addr: 0x%08X\n", allc_addr);

	init_vmm();
	init_heap();

	test_heap();

	init_sched();

	kernel_thread(thread,NULL);

	asm volatile("sti");
	while (1)
	{
		if (flag == 0)
		{
			printk_color(rc_black,rc_red,"A");
			flag = 1;
		}		
	}
	

	while (1) {
		asm volatile ("hlt");
	}
}

