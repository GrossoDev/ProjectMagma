#ifndef __DEBUG_H
#define __DEBUG_H

#include <stdbool.h>
#include <sys/desctables.h>

extern void kernel_putString(char* str);
extern void kernel_lineString(char* str);

extern void kernel_printException(struct regs_t *r);
extern bool kernel_cpuid(void);

extern unsigned char *exception_messages[];

#endif