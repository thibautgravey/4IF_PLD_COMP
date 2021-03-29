#include <stdint.h>

int32_t main()
{
    int32_t a = 23;
    int32_t b = 39;
    int32_t c = 50;
    int32_t d = 10;
    int32_t x = (((a + b) * c) - c + a) * d;
    int32_t g = (x + (d * 5) - 3) * b - a;

    return x+g;
}