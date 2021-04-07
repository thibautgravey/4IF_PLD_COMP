#include <stdint.h>

int32_t main() {

    int32_t a = 1;
    int32_t b = 0;
    while (a != 10 && b <= 100 * a) {
        a = a + 1;
        b = b * b;
        if (a <= 5) {
            b = b + 1;
        }
    }

    return a + b;
}