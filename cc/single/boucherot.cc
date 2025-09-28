// Dieses Programm berechnet die Leuchtstofflampenschaltung mit Boucherotglied, Resonanztrafo, Serienschwingkreis

#include "../class/vektor.h"

#include <cstdio>

void dateneingabe (float& pu, float& pi, float& pf, float& pb)
  {
  printf ("\n");
  printf ("Brückenspannung(V):   ");
  scanf ("%f", &pu);
  printf ("Lampenstrom(A):       ");
  scanf ("%f", &pi);
  printf ("Resonanzfrequenz(Hz): ");
  scanf ("%f", &pf);
  printf ("Lampenspannung(V):    ");
  scanf ("%f", &pb);
  printf ("\n");
  }
  
void datenausgabe (float pL, float pC, float pR, float pQ, cvektor2 pXL, cvektor2 pXC,
                   cvektor2 pur, cvektor2 pir, cvektor2 puc, cvektor2 pic, cvektor2 pul, cvektor2 pil,
 				   cvektor2 pX, cvektor2 pSR, cvektor2 pSC, cvektor2 pSL, cvektor2 pS,
				   cvektor2 pugil, cvektor2 puluc, cvektor2 piric, cvektor2 pulil,
				   cvektor2 suq, cvektor2 siq)
  {
  printf ("L:                    %24.9f µH\n", pL*1e6);
  printf ("C:                    %24.9f nF\n", pC*1e9);
  printf ("R:                    %24.9f Ohm\n", pR);
  printf ("Q:                    %24.9f\n", pQ);
  printf ("\n");
  printf ("XL:                   %24.9f %24.9f\n", pXL.x, pXL.y);
  printf ("XC:                   %24.9f %24.9f\n", pXC.x, pXC.y);
  printf ("\n");
  printf ("UR:                   %24.9f %24.9f\n", pur.x, pur.y);
  printf ("IR:                   %24.9f %24.9f\n", pir.x, pir.y);
  printf ("\n");
  printf ("UC:                   %24.9f %24.9f\n", puc.x, puc.y);
  printf ("IC:                   %24.9f %24.9f\n", pic.x, pic.y);
  printf ("\n");
  printf ("UL:                   %24.9f %24.9f\n", pul.x, pul.y);
  printf ("IL:                   %24.9f %24.9f\n", pil.x, pil.y);
  printf ("\n");
  printf ("Zges:                 %24.9f %24.9f\n", pX.x, pX.y);
  printf ("Sges:                 %24.9f %24.9f\n", pS.x, pS.y);
  printf ("SR:                   %24.9f %24.9f\n", pSR.x, pSR.y);
  printf ("SC:                   %24.9f %24.9f\n", pSC.x, pSC.y);
  printf ("SL:                   %24.9f %24.9f\n", pSL.x, pSL.y);
  printf ("\n");
  printf ("Konsistenzprüfung:\n");
  printf ("Uges/Iges= Zges:      %24.9f %24.9f\n", pugil.x, pugil.y);
  printf ("UL + UC= U:           %24.9f %24.9f\n", puluc.x, puluc.y);
  printf ("IR + IC= IL:          %24.9f %24.9f\n", piric.x, piric.y);
  printf ("UL/IL= XL:            %24.9f %24.9f\n", pulil.x, pulil.y);
  printf ("S = |U|²/(2*conj(Z))  %24.9f %24.9f\n", suq.x, suq.y);
  printf ("S = |I|²*Z/2          %24.9f %24.9f\n", siq.x, siq.y);
  printf ("\n");
  }
  
 void rechneboucherot ()
  {
  float pu, pi, pf, pb;
  float L, C, Q, R, U;
  cvektor2 ul, uc, ur, il, ic, ir, xl, xc, xr, pr, UG, I, X;
  cvektor2 ugil, uluc, icir, ulil;
  cvektor2 SR, SC, SL, S, siq, suq;
  dateneingabe (pu, pi, pf, pb);
  L= pu/(pi*2*M_PI*pf);  
  C= pi/(pu*2*M_PI*pf);  
  R= pb/pi;
  Q= R*sqrt (C/L);
  U= pu;
  UG= cvektor2 (U, 0.f);
  xr= cvektor2 (R, 0.f);
  xl= cvektor2 (0.f, sqrt (L/C));
  xc= cvektor2 (0.f, -sqrt (L/C));
  ur= cvektor2 (0.f, -U*R*sqrt (C/L));
  ir= cvektor2 (0.f, -U*sqrt (C/L));
  uc= cvektor2 (0.f, -U*R*sqrt (C/L));
  ic= cvektor2 (U*R*C/L, 0.f);
  ul= cvektor2 (U, U*R*sqrt (C/L));
  il= cvektor2 (U*R*C/L, -U*sqrt (C/L));
  I= cvektor2 (U*R*C/L, U* sqrt (C/L));
  X= cvektor2 (1/(R*C/L + 1/R), 1/(R*R*sqrt (C*C*C/(L*L*L)) + sqrt (C/L)));
  SR= ur*~ir/2;
  SC= uc*~ic/2;
  SL= ul*~il/2;
  S= UG*~il/2;
  
  // Konsistenzprüfung
  ugil= UG/il;
  uluc= ul + uc;
  icir= ir + ic;
  ulil= ul/il;
  suq= abs (UG) * abs (UG)/(2*~X);
  siq= abs (il) * abs (il)*X/2;
  datenausgabe (L, C, R, Q, xl, xc, ur, ir, uc, ic, ul, il, X, SR, SC, SL, S, ugil, uluc, icir, ulil, suq, siq);
  }

int main ()
  {
  rechneboucherot ();
  return 0;
  }
