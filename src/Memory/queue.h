#ifndef QUEUE_H
#define QUEUE_H

#include "utils.h"
#include "array.h"

typedef struct {
    void *buffer;
    size_t element_size;
    size_t head;
    size_t tail;
    size_t capacity;
    size_t size;
} Queue;

Queue *create_queue(size_t element_size, size_t initial_capacity);
void destroy_queue(Queue *q, void (*free_elem)(void *));

dbool queue_enqueue(Queue* q, const void* elem);
dbool queue_dequeue(Queue *q, void *out_elem);
void *queue_front_ptr(Queue *q);
dbool queue_is_empty(const Queue *q);
size_t queue_size(const Queue *q);

#endif