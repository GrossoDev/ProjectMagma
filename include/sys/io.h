#ifndef __IO_H
#define __IO_H

#include <stdbool.h>

// IO.C
extern unsigned char inb (unsigned short port);
extern unsigned short inw(unsigned short port);
extern unsigned int inl(unsigned short port);
extern void outb(unsigned short port, unsigned char data);
extern void outw(unsigned short port, unsigned short data);
extern void outl(unsigned short port, unsigned int data);

typedef union {
    struct {
        int carryflag : 1;
        int reserved1 : 1;
        int parityflag : 1;
        int reserved2 : 1;
        int auxiliaryflag : 1;
        int reserved3 : 1;
        int zeroflag : 1;
        int signflag : 1;
        int trapflag : 1;
        int interruptflag : 1;
        int directionflag : 1;
        int overflowflag : 1;
        int iopl : 2;
        int nestedtask : 1;
        int resumeflag : 1;
        int vmflag : 1;
        int algmntchkflag : 1;
        int viflag : 1;
        int vipendingflag : 1;
        int idflag : 1;
    };

    int value;
} eflags_t;

extern eflags_t get_eflags(void);

extern void ints_set_enabled(bool enable);
extern bool ints_get_enabled(void);

#endif