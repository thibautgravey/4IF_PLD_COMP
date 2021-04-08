#include <stdint.h>

int32_t fibonacci(int32_t n)
{
  if (n == 0 || n == 1)
    return n;
  else
    return (fibonacci(n - 1) + fibonacci(n - 2));
}

int32_t main()
{
  int32_t nbr = 15;
  return fibonacci(nbr);
}