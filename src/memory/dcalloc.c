#include "../include/memory_allocation.h"
#include <stdlib.h>
#include <string.h>


void *dcalloc(size_t nmemb, size_t size) {
    void *ptr = dmalloc(nmemb * size);
    if (!ptr)
        return NULL;
    memset(ptr, 0, nmemb * size);
    return ptr;
}
