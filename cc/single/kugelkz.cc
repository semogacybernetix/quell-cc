// Dieses Programm berechnet das Volumen aus eine Kugelannäherung durch Zylinder und Kegel

#include <cstdio>
#include <cmath>

using namespace std;

void kugelkzvol ()
  {
// Kantenlängeneingabe

  printf ("\n");
  long double klen;
  printf ("  Kantenlänge:     ");
  int ret= scanf ("%Lf", &klen);
  if (ret == 0) return;

// Volumenberechnung

  //Volumen Zylinder
  long double r1= klen/2;
  long double d2= klen + 2*klen/sqrt(2);
  long double r2= d2/2;
  long double volzyl= klen * M_PI*r2*r2;

  // Volumen Kegel
  long double g1= M_PI*r1*r1;
  long double g2= M_PI*r2*r2;
  long double kegh= klen/sqrt(2);
  long double volkeg= kegh/3 * (g1 + g2 + sqrt (g1*g2));

  // Volumen Kugel
  long double volkug= volzyl + 2*volkeg;
  long double objh= klen + 2*kegh;
  long double volkug2= r1*r1*r1*M_PI*(22*sqrt(2)/3 + 10);
  long double volzyl2= r1*r1*r1*M_PI*(4*sqrt(2) + 6);
  long double volkeg2= r1*r1*r1*M_PI*(5*sqrt(2)/3 + 2);
  long double obkeg= r1*r1*M_PI*(8*sqrt(2) + 14);

  // Volumen 8-spitz
  long double volspitz= r1*r1*r1*M_PI*(sqrt(2) - 1)/3;
  long double volstumpf= r1*r1*r1*M_PI/3*(3 + sqrt (2));
  long double vol8spitz= 2*(volspitz + volstumpf);

  // Oberfläche 8-spitz
  long double obspitz= r1*r1*M_PI*sqrt (4 - 2*sqrt(2));
  long double obstumpf= r1*r1*M_PI*(1 + sqrt(2))*sqrt(4 - 2*sqrt(2));
  long double ob8spitz= 2*(obspitz + obstumpf);

  printf ("\n");
  printf ("  Kantenlänge            :              %18.3Lf\n", klen);
  printf ("  Zylinderdurchmesser    :              %18.3Lf\n", d2);
  printf ("  Objekthöhe             :              %18.3Lf\n", objh);
  printf ("  Zylindervolumen        :              %18.3Lf\n", volzyl);
  printf ("  Kegelvolumen           :              %18.3Lf\n", volkeg);
  printf ("  Volumen Kugelannäherung:              %18.3Lf\n", volkug);
  printf ("  Volumen Kugelannäherung:              %18.3Lf\n", volkug2);
  printf ("  Zylindervolumen        :              %18.3Lf\n", volzyl2);
  printf ("  Kegelvolumen           :              %18.3Lf\n", volkeg2);
  printf ("  Oberfläche Kugelnäherung:             %18.3Lf\n", obkeg);
  printf ("  Volumen 8-spitz:                      %18.8Lf\n", vol8spitz);
  printf ("  Oberfläche 8-spitz:                   %18.8Lf\n", ob8spitz);

  printf ("\n");
  return;
  }

int main ()
  {
  kugelkzvol ();
  return 0;
  }
