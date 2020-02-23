; Debug serial driver
; Configures and manages a serial port for debugging.
; Configured for COM1 (0x3F8), 9600 bauds 8N1

[BITS 32]

%macro serial 2
    mov al, %2
    out 0x3F8 + %1, al
%endmacro

global debug_install_serial
debug_install_serial:
    serial 1, 0x00		; Disable interrupts from serial
    
                  		; Line control register
                  		; Configure serial to 9600 baud 8N1
    serial 3, 0x80		; Enable DLAB to set baud rate divisor to 12
    serial 0, 0x0C		; Lo byte of decimal divisor
    serial 1, 0x00		; Hi byte
    serial 3, 0x03		; 8 bits - No parity - 1 stop bit
    
    serial 2, 0xC7		; Enable FIFO, clear RX & TX and trigger at 14 bytes
    
    serial 4, 0x0B		; Reenable interrupts and set RTS & DTR to HIGH

    ret
