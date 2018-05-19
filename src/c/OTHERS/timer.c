/* This file doesn't get compiled.
 * It's here just for reference */

#include <time.h>
#include <desctables.h> // irq_install_handler

// Ticks since the kernel booted up
volatile unsigned timer_ticks = 0;
float timer_tickrate;

// Convertion helpers
float timer_ticktosec  (int ticks) { return ticks/timer_tickrate;        }
float timer_ticktomilli(int ticks) { return ticks/(timer_tickrate/1000); }
int   timer_sectoticks (int secs)  { return secs*timer_tickrate;         }
int   timer_millitotick(int milli) { return milli*(timer_tickrate/1000); }

// Handles the timer.
void timer_handler(struct regs_t *r)
{
    // Increment the tick count
    timer_ticks++;
}

// Wait until the desired amount of ticks have been reached.
void timer_waitticks(int ticks)
{
    unsigned long eticks;

    eticks = timer_ticks + ticks;
    while(timer_ticks < eticks)
    {
        __asm__ __volatile__ ("sti;hlt;cli");
    }
}

// Install a Interrupt Request Handler at IRQ0 to handle the timer
void timer_install()
{
    // By default, the timer fires 18.222 times per second.
    timer_tickrate = 18 + 2/9;

    // Installs 'timer_handler' to IRQ0
    irq_install_handler(0, timer_handler);
}