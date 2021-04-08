#include <stdint.h>

//Structures de contrôle, blocs
int32_t main() {
    int32_t a = 3;
    if (a == 3) {
        int32_t i = 0;
        while (i < a) {
            i = i + 1;
        }
        int32_t j;
        for (j = 0; j < a; j = j + 1) {}
        return i + j; //6
    }
    return a; //!3
}