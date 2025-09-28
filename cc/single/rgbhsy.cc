// Dieses Programm konvertiert RGB <-> HSY

#include <cstdio>
#include <cmath>

#include "single.h"

using namespace std;

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
  printf ("hue:   ");
  ret= scanf ("%Lf", &ohue);
  printf ("sat:  ");
  ret= scanf ("%Lf", &osat);
  printf ("hell:  ");
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
  
 void rechnergbhsy ()
  {
  real prot, pgrn, pblu;
  real phue, psat, phell;
  rgbeingabe (prot, pgrn, pblu);
  rgbausgabe (prot, pgrn, pblu);
  rgbtohsy (prot, pgrn, pblu, phue, psat, phell);
  hsyausgabe (phue, psat, phell);
  hsytorgb (phue, psat, phell, prot, pgrn, pblu);
  rgbausgabe (prot, pgrn, pblu);
  }

int main ()
  {
  rechnergbhsy ();
  return 0;
  }
