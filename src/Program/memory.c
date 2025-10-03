#include "../Memory/memory.h"
#include "../Memory/utils.h"


typedef struct BlockHeader
{
    size_o size;
    dbool free;
    struct BlockHeader *next;
} BlockHeader;

typedef enum
{
    FIRST_FIT,
    BEST_FIT,
    NEXT_FIT
} FitStrategy;

static void *heap_start = NULL;
static size_o heap_size = 0;
static BlockHeader *first = NULL;
static BlockHeader *last_alloc = NULL;


#define ALIGN8(x) ((((x) + 7) / 8) * 8)

static void memorycopy(void *dst, const void *src, size_o n)
{
    unsigned char *d = (unsigned char *)dst;
    const unsigned char *s = (const unsigned char *)src;
    while (n--)
    {
        *d++ = *s++;
    }
}

static void memoryset(void *dst, int val, size_o n)
{
    unsigned char *d = (unsigned char *)dst;
    unsigned char v = (unsigned char)val;
    while (n--)
    {
        *d++ = v;
    }
}

static void *header_to_payload(BlockHeader *h)
{
    if (h == NULL)
    {
        return NULL;
    }
    return (void *)((unsigned char *)h + ALIGN8(sizeof(BlockHeader)));
}

static BlockHeader *payload_to_header(void *p)
{
    if (p == NULL)
    {
        return NULL;
    }
    return (BlockHeader *)((unsigned char *)p - ALIGN8(sizeof(BlockHeader)));
}

dbool memory_init(void *buffer, size_o buffer_size)
{
    if (buffer == NULL)
        return MY_FALSE;

    typedef unsigned long uptr; 

    uptr aligned_start = ((uptr)buffer + 7) & ~((uptr)7);
    size_o offset = aligned_start - (uptr)buffer;

    if (buffer_size <= offset + ALIGN8(sizeof(BlockHeader)))
        return MY_FALSE;

    heap_start = (void *)aligned_start;
    heap_size = buffer_size - offset;

    first = (BlockHeader *)heap_start;
    first->size = heap_size - ALIGN8(sizeof(BlockHeader));
    first->free = MY_TRUE;
    first->next = NULL;

    return MY_TRUE;
}

void memory_shutdown(void)
{
    heap_start = NULL;
    heap_size = 0;
    first = NULL;
    
}



static BlockHeader *find_free_block(size_o size, BlockHeader **out_prev, FitStrategy start)
{
    BlockHeader *curr = NULL, *prev = NULL;
    BlockHeader *best = NULL, *best_prev = NULL;

    switch (start) {
        case FIRST_FIT:
            curr = first;
            prev = NULL;
            while (curr) {
                if (curr->free && curr->size >= size) {
                    if (out_prev)
                        *out_prev = prev;
                    return curr;
                }
                prev = curr;
                curr = curr->next;
            }
            break;
        case BEST_FIT:
            curr = first;
            prev = NULL;
            while (curr) {
                if (curr->free && curr->size >= size) {
                    if (best == NULL || curr->size < best->size) {
                        best = curr;
                        best_prev = prev;
                    }
                }
                prev = curr;
                curr = curr->next;
            }
            if (best && out_prev)
                *out_prev = best_prev;
            return best;
        case NEXT_FIT:
            if (last_alloc == NULL) {
                last_alloc = first;
            }

            curr = last_alloc;
            prev = NULL;
            do {
                if (curr->free && curr->size >= size) {
                    if (out_prev)
                        *out_prev = prev;
                    last_alloc = curr->next ? curr->next : first;
                    return curr;
                }
                prev = curr;
                curr = (curr->next) ? curr->next : first;
            } while (curr != last_alloc);
            break;
    }   

    if (out_prev)
        *out_prev = NULL;
    return NULL;
}

static void split_block(BlockHeader *b, size_o size)
{
    size_o header_rs = ALIGN8(sizeof(BlockHeader));
    if (b == NULL)
        return;
    if (b->size < size + header_rs + 8)
    {
        return;
    }

    unsigned char *new_block_addr = (unsigned char *)header_to_payload(b) + size;
    BlockHeader *new_b = (BlockHeader *)new_block_addr;
    new_b->size = b->size - size - header_rs;
    new_b->free = MY_TRUE;
    new_b->next = b->next;

    b->size = size;
    b->next = new_b;
}

static void coalesce()
{
    BlockHeader *curr = first;
    while (curr && curr->next)
    {
        if (curr->free && curr->next->free)
        {
            curr->size = curr->size + ALIGN8(sizeof(BlockHeader)) + curr->next->size;
            curr->next = curr->next->next;
            continue;
        }
        curr = curr->next;
    }
}

static FitStrategy choose_strategy(size_o size) {
    if (size < 64) {
        return FIRST_FIT;
    } else if (size > 256) {
        return BEST_FIT;
    } else {
        return NEXT_FIT;
    }
}

void *dmalloc(size_o size)
{
    if (size == 0 || heap_start == NULL)
    {
        return NULL;
    }

    size = ALIGN8(size);

    BlockHeader *prev = NULL;

    FitStrategy start = choose_strategy(size);

    BlockHeader *b = find_free_block(size, &prev, start);

    if (b == NULL) {
        return NULL;
    }

    split_block(b, size);
    b->free = MY_FALSE;
    return header_to_payload(b);
}

void *dcalloc(size_o nmemb, size_o el_size)
{
    if (nmemb == 0 || el_size == 0)
        return NULL;
    size_o total = nmemb * el_size;
    if (el_size != 0 && total / el_size != nmemb)
        return NULL;

    void *p = dmalloc(total);

    if (p)
        memoryset(p, 0, total);

    return p;
}

void *drealloc(void *ptr, size_o new_size)
{
    if (ptr == NULL)
    {
        return dmalloc(new_size);
    }
    if (new_size == 0)
    {
        dfree(ptr);
        return NULL;
    }

    BlockHeader *old_header = payload_to_header(ptr);
    if (old_header->size >= new_size)
    {
        // shrink case
        size_o aligned_new = ALIGN8(new_size);
        if (old_header->size >= aligned_new + ALIGN8(sizeof(BlockHeader)) + 8)
        {
            split_block(old_header, aligned_new); // free remainder
        }
        return ptr;
    }

    void *new_ptr = dmalloc(new_size);
    if (new_ptr == NULL)
    {
        return NULL;
    }

    size_o copy_size = old_header->size < new_size ? old_header->size :
            new_size;
            memorycopy(new_ptr, ptr, copy_size);
            dfree(ptr);
            return new_ptr;
}

void dfree(void *ptr)
{
    if (ptr == NULL)
    {
        return;
    }

    BlockHeader *header = payload_to_header(ptr);
    header->free = MY_TRUE;
    coalesce();
}

size_o memory_total_size(void)
{
    return heap_size;
}

size_o memory_used_size(void)
{
    if (heap_start == NULL)
    {
        return 0;
    }

    size_o used = 0;
    BlockHeader *curr = first;
    while (curr)
    {
        if (!curr->free)
        {
            used += curr->size;
        }
        curr = curr->next;
    }
    return used;
}

size_o memory_free_size(void)
{
    if (heap_start == NULL)
    {
        return 0;
    }

    size_o free_space = 0;
    BlockHeader *curr = first;
    while (curr)
    {
        if (curr->free)
        {
            free_space += curr->size;
        }
        curr = curr->next;
    }
    return free_space;
}
