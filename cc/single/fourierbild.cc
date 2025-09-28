// Berechnung der Fourieranalyse eines Rechtecksignals mit 1/3 Totzeit und 1/2 Totzeit

#include "../screen/allscr.h"
#include "single.h"
#include "../class/vektor.h"

#include <cstdio>
#include <cstdlib>

const long double acht (8);
const long double zwei (2);
const long double drei (3);
const long double vier (4);
const long double hundert (100);

long double berechnerechteck (long double ix)
  {
  long double ret= 0;
  for (long double klauf= 1; klauf < 100; klauf++)
    {
    long double ak= acht/(klauf*M_PI*M_PI)*sin (klauf*M_PI/zwei);
    ret+= ak*cos (klauf*ix);
    }
  return ret;
  }

long double berechnek3 (long double kr)
  {
  return sqrt (drei)/(M_PI*kr)*(sin (kr*M_PI/drei) + sin (kr*2*M_PI/drei));
  }

long double berechnek4 (long double kr)
  {
  return zwei/(M_PI*kr)*(sin (kr*M_PI/vier) + sin (kr*drei*M_PI/vier));
  }

long double berechnefourier (long double ix)
  {
  long double ret= 0;
  for (long double klauf= 1; klauf < 100; klauf++)
    {
    long double ak= berechnek3 (klauf);
    ret+= pow ((long double)(1.02), 1-klauf)*ak*cos (klauf*ix);
    }
  return ret;
  }

void zeichnefourier ()
  {
  cbmpdatei hslbild ("fourierbild.bmp", 1280, 720);
//  hslbild.hintergrund (0xff);
for (long double laufk= 0; laufk < 20; laufk++)
  {
  for (long double laufx= 0; laufx < 1279; laufx++)
    {
    long double rx= laufx/hundert;
    long double fx= berechnefourier (rx);
    long double fk= berechnek3 (laufk);
    long double fcos= fk*cos (laufk*rx);
    signed long plotcos= 383 + lrint (fcos*hundert);
    signed long ploty= 383 + lrint (fx*hundert);
    hslbild.putpixel (laufx, 383, 0, 0, 255);
    hslbild.putpixel (laufx, plotcos, 0, 255, 0);
    hslbild.putpixel (laufx, ploty, 255, 0, 0);
    }
  }
  for (signed long laufk= 0; laufk < 100; laufk++)
    {
    long double fk= berechnek3 (laufk);
    signed long plotk= lrint (hundert*fk);
    signed long kadd;
    if (plotk >= 0)
      kadd= 1;
      else
      kadd= -1;
    for (signed long laufy= 0; abs (laufy) < abs (plotk); laufy+= kadd)
      hslbild.putpixel (laufk*2, hundert + laufy, 0, 0, 0);
    }
  for (signed long laufk= 0; laufk < 100; laufk++)
    {
    long double fk= berechnek4 (laufk);
    signed long plotk= lrint (hundert*fk);
    signed long kadd;
    if (plotk >= 0)
      kadd= 1;
      else
      kadd= -1;
  for (signed long laufy= 0; abs (laufy) < abs (plotk); laufy+= kadd)
      hslbild.putpixel (250 + laufk*2, 100 + laufy, 0, 0, 0);
    }
  }


int main ()
  {
  zeichnefourier ();
  printf ("Harmonische            ptot=1/3            ptot= 1/4 \n");
  for (long double laufk= 1; laufk < 20; laufk++)
    {
    long double ak3= berechnek3 (laufk);
    long double ak4= berechnek4 (laufk);
    printf ("a%2Lf     %24.9Lf%24.9Lf\n", laufk, ak3, ak4);
    }
  return 0;
  }
