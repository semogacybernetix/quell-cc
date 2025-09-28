// Dieses Programm berechnet einen LCR-Serienschwingkreis
// es dient zur Berechnung der Resonanzkurve von Antennen
// die Antenne wird als LCR-Serienschwingkreis aufgefasst. R ist der Strahlungswiderstand

#include <cstdio>
#include <cmath>

#include "../class/vektor.h"

using namespace std;

void dateneingabe (float& pu, float& pl, float& pc, float& pr, float& pf)
  {
  printf ("\n");
  printf ("Ugesamt (V):   ");
  scanf ("%f", &pu);
  printf ("L (H):         ");
  scanf ("%f", &pl);
  printf ("C (F):         ");
  scanf ("%f", &pc);
  printf ("R (Ohm):       ");
  scanf ("%f", &pr);
  printf ("Frequenz (Hz): ");
  scanf ("%f", &pf);
  printf ("\n");
  }
  
void datenausgabe (float pug, float pl, float pc, float pr, float pf, float pfr,
                   cvektor2 pig, cvektor2 pzl, cvektor2 pzc, cvektor2 pzr,
				   cvektor2 pul, cvektor2 puc, cvektor2 pur, cvektor2 psl, cvektor2 psc, cvektor2 psr)
  {
  printf ("Uges:                 %24.9f V\n", pug);
  printf ("L:                    %24.9f µH\n", pl*1e6);
  printf ("C:                    %24.9f pF\n", pc*1e12);
  printf ("R:                    %24.9f Ohm\n", pr);
  printf ("f:                    %24.9f MHz\n", pf*1e-6);
  printf ("\n");
  printf ("fRes:                 %24.9f MHz\n", pfr*1e-6);
  printf ("Iges:                 %24.9f %24.9f\n", pig.x, pig.y);
  printf ("\n");
  printf ("ZL:                   %24.9f %24.9f\n", pzl.x, pzl.y);
  printf ("ZC:                   %24.9f %24.9f\n", pzc.x, pzc.y);
  printf ("ZR:                   %24.9f %24.9f\n", pzr.x, pzr.y);
  printf ("\n");
  printf ("UL:                   %24.9f %24.9f\n", pul.x, pul.y);
  printf ("UC:                   %24.9f %24.9f\n", puc.x, puc.y);
  printf ("UR:                   %24.9f %24.9f\n", pur.x, pur.y);
  printf ("\n");
  printf ("SL:                   %24.9f %24.9f\n", psl.x, psl.y);
  printf ("SC:                   %24.9f %24.9f\n", psc.x, psc.y);
  printf ("SR:                   %24.9f %24.9f\n", psr.x, psr.y);
  printf ("\n");
  }
  
 void rechneserienschwingkreis ()
  {
  float pu, pl, pc, pr, pf;
  cvektor2 uges, zges, iges, ul, uc, ur, zl, zc, zr, sl, sc, sr;
  dateneingabe (pu, pl, pc, pr, pf);
  float w= 2*M_PI*pf;
  float fr= 1/(2*M_PI*sqrt (pl*pc));
  zl.x= 0;
  zl.y= w*pl;
  zc.x= 0;
  zc.y= -1/(w*pc);
  zr.x= pr;
  zr.y= 0;
  zges= zl + zc + zr;
  uges.x= pu;
  uges.y= 0;
  iges= uges/zges;
  ul= iges*zl;
  uc= iges*zc;
  ur= iges*zr;
  sl= ul*~iges/2;
  sc= uc*~iges/2;
  sr= ur*~iges/2;
  datenausgabe (pu, pl, pc, pr, pf, fr, iges, zl, zc, zr, ul, uc, ur, sl, sc, sr);
  }

int main ()
  {
  rechneserienschwingkreis ();
  return 0;
  }
