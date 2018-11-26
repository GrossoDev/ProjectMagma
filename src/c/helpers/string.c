#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

void *memcpy(void *dest, void *src, size_t n)
{
    // Typecast src and dest addresses to (char *)
    char *csrc = (char *)src;
    char *cdest = (char *)dest;

    // Copy contents of src[] to dest[]
    int i;
    for (i=0; i<n; i++)
        cdest[i] = csrc[i];

    return dest;
}
void *memmove(void *dest, void *src, size_t n)
{
    // Typecast src and dest addresses to (char *)
    char *csrc = (char *)src;
    char *cdest = (char *)dest;
 
    // Create a temporary array to hold data of src
    char temp[n];
 
    int i;
    // Copy data from csrc[] to temp[]
    for (i = 0; i < n; i++)
        temp[i] = csrc[i];
 
    // Copy data from temp[] to cdest[]
    for (i = 0; i < n; i++)
        cdest[i] = temp[i];
 
    return dest;
}
void *memset(void *dest, uint8_t c, int len)
{
    int i;
    uint8_t *cdest = (uint8_t*)dest;

    for (i = 0; i < len; i++)
    {
        cdest[i] = c;
    }
}
void *memsetw(void *dest, uint16_t c, int len)
{
    int i;
    uint16_t *wdest = (uint16_t*)dest;

    for (i = 0; i < len; i++)
    {
        wdest[i] = c;
    }
}
void *memsetd(void *dest, uint32_t c, int len)
{
    int i;
    uint32_t *ddest = (uint32_t*)dest;

    for (i = 0; i < len; i++)
    {
        ddest[i] = c;
    }
}
void *memsetl(void *dest, uint64_t c, int len)
{
    int i;
    uint64_t *ldest = (uint64_t*)dest;

    for (i = 0; i < len; i++)
    {
        ldest[i] = c;
    }
}

// A utility function to get the size of a string
size_t strlen(const char *str)
{
    size_t retval;
    for(retval = 0; *str != '\0'; str++) retval++;
    return retval;
}

char *strcpy(char *dest, const char *src)
{
    // Copy contents of src[] to dest[]
    int i = 0;
    do
    {
        dest[i] = src[i];
    }
    while (src[i++] != '\0');

    return dest;
}

// A utility function to reverse a string
void reverse(char s[])
{
    int i, j;
    char c;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

// Implementation of itoa()
char* itoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;
 
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i] = '0';
        str[++i] = '\0';
        return str;
    }
 
    // In standard itoa(), negative numbers are handled only with 
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }
 
    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    reverse(str);
 
    return str;
}

// Convert boolean to string
char* btoa(bool value, char* str)
{
    if (value) strcpy(str, "TRUE");
    else       strcpy(str, "FALSE");

    return str;
}