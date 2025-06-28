#ifndef HASHMAP_H
#define HASHMAP_H

#define TABLE_SIZE 100

typedef struct HashNode
{
    char *key;
    int value;
    struct HashNode *next;
} HashNode;

typedef struct HashMap
{
    HashNode *table[TABLE_SIZE];
} HashMap;

// Function prototypes
HashMap *hashmap_create();
void hashmap_insert(HashMap *map, const char *key, int value);
int hashmap_get(HashMap *map, const char *key, int *found);
void hashmap_delete(HashMap *map, const char *key);
void hashmap_free(HashMap *map);

#endif // HASHMAP_H