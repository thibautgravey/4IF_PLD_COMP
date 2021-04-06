#include <stdint.h>
int32_t main()
{
    int32_t a = 0;
    int32_t r = 0;

    if (a == 0)
    {
        int32_t a = 1;
        if (a == 0)
            r = r + 1;
        if (a == 1)
        {
            int32_t a = 2;
            if (a == 1)
                r = r + 2;

            if (a == 2)
            {
                r = r + 4;
            }
            else
                r = r + 8;
        }
    }
    else
    {
        if (a == 0)
            r = r + 16;
    }

    if (a == 0)
        r = r + 32;

    return r;
}