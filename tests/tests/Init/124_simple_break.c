#include <stdint.h>

int32_t main() {
    int32_t test = 10;
    while (test > 0) {
        if (test == 1) {
            break;
        }
        test = test - 1;
    }
    return test;
}