#include <stdint.h>
int32_t main() {
    int32_t f = 0;
    int32_t v = 1;
    int32_t r = 0;
    
    if (v || v)
        r = r + 1;
    if (v || f)
        r = r + 2;
    if (f || v)
        r = r + 4;
    if (f || f)
        r = r + 8;

    return r;
}