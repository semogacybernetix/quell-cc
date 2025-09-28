#include <cmath>
#include <cstdio>

void phytagoras ()
  {
  long double kseite;
  for (long double lauf= 1; lauf < 200; lauf++)
    for (long double ilauf= 1; ilauf < lauf; ilauf++)
      {
      kseite= sqrtl (lauf*lauf + ilauf*ilauf);
      if ((kseite - floorl (kseite)) < 1e-8)
        printf ("%6.0Lf  %6.0Lf  %6.0Lf %12.6Lf\n", ilauf, lauf, kseite, 180/M_PIl*atanl (ilauf/lauf));
      }
  }

void binaerphytagoras ()
  {
  long double a, b, c;
  for (long double lauf= -10; lauf < 20; lauf++)
    {
    a= powl (2, lauf + 1);
    b= powl (2, 2*lauf) - 1;
    c= powl (2, 2*lauf) + 1;
    printf ("%32.16Lf  %32.16Lf  %32.16Lf %32.16Lf\n", a, b, c, 180/M_PIl*atanl (a/b));
    }
  }

int main ()
  {
  phytagoras ();
  printf ("\n");
  binaerphytagoras ();
  return 0;
  }
