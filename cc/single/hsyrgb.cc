// Konvertierung von HSY -> RGB -> HSY

#include "single.h"

#include <cstdio>
#include <cmath>

void rgbeingabe (real& orot, real& ogrn, real& oblu)
  {
  integer ret;
  printf ("\n");
  printf ("rot:   ");
  ret= scanf ("%Lf", &orot);
  printf ("grün:  ");
  ret= scanf ("%Lf", &ogrn);
  printf ("blau:  ");
  ret= scanf ("%Lf", &oblu);
  printf ("\n");
  ret++;
  }
  
void hsyeingabe (real& ohue, real& osat, real& ohell)
  {
  integer ret;
  printf ("\n");
  printf ("hue[°]:   ");
  ret= scanf ("%Lf", &ohue);
  ohue= ohue/180*M_PI;
  printf ("sat[°]:   ");
  ret= scanf ("%Lf", &osat);
  osat= osat/180*M_PI;
  printf ("hell:     ");
  ret= scanf ("%Lf", &ohell);
  printf ("\n");
  ret++;
  }
  
void rgbausgabe (real irot, real igrn, real iblu)
  {
  printf ("rot:     %24.9Lf\n", irot);
  printf ("grün:    %24.9Lf\n", igrn);
  printf ("blau:    %24.9Lf\n", iblu);
  printf ("\n");
  }
  
void hsyausgabe (real ihue, real isat, real ihell)
  {
  printf ("Hue:     %24.9Lf %24.Lf\n", ihue, ihue/M_PI*180);
  printf ("Sat:     %24.9Lf %24.Lf\n", isat, isat/M_PI*180);
  printf ("Hell:    %24.9Lf\n", ihell);
  printf ("\n");
  }
 
 void rechnehsyrgb ()
  {
  real prot, pgrn, pblu;
  real phue, psat, phell;
  hsyeingabe (phue, psat, phell);
  hsyausgabe (phue, psat, phell);
  hsytorgb (phue, psat, phell, prot, pgrn, pblu);
  rgbausgabe (prot, pgrn, pblu);
  rgbtohsy (prot, pgrn, pblu, phue, psat, phell);
  hsyausgabe (phue, psat, phell);
  }

int main ()
  {
  rechnehsyrgb ();
  return 0;
  }
