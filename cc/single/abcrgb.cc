// Konvertierung von ABC -> RGB -> ABC

#include <cstdio>
#include <cmath>

#include "single.h"

void rgbeingabe (long double& orot, long double& ogrn, long double& oblu)
  {
  printf ("\n");
  printf ("rot:   ");
  scanf ("%Lf", &orot);
  printf ("grün:  ");
  scanf ("%Lf", &ogrn);
  printf ("blau:  ");
  scanf ("%Lf", &oblu);
  printf ("\n");
  }
  
void abceingabe (long double& ohel, long double& osat, long double& ocol)
  {
  printf ("\n");
  printf ("Helligkeit:   ");
  scanf ("%Lf", &ohel);
  printf ("Saettigung:   ");
  scanf ("%Lf", &osat);
  printf ("Farbwinkel:   ");
  scanf ("%Lf", &ocol);
  ocol=ocol/180*M_PI;
  printf ("\n");
  }
  
void rgbausgabe (long double irot, long double igrn, long double iblu)
  {
  printf ("rot:     %24.9Lf\n", irot);
  printf ("grün:    %24.9Lf\n", igrn);
  printf ("blau:    %24.9Lf\n", iblu);
  printf ("\n");
  }
  
void abcausgabe (long double ihel, long double isat, long double icol)
  {
  printf ("Helligkeit:    %24.9Lf\n", ihel);
  printf ("Saettigung:    %24.9Lf\n", isat);
  printf ("Farbwinkel:    %24.9Lf %14.8Lf\n", icol, icol/M_PI*180);
  printf ("\n");
  }
 
 void rechneabcrgb ()
  {
  long double prot, pgrn, pblu;
  long double phel, psat, pcol;
  abceingabe (phel, psat, pcol);
  abcausgabe (phel, psat, pcol);
  abctorgb (phel, psat, pcol, prot, pgrn, pblu);
  rgbausgabe (prot, pgrn, pblu);
  rgbtoabc (prot, pgrn, pblu, phel, psat, pcol);
  abcausgabe (phel, psat, pcol);
  }

int main ()
  {
  rechneabcrgb ();
  return 0;
  }
