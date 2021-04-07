#include <stdint.h>

int32_t main()
{
    int32_t a = 1;
    {
        int32_t a = 2;
        a = 0;
    }
    return a;
}