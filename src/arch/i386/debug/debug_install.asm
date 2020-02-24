; Debug install
; Initializes debugging functions and outputs.
; Can be initialized to use the Serial port, the VGA display or both.

[BITS 32]
%define DEBUG_INSTALL_ASM
%include "debug/debug.mac"
extern debug_install_vga, debug_install_serial
extern serial_put_char, vga_put_char

global debug_install


debug_install:
	; Check if vga flag is set
    test eax, INSTALL_VGA
    jz no_vga
        call debug_install_vga
    no_vga:
    
    ; Check if serial flag is set
    test eax, INSTALL_SERIAL
    jz no_serial
        call debug_install_serial
    no_serial:

    ; TODO: Remove test
    mov cx, 80
.loop:
    mov al, 'A'
    mov ah, cl
    call vga_put_char
    loop .loop

    ret
