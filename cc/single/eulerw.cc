/*
// dieses Programm berechnet aus einer Drehmatrix die Eulerwinkel und die Gesamtdrehachse
------------------------------------------------------------------------------------------------
Man ist folgendermaßen in das Koordinatensystem eingebettet:

x-Achse nach rechts
y-Achse nach oben
z-Achse nach vorn

Die Eulerwinkel sind Drehungen um die Achsen des eigenen Koordinatensystems in der angebebenen Reihenfolge

Längengrad:   Nase nach rechts bzw. rechtes Ohr nach hinten
Breitengrad:  Nase nach oben bzw. Fontanelle nach hinten
Neigung:      rechtes Ohr nach unten bzw. Fontanelle nach rechts
-------------------------------------------------------------------------------------------------

// Die Eulerwinkel entstehen aus den generischen Rotationsmatrizen:
// 1. Drehung um die x-Achse [-pi, pi]
// 2. Drehung um die y-Achse [-pi/2, pi/2]
// 3. Drehung um die z-Achse [-pi, pi]

ein Problem tritt auf, wenn die y-Drehung pi/2 oder -pi/2 ist. Dann fällt die z-Achse auf die x-Achse.
Das hat zur Folge, dass die 3.Drehung (um die z-Achse) sich direkt zur 1. Drehung (um die x-Achse)
addiert oder subtrahiert. Man kann also bei der Rückrechnung den 3. Eulerwinkel 0 setzen und dafür
den 1. Winkel entsprechend der Summe setzen.
*/

#include "../class/vektor.h"
#include "single.h"
#include <cstdlib>
#include <cstdio>

//------------------------- Hilfsfunktionen ----------------------------------------------------------

integer scanret;

signed long entscheidungseingabe ()
  {
  signed long ent;
  printf ("\n");
  printf ("[1] Flugwinkel eingeben        [2] Drehachse und Drehwinkel eingeben        [3] Mehrfachdrehung        [4] Konsistenzprüfung   ");
  scanret= scanf ("%ld", &ent);
  return ent;
  }

cvektor3 eulerwinkeleingabe ()
  {
  cvektor3 p1 (0, 0, 0);
  printf ("\nFlugwinkel\n");
  printf ("  Längengrad  [°]:  ");
  scanret= scanf ("%Lf", &p1.x);
  p1.x= p1.x/180*M_PI;
  printf ("  Breitengrad [°]:  ");
  scanret= scanf ("%Lf", &p1.y);
  p1.y= p1.y/180*M_PI;
  printf ("  Neigung     [°]:  ");
  scanret= scanf ("%Lf", &p1.z);
  p1.z= p1.z/180*M_PI;
  printf ("\n");
  return p1;
  }

void eulerwinkelausgabe (cvektor3 p1)
  {
  printf ("Flugwinkel:\n");
  printf ("%16.9Lf\n", p1.x/M_PI*180);
  printf ("%16.9Lf\n", p1.y/M_PI*180);
  printf ("%16.9Lf\n", p1.z/M_PI*180);
  printf ("\n");
  }

void zahlausgabe (long double pzahl)
  {
  printf ("%16.9Lf\n", pzahl);
  }

void achsewinkelausgabe (cvektor4 pdw)
  {
  cvektor4 dw1 (pdw);
  printf ("Drehachse und Drehwinkel:\n");
  printf ("%14.9Lf %16.9Lf\n", dw1.i, dw1.r/M_PI*180);
  printf ("%14.9Lf        \n", dw1.j);
  printf ("%14.9Lf        \n", dw1.ij);
  printf ("\n");
  }

void quaternionausgabe (cvektor4 pdw)
  {
  cvektor4 q1 (pdw);
  cvektor4 q2 (-pdw);
  printf ("Drehquaternion:\n");
  printf ("q = %12.9Lf    %12.9Lf i  %12.9Lf j  %12.9Lf ij    |q|= %12.9Lf\n", q1.r, q1.i, q1.j, q1.ij, norm (q1));
  //printf ("qi= %12.9Lf    %12.9Lf i  %12.9Lf j  %12.9Lf ij    |q|= %12.9Lf\n", q2.r, q2.i, q2.j, q2.ij, norm (q2));
  printf ("\n");
  }

void drehmatrixausgabe (cbasis3 pdw)
  {
  printf ("Drehmatrix:\n");
  printf ("%14.9Lf %14.9Lf %14.9Lf\n", pdw.x.x, pdw.y.x, pdw.z.x);
  printf ("%14.9Lf %14.9Lf %14.9Lf\n", pdw.x.y, pdw.y.y, pdw.z.y);
  printf ("%14.9Lf %14.9Lf %14.9Lf\n", pdw.x.z, pdw.y.z, pdw.z.z);
  printf ("\n");
  }

//----------------------------------------- Menüpunkt 1 -----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------

void eulerwinkel_nach_achsewinkel ()
  {
  // Input -> Eulerwinkel
  cvektor3 flugw (eulerwinkeleingabe ());

  //------------------------------- Ermittlung aller Darstellungen -------------------------------
  // Eulerwinkel -> Matrix
  cbasis3 drehmatrix (matrixfromeulerwinkel (flugw));
  // Eulerwinkel -> Quaternion
  cvektor4 drehq (quaternionfromeulerwinkel (flugw));
  // Qaternion -> Achsewinkel
  cvektor4 drehachse (achsewinkelfromquaternion (drehq));

//--------------------------------- Konsistenzprüfung -------------------------------------------

  eulerwinkelausgabe (flugw);
  drehmatrixausgabe (drehmatrix);
  quaternionausgabe (drehq);
  achsewinkelausgabe (drehachse);
  }

//----------------------------------------- Menüpunkt 2 -----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------

void achsewinkel_nach_eulerwinkel ()
  {
  // Input -> Achsewinkel
  cvektor4 achsewinkelein (achsewinkeleingabe ());

  //------------------------------- Ermittlung aller Darstellungen -------------------------------
  // Achsewinkelein -> Quaternion
  cvektor4 drehquaternion (quaternionfromachsewinkel (achsewinkelein));
  // Quaternion -> Achsewinkel
  cvektor4 achsewinkelq (achsewinkelfromquaternion (drehquaternion));
  // Quaternion -> Matrix
  cbasis3 drehmatrix (matrixfromquaternion (drehquaternion));
  // Matrix -> Achsewinkel
  cvektor4 achsewinkelm (achsewinkelfromquaternion (quaternionfrommatrix (drehmatrix)));
  // Matrix -> Eulerwinkel
  cvektor3 dreheulerwinkel (eulerwinkelfrommatrix (drehmatrix));
  // Eulerwinkel -> Quaternion
  cvektor4 eulerquaternion (quaternionfromeulerwinkel (dreheulerwinkel));
  

//------------------------------- Konsistenzprüfung ------------------------------------------

  quaternionausgabe (drehquaternion);
  achsewinkelausgabe (achsewinkelq);
  drehmatrixausgabe (drehmatrix);
  achsewinkelausgabe (achsewinkelm);
  eulerwinkelausgabe (dreheulerwinkel);
  quaternionausgabe (eulerquaternion);
  }

//----------------------------------------- Menüpunkt 3 -----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------

void mehrfachdrehung ()
  {
  cvektor3 flugw1 (eulerwinkeleingabe ());
  cvektor3 flugw2 (eulerwinkeleingabe ());
  cbasis3 db1 (matrixfromeulerwinkel (flugw1));
  cbasis3 db2 (matrixfromeulerwinkel (flugw2));
  cbasis3 db3 (normiere (db1*db2));
  cvektor3 flugw31 (eulerwinkelfrommatrix (db3));
  cvektor4 quat1 (quaternionfromeulerwinkel (flugw1));
  cvektor4 quat2 (quaternionfromeulerwinkel (flugw2));
  cvektor3 flugw32 (eulerwinkelfrommatrix (matrixfromquaternion (quat1*quat2)));
  eulerwinkelausgabe (flugw31);
  eulerwinkelausgabe (flugw32);
  }

void konsistenzpruefung (cvektor4 pachsewinkel, cvektor4 pquaternion, cbasis3 pmatrix, cvektor3 peulerwinkel)
  {
  }

void testeachsewinkelquaternion ()
  {
  cvektor4 rquat;
  cvektor4 rachsewinkel;
  cvektor4 rqzurueck;
  cbasis3 rmatrix;
  cvektor3 achse;
  cvektor4 achsewinkel;
  long double nor;
  cvektor4 quot;
  for (signed long lauf= 0; lauf < 100; lauf++)
    {
    rquat.r= -.5 + drand48 ();
    rquat.i= -.5 + drand48 ();
    rquat.j= -.5 + drand48 ();
    rquat.ij= -.5 + drand48 ();
    rquat= normiere (rquat);

    achse.x= -.5 + drand48 ();
    achse.y= -.5 + drand48 ();
    achse.z= -.5 + drand48 ();
    achse= normiere (achse);
   // rquat= cvektor4 (0, achse.x, achse.y, achse.z);
 //   quaternionausgabe (rquat);
    rmatrix= matrixfromquaternion (rquat);
//    drehmatrixausgabe (rmatrix);
    rqzurueck= quaternionfrommatrix (rmatrix);
      // achsewinkelfromquaternion (quaternionfrommatrix (rmatrix));
 //   quaternionausgabe (rqzurueck);
    if (rquat.r < 0)
      {
      rquat= -rquat;
      printf(" ");
      }
    nor= norm (rquat -rqzurueck);
    zahlausgabe (nor);
    //achsewinkelausgabe (achsewinkel);
    }
  }
  
//------------------------------------------------- Hauptprogramm ----------------------------------------------------------
int main ()
  {
  signed long ent (entscheidungseingabe ());
  switch (ent)
    {
    case 1:
      eulerwinkel_nach_achsewinkel ();
      break;
    case 2:
      achsewinkel_nach_eulerwinkel ();
      break;
    case 3:
      mehrfachdrehung ();
      break;
    case 4:
      testeachsewinkelquaternion ();
      break;
    }
  return 0;
  }
