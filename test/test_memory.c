#include <stdio.h>
#include "../src/Memory/memory.h"

#define HEAP_SIZE 1024 // 1 KB custom heap for testing

int main()
{
    unsigned char buffer[HEAP_SIZE];
    memory_init(buffer, HEAP_SIZE);
    printf("=== Memory Allocator Test ===\n");

    printf("Total: %zu, Used: %zu, Free: %zu\n",
           memory_total_size(), memory_used_size(), memory_free_size());

    // Test malloc
    void *p1 = dmalloc(100);
    printf("malloc(100) -> %p\n", p1);
    printf("Used: %zu, Free: %zu\n", memory_used_size(), memory_free_size());

    // Test calloc
    int *arr = (int *)dcalloc(10, sizeof(int));
    printf("calloc(10, int) -> %p\n", arr);
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]); // should print 0
    }
    printf("\nUsed: %zu, Free: %zu\n", memory_used_size(), memory_free_size());

    // Test realloc (increase size)
    arr = (int *)drealloc(arr, 20 * sizeof(int));
    printf("realloc(..., 20 ints) -> %p\n", arr);
    printf("Used: %zu, Free: %zu\n", memory_used_size(), memory_free_size());

    // Test realloc (shrink size)
    arr = (int *)drealloc(arr, 5 * sizeof(int));
    printf("realloc(..., 5 ints) -> %p\n", arr);
    printf("Used: %zu, Free: %zu\n", memory_used_size(), memory_free_size());

    // Test free
    dfree(p1);
    printf("free(p1)\nUsed: %zu, Free: %zu\n", memory_used_size(), memory_free_size());

    dfree(arr);
    printf("free(arr)\nUsed: %zu, Free: %zu\n", memory_used_size(), memory_free_size());

    // Edge cases
    void *null_ptr = dmalloc(0);
    printf("malloc(0) -> %p (should be NULL)\n", null_ptr);

    dfree(NULL); // should safely do nothing

    printf("=== Test Complete ===\n");
    return 0;
}
