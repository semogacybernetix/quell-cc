// Dieses Programm testet Heptanionen

#include "single.h"
#include "../class/vektor.h"

#include <cstdio>
#include <cstdlib>

integer lmax (1000);

//---------------------------------- Ausgabe ----------------------------------------------------
void printvektor3 (cvektor3 pv)
  {
  FILE* datei= fopen ("quaternionenoutput.txt", "ab");
          printf ("%12.9Lf %12.9Lf %12.9Lf\n", pv.x, pv.y, pv.z);
  fprintf (datei, "%12.9Lf %12.9Lf %12.9Lf\n", pv.x, pv.y, pv.z);
  fclose (datei);
  }

void printbasis3 (cbasis3 pb, integer pord)
  {
  FILE* datei= fopen ("quaternionenoutput.txt", "ab");
          printf ("        %12.9Lf %12.9Lf %12.9Lf        %12.9Lf %12.9Lf %12.9Lf        %12.9Lf %12.9Lf %12.9Lf        %12.9Lf    %6ld\n", pb.x.x, pb.x.y, pb.x.z, pb.y.x, pb.y.y, pb.y.z, pb.z.x, pb.z.y, pb.z.z, det (pb), pord);
  fprintf (datei, "        %12.9Lf %12.9Lf %12.9Lf        %12.9Lf %12.9Lf %12.9Lf        %12.9Lf %12.9Lf %15.9Lf        %12.9Lf    %6ld\n", pb.x.x, pb.x.y, pb.x.z, pb.y.x, pb.y.y, pb.y.z, pb.z.x, pb.z.y, pb.z.z, det (pb), pord);
  fclose (datei);
  }

void printvektor4 (cvektor4 pv, integer pord)
  {
  FILE* datei= fopen ("quaternionenoutput.txt", "ab");
  cvektor4 aw= achsewinkelfromquaternion (pv);
  real wi= aw.r*180/M_PI;
          printf ("%24.9Lf %18.9Lf %18.9Lf %18.9Lf            %14.9Lf %14.9Lf %14.9Lf %10.3Lf     %14.9Lf  %6ld\n", pv.r, pv.i, pv.j, pv.ij, aw.i, aw.j, aw.ij, wi, abs (pv), pord);
  fprintf (datei, "%24.9Lf %18.9Lf %18.9Lf %18.9Lf            %14.9Lf %14.9Lf %14.9Lf %10.3Lf     %14.9Lf  %6ld\n", pv.r, pv.i, pv.j, pv.ij, aw.i, aw.j, aw.ij, wi, abs (pv), pord);
  fclose (datei);
  }

void printvektor7 (cvektor7 pv, integer pord)
  {
  FILE* datei= fopen ("heptanionenoutput.txt", "ab");
//  cvektor4 aw= achsewinkelfromquaternion (pv);
//  real wi= aw.r*180/M_PI;
          printf ("%24.9Lf %18.9Lf %18.9Lf %18.9Lf %18.9Lf %18.9Lf %18.9Lf\n", pv.r, pv.i, pv.j, pv.ij, pv.ji, pv.iji, pv.jij);
  fprintf (datei, "%24.9Lf %18.9Lf %18.9Lf %18.9Lf %18.9Lf %18.9Lf %18.9Lf\n", pv.r, pv.i, pv.j, pv.ij, pv.ji, pv.iji, pv.jij);
  fclose (datei);
  }

void printv3liste (cvektor3liste& pvliste)
  {
  FILE* datei= fopen ("quaternionenoutput.txt", "ab");
  for (integer lauf= 0; lauf < pvliste.anz; lauf++)
    printvektor3 (pvliste.v[lauf]);
          printf ("\nVektor Liste: %10ld Elemente", pvliste.anz);
  fprintf (datei, "\nVektor Liste: %10ld Elemente", pvliste.anz);
  if (pvliste.uebergelaufen)
    {
            printf ("    übergelaufen");
    fprintf (datei, "    übergelaufen");
    }
          printf ("\n\n");
  fprintf (datei, "\n\n");
  fclose (datei);
  }

void printb3liste (cbasis3liste& pbliste)
  {
  FILE* datei= fopen ("quaternionenoutput.txt", "ab");
  for (integer lauf= 0; lauf < pbliste.anz; lauf++)
    printbasis3 (pbliste.b[lauf], pbliste.ord[lauf]);
  printf ("\nMatrix Liste: %10ld Elemente", pbliste.anz);
  fprintf (datei, "\nMatrix Liste: %10ld Elemente", pbliste.anz);
  if (pbliste.uebergelaufen)
    {
    printf ("    übergelaufen");
    fprintf (datei, "    übergelaufen");
    }
  printf ("\n\n");
  fprintf (datei, "\n\n");
  for (integer lauf= 0; lauf < pbliste.anz + 1; lauf++)
    if (pbliste.ordanz[lauf] > 0)
      {
      printf ("%5ld %5ld\n", pbliste.ordanz[lauf], lauf);
      fprintf (datei, "%5ld %5ld\n", pbliste.ordanz[lauf], lauf);
      }
  printf ("\n\n");
  fprintf (datei, "\n\n");
  fclose (datei);
  }

void printv4liste (cvektor4liste& pqliste)
  {
  FILE* datei= fopen ("quaternionenoutput.txt", "ab");
  for (integer lauf= 0; lauf < pqliste.anz; lauf++)
    printvektor4 (pqliste.v[lauf], pqliste.ord[lauf]);
  printf ("\nQuaternionen Liste: %10ld Elemente", pqliste.anz);
  fprintf (datei, "\nQuaternionen Liste: %10ld Elemente", pqliste.anz);
  if (pqliste.uebergelaufen)
    {
    printf ("    übergelaufen");
    fprintf (datei, "    übergelaufen");
    }
  printf ("\n\n");
  fprintf (datei, "\n\n");
  for (integer lauf= 0; lauf < pqliste.anz + 1; lauf++)
    if (pqliste.ordanz[lauf] > 0)
      {
      printf ("%5ld %5ld\n", pqliste.ordanz[lauf], lauf);
      fprintf (datei, "%5ld %5ld\n", pqliste.ordanz[lauf], lauf);
      }
  printf ("\n\n");
  fprintf (datei, "\n\n");
  fclose (datei);
  }

void zeigepotenzen (cvektor4 pv)
  {
  FILE* datei= fopen ("quaternionenoutput.txt", "ab");
  cvektor4 qpot (1, 0, 0, 0);
  for (integer nlauf= 0; nlauf < 25; nlauf++)
    {
    printf ("p=%5ld", nlauf);
    fprintf (datei, "p=%5ld", nlauf);
    printvektor4 (qpot, 0);
    qpot= qpot*pv;
    }
  printf ("\n");
  fprintf (datei, "\n");
  fclose (datei);
  }

void zeigedrehungen (cvektor3 pv, cvektor3 pdv, long double pwi)
  {
  FILE* datei= fopen ("quaternionenoutput.txt", "ab");
  pdv= normiere (pdv);
  pwi= pwi*M_PI/180;
  pwi= pwi/2;
  cvektor4 gedv (0, pv.x, pv.y, pv.z);
  cvektor4 qdreh (cos (pwi), pdv.x*sin (pwi), pdv.y*sin (pwi), pdv.z*sin (pwi));
  printvektor4 (qdreh, 0);
  printf ("---------------------------------------------------------------------------------------------------\n");
  fprintf (datei, "---------------------------------------------------------------------------------------------------\n");
  for (integer nlauf= 0; nlauf < 25; nlauf++)
    {
    printvektor4 (gedv, 0);
    gedv= qdreh*gedv*~qdreh;
    }
  printf ("\n");
  fprintf (datei, "\n");
  fclose (datei);
  }

//---------------------------------- Objekte ---------------------------------------------------------------------
//---------------------------------- Hilfsfunktionen ------------------------------------------------------------

integer scanret;
// 1.618033988749894848204586834365638117720309179 
// 0.6180339887498948482045868343656
// 0.3090169943749474241022934171828

void zeigekonstanten ()
  {
  printf ("\n");
  long double gschnitt= sqrt(1.25) - 1.1;
  printf ("%30.26Le\n", gschnitt);
  long double gschnitt2= sqrt(0.3125) - 0.55;
  printf ("%30.26Le\n", gschnitt2);
  long double gschnitt3= cos(M_PI*36/180);
  printf ("%30.26Le\n\n", gschnitt3);
  printf ("\n");
  }

void vektoreingabe (cvektor3& pv)
  {
  printf ("\n");
  printf ("x:  ");
  scanret= scanf ("%Lf", &pv.x);
  printf ("y:  ");
  scanret= scanf ("%Lf", &pv.y);
  printf ("z:  ");
  scanret= scanf ("%Lf", &pv.z);
  printf ("\n");
  }

void quaternioneneingabe (cvektor4& pv)
  {
  printf ("\n");
  printf ("r:  ");
  scanret= scanf ("%Lf", &pv.r);
  printf ("i:  ");
  scanret= scanf ("%Lf", &pv.i);
  printf ("j:  ");
  scanret= scanf ("%Lf", &pv.j);
  printf ("ij  ");
  scanret= scanf ("%Lf", &pv.ij);
  printf ("\n");
  }

void heptanioneneingabe (cvektor7& pv)
  {
  printf ("\n");
  printf ("r:  ");
  scanret= scanf ("%Lf", &pv.r);
  printf ("i:  ");
  scanret= scanf ("%Lf", &pv.i);
  printf ("j:  ");
  scanret= scanf ("%Lf", &pv.j);
  printf ("ij  ");
  scanret= scanf ("%Lf", &pv.ij);
  printf ("ji  ");
  scanret= scanf ("%Lf", &pv.ji);
  printf ("iji  ");
  scanret= scanf ("%Lf", &pv.iji);
  printf ("jij  ");
  scanret= scanf ("%Lf", &pv.jij);
  printf ("\n");
  }

//-------------------------- Menüpunkte  --------------------------------------------------------------------------------------------

void quatmul ()
  {
  cvektor4 quat= cvektor4 (1, 0, 0, 0);
  cvektor4 qein= quat;
  while (1)
    {
    quaternioneneingabe (qein);
    quat= qein*quat;
    printvektor4 (quat, 0);
    }
  }

void heptmul ()
  {
  cvektor7 hept= cvektor7 (1, 0, 0, 0, 0, 0, 0);
  cvektor7 hein= hept;
  while (1)
    {
    heptanioneneingabe (hein);
    hept= hein*hept;
    printvektor7 (hept, 0);
    }
  }

void testedivision ()
  {
  cvektor4 quata, quatb, quatc, qeins, quatl, quatr, quataz, quatbz;
  quaternioneneingabe (quata);
  quaternioneneingabe (quatb);

  qeins= cvektor4 (1, 0, 0, 0);
  quatl=qeins/quata;
  quatr=qeins|quata;
  quatc= quatb*quata;
  quataz= quatc/quatb;
  quatbz= quatc|quata;

  printf ("Linksinverses von Q1:\n");
  printvektor4 (quatl, 0);
  printf ("Rechtsinverses von Q1:\n");
  printvektor4 (quatr, 0);
  printf ("c:\n");
  printvektor4 (quatc, 0);
  printf ("az:\n");
  printvektor4 (quataz, 0);
  printf ("bz:\n");
  printvektor4 (quatbz, 0);
  }

void testegoldenematrix ()
  {
  cvektor4 v1, v2, v3, v4, ein1, ass1, ass2, ass3;
  long double r1= .25*(sqrt(5) + 1);
  long double i1= .25*(sqrt(10 - 2*sqrt(5)));
  long double r2= .25*(sqrt(5) - 1);
  long double i2= .25*(sqrt(10 + 2*sqrt(5)));
  long double d3= sqrt(3)/2;
  v1= cvektor4 (r1, i1, 0, 0);
  v2= cvektor4 (r2, i2, 0, 0);
  v3= cvektor4 (r1, -i1, 0, 0);
  v4= cvektor4 (r2, -i2, 0, 0);

  v1= cvektor4 (i1, r1, 0, 0);
  v2= cvektor4 (i2, r2, 0, 0);
  v3= cvektor4 (i1, -r1, 0, 0);
  v4= cvektor4 (i2, -r2, 0, 0);

  v1= cvektor4 (d3, -.5, 0, 0);
  v2= cvektor4 (-d3, -.5, 0, 0);
  v3= cvektor4 (d3,.5, 0, 0);
  v4= cvektor4 (-d3,.5, 0, 0);
  }

//--------------------------------------- Testedrehungen mit Schrittweite ---------------------

void testedrehungen ()
  {
  integer sanz, danz;
  cvektor4 lage (1, 0, 0, 0);
  cvektor4 qdreh, awein;
  FILE* datei;

  while (1)
    {
    awein= achsewinkeleingabe ();
    printf ("\n");
    printf ("Schritte:  ");
    scanret= scanf ("%ld", &sanz);
    printf ("Anzahl Drehungen:  ");
    scanret= scanf ("%ld", &danz);
    awein.r/= sanz;
    qdreh= quaternionfromachsewinkel (awein);
    datei= fopen ("quaternionenoutput.txt", "ab");
    printf ("\nDrehquaternion:\n");
    fprintf (datei, "\nDrehquaternion:\n");
    fclose (datei);
    printvektor4 (qdreh, 0);
    datei= fopen ("quaternionenoutput.txt", "ab");
    printf ("\nDrehungen:\n");
    fprintf (datei, "\nDrehungen:\n");
    fclose (datei);
    for (integer laufd= 0; laufd < danz; laufd++)
      for (integer laufs= 0; laufs < sanz; laufs++)
        {
        lage= qdreh*lage;
        printvektor4 (lage, 0);
        }
    }
  }

//--------------------------------------  1 Drehungen ---------------------------------

void dreh1spieg0 ()
  {
  cvektor4 elneu;
  cvektor4liste qliste (lmax);
  cbasis3liste bliste (lmax);
  cvektor3liste vliste (lmax);

  elneu= achsewinkeleingabe ();
  elneu= quaternionfromachsewinkel (elneu);
  qliste.elementhinzu (elneu);
  bliste.elementhinzu (elneu);
  qliste.schliesseab ();
  bliste.schliesseab ();

  printv4liste (qliste);
  printb3liste (bliste);

  vliste.elementhinzu (cvektor3 (1, 0, 0));
  vliste.schliesseab (bliste);
  printv3liste (vliste);
  }

//-------------------------------------- 2 Drehungen 0 Spiegelungen ---------------------------------

void dreh2spieg0 ()
  {
  cvektor4 el1, el2;
  cvektor4liste qliste (lmax);
  cbasis3liste bliste (lmax);
  cvektor3liste vliste (lmax);

  el1= achsewinkeleingabe ();
  el2= achsewinkeleingabe ();
  el1= quaternionfromachsewinkel (el1);
  el2= quaternionfromachsewinkel (el2);
  qliste.elementhinzu (el1);
  qliste.elementhinzu (el2);
  bliste.elementhinzu (el1);
  bliste.elementhinzu (el2);
  qliste.schliesseab ();
  bliste.schliesseab ();
  qliste.ermittleordnung ();
  bliste.ermittleordnung ();

  printv4liste (qliste);
  printb3liste (bliste);

//  vliste.elementhinzu (cvektor3 (1, 0.61803398874989, 0));                // V12 Ikosaeder
//  vliste.elementhinzu (cvektor3 (1, 2.61803398874989, 0));                // V20 Dodekaeder
//  vliste.elementhinzu (cvektor3 (1, 1.61803398874989, 0.61803398874989)); // V30 Ikosaeder, Dodekaeder
//  vliste.elementhinzu (cvektor3 (1, 1, 1));                               // V20 Dodekaeder klein
  vliste.elementhinzu (cvektor3 (0, 1, 0));                               // V30 Ikosaeder, Dodekaeder klein
  vliste.schliesseab (bliste);
  printv3liste (vliste);
  }

//-------------------------------------- 2 Drehungen 1 Spiegelung ---------------------------------

void dreh2spieg1 ()
  {
  cvektor4 el1, el2;
  cvektor4liste qliste (lmax);
  cbasis3liste bliste (lmax);
  cvektor3liste vliste (lmax);
  cvektor3 spiegachse;

  el1= achsewinkeleingabe ();
  el2= achsewinkeleingabe ();
  vektoreingabe (spiegachse);

  cbasis3 psp (getspieg (spiegachse));
  el1= quaternionfromachsewinkel (el1);
  el2= quaternionfromachsewinkel (el2);
  qliste.elementhinzu (el1);
  qliste.elementhinzu (el2);
  bliste.elementhinzu (el1);
  bliste.elementhinzu (el2);
  bliste.elementhinzu (psp);
  qliste.schliesseab ();
  bliste.schliesseab ();
  qliste.ermittleordnung ();
  bliste.ermittleordnung ();

  printv4liste (qliste);
  printb3liste (bliste);

  vliste.elementhinzu (spiegachse);
  vliste.schliesseab (bliste);
  printv3liste (vliste);
  }

//-------------------------------------- 2 Drehungen 2 Spiegelungen ---------------------------------

void dreh2spieg2 ()
  {
  cvektor4 el1, el2;
  cvektor4liste qliste (lmax);
  cbasis3liste bliste (lmax);
  cvektor3liste vliste (lmax);
  cvektor3 spiegachse;
  cvektor3 spiegachse2;

  el1= achsewinkeleingabe ();
  el2= achsewinkeleingabe ();
  vektoreingabe (spiegachse);
  vektoreingabe (spiegachse2);

  cbasis3 psp (getspieg (spiegachse));
  cbasis3 psp2 (getspieg (spiegachse2));
  el1= quaternionfromachsewinkel (el1);
  el2= quaternionfromachsewinkel (el2);
  qliste.elementhinzu (el1);
  qliste.elementhinzu (el2);
  bliste.elementhinzu (el1);
  bliste.elementhinzu (el2);
  bliste.elementhinzu (psp);
  bliste.elementhinzu (psp2);
  qliste.schliesseab ();
  bliste.schliesseab ();
  qliste.ermittleordnung ();
  bliste.ermittleordnung ();

  printv4liste (qliste);
  printb3liste (bliste);

  vliste.elementhinzu (spiegachse);
  vliste.elementhinzu (spiegachse2);
  vliste.schliesseab (bliste);
  printv3liste (vliste);
  }

//-------------------------------------- 0 Drehungen 3 Spiegelungen ---------------------------------

void dreh0spieg3 ()
  {
  cvektor4 el1, el2;
  cbasis3liste bliste (lmax);
  cvektor3liste vliste (lmax);
  cvektor3 spiegachse;
  cvektor3 spiegachse2;
  cvektor3 spiegachse3;

//  el1= achsewinkeleingabe ();
//  el2= achsewinkeleingabe ();
  vektoreingabe (spiegachse);
  vektoreingabe (spiegachse2);
  vektoreingabe (spiegachse3);

  cbasis3 psp (getspieg (spiegachse));
  cbasis3 psp2 (getspieg (spiegachse2));
  cbasis3 psp3 (getspieg (spiegachse3));
//  el1= quaternionfromachsewinkel (el1);
//  el2= quaternionfromachsewinkel (el2);
//  qliste.elementhinzu (el1);
//  qliste.elementhinzu (el2);
//  bliste.elementhinzu (el1);
//  bliste.elementhinzu (el2);
  bliste.elementhinzu (psp);
  bliste.elementhinzu (psp2);
  bliste.elementhinzu (psp3);
//  qliste.schliesseab ();
  bliste.schliesseab ();
  bliste.ermittleordnung ();

//  printv4liste (qliste);
  printb3liste (bliste);

  vliste.elementhinzu (spiegachse);
  vliste.elementhinzu (spiegachse2);
  vliste.elementhinzu (spiegachse3);
  vliste.schliesseab (bliste);
  printv3liste (vliste);
  }

//-------------------------------------- Testematrix ------------------------------------------------------

void testematrix ()
  {
  cbasis3liste bliste (lmax);
  cvektor3liste vliste (lmax);
  cvektor3 spiegachse;
  real C5 (0.5);
  real C3 (0.309016994374947);
  real C8 (0.809016994374947);

  cbasis3 drehspieg
    (
    cvektor3 (-C5, -C3, -C8),
    cvektor3 (-C3, -C8, C5),
    cvektor3 (C8, -C5, -C3)
    );

  bliste.elementhinzu (drehspieg);
  bliste.schliesseab ();

  printb3liste (bliste);

  return;
  vliste.elementhinzu (spiegachse);
  vliste.schliesseab (bliste);
  printv3liste (vliste);
  }

void  testespiegelung ()
  {
  cvektor3 spiegachse;
  vektoreingabe (spiegachse);
  cbasis3 bspieg (getspieg (spiegachse));
  cvektor3 gspieg= bspieg*spiegachse;
  printvektor3 (spiegachse);
  printf ("\n");
  printbasis3 (bspieg, 0);
  printf ("\n");
  printvektor3 (gspieg);
  printf ("\n");
  printf ("Determinante: %12Lf\n", det (bspieg));
  printf ("\n");
  printf ("Metrik:\n");
  cbasis3 bmetrik (cvektor3 (bspieg.x%bspieg.x, bspieg.x%bspieg.y, bspieg.x%bspieg.z), cvektor3 (bspieg.y%bspieg.x, bspieg.y%bspieg.y, bspieg.y%bspieg.z), cvektor3 (bspieg.z%bspieg.x, bspieg.z%bspieg.y, bspieg.z%bspieg.z));
  printbasis3 (bmetrik, 0);
  cbasis3 quad (bspieg*bspieg);
  printf ("\n");
  printf ("Quadrat der Spiegelungsmatrix:\n");
  printf ("\n");
  printbasis3 (quad, 0);
  printf ("\n");
  }

integer entscheidungseingabe ()
  {
  integer ent;
  printf ("\n");
  printf ("[1] Drehungen  [2] Quaternionenmultiplikation  [3] Division  [4] Heptanionenmultiplikation  [5] Testematrix      [6] 2 Dreh 0 Spieg   [7] 2 Dreh 1 Spieg   [8] 2 Dreh 2 Spieg   [9] 3 Spieg    ");
  scanret= scanf ("%ld", &ent);
  return ent;
  }

//--------------------- Hauptprogramm ----------------------------------------------
int main ()
  {
  integer ent (entscheidungseingabe ());
  switch (ent)
    {
    case 1:
      testedrehungen ();
      break;
    case 2:
      quatmul ();
      break;
    case 3:
      testedivision ();
      break;
    case 4:
      heptmul ();
      break;
    case 5:
      testematrix ();
      break;
    case 6:
      dreh2spieg0 ();
      break;
    case 7:
      dreh2spieg1 ();
      break;
    case 8:
      dreh2spieg2 ();
      break;
    case 9:
      dreh0spieg3 ();
      break;
    }
  return 0;
  }
