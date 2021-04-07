#include <stdint.h>

int32_t main()
{

    int32_t cpt = 0;

    for (1 + 1, 2 + 2; cpt < 10;)
    {
        cpt = cpt + 1;
    }

    return cpt;
}