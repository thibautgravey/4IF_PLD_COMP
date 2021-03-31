#include <stdint.h>
int32_t main() {
    int32_t t = 5;

    int32_t r = 0;

    if (t >= 10 || t == 5) {
        r = r + 1;
    }

    if (t <= 5 && t != 4 && t > -1) {
        r = r + 10;
    }

    if (t < 6 && (t != 5 || t * 2 + 2 == 10 + 2)) {
        r = r + 100;
    }

    return r;
}