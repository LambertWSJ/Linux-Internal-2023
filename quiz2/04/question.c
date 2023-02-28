#include <stdint.h>
#include <stdbool.h>

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

bool is_pattern(uint16_t x)                             {
    const uint16_t n = EEEE;
    return (n ^ x) < FFFF;
}