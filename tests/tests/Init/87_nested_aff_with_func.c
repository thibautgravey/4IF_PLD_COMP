#include <stdint.h>

int32_t toto(int32_t a) {
    return a + 5;
}

int32_t main() {
    int32_t a;
    int32_t b;
    b = 2 * 3 + (5 + (a = toto(3)));
    return a + b;
}
