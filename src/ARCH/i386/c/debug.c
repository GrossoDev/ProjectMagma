#include <debug.h>
#include <sys/io.h> // outb()
#include <stdlib.h> // itoa()
#include <string.h> // strlen()

////////
#define PORT 0x3F8 // COM1

void serial_init()
{
    outb(PORT + 1, 0x00);    // Disable all interrupts
    outb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    outb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    outb(PORT + 1, 0x00);    //                  (hi byte)
    outb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
    outb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    outb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}
int is_transmit_empty() {
    return inb(PORT + 5) & 0x20;
}
void putChar(char ch)
{
    while (is_transmit_empty() == 0);
 
    outb(PORT,ch);
}
////////

void kernel_putString(char* str)
{
    int i, len = strlen((const char*)str);
    for (i = 0; i < len; i++)
    {
        putChar(str[i]);
    }
}
void kernel_lineString(char* str)
{
    kernel_putString(str);
    kernel_putString("\r\n");
}

void kernel_putStacktrace(int max)
{
    void* stackptr;
    __asm__ __volatile__ ("mov %%esp, %0" : "=a" (stackptr));

    // First, capture the stack
    int* addrs[max];
    int values[max];

    int i;
    for (i = 0; stackptr + i < stackptr + max; i++)
    {
        addrs[i]  = (int*)stackptr + i;
        values[i] = *(addrs[i]);
    }

    // Then write it to the serial
    char text[10];
    kernel_lineString("Stack trace: ");

    for (i = 0; i < max; i++)
    {
        kernel_putString("At: 0x");
        itoa((int)addrs[i], text, 16);
        kernel_putString(text);
        kernel_putString(" = 0x");
        itoa(values[i], text, 16);
        kernel_lineString(text);
    }
}