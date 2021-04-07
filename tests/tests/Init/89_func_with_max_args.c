#include <stdint.h>

int32_t toto(int32_t a, int32_t b, int32_t c, int32_t d, int32_t e, int32_t f) {
    return a - b * c + d - e * f;
}

int32_t main() {
    return toto(1, 2, 3, 4, 5, 6);
}