/* Available included headers:
 * <stdbool.h>, <stddef.h>, <stdint.h>,
 * <float.h>, <iso646.h>, <limits.h>, 
 * <stdarg.h>
 */
#include <sys/io.h>
#include <sys/system.h> // sys_loadprocess
#include <desctables.h> // GDT, IDT and functions to add ISRs and IRQ handlers.
#include <math.h>       // Some math goodies
#include <stdlib.h>
#include <stdint.h>

#ifdef DEBUG
#include <debug.h> // If we're debugging, add some debugging functions
#endif

void main()
{
    // Initialize interrupts
    #ifdef ARCH_i386
    gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    #endif

    // Do some testing for now /////////////////////////////////
    #ifdef DEBUG

    kernel_lineString("\r\nProject Magma");

    #endif
    ////////////////////////////////////////////////////////////

    // Start receiving interrupts
    ints_set_enabled(true);
}