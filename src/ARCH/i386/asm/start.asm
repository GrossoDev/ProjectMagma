[BITS 32]
global start
start:                  ; The kernel's bootstrap
    mov esp, _sys_stack ; This points the stack to our new stack area
    jmp entry

; This part MUST be 4byte aligned, so we solve that issue using 'ALIGN 4'
; This is what grub has to recognize to bootup the kernel.
ALIGN 4
mboot:
    ; Multiboot macros to make a few lines later more readable
    MULTIBOOT_PAGE_ALIGN	equ 1<<0
    MULTIBOOT_MEMORY_INFO	equ 1<<1
    MULTIBOOT_AOUT_KLUDGE	equ 1<<16
    MULTIBOOT_HEADER_MAGIC	equ 0x1BADB002
    MULTIBOOT_HEADER_FLAGS	equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO | MULTIBOOT_AOUT_KLUDGE
    MULTIBOOT_CHECKSUM	    equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
    EXTERN code, bss, end

    ; This is the GRUB Multiboot header. A boot signature
    dd MULTIBOOT_HEADER_MAGIC
    dd MULTIBOOT_HEADER_FLAGS
    dd MULTIBOOT_CHECKSUM
    
    ; AOUT kludge - must be physical addresses. Make a note of these:
    ; The linker script fills in the data for these ones!
    dd mboot
    dd code
    dd bss
    dd end
    dd start

; "kernel_setup()" is in C.
entry:
    extern kernel_setup
    call kernel_setup
    call prepair_entryprocess ; Prepair the OS' bootstrap
global system_halt
system_halt:
    hlt
    jmp system_halt    ; We'll have headaches if we get here

prepair_entryprocess:
    ret

; Remember that a stack actually grows downwards, so
; we declare the size of the data before declaring
; the identifier '_sys_stack'
SECTION .bss
global _sys_log
_sys_log:       ; The log grows upwards
    resb 64	    ; This reserves the log here
    resb 1024	; and the stack here
_sys_stack:     ; Remember, the stack grows downwards