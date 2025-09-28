#include <cstdio>
#include <cmath>

void inab ()
  {
  long double la, ka, lb, kb;
  printf ("a1:  ");
  scanf ("%Lf", &la);
  printf ("b1:  ");
  scanf ("%Lf", &lb);
  printf ("a2:  ");
  scanf ("%Lf", &ka);
  printf ("b2:  ");
  scanf ("%Lf", &kb);
  long double alpha= ka/la;
  long double beta= kb/lb;
  long double na= la*alpha*(1 - beta)/ (1 - alpha*beta);
  long double nb= lb*beta*(1 - alpha)/ (1 - alpha*beta);

  printf ("a1:   %24.20Lf\n", la);
  printf ("b1:   %24.20Lf\n", lb);
  printf ("a2:   %24.20Lf\n", ka);
  printf ("b2:   %24.20Lf\n", kb);
  printf ("a3:   %24.20Lf\n", na);
  printf ("b3:   %24.20Lf\n", nb);
  }

int main ()
  {
  inab ();
  return 0;
  }
