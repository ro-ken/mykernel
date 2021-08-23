#!Makefile

##### 变量区↓
C=$(shell find . -name "*.c")
S=$(shell find . -name "*.s")
C_O=$(patsubst %.c,%.o,$(C))
S_O=$(patsubst %.s,%.o,$(S))
 
AS=nasm
CC=gcc
LD=ld

CC_PARAM=-c -Wall -m32 -ggdb -gstabs+ -nostdinc  -fno-pic  -fno-builtin -fno-stack-protector -I include
AS_PARAM=-f elf -g -F stabs
LD_PARAM=-T scripts/kernel.ld -m elf_i386 -nostdlib

#####变量区↑

default:make

# 编译kernel并安装到img
make:hx_kernel mount install umount

hx_kernel: $(S_O) $(C_O) 
	$(LD) $^ $(LD_PARAM) -o $@

# 隐晦规则
.s.o:
	$(AS) $^ $(AS_PARAM) -o $@ 

.c.o:
	$(CC) $^ $(CC_PARAM) -o $@

#单命令区
clean:
	rm $(C_O) $(S_O) hx_kernel

qemu:
	qemu -fda floppy.img -boot a

mount:
	sudo mount floppy.img /mnt/kernel

umount:
	sudo umount /mnt/kernel

uninstall:
	sudo rm /mnt/kernel/hx_kernel

install:
	sudo cp hx_kernel /mnt/kernel/

debug:
	qemu -S -s -fda floppy.img -boot a &
	sleep 1
	cgdb -x scripts/gdbinit

#在img上删除kernel
clear:mount uninstall umount

reset:clean clear

run:qemu

mrun:make run

rrun:reset run