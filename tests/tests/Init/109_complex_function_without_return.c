#include <stdint.h>

int32_t toto(int32_t a) {
    int32_t b = 2 * a;
    int32_t c = 1 + 2 + b + a;
    int32_t d = 5 * c - (a + 2 * b);
    a = 42;
}

int32_t main() {
    int32_t a = 45;
    int32_t b = a * 2 + 1;
    int32_t c = toto(b);
    return c;
}