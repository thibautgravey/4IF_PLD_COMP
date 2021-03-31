#include <stdint.h>

void toto(int32_t y) {
    return y + 1;
}

int32_t main() {
    int32_t a = toto(5);
    return a;
}