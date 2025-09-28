#include <cmath>
#include <cstdio>

long double fakul (signed long long n)
  {
  if (n < 2)
    return 1;
  return n*fakul (n - 1);
  }

long double comb (signed long long n, signed long long r)
  {
  long double prod= 1;
  while (r > 0)
    prod*= (long double) (n--) / (long double) (r--);
  return prod;
  }

long double bellrekursiv (signed long long n)
  {
  if (n == 0)
    return 1;
  long double summe= 0;
  for (signed long long k= 0; k < n; k++)
    summe+= bellrekursiv (k) * comb (n - 1, k);
  return summe;
  }

long double belliterativ (signed long long n)
  {
  if (n == 0)
    return 1;
  long double summe= 0;
  long double summand;
  signed long long k= 0;
    do
    {
    summand = powl (k,n) / fakul (k);
    summe+= summand;
    k++;
    }
  while (!((summand > 0) && (summand < 1)));
  return rintl (exp (-1) * summe);
  }

int main ()
  {
  for (signed long long x = 0; x < 24; x++)
    printf ("Bei %3llu  %30Lf  Partitionen  %30Lf\n", x, bellrekursiv (x), belliterativ (x));
  return 0;
  }
