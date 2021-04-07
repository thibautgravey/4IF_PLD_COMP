#include <stdint.h>

int32_t toto(int32_t a, int64_t b, char c) {
    int32_t p = b + c;
    int32_t l = a + c;
    int64_t m = a + b;
    return p + l + m;
}

int32_t main() {
    int32_t testVar = 10;
    int64_t abc = 4512154 + 5454152145;
    char p = toto(testVar, abc, 'r');
    int32_t tmp = toto(abc, testVar, p);
    int64_t ret = toto(415121, tmp, 'e');
    return ret;
}