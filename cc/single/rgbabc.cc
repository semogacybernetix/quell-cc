// Dieses Programm konvertiert RGB <-> ABC
// A: Helligkeit[0-255]
// B: Saettigung[0-255]
// C: Farbwinkel[-PI-PIs]

#include <cstdio>
#include <cmath>

#include "single.h"

using namespace std;

void rgbeingabe (float& orot, float& ogrn, float& oblu)
  {
  printf ("\n");
  printf ("rot:   ");
  scanf ("%f", &orot);
  printf ("grün:  ");
  scanf ("%f", &ogrn);
  printf ("blau:  ");
  scanf ("%f", &oblu);
  printf ("\n");
  }
  
void abceingabe (float& ohel, float& osat, float& ofar)
  {
  printf ("\n");
  printf ("Helligkeit:   ");
  scanf ("%f", &ohel);
  printf ("Saettigung:   ");
  scanf ("%f", &osat);
  printf ("Farbwinkel:   ");
  scanf ("%f", &ofar);
  ofar= ofar/180*M_PI;
  printf ("\n");
  }
  
void rgbausgabe (float irot, float igrn, float iblu)
  {
  printf ("rot:     %24.9f\n", irot);
  printf ("grün:    %24.9f\n", igrn);
  printf ("blau:    %24.9f\n", iblu);
  printf ("\n");
  }
  
void abcausgabe (float ihel, float isat, float ifar)
  {
  printf ("Helligkeit:    %24.9f\n", ihel);
  printf ("Saettigung:    %24.9f\n", isat);
  printf ("Farbwinkel:    %24.9f %14.8f\n", ifar, ifar/M_PI*180);
  printf ("\n");
  }
  
 void rechnergbabc ()
  {
  float prot, pgrn, pblu;
  float phel, psat, pfar;
  rgbeingabe (prot, pgrn, pblu);
  rgbausgabe (prot, pgrn, pblu);
  rgbtoabc (prot, pgrn, pblu, phel, psat, pfar);
  abcausgabe (phel, psat, pfar);
  abctorgb (phel, psat, pfar, prot, pgrn, pblu);
  rgbausgabe (prot, pgrn, pblu);
  }

int main ()
  {
  rechnergbabc ();
  return 0;
  }
