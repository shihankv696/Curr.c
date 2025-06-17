#include "memory_allocation.h"

extern void merge_block();

void* drealloc(void* ptr, size_t size) {
    if (!ptr)
        return dmalloc(size);
    if (size == 0) {
        dfree(ptr);
        return NULL;
    }

    MemoryBlock *block = (MemoryBlock *)((char *)ptr - sizeof(MemoryBlock));
    if (block->size >= size)
        return ptr;

    void *new_ptr = dmalloc(size);
    if (new_ptr) {
        char *src = (char *)ptr;
        char *dest = (char *)new_ptr;
        for (size_t i = 0; i < block->size; i++) {
            dest[i] = src[i];
        }
        dfree(ptr);
    }
    return new_ptr;
}