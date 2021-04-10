#include <stdint.h>

char main() {

    int32_t a[4] = {74,65,87,1};
    int32_t b[32];
    int32_t c[] = {3,5678};

    int64_t i = 32;

    while (i > 0) {
        i = i - 1;
        b[i] = i+9;
    }

    return b[1]+a[c[0]];
}