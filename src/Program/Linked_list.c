#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
#include "memory_allocation.h"


Node *Create(void *data, size_t data_size)
{
    Node *newNode = (Node *)dmalloc(sizeof(Node));
    newNode->data = dmalloc(data_size);
    memcpy(newNode->data, data, data_size);
    newNode->next = NULL;
    return newNode;
}

void Insert(Node **head, void *data, size_t data_size)
{
    Node *newNode = Create(data, data_size);
    newNode->next = *head;
    *head = newNode;
}

void Delete(Node **head, void *key, int (*cmp)(void *, void *))
{
    Node *temp = *head, *prev = NULL;
    while (temp != NULL && cmp(temp->data, key) == 0)
    {
        *head = temp->next;
        dfree(temp->data);
        dfree(temp);
        return;
    }
    while (temp != NULL && cmp(temp->data, key) != 0)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return;
    prev->next = temp->next;
    dfree(temp->data);
    dfree(temp);
}

Node *Search(Node *head, void *key, int (*cmp)(void *, void *))
{
    while (head != NULL)
    {
        if (cmp(head->data, key) == 0)
        {
            return head;
        }
        head = head->next;
    }
    return NULL; // Return NULL if the key is not found
}

void Reverse(Node **head)
{
    Node *prev = NULL, *current = *head, *next = NULL;
    while (current)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

void Traverse(Node *head, void (*print_func)(void *))
{
    while (head != NULL)
    {
        print_func(head->data);
        head = head->next;
    }
}

static int length(Node *head)
{
    int count = 0;
    while (head)
    {
        count++;
        head = head->next;
    }
    return count;
}

void Destroy(Node **head)
{
    Node *temp = *head;
    while (temp) // Corrected to use temp for traversal
    {
        Node *next = temp->next;
        dfree(temp->data);
        dfree(temp);
        temp = next;
    }
    *head = NULL;
}
