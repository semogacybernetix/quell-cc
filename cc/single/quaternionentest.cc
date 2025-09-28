// Dieses Programm testet die Quaternionendrehungen

/*
2 Drehungen sind äquivalent zu 3 Spiegelungen

   0° Drehung:    Identitätsmatrix, Quaternion: 1
 180° Drehung:    Geradenspiegelung, Drehachse ist Spiegelungsachse, Quaternion: Realteil 0
 360° Drehung:    Identitätsmatrix, Quaternion: -1
-180° Drehung:    Ebenenspiegelung entlang der Drehachse (Drehachse ist Normale der Spiegelungsebene, Spiegelungsebene geht durch den Ursprung), Quaternion: 180° Drehung
-360° Drehung:    Punktspiegelung am Ursprung, Quaternion: -1

*/

#include "../../conio/vektorcon.h"
#include "../../conio/gruppecon.h"

#include <iostream>          // cout, FILE, printf, scanf

using namespace std;         // damit man cout schreiben kann statt std::cout schreiben zu müssen

integer lmax (1000);  // Anzahl von Elementen bei denen qliste, bliste und vliste voll ist.
integer scanret;      // Rückgabewert von scanf

//---------------------------------- Hilfsfunktionen ------------------------------------------------------------

// 0.6666666666666666666666666666666666-345678  128
// 1.6180339887498948482045868343656381-596970  128
// 0.6180339887498948482045868343656381-596970  128
// 0.8090169943749474241022934171828190-798485  128
// 0.3090169943749474241022934171828190-317003  128
// 3.141592653589793238462643383279502-7974791  128
// 1.8392867552141611325518525646532865-010030  128

// 1.61803398874989484820-72100296669248109538  80
// 1.839286755214161132-6051162667027938368847  80

// 2.618033988749894848204586834365638117720309179     (V5+3)/2
// 1.618033988749894848204586834365638117720309179     (V5+1)/2  2cos 36°
// 0.618033988749894848204586834365638117720309179     (V5-1)/2  2sin 18°

// 0.3090169943749474241022934171828                   (V5-1)/4   cos 72°  sin 18°
// 0.5                                                      2/4   cos 60°  sin 30°
// 0.8090169943749474241022934171828                   (V5+1)/4   cos 36°  sin 54°

real kubischegleichung (real pa, real pb, real pc)
  {
  real redp, redq, disk, retz, retx;

  redp= pb - pa*pa/3;
  redq= 2*pa*pa*pa/27 - pa*pb/3 + pc;

  disk= redq*redq/4 + redp*redp*redp/27;
  
  retz= cbrtl (-redq/2 + sqrtl (disk)) + cbrtl (-redq/2 - sqrtl (disk));
  retx= retz - pa/3;
  return retx;
  }

void zeigekonstanten ()
  {
  printf ("\n");
  long double gschnitt= sqrtl(1.25) - 1.1;
  printf ("%30.26Le\n", gschnitt);
  long double gschnitt2= sqrtl(0.3125) - 0.55;
  printf ("%30.26Le\n", gschnitt2);
  long double gschnitt3= cosl(M_PIl*36/180);
  printf ("%30.26Le\n\n", gschnitt3);
  printf ("\n");
  }

void zeigepotenzen (cvektor4 pv)
  {
  FILE* datei= fopen ("quaternionenoutput.txt", "ab");
  cvektor4 qpot (1, 0, 0, 0);
  for (integer nlauf= 0; nlauf < 25; nlauf++)
    {
    printf ("p=%5lld", nlauf);
    fprintf (datei, "p=%5lld", nlauf);
    printvektor4dreh (qpot, 0, 0, 0);
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
  pwi= pwi*M_PIl/180;
  pwi= pwi/2;
  cvektor4 gedv (0, pv);
  cvektor4 qdreh (cosl (pwi), sinl (pwi)*pdv);
  printvektor4dreh (qdreh, 0, 0, 0);
  printf ("---------------------------------------------------------------------------------------------------\n");
  fprintf (datei, "---------------------------------------------------------------------------------------------------\n");
  for (integer nlauf= 0; nlauf < 25; nlauf++)
    {
    printvektor4dreh (gedv, 0, 0, 0);
    gedv= qdreh*gedv*~qdreh;
    }
  printf ("\n");
  fprintf (datei, "\n");
  fclose (datei);
  }

void zeigewinkel (const cbasis3& pdreibein)
  {
  cvektor3 pwi;
  pwi.x= winkelb (pdreibein.x, pdreibein.y);
  pwi.y= winkelb (pdreibein.x, pdreibein.z);
  pwi.z= winkelb (pdreibein.y, pdreibein.z);
  pwi.x*= 180/M_PIl;
  pwi.y*= 180/M_PIl;
  pwi.z*= 180/M_PIl;
  
  printtext ("Winkel zwischen den Achsen:\n");
  printvektor3ord (pwi, 0);
  real det3b= det (pdreibein);
  printtext ("Determinante:\n");
  printreal (det3b);
  }

void zeigedreibein (const cbasis3& pdreibein)
  {
  printf ("Spiegelachsen:\n");
  printvektor3ord (pdreibein.x, 0);
  printvektor3ord (pdreibein.y, 0);
  printvektor3ord (pdreibein.z, 0);
  printf ("\n");

  printf ("Winkel zwischen den Spiegelachsen:\n");
  cbasis3 dreibein= pdreibein;
  zeigewinkel (dreibein);
  dreibein.x= -dreibein.x;
  zeigewinkel (dreibein);
  dreibein.x= -dreibein.x;
  dreibein.y= -dreibein.y;
  zeigewinkel (dreibein);
  dreibein.x= -dreibein.x;
  zeigewinkel (dreibein);
  dreibein.x= -dreibein.x;
  dreibein.y= -dreibein.y;
  dreibein.z= -dreibein.z;
  zeigewinkel (dreibein);
  dreibein.x= -dreibein.x;
  zeigewinkel (dreibein);
  dreibein.x= -dreibein.x;
  dreibein.y= -dreibein.y;
  zeigewinkel (dreibein);
  dreibein.x= -dreibein.x;
  zeigewinkel (dreibein);
  printf ("\n");

  cvektor3 iwi;
  iwi.x= winkelb (pdreibein.x^pdreibein.y, -pdreibein.y^pdreibein.z);
  iwi.y= winkelb (pdreibein.y^pdreibein.z, -pdreibein.z^pdreibein.x);
  iwi.z= winkelb (pdreibein.z^pdreibein.x, -pdreibein.x^pdreibein.y);
  iwi.x*= 180/M_PIl;
  iwi.y*= 180/M_PIl;
  iwi.z*= 180/M_PIl;
  real iws= iwi.x + iwi.y + iwi.z;
  printf ("Innenwinkel des Dreibeins:\n %16.10LF %16.10LF %16.10LF    Innenwinkelsumme: %16.10LF\n", iwi.x, iwi.y, iwi.z, iws);
  printf ("\n");

  cvektor3 zv= normiere (pdreibein.x + pdreibein.y + pdreibein.z);
  printf ("Zentrivektor:\n");
  printvektor3ord (zv, 0);
  printf ("\n");

  cvektor3 zwi;
  zwi.x= winkelb (zv, pdreibein.x);
  zwi.y= winkelb (zv, pdreibein.y);
  zwi.z= winkelb (zv, pdreibein.z);
  zwi.x*= 180/M_PIl;
  zwi.y*= 180/M_PIl;
  zwi.z*= 180/M_PIl;
  printf ("Zentriwinkel zwischen Zentrivektor und den Spiegelachsen:\n %16.10LF %16.10LF %16.10LF\n", zwi.x, zwi.y, zwi.z);
  printf ("\n");

  cbasis3liste spiegeldrehungen (3);
  drehungenvonspiegelungen (spiegeldrehungen, pdreibein);
  printf ("von den Spiegelungen abgeleitetes Drehsystem:\n");
  printbasis3dreh (spiegeldrehungen.b[0], 0, 0, 0);
  printbasis3dreh (spiegeldrehungen.b[1], 0, 0, 0);
  printbasis3dreh (spiegeldrehungen.b[2], 0, 0, 0);
  printf ("\n");

  cvektor4 wiachs1= (winkelachsefrommatrix (spiegeldrehungen.b[0]));
  cvektor4 wiachs2= (winkelachsefrommatrix (spiegeldrehungen.b[1]));
  cvektor4 wiachs3 (winkelachsefrommatrix (spiegeldrehungen.b[2]));
  cvektor3 achse1= orientiere (normiere (cvektor3 (wiachs1.i, wiachs1.j, wiachs1.ij)));
  cvektor3 achse2= orientiere (normiere (cvektor3 (wiachs2.i, wiachs2.j, wiachs2.ij)));
  cvektor3 achse3 (orientiere (normiere (cvektor3 (wiachs3.i, wiachs3.j, wiachs3.ij))));
  real wid1 (180/M_PIl*winkelg (achse1, achse2));
  real wid2 (180/M_PIl*winkelg (achse1, achse3));
  real wid3 (180/M_PIl*winkelg (achse2, achse3));
  printf ("Winkel zwischen den Drehachsen (xy,xz,yz): %9.3Lf°%9.3Lf°%9.3Lf°\n", wid1, wid2, wid3);
  }

void zeigedreibein2(const cbasis3& pdreibein)
  {
  printf ("Spiegelachsen:\n");
  printvektor3ord (pdreibein.x, 0);
  printvektor3ord (pdreibein.y, 0);
  printvektor3ord (pdreibein.z, 0);
  printf ("\n");

  printf ("Winkel zwischen den Spiegelachsen:\n");
  cbasis3 dreibein= pdreibein;
  zeigewinkel (dreibein);
  printf ("\n");

  cvektor3 iwi;
  iwi.x= winkelb (pdreibein.x^pdreibein.y, -pdreibein.y^pdreibein.z);
  iwi.y= winkelb (pdreibein.y^pdreibein.z, -pdreibein.z^pdreibein.x);
  iwi.z= winkelb (pdreibein.z^pdreibein.x, -pdreibein.x^pdreibein.y);
  iwi.x*= 180/M_PIl;
  iwi.y*= 180/M_PIl;
  iwi.z*= 180/M_PIl;
  real iws= iwi.x + iwi.y + iwi.z;
  printf ("Innenwinkel des Dreibeins:\n %16.10LF %16.10LF %16.10LF    Innenwinkelsumme: %16.10LF\n", iwi.x, iwi.y, iwi.z, iws);
  printf ("\n");

  cbasis3liste spiegeldrehungen (3);
  drehungenvonspiegelungen (spiegeldrehungen, pdreibein);
  printf ("von den Spiegelungen abgeleitetes Drehsystem:\n");
  printbasis3dreh (spiegeldrehungen.b[0], 0, 0, 0);
  printbasis3dreh (spiegeldrehungen.b[1], 0, 0, 0);
  printbasis3dreh (spiegeldrehungen.b[2], 0, 0, 0);
  printf ("\n");

  cvektor4 wiachs1= (winkelachsefrommatrix (spiegeldrehungen.b[0]));
  cvektor4 wiachs2= (winkelachsefrommatrix (spiegeldrehungen.b[1]));
  cvektor4 wiachs3 (winkelachsefrommatrix (spiegeldrehungen.b[2]));
  cvektor3 achse1= orientiere (normiere (cvektor3 (wiachs1.i, wiachs1.j, wiachs1.ij)));
  cvektor3 achse2= orientiere (normiere (cvektor3 (wiachs2.i, wiachs2.j, wiachs2.ij)));
  cvektor3 achse3 (orientiere (normiere (cvektor3 (wiachs3.i, wiachs3.j, wiachs3.ij))));
  real wid1 (180/M_PIl*winkelg (achse1, achse2));
  real wid2 (180/M_PIl*winkelg (achse1, achse3));
  real wid3 (180/M_PIl*winkelg (achse2, achse3));
  printf ("Winkel zwischen den Drehachsen (xy,xz,yz): %9.3Lf°%9.3Lf°%9.3Lf°\n", wid1, wid2, wid3);
  printf ("-------------------------------------------------------------------------------------------------------------------------\n");
  }

//-------------------------- Menüpunkte  --------------------------------------------------------------------------------------------

void drehmul ()
  {
  cvektor4 el1= cvektor4 (1, 0, 0, 0);
  while (1)
    {
    cvektor4 quat= winkelachseeingabe ();
    el1=quaternionfromwinkelachse (quat)*el1;
    printvektor4quat (el1, 0, 0);
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
  printvektor4dreh (quatl, 0, 0, 0);
  printf ("Rechtsinverses von Q1:\n");
  printvektor4dreh (quatr, 0, 0, 0);
  printf ("c:\n");
  printvektor4dreh (quatc, 0, 0, 0);
  printf ("az:\n");
  printvektor4dreh (quataz, 0, 0, 0);
  printf ("bz:\n");
  printvektor4dreh (quatbz, 0, 0, 0);
  }

void testegoldenematrix ()
  {
  cvektor4 v1, v2, v3, v4, ein1, ass1, ass2, ass3;
  long double r1= .25*(sqrtl(5) + 1);
  long double i1= .25*(sqrtl(10 - 2*sqrtl(5)));
  long double r2= .25*(sqrtl(5) - 1);
  long double i2= .25*(sqrtl(10 + 2*sqrtl(5)));
  long double d3= sqrtl(3)/2;
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
  real sanz, danz;
  cvektor4 lage (1, 0, 0, 0);
  cvektor4 qdreh, awein;
  FILE* datei;

  while (1)
    {
    awein= winkelachseeingabe ();
    printf ("\n");
    printf ("Schritte:  ");
    scanret= scanf ("%Lf", &sanz);
    printf ("Anzahl Drehungen:  ");
    scanret= scanf ("%Lf", &danz);
    sanz= awein.r/sanz;
    qdreh= quaternionfromwinkelachse (awein);
    datei= fopen ("quaternionenoutput.txt", "ab");
    printf ("\nDrehquaternion:\n");
    fprintf (datei, "\nDrehquaternion:\n");
    fclose (datei);
    printvektor4dreh (qdreh, 0, 0, 0);
    datei= fopen ("quaternionenoutput.txt", "ab");
    printf ("\nDrehungen:\n");
    fprintf (datei, "\nDrehungen:\n");
    fclose (datei);
    for (integer laufd= 0; laufd < danz; laufd++)
      for (integer laufs= 0; laufs < sanz; laufs++)
        {
        lage= qdreh*lage;
        printvektor4dreh (lage, 0, 0, 0);
        }
    }
  }

//--------------------------------------  1 Drehspiegelung -------------------------------------------------

void dreh1 ()
  {
  cvektor4 el;
  cvektor4liste qliste (lmax);
  cbasis3liste bliste (lmax);
  cvektor3liste vliste (lmax);

  el= winkelachseeingabe ();
  if (el.r < 0)
    {
    el.r= -el.r;
    qliste.winkelachsehinzu (-el);
    bliste.winkelachsespieghinzu (el);
    }
    else
    {
    qliste.winkelachsehinzu (el);
    bliste.winkelachsehinzu (el);
    }
  qliste.schliesseab ();
  bliste.schliesseab ();

  printv4liste (qliste);
  printb3liste (bliste);

  vliste.elementhinzu (cvektor3 (1, 0, 0), 1);
  vliste.schliesseab (bliste);
  printv3liste (vliste);
  }

//-------------------------------------- 2 Drehspiegelungen ------------------------------------------------

void dreh2 ()
  {
  const char* objdatei="quaternionenoutput.obj";

//  printkreis ("kreis.obj", cbasis3 (cvektor3 (1, 2, 3), cvektor3 (5, 2, 8), cvektor3 (2, -5, 4)), 360);
  cvektor4 el1, el2;
  cvektor4liste qliste (lmax);
  cbasis3liste bliste (lmax);
  ccluster cluster (1000);
  cvektor3liste vliste (lmax);

  el1= winkelachseeingabe ();
  el2= winkelachseeingabe ();

  // negative Winkel bedeuten positiver Winkel + Inversion (Drehspiegelung)

  printtextobj (objdatei, "# --------------------------------------------------------------------------------------------------------------\n");
  printtextobj (objdatei, "# Körper\n\n");
  printtextobj (objdatei, "# Drehung1: ");
  printvektor3perfobj (objdatei, cvektor3 (el1.i, el1.j, el1.ij), 10);
  printtextobj (objdatei, " ");
  printzahlobj (objdatei, el1.r, 1);
  printtextobj (objdatei, "°\n");
  printtextobj (objdatei, "# Drehung2: ");
  printvektor3perfobj (objdatei, cvektor3 (el2.i, el2.j, el2.ij), 10);
  printtextobj (objdatei, " ");
  printzahlobj (objdatei, el2.r, 1);
  printtextobj (objdatei, "°\n");
  printtextobj (objdatei, "\n");
  el1.r= el1.r/180*M_PIl;
  el2.r= el2.r/180*M_PIl;

  if (el1.r < 0)
    {
    el1.r= -el1.r;
    qliste.winkelachsehinzu (-el1);
    bliste.winkelachsespieghinzu (el1);
    }
    else
    {
    qliste.winkelachsehinzu (el1);
    bliste.winkelachsehinzu (el1);
    }
  if (el2.r < 0)
    {
    el2.r= -el2.r;
    qliste.winkelachsehinzu (-el2);
    bliste.winkelachsespieghinzu (el2);
    }
    else
    {
    qliste.winkelachsehinzu (el2);
    bliste.winkelachsehinzu (el2);
    }

  qliste.schliesseab ();
  bliste.schliesseab ();
  
  if (!qliste.uebergelaufen)
    {
    qliste.ermittleordnung ();
    qliste.sortierenachordnung ();
    qliste.ermittlepaarung ();
    }
  if (!bliste.uebergelaufen)
    {
    bliste.ermittleordnung ();
    bliste.sortierenachordnung ();
//    bliste.ermittlepaarung ();
    }

  printtext ("-- Anfang -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
  printv4liste (qliste);
  getchar ();
  printb3liste (bliste);
  getchar ();
  cluster.gruppe->kopiere (bliste);
  cluster.vervollstaendige ();

  printtext ("Gruppe:\n");
  printb3liste (*cluster.gruppe);
  getchar ();
  printtext ("Kern:\n");
  printb3liste (*cluster.kern);
  getchar ();
  printtext ("maxord Gruppe:   ");
  printinteger (cluster.gruppe->maxord);
  printtext ("maxord Kern:   ");
  printinteger (cluster.kern->maxord);
  printtext ("\nPartliste:\n");
  printv3liste (*cluster.partliste);
  printtext ("maximale Zähligkeit:   ");
  printreal (real (cluster.gruppe->maxord));
  printtext ("\n\n");

  printtext ("Kanten:\n");
  printv3liste (*cluster.kliste);
  printtext ("Ecken:\n");
  printv3liste (*cluster.eliste);
  printtext ("Flächen:\n");
  printv3liste (*cluster.fliste);

  printtext ("Spiegelungen:\n");
  printb3liste (*cluster.spieg);

// ------  objprint -----------------------------------

  printtextobj (objdatei, "# Gruppenordnung: ");
  printrealobj (objdatei, bliste.anz);
  printtextobj (objdatei, "\n");
  printtextobj (objdatei, "# Drehungen: ");
  printrealobj (objdatei, cluster.kern->anz);
  printtextobj (objdatei, "\n");

  if (bliste.anz != cluster.kern->anz)
    {
    printtextobj (objdatei, "# kleinster Drehinversionswinkel: ");
    printzahlobj (objdatei, cluster.gruppe->miniwinkel/M_PIl*180,2);
    printtextobj (objdatei, "°\n");
    printtextobj (objdatei, "# Spiegelebenen: ");
    printrealobj (objdatei, cluster.spieg->anz);
    printtextobj (objdatei, "\n");
    }

  printtextobj (objdatei, "\n");
  printtext ("Vektoreingabe:\n");
  cvektor3 vein;
  vektor3eingabe (vein);
  printtextobj (objdatei, "# Körpervektor:          ");
  printvektor3perfobj (objdatei, vein, 10);
  printtextobj (objdatei, "\n");
  cvektor3 nvein= normiere (vein);
  printtextobj (objdatei, "# Körpervektor normiert: ");
  printvektor3perfobj (objdatei, nvein, 10);
  printtextobj (objdatei, "\n");
  printtextobj (objdatei, "\n");
  cvektor3 efk= cluster.ermittleefkdreibein (nvein, 1);
  cvektor3 vecke= cluster.fliste->v[integer (efk.x)];
  cvektor3 vflaeche= cluster.eliste->v[integer (efk.y)];
  cvektor3 vkante= cluster.kliste->v[integer (efk.z)];
  printtextobj (objdatei, "# Eckenvektor:   ");
  printvektor3perfobj (objdatei, vecke, 10);
  printtextobj (objdatei, "\n");
  printtextobj (objdatei, "# Flächenvektor: ");
  printvektor3perfobj (objdatei, vflaeche, 10);
  printtextobj (objdatei, "\n");
  printtextobj (objdatei, "# Kantenvektor:  ");
  printvektor3perfobj (objdatei, vkante, 10);
  printtextobj (objdatei, "\n");
  cbasis3 divbasis= cbasis3 (vecke, vflaeche, vkante);
  printtextobj (objdatei, "# Volumen EFK Dreibein:  ");
  printzahlobj (objdatei, det (divbasis), 10);
  printtextobj (objdatei, "\n\n");

  cvektor3 efklin, efknorm, efkenorm, efkfnorm;
  efklin= nvein/divbasis;
  printtextobj (objdatei, "# efk-Vektor:                                  ");
  printvektor3perfobj (objdatei, efklin, 10);
  printtextobj (objdatei, "\n");
  efknorm= normiere (efklin);
  printtextobj (objdatei, "# efk-Vektor normiert:                         ");
  printvektor3perfobj (objdatei, efknorm, 10);
  printtextobj (objdatei, "\n");
  if (!aehnlich (efklin.x, 0))
    efkenorm= efklin/efklin.x;
    else
    efkenorm= cvektor3 (0, 0, 0);
  printtextobj (objdatei, "# efk-Vektor E-normiert:                       ");
  printvektor3perfobj (objdatei, efkenorm, 10);
  printtextobj (objdatei, "\n");
  if (!aehnlich (efklin.y, 0))
    efkfnorm= efklin/efklin.y;
    else
    efkfnorm= cvektor3 (0, 0, 0);
  printtextobj (objdatei, "# efk-Vektor F-normiert:                       ");
  printvektor3perfobj (objdatei, efkfnorm, 10);
  printtextobj (objdatei, "\n");

  cvektor3 rvlin= divbasis*efklin;
  printtextobj (objdatei, "# Körpervektor aus Linearkombination:          ");
  printvektor3perfobj (objdatei, rvlin, 10);
  printtextobj (objdatei, "\n");
  rvlin= normiere (rvlin);
  printtextobj (objdatei, "# Körpervektor aus Linearkombination normiert: ");
  printvektor3perfobj (objdatei, rvlin, 10);
  printtextobj (objdatei, "\n");
  cvektor3 vlindif= rvlin - nvein;
  printtextobj (objdatei, "# Differenz KöV normiert, LK normiert:         ");
  printvektor3perfobj (objdatei, vlindif, 10);
  printtextobj (objdatei, "\n");

  printtextobj (objdatei, "\n");
  // Vektor mit Gruppe zum Körper aufspannen
  vliste.elementhinzu (nvein, 1);
  vliste.schliesseab (bliste);
  printtextobj (objdatei, "# Punkte: ");
  printrealobj (objdatei, vliste.anz);
  printtextobj (objdatei, "\n");
  printtextobj (objdatei, "\n");
  printv3liste (vliste);
  printv3listeobj (objdatei, vliste);

  // Kantenkörper aufbauen
  const char* kkdatei="kantenkörper.obj";
  printv3listekantenobj (kkdatei, vliste);
  printtextobj (kkdatei, "\n# EFK-Vektoren\n");
  printvektor3blenderobj (kkdatei, cvektor3 (0, 0, 0), 10);
  printvektor3blenderobj (kkdatei, vecke, 10);
  printvektor3blenderobj (kkdatei, vflaeche, 10);
  printvektor3blenderobj (kkdatei, vkante, 10);
  printtextobj (kkdatei, "\n");
  printtextobj (kkdatei, "l ");
  printzahlobj (kkdatei, vliste.anz + 1, 0);
  printtextobj (kkdatei, " ");
  printzahlobj (kkdatei, vliste.anz + 2, 0);
  printtextobj (kkdatei, "\n");
  printtextobj (kkdatei, "l ");
  printzahlobj (kkdatei, vliste.anz + 1, 0);
  printtextobj (kkdatei, " ");
  printzahlobj (kkdatei, vliste.anz + 3, 0);
  printtextobj (kkdatei, "\n");
  printtextobj (kkdatei, "l ");
  printzahlobj (kkdatei, vliste.anz + 1, 0);
  printtextobj (kkdatei, " ");
  printzahlobj (kkdatei, vliste.anz + 4, 0);
  printtextobj (kkdatei, "\n");
  printtextobj (kkdatei, "\n# Körpervektor\n");
  printvektor3blenderobj (kkdatei, nvein, 10);
  printtextobj (kkdatei, "\n");
  printtextobj (kkdatei, "l ");
  printzahlobj (kkdatei, vliste.anz + 1, 0);
  printtextobj (kkdatei, " ");
  printzahlobj (kkdatei, vliste.anz + 5, 0);
  printtextobj (kkdatei, "\n\n");

  printtext ("-- Ende -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
  }

//-------------------------------------- EFK Körper aufbauen ------------------------------------------------

void dreh2efk ()
  {
  const char* objdatei="quaternionenoutput.obj";
  cvektor4 el1, el2;
  cvektor4liste qliste (lmax);
  cbasis3liste bliste (lmax);
  ccluster cluster (1000);
  cvektor3liste vliste (lmax);

  el1= winkelachseeingabe ();
  el2= winkelachseeingabe ();

  // negative Winkel bedeuten positiver Winkel + Inversion (Drehspiegelung)

  printtextobj (objdatei, "# --------------------------------------------------------------------------------------------------------------\n");
  printtextobj (objdatei, "# Körper\n\n");
  printtextobj (objdatei, "# Drehung1: ");
  printvektor3perfobj (objdatei, cvektor3 (el1.i, el1.j, el1.ij), 10);
  printtextobj (objdatei, " ");
  printzahlobj (objdatei, el1.r, 1);
  printtextobj (objdatei, "°\n");
  printtextobj (objdatei, "# Drehung2: ");
  printvektor3perfobj (objdatei, cvektor3 (el2.i, el2.j, el2.ij), 10);
  printtextobj (objdatei, " ");
  printzahlobj (objdatei, el2.r, 1);
  printtextobj (objdatei, "°\n");
  printtextobj (objdatei, "\n");
  el1.r= el1.r/180*M_PIl;
  el2.r= el2.r/180*M_PIl;

  if (el1.r < 0)
    {
    el1.r= -el1.r;
    qliste.winkelachsehinzu (-el1);
    bliste.winkelachsespieghinzu (el1);
    }
    else
    {
    qliste.winkelachsehinzu (el1);
    bliste.winkelachsehinzu (el1);
    }
  if (el2.r < 0)
    {
    el2.r= -el2.r;
    qliste.winkelachsehinzu (-el2);
    bliste.winkelachsespieghinzu (el2);
    }
    else
    {
    qliste.winkelachsehinzu (el2);
    bliste.winkelachsehinzu (el2);
    }

  qliste.schliesseab ();
  bliste.schliesseab ();
  
  if (!qliste.uebergelaufen)
    {
    qliste.ermittleordnung ();
    qliste.sortierenachordnung ();
    qliste.ermittlepaarung ();
    }
  if (!bliste.uebergelaufen)
    {
    bliste.ermittleordnung ();
    bliste.sortierenachordnung ();
//    bliste.ermittlepaarung ();
    }

  printtext ("-- Anfang -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
  printv4liste (qliste);
//  getchar ();
  printb3liste (bliste);
//  getchar ();
  cluster.gruppe->kopiere (bliste);
  cluster.vervollstaendige ();

  printtext ("Gruppe:\n");
  printb3liste (*cluster.gruppe);
//  getchar ();
  printtext ("Kern:\n");
  printb3liste (*cluster.kern);
//  getchar ();
  printtext ("maxord Gruppe:   ");
  printinteger (cluster.gruppe->maxord);
  printtext ("maxord Kern:   ");
  printinteger (cluster.kern->maxord);
  printtext ("\nPartliste:\n");
  printv3liste (*cluster.partliste);
  printtext ("maximale Zähligkeit:   ");
  printreal (real (cluster.gruppe->maxord));
  printtext ("\n\n");

  printtext ("Kanten:\n");
  printv3liste (*cluster.kliste);
  printtext ("Ecken:\n");
  printv3liste (*cluster.eliste);
  printtext ("Flächen:\n");
  printv3liste (*cluster.fliste);

  printtext ("Spiegelungen:\n");
  printb3liste (*cluster.spieg);

// ----------------- obj print -------------------------------

  printtextobj (objdatei, "# Gruppenordnung: ");
  printrealobj (objdatei, bliste.anz);
  printtextobj (objdatei, "\n");
  printtextobj (objdatei, "# Drehungen: ");
  printrealobj (objdatei, cluster.kern->anz);
  printtextobj (objdatei, "\n");

  if (bliste.anz != cluster.kern->anz)
    {
    printtextobj (objdatei, "# kleinster Drehinversionswinkel: ");
    printzahlobj (objdatei, cluster.gruppe->miniwinkel/M_PIl*180,2);
    printtextobj (objdatei, "°\n");
    printtextobj (objdatei, "# Spiegelebenen: ");
    printrealobj (objdatei, cluster.spieg->anz);
    printtextobj (objdatei, "\n");
    }

  printtextobj (objdatei, "\n");

  cvektor3 efk= cluster.ermittleefkdreibein (cluster.kliste->v[0], 1);
//  cvektor3 efk= cluster.ermittleefkdreibein (cvektor3 (el1.i, el1.j, el1.ij), 1);
  cvektor3 vecke= cluster.fliste->v[integer (efk.x)];
  cvektor3 vflaeche= cluster.eliste->v[integer (efk.y)];
  cvektor3 vkante= cluster.kliste->v[integer (efk.z)];
  printtextobj (objdatei, "# Eckenvektor:   ");
  printvektor3perfobj (objdatei, vecke, 10);
  printtextobj (objdatei, "\n");
  printtextobj (objdatei, "# Flächenvektor: ");
  printvektor3perfobj (objdatei, vflaeche, 10);
  printtextobj (objdatei, "\n");
  printtextobj (objdatei, "# Kantenvektor:  ");
  printvektor3perfobj (objdatei, vkante, 10);
  printtextobj (objdatei, "\n");
  cbasis3 divbasis= cbasis3 (vecke, vflaeche, vkante);
  printtextobj (objdatei, "# Volumen EFK Dreibein:  ");
  printzahlobj (objdatei, det (divbasis), 10);
  printtextobj (objdatei, "\n\n");

  cvektor3 efkein, efknorm, efkenorm, efkfnorm, vein, nvein;
  printtext ("efk-Vektor:\n");
  vektor3eingabe (efkein);
  printtextobj (objdatei, "# efk-Vektor:              ");
  printvektor3perfobj (objdatei, efkein, 10);
  printtextobj (objdatei, "\n");
  efknorm= normiere (efkein);
  printtextobj (objdatei, "# efk-Vektor normiert:     ");
  printvektor3perfobj (objdatei, efknorm, 10);
  printtextobj (objdatei, "\n");
  if (!aehnlich (efkein.x, 0))
    efkenorm= efkein/efkein.x;
    else
    efkenorm= cvektor3 (0, 0, 0);
  printtextobj (objdatei, "# efk-Vektor E-normiert:   ");
  printvektor3perfobj (objdatei, efkenorm, 10);
  printtextobj (objdatei, "\n");
  if (!aehnlich (efkein.y, 0))
    efkfnorm= efkein/efkein.y;
    else
    efkfnorm= cvektor3 (0, 0, 0);
  printtextobj (objdatei, "# efk-Vektor F-normiert:   ");
  printvektor3perfobj (objdatei, efkfnorm, 10);
  printtextobj (objdatei, "\n");
  vein= divbasis*efkein;
  printtextobj (objdatei, "# Körpervektor:          ");
  printvektor3perfobj (objdatei, vein, 10);
  printtextobj (objdatei, "\n");
  nvein= normiere (vein);
  printtextobj (objdatei, "# Körpervektor normiert: ");
  printvektor3perfobj (objdatei, nvein, 10);
  printtextobj (objdatei, "\n");
  printtextobj (objdatei, "\n");

  // Vektor mit Gruppe zum Körper aufspannen
  real kreispunkte= 1;
  printtext ("Kantenstücke:\n");
  realeingabe (kreispunkte);

  vliste.elementhinzu (nvein, 1);
  vliste.schliesseab (bliste);
  printtextobj (objdatei, "# Punkte: ");
  printrealobj (objdatei, vliste.anz);
  printtextobj (objdatei, "\n");
  printtextobj (objdatei, "\n");
  printv3liste (vliste);
  printv3listeobj (objdatei, vliste);

  // Kantenkörper aufbauen
  const char* kkdatei="kantenkörper.obj";
  if (aehnlich (kreispunkte, 0))
    {
  printv3listekantenobj (kkdatei, vliste);
  printtextobj (kkdatei, "\n# EFK-Vektoren\n");
  printvektor3blenderobj (kkdatei, cvektor3 (0, 0, 0), 10);
  printvektor3blenderobj (kkdatei, vecke, 10);
  printvektor3blenderobj (kkdatei, vflaeche, 10);
  printvektor3blenderobj (kkdatei, vkante, 10);
  printtextobj (kkdatei, "\n");
  printtextobj (kkdatei, "l ");
  printzahlobj (kkdatei, vliste.anz + 1, 0);
  printtextobj (kkdatei, " ");
  printzahlobj (kkdatei, vliste.anz + 2, 0);
  printtextobj (kkdatei, "\n");
  printtextobj (kkdatei, "l ");
  printzahlobj (kkdatei, vliste.anz + 1, 0);
  printtextobj (kkdatei, " ");
  printzahlobj (kkdatei, vliste.anz + 3, 0);
  printtextobj (kkdatei, "\n");
  printtextobj (kkdatei, "l ");
  printzahlobj (kkdatei, vliste.anz + 1, 0);
  printtextobj (kkdatei, " ");
  printzahlobj (kkdatei, vliste.anz + 4, 0);
  printtextobj (kkdatei, "\n");
  printtextobj (kkdatei, "\n# Körpervektor\n");
  printvektor3blenderobj (kkdatei, nvein, 10);
  printtextobj (kkdatei, "\n");
  printtextobj (kkdatei, "l ");
  printzahlobj (kkdatei, vliste.anz + 1, 0);
  printtextobj (kkdatei, " ");
  printzahlobj (kkdatei, vliste.anz + 5, 0);
  printtextobj (kkdatei, "\n\n");
    }
    else
    printv3listekreiskantenobj ("kantenkörper.obj", vliste, integer (kreispunkte));
  printtext ("-- Ende -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
  }

//-------------------------------------- Generiere Polyeder ------------------------------------------------

void ermittleefkvektor (cvektor3& pefkvektor, cvektor4 pdreh1, cvektor4 pdreh2, cvektor3 pkoerperv)
  {
  cvektor4 el1, el2;
  cbasis3liste bliste (lmax);
  ccluster cluster (1000);
  cvektor3liste vliste (lmax);

  el1= pdreh1;
  el2= pdreh2;

  el1.r= el1.r/180*M_PIl;
  el2.r= el2.r/180*M_PIl;

  // negative Winkel bedeuten positiver Winkel + Inversion (Drehspiegelung)

  if (el1.r < 0)
    {
    el1.r= -el1.r;
    bliste.winkelachsespieghinzu (el1);
    }
    else
    {
    bliste.winkelachsehinzu (el1);
    }
  if (el2.r < 0)
    {
    el2.r= -el2.r;
    bliste.winkelachsespieghinzu (el2);
    }
    else
    {
    bliste.winkelachsehinzu (el2);
    }

  bliste.schliesseab ();
  
  if (!bliste.uebergelaufen)
    {
    bliste.ermittleordnung ();
    bliste.sortierenachordnung ();
//    bliste.ermittlepaarung ();
    }

  cluster.gruppe->kopiere (bliste);
  cluster.vervollstaendige ();

  cvektor3 efk= cluster.ermittleefkdreibein (pkoerperv, 1);
  cvektor3 vecke= cluster.fliste->v[integer (efk.x)];
  cvektor3 vflaeche= cluster.eliste->v[integer (efk.y)];
  cvektor3 vkante= cluster.kliste->v[integer (efk.z)];
  cbasis3 divbasis= cbasis3 (vecke, vflaeche, vkante);

  pefkvektor= pkoerperv/divbasis;
  pefkvektor= pefkvektor/pefkvektor.x;
  }

// praum = {1, -1} efkja= {0, 1}
void generiere1polyederobj (const char* pdateiname, cvektor4 pdreh1, cvektor4 pdreh2, cvektor3 pefk, real praum, integer efkja)
  {
  const char* kkdatei=  pdateiname;
  cvektor4 el1, el2;
  cbasis3liste bliste (lmax);
  ccluster cluster (1000);
  cvektor3liste vliste (lmax);
  cvektor3 efkein, efknorm, efkenorm, efkfnorm, vein, nvein;

  el1= pdreh1;
  el2= pdreh2;
  efkein= pefk;

  el1.r= el1.r/180*M_PIl;
  el2.r= el2.r/180*M_PIl;

  // negative Winkel bedeuten positiver Winkel + Inversion (Drehspiegelung)

  if (el1.r < 0)
    {
    el1.r= -el1.r;
    bliste.winkelachsespieghinzu (el1);
    }
    else
    {
    bliste.winkelachsehinzu (el1);
    }
  if (el2.r < 0)
    {
    el2.r= -el2.r;
    bliste.winkelachsespieghinzu (el2);
    }
    else
    {
    bliste.winkelachsehinzu (el2);
    }

  bliste.schliesseab ();
  
  if (!bliste.uebergelaufen)
    {
    bliste.ermittleordnung ();
    bliste.sortierenachordnung ();
//    bliste.ermittlepaarung ();
    }

  cluster.gruppe->kopiere (bliste);
  cluster.vervollstaendige ();

  // EFK-Basis erstellen
  cvektor3 efk= cluster.ermittleefkdreibein (cluster.kliste->v[0], praum);
  cvektor3 vecke= cluster.fliste->v[integer (efk.x)];
  cvektor3 vflaeche= cluster.eliste->v[integer (efk.y)];
  cvektor3 vkante= cluster.kliste->v[integer (efk.z)];
  cbasis3 divbasis= cbasis3 (vecke, vflaeche, vkante);

  if (efkja)
    {
    // Körpervektor aus EFK-Vektor berechnen
    efknorm= normiere (efkein);
    efkenorm= normiere (efkein);
    vein= divbasis*efkein;
    }
    else
    {
    vein= efkein;
    efkein= vein/divbasis;
    }
  nvein= normiere (vein);

 // Vektor mit Gruppe zum Körper aufspannen
  vliste.elementhinzu (nvein, 1);
  vliste.schliesseab (bliste);

// ----------------- print Eingabedaten -------------------------------------------------------------------------------------------------------

  printtextobj (kkdatei, "# --------------------------------------------------------------------------------------------------------------\n");
  printtextobj (kkdatei, "# Körper\n\n");
  printtextobj (kkdatei, "# Drehung1: ");
  printvektor3perfobj (kkdatei, cvektor3 (el1.i, el1.j, el1.ij), 10);
  printtextobj (kkdatei, " ");
  printzahlobj (kkdatei, pdreh1.r, 1);
  printtextobj (kkdatei, "°\n");
  printtextobj (kkdatei, "# Drehung2: ");
  printvektor3perfobj (kkdatei, cvektor3 (el2.i, el2.j, el2.ij), 10);
  printtextobj (kkdatei, " ");
  printzahlobj (kkdatei, pdreh2.r, 1);
  printtextobj (kkdatei, "°\n");
  printtextobj (kkdatei, "\n");

// ----------------- kantenkörperdatei print -------------------------------

  printtextobj (kkdatei, "# Gruppenordnung: ");
  printrealobj (kkdatei, bliste.anz);
  printtextobj (kkdatei, "\n");
  printtextobj (kkdatei, "# Drehungen: ");
  printrealobj (kkdatei, cluster.kern->anz);
  printtextobj (kkdatei, "\n");

  if (bliste.anz != cluster.kern->anz)
    {
    printtextobj (kkdatei, "# kleinster Drehspiegelungswinkel: ");
    printzahlobj (kkdatei, cluster.gruppe->miniwinkel/M_PIl*180,2);
    printtextobj (kkdatei, "°\n");
    printtextobj (kkdatei, "# Spiegelebenen: ");
    printrealobj (kkdatei, cluster.spieg->anz);
    printtextobj (kkdatei, "\n");
    }

  printtextobj (kkdatei, "\n");

  printtextobj (kkdatei, "# Eckenvektor:   ");
  printvektor3perfobj (kkdatei, vecke, 10);
  printtextobj (kkdatei, "\n");
  printtextobj (kkdatei, "# Flächenvektor: ");
  printvektor3perfobj (kkdatei, vflaeche, 10);
  printtextobj (kkdatei, "\n");
  printtextobj (kkdatei, "# Kantenvektor:  ");
  printvektor3perfobj (kkdatei, vkante, 10);
  printtextobj (kkdatei, "\n");

  printtextobj (kkdatei, "# Volumen EFK Dreibein:  ");
  printzahlobj (kkdatei, det (divbasis), 10);
  printtextobj (kkdatei, "\n\n");

  printtextobj (kkdatei, "# efk-Vektor:            ");
  printvektor3perfobj (kkdatei, efkein, 10);
  printtextobj (kkdatei, "\n");

  printtextobj (kkdatei, "# efk-Vektor normiert:   ");
  printvektor3perfobj (kkdatei, efknorm, 10);
  printtextobj (kkdatei, "\n");

  printtextobj (kkdatei, "# efk-Vektor normiert:   ");
  printvektor3perfobj (kkdatei, efknorm, 10);
  printtextobj (kkdatei, "\n");

  printtextobj (kkdatei, "# Körpervektor:          ");
  printvektor3perfobj (kkdatei, vein, 10);
  printtextobj (kkdatei, "\n");

  printtextobj (kkdatei, "# Körpervektor normiert: ");
  printvektor3perfobj (kkdatei, nvein, 10);
  printtextobj (kkdatei, "\n");
  printtextobj (kkdatei, "\n");

  printtextobj (kkdatei, "# Punkte: ");
  printrealobj (kkdatei, vliste.anz);
  printtextobj (kkdatei, "\n");
  printtextobj (kkdatei, "\n");

  // Kantenkörper aufbauen
  printv3listekantenobj (kkdatei, vliste);
  printtextobj (kkdatei, "\n# EFK-Vektoren\n");
  printvektor3blenderobj (kkdatei, cvektor3 (0, 0, 0), 10);
  printvektor3blenderobj (kkdatei, vecke, 10);
  printvektor3blenderobj (kkdatei, vflaeche, 10);
  printvektor3blenderobj (kkdatei, vkante, 10);
  printtextobj (kkdatei, "\n");
  printtextobj (kkdatei, "l ");
  printzahlobj (kkdatei, vliste.anz + 1, 0);
  printtextobj (kkdatei, " ");
  printzahlobj (kkdatei, vliste.anz + 2, 0);
  printtextobj (kkdatei, "\n");
  printtextobj (kkdatei, "l ");
  printzahlobj (kkdatei, vliste.anz + 1, 0);
  printtextobj (kkdatei, " ");
  printzahlobj (kkdatei, vliste.anz + 3, 0);
  printtextobj (kkdatei, "\n");
  printtextobj (kkdatei, "l ");
  printzahlobj (kkdatei, vliste.anz + 1, 0);
  printtextobj (kkdatei, " ");
  printzahlobj (kkdatei, vliste.anz + 4, 0);
  printtextobj (kkdatei, "\n");
  printtextobj (kkdatei, "\n# Körpervektor\n");
  printvektor3blenderobj (kkdatei, nvein, 10);
  printtextobj (kkdatei, "\n");
  printtextobj (kkdatei, "l ");
  printzahlobj (kkdatei, vliste.anz + 1, 0);
  printtextobj (kkdatei, " ");
  printzahlobj (kkdatei, vliste.anz + 5, 0);
  printtextobj (kkdatei, "\n\n");
  }

void generierepolyederobj ()
  {
  const char* objdatei;
  cvektor4 dreh1, dreh2, dreh3;
  cvektor3 koerperv, vefk;

//------------------------  T, Td -----------------------------------------------------------------------

  dreh1= cvektor4 (120, 0, 0, -1);
  dreh2= cvektor4 (120, sqrtl (8), 0, 1);
  dreh3= cvektor4 (-180, 1, 0, sqrtl (2));  // Spiegelkante funktioniert nicht als Drehkante

  // Tetraeder E
  objdatei= "Polyeder/11 T  E     Tetraeder.obj";
  vefk= cvektor3 (0, 1, 0);
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 1);

  // Tetraeder F (dual)
  objdatei= "Polyeder/12 T  F     Tetraeder dual.obj";
  vefk= cvektor3 (1, 0, 0);
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 1);

  // Tetraeder K (Oktaeder)
  objdatei= "Polyeder/13 T  K     Oktaeder.obj";
  vefk= cvektor3 (0, 0, 1);
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 1);

  // Tetraeder E+K (Tetraederstumpf)
  objdatei= "Polyeder/14 T  E+K   Tetraederstumpf.obj";
  vefk= cvektor3 (0, 1, 2/sqrtl (3));
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 1);

  // Tetraeder F+K (Tetraederstumpf dual)
  objdatei= "Polyeder/15 T  F+K   Tetraederstumpf dual.obj";
  vefk= cvektor3 (1, 0, 2/sqrtl (3));
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 1);

  // Tetraeder E+F (Kuboktaeder)
  objdatei= "Polyeder/16 T  E+F   Kuboktaeder.obj";
  vefk= cvektor3 (1, 1, 0);
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 1);

  // Tetraeder E+F+K (Ikosaeder)
  vefk= cvektor3 (1, 1, (sqrtl (5) - 1)/sqrtl (3));

  // Tetraeder E+F+K (Ikosaeder) FEK+
  objdatei= "Polyeder/17 T  E+F+K Ikosaeder FEK+.obj";
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 1);

  // Tetraeder E+F+K (Ikosaeder) FEK-
  objdatei= "Polyeder/17 T  E+F+K Ikosaeder FEK-.obj";
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, -1, 1);

  // Tetraeder E+F+K (Oktaederstumpf)
  objdatei= "Polyeder/18 Td E+F+K Oktaederstumpf.obj";
  vefk= cvektor3 (1, 1, 2/sqrtl (3));
  generiere1polyederobj (objdatei, dreh1, dreh3, vefk, 1, 1);

//----------------------------------------------- O, Oh -------------------------------------------------

  dreh1= cvektor4 (90, 1, 0, 0);
  dreh2= cvektor4 (90, 0, 1, 0);
  dreh3= cvektor4 (-90, 0, 1, 0);

  // Würfel E
  objdatei= "Polyeder/21 O  E     Würfel.obj";
  vefk= cvektor3 (1, 0, 0);
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 1);

  // Oktaeder F
  objdatei= "Polyeder/22 O  F     Oktaeder.obj";
  vefk= cvektor3 (0, 1, 0);
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 1);

  // Kuboktaeder K
  objdatei= "Polyeder/23 O  K     Kuboktaeder.obj";
  vefk= cvektor3 (0, 0, 1);
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 1);

  // Würfelstumpf E+K
  objdatei= "Polyeder/24 O  E+K   Würfelstumpf.obj";
  vefk= cvektor3 (1, 0, 2/sqrtl (3));
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 1);

  // Oktaederstumpf F+K
  objdatei= "Polyeder/25 O  F+K   Oktaederstumpf.obj";
  vefk= cvektor3 (0, 1, sqrtl (2));
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 1);

  // Rhombenkuboktaeder E+F
  objdatei= "Polyeder/26 O  E+F   Rhombenkuboktaeder.obj";
  vefk= cvektor3 (1, sqrtl (real (2)/3), 0);
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 1);

  // Cubus Simus E+F+K
  koerperv= cvektor3 (tk, 1, 1/tk);
  ermittleefkvektor (vefk, dreh1, dreh2, koerperv);

  // Cubus Simus E+F+K FEK+
  objdatei= "Polyeder/27 O  E+F+K Cubus Simus FEK+.obj";
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 1);

  // Cubus Simus E+F+K FEK-
  objdatei= "Polyeder/27 O  E+F+K Cubus Simus FEK-.obj";
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, -1, 1);

  // großes Rhombenkuboktaeder E+F+K
  objdatei= "Polyeder/28 Oh E+F+K großes Rhombenkuboktaeder.obj";
  vefk= cvektor3 (1, sqrtl (real (2)/3), 2/sqrtl (3));
  generiere1polyederobj (objdatei, dreh1, dreh3, vefk, 1, 1);

//----------------------------------------------- I, Ih -------------------------------------------------

  dreh1= cvektor4 (72, 0, 0, 1);
  dreh2= cvektor4 (180, -1, 0, gk);
  dreh3= cvektor4 (-180, -1, 0, gk);

  // Dodecaedron simum
  cvektor4 dreh1kart, dreh2kart;
  dreh1kart= cvektor4 (120, 1, 1, 1);
  dreh2kart= cvektor4 (72, 0, 1, gk);
  real x;

  // Dodekaeder E
  objdatei= "Polyeder/31 I  E     Dodekaeder.obj";
  vefk= cvektor3 (1, 0, 0);
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 1);

  // Ikosaeder F
  objdatei= "Polyeder/32 I  F     Ikosaeder.obj";
  vefk= cvektor3 (0, 1, 0);
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 1);

  // Ikosidodekaeder K
  objdatei= "Polyeder/33 I  K     Ikosidodekaeder.obj";
  vefk= cvektor3 (0, 0, 1);
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 1);

  // Dodekaederstumpf E+K
  objdatei= "Polyeder/34 I  E+K   Dodekaederstumpf.obj";
  vefk= cvektor3 (1, 0, 2/sqrtl (3));
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 1);

  // Ikosaederstumpf F+K
  objdatei= "Polyeder/35 I  F+K   Ikosaederstumpf.obj";
  vefk= cvektor3 (0, 1, sqrtl (8/(5 - sqrtl(5))));
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 1);

  // Rhombenikosidodekaeder E+F
  objdatei= "Polyeder/36 I  E+F   Rhombenikosidodekaeder.obj";
  vefk= cvektor3 (1, sqrtl ((5 - sqrtl(5))/6), 0);
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 1);

  // Dodecaedron simum E+F+K
  x= kubischegleichung (2, 0, -gk*gk);
  koerperv= cvektor3 (x, (1 - x)*gk*gk, ((2*x + 1)*x - gk*gk)*gk);
  ermittleefkvektor (vefk, dreh1kart, dreh2kart, koerperv);

  // Dodecaedron simum E+F+K  FEK+
  objdatei= "Polyeder/37 I  E+F+K Dodecaedron simum FEK+.obj";
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 1);

  // Dodecaedron simum E+F+K  FEK-
  objdatei= "Polyeder/37 I  E+F+K Dodecaedron simum FEK-.obj";
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, -1, 1);

  // großes Rhombenkikosidodekaeder E+F+K
  objdatei= "Polyeder/38 Ih E+F+K großes Rhombenikosidodekaeder.obj";
  vefk= cvektor3 (1, sqrtl ((5 - sqrtl(5))/6), 2/sqrtl (3));
  generiere1polyederobj (objdatei, dreh1, dreh3, vefk, 1, 1);

//----------------------------------------------- Th -------------------------------------------------------

  // Th E (Würfel)
  objdatei= "Polyeder/41 Th E     Würfel.obj";
  dreh1= cvektor4 (120, 1, 1, 1);
  dreh2= cvektor4 (-180, 1, 0, 0);
  vefk= cvektor3 (1, 1, 1);
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 0);

  // Th F (Oktaeder)
  objdatei= "Polyeder/42 Th F     Oktaeder.obj";
  dreh1= cvektor4 (120, 1, 1, 1);
  dreh2= cvektor4 (-180, 1, 0, 0);
  vefk= cvektor3 (1, 0, 0);
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 0);

  // Th K (Kuboktaeder)
  objdatei= "Polyeder/43 Th K     Kuboktaeder.obj";
  dreh1= cvektor4 (120, 1, 1, 1);
  dreh2= cvektor4 (-180, 1, 0, 0);
  vefk= cvektor3 (1, 1, 0);
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 0);

  // Th E+K (Würfelstumpf)
  objdatei= "Polyeder/44 Th E+K   Würfelstumpf.obj";
  dreh1= cvektor4 (120, 1, 1, 1);
  dreh2= cvektor4 (-180, 1, 0, 0);
  vefk= cvektor3 (1, 1, sqrtl (2) - 1);
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 0);

  // Th F+K (Ikosaeder)
  objdatei= "Polyeder/45 Th F+K   Ikosaeder.obj";
  dreh1= cvektor4 (120, 1, 1, 1);
  dreh2= cvektor4 (-180, 1, 0, 0);
  vefk= cvektor3 (gk, 1, 0);
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 0);

  // Th E+F (Rhombenkuboktaeder)
  objdatei= "Polyeder/46 Th E+F   Rhombenkuboktaeder.obj";
  dreh1= cvektor4 (120, 1, 1, 1);
  dreh2= cvektor4 (-180, 1, 0, 0);
  vefk= cvektor3 (1 + sqrtl (2), 1, 1);
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 0);

  // Th E (Trapezkörper Würfel FK)
  objdatei= "Polyeder/471 Th E-FK  Trapezkörper Würfel FK.obj";
  dreh1= cvektor4 (120, 1, 1, 1);
  dreh2= cvektor4 (-180, 1, 0, 0);
  vefk= cvektor3 (1.2, 1.1, 1);
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 0);

  // Th E (Trapezkörper Würfel F)
  objdatei= "Polyeder/471 Th E-F  Trapezkörper Würfel F.obj";
  dreh1= cvektor4 (120, 1, 1, 1);
  dreh2= cvektor4 (-180, 1, 0, 0);
  vefk= cvektor3 (1.1, 1, 1);
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 0);

  // Th E (Trapezkörper Würfel K)
  objdatei= "Polyeder/471 Th E-K  Trapezkörper Würfel K.obj";
  dreh1= cvektor4 (120, 1, 1, 1);
  dreh2= cvektor4 (-180, 1, 0, 0);
  vefk= cvektor3 (1.1, 1.1, 1);
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 0);

  // Th F (Trapezkörper Oktaeder EK)
  objdatei= "Polyeder/472 Th e+F+k  Trapezkörper Oktaeder EK.obj";
  dreh1= cvektor4 (120, 1, 1, 1);
  dreh2= cvektor4 (-180, 1, 0, 0);
  vefk= cvektor3 (1.2, 0.2, 0.1);
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 0);

  // Th F (Trapezkörper Oktaeder E)
  objdatei= "Polyeder/472 Th e+F Trapezkörper Oktaeder E.obj";
  dreh1= cvektor4 (120, 1, 1, 1);
  dreh2= cvektor4 (-180, 1, 0, 0);
  vefk= cvektor3 (1.1, 0.1, 0.1);
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 0);

  // Th F (Trapezkörper Oktaeder K)
  objdatei= "Polyeder/472 Th e+F+k  Trapezkörper Oktaeder K.obj";
  dreh1= cvektor4 (120, 1, 1, 1);
  dreh2= cvektor4 (-180, 1, 0, 0);
  vefk= cvektor3 (1.1, 0.1, 0);
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 0);

  // Th K (Trapezkörper Kuboktaeder EF)
  objdatei= "Polyeder/473 Th e+f+K  Trapezkörper Kuboktaeder EF.obj";
  dreh1= cvektor4 (120, 1, 1, 1);
  dreh2= cvektor4 (-180, 1, 0, 0);
  vefk= cvektor3 (1.2, 1.1, 0.1);
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 0);

  // Th K (Trapezkörper Kuboktaeder E)
  objdatei= "Polyeder/473 Th e+f+K  Trapezkörper Kuboktaeder E.obj";
  dreh1= cvektor4 (120, 1, 1, 1);
  dreh2= cvektor4 (-180, 1, 0, 0);
  vefk= cvektor3 (1.1, 1.1, 0.1);
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 0);

  // Th K (Trapezkörper Kuboktaeder F)
  objdatei= "Polyeder/473 Th e+f+K  Trapezkörper Kuboktaeder F.obj";
  dreh1= cvektor4 (120, 1, 1, 1);
  dreh2= cvektor4 (-180, 1, 0, 0);
  vefk= cvektor3 (1.1, 1, 0);
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 0);

  // Th E+K (Trapezkörper Würfelstumpf F)
  objdatei= "Polyeder/474 Th E+f+K  Trapezkörper Würfelstumpf.obj";
  dreh1= cvektor4 (120, 1, 1, 1);
  dreh2= cvektor4 (-180, 1, 0, 0);
  vefk= cvektor3 (1.1, 1, sqrtl (2) - 1);
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 0);

  // Th F+K (Trapezkörper Ikosaeder E)
  objdatei= "Polyeder/475 Th e+F+K  Trapezkörper Ikosaeder.obj";
  dreh1= cvektor4 (120, 1, 1, 1);
  dreh2= cvektor4 (-180, 1, 0, 0);
  vefk= cvektor3 (gk + 0.1, 1.1, 0.1);
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 0);

  // Th E+F (Trapezkörper Rhombenkuboktaeder K)
  objdatei= "Polyeder/476 Th E+F+k  Trapezkörper Rhombenkuboktaeder.obj";
  dreh1= cvektor4 (120, 1, 1, 1);
  dreh2= cvektor4 (-180, 1, 0, 0);
  vefk= cvektor3 (1.1 + sqrtl (2), 1.1, 1);
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 0);

  // Th E+F+K (Trapezkörper Trapezkörper)
  objdatei= "Polyeder/477 Th E+F+K  Trapezkörper Trapezkörper.obj";
  dreh1= cvektor4 (120, 1, 1, 1);
  dreh2= cvektor4 (-180, 1, 0, 0);
  vefk= cvektor3 (1/sqrtl (3) + sqrtl (0.5) + 1, 1/sqrtl (3) + sqrtl (0.5), 1/sqrtl (3));
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 0);

//----- Sonderkörper ---------------------------------------------------------------------------------------

  // Würfel auf Spitze mit Sechseck
  objdatei= "Polyeder/51 O  E     Würfel Spitze.obj";
  dreh1= cvektor4 (120, 0, 0, 1);
  dreh2= cvektor4 (180, 1, 0, sqrtl (2));
  vefk= cvektor3 (1, 0, 0);
  generiere1polyederobj (objdatei, dreh1, dreh2, vefk, 1, 1);

  }

//-------------------------------------- 3 Drehspiegelungen ------------------------------------------------

void dreh3 ()
  {
  cvektor4 el1, el2, el3;
  cvektor4liste qliste (lmax);
  cbasis3liste bliste (lmax);
  ccluster cluster (1000);

  el1= winkelachseeingabe ();
  el2= winkelachseeingabe ();
  el3= winkelachseeingabe ();

  cbasis3 aw;
  aw.x= cvektor3 (el1.i, el1.j, el1.ij);
  aw.y= cvektor3 (el2.i, el2.j, el2.ij);
  aw.z= cvektor3 (el3.i, el3.j, el3.ij);
  zeigewinkel (aw);
  getchar ();

  // negative Winkel bedeuten positiver Winkel + Inversion (Drehspiegelung)

  if (el1.r < 0)
    {
    el1.r= -el1.r;
    qliste.winkelachsehinzu (-el1);
    bliste.winkelachsespieghinzu (el1);
    }
    else
    {
    qliste.winkelachsehinzu (el1);
    bliste.winkelachsehinzu (el1);
    }
  if (el2.r < 0)
    {
    el2.r= -el2.r;
    qliste.winkelachsehinzu (-el2);
    bliste.winkelachsespieghinzu (el2);
    }
    else
    {
    qliste.winkelachsehinzu (el2);
    bliste.winkelachsehinzu (el2);
    }
  if (el3.r < 0)
    {
    el3.r= -el3.r;
    qliste.winkelachsehinzu (-el3);
    bliste.winkelachsespieghinzu (el3);
    }
    else
    {
    qliste.winkelachsehinzu (el3);
    bliste.winkelachsehinzu (el3);
    }

  qliste.schliesseab ();
  bliste.schliesseab ();

  if (!qliste.uebergelaufen)
    {
    qliste.ermittleordnung ();
    qliste.sortierenachordnung ();
    qliste.ermittlepaarung ();
    }
  if (!bliste.uebergelaufen)
    {
    bliste.ermittleordnung ();
    bliste.sortierenachordnung ();
    bliste.ermittlepaarung ();
    }

  printv4liste (qliste);
  getchar ();
  getchar ();
  printb3liste (bliste);
  getchar ();

  cluster.gruppe->kopiere (bliste);
  cluster.vervollstaendige ();

  printtext ("Gruppe:\n");
  printb3liste (*cluster.gruppe);
  getchar ();
  printtext ("Kern:\n");
  printb3liste (*cluster.kern);
  getchar ();
  printtext ("maxord Gruppe:   ");
  printinteger (cluster.gruppe->maxord);
  printtext ("maxord Kern:   ");
  printinteger (cluster.kern->maxord);
  printtext ("\nPartliste:\n");
  printv3liste (*cluster.partliste);
  printtext ("maximale Zähligkeit:   ");
  printreal (real (cluster.gruppe->maxord));
  printtext ("\n\n");

  printtext ("Kanten:\n");
  printv3liste (*cluster.kliste);
  printtext ("Ecken:\n");
  printv3liste (*cluster.eliste);
  printtext ("Flächen:\n");
  printv3liste (*cluster.fliste);

  printtext ("Spiegelungen:\n");
  printb3liste (*cluster.spieg);
  }

// -----------------------------------------------------------------------------------------------------------
//-------------------------------------- 2 Drehspiegelungen  plus Koordinatendrehung -------------------------

void dreh2k ()
  {
  cvektor4 el1, el2, el3;
  cvektor4liste qliste (lmax);
  cbasis3liste bliste (lmax);
  cvektor3liste vliste (lmax);

  el1= winkelachseeingabe ();
  el2= winkelachseeingabe ();
  el3= winkelachseeingabe ();

  // Drehungen mit Koordinatendrehung drehen
  cbasis3 kdrehb= matrixfromwinkelachse (el3);

  cvektor3 achse1= cvektor3 (el1.i, el1.j, el1.ij);
  cvektor3 achse2= cvektor3 (el2.i, el2.j, el2.ij);
  achse1= achse1/kdrehb;
  achse2= achse2/kdrehb;
  el1.i= achse1.x;
  el1.j= achse1.y;
  el1.ij= achse1.z;
  el2.i= achse2.x;
  el2.j= achse2.y;
  el2.ij= achse2.z;

  if (el1.r < 0)
    {
    el1.r= -el1.r;
    qliste.winkelachsehinzu (-el1);
    bliste.winkelachsespieghinzu (el1);
    }
    else
    {
    qliste.winkelachsehinzu (el1);
    bliste.winkelachsehinzu (el1);
    }
  if (el2.r < 0)
    {
    el2.r= -el2.r;
    qliste.winkelachsehinzu (-el2);
    bliste.winkelachsespieghinzu (el2);
    }
    else
    {
    qliste.winkelachsehinzu (el2);
    bliste.winkelachsehinzu (el2);
    }

  qliste.schliesseab ();
  bliste.schliesseab ();
  if (!qliste.uebergelaufen)
    {
    qliste.ermittleordnung ();
    qliste.sortierenachordnung ();
    qliste.ermittlepaarung ();
    }
  if (!bliste.uebergelaufen)
    {
    bliste.ermittleordnung ();
    bliste.sortierenachordnung ();
    bliste.ermittlepaarung ();
    }

  printv4liste (qliste);
  getchar ();
  getchar ();
  printb3liste (bliste);
  getchar ();
  vliste.elementhinzu (cvektor3 (1, 1, 1), 1);                               // V20 Dodekaeder klein
  vliste.schliesseab (bliste);
  printv3liste (vliste);
  }

// -----------------------------------------------------------------------------------------------------------

//-------------------------------------- 3 Ebenenwinkel ------------------------------------------------

void ebenenwinkel3 ()  // Gruppe aus 3 Ebenenspiegelungen aufbauen
  {
  cvektor4 el1, el2, el3;
  cvektor4liste qliste (lmax);
  cbasis3liste bliste (lmax);
  ccluster cluster (1000);
  cvektor3 wi;

  printtext ("\nWinkel zwischen den Ebenen [0..180°]\n");
  vektor3eingabe (wi);
  wi.x*= M_PIl/180;
  wi.y*= M_PIl/180;
  wi.z*= M_PIl/180;
  cbasis3 sachsen (spiegelachsenvonebenenwinkelk (wi));
  zeigedreibein (sachsen);

  getchar ();
  getchar ();

  el1= cvektor4 (M_PIl, sachsen.x);
  el2= cvektor4 (M_PIl, sachsen.y);
  el3= cvektor4 (M_PIl, sachsen.z);
  
  qliste.winkelachsehinzu (-el1);
  qliste.winkelachsehinzu (-el2);
  qliste.winkelachsehinzu (-el3);

  bliste.winkelachsespieghinzu (el1);
  bliste.winkelachsespieghinzu (el2);
  bliste.winkelachsespieghinzu (el3);

  qliste.schliesseab ();
  bliste.schliesseab ();

  if (!qliste.uebergelaufen)
    {
    qliste.ermittleordnung ();
    qliste.sortierenachordnung ();
    qliste.ermittlepaarung ();
    }
  if (!bliste.uebergelaufen)
    {
    bliste.ermittleordnung ();
    bliste.sortierenachordnung ();
    bliste.ermittlepaarung ();
    }

  printv4liste (qliste);
  getchar ();
  printb3liste (bliste);
  getchar ();

  cluster.gruppe->kopiere (bliste);
  cluster.vervollstaendige ();

  printtext ("Gruppe:\n");
  printb3liste (*cluster.gruppe);
  getchar ();
  printtext ("Kern:\n");
  printb3liste (*cluster.kern);
  getchar ();
  printtext ("maxord Gruppe:   ");
  printinteger (cluster.gruppe->maxord);
  printtext ("maxord Kern:   ");
  printinteger (cluster.kern->maxord);
  printtext ("\nPartliste:\n");
  printv3liste (*cluster.partliste);
  printtext ("maximale Zähligkeit:   ");
  printreal (real (cluster.gruppe->maxord));
  printtext ("\n\n");

  printtext ("Kanten:\n");
  printv3liste (*cluster.kliste);
  printtext ("Ecken:\n");
  printv3liste (*cluster.eliste);
  printtext ("Flächen:\n");
  printv3liste (*cluster.fliste);

  printtext ("Spiegelungen:\n");
  printb3liste (*cluster.spieg);
  }

void ebenenwinkel180 ()                               // 3 180° Drehungen 
  {
  cvektor4 el1, el2, el3;
  cvektor4liste qliste (lmax);
  cbasis3liste bliste (lmax);
  cvektor3liste partliste (lmax);
  cvektor3 wi;

  printf ("\nWinkel zwischen den Ebenen [0..180°]\n");
  vektor3eingabe (wi);
  wi.x*= M_PIl/180;
  wi.y*= M_PIl/180;
  wi.z*= M_PIl/180;
  cbasis3 sachsen (spiegelachsenvonebenenwinkelk (wi));
  zeigedreibein (sachsen);

  getchar ();
  getchar ();

  el1= cvektor4 (M_PIl, sachsen.x);
  el2= cvektor4 (M_PIl, sachsen.y);
  el3= cvektor4 (M_PIl, sachsen.z);
  
  qliste.winkelachsehinzu (el1);
  qliste.winkelachsehinzu (el2);
  qliste.winkelachsehinzu (el3);
  
  bliste.winkelachsehinzu (el1);
  bliste.winkelachsehinzu (el2);
  bliste.winkelachsehinzu (el3);
  
  qliste.schliesseab ();
  bliste.schliesseab ();
  if (!qliste.uebergelaufen)
    {
    qliste.ermittleordnung ();
    qliste.sortierenachordnung ();
    qliste.ermittlepaarung ();
    }
  if (!bliste.uebergelaufen)
    {
    bliste.ermittleordnung ();
    bliste.sortierenachordnung ();
    bliste.ermittlepaarung ();
    }

  ermittlepartvektoren (bliste, partliste);

  printv4liste (qliste);
  printb3liste (bliste);
  printv3liste (partliste);

  }

void ebenenachdreh ()                  // Ebenenwinkel -> Spiegelungen -> Drehungen
  {
  cvektor4 el1, el2, el3;
  cvektor4liste qliste (lmax);
  cbasis3liste bliste (lmax);
  cvektor3liste vliste (lmax);
  cvektor3 wi;

  printf ("\nWinkel zwischen den Ebenen [0..180°]\n");
  vektor3eingabe (wi);
  wi.x*= M_PIl/180;
  wi.y*= M_PIl/180;
  wi.z*= M_PIl/180;
  cbasis3 sachsen (spiegelachsenvonebenenwinkelk (wi));
  zeigedreibein (sachsen);
  // Spiegelachsen von Ebenenwinkel berechnet

  real wis1= 180/M_PIl*winkelg (sachsen.x, sachsen.y);
  real wis2= 180/M_PIl*winkelg (sachsen.x, sachsen.z);
  real wis3= 180/M_PIl*winkelg (sachsen.y, sachsen.z);
  printf ("\nWinkel zwischen den Spiegelachsen: %9.3Lf°%9.3Lf°%9.3Lf°\n", wis1, wis2, wis3);
  printvektor3ord (orientiere (normiere (sachsen.x)), 0);
  printvektor3ord (orientiere (normiere (sachsen.y)), 0);
  printvektor3ord (orientiere (normiere (sachsen.z)), 0);
  printf ("\n");
  cbasis3liste spiegeldrehungen (lmax);
  drehungenvonspiegelungen (spiegeldrehungen, sachsen);
  // Drehungen aus den Spiegelungen berechnet

  cvektor4 wiachs1= (winkelachsefrommatrix (spiegeldrehungen.b[0]));
  cvektor4 wiachs2= (winkelachsefrommatrix (spiegeldrehungen.b[1]));
  cvektor4 wiachs3 (winkelachsefrommatrix (spiegeldrehungen.b[2]));
  cvektor3 achse1= orientiere (normiere (cvektor3 (wiachs1.i, wiachs1.j, wiachs1.ij)));
  cvektor3 achse2= orientiere (normiere (cvektor3 (wiachs2.i, wiachs2.j, wiachs2.ij)));
  cvektor3 achse3 (orientiere (normiere (cvektor3 (wiachs3.i, wiachs3.j, wiachs3.ij))));
  real wid1 (180/M_PIl*winkelg (achse1, achse2));
  real wid2 (180/M_PIl*winkelg (achse1, achse3));
  real wid3 (180/M_PIl*winkelg (achse2, achse3));
  printf ("Winkel zwischen den Drehachsen: %9.3Lf°%9.3Lf°%9.3Lf°\n", wid1, wid2, wid3);
  printb3liste (spiegeldrehungen);
  cvektor4 dreh1, dreh2;
  dreh1= winkelachsefrommatrix (spiegeldrehungen.b[0]);
  dreh2= winkelachsefrommatrix (spiegeldrehungen.b[1]);
  getchar ();
  getchar ();

  qliste.winkelachsehinzu (dreh1);
  qliste.winkelachsehinzu (dreh2);
  bliste.winkelachsehinzu (dreh1);
  bliste.winkelachsehinzu (dreh2);
  qliste.schliesseab ();
  bliste.schliesseab ();
  if (!qliste.uebergelaufen)
    {
    qliste.ermittleordnung ();
    qliste.sortierenachordnung ();
    qliste.ermittlepaarung ();
    }
  if (!bliste.uebergelaufen)
    {
    bliste.ermittleordnung ();
    bliste.sortierenachordnung ();
    bliste.ermittlepaarung ();
    }

  printv4liste (qliste);
  printb3liste (bliste);
  }

void testespiegelebenen2 ()
  {
  cvektor3 wi;
  cbasis3 sachsen;

  printf ("\nWinkel zwischen den Ebenen [0..180°]\n");
  vektor3eingabe (wi);
  wi.x*= M_PIl/180;
  wi.y*= M_PIl/180;
  wi.z*= M_PIl/180;

  // Spiegelachsen von Ebenenwinkel
  sachsen= spiegelachsenvonebenenwinkelk (wi);
  zeigedreibein2 (sachsen);
  sachsen= spiegelachsenvonebenenwinkel2 (wi);
  zeigedreibein2 (sachsen);
  sachsen= spiegelachsenvonebenenwinkel3 (wi);
  zeigedreibein2 (sachsen);
  }

void testestern ()
  {
  real wi;
  cbasis3 stern;

  realeingabe (wi);
  printf ("\n");
  wi*= M_PIl/180;
  stern= getsternbasis (wi);
  zeigedreibein (stern);
  stern= getsternbasis2 (wi);
  zeigedreibein (stern);
  stern= spiegelachsenvonebenenwinkelk (cvektor3 (wi, wi, wi));
  zeigedreibein (stern);
  stern= spiegelachsenvonebenenwinkel2 (cvektor3 (wi, wi, wi));
  zeigedreibein (stern);
  stern= spiegelachsenvonebenenwinkel3 (cvektor3 (wi, wi, wi));
  zeigedreibein (stern);

  getchar ();
  getchar ();

  cvektor4 el1, el2, el3;
  cvektor4liste qliste (lmax);
  cbasis3liste bliste (lmax);
  cvektor3liste vliste (lmax);

  el1= cvektor4 (M_PIl, stern.x);
  el2= cvektor4 (M_PIl, stern.y);
  el3= cvektor4 (M_PIl, stern.z);
  qliste.winkelachsehinzu (-el1);
  qliste.winkelachsehinzu (-el2);
  qliste.winkelachsehinzu (-el3);
  bliste.winkelachsespieghinzu (el1);
  bliste.winkelachsespieghinzu (el2);
  bliste.winkelachsespieghinzu (el3);
//  vliste.elementhinzu (cvektor3 (1), 0);      // Flächen (Dreieckskörper)
//  vliste.elementhinzu (stern.x, 0);              // Kanten
  vliste.elementhinzu (stern.x^stern.y, 0);         // Ecken
  qliste.schliesseab ();
  bliste.schliesseab ();
  vliste.schliesseab (bliste);
  if (!qliste.uebergelaufen)
    {
    qliste.ermittleordnung ();
    qliste.sortierenachordnung ();
    qliste.ermittlepaarung ();
    }
  if (!bliste.uebergelaufen)
    {
    bliste.ermittleordnung ();
    bliste.sortierenachordnung ();
    bliste.ermittlepaarung ();
    }

  printv4liste (qliste);
  getchar ();
  printb3liste (bliste);
  getchar ();
  printv3liste (vliste);
  }

//-------------------------------------- Testematrix ------------------------------------------------------

void testematrix ()
  {
  cvektor4 el, quat;
  cbasis3 drehbasis;
  cvektor3 drehvektor, gdrehvektor;

  el= winkelachseeingabe ();
  vektor3eingabe (drehvektor);

  quat= quaternionfromwinkelachse (el);
  printf ("\nDrehquaternion:\n");
  printvektor4dreh (quat, 0, 0, 0);

  drehbasis= matrixfromquaternion (quat);
  gdrehvektor= drehbasis*drehvektor;
  printf ("\nDrehmatrix:\n");
  printbasis3dreh (drehbasis, 0, 0, 0);
  printbasis3mat (drehbasis, 0, 0);
  printf ("\ngedrehter Vektor:\n");
  printvektor3wi (gdrehvektor, 0);

  quat= quaternionfrommatrix (drehbasis);
  printf ("\nDrehquaternion aus Drehmatrix:\n");
  printvektor4dreh (quat, 0, 0, 0);
  printf ("\n");
  }

void testematrixalt ()
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
  vliste.elementhinzu (spiegachse, 0);
  vliste.schliesseab (bliste);
  printv3liste (vliste);
  }

//-------------------------------------- Testespiegelung ------------------------------------------------------
void  testespiegelung ()
  {
  cvektor3 spiegachse;
  vektor3eingabe (spiegachse);
  cbasis3 spiegbasis (getspiegbasis (spiegachse));  // Spiegelungsmatrix
  cbasis3 drehspiegbasis (getdrehspiegbasis (spiegachse));  // Spiegelungsmatrix

  cvektor3 gspiegachse (spiegbasis*spiegachse);      // gespiegelte Spiegelachse
  cvektor3 gdrehspiegachse (drehspiegbasis*spiegachse);      // drehgespiegelte Spiegelachse
  printf ("Spiegelachse:\n");
  printvektor3ord (spiegachse, 0);               // Spiegelachse ausgeben
  printf ("\n");
  printf ("Spiegelmatrix:\n");
  printbasis3mat (spiegbasis, 0, 0);              // Spiegelmatrix ausgeben
  printf ("\n");
  printf ("Drehspiegelmatrix:\n");
  printbasis3mat (drehspiegbasis, 0, 0);              // Drehspiegelmatrix ausgeben
  printf ("\n");
  printf ("gespiegelte Spiegelachse:\n");
  printvektor3ord (gspiegachse, 0);                   // gespiegelte Spiegelachse ausgeben
  printf ("\n");
  printf ("drehgespiegelte Spiegelachse:\n");
  printvektor3ord (gdrehspiegachse, 0);                   // drehgespiegelte Spiegelachse ausgeben
  printf ("\n");
  printf ("Determinante Spiegelmatrix: %12Lf\n", det (spiegbasis));   // Determinante Spiegelmatrix
  printf ("\n");
  printf ("Determinante Drehspiegelmatrix: %12Lf\n", det (drehspiegbasis));   // Determinante Spiegelmatrix
  printf ("\n");
  cbasis3 spiegmetrik (cvektor3 (spiegbasis.x%spiegbasis.x, spiegbasis.x%spiegbasis.y, spiegbasis.x%spiegbasis.z), cvektor3 (spiegbasis.y%spiegbasis.x, spiegbasis.y%spiegbasis.y, spiegbasis.y%spiegbasis.z), cvektor3 (spiegbasis.z%spiegbasis.x, spiegbasis.z%spiegbasis.y, spiegbasis.z%spiegbasis.z));
  cbasis3 drehspiegmetrik (cvektor3 (drehspiegbasis.x%drehspiegbasis.x, drehspiegbasis.x%drehspiegbasis.y, drehspiegbasis.x%drehspiegbasis.z), cvektor3 (drehspiegbasis.y%drehspiegbasis.x, drehspiegbasis.y%drehspiegbasis.y, drehspiegbasis.y%drehspiegbasis.z), cvektor3 (drehspiegbasis.z%drehspiegbasis.x, drehspiegbasis.z%drehspiegbasis.y, drehspiegbasis.z%drehspiegbasis.z));
  printf ("Metrik Spiegelmatrix:\n");
  printbasis3mat (spiegmetrik, 0, 0);              // Metrikmatrix ausgeben
  printf ("\n");
  printf ("Metrik Drehspiegelmatrix:\n");
  printbasis3mat (drehspiegmetrik, 0, 0);              // Metrikmatrix ausgeben
  printf ("\n");
  cbasis3 spiegquad (spiegbasis*spiegbasis);
  cbasis3 drehspiegquad (drehspiegbasis*drehspiegbasis);
  printf ("Quadrat der Spiegelungsmatrix:\n");
  printbasis3mat (spiegquad, 0, 0);                 // Quadrat der Spiegelungsmatrix ausgeben
  printf ("\n");
  printf ("Quadrat der Drehspiegelungsmatrix:\n");
  printbasis3mat (drehspiegquad, 0, 0);                 // Quadrat der Spiegelungsmatrix ausgeben
  printf ("\n");
  cvektor3 spiegachseb (getspiegachse (spiegbasis));
  printf ("mit getspiegachse berechnete Spiegelachse der Spiegelungsmatrix:\n");
  printvektor3ord (spiegachseb, 0);               // berechnete Spiegelachse ausgeben
  printf ("\n");
  cvektor4 achsew (winkelachsefrommatrix (-spiegbasis));
  cvektor3 spiegachsec;
  spiegachsec.x= achsew.i;
  spiegachsec.y= achsew.j;
  spiegachsec.z= achsew.ij;
  printf ("mit winkelachsefrommatrix berechnete Drehachse der negativen Spiegelungsmatrix:\n");
  printvektor3ord (spiegachsec, 0);               // berechnete Spiegelachse ausgeben
  cvektor3 gespeigen (spiegbasis*spiegachseb);
  cvektor3 gespeigen2 (drehspiegbasis*spiegachseb);
  printf ("\n");
  printf ("gespiegelte mit getspiegachse berechnete Spiegelachse:\n");
  printvektor3ord (gespeigen, 0);                 // gespiegelte berechnete Spiegelachse ausgeben
  printf ("\n");
  printf ("drehgespiegelte mit getspiegachse berechnete Spiegelachse:\n");
  printvektor3ord (gespeigen2, 0);                 // gespiegelte berechnete Spiegelachse ausgeben
  printf ("\n");
  }

void  testekonvertierung23 ()
  {
  cvektor4 wiachs1, wiachs2;
  wiachs1= winkelachseeingabe ();
  wiachs2= winkelachseeingabe ();
  wiachs1= winkelachsefrommatrix (matrixfromwinkelachse (wiachs1));
  wiachs2= winkelachsefrommatrix (matrixfromwinkelachse (wiachs2));
  cvektor3 achse1= orientiere (normiere (cvektor3 (wiachs1.i, wiachs1.j, wiachs1.ij)));
  cvektor3 achse2= orientiere (normiere (cvektor3 (wiachs2.i, wiachs2.j, wiachs2.ij)));
  real wiz= 180/M_PIl*winkelg (achse1, achse2);

  printf ("Drehachsen: %9.3Lf°\n", wiz);
  printvektor3wi (achse1, wiachs1.r);
  printvektor3wi (achse2, wiachs2.r);

  cbasis3liste drehspiegelungen (lmax);
  spiegelungenvondrehungen (drehspiegelungen, wiachs1, wiachs2);
  cbasis3 spiegachsen;
  spiegachsen.x= getspiegachse (drehspiegelungen.b[0]);
  spiegachsen.y= getspiegachse (drehspiegelungen.b[1]);
  spiegachsen.z= getspiegachse (drehspiegelungen.b[2]);
  real wis1= 180/M_PIl*winkelg (spiegachsen.x, spiegachsen.y);
  real wis2= 180/M_PIl*winkelg (spiegachsen.x, spiegachsen.z);
  real wis3= 180/M_PIl*winkelg (spiegachsen.y, spiegachsen.z);
  printf ("\nSpiegelachsen: %9.3Lf°%9.3Lf°%9.3Lf°\n", wis1, wis2, wis3);
  printb3liste (drehspiegelungen);

  cbasis3liste spiegeldrehungen (lmax);
  drehungenvonspiegelungen (spiegeldrehungen, spiegachsen);
  wiachs1= (winkelachsefrommatrix (spiegeldrehungen.b[0]));
  wiachs2= (winkelachsefrommatrix (spiegeldrehungen.b[1]));
  cvektor4 wiachs3 (winkelachsefrommatrix (spiegeldrehungen.b[2]));
  achse1= orientiere (normiere (cvektor3 (wiachs1.i, wiachs1.j, wiachs1.ij)));
  achse2= orientiere (normiere (cvektor3 (wiachs2.i, wiachs2.j, wiachs2.ij)));
  cvektor3 achse3 (orientiere (normiere (cvektor3 (wiachs3.i, wiachs3.j, wiachs3.ij))));
  real wid1 (180/M_PIl*winkelg (achse1, achse2));
  real wid2 (180/M_PIl*winkelg (achse2, achse3));
  real wid3 (180/M_PIl*winkelg (achse3, achse1));
  printf ("Drehachsen: %9.3Lf°%9.3Lf°%9.3Lf°\n", wid1, wid2, wid3);
  printb3liste (spiegeldrehungen);
  }

void  testekonvertierung32 ()
  {
  cbasis3 spiegachsen;
  vektor3eingabe (spiegachsen.x);
  vektor3eingabe (spiegachsen.y);
  vektor3eingabe (spiegachsen.z);
  real wis1= 180/M_PIl*winkelg (spiegachsen.x, spiegachsen.y);
  real wis2= 180/M_PIl*winkelg (spiegachsen.x, spiegachsen.z);
  real wis3= 180/M_PIl*winkelg (spiegachsen.y, spiegachsen.z);
  printf ("\nSpiegelachsen: %9.3Lf°%9.3Lf°%9.3Lf°\n", wis1, wis2, wis3);
  printvektor3ord (orientiere (normiere (spiegachsen.x)), 0);
  printvektor3ord (orientiere (normiere (spiegachsen.y)), 0);
  printvektor3ord (orientiere (normiere (spiegachsen.z)), 0);
  printf ("\n");
  cbasis3liste spiegeldrehungen (lmax);
  drehungenvonspiegelungen (spiegeldrehungen, spiegachsen);
  cvektor4 wiachs1= (winkelachsefrommatrix (spiegeldrehungen.b[0]));
  cvektor4 wiachs2= (winkelachsefrommatrix (spiegeldrehungen.b[1]));
  cvektor4 wiachs3 (winkelachsefrommatrix (spiegeldrehungen.b[2]));
  cvektor3 achse1= orientiere (normiere (cvektor3 (wiachs1.i, wiachs1.j, wiachs1.ij)));
  cvektor3 achse2= orientiere (normiere (cvektor3 (wiachs2.i, wiachs2.j, wiachs2.ij)));
  cvektor3 achse3 (orientiere (normiere (cvektor3 (wiachs3.i, wiachs3.j, wiachs3.ij))));
  real wid1 (180/M_PIl*winkelg (achse1, achse2));
  real wid2 (180/M_PIl*winkelg (achse1, achse3));
  real wid3 (180/M_PIl*winkelg (achse2, achse3));
  printf ("Drehachsen: %9.3Lf°%9.3Lf°%9.3Lf°\n", wid1, wid2, wid3);
  printb3liste (spiegeldrehungen);
  cvektor4 dreh1, dreh2;
  dreh1= winkelachsefrommatrix (spiegeldrehungen.b[0]);
  dreh2= winkelachsefrommatrix (spiegeldrehungen.b[1]);
  cbasis3liste drehspiegelungen (lmax);
  spiegelungenvondrehungen (drehspiegelungen, dreh1, dreh2);
  spiegachsen.x= getspiegachse (drehspiegelungen.b[0]);
  spiegachsen.y= getspiegachse (drehspiegelungen.b[1]);
  spiegachsen.z= getspiegachse (drehspiegelungen.b[2]);
  wis1= 180/M_PIl*winkelg (spiegachsen.x, spiegachsen.y);
  wis2= 180/M_PIl*winkelg (spiegachsen.x, spiegachsen.z);
  wis3= 180/M_PIl*winkelg (spiegachsen.y, spiegachsen.z);
  printf ("\nSpiegelachsen: %9.3Lf°%9.3Lf°%9.3Lf°\n", wis1, wis2, wis3);
  printb3liste (drehspiegelungen);
  }

void testespiegelebenen ()
  {
  cvektor3 wi;
  cbasis3 sachsen;
  real wixy, wiyz, wizx;

  printf ("\nWinkel zwischen den Ebenen [0..180°]\n");
  vektor3eingabe (wi);
  wi.x*= M_PIl/180;
  wi.y*= M_PIl/180;
  wi.z*= M_PIl/180;

  sachsen= spiegelachsenvonebenenwinkele (wi);
  printvektor3ord (sachsen.x, 0);
  printvektor3ord (sachsen.y, 0);
  printvektor3ord (sachsen.z, 0);
  wixy= 180/M_PIl*winkelb (sachsen.x, sachsen.y);
  wiyz= 180/M_PIl*winkelb (sachsen.y, sachsen.z);
  wizx= 180/M_PIl*winkelb (sachsen.z, sachsen.x);
  printf ("\nWinkel xy, yz, zx: %9.3Lf°%9.3Lf°%9.3Lf°\n", wixy, wizx, wiyz);

  sachsen= spiegelachsenvonebenenwinkel2 (wi);
  printvektor3ord (sachsen.x, 0);
  printvektor3ord (sachsen.y, 0);
  printvektor3ord (sachsen.z, 0);
  wixy= 180/M_PIl*winkelb (sachsen.x, sachsen.y);
  wiyz= 180/M_PIl*winkelb (sachsen.y, sachsen.z);
  wizx= 180/M_PIl*winkelb (sachsen.z, sachsen.x);
  printf ("\nWinkel xy, yz, zx: %9.3Lf°%9.3Lf°%9.3Lf°\n", wixy, wizx, wiyz);

  sachsen= spiegelachsenvonebenenwinkel3 (wi);
  printvektor3ord (sachsen.x, 0);
  printvektor3ord (sachsen.y, 0);
  printvektor3ord (sachsen.z, 0);
  wixy= 180/M_PIl*winkelb (sachsen.x, sachsen.y);
  wiyz= 180/M_PIl*winkelb (sachsen.y, sachsen.z);
  wizx= 180/M_PIl*winkelb (sachsen.z, sachsen.x);
  printf ("\nWinkel xy, yz, zx: %9.3Lf°%9.3Lf°%9.3Lf°\n", wixy, wizx, wiyz);

  sachsen= spiegelachsenvonebenenwinkelk (wi);
  printvektor3ord (sachsen.x, 0);
  printvektor3ord (sachsen.y, 0);
  printvektor3ord (sachsen.z, 0);
  wixy= 180/M_PIl*winkelb (sachsen.x, sachsen.y);
  wiyz= 180/M_PIl*winkelb (sachsen.y, sachsen.z);
  wizx= 180/M_PIl*winkelb (sachsen.z, sachsen.x);
  printf ("\nspiegelachsenvonebenenwinkelk:       Winkel xy, yz, zx: %9.3Lf°%9.3Lf°%9.3Lf°\n", wixy, wizx, wiyz);

  sachsen= getsternbasis (wi.x);
  printvektor3ord (sachsen.x, 0);
  printvektor3ord (sachsen.y, 0);
  printvektor3ord (sachsen.z, 0);
  wixy= 180/M_PIl*winkelb (sachsen.x, sachsen.y);
  wiyz= 180/M_PIl*winkelb (sachsen.y, sachsen.z);
  wizx= 180/M_PIl*winkelb (sachsen.z, sachsen.x);
  printf ("\nWinkel xy, yz, zx: %9.3Lf°%9.3Lf°%9.3Lf°\n", wixy, wizx, wiyz);

  sachsen= getsternbasis2 (wi.x);
  printvektor3ord (sachsen.x, 0);
  printvektor3ord (sachsen.y, 0);
  printvektor3ord (sachsen.z, 0);
  wixy= 180/M_PIl*winkelb (sachsen.x, sachsen.y);
  wiyz= 180/M_PIl*winkelb (sachsen.y, sachsen.z);
  wizx= 180/M_PIl*winkelb (sachsen.z, sachsen.x);
  printf ("\nWinkel xy, yz, zx: %9.3Lf°%9.3Lf°%9.3Lf°\n", wixy, wizx, wiyz);

  }

void testevektordreh ()
  {
  cvektor4 dq, z1, z2;
  cvektor3 dv, v1, v2;
  cbasis3 dm, eig;


  dq= winkelachseeingabe ();
  dq= quaternionfromwinkelachse (dq);
  vektor3eingabe (dv);
  dm= matrixfromquaternion (dq);
  eig= dm;
  eig.x.x-= 1;
  eig.y.y-= 1;
  eig.z.z-= 1;
  eig= transp (cbasis3 (eig.y^eig.z, eig.z^eig.x, eig.x^eig.y));


  printf ("Drehmatrix\n");
  printbasis3mat (dm, 0, 0);
  printf ("Eigenwertmatrix\n");
  printbasis3mat (eig, 0, 0);

  z1= quaternionfrommatrix (dm);
  z2= quaternionfrommatrix2 (dm);

  printf ("\nquaternionfrommatrix1 quaternionfrommatrix2\n");
  printvektor4quat (z1, 0, 0);
  printvektor4quat (z2, 0, 0);

  v1= dm*dv;
  printf ("\nMatrix mal Vektor\n");
  printvektor3ord (v1, 0);

  v2= z2*dv;
  printf ("\nQuaternion mal Vektor\n");
  printvektor3ord (v2, 0);
  printf ("\n");
  }

integer entscheidungseingabe ()
  {
  integer ent;
  printf ("\n");
  printf (" [1] Drehungen      [2] Drehmultiplikation  [3] Division                [4] Testespiegelung  [5] Testematrix     [6] 2 Drehspiegelungen      [66] EFK objDatei            [7] 3 Drehspiegelungen\n");
  printf (" [8] Dreh -> Spieg  [9] Spieg -> Dreh      [10] 3 Spiegelebenenwinkel  [11] 3 gleiche Spiegelebenenwinkel\n");
  printf ("[12]  2 Drehungen + Koordinatendrehung     [13] Ebenenwinkel -> Spiegelachsenwinkel   [14] 3 Drehebenenwinkel   [15] 3 Ebenespieg -> Dreh    [16] Testespiegelebenen     [17] Testeqv      ");
  printf ("[20] Generiere Polyeder    ");
  scanret= scanf ("%lld", &ent);
  return ent;
  }

/*

float         8 Stellen
double       16 Stellen
long double  20 Stellen
__float128   35 Stellen

*/


//--------------------- Hauptprogramm ----------------------------------------------

int main ()
  {

/*
  zahl1010 zahl;
  long double wert= 128.343;
  zahl.erstelle (wert);

  printf ("%50.40Lf\n\n", wert);
  zahl.print (7);
  zahl.printobj (7);
  printf ("\n\n");
  exit(0);
*/

/*
  cbasis3 b1 (cvektor3 (0.309016994,  0.500000000, -0.809016994), cvektor3 (-0.500000000,  0.809016994,  0.309016994), cvektor3 (0.809016994,  0.309016994,     0.500000000 ));
  cbasis3 b2 (cvektor3 (-0.500000000,  0.809016994,  0.309016994), cvektor3 (0.809016994,  0.309016994,  0.500000000), cvektor3 (-0.309016994, -0.500000000,     0.809016994));
  printbasis3dreh (b1, 0, 0, 0);
  printbasis3dreh (b2, 0, 0, 0);
*/

  integer ent (entscheidungseingabe ());
  switch (ent)
    {
    case 1:
      dreh1 ();
      //testedrehungen ();
      break;
    case 2:
      drehmul ();
      break;
    case 3:
      testedivision ();
      break;
    case 4:
      testespiegelung ();
      break;
    case 5:
      testematrix ();
      break;
    case 6:
      dreh2 ();
      break;
    case 66:
      dreh2efk ();
      break;
    case 20:
      generierepolyederobj ();
      break;
    case 7:
      dreh3 ();
      break;
    case 8:
      testekonvertierung23 ();
      break;
    case 9:
      testekonvertierung32 ();
      break;
    case 10:
      ebenenwinkel3 ();          // 3 Spiegelungen
      break;
    case 11:
      testestern ();
      break;
    case 12:
      dreh2k ();
      break;
    case 13:
      testespiegelebenen ();
      break;
    case 14:
      ebenenwinkel180 ();  // 3 180° Drehungen direkt
      break;
    case 15:
      ebenenachdreh ();
      break;
    case 16:
      testespiegelebenen2 ();
      break;
    case 17:
      testevektordreh ();
      break;
    }
  printtext ("");
  return 0;
  }

