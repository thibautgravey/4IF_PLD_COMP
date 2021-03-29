#include <stdint.h>

int32_t main() {
    int32_t a = 1;
    int32_t b = 5;
    int32_t c = a ^ b;
    int32_t k = 9;
    int32_t d = (c | b) & 7 ^ k;

    return d;
}