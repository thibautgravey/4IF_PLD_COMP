#include <stdint.h>

int32_t main() {
    int32_t test = 10;
    int32_t ret = 0;
    while (test > 0) {
        test = test - 1;
        if (test == 1) {
            continue;
        }
        ret = ret + test;
    }
    return ret;
}