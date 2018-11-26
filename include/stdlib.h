#ifndef __STDLIB_H
#define __STDLIB_H

#include <stdbool.h>

extern void reverse(char s[]);
extern char* itoa(int num, char* str, int base);
extern char* btoa(bool value, char* str);

#endif