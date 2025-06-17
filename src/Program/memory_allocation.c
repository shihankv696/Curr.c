#include <stdbool.h>
#include "../include/memory_allocation.h"


// Define the memory pool and free list
#define MEMORY_POOL_SIZE 1024 * 1024 // 1MB Pool
static char memory_pool[MEMORY_POOL_SIZE];
MemoryBlock *free_list = (MemoryBlock *)memory_pool;

// Initialize memory pool
__attribute__((constructor)) void memory_init()
{
    free_list->size = MEMORY_POOL_SIZE - sizeof(MemoryBlock);
    free_list->is_free = true;
    free_list->next = NULL;
}

// Helper function to merge adjacent free blocks
void merge_blocks()
{
    MemoryBlock *current = free_list;
    while (current && current->next)
    {
        if (current->is_free && current->next->is_free)
        {
            current->size += current->next->size + sizeof(MemoryBlock);
            current->next = current->next->next;
        }
        else
        {
            current = current->next;
        }
    }
}

// Helper function to split a block
void split_block(MemoryBlock *block, size_t size)
{
    MemoryBlock *new_block = (MemoryBlock *)((char *)block + sizeof(MemoryBlock) + size);
    new_block->size = block->size - size - sizeof(MemoryBlock);
    new_block->is_free = true;
    new_block->next = block->next;

    block->size = size;
    block->is_free = false;
    block->next = new_block;
}
