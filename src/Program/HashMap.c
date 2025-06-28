#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashMap.h"
#include "memory_allocation.h"

#define TABLE_SIZE 100


// Create a new hash node
HashNode *create_node(const char *key, int value)
{
    HashNode *new_node = (HashNode *)dmalloc(sizeof(HashNode));
    new_node->key = (char *)dmalloc(strlen(key) + 1);
    strcpy(new_node->key, key);
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

// Hash function (simple)
unsigned int hash(const char *key)
{
    unsigned int hash = 0;
    for (int i = 0; key[i] != '\0'; ++i)
    {
        hash = hash * 31 + key[i];
    }
    return hash % TABLE_SIZE;
}

// Create a new hash map
HashMap *hashmap_create()
{
    HashMap *map = (HashMap *)dmalloc(sizeof(HashMap));
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        map->table[i] = NULL;
    }
    return map;
}

// Insert key-value pair
void hashmap_insert(HashMap *map, const char *key, int value)
{
    unsigned int index = hash(key);
    HashNode *head = map->table[index];

    // Check if key exists
    HashNode *current = head;
    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            current->value = value;
            return;
        }
        current = current->next;
    }

    // Key doesn't exist, create new node
    HashNode *new_node = create_node(key, value);
    new_node->next = head;
    map->table[index] = new_node;
}

// Get value by key
int hashmap_get(HashMap *map, const char *key, int *found)
{
    unsigned int index = hash(key);
    HashNode *current = map->table[index];
    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            *found = 1;
            return current->value;
        }
        current = current->next;
    }
    *found = 0;
    return -1;
}

// Delete key
void hashmap_delete(HashMap *map, const char *key)
{
    unsigned int index = hash(key);
    HashNode *current = map->table[index];
    HashNode *prev = NULL;

    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            if (prev == NULL)
            {
                map->table[index] = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            dfree(current->key);
            dfree(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void hashmap_free(HashMap *map)
{
    if (map == NULL)
        return;
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        HashNode *current = map->table[i];
        while (current != NULL)
        {
            HashNode *temp = current;
            current = current->next;
            dfree(temp->key);
            dfree(temp);
        }
    }
    dfree(map);
}
