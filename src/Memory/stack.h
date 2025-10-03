#ifndef STACK_H
#define STACK_H

#include "utils.h"
#include "array.h"

typedef struct {
    DynamicArray *backing;
} Stack;

Stack* create_stack(size_t element_size, size_t initial_capacity);
void destroy_stack(Stack *s, void (*free_elem)(void *));

dbool stack_push(Stack *s, const void *elem);
dbool stack_pop(Stack *s, void *out_elem);
void *stack_top_ptr(Stack *s);
dbool stack_is_empty(const Stack *s);
size_t stack_size(const Stack *s);

#endif