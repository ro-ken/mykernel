
[global switch_to]

switch_to:
    ;保存前一个现场
    mov eax,[esp+4]
    mov [eax+0],esp
    mov [eax+4],ebp
    mov [eax+8],ebx
    mov [eax+12],esi
    mov [eax+16],edi
    pushf   ;  将eflag压入栈顶
    pop ecx
    mov [eax+20],ecx

    mov eax,[esp+8]
    ;恢复后一个现场
    mov esp,[eax+0]
    mov ebp,[eax+4]
    mov ebx,[eax+8]
    mov esi,[eax+12]
    mov edi,[eax+16]
    mov eax,[eax+20]    ;  eflags -> eax -> eflags
    push eax
    popf
    ret
