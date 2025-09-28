// Berechnung der relativen Exponentialfunktion

#include "../screen/allscr.h"
#include "single.h"
#include "../class/vektor.h"

#include <cstdio>
#include <cstdlib>
#include <cmath>

#define ftype double
#define itype signed long

const ftype acht (8);
const ftype zwei (2);
const ftype drei (3);
const ftype vier (4);

ftype berechnerechteck (ftype ix)
  {
  ftype ret= 0;
  for (itype klauf= 1; klauf < 100; klauf++)
    {
    ftype kr= ftype (klauf);
    ftype ak= acht/(kr*M_PI*M_PI)*sin (kr*M_PI/zwei);
    ret+= ak*cos (klauf*ix);
    }
  return ret;
  }

ftype berechnek3 (signed long ik)
  {
  ftype kr= ftype (ik);
  ftype pot= pow (2, kr);
  return pot/(pot + 1)*100;
  }

ftype berechnek4 (signed long ik)
  {
  ftype kr= ftype (ik);
  ftype pot= pow (1.5, kr);
  return pot/(pot + 1)*100;
  }

ftype berechnerelexpo (ftype ix)
  {
  ftype ret= 0;
  ret= exp (ix);
  return ret/(ret + 1) - 0.5;
  }

void zeichnerelexpo ()
  {
  cbmpdatei hslbild ("relexpo.bmp", 1280, 720);
//  hslbild.hintergrund (0xff);
  for (signed long laufx= 0; laufx < 1279; laufx++)
    {
    double rx= (laufx - 640)/double (100);
    ftype fx= berechnerelexpo (rx);
    ftype tx= tanh (rx/2);
    signed long werty= 383 + rint (fx*500 + 0.5);
    signed long tany= 383 + rint (tx*250 + 0.5);
    hslbild.putpixel (laufx, 383 + 250, 0, 0, 255);
    hslbild.putpixel (laufx, 383 +   0, 0, 0, 255);
    hslbild.putpixel (laufx, 383 - 250, 0, 0, 255);
    hslbild.putpixel (laufx, tany, 255, 0, 0);
    hslbild.putpixel (laufx, werty, 255, 255, 255);
    }
  }


int main ()
  {
  zeichnerelexpo ();
  printf ("Mischung                 ptot= 2                 ptot= 1.5\n\n");
  for (signed long laufk= -10; laufk <= 10; laufk++)
    {
    ftype ak3= berechnek3 (laufk);
    ftype ak4= berechnek4 (laufk);
    printf ("a%4ld     %24.9f%24.9f\n", laufk, ak3, ak4);
    }
  return 0;
  }
