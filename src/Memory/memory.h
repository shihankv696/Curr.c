#ifndef MEMORY_H
#define MEMORY_H

#include "utils.h"

dbool memory_init(void *buffer, size_o buffer_size);

void memory_shutdown(void);

void *dmalloc(size_o size);
void *dcalloc(size_o nmemb, size_o size);
void *drealloc(void *ptr, size_o new_size);
void dfree(void *ptr);

size_o memory_total_size(void);
size_o memory_used_size(void);
size_o memory_free_size(void);

#endif
