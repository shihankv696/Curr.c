#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "queue.h"
#include "memory_allocation.h"


Queue *queue()  {
    Queue *queue = (Queue *)dmalloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

void enqueue(Queue *queue, void *data) {
    QueueNode *newNode = (QueueNode *)dmalloc(sizeof(QueueNode));
    newNode->data = data;
    newNode->next = NULL;

    if (queue->rear == NULL)
    {
        queue->front = queue->rear = newNode;
        return;
    }

    queue->rear->next = newNode;
    queue->rear = newNode;
}

void *dequeue(Queue *queue) {
    if (queue->front == NULL)
    {
        return NULL; // Queue is empty
    }

    QueueNode *temp = queue->front; 
    void *data = temp->data; // Store the data to return

    queue->front = queue->front->next;

    if (queue->front == NULL)
    {
        queue->rear = NULL; // Queue is now empty
    }

    dfree(temp); // Free the dequeued node
    return data; // Return the data
}

void *peek(Queue *queue) {
    return (queue->front) ? queue->front->data : NULL;
}


static int length(Queue *queue) {
    int count = 0;
    QueueNode *current = queue->front;

    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

bool isEmpty(Queue *queue) {
    return (queue->front == NULL);
}

Queue *clone(Queue *original, void *(*copy_func)(void *)) {
    Queue *newQueue = queue();
    QueueNode *current = original->front;

    while (current != NULL) {
        void *copied_data = copy_func(current->data);
        enqueue(newQueue, copied_data);
        current = current->next;
    }
    return newQueue;
}
