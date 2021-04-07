#include <stdint.h>

int32_t main()
{

    int32_t cpt = 0;

    for (int32_t i = 0; i < 10; i = i + 1)
    {
        cpt = cpt + i;
    }

    return cpt;
}