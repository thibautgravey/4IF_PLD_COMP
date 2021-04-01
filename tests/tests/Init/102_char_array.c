#include <stdint.h>

char main() {

    char a[4] = {74,65,87,1};
    char b[64];
    char c[] = {123,3};
    char d[] = "Hey!";

    char i = 64;

    while (i = i - 1) {
        b[i] = i;
    }

    return b[1]+a[c[3]]+d[2];
}