#ifndef __MATH_H
#define __MATH_H

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