/*

die Bandbreite einer Datenleitung soll möglichst fair zwischen mehreren Nutzern aufgeteilt werden

Feststellungen:
Die Datenleitung hat eine festgelegte Bandbreite B.
Jeder Nutzer stellt einen Anspruch, wieviel Bandbreite er haben möchte.
Gibt es Nutzer mit geringerer Bandbreite als jemand anderes, können diese ihre Bandbreite erhöhen, um die Differenz zu jemandem mit höherer Bandbreite zu verringern.

Die Bandbreitenregelung stellt jedem Nutzer eine bestimmte Bandbreite zur Verfügung. Sobald ein Nutzer seinen Anspruch ändert, wird die Bandbreitenzuteilung neu berechnet und die Bandbreite entsprechend zugeteilt.

Algorithmus:
1. Liegt der kleinste Bandbreitenanspruch nicht unter dem gerechten Anteil (Bandbreite/Benutzer), wird die Bandbreite gerecht verteilt.
2. Liegt der kleinste Bandbreitenanspruch unter dem gerechten Anteil (B

Die Bandbreite wird nach einem rekursiven Algorithmus aufgeteilt

Algorithmus A: Aufteilung einer Bandbreite B auf n Teilnehmer:
1. Wenn alle Teilnehmer mindestens ihren gerechten Anteil (B/n) fordern, wird die Bandbreite gerecht verteilt (Jeder bekommt den gerechten Anteil Bandbreite zugeteilt). (Abbruchbedingung)
2. Ist die Bandbreitenforderung eines Teilnehmers k geringer als sein gerechter Anteil, bekommt er seine geforderte Bandbreite Bk zugeteilt und die übrige Bandbreite (B - Bk) wird auf die übrigen Teilnehmer (n-1) nach Algorithmus A verteilt.

*/
#include "../class/vektor.h"
#include "../class/gruppe.h"
#include "../../conio/vektorcon.h"
#include "../../conio/gruppecon.h"

#include <iostream>          // cout, FILE, printf, scanf
#include <cstdio>

integer scanret;

cvektor4 berechnebandbreite (cvektor4 anspruch)
  {
  real bandbreite, median;
  
  bandbreite= 100;
  median= bandbreite/4;
  if (anspruch.r >= median)
    return cvektor4 (median, median, median, median);
  bandbreite= bandbreite - anspruch.r;
  median= bandbreite/3;
  if (anspruch.i >= median)
    return cvektor4 (anspruch.r, median, median, median);
  bandbreite= bandbreite - anspruch.i;
  median= bandbreite/2;
  if (anspruch.j >= median)
    return cvektor4 (anspruch.r, anspruch.i, median, median);
  bandbreite= bandbreite - anspruch.j;
  median= bandbreite;
  if (anspruch.ij >= median)
    return cvektor4 (anspruch.r, anspruch.i, anspruch.j, median);
  return cvektor4 (anspruch.r, anspruch.i, anspruch.j, anspruch.ij);
  }

void zahlausgabe (real pzahl)
  {
  printf ("%50.2Lf\n", pzahl);
  }

void vektor4ausgabe (cvektor4 p1)
  {
  printf ("%50.2Lf\n", p1.r);
  printf ("%50.2Lf\n", p1.i);
  printf ("%50.2Lf\n", p1.j);
  printf ("%50.2Lf\n", p1.ij);
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


integer entscheidungseingabe ()
  {
  integer ent;
  printf ("\n");
  printf ("[1] Drehungen  [2] Drehmultiplikation  [3] Division  [4] Testespiegelung  [5] Testematrix  [6] 2 Drehspiegelungen [7] 3 Drehspiegelungen [8] Dreh -> Spieg  [9] Spieg -> Dreh  [10] 3 Spiegelebenenwinkel  [11] 3 gleiche Spiegelebenenwinkel\n");
  printf ("[12]  2 Drehungen + Koordinatendrehung   [13] Ebenenwinkel -> Spiegelachsenwinkel   [14] 3 Drehebenenwinkel   [15] 3 Ebenespieg -> Dreh    [16] Testespiegelebenen     [17] Testeqv      ");
  scanret= scanf ("%lld", &ent);
  return ent;
  }

int main ()
  {
  cvektor4 anspruch, zuteilung;
  quaternioneneingabe (anspruch);
  zuteilung= berechnebandbreite (anspruch);
  printvektor4quat (zuteilung, 0, 0);
  return 0;
  }
