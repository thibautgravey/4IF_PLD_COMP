#include <stdint.h>

int32_t main() {
    int32_t test1;
    int32_t test2 = 4;
    int32_t test3;
    int32_t res = test1 = 5 + 2 * (test3 = test2 * 4);
    return res + test1 + test2 + test3;
}