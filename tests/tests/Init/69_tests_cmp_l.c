#include <stdint.h>
int32_t main() {
    int32_t t = 3;
    int32_t r = 0;
    
    if (t < 4)
        r = r + 1;
    if (t < 3)
        r = r + 2;
    if (t <= 2)
        r = r + 4;
    if (t <= 3)
        r = r + 8;

    return r;
}