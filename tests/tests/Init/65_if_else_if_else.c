#include <stdint.h>
int32_t main() {
    int32_t t = 5;

    int32_t r = 3;

    if (t != 1) {
        r = 2;
        if (r == 2) {
            r = 4;
        } else {
            r = 6;
        }

    }

    else {
    }

    return r;
}