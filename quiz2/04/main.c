#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef bool(func)(uint16_t);

void dump_16bit(uint16_t n)
{
    uint16_t mask = 0x8000;
    for (size_t i = 0; i < 16; i++) {
        printf("%d", n & (mask >> i) ? 1 : 0);
    }
}

bool is_pattern(uint16_t x)
{
    if (!x)
        return 0;

    while (x > 0) {
        if (!(x & 0x8000))
            return false;
        x <<= 1;
    }

    return true;
}

bool fast_is_pattern(uint16_t x)
{
    const uint16_t n = -x;
    return (n ^ x) < x;
}


void demo(const int n)
{
    for (size_t i = 0; i < n; i++) {
        if (is_pattern(i)) {
            printf("%lx match pattern: ", i);
            dump_16bit(i);
            puts("");
        }
    }
}

void validate(const int n, func check, func test)
{
    for (size_t i = 0; i < n; i++) 
        assert(check(i) == test(i));
}

int main(int argc, char const *argv[])
{
    const int n = 0xffff;
    demo(n);
    puts("validate faster match pattern function");
    validate(n, is_pattern, fast_is_pattern);
    puts("faster match pattern pass");
    return 0;
}