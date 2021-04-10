#include <stdint.h>
#include <stdio.h>

int32_t main() {
    int32_t test = 10;
    int32_t ret = 0;
    while (test > 0) {
        for (int32_t i = 0; i < test ; i = i + 1) {
            for (int32_t j = 0; j < i; j = j + 1) {
                if (i == j) {
                    continue;
                }
                ret = ret + j;
                putchar(j);
            }
            if (i > 6) {
                continue;
            }
            ret = ret + i;
        }
        test = test - 1;
    }
    return test;
}