// Dieses Programm berechnet Legierungsbestandteile

#include "../class/vektor.h"

#include <cstdio>

void kupferpluslegierung ()
  {
  printf ("\n");
  
  long double zinnanf;
  printf ("  Zinngehalt Ausgangslegierung [Prozent]:  ");
  scanf ("%Lf", &zinnanf);
  zinnanf*=0.01;
  
  long double zinnend;
  printf ("  Kupferatome pro Zinnatom:                ");
  scanf ("%Lf", &zinnend);
  //zinnend*=0.01;
  zinnend= 118.71/(118.71 + zinnend*63.546);
  
  long double kupferanf;
  printf ("  Kupfergewicht:                           ");
  scanf ("%Lf", &kupferanf);
  
  long double leganf;
  leganf= kupferanf/(zinnanf/zinnend*(1 - zinnend) - (1 - zinnanf));
  long double legend;
  legend= leganf*zinnanf/zinnend;
  
  printf ("\n");
  printf ("\n");
  printf ("\n");
  printf ("  Gewicht Ausgangslegierung:                     %18.3Lf g\n", leganf);
  printf ("  Gewicht Endlegierung:                          %18.3Lf g\n", legend);

  long double endlegkupfer, endlegzinn, endleggew, endleggehkupfer, endleggehzinn;
  endlegkupfer= kupferanf + leganf*(1 - zinnanf);
  endlegzinn= leganf*zinnanf;
  endleggew= endlegkupfer + endlegzinn;
  endleggehkupfer= endlegkupfer/endleggew;
  endleggehzinn= endlegzinn/endleggew;

  printf ("\n");
  printf ("  Gewicht Endlegierung                           %18.3Lf g\n", endleggew);
  printf ("  Zinngehalt                                     %18.2Lf Prozent\n", endleggehzinn*100);
  printf ("  Kupfergehalt                                   %18.2Lf Prozent\n", endleggehkupfer*100);
  printf ("\n");
  }
  
void dreilegierungen ()
  {
  printf ("\n");
  
  long double zinn1;
  printf ("  Zinngehalt 1. Legierung[Prozent]:     ");
  scanf ("%Lf", &zinn1);
  zinn1*=0.01;
  
  long double zinn2;
  printf ("  Zinngehalt 2. Legierung[Prozent]:     ");
  scanf ("%Lf", &zinn2);
  zinn2*=0.01;
  
  long double zinn3;
  printf ("  Zinngehalt Summenlegierung[Prozent]:  ");
  scanf ("%Lf", &zinn3);
  zinn3*=0.01;
    
  long double gew1;
  printf ("  Gewicht 1. Legierung:                 ");
  scanf ("%Lf", &gew1);
    
  // Homogenes 3-dimensionales System
  cvektor3 leg1 (1 - zinn1, zinn1, 0);
  cvektor3 leg2 (1 - zinn2, zinn2, 0);
  cvektor3 leg3 (1 - zinn3, zinn3, 0);
  cvektor3 endleg (geteigen (cbasis3 (leg1, leg2, leg3)));
  endleg= (gew1/endleg.x)*endleg;
  
  printf ("\n");
  printf ("homogenes 3-dimensionales System\n");
  printf ("\n");
  printf ("  Gewicht 1. Legierung:                          %18.3f g\n", endleg.x);
  printf ("  Gewicht 2. Legierung:                          %18.3f g\n", endleg.y);
  printf ("  Gewicht Summenlegierung:                       %18.3f g\n", -endleg.z);

  // inhomogenes 2-dimensionales System
  cvektor2 legi1 (1 - zinn1, zinn1);
  cvektor2 legi2 (1 - zinn2, zinn2);
  cvektor2 legi3 (1 - zinn3, zinn3);
  cvektor2 endlegi (legi3/cbasis2 (legi1, legi2));
  float endlegigew= gew1/endlegi.x;
  endlegi= endlegigew*endlegi;

  printf ("\n");
  printf ("inhomogenes 2-dimensionales System\n");
  printf ("\n");
  printf ("  Gewicht 1. Legierung:                          %18.3f g\n", endlegi.x);
  printf ("  Gewicht 2. Legierung:                          %18.3f g\n", endlegi.y);
  printf ("  Gewicht Summenlegierung:                       %18.3f g\n", endlegigew);
  printf ("\n");
  }
  
void kupfersilberzinn ()
  {
  printf ("\n");
  
  long double atomcu;
  printf ("  Atome Kupfer[Anzahl]:     ");
  scanf ("%Lf", &atomcu);
  
  long double atomag;
  printf ("  Atome Silber[Anzahl]:     ");
  scanf ("%Lf", &atomag);
  
  long double atomsn;
  printf ("  Atome Zinn[Anzahl]:       ");
  scanf ("%Lf", &atomsn);
  
  long double gewag;
  printf ("  Gewicht Silber[Gramm]:    ");
  scanf ("%Lf", &gewag);
  
  long double legsn;
  printf ("  Zinngehalt der Zinnlegierung[Prozent]:    ");
  scanf ("%Lf", &legsn);
  legsn*= 0.01;
  
// Atomanzahlen der Legierungselemente ausrechnen
  
  long double molag= gewag/107.868;
  long double molcu= molag/atomag*atomcu;
  long double molsn= molag/atomag*atomsn;
  
// Gewichte der Legierungselemente ausrechnen

  long double gewcu= molcu*63.546;
  long double gewsn= molsn*118.710;
//  long double gewcusn= gewcu + gewsn;
  long double gewcuagsn= gewcu + gewag + gewsn;
  
// Gewichte der Legierungselemente ausgeben

  printf ("\n");
  printf ("  Gewicht Kupfer:      %18.3Lf g\n", gewcu);
  printf ("  Gewicht Silber:      %18.3Lf g\n", gewag);
  printf ("  Gewicht Zinn:        %18.3Lf g\n", gewsn);
  printf ("  Gewicht Legierung:   %18.3Lf g\n", gewcuagsn);
  
// Kupfer und Zinn aus Kupfer und Kupfer-Zinn-Legierung zusammensetzen

  cvektor2 vlegcu (1, 0);
  cvektor2 vlegsn (1 - legsn, legsn);
  cvektor2 vlegcusn (gewcu, gewsn);
  cvektor2 vendlegi (vlegcusn/cbasis2 (vlegcu, vlegsn));

// Anteile Kupfer und Kupfer-Zinn-Legierung ausgeben

  printf ("\n");
  printf ("  Gewicht Kupfer:              %18.3f g\n", vendlegi.x);
  printf ("  Gewicht CuSn Legierung:      %18.3f g\n", vendlegi.y);
  printf ("\n");
  return;
  }
  
void legierungenprozent ()
  {
  printf ("\n");
  
  long double proz1;
  printf ("  Gehalt 1. Legierung[Prozent]:     ");
  scanf ("%Lf", &proz1);
  
  long double proz2;
  printf ("  Gehalt 2. Legierung[Prozent]:     ");
  scanf ("%Lf", &proz2);
  
  long double proz3;
  printf ("  Gehalt 3. Legierung[Prozent]:     ");
  scanf ("%Lf", &proz3);

// Legierungszusammensetzung nach Formel ausrechnen

  float prozfx= (proz3 - proz2)/(proz1 - proz2);
  float prozfy= (proz3 - proz1)/(proz2 - proz1);

// Legierungszusammensetzung mit Vektoren ausrechnen

  proz1*= 0.01;
  proz2*= 0.01;
  proz3*= 0.01;
  
// Legierungszusammensetzung ausrechnen

  cvektor2 vleg1 (proz1, 1 - proz1);
  cvektor2 vleg2 (proz2, 1 - proz2);
  cvektor2 vleg3 (proz3, 1 - proz3);
  cvektor2 vprozent (vleg3/cbasis2 (vleg1, vleg2));

// Anteile Kupfer und Kupfer-Zinn-Legierung ausgeben

  printf ("\n");
  printf ("  Prozent 1. Legierung (Formel)%18.3f Prozent\n", prozfx*100);
  printf ("  Prozent 2. Legierung (Formel)%18.3f Prozent\n", prozfy*100);
  printf ("\n");
  printf ("  Prozent 1. Legierung         %18.3f Prozent\n", vprozent.x*100);
  printf ("  Prozent 2. Legierung         %18.3f Prozent\n", vprozent.y*100);
  printf ("\n");
  return;
  }
  
signed long entscheidungseingabe ()
  {
  signed long ent;
  printf ("\n");
  printf ("[1]  Kupfer + Legierung eingeben        [2]  3 Legierungen eingeben        [3]  3 Kupfer Silber Zinn\n");
  printf ("[4]  Legierungen prozentual ");
  scanf ("%ld", &ent);
  return ent;
  }

int main ()
  {
  signed long ent;
  ent= entscheidungseingabe ();
  switch (ent)
    {
	case 1:
    kupferpluslegierung ();
	break;
    case 2:
    dreilegierungen ();
	break;
    case 3:
    kupfersilberzinn ();
	break;
    case 4:
    legierungenprozent ();
	break;
	}
  return 0;
  }
