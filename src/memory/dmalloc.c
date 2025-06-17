#include "../include/memory_allocation.h"

extern MemoryBlock *free_list;
extern void split_block(MemoryBlock *, size_t);

void *dmalloc(size_t size)
{
    if (size == 0)
        return NULL;
    MemoryBlock *current = free_list;
    while (current)
    {
        if (current->is_free && current->size >= size)
        {
            if (current->size > size + sizeof(MemoryBlock))
            {
                split_block(current, size);
            }
            current->is_free = false;
            return (char *)current + sizeof(MemoryBlock);
        }
        current = current->next;
    }

    return NULL;
}
