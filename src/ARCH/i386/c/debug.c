#include <debug.h>
#include <sys/io.h>  // outb()
#include <stdlib.h>  // itoa()
#include <stdbool.h> // bool, true, false
#include <string.h>  // strlen()

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

void kernel_printException(struct regs_t *r)
{
    char buffer[32];
    
    kernel_putString(exception_messages[r->int_no]);
    kernel_lineString(" Exception. System Halted!");

    kernel_putString("==Error code: 0b");
    itoa((int)r->err_code, buffer, 2);
    kernel_lineString(buffer);

    kernel_putString("==At instruction: 0x");
    itoa((int)r->eip, buffer, 16);
    kernel_lineString(buffer);

    kernel_lineString("==Registers:");

    kernel_putString("====EAX: 0x");
    itoa((int)r->eax, buffer, 16); kernel_putString(buffer);

    kernel_putString("    EBX: 0x");
    itoa((int)r->ebx, buffer, 16); kernel_putString(buffer);

    kernel_putString("    ECX: 0x");
    itoa((int)r->ecx, buffer, 16); kernel_putString(buffer);

    kernel_putString("    EDX: 0x");
    itoa((int)r->edx, buffer, 16); kernel_lineString(buffer);

    // Add empty line
    kernel_lineString("");
}

enum {
  CPUID_GETVENDORSTRING,
  CPUID_GETFEATURES,
  CPUID_GETTLB,
  CPUID_GETSERIAL,
 
  CPUID_INTELEXTENDED=0x80000000,
  CPUID_INTELFEATURES,
  CPUID_INTELBRANDSTRING,
  CPUID_INTELBRANDSTRINGMORE,
  CPUID_INTELBRANDSTRINGEND,
};

bool kernel_cpuid()
{
    char buffer[64];
    int registers[4];

    kernel_lineString("\r\nCPUID: ");

    // Request vendor string
    asm volatile("cpuid":"=b"(*(registers)),"=c"(*(registers+2)),"=d"(*(registers+1)):
        "a"(CPUID_GETVENDORSTRING));
    
    int i;
    for (i = 0; i < 3; i++)
    {
        buffer[0+(i*4)] = registers[i];
        buffer[1+(i*4)] = (registers[i] >> 8);
        buffer[2+(i*4)] = (registers[i] >> 16);
        buffer[3+(i*4)] = (registers[i] >> 24);
    }
    buffer[12] = '\0';

    kernel_putString(" Vendor: "); kernel_lineString(buffer);

    // Request brand string
    // First part
    asm volatile("cpuid":"=a"(*(registers)),"=b"(*(registers+1)),"=c"(*(registers+2)),"=d"(*(registers+3)):
        "a"(CPUID_INTELBRANDSTRING));
    
    for (i = 0; i < 4; i++)
    {
        buffer[0+(i*4)] = registers[i];
        buffer[1+(i*4)] = (registers[i] >> 8);
        buffer[2+(i*4)] = (registers[i] >> 16);
        buffer[3+(i*4)] = (registers[i] >> 24);
    }
    // Second part
    asm volatile("cpuid":"=a"(*(registers)),"=b"(*(registers+1)),"=c"(*(registers+2)),"=d"(*(registers+3)):
        "a"(CPUID_INTELBRANDSTRINGMORE));
    
    for (i = 0; i < 4; i++)
    {
        buffer[0+(i*4+16)] = registers[i];
        buffer[1+(i*4+16)] = (registers[i] >> 8);
        buffer[2+(i*4+16)] = (registers[i] >> 16);
        buffer[3+(i*4+16)] = (registers[i] >> 24);
    }
    // Third part
    asm volatile("cpuid":"=a"(*(registers)),"=b"(*(registers+1)),"=c"(*(registers+2)),"=d"(*(registers+3)):
        "a"(CPUID_INTELBRANDSTRINGEND));
    
    for (i = 0; i < 4; i++)
    {
        buffer[0+(i*4+32)] = registers[i];
        buffer[1+(i*4+32)] = (registers[i] >> 8);
        buffer[2+(i*4+32)] = (registers[i] >> 16);
        buffer[3+(i*4+32)] = (registers[i] >> 24);
    }
    buffer[48] = '\0';

    kernel_putString(" Brand: "); kernel_lineString(buffer);

    // Request features
    asm volatile("cpuid":"=a"(*registers),"=b"(*(registers+1)),"=c"(*(registers+2)),"=d"(*(registers+3)):
        "a"(CPUID_GETFEATURES));
    
    btoa((registers[1] >> 9) & 0b1, buffer);
    kernel_putString(" Vx86 supported?: "); kernel_lineString(buffer);
    btoa((registers[1] >> 9) & 0b1, buffer);
    kernel_putString(" On-board APIC?: "); kernel_lineString(buffer);
    btoa((registers[1] >> 11) & 0b1, buffer);
    kernel_putString(" SYSENTER-SYSEXIT supported?: "); kernel_lineString(buffer);
    btoa((registers[2] >> 31) & 0b1, buffer);
    kernel_putString(" Is hypervised?: "); kernel_lineString(buffer);
    btoa((registers[2] >> 30) & 0b1, buffer);
    kernel_putString(" RDRAND (on-chip random number generator) supported?: "); kernel_lineString(buffer);
    
    asm volatile("cpuid":"=a"(*registers),"=b"(*(registers+1)),"=c"(*(registers+2)),"=d"(*(registers+3)):
        "a"(CPUID_INTELFEATURES));

    btoa((registers[1] >> 20) & 0b1, buffer);
    kernel_putString(" NX bit supported?: "); kernel_lineString(buffer);
    btoa((registers[1] >> 29) & 0b1, buffer);
    kernel_putString(" Long mode supported?: "); kernel_lineString(buffer);

    // Add empty line
    kernel_lineString("");
}

unsigned char *exception_messages[] =
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};