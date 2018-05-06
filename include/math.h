#ifndef __MATH_H
#define __MATH_H

//
// Unit helpers
//
#define UINT8_MAX 255
#define INT8_MAX 127
#define INT8_MIN -128

#define UINT16_MAX 65535
#define INT16_MAX 32783
#define INT16_MIN -32784

#define UINT32_MAX 4294967295
#define INT32_MAX 2147483647
#define INT32_MIN -2147483648

#define UINT64_MAX 18446744073709551615
#define INT64_MAX 9223372036854775807
#define INT64_MIN -9223372036854775808

//
// MATH.H
//
#define math_PI 3.14159265359
#define math_E 2.71828182846

extern unsigned long math_pow(int n, unsigned int p);
extern unsigned long math_powoftwo(unsigned int p);
extern unsigned long math_fibonnacci(unsigned int n);
extern unsigned long math_factorial(unsigned int n);

#define math_abs(n) n < 0 ? -n : n
#define math_max(a,b) a < b ? b : a
#define math_min(a,b) a > b ? b : a
#define math_roll(n,rollat) n < 0 ? rollat + n : n % rollat

#endif