#include <stdint.h>

int32_t main()
{

    int32_t cpt = 0;

    for (int32_t i = 0, j = 9; i < j; i = i + 1, j = j - 1)
    {
        cpt = cpt + i + j;
    }

    return cpt;
}