#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct QueueNode {
    void *data;
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode *front;
    QueueNode *rear;
} Queue;

Queue* queue(); // Function to create a queue
void enqueue(Queue* queue, void* data); // Function to add an element to the queue
void* dequeue(Queue* queue); // Function to remove an element from the queue
void print(Queue* queue, void (*print_func)(void*)); // Function to print the queue
int length(Queue *queue);
bool isEmpty(Queue *queue);
Queue *copy(Queue *original, void *(*copy_func)(void *));
void clear(Queue * queue, void (*free_func)(void *));