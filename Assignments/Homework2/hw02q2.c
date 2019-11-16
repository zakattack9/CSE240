#include <stdio.h>
#pragma warning(disable : 4996) // needed in VS

#define addm(a, b) (a + b)
#define squarem(a) (a * a)
#define maxm(a, b) (a >= b ? a : b)
#define evenm(a) (a % 2 == 0 ? 0 : 1)

int addf(int a, int b)
{
  return a + b;
}

int squaref(int a)
{
  return a * a;
}
int maxf(int a, int b)
{
  if (a >= b)
  {
    return a;
  }
  else
  {
    return b;
  }
}
int evenf(int a)
{
  if (a % 2 == 0)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

int main()
{
  int a = 2, b = 8;

  printf("addf(a, b) = %d \n", addf(a, b));
  printf("addm(a, b) = %d \n", addm(a, b));
  printf("addf(a++, b--) = %d \n", addf(a++, b--));
  a = 2;
  b = 8;
  printf("addm(a++, b--) = %d \n", addm(a++, b--));

  a = 2;
  b = 8;
  printf("squaref(a) = %d \n", squaref(a));
  printf("squarem(a) = %d \n", squarem(a));
  printf("squaref(--a) = %d \n", squaref(--a));
  a = 2;
  b = 8;
  printf("squarem(--a) = %d \n", squarem(--a));

  a = 2;
  b = 8;
  printf("maxf(a, b) = %d \n", maxf(a, b));
  printf("maxm(a, b) = %d \n", maxm(a, b));
  printf("maxf(--a, --b) = %d \n", maxf(--a, --b));
  a = 2;
  b = 8;
  printf("maxm(--a, --b) = %d \n", maxm(--a, --b));

  a = 2;
  b = 8;
  printf("evenf(a) = %d \n", evenf(a));
  printf("evenm(a) = %d \n", evenm(a));
  printf("evenf(a++) = %d \n", evenf(a++));
  a = 2;
  b = 8;
  printf("evenm(a++) = %d \n", evenm(a++));
}
