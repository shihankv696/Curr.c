#ifndef HASHMAP_H
#define HASHMAP_H

typedef struct HashNode
{
    char *key;
    int value;
    struct HashNode *next;
} HashNode;

typedef struct
{
    int size;
    HashNode **buckets;
} HashMap;

// HashMap functions
HashMap *Hashmap();
void put(HashMap *map, const char *key, int value);
int get(HashMap *map, const char *key, int *found);
void removeKey(HashMap *map, const char *key);
void hashmap_free(HashMap *map);

#endif // HASHMAP_H
