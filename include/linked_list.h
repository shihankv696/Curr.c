#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>

// Node structure
typedef struct Node
{
    void *data;
    struct Node *next;
} Node;

// Linked List Function Prototypes
Node *Create(void *data, size_t data_size);
void Insert(Node **head, void *data, size_t data_size);
void Delete(Node **head, void *key, int (*cmp)(void *, void *));
Node *Search(Node *head, void *key, int (*cmp)(void *, void *));
void Reverse(Node **head);
void Traverse(Node *head, void (*print_func)(void *));
void Destroy(Node **head);

#endif // LINKED_LIST_H
