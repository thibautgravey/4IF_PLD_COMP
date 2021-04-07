#include <stdint.h>

int32_t main() {
    char abc = 'u';
    int32_t xyz = 142;
    int32_t test = abc + xyz;
    int64_t big = 10000000000000;
    int32_t mid = test + big + abc;
    return mid;
}