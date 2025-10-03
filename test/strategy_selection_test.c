#include <stdio.h>
#include "../src/Memory/memory.h"

void strategy_test()
{
    char buffer[1024];
    memory_init(buffer, sizeof(buffer));

    // Small allocations → FIRST_FIT (based on your choose_strategy rule)
    void *a = dmalloc(20);
    void *b = dmalloc(30);
    printf("Auto (expected FIRST_FIT): %p %p\n", a, b);

    memory_shutdown();
    memory_init(buffer, sizeof(buffer));

    // Medium allocations → NEXT_FIT
    void *c = dmalloc(100);
    void *d = dmalloc(150);
    printf("Auto (expected NEXT_FIT): %p %p\n", c, d);

    memory_shutdown();
    memory_init(buffer, sizeof(buffer));

    // Large allocations → BEST_FIT
    void *e = dmalloc(300);
    void *f = dmalloc(400);
    printf("Auto (expected BEST_FIT): %p %p\n", e, f);
}

int main()
{
    strategy_test();
    return 0;
}
