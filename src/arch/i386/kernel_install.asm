; Kernel install
; Entry point for the kernel.
; Initializes the hardware and sets-up the environment to start the kernel.

[BITS 32]

%include "debug/debug.mac"

global kernel_install
kernel_install:
%ifdef DEBUG
    mov eax, INSTALL_VGA | INSTALL_SERIAL
    call debug_install
%endif

    jmp $
