#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_SIZE 100000
#define clz(x) __builtin_clz(x)

uint64_t next_pow2(uint64_t x)
{
    x |= x >> 1;

    x |= x >> 1;
    x |= x >> 1;

    x |= x >> 1;
    x |= x >> 1;
    x |= x >> 1;
    x |= x >> 1;

    x |= x >> 8;
    x |= x >> 16;
    x |= x >> 32;
    return x + 1;
}

uint64_t next_pow2_clz(uint64_t x)
{
    uint32_t lsb = clz(x);
    return (1 << (64 - lsb));
}

int main(int argc, char const *argv[])
{
    uint64_t nums[] = {3, 5, 13, 27, 40};
    for (size_t i = 0; i < 5; i++)
    {
        printf("%2ld: %ld, %ld\n", nums[i], next_pow2(nums[i]), next_pow2_clz(nums[i]));
    }

    return 0;
}