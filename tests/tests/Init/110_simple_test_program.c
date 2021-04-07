#include <stdint.h>
#include <stdio.h>

int32_t main() {
    char a;
    a = 'A';
    while (a < 'Z' + 1) {
        putchar(a);
        a = a + 1;
    }
    return 0;
}