#ifndef __SYSCALLS_H
#define __SYSCALLS_H

#include <desctables.h>

extern void syscall_install(int int_no);
extern void syscall_installhandler(void* handler);
extern void syscall_handler(struct regs_t *r);

#endif