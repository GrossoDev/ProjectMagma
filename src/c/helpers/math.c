#include <math.h>

unsigned long math_pow(int n, unsigned int p)
{
    return p != 0 ? math_pow(n, p-1) * n : 1;
}

unsigned long math_powoftwo(unsigned int p)
{
    return 1 << p;
}

// Special
unsigned long math_fibonnacci(unsigned int n)
{
    unsigned int x = 1, y = 1;

    unsigned int i;
    for (i = 0; i < n; i++) 
    {
        unsigned int z = x + y;
        x = y;
        y = z;
    }

    return y;
}

unsigned long math_factorial(unsigned int n)
{
    return n != 1 ? math_factorial(n-1) * n : 1;
}