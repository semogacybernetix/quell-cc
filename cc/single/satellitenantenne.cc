// Dieses Programm berechnet die Ausrichtung einer Satellitenantenne

#include "../class/vektor.h"

#include <cstdio>

void zahlausgabe (real pzahl)
  {
  printf ("%50.2Lf\n", pzahl);
  }

void vektorausgabe (cvektor3 p1)
  {
  printf ("%50.2Lf\n", p1.x);
  printf ("%50.2Lf\n", p1.y);
  printf ("%50.2Lf\n", p1.z);
  printf ("\n");
  }

void matrixausgabe (cbasis3 pdw)
  {
  printf ("%14.9Lf %14.9Lf %14.9Lf\n", pdw.x.x, pdw.y.x, pdw.z.x);
  printf ("%14.9Lf %14.9Lf %14.9Lf\n", pdw.x.y, pdw.y.y, pdw.z.y);
  printf ("%14.9Lf %14.9Lf %14.9Lf\n", pdw.x.z, pdw.y.z, pdw.z.z);
  printf ("\n");
  }

void eulerwinkelausgabe (cvektor3 p1)
  {
  printf ("%8.2Lf° nach rechts drehen\n", p1.x/M_PIl*180);
  printf ("%8.2Lf° nach oben neigen\n", p1.y/M_PIl*180);
  printf ("%8.2Lf° nach rechts kippen\n", p1.z/M_PIl*180);
  printf ("\n");
  }

void berechneantennendaten ()
  {
  // Eingabe der Daten
  integer scanret;
  printf ("\n");
  real satposl;
  printf ("Satellit Längengrad  [°Ost]:       ");
  scanret= scanf ("%Lf", &satposl);
  scanret++;                  // so jetzt ist die Variable benutzt und der Compiler meckert nicht mehr, dass sie nicht benutzt wird
  satposl*= M_PIl/180;

  printf ("\n");
  real antposb;
  printf ("Antenne Breitengrad  [°Nord]:      ");
  scanret= scanf ("%Lf", &antposb);
  scanret++;
  antposb*= M_PIl/180;

  real antposl;
  printf ("Antenne Längengrad   [°Ost]:       ");
  scanret= scanf ("%Lf", &antposl);
  scanret++;
  antposl*= M_PIl/180;

  real antposh;
  printf ("Antenne Höhe über NN [m]:          ");
  scanret= scanf ("%Lf", &antposh);
  scanret++;

  printf ("\n");

  // Satellitenradius nach Keplerschen Gesetzen berechnen
  real radiuse= 6373000;  // Geoidnäherung des Erdradiusses
  real umlauft= 86400;   // Satellitenumlaufzeit 1 Tag
  real fallbeschl= 9.76044972; // Fallbeschleunigung
  real satradius= powl (fallbeschl*radiuse*radiuse*powl (umlauft/(2*M_PIl), 2), 1/3.);

  // Satellitenradius nach festen Werten vorgeben
  satradius= 42410000;  // Flughöhe beste Annäherung an Satlex, Satbeams
  satradius= 42164000;  // Äquatorradius: 6378 km, Flughöhe über Äquator: 35786 km nach Wikipedia Angaben

  printf ("Entfernung des Satelliten vom Erdmittelpunkt:\n");
  zahlausgabe (satradius);

  // Erdradius nach WGS84 Referenzellipsoid berechnen
  real halba= 6378137;
  real halbb= 6356752;

  real platt= halbb/halba;
  real sinantposb= sinl (antposb);
  real cosantposb= cosl (antposb);
  real elipxq= halbb*halbb*cosantposb*cosantposb/(sinantposb*sinantposb + platt*platt*cosantposb*cosantposb);
  real elipyq= platt*platt*(halba*halba - elipxq);
  radiuse= sqrtl (elipxq + elipyq);

  // Antennenhöhe addieren
  radiuse+= antposh;
  printf ("Entfernung der Antenne vom Erdmittelpunkt:\n");
  zahlausgabe (radiuse);

  // Satellitenposition berechnen
  cvektor3 satpos (cosl (satposl)*satradius, sinl (satposl)*satradius, 0);
  printf ("Satellitenposition:\n");
  vektorausgabe (satpos);

  // Antennenposition berechnen
  cvektor3 antpos (cosl (antposl)*cosl (antposb), sinl (antposl)*cosl (antposb), sinl (antposb));
  antpos= radiuse*antpos;
  printf ("Antennenposition:\n");
  vektorausgabe (antpos);

  // Standpunktkoordinatensystem berechnen
  cvektor3 standy (normiere (antpos));
  cvektor3 standz (cosl (antposl)*sinl (-antposb), sinl (antposl)*sinl (-antposb), cosl (antposb));
  cvektor3 standx (standz^standy);
  cbasis3 standbas (standx, standy, standz);
  printf ("Standpunktkoordinatensystem:\n");
  matrixausgabe (standbas);
  printf ("Determinante: %16.14Lf\n", det (standbas));
  printf ("\n");

  // Antennenausrichtungskoordinatensystem berechnen
  cvektor3 antausz (normiere (satpos - antpos));
  cvektor3 zachse (0, 0, 1);
  cvektor3 antausx (normiere (antausz^zachse));
  cvektor3 antausy (antausx^antausz);
  cbasis3 antausbas (antausx, antausy, antausz);
  printf ("Antennenausrichtungskoordinatensystem:\n");
  matrixausgabe (antausbas);
  printf ("Determinante: %16.14Lf\n", det (antausbas));
  printf ("\n");

  // Antennendrehmatrix berechnen
  cbasis3 antdrehung (antausbas/standbas);
  printf ("Antennendrehmatrix:\n");
  matrixausgabe (antdrehung);
  printf ("Determinante: %16.14Lf\n", det (antdrehung));
  printf ("\n");

  // Eulerwinkel aus der Antennendrehmatrix berechnen
  cvektor3 eulerdrehwinkel (eulerwinkelfrommatrix (antdrehung));
  if (cosl (antposb) > 0)
    printf ("Die Antenne zeigt vor der Ausrichtung nach Norden.\n");
    else
    printf ("Die Antenne zeigt vor der Ausrichtung nach Süden.\n");
  printf ("\n");
  printf ("Ausrichtung der Antenne:\n");
  printf ("\n");
  eulerwinkelausgabe (eulerdrehwinkel);

  // Umrechnung der Eulerwinkel in Standard Angaben (Azimut, Elevation, Tilt)
  real satent= abs (satpos - antpos)/1000;
  real azimut= eulerdrehwinkel.x*180/M_PIl;
  if (azimut < 0)
    azimut= azimut + 360;
  real elev= eulerdrehwinkel.y*180/M_PIl;
  real tilt= eulerdrehwinkel.z*180/M_PIl;
  if (tilt < -90)
    tilt= tilt + 180;
  if (tilt > 90)
    tilt= tilt - 180;
  printf ("Konvertierung in Standardsatelliteneinheiten:\n");
  printf ("\n");
  printf ("  Satellitenentfernung:   %8.2Lf km\n", satent);
  printf ("  Azimut:                 %8.2Lf° \n", azimut);
  printf ("  Elevation:              %8.2Lf° \n", elev);
  printf ("  LNB Tilt:               %8.2Lf° \n", tilt);
  printf ("\n");

  // Hausstandpunkt berechnen
  printf ("Hausstandpunkt:\n");
  cvektor2 fli, fre;
  real wi, fl;
  fl= 199/tanl (eulerdrehwinkel.y);
  printf ("  fl:                     %8.2Lf  \n", fl);

  wi= 207.9 - azimut;
  printf ("  Bodenwinkel nach links: %8.2Lf° \n", wi);
  wi= wi*M_PIl/180;

  fli.x= 114 - fl*sinl (wi);
  fli.y=       fl*cosl (wi) - 15;
  fre.x= 222 - fl*sinl (wi);
  fre.y=       fl*cosl (wi) - 15;

  printf ("  Fenster links:      %8.2Lf  %8.2Lf\n", fre.x, fre.y);
  printf ("  Fenster rechts:     %8.2Lf  %8.2Lf\n", fli.x, fli.y);
  }

int main ()
  {
  berechneantennendaten ();
  return 0;
  }
