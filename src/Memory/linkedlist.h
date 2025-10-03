#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "utils.h"
#include "memory.h"

typedef struct LLNode {
    void *data;
    struct LLNode *next;
} LLNode;

typedef struct {
    LLNode *head;
    size_t size;
} LinkedList;

LinkedList *ll_create(void);
void ll_destroy(LinkedList *list, void (*free_data)(void *));

dbool ll_push_front(LinkedList *list, void *data);
dbool ll_push_back(LinkedList *list, void *data);
void *ll_pop_front(LinkedList *list);
dbool ll_remove(LinkedList *list, void *data, int (*cmp)(const void *, const void *), void (*free_data)(void *));

size_t ll_size(const LinkedList *list);

#endif