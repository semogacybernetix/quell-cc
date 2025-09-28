// Dieses Programm berechnet die (Entfernung über die Erdoberfläche) zweier in Koordinaten gegebenen Punkte der Erdoberfläche

#include "../class/vektor.h"

#include <cstdio>

signed long entscheidungseingabe ()
  {
  signed long retf= 0;
  retf+= 0;
  signed long ent;
  printf ("\n");
  printf ("[1] Orte eingeben        [2] Höhe eingeben   ");
  retf= scanf ("%ld", &ent);
  return ent;
  }
  
void koordinateneingabe (long double& pbg, long double& plg)
  {
  signed long retf= 0;
  retf+= 0;
  long double bgr, bmi, bse, lgr, lmi, lse;
  printf ("\n");
  printf ("Breitengrad:        ");
  retf= scanf ("%Lf", &bgr);
  printf ("Breitenminute:      ");
  retf= scanf ("%Lf", &bmi);
  printf ("Breitensekunde:     ");
  retf= scanf ("%Lf", &bse);
  printf ("Längengrad:         ");
  retf= scanf ("%Lf", &lgr);
  printf ("Längenminute:       ");
  retf= scanf ("%Lf", &lmi);
  printf ("Längensekunde:      ");
  retf= scanf ("%Lf", &lse);
  pbg= (bgr/180 + bmi/10800 + bse/648000)*M_PIl;
  plg= (lgr/180 + lmi/10800 + lse/648000)*M_PIl;
  printf ("\n");
  }
  
void datenausgabe (long double bg1, long double bg2, long double lg1, long double lg2, long double entf, long double entfd)
  {
  printf ("\n");
  printf ("Ort1:         %2.12Lf    %2.12Lf\n", bg1, lg1);
  printf ("Ort2:         %2.12Lf    %2.12Lf\n", bg2, lg2);
  printf ("\n");
  printf ("Entfernung:    %6.3Lf km    %6.3Lf km\n", entf, entfd);
  printf ("\n");
  }
  
void berechneentfernung ()
  {
  long double bg1, lg1, bg2, lg2;
  koordinateneingabe (bg1, lg1);
  koordinateneingabe (bg2, lg2);
  long double entf (6370*acosl (sinl (bg1)*sinl (bg2) + cosl (bg1)*cosl (bg2)*cosl (lg1 - lg2)));
  long double x1 (cosl (lg1)*cosl (bg1));
  long double y1 (sinl (lg1)*cosl (bg1));
  long double z1 (sinl (bg1));
  long double x2 (cosl (lg2)*cosl (bg2));
  long double y2 (sinl (lg2)*cosl (bg2));
  long double z2 (sinl (bg2));
  long double v1 (x1 - x2);
  long double v2 (y1 - y2);
  long double v3 (z1 - z2);
  long double entf2 (6370*sqrtl (v1*v1 + v2*v2 + v3*v3));
  datenausgabe (bg1, bg2, lg1, lg2, entf, entf2);
  }
  
void berechnehoehe ()
  {
  signed long retf= 0;
  retf+= 0;
  printf ("\n");
  printf ("Höhe:[m]          ");
  long double hoe, hyp, entf, entf2;
  retf= scanf ("%Lf", &hoe);
  hyp= 6370 + hoe/1000;
  entf= 6370*acosl (6370/hyp);
  entf2= sqrtl (hyp*hyp - 6370*6370);
  printf ("Entfernung:    %6.3Lf km  %6.3Lf km\n", entf, entf2);
  printf ("\n");
  }
  
int main ()
  {
  signed long ent (entscheidungseingabe ());
  switch (ent)
    {
	case 1:
      berechneentfernung ();
	  break;
	case 2:
 	  berechnehoehe ();
	  break;
	}
  return 0;
  }
