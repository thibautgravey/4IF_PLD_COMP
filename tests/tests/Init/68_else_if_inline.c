#include <stdint.h>
int32_t main() {
    int32_t t = 5;

    int32_t r = 4;

    if (t == 1)
        r = 1;
    else if (t == 2)
        r = 2;
    else if (t == 5)
        r = 3;
    else
        r = 10;
    return r;
}