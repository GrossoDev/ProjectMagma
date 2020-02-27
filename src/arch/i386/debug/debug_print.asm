; Debug print
; Provides the functions to print to the installed devices.

[BITS 32]
%define DEBUG_PRINT_ASM
%include "debug/debug.mac"
extern debug_install_vga, debug_install_serial, serial_put_char, vga_put_char

; Prints a null terminated string.
; The pointer to the string is to be passed through SI
global debug_print_string
debug_print_string:
    pusha           ; Save the SI

    .loop:
        lodsb       ; Get byte from string.
        
        ; Check if it is null (end of the string)
        cmp al, 0x0
        je .end

        call debug_put_char
        jmp .loop
    .end:

    popa

    ret


debug_put_char:
    call serial_put_char

    mov ah, 0x12
    call vga_put_char

    ret