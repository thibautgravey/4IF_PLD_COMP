#include <stdint.h>

int32_t sumPlus(int32_t a, int32_t b) {
    a = a + 1;
    b = b + 1;
    return a + b;
}

int32_t main() {
    int32_t a = sumPlus(10, 12);
    return a;
}