#include <stdint.h>

int32_t main() {
    int32_t a = 5;
    int32_t b = 10 / a;
    int32_t c = 5 * b + (a - 35) * a;
    int32_t d = b / 2 + c;
    return d;
}