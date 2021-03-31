#include <stdint.h>

int32_t multPlus(int32_t a, int32_t b) {
    a = a + 8;
    b = b + a;
    return a * b;
}

int32_t sumPlus(int32_t a, int32_t b) {
    a = a + 3;
    b = b - a;
    return a + b;
}

int32_t main() {
    int32_t a = 4;
    int32_t b = 12;
    int32_t c = (1 + 3) * ((4 + 5) * 4) + (multPlus(a + 4, 4) - 7 * sumPlus(b, 34));
}