#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/hashMap.h"

void test_hashmap_basic()
{
    printf("Testing basic HashMap operations...\n");
    HashMap *map = hashmap_create();

    hashmap_insert(map, "one", 1);
    hashmap_insert(map, "two", 2);
    hashmap_insert(map, "three", 3);

    int found;
    int val = hashmap_get(map, "two", &found);
    if (found)
    {
        printf("Value for 'two': %d\n", val);
    }
    else
    {
        printf("Key 'two' not found\n");
    }

    hashmap_delete(map, "two");
    val = hashmap_get(map, "two", &found);
    if (!found)
    {
        printf("'two' key removed successfully\n");
    }
    else
    {
        printf("Failed to remove 'two' key\n");
    }

    hashmap_free(map);
}

void test_hashmap_edge_cases()
{
    printf("Testing HashMap edge cases...\n");

    HashMap *map = hashmap_create();

    // Get from empty map
    int found;
    int val = hashmap_get(map, "nonexistent", &found);
    (void)val; // Suppress unused variable warning
    if (!found)
    {
        printf("Get from empty map returned not found as expected\n");
    }

    // Remove from empty map
    hashmap_delete(map, "nonexistent");
    printf("Remove from empty map handled correctly\n");

    // ✅ NULL key handling
    printf("Testing NULL key in hashmap...\n");
    hashmap_insert(map, NULL, 123); // Should print error message, not crash

    val = hashmap_get(map, NULL, &found); // Should print error and return default
    if (!found)
    {
        printf("Put and get NULL key handled correctly\n");
    }

    hashmap_delete(map, NULL); // Should print error message

    hashmap_free(map);
}
int main() {
    test_hashmap_basic();
    test_hashmap_edge_cases();
    return 0;
}
