#include <stdint.h>
#include <stdio.h>

int32_t main() {
    int32_t test = 10;
    while (test > 0) {
        for (int32_t i = 0; i < test ; i = i + 1) {
            for (int32_t j = 0; j < i; j = j + 1) {
                if (i == j) {
                    break;
                }
                putchar(j);
            }
            if (i > 6) {
                break;
            }
        }
        test = test - 1;
    }
    return test;
}