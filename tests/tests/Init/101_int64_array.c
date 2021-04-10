#include <stdint.h>

char main() {

    int64_t a[4] = {74,65,87,1};
    int64_t b[64];
    int64_t c[] = {1234,3};

    int64_t i = 32;

    while (i > 0) {
        i = i - 1;
        b[i] = i-27;
    }

    return b[31]+a[c[1]];
}