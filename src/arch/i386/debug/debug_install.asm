; Debug install
; Initializes debugging functions and outputs.

[BITS 32]

%define DEBUG_INSTALL_ASM
%include "debug/debug.mac"

extern debug_install_vga, debug_install_serial
extern serial_put_char

global debug_install
debug_install:
	mov [debug_flags], eax	; Store debug flags

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

    ret

SECTION .bss
debug_flags resb 1
