#include <stdint.h>

int32_t main()
{
    int32_t ret;
    int32_t a = 1;
    ret = ret + a;
    {
        int32_t a = 2;
        ret = ret + a;
        {
            int32_t a = 4;
            int32_t b = 1;
            ret = ret + a + b;
            {
                int32_t c = a + b;
                ret = ret + c;
                {
                    int32_t b = 5;
                    int32_t c = a + b;
                    ret = ret + b + c;
                }
            }
            ret = ret * 2;
        }
        a = 1000;
    }
    return ret + a;
}