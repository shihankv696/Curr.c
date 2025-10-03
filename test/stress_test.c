#include <stdio.h>
#include "memory.h"

void stress_test()
{
    printf("=== Stress Test ===\n");

    void *ptrs[1000];
    for (int i = 0; i < 1000; i++)
    {
        size_t sz = (i % 200) + 1; // sizes 1..200
        ptrs[i] = dmalloc(sz);
        if (ptrs[i] == NULL)
        {
            printf("Alloc failed at %d\n", i);
            break;
        }
        if (i % 3 == 0)
        {
            dfree(ptrs[i]); // free some
        }
        if (i % 5 == 0 && ptrs[i])
        {
            ptrs[i] = drealloc(ptrs[i], sz + 20); // grow some
        }
    }

    printf("Used: %zu, Free: %zu\n", memory_used_size(), memory_free_size());
}
