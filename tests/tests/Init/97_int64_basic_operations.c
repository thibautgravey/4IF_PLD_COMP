#include <stdint.h>

int64_t main() {

    int64_t int64_max = 9223372036854775807;
    int64_t int64_min = -9223372036854775808;
    int64_t int64_1 = 1;

    return (int64_max + int64_1) + (int64_min - int64_1);
}