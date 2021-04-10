#include <stdint.h>

int64_t toto(int64_t a, int64_t b) {
    return a * b;
}

int32_t main() {
    int32_t arr[] = {1, 2, toto(12, 14), 42};
    return arr[0] + arr [2];
}