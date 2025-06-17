#include <stdio.h>
#include <string.h>
#include "../include/hashMap.h"
#include "../include/memory_allocation.h" // dmalloc, dfree, etc.

#define HASHMAP_INITIAL_SIZE 101

// Hash function (djb2)
unsigned int hash_function(const char *key)
{
    unsigned int hash = 5381;
    int c;
    while ((c = *key++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash;
}

HashMap *Hashmap()
{
    HashMap *map = (HashMap *)dmalloc(sizeof(HashMap));
    map->size = HASHMAP_INITIAL_SIZE;
    map->buckets = (HashNode **)dmalloc(sizeof(HashNode *) * map->size);

    for (int i = 0; i < map->size; i++)
        map->buckets[i] = NULL;

    return map;
}

void put(HashMap *map, const char *key, int value)
{
    unsigned int index = hash_function(key) % map->size;
    HashNode *node = map->buckets[index];

    while (node != NULL)
    {
        if (strcmp(node->key, key) == 0)
        {
            node->value = value;
            return;
        }
        node = node->next;
    }

    HashNode *new_node = (HashNode *)dmalloc(sizeof(HashNode));
    new_node->key = (char *)dmalloc(strlen(key) + 1);
    strcpy(new_node->key, key);
    new_node->value = value;
    new_node->next = map->buckets[index];
    map->buckets[index] = new_node;
}

int get(HashMap *map, const char *key, int *found)
{
    unsigned int index = hash_function(key) % map->size;
    HashNode *node = map->buckets[index];

    while (node != NULL)
    {
        if (strcmp(node->key, key) == 0)
        {
            *found = 1;
            return node->value;
        }
        node = node->next;
    }

    *found = 0;
    return -1;
}

void removeKey(HashMap *map, const char *key)
{
    unsigned int index = hash_function(key) % map->size;
    HashNode *node = map->buckets[index];
    HashNode *prev = NULL;

    while (node != NULL)
    {
        if (strcmp(node->key, key) == 0)
        {
            if (prev == NULL)
                map->buckets[index] = node->next;
            else
                prev->next = node->next;

            dfree(node->key);
            dfree(node);
            return;
        }
        prev = node;
        node = node->next;
    }
}

void hashmap_free(HashMap *map)
{
    for (int i = 0; i < map->size; i++)
    {
        HashNode *node = map->buckets[i];
        while (node)
        {
            HashNode *temp = node;
            node = node->next;
            dfree(temp->key);
            dfree(temp);
        }
    }
    dfree(map->buckets);
    dfree(map);
}
