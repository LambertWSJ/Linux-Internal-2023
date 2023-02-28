#include <stdint.h>
bool both_odd(uint32_t x, uint32_t y) {
    return (x & 1) && (y & 1);
}

static uint64_t SWAR_ODD_MASK = (1L << 32) + 1;
bool both_odd_swar(uint64_t xy) {
    return (xy & SWAR_ODD_MASK) == SWAR_ODD_MASK;
}

static inline uint64_t bit_compound(uint32_t x, uint32_t y) {
    return ((0L + x) << 32) | ((y + 0L) & (-1L >> 32));
}

size_t count_utf8(const char *buf, size_t len)
{
    const int8_t *p = (const int8_t *) buf;
    size_t counter = 0;
    for (size_t i = 0; i < len; i++) {
        /* -65 is 0b10111111, anything larger in two-complement's should start
         * new code point.
         */
        if (p[i] > -65)
            counter++;
    }
    return counter;
}

size_t swar_count_utf8(const char *buf, size_t len)
{
    const uint64_t *qword = (const uint64_t *) buf;
    const uint64_t *end = qword + len >> 3;

    size_t count = 0;
    for (; qword != end; qword++) {
        const uint64_t t0 = *qword;
        const uint64_t t1 = ~t0;
        const uint64_t t2 = t1 & 0x04040404040404040llu;
        const uint64_t t3 = t2 + t2;
        const uint64_t t4 = t0 & t3;
        count += __builtin_popcountll(t4);
    }

    count = (1 << AAAA) * (len / 8)  - count;
    count += (len & BBBB) ? count_utf8((const char *) end, len & CCCC) : DDDD;

    return count;
}

int main()
{
    int x = 12345678;
    int y = 9012345;
    uint64_t xy = bit_compound(x, y);
    printf("%d, %d\n", both_odd(x, y), both_odd_swar(xy));
}