#include <stdio.h>
#include "../src/Memory/memory.h"

void alignment_test()
{
    char buffer[512];
    memory_init(buffer, sizeof(buffer));

    void *p1 = dmalloc(13);
    void *p2 = dmalloc(29);
    void *p3 = dmalloc(7);

    printf("p1=%p, aligned=%d\n", p1, ((unsigned long)p1 % 8 == 0));
    printf("p2=%p, aligned=%d\n", p2, ((unsigned long)p2 % 8 == 0));
    printf("p3=%p, aligned=%d\n", p3, ((unsigned long)p3 % 8 == 0));
}

int main() {
    alignment_test();
    return 0;
}