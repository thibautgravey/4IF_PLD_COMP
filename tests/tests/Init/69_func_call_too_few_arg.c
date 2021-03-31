#include <stdint.h>

int32_t toto(int32_t a, int32_t b, int32_t c) {
    int32_t res = a * (b + c);
    return res;
}

int32_t main() {
    int32_t test = toto(1, 2);
    return test;
}