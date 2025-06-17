#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/stack.h"
#include "../include/memory_allocation.h"

Stack *stack()
{
    Stack *stack = (Stack *)dmalloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

void push(Stack *stack, void *data, size_t data_size)
{
    StackNode *node = (StackNode *)dmalloc(sizeof(StackNode));
    node->data = dmalloc(data_size);
    memcpy(node->data, data, data_size);
    node->next = stack->top;
    stack->top = node;
}

void *pop(Stack *stack)
{
    if (stack->top == NULL)
    {
        return NULL;
    }

    StackNode *temp = stack->top;

    void *data = temp->data;
    stack->top = stack->top->next;

    dfree(temp);
    return data;
}

