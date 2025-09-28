void genauigkeit ()
  {
  real wert1, wert2, faktor, exponent;

  wert1= 1;
  faktor= logl (10);
  exponent= 0;
    do
    {
    wert2= wert1 + expl (-exponent*faktor);
    printf ("wert2: %3.0Lf %70.66Lf\n", exponent, wert2);
    exponent++;
    }
//  while (exponent < 50);
  while (wert2 != wert1);
  

  }

/*

float             8
double           16
long double      20

__float80        20
__float128       35

*/
