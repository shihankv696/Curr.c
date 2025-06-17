#ifndef MEMORY_ALLOCATION_H
#define MEMORY_ALLOCATION_H

#include <stddef.h>
#include <stdbool.h>

// Define the memory block structure only in the header file
typedef struct MemoryBlock
{
    size_t size;
    bool is_free;
    struct MemoryBlock *next;
} MemoryBlock;

// Memory management function prototypes
void *dmalloc(size_t size);
void *dcalloc(size_t num, size_t size);
void *drealloc(void *ptr, size_t size);
void dfree(void *ptr);

// External global variables used in memory management
extern MemoryBlock *free_list;

// Helper functions for memory management
void merge_blocks();
void split_block(MemoryBlock *block, size_t size);

#endif // MEMORY_ALLOCATION_H
