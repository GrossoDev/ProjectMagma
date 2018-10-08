/* Available included headers:
 * <stdbool.h>, <stddef.h>, <stdint.h>,
 * <float.h>, <iso646.h>, <limits.h>, 
 * <stdarg.h>
 */
#include <sys/io.h>
#include <sys/system.h>     // sys_loadprocess
#include <sys/syscalls.h>   // syscall_install
#include <sys/syslog.h>
#include <sys/desctables.h>   // GDT, IDT and functions to add ISRs and IRQ handlers.
#include <sys/paging.h>     // paging_setup();
#include <math.h>           // Some math goodies
#include <stdlib.h>
#include <stdint.h>

#ifdef DEBUG
#include <debug.h> // If we're debugging, add some debugging functions
#endif

// It's platform independent, so
// we declare it in the assembly file
// "start.asm"
extern syslog_t _sys_log;

void kernel_setup()
{
    // Initialize 
    #ifdef ARCH_i386
    gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    
    paging_pagekernel();

    syscall_install(0x42);
    #endif
    
    // Push current version to the system log
    int syslog_i = 0;
    _sys_log.messages[syslog_i++] = (sysmsg_t){ KERNEL_VER, 0x0001 };

    // Do some testing for now /////////////////////////////////
    #ifdef DEBUG

    kernel_lineString("Project Magma");
    kernel_cpuid();

    #endif
    ////////////////////////////////////////////////////////////

    // Start receiving interrupts
    ints_set_enabled(true);
}