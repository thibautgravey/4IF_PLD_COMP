#include <stdint.h>
int32_t main() {
    int32_t f = 0;
    int32_t v = 1;
    
    if (v && f)
        return 1;
    if (v && v)
        return 2;

    return 0;
}