#include <stdint.h>

int32_t main() {

    int32_t a = 1;
    int32_t b = 0;
    while (a <= 10) {
        a = a + 1;
        b = b * b;
    }

    return a + b;
}