[BITS 32]

global paging_loaddir
paging_loaddir:
    pop ebx     ; Pop the EIP
    pop ecx     ; Pop the argument (page_directory)

    mov cr3, ecx    ; Set the current page directory
                    ; Note that it MUST be identity paged 
                    ; so the program can continue correctly

    push ecx    ; Push the argument back
    push ebx    ; Push the EIP back
    ret

global paging_enable
paging_enable:
    mov eax, cr0
    or eax, 0x80000001  ; Set the PAGING_ENABLE bit in CR0
    mov cr0, eax        ; Activate paging

    ret
    
global paging_disable
paging_disable:
    pop ebx     ; Pop the EIP

    mov eax, cr0
    and eax, 0x7FFFFFFF ; Unset the PAGING_ENABLE bit in CR0
    mov cr0, eax        ; Deactivate paging

    push ebx    ; Push the EIP back
    ret