; Debug VGA driver
; Configures and manages the VGA hardware for debugging.
; Configured for Text mode 80x25, 16 colors and from address B8000-BFFFF

[BITS 32]

%macro outb 2
    mov dx, %1
	mov al, %2
	out dx, al
%endmacro

global debug_install_vga
debug_install_vga:
	outb 0x3CE, 0x06	; Specify index to GR06 (Miscellaneous)
	outb 0x3CF, 0x0C	; Enable text mode (from B8000 to BFFFF)
	
    outb 0x3D4, 0x0A	; Specify index to CR0A (Text cursor start)
	outb 0x3D5, 0x10	; Disable cursor
    
    ret
