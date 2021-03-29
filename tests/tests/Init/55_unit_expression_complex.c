#include <stdint.h>

int32_t main() {
    int32_t x = 0, y = !x;
    int32_t g = -(-(y + 30));
    int32_t h = !!g;
    return h + g + y;
}
