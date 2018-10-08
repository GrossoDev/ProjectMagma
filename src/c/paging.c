#include <sys/paging.h>

uint32_t kernel_page_directory[1024] __attribute__((aligned(4096)));
uint32_t kernel_page_table[1024] __attribute__((aligned(4096)));

void paging_pagekernel()
{
    // Set each entry to not present, we only need one
    unsigned int i;
    for (i = 0; i < 1024; i++)
    {
        // This sets the following flags to the pages:
        //   Supervisor: Only kernel-mode can access them
        //   Write Enabled: It can be both read from and written to
        //   Not Present: The page table is not present
        kernel_page_directory[i] = 0b010;
    }

    // Fill all 1024 entries in the table, mapping the first 4 megabytes
    for (i = 0; i < 1024; i++)
    {
        // As the address is page aligned, it will always leave 12 bits zeroed.
        // Those bits are used by the attributes ;)
        kernel_page_table[i] = (i * 0x1000) | 3; // Supervisor level, read/write, present
    }

    // Supervisor level, read/write, present
    kernel_page_directory[0] = ((unsigned int)kernel_page_table) | 3;

    paging_loaddir(kernel_page_directory);
    paging_enable();
}