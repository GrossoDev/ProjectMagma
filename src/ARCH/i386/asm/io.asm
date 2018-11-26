; sys/io.h

global ints_set_enabled, ints_get_enabled
ints_set_enabled:
    push ebp
    mov ebp, esp

    or dword [ebp+8], 0
    jz .clear_ints

    sti
.exit:
    pop ebp
    ret
.clear_ints:
    cli
    jmp .exit

ints_get_enabled:
    call get_eflags

    shr eax, 9
    and eax, 1

    ret

global get_eflags
get_eflags:
    pushf
    pop eax

    ret
    
global noop
noop:
    nop
    ret
;
; OUT functions
;

global outb, outw, outl
outb:
    push ebp
    mov ebp, esp

    mov dx, [ebp+8]
    mov al, [ebp+12]
    out dx, al

    pop ebp
    ret
outw:
    push ebp
    mov ebp, esp

    mov dx, [ebp+8]
    mov ax, [ebp+12]
    out dx, ax

    pop ebp
    ret
outl:
    push ebp
    mov ebp, esp

    mov dx, [ebp+8]
    mov eax, [ebp+12]
    out dx, eax

    pop ebp
    ret

;
; IN functions
;

global inb, inw, inl
inb:
inw:
inl:
    push ebp
    mov ebp, esp

    mov dx, [ebp + 8]
    in eax, dx

    pop ebp
    ret