#ifndef __STRING_H
#define __STRING_H

#include <stddef.h>
#include <stdint.h>

extern void *memcpy(void *dest, void *src, size_t n);
extern void *memmove(void *dest, void *src, size_t n);
extern void *memset(void *dest, uint8_t c, int len);
extern void *memsetw(void *dest, uint16_t c, int len);
extern void *memsetd(void *dest, uint32_t c, int len);
extern void *memsetl(void *dest, uint64_t c, int len);

extern size_t strlen(const char *str); // A utility function to get the size of a string

#endif