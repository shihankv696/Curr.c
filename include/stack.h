#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

typedef struct StackNode {
    void *data;
    struct StackNode *next;
} StackNode;

typedef struct {
    StackNode *top;
} Stack;

Stack* stack(); // Function to create a stack
void push(Stack* stack, void* data, size_t data_size);
void* pop(Stack* stack);
void* peek(Stack* stack);
void print(Stack* stack, void (*print_func)(void*)); // Function to print stack
#endif // STACK_H
