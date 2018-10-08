#ifndef __PAGING_H__
#define __PAGING_H__

#include <stdint.h>

typedef struct cr3_s
{
    union
    {
        struct
        {
            int IGNORE : 3;
            int write_through : 1;
            int cache_disabled : 1;
            int IGNORED : 7;
            int address : 20;
        };
        int value;
    };
} cr3_t;

typedef struct pagedirentry_s
{
    union
    {
        struct
        {
            int present : 1;
            int read_write : 1;
            int user_supervisor : 1;
            int write_through : 1;
            int cache_disabled : 1;
            int accessed : 1;
            int ALWAYS_ZERO : 1;
            int page_size : 1;
            int IGNORED : 1;
            int AVAILABLE : 3;
            int address : 20;
        };
        int value;
    };
} pagedirentry_t;

typedef struct pagetabentry_s
{
    union
    {
        struct
        {
            int present : 1;
            int read_write : 1;
            int user_supervisor : 1;
            int write_through : 1;
            int cache_disabled : 1;
            int accessed : 1;
            int dirty : 1;
            int ALWAYS_ZERO : 1;
            int global : 1;
            int AVAILABLE : 3;
            int address : 20;
        };
        int value;
    };
} pagetabentry_t;

extern void paging_loaddir(unsigned int* page_directory);
extern void paging_enable(void);
extern void paging_disable(void);
extern void paging_pagekernel(void);

#endif