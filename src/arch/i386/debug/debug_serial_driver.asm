; Debug serial driver
; Configures and manages a serial port for debugging.
; Configured for COM1 (0x3F8), 9600 bauds 8N1

[BITS 32]
%define PORT 0x3F8

%macro serial 2
    mov al, %2
    mov dx, PORT + %1
    out dx, al
%endmacro


; Configures the Serial port to 9600 bauds - 8N1
; Uses: AL
global debug_install_serial
debug_install_serial:
    serial 1, 0x00		; Disable interrupts from serial
    
                  		; Line control register
    serial 3, 0x80		; Enable DLAB
    serial 0, 0x0C		; Lo byte of decimal divisor (12 for 9600)
    serial 1, 0x00		; Hi byte (not used)
    serial 3, 0x03		; 8 bits - No parity - 1 stop bit
    
    serial 2, 0xC7		; Enable FIFO, clear RX & TX and trigger at 14 bytes
    
    serial 4, 0x0B		; Reenable interrupts and set RTS & DTR to HIGH

    mov byte [serial_installed], 0x1

    ret


; Sends a character through the serial port
; The character to send is to be passed through AL
global serial_put_char
serial_put_char:
    ; Check if the Serial output is enabled
    cmp byte [serial_installed], 0x1
    jne .serial_enabled
        ret
    .serial_enabled:

    ; Commented out because QEMU doesn't seem to like this
    ; push ax				; serial_transmit_ready will use AL
    ;
    ; .wait_to_transmit:
    ;     call serial_transmit_ready
    ; jnz .wait_to_transmit
    ;
    ; pop ax

    push ax             ; The comparation uses AL

    ; Put a CR before a LF
    cmp byte al, 0x0A
    jne .not_lf
        serial 0, 0x0D
    .not_lf:

    pop ax
    
    serial 0, al

    ret


; Checks if the port is ready to receive another character.
; Sets the zero flag if it's ready.
; Uses: AL
serial_transmit_ready:
    in al, PORT + 5		; From the Line status register
    test al, 0x20		; Check the Transmit Holding Register Empty flag
    ret


serial_installed: db 0    ; Flag that represents if this output is enabled