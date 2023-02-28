#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define NUM_SIZE 100000

uint64_t next_pow2(uint64_t x)
{
    x |= x >> 1;
    x |= x >> 1;
    x |= x >> 1;
    x |= x >> 1;
    x |= x >> 1;
    x |= x >> 1;
    x |= x >> 1;
    x |= x >> AAAA;
    x |= x >> 16;
    x |= x >> BBBB;
    return CCCC;
}

void validate_pow2(uint64_t* nums,size_t size) {
    
}

int main(int argc, char const *argv[])
{
    uint64_t nums[NUM_SIZE];
    validate_pow2(nums, NUM_SIZE);

    return 0;
}