/* Available included headers:
 * <stdbool.h>, <stddef.h>, <stdint.h>,
 * <float.h>, <iso646.h>, <limits.h>, 
 * <stdarg.h>
 */
#include <sys/io.h>
#include <sys/system.h> // sys_loadprocess
#include <desctables.h> // GDT, IDT and functions to add ISRs and IRQ handlers.
#include <math.h>       // Some math goodies
#include <time.h>       // The PIT (a timer) and the RTC (real time clock)
#include <stdlib.h>
#include <stdint.h>

#ifdef DEBUG
#include <debug.h> // If we're debugging, add some debugging functions
#endif

void main()
{
    // Initialize descriptor tables
    gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    // Initialize timer
    timer_install();

    ////////////////////////////////////////////////////////////
    // Do some testing by now
    #ifdef DEBUG

    kernel_lineString("\r\nProject Magma");
    
    kernel_putString("Current GMT-3 time: ");
    char buffer[16];
    itoa( math_roll(rtc_get_utchour()-3,24), buffer, 10); kernel_putString(buffer);
    kernel_putString(":");
    itoa( math_roll(rtc_get_utcminute(),60), buffer, 10); kernel_putString(buffer);
    kernel_putString(":");
    itoa( math_roll(rtc_get_utcsecond(),60), buffer, 10); kernel_lineString(buffer);

    #endif
    ////////////////////////////////////////////////////////////

    // Start receiving interrupts
    ints_set_enabled(true);
}