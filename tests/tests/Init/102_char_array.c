#include <stdint.h>

char main() {

    char a[4] = {74,65,87,1};
    char b[64];
    int64_t c[] = {123,3};
    //char d[] = "Hey!";

    int64_t i = 64;

    while (i > 0) {
        i = i - 1;
        b[i] = i;
    }

    return b[1]+a[c[1]];//+d[2];
}