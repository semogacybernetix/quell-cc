#include <cmath>
#include <cstdio>

void udirekursiv ()
  {
  long double L, C, f, ton, tr, tf, Ue, Uc0, I0, r, phi, uc, i;
/*
  printf ("f: ");
  scanf ("%Lf", &f);
  printf ("ton: ");
  scanf ("%Lf", &ton);
  printf ("L: ");
  scanf ("%Lf", &L);
  printf ("C: ");
  scanf ("%Lf", &C);
  printf ("Ue: ");
  scanf ("%Lf", &Ue);
  printf ("Uc: ");
  scanf ("%Lf", &Uc0);
  printf ("I: ");
  scanf ("%Lf", &I0);
*/  
  f= 1;
  ton= 0.5;
  L= 1;
  C= 1;
  Ue= 1;
  Uc0= 0;
  I0= 0;

  tr= (1-ton)/f;
  tf= ton/f;
  uc= Uc0;
  i= I0;
  
//  f= atan2 (-7,0);
  
  printf ("f:   %4.2Lf\n", f);
  printf ("ton: %8Lf\n", ton);
  printf ("L:   %8Lf\n", L);
  printf ("C:   %8Lf\n", C);
  printf ("Ue:  %8Lf\n", Ue);
  printf ("tr:  %8Lf\n", tr);
  printf ("tf:  %8Lf\n", tf);
  printf ("\n");
  
  for (signed long lauf= 0; lauf < 50000; lauf++)
    {
    r= sqrt (uc*uc + L/C*i*i);
    phi= atan2 (uc, sqrt(L/C)*i);
//    printf ("r:   %24.20Lf\n", r);
//    printf ("phi: %24.20Lf\n", phi);
    uc= r*sin (1/sqrt(L*C)*tr + phi);
    i= r*sqrt (C/L)*cos (1/sqrt(L*C)*tr + phi);
    printf ("uc: %24.20Lf", uc);
    printf ("i:  %24.20Lf", i);
    printf ("\n\n");
    r= sqrt ((uc-Ue)*(uc-Ue) + L/C*i*i);
    phi= atan2 (uc-Ue, sqrt(L/C)*i);
//    printf ("r:   %24.20Lf\n", r);
//    printf ("phi: %24.20Lf\n", phi);
    
    long double ucnull= Ue + r*sin (phi);
    long double inull= r*sqrt (C/L)*cos (phi);
//    printf ("ucnull: %24.20Lf\n", ucnull);
//    printf ("inull:  %24.20Lf\n", inull);
    
    uc= Ue + r*sin (1/sqrt(L*C)*tf + phi);
    i= r*sqrt (C/L)*cos (1/sqrt(L*C)*tf + phi);
    printf ("uc: %24.20Lf", uc);
    printf ("i:  %24.20Lf", i);
    printf ("\n\n");
    }  
  }

int main ()
  {
  udirekursiv ();
  return 0;
  }
