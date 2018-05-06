#include <sys/io.h>
#include <stdbool.h>

// TODO: Move to ports.asm

unsigned char inb (unsigned short port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (port));
    return rv;
}
unsigned short inw (unsigned short port)
{
    unsigned short rv;
    __asm__ __volatile__ ("inw %1, %0" : "=a" (rv) : "dN" (port));
    return rv;
}
unsigned int inl (unsigned short port)
{
    unsigned int rv;
    __asm__ __volatile__ ("inl %1, %0" : "=a" (rv) : "dN" (port));
    return rv;
}
void outb (unsigned short port, unsigned char data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (data));
}
void outw (unsigned short port, unsigned short data)
{
    __asm__ __volatile__ ("outw %1, %0" : : "dN" (port), "a" (data));
}
void outl (unsigned short port, unsigned int data)
{
    __asm__ __volatile__ ("outl %1, %0" : : "dN" (port), "a" (data));
}

eflags_t get_eflags()
{
    int eax;

    __asm__ __volatile__("pushf; pop %0" : "=a"(eax));

    return (eflags_t)eax;
}

void ints_set_enabled(bool enable)
{
    if (enable)
    __asm__ __volatile__ ("sti");
    else
    __asm__ __volatile__ ("cli");
}
bool ints_get_enabled()
{
    unsigned long flags;
    __asm__ __volatile__ ("pushf; pop %0" : "=g"(flags) );
    return flags & (1 << 9);
}