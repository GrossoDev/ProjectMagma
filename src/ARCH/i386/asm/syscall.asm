extern syscall_handler
global syscall_do

syscall_do:
    pusha
    push ds
    push es
    push fs
    push gs

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp

    push eax
    mov eax, syscall_handler
    call eax
    pop eax

    pop gs
    pop fs
    pop es
    pop ds
    popa
    iret