#include <cstdio>

void auf2 ()
  {
  long double sum= 0;
  long double prod= 1;
  for (unsigned long nlauf= 1; nlauf < 50; nlauf++)
    {
    prod*= 2;
    sum+= (nlauf*2 - 1)/prod;
    printf ("%5ld Summe: %10.20Lf\n",nlauf, sum);
    }
  }

void auf3 ()
  {
  long double prod= 1;
  for (unsigned long nlauf= 2; nlauf < 100; nlauf++)
    {
    prod*= (nlauf*nlauf*nlauf - 1)/(nlauf*nlauf*nlauf + 1.);
    printf ("%5ld Produkt: %10.20Lf\n",nlauf, prod);
    }
  }

void auf4 ()
  {
  long double sum= 0;
  unsigned long m= 1;
  for (unsigned long nlauf= 2; nlauf < 100000000; nlauf+= 4)
    {
    sum+= 1./m - 1./nlauf - 1./(nlauf+2);
    m+= 2;
    printf ("%5ld Summe: %10.20Lf\n",nlauf, sum);
    }
  }

int main ()
  {
  auf4 ();
  return 0;
  }
  
