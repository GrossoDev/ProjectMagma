; Debug VGA driver
; Configures and manages the VGA adapter for debugging.
; Configured for Text mode 80x25, 16 colors and from address B8000-BFFFF

[BITS 32]
%macro outb 2
    mov dx, %1
	mov al, %2
	out dx, al
%endmacro

global debug_install_vga, vga_put_char


debug_install_vga:
	outb 0x3CE, 0x06	; Specify index to GR06 (Miscellaneous)
	outb 0x3CF, 0x0C	; Enable text mode (from B8000 to BFFFF)
	
    outb 0x3D4, 0x0A	; Specify index to CR0A (Text cursor start)
	outb 0x3D5, 0x10	; Disable cursor
    
	mov byte [vga_installed], 0x1
	mov byte [current_col], 0x0

    ret


; Sends a character through the VGA display
; The character to send is to be passed through AL
; The color is to be passed through AH
vga_put_char:
	; Check if the newline character has been passed
    cmp al, 0x0A
	jne .not_a_newline
		;call vga_scroll
		ret
	.not_a_newline:

	; Write it to the last line
	; last_char_address - max_columns(in bytes) + cur_column(in bytes)
	mov ebx, [current_col]
	mov [0xB8FA0 - 80*2 + ebx*2], ax

	inc byte [current_col]

	; Check if the line is full
	cmp byte [current_col], 80
	jl .line_not_full
		;call vga_scroll
	.line_not_full:

	ret


SECTION .bss
current_col: resb 1
vga_installed: db 0		; Flag that represents if this output is enabled