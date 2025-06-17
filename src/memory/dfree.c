#include "memory_allocation.h"

extern void merge_blocks();

void dfree(void *ptr)
{
    if (!ptr)
        return;

    MemoryBlock *block = (MemoryBlock *)((char *)ptr - sizeof(MemoryBlock));
    block->is_free = true;
    merge_blocks();
}