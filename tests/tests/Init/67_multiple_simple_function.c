#include <stdint.h>

int32_t sum1(int32_t a, int32_t b) {
    return a + b + 3;
}

int32_t sum2(int32_t a, int32_t b) {
    return a + b + 8;
}

int32_t sum3(int32_t b, int32_t c) {
    return sum1(b, 5) + sum2(c, 6);
}

int32_t main() {
    return sum3(56, 45);
}