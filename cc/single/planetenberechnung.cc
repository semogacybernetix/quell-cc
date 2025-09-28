// Dieses Programm berechnet die Satellitengeschwindigkeiten um einen fiktiven Planeten

#include "../class/vektor.h"

#include <cstdio>

signed long entscheidungseingabe ()
  {
  signed long retf= 0;
  retf+= 0;
  signed long ent;
  printf ("\n");
  printf ("[1]  Dichte, Durchmesser, Höhe eingeben        [2]  Fallbeschleunigung, Radius, Höhe eingeben        [3]  Fallbeschleunigung, Radius, Umlaufzeit eingeben   ");
  retf= scanf ("%ld", &ent);
  return ent;
  }

void datenausgabe (long double masse, long double dichte, long double kgeschw1, long double geschw, long double umlauft,
                   long double obeschl, long double bbeschl, long double hoehe)
  {
  printf ("\n");
  printf ("Planetendaten:\n");
  printf ("  Masse:                                %Le kg\n", masse);
  printf ("  Dichte:                     %15.3Lf g/cm³\n", dichte);
  printf ("  Oberflächenbeschleunigung:  %15.3Lf m/s²\n", obeschl);
  printf ("  Fallzeit aus 1m Höhe:       %15.3Lf s\n", sqrtl (2/obeschl));
  printf ("  Höhe für 1m Fall:           %15.3Lf m\n", 9.81/obeschl);
  printf ("\n");
  printf ("  1. kosmische Geschwindigkeit (Radiusbahngeschwindigkeit):       %15.3Lf m/s       %15.3Lf km/h\n", kgeschw1, 3.6*kgeschw1);
  printf ("  2. kosmische Geschwindigkeit (Flucht/Aufprallgeschwindigkeit):  %15.3Lf m/s       %15.3Lf km/h\n", sqrtl (2)*kgeschw1, sqrtl (2)*3.6*kgeschw1);
  printf ("\n");
  printf ("Bahndaten:\n");
  printf ("  Bahnbeschleunigung:    %15.3Lf m/s²\n", bbeschl);
  printf ("  Bahngeschwindigkeit:   %15.3Lf m/s       %15.3Lf km/h\n", geschw, 3.6*geschw);
  printf ("  Umlaufzeit:            %11.0Lf     s         %15.3Lf h\n", umlauft, umlauft/3600);
  printf ("  Höhe:                                    %23.3Lf km\n", hoehe/1000);
  printf ("\n");
  }

void berechnemitdichte ()
  {
  signed long retf= 0;
  retf+= 0;
  printf ("\n");
  long double dichte;
  printf ("Dichte [g/cm³]:        ");
  retf= scanf ("%Lf", &dichte);
  long double radius;
  printf ("Durchmesser [km]:      ");
  retf= scanf ("%Lf", &radius);
  long double hoehe;
  printf ("Höhe [km]:             ");
  retf= scanf ("%Lf", &hoehe);

  // Einheiten auf Basis skalieren
  radius*= 0.5;
  long double radiusm= radius*1000;
  long double hoehem= hoehe*1000;
  long double dichtem= dichte*1000;
  long double bhoehe= radiusm + hoehem;

  // Masse berechnen
  long double volumen= (long double) (4)/3*M_PIl*radiusm*radiusm*radiusm;
  long double masse= volumen*dichtem;

  // Beschleunigungen berechnen
  long double obeschl= 6.672e-11*masse/(radiusm*radiusm);
  long double bbeschl= 6.672e-11*masse/(bhoehe*bhoehe);

  // Geschwindigkeiten berechnen
  long double kgeschw1= sqrtl (obeschl*radiusm);
  long double geschw= sqrtl (bbeschl*bhoehe);

  // Umlaufzeit berechnen
  long double umlauft= 2*M_PIl*sqrtl (bhoehe/bbeschl);

  datenausgabe (masse, dichte, kgeschw1, geschw, umlauft, obeschl, bbeschl, hoehem);
  }

void berechnemitbeschl ()
  {
  signed long retf= 0;
  retf+= 0;
  printf ("\n");
  long double obeschl;
  printf ("Fallbeschleunigung [m/s²]:  ");
  retf= scanf ("%Lf", &obeschl);
  long double radius;
  printf ("Durchmesser [km]:           ");
  retf= scanf ("%Lf", &radius);
  long double hoehe;
  printf ("Höhe [km]:                  ");
  retf= scanf ("%Lf", &hoehe);

  // Einheiten auf Basis skalieren
  radius*= 0.5;
  long double radiusm= radius*1000;
  long double hoehem= hoehe*1000;
  long double bhoehe= radiusm + hoehem;

  // Masse berechnen
  long double volumen= (long double) (4)/3*M_PIl*radiusm*radiusm*radiusm;
  long double masse= obeschl*radiusm*radiusm/6.672e-11;
  long double dichte= masse/volumen/1000;

  // Bahnbeschleunigung berechnen
  long double bbeschl= 6.672e-11*masse/(bhoehe*bhoehe);

  // Geschwindigkeiten berechnen
  long double kgeschw1= sqrtl (obeschl*radiusm);
  long double geschw= sqrtl (bbeschl*bhoehe);

  // Umlaufzeit berechnen
  long double umlauft= 2*M_PIl*sqrtl (bhoehe/bbeschl);

  datenausgabe (masse, dichte, kgeschw1, geschw, umlauft, obeschl, bbeschl, hoehem);
  }

void berechnemitumlaufzeit ()
  {
  signed long retf= 0;
  retf+= 0;
  printf ("\n");
  long double obeschl;
  printf ("Fallbeschleunigung [m/s²]:  ");
  retf= scanf ("%Lf", &obeschl);
  long double radius;
  printf ("Durchmesser [km]:           ");
  retf= scanf ("%Lf", &radius);
  long double umlauft;
  printf ("Umlaufzeit   [h]:           ");
  retf= scanf ("%Lf", &umlauft);

  // Einheiten auf Basis skalieren
  radius*= 0.5;
  long double radiusm= radius*1000;
  long double umlauftm= umlauft*3600;

  // Masse berechnen
  long double volumen= (long double) (4)/3*M_PIl*radiusm*radiusm*radiusm;
  long double masse= obeschl*radiusm*radiusm/6.672e-11;
  long double dichte= masse/volumen/1000;

  // Höhe berechnen
  long double bhoehe= powl (6.672e-11*masse*powl (umlauftm/(2*M_PIl), 2), 1./3);

  // Bahnbeschleunigung berechnen
  long double bbeschl= 6.672e-11*masse/(bhoehe*bhoehe);

  // Geschwindigkeiten berechnen
  long double kgeschw1= sqrtl (obeschl*radiusm);
  long double geschw= sqrtl (bbeschl*bhoehe);

  long double hoehem= bhoehe - radiusm;
  datenausgabe (masse, dichte, kgeschw1, geschw, umlauftm, obeschl, bbeschl, hoehem);
  }

int main ()
  {
  signed long ent (entscheidungseingabe ());
  switch (ent)
    {
 case 1:
      berechnemitdichte ();
   break;
 case 2:
    berechnemitbeschl ();
   break;
 case 3:
    berechnemitumlaufzeit ();
   break;
 }
  return 0;
  }
