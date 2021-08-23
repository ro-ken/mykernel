

MAGIC equ 0x1BADB002
FLAGS equ 0x00000003
CHECKSUM equ -(MAGIC+FLAGS)

STACKSIZE equ 1024; * 32

[bits 32]
[global start]
[global mboot_ptr_tmp]
[EXTERN kern_entry]

section .init.text

dd MAGIC
dd FLAGS
dd CHECKSUM

start:
	cli
	mov esp,STACKSIZE
	;mov esp,stack+STACKSIZE
	mov ebp,0
	mov [mboot_ptr_tmp],ebx
	call kern_entry

stop:
	hlt
	jmp stop

section .init.data

;stack:
;	resb STACKSIZE
mboot_ptr_tmp:
	resb 4

;dd define double word 4
;dw define word 2
;db define byte 1
;STACK_TOP equ $-stack-4


