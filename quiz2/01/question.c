#include <stdint.h>
static inline uint64_t pow2(uint8_t e) { return ((uint64_t)1) << e; }

uint64_t next_pow2(uint64_t x)
{
    uint8_t lo = 0, hi = 63;
    while (lo < hi) {
        uint8_t test = (lo + hi)/2;
        if (x < pow2(test)) { hi = test; }
        else if (pow2(test) < x) { lo = test+1; }
        else { return pow2(test); }
    }
    return pow2(lo);
}

/* 
output:
x = 0010000000000000
x = 0011000000000000
x = 0011110000000000
x = 0011111111000000
x = 0011111111111111

 */

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