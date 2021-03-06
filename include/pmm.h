#ifndef INCLUDE_PMM_H_
#define INCLUDE_PMM_H_

#include "multiboot.h"

#define STACK_SIZE 8192

#define PMM_MAX_SIZE 0x20000000

#define PMM_PAGE_SIZE 0x1000

#define PAGE_MAX_SIZE (PMM_MAX_SIZE / PMM_PAGE_SIZE)
//地址掩码4KB对齐
#define PHY_PAGE_MASK 0xFFFFF000

// 输出 BIOS 提供的物理内存布局
void show_memory_map();

extern uint8_t kern_start[];
extern uint8_t kern_end[];

extern uint32_t phy_page_count;
extern uint32_t kern_stack_top;

void show_memory_map();

void init_pmm();

uint32_t pmm_alloc_page();

void pmm_free_page(uint32_t p);

#endif  // INCLUDE_PMM_H_