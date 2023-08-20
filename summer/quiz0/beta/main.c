#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#ifndef ALIGN_SZ
#define ALIGN_SZ 4
#endif

enum ALIGN_MODE {
    ADDR_ALIGN_UP,
    ADDR_ALIGN_DOWN,
};

typedef uintptr_t(align_f)(uintptr_t sz, size_t alignment);

static inline uintptr_t align_up(uintptr_t sz, size_t alignment)
{
    uintptr_t mask = alignment - 1;
    if ((alignment & mask) == 0) { /* power of two? */
        return (sz + mask) & ~mask;
    }
    return (((sz + mask) / alignment) * alignment);
}

static inline uintptr_t align_down(uintptr_t sz, size_t alignment)
{
    uintptr_t mask = alignment - 1;
    if ((alignment & mask) == 0) {
        return sz & -alignment;
    }
    return (sz / alignment) * alignment;
}

static align_f *align_addr[] = {
    [ADDR_ALIGN_UP] = align_up,
    [ADDR_ALIGN_DOWN] = align_down,
};

static void dump_align(uintptr_t *addrs,
                       size_t len,
                       size_t alignment,
                       enum ALIGN_MODE mode)
{
    for (int i = 0; i < len; i++) {
        char tok = i == len - 1 ? '\n' : ' ';
        printf("%ld%c", align_addr[mode](addrs[i], alignment), tok);
    }
}

int main()
{
    uintptr_t addrs[] = {120, 121, 122, 123, 126, 129};
    size_t sz = sizeof(addrs) / sizeof(uintptr_t);
    size_t alignment = ALIGN_SZ;
    printf("align size: %ld\n", alignment);
    puts("align up");
    dump_align(addrs, sz, alignment, ADDR_ALIGN_UP);
    puts("align down");
    dump_align(addrs, sz, alignment, ADDR_ALIGN_DOWN);
}