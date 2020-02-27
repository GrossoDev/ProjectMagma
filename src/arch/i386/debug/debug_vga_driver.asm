; Debug VGA driver
; Configures and manages the VGA adapter for debugging.
; Configured for Text mode 80x25, 16 colors and from address B8000-BFFFF

[BITS 32]
%macro outb 2
    mov dx, %1
	mov al, %2
	out dx, al
%endmacro


; Configures the VGA adapter.
; Uses: AL, DX
global debug_install_vga
debug_install_vga:
	outb 0x3CE, 0x06	; Specify index to GR06 (Miscellaneous)
	outb 0x3CF, 0x0C	; Enable text mode (from B8000 to BFFFF)
	
    outb 0x3D4, 0x0A	; Specify index to CR0A (Text cursor start)
	outb 0x3D5, 0x10	; Disable cursor
    
	mov byte [current_col], 0x0
	mov byte [vga_installed], 0x1

    ret


; Sends a character through the VGA display
; The character to send is to be passed through AL
; The color is to be passed through AH
; Used: EAX, EBX, ECX(vga_scroll)
global vga_put_char
vga_put_char:
	; Check if the VGA output is enabled
    test byte [vga_installed], 0x1
    jnz .vga_enabled
        ret
    .vga_enabled:

	; Check if the newline character has been passed
    cmp al, 0x0A
	jne .not_a_newline
		call vga_scroll
		ret
	.not_a_newline:

	; Write it to the last line
	; last_char_address - max_columns(in bytes) + cur_column(in bytes)
	mov ebx, 0				; Make sure the rest of the register is 0
	mov bl, [current_col]	; mov only a byte, not a dword
	mov [0xB8FA0 - 80*2 + ebx*2], ax

	inc byte [current_col]

	; Check if the line is full
	cmp byte [current_col], 80
	jl .line_not_full
		call vga_scroll
	.line_not_full:

	ret

; Moves the content on the display 1 row up
; Uses: EAX, ECX
vga_scroll:
    ; Copy:
    ; 0xB8000 + 80*2 | 0xB8FA0
    ; To:
    ; 0xB8000 | 0xB8FA0 - 80*2
    mov ecx, 0x0
    .loop:
        mov al, [0xB80A0 + ecx]
        mov [0xB8000 + ecx], al
    inc ecx
    cmp ecx, 0xFA0
    jl .loop

    mov byte [current_col], 0x0

    ret


current_col: resb 1
vga_installed: db 0		; Flag that represents if this output is enabled