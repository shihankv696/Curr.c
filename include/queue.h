#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct QueueNode
{
    void *data;
    struct QueueNode *next;
} QueueNode;

typedef struct
{
    QueueNode *front;
    QueueNode *rear;
} Queue;

Queue *queue();                                                 // Function to create a queue
void enqueue(Queue *queue, void *data);                         // Function to add an element to the queue
void *dequeue(Queue *queue);                                    // Function to remove an element from the queue
bool isEmpty(Queue *queue);                                     // Function to check the queue is Empty or NOT
Queue *clone(Queue *original, void *(*copy_func)(void *));      // Function to check the copy or clone the  queue 
            