#ifndef ARRAY_H
#define ARRAY_H

#include "utils.h"
#include "memory.h"

typedef struct {
    void *data;
    size_t element_size;
    size_t length;
    size_t capacity;
} DynamicArray;

DynamicArray *da_create(size_t element_size, size_t initial_capacity);

void da_destroy(DynamicArray *arr);

dbool push(DynamicArray *arr, const void *element);
dbool pop(DynamicArray *arr, void *out_element);
void *get(DynamicArray *arr, size_t index);
dbool set(DynamicArray *arr, size_t index, const void *element);

dbool ds_reserve(DynamicArray *arr, size_t new_capacity);

size_t ds_size(const DynamicArray *arr);
size_t ds_capacity(const DynamicArray *arr);

#endif