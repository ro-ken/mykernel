ENTRY(start)

SECTIONS
{
    PROVIDE( kern_start = 0xC0100000);
    . = 0x100000;/*定义符号地址 */

    /*后面无参数，装载地址即符号地址 */
    .init.text : 
    {
        *(.init.text)
        . = ALIGN(4096);
    }
    
    .init.data :
    {
        *(.init.data)
        . = ALIGN(4096);
    }

    . += 0xC0000000;
    /* AT()表示装载的物理地址，ADDR()计算符号的地址 */
    .text : AT(ADDR(.text) - 0xC0000000)
    {
        *(.text)
        . = ALIGN(4096);
    }

    .data : AT(ADDR(.data) - 0xC0000000)
    {
        *(.data)
        *(.rodata)
        . = ALIGN(4096);
    }

    .bss : AT(ADDR(.bss) - 0xC0000000)
    {
        *(.bss)
        . = ALIGN(4096);
    }

    .stab : AT(ADDR(.stab) - 0xC0000000)
    {
        *(.stab)
        . = ALIGN(4096);
    }

    .stabstr : AT(ADDR(.stabstr) - 0xC0000000)
    {
        *(.stabstr)
        . = ALIGN(4096);
    }
    
    /DISCARD/ : {*(.comment) *(.eh_frame)}
    PROVIDE(kern_end = .);
}