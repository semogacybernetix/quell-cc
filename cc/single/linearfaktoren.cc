// Dieses Programm bestimmt die Linearfaktoren von Polynomen

#include <cstdio>
#include "../class/vektor.h"
#include "../../conio/vektorcon.h"

using namespace std;

//--------------------------------------------------------------------------- quadratische Gleichung ----------------------------------------------------------------------------------------------------------------------------------------

void quadratischreduziert (ckomplexk p, ckomplexk& y1, ckomplexk& y2)
  {
  y1=  sqrtr (-p);
  y2= -sqrtr (-p);
  }

void quadratischreduziertk (ckomplexk a, ckomplexk b, ckomplexk& p)
  {
  p= b - a*a/4;
  }

void quadratischnormal (ckomplexk a, ckomplexk b, ckomplexk& x1, ckomplexk& x2)
  {
  ckomplexk a2, p, y1, y2;

  quadratischreduziertk (a, b, p);
  quadratischreduziert (p, y1, y2);

  a2= a/2;
  x1= y1 - a2;
  x2= y2 - a2;
  }

void quadratisch2 (ckomplexk a, ckomplexk b, ckomplexk& x1, ckomplexk& x2)
  {
  ckomplexk D;

  D= sqrtr (a*a - b*4);

  x1= -(a - D)/2;
  x2= -(a + D)/2;
  }

void quadratischp (ckomplexp a, ckomplexp b, ckomplexp& x1, ckomplexp& x2)
  {
  ckomplexp D;

  D= sqrtr (a*a - b*4);

  x1= -(a - D)/2;
  x2= -(a + D)/2;
  }

void quadratischparameter ()
  {
  ckomplexk a, b, x1, x2, x3, x4, x5, x6;
  ckomplexp x7, x8;

  vektor2eingabek (a);
  vektor2eingabek (b);

  quadratisch (a, b, x1, x2);
  quadratisch (a, b, x3, x4);
  quadratisch2 (a, b, x5, x6);
  quadratischp (polar360 (a), polar360 (b), x7, x8);

  printtext ("---------------------- quadratisch ------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("x1          ", x1, 1);
  printvektor2komplex ("x2          ", x2, 1);
  printtext ("\n");
  printtext ("---------------------- quadratisch ------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("x1          ", x3, 1);
  printvektor2komplex ("x2          ", x4, 1);
  printtext ("\n");
  printtext ("---------------------- quadratisch2 -----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("x1          ", x5, 1);
  printvektor2komplex ("x2          ", x6, 1);
  printtext ("\n");
  printtext ("---------------------- quadratischp -----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplexp ("x1          ", x7);
  printvektor2komplexp ("x2          ", x8);
  printtext ("\n");
  }

void quadratischweg1 (ckomplexk ad, ckomplexk bd)
  {
  ckomplexk  pd, al, yl, xl, y1d, y2d, x1d, x2d;

  // Koeffizienten der reduzierten quadratischen Gleichung aus den zentrierten Lösungen der quadratischen Gleichung
  pd= bd - ad*ad/4;

  // Übergabe der quadratischen Parameter an die eingebettete lineare Gleichung
  al= pd;

  // Lösungen der reduzierten linearen Gleichung (die reduzierte lineare Gleichung hat keine Parameter somit ist deren Lösung immer Null)
  yl= 0;

  // Rücktransformation der Lösungen der reduzierten linearen Gleichung in die Lösungen der normalen linearen Gleichung
  xl= yl - al;

  // Rückübergabe der Lösungen der linearen Gleichung an die Lösungen der quadratischen Gleichung
  y1d=  sqrtr (xl);
  y2d= -sqrtr (xl);

  // Rücktransformation ydp -> xdp
  x1d= y1d - ad/2;
  x2d= y2d - ad/2;

  printvektor2komplex ("ad         ", ad, 1);
  printvektor2komplex ("bd         ", bd, 1);
  printtext ("\n");
  printvektor2komplex ("pd         ", pd, 1);
  printtext ("\n");
  printvektor2komplex ("al         ", al, 1);
  printtext ("\n");
  printvektor2komplex ("yl         ", yl, 0);
  printtext ("\n");
  printvektor2komplex ("xl (D)     ", xl, 0);
  printtext ("\n");
  printvektor2komplex ("y1d        ", y1d, 0);
  printvektor2komplex ("y2d        ", y2d, 0);
  printtext ("\n");
  printvektor2komplex ("x1d        ", x1d, 0);
  printvektor2komplex ("x2d        ", x2d, 0);
  printtext ("\n");
  }

void quadratischweg2 (ckomplexk ad, ckomplexk bd)
  {
  ckomplexk  xl, y1, y2, x1, x2;

  // lineare Lösung
  xl= ad*ad/4 - bd;

  // Lösungen reduzierte quadratische Gleichung
  y1=  sqrtr (xl);
  y2= -sqrtr (xl);

  // Lösungen normale quadratische Gleichung
  x1= y1 - ad/2;
  x2= y2 - ad/2;

  printvektor2komplex ("ad         ", ad, 1);
  printvektor2komplex ("bd         ", bd, 1);
  printtext ("\n");
  printvektor2komplex ("xl         ", xl, 0);
  printtext ("\n");
  printvektor2komplex ("y1         ", y1, 0);
  printvektor2komplex ("y2         ", y2, 0);
  printtext ("\n");
  printvektor2komplex ("x1         ", x1, 0);
  printvektor2komplex ("x2         ", x2, 0);
  printtext ("\n");
  }

void quadratischloesungen ()
  {
  ckomplexk a, b, x1, x2, y1, y2, y3, y4, y5, y6;
  ckomplexp xp1, xp2, apol, bpol, y7, y8;

  vektor2eingabek (x1);
  vektor2eingabek (x2);

  a= -(x1 + x2);
  b= x1*x2;

  quadratischweg1 (a, b);
  }

void quadratischeingabezw ()
  {
  ckomplexk x1, x2;

  vektor2eingabek (x1);
  vektor2eingabek (x2);

  quadratischweg2 (x1, x2);
  }

//--------------------------------------------------------------------------- kubische Gleichung ----------------------------------------------------------------------------------------------------------------------------------------

void kubischelementar (ckomplexk a, ckomplexk b, ckomplexk c, ckomplexk& x1, ckomplexk& x2, ckomplexk& x3);       // Nur Deklaration, Implementation später

void kubischparameter ()
  {
  ckomplexk a, b, c, p, q, dp, y1, y2, y3;

  vektor2eingabek (a);
  vektor2eingabek (b);
  vektor2eingabek (c);

  kubischreduziertk (a, b, c, p, q);
  dp= sqrtr (q*q/4 + p*p*p/27)*sqrtr (ckomplexk (-108));
  printtext ("---------------------- Differenzenprodukt der Lösungen -----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("dp          ", dp, 0);
  printtext ("\n");

  kubischreduziertcardano (p, q, y1, y2, y3);
  printtext ("---------------------- kubisch cardano -----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("x1          ", (y1 - a)/3, 0);
  printvektor2komplex ("x2          ", (y2 - a)/3, 0);
  printvektor2komplex ("x3          ", (y3 - a)/3, 0);
  printtext ("\n");

  kubischreduziertu (p, q, y1, y2, y3);
  printtext ("---------------------- kubisch u -----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("x1          ", (y1 - a)/3, 0);
  printvektor2komplex ("x2          ", (y2 - a)/3, 0);
  printvektor2komplex ("x3          ", (y3 - a)/3, 0);
  printtext ("\n");

  kubischreduziertcardano3 (p, q, y1, y2, y3);
  printtext ("---------------------- kubisch cardano3 -----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("x1          ", (y1 - a)/3, 0);
  printvektor2komplex ("x2          ", (y2 - a)/3, 0);
  printvektor2komplex ("x3          ", (y3 - a)/3, 0);
  printtext ("\n");

  kubischreduziertu3 (p, q, y1, y2, y3);
  printtext ("---------------------- kubisch u3 -----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("x1          ", (y1 - a)/3, 0);
  printvektor2komplex ("x2          ", (y2 - a)/3, 0);
  printvektor2komplex ("x3          ", (y3 - a)/3, 0);
  printtext ("\n");
  }

void kubischloesungen ()
  {
  real y;
  ckomplexk x1, x2, x3, a, b, c, p, q, y1, y2, y3;

  vektor2eingabek (x1);
  vektor2eingabek (x2);
  vektor2eingabek (x3);

  a= -(x1 + x2 + x3);
  b= x1*x2 + x1*x3 + x2*x3;
  c= -(x1*x2*x3);

  kubischreduziertk (a, b, c, p, q);

  printvektor2komplex ("a", a, 0);
  printvektor2komplex ("b", b, 0);
  printvektor2komplex ("c", c, 0);
  printtext ("\n");

  kubischreduziertcardano (p, q, y1, y2, y3);
  printtext ("---------------------- kubisch cardano -----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("x1", y1 - a/3, 0);
  printvektor2komplex ("x2", y2 - a/3, 0);
  printvektor2komplex ("x3", y3 - a/3, 0);
  printtext ("\n");

  kubischreduziertcardano3 (p, q, y1, y2, y3);
  printtext ("---------------------- kubisch cardano3 -----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("x1", (y1 - a)/3, 0);
  printvektor2komplex ("x2", (y2 - a)/3, 0);
  printvektor2komplex ("x3", (y3 - a)/3, 0);
  printtext ("\n");

  kubischreduziertu (p, q, y1, y2, y3);
  printtext ("---------------------- kubisch u -----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("x1", y1 - a/3, 0);
  printvektor2komplex ("x2", y2 - a/3, 0);
  printvektor2komplex ("x3", y3 - a/3, 0);
  printtext ("\n");

  kubischreduziertu3 (p, q, y1, y2, y3);
  printtext ("---------------------- kubisch u3 -----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("x1", (y1*3 - a)/3, 0);
  printvektor2komplex ("x2", (y2*3 - a)/3, 0);
  printvektor2komplex ("x3", (y3*3 - a)/3, 0);
  printtext ("\n");

  kubischelementar (a, b, c, x1, x2, x3);
  printtext ("---------------------- kubisch elementar --------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("x1", x1, 0);
  printvektor2komplex ("x2", x2, 0);
  printvektor2komplex ("x3", x3, 0);
  printtext ("\n");

  kubischreduziertreellc (p.x, q.x, y);
  printtext ("---------------------- kubisch reell c -----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("x", y - a.x/3, 0);
  printtext ("\n");

  kubischreduziertreellu (p.x, q.x, y);
  printtext ("---------------------- kubisch reell u -----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("x", y - a.x/3, 0);
  printtext ("\n");
  }

void kubischzwischenwerte (ckomplexk px1, ckomplexk px2, ckomplexk& px3)
  {
  ckomplexk  d_k, d_17p, d_21p, d_ql, dq, bed;
  ckomplexk  u31x, u32x, u33x, v31x, v32x, v33x, uh3x, vh3x;
  ckomplexk  D21_lm, D21_pm, uh3_21pm, vh3_21pm, L1_21pm, L2_21pm, L3_21pm;
  ckomplexk  D21_l, D21_p, uh3_21p, vh3_21p, L1_21p, L2_21p, L3_21p;
  ckomplexk  D17_l, D17_p, uh3_17p, vh3_17p, L1_17p, L2_17p, L3_17p;
  ckomplexk  D1_lm, D1_pm, uh3_1pm, vh3_1pm, L1_1pm, L2_1pm, L3_1pm;
  ckomplexk  D1_l, D1_p, uh3_1p, vh3_1p, L1_1p, L2_1p, L3_1p;
  ckomplexk  D3_lm, D3_pm, uh3_3pm, vh3_3pm, L1_3pm, L2_3pm, L3_3pm;
  ckomplexk  D27_lm, D27_pm, uh3_27pm, vh3_27pm, L1_27pm, L2_27pm, L3_27pm;
  ckomplexk  kx1, kx2, kx3;

  ckomplexk  dx1k, dx2k, dy1k, dy2k, dxkff, kax, kbx, kcx, ky1, ky2, ky3, kpp, kqp, kpy, kqy, D3p, dpp, dx1, dx2, dy1, dy2, dax, dbx, diffpd, diffpk;
  ckomplexk  bla, bla2, blay;

  // kubische Parameter aus kubischen Lösungen: kx1, kx2, kx3 -> kax, kbx, kcx
  kax= -(px1 + px2 + px3);
  kbx= px1*px2 + px2*px3 + px3*px1;
  kcx= -(px1*px2*px3);

  printtext ("******************************** Parameter der kubischen Gleichung ***********************************************************************************************************************\n");
  printvektor2komplex ("kax           ", kax, 1);
  printvektor2komplex ("kbx           ", kbx, 1);
  printvektor2komplex ("kcx           ", kcx, 1);
  printtext ("\n");

  // zentrierte kubische Lösungen aus kubischen Lösungen: kx1, kx2, kx3 -> ky1, ky2, ky3
  ky1= px1 + kax/3;
  ky2= px2 + kax/3;
  ky3= px3 + kax/3;

  printtext ("-------------------------------- die Lösungen der zentrierten kubischen Gleichung --------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("ky1           ", ky1, 1);
  printvektor2komplex ("ky2           ", ky2, 1);
  printvektor2komplex ("ky3           ", ky3, 1);
  printtext ("\n");

  // zentrierte kubische Parameter aus kubischen Parametern: kax, kbx, kcx -> kpp, kqp
  kpp= -(kax*kax)/3 + kbx;
  kqp= kax*(kax*kax/real (4.5) - kbx)/3 + kcx;

  // zentrierte kubische Parameter aus zentrierten kubischen Lösungen: ky1, ky2, ky3 -> kpy, kqy
  kpy= ky1*ky2 + ky2*ky3 + ky3*ky1;
  kqy= -(ky1*ky2*ky3);

  // quadratische Lösungen aus kubischen Lösungen: px1, px2, px3 -> dx1k, dx2k
  bla= (2*px1 - px2 - px3)*(-px1 + 2*px2 - px3)*(-px1 - px2 + 2*px3)/sqrtr (real (27));
  blay= (2*ky1 - ky2 - ky3)*(-ky1 + 2*ky2 - ky3)*(-ky1 - ky2 + 2*ky3)/sqrtr (real (27));
  bla2= px1*px2*px3*sqrtr (real (27));  // ungenau

  dx1k= bla*ik - px1*px2*px2 - px2*px3*px3 - px3*px1*px1 + px1*px1*px2 + px2*px2*px3 + px3*px3*px1;
  dx2k= bla*ik + px1*px2*px2 + px2*px3*px3 + px3*px1*px1 - px1*px1*px2 - px2*px2*px3 - px3*px3*px1;

  dy1k= blay*ik - ky1*ky2*ky2 - ky2*ky3*ky3 - ky3*ky1*ky1 + ky1*ky1*ky2 + ky2*ky2*ky3 + ky3*ky3*ky1;
  dy2k= blay*ik + ky1*ky2*ky2 + ky2*ky3*ky3 + ky3*ky1*ky1 - ky1*ky1*ky2 - ky2*ky2*ky3 - ky3*ky3*ky1;

  dx1k= -dx1k*sqrtr (real (6.75))*ik;
  dx2k= -dx2k*sqrtr (real (6.75))*ik;

  dy1k= -dy1k*sqrtr (real (6.75))*ik;
  dy2k= -dy2k*sqrtr (real (6.75))*ik;

  dxkff= -(dx1k + dx2k)/2;

  printtext ("-------------------------------- Parameter der zentrierten kubischen Gleichung -----------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("kpp           ", kpp, 1);
  printvektor2komplex ("kpy           ", kpy, 1);
  printvektor2komplex ("kqp           ", kqp, 1);
  printvektor2komplex ("kqy           ", kqy, 1);
  printtext ("\n");

  // zentrierter quadratischer Parameter aus zentrierten kubischen Parametern: kpp, kqp -> dpp
  dpp= -(kpp*kpp*kpp)*27 - kqp*kqp*real (182.25);

  // zentrierte quadratische Lösungen aus zentriertem quadratischem Parameter: D, kq -> dy1, dy2
  dy1= -sqrtr (-dpp);
  dy2=  sqrtr (-dpp);

  // quadratische Lösungen aus zentrierten quadratischen Lösungen: dy1, dy2 -> dx1, dx2
  dx1= dy1 - kqp*real (13.5);
  dx2= dy2 - kqp*real (13.5);
  dax= -(dx1 + dx2);
  dbx= dx1*dx2;

  // kubische Lösungen aus quadratischer Lösung: dx1, kp -> kx1
  cbrtr (dx1, kx1, kx2, kx3);

  kx1= (kx1/3 - kpp/kx1);
  kx2= (kx2/3 - kpp/kx2);
  kx3= (kx3/3 - kpp/kx3);

  kax= -(kx1 + kx2 + kx3);
  kbx= kx1*kx2 + kx2*kx3 + kx3*kx1;
  kcx= -(kx1*kx2*kx3);

  diffpd= dx1 - dx2;
  diffpk= (kx1 - kx2)*(kx2 - kx3)*(kx3 - kx1);

  printtext ("-------------------------------- Parameter der zentrierten quadratischen Resolvente ------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("dpp           ", dpp, 1);
  printvektor2komplex ("diffpd²/-4    ", diffpd*diffpd/-4, 1);
  printvektor2komplex ("diffpk²*6.75  ", diffpk*diffpk*real (6.75), 1);
  printtext ("\n");

  printtext ("-------------------------------- Lösung der zentrierten quadratischen Resolvente --------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("dy1           ", dy1, 1);
  printvektor2komplex ("dy2           ", dy2, 1);
  printvektor2komplex ("dx1           ", dx1, 1);
  printvektor2komplex ("dx2           ", dx2, 1);
  printtext ("\n");
  printvektor2komplex ("dx1k          ", dx1k, 1);
  printvektor2komplex ("dx2k          ", dx2k, 1);
  printvektor2komplex ("dy1k          ", dy1k, 1);
  printvektor2komplex ("dy2k          ", dy2k, 1);
  printvektor2komplex ("dx1k + ff     ", dx1k+dxkff, 1);
  printvektor2komplex ("dx2k + ff     ", dx2k+dxkff, 1);
  printtext ("\n");
  printvektor2komplex ("dax/27        ", dax/27, 1);
  printvektor2komplex ("kcx           ", kcx, 1);
  printvektor2komplex ("kqp           ", kqp, 1);
  printtext ("\n");
  printvektor2komplex ("dbx           ", dbx, 1);
  printvektor2komplex ("(kbx*-3)³     ", (kbx*-3)*(kbx*-3)*(kbx*-3), 1);
  printvektor2komplex ("(kpp*-3)³     ", (kpp*-3)*(kpp*-3)*(kpp*-3), 1);
  printtext ("\n");

  printtext ("-------------------------------- Lösung der reduzierten kubischen Gleichung ------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("kx1           ", kx1, 1);
  printvektor2komplex ("kx2           ", kx2, 1);
  printvektor2komplex ("kx3           ", kx3, 1);
  printtext ("\n");
  printvektor2komplex ("kbx           ", kbx, 1);
  printvektor2komplex ("kpp           ", kpp, 1);
  printvektor2komplex ("kcx           ", kcx, 1);
  printvektor2komplex ("kqp           ", kqp, 1);
  printtext ("\n");

  d_k= (kx1 - kx2)*(kx2 - kx3)*(kx3 - kx1);
  d_ql= dx1k - dx2k;
  dq= d_k*d_k;

  // Lösungen Faktor 4.32   D= -60.75 d²
  D27_lm= -dq*real (60.75);
  D27_pm= kqp*kqp*real (1640.25) + kpp*kpp*kpp*243;
  uh3_27pm= -kqp*real (40.5) + sqrtr (D27_lm);
  vh3_27pm= -kqp*real (40.5) - sqrtr (D27_lm);
  bed= kpp*cbrtr (real (-243));
  uvaddition (uh3_27pm, vh3_27pm, bed, L1_27pm, L2_27pm, L3_27pm);
  L1_27pm= L1_27pm/cbrtr (real (81));
  L2_27pm= L2_27pm/cbrtr (real (81));
  L3_27pm= L3_27pm/cbrtr (real (81));

  // Lösungen Faktor 3    D= -6.75 d²
  D3_lm= -dq*real (6.75);
  D3_pm= kqp*kqp*real (182.25) + kpp*kpp*kpp*27;
  uh3_3pm= -kqp*real (13.5) + sqrtr (D3_lm);
  vh3_3pm= -kqp*real (13.5) - sqrtr (D3_lm);
  bed= -kpp*3;
  uvaddition (uh3_3pm, vh3_3pm, bed, L1_3pm, L2_3pm, L3_3pm);
  L1_3pm= L1_3pm/3;
  L2_3pm= L2_3pm/3;
  L3_3pm= L3_3pm/3;

  // Lösungen Faktor 2.18  D = -d²
  D21_lm= -dq;
  D21_pm= kqp*kqp*27 + kpp*kpp*kpp*4;
  uh3_21pm= -kqp*sqrtr (real (27)) + sqrtr (D21_lm);
  vh3_21pm= -kqp*sqrtr (real (27)) - sqrtr (D21_lm);
  bed= kpp*cbrtr (real (-4));
  uvaddition (uh3_21pm, vh3_21pm, bed, L1_21pm, L2_21pm, L3_21pm);
  L1_21pm= L1_21pm/cbrtr (sqrtr (real (108)));  // = sqrtr (3)*cbrtr (2)
  L2_21pm= L2_21pm/cbrtr (sqrtr (real (108)));
  L3_21pm= L3_21pm/cbrtr (sqrtr (real (108)));

  // Lösungen Faktor -2.18i D = d²
  D21_l= dq;
  D21_p= kqp*kqp*-27 + kpp*kpp*kpp*-4;
  uh3_21p= -kqp*sqrtr (real (27))*ik - sqrtr (D21_l);
  vh3_21p= -kqp*sqrtr (real (27))*ik + sqrtr (D21_l);
  d_21p= uh3_21p - vh3_21p;
  bed= -kpp*cbrtr (-ckomplexk (4));
  uvaddition (uh3_21p, vh3_21p, bed, L1_21p, L2_21p, L3_21p);
  L1_21p= L1_21p/cbrtr (ik*sqrtr (real (108)));
  L2_21p= L2_21p/cbrtr (ik*sqrtr (real (108)));
  L3_21p= L3_21p/cbrtr (ik*sqrtr (real (108)));

  // Lösungen Faktor 1.73i  D = d²/4
  D17_l= dq/4;
  D17_p= -(kqp*kqp)*27/4 - kpp*kpp*kpp;
  uh3_17p= -kqp/2*sqrtr (-ckomplexk (27)) + sqrtr (D17_l);
  vh3_17p= -kqp/2*sqrtr (-ckomplexk (27)) - sqrtr (D17_l);
  d_17p= uh3_17p - vh3_17p;
  bed= kpp*-cbrtr (-ckomplexk (1));
  uvaddition (uh3_17p, vh3_17p, bed, L1_17p, L2_17p, L3_17p);
  L1_17p= L1_17p/cbrtr (ik*sqrtr (real (27)));
  L2_17p= L2_17p/cbrtr (ik*sqrtr (real (27)));
  L3_17p= L3_17p/cbrtr (ik*sqrtr (real (27)));

  // Lösungen Faktor 1      D=d²/-108
  D1_lm= dq/-108;
  D1_pm= kqp*kqp/4 + kpp*kpp*kpp/27;
  uh3_1pm= -kqp/2 + sqrtr (D1_lm);
  vh3_1pm= -kqp/2 - sqrtr (D1_lm);
  bed= kpp/-3;
  uvaddition (uh3_1pm, vh3_1pm, bed, L1_1pm, L2_1pm, L3_1pm);

  // Lösungen Faktor -i     D= d²/108
  D1_l= dq/108;
  D1_p= kqp*kqp/-4 + kpp*kpp*kpp/-27;
  uh3_1p= -kqp/2*ik + sqrtr (D1_l);
  vh3_1p= -kqp/2*ik - sqrtr (D1_l);
  bed= kpp/3;
  uvaddition (uh3_1p, vh3_1p, bed, L1_1p, L2_1p, L3_1p);
  L1_1p= L1_1p/-ik;
  L2_1p= L2_1p/-ik;
  L3_1p= L3_1p/-ik;

  // die 3 Lösungen für u aus den Lösungen 27u³
  u31x= (ky1     + e32*ky2 + e31*ky3);
  u32x= (e31*ky1 +     ky2 + e32*ky3);
  u33x= (e32*ky1 + e31*ky2 +     ky3);
  uh3x= u31x*u31x*u31x;

  // die 3 Lösungen für v aus den Lösungen 27v³
  v31x= (ky1     + e31*ky2 + e32*ky3);
  v32x= (e32*ky1 +     ky2 + e31*ky3);
  v33x= (e31*ky1 + e32*ky2 +     ky3);
  vh3x= v31x*v31x*v31x;

  printtext ("-------------------------------- das Differenzenprodukt dk -----------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("d_k        ", d_k, 1);
  printvektor2komplex ("d_kl       ", d_ql, 1);
  printvektor2komplex ("d_17p      ", d_17p, 1);
  printvektor2komplex ("d_21p      ", d_21p, 1);
  printtext ("\n");
  printtext ("-------------------------------- die Werte u³, v³ aus den x-Lösungen ---------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("dx1k       ", dx1k, 1);
  printvektor2komplex ("dx2k       ", dx2k, 1);
  printtext ("\n");
  printtext ("-------------------------------- die Werte u³, v³  mit Faktor 27 D= d²*-60.75---------------------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("uh3_27pm   ", uh3_27pm, 1);
  printvektor2komplex ("vh3_27pm   ", vh3_27pm, 1);
  printtext ("\n");
  printtext ("-------------------------------- die Werte u³, v³  mit Faktor 3 D= d²*-6.75---------------------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("uh3x       ", uh3x, 1);
  printvektor2komplex ("vh3x       ", vh3x, 1);
  printtext ("\n");
  printvektor2komplex ("uh3_3pm    ", uh3_3pm, 1);
  printvektor2komplex ("vh3_3pm    ", vh3_3pm, 1);
  printtext ("\n");
  printtext ("-------------------------------- die Werte u³, v³ mit Faktor -2.18 (6V108) D = -d² ---------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("3u³_21pm   ", uh3_21pm, 1);
  printvektor2komplex ("3v³_21pm   ", vh3_21pm, 1);
  printtext ("\n");
  printtext ("-------------------------------- die Werte u³, v³ mit Faktor  2.18 D = d² ---------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("3u³_p      ", uh3_21p, 1);
  printvektor2komplex ("3v³_p      ", vh3_21p, 1);
  printtext ("\n");
  printtext ("-------------------------------- die Werte u³, v³ mit Faktor  1.73 D= d²/4 ---------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("3u³_p      ", uh3_17p, 1);
  printvektor2komplex ("3v³_p      ", vh3_17p, 1);
  printtext ("\n");
  printtext ("-------------------------------- die Werte u³, v³ mit Faktor -1 D= d²/-108 ------------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("u³_p       ", uh3_1pm, 1);
  printvektor2komplex ("v³_p       ", vh3_1pm, 1);
  printtext ("\n");
  printtext ("-------------------------------- die Werte u³, v³ mit Faktor  1 D= d²/108 ------------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("u³_p       ", uh3_1p, 1);
  printvektor2komplex ("v³_p       ", vh3_1p, 1);
  printtext ("\n");
  printtext ("-------------------------------- die Lösungen aus Faktor -27 ----------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("x0p D0     ", L1_27pm, 1);
  printvektor2komplex ("x0p D0     ", L2_27pm, 1);
  printvektor2komplex ("x0p D0     ", L3_27pm, 1);
  printtext ("\n");
  printtext ("-------------------------------- die Lösungen aus Faktor -3 ----------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("x0p D0     ", L1_3pm, 1);
  printvektor2komplex ("x0p D0     ", L2_3pm, 1);
  printvektor2komplex ("x0p D0     ", L3_3pm, 1);
  printtext ("\n");
  printtext ("-------------------------------- die Lösungen aus Faktor -2.18 ----------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("x0p D0     ", L1_21pm, 1);
  printvektor2komplex ("x0p D0     ", L2_21pm, 1);
  printvektor2komplex ("x0p D0     ", L3_21pm, 1);
  printtext ("\n");
  printtext ("-------------------------------- die Lösungen aus Faktor 2.18 ----------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("x0p D0     ", L1_21p, 1);
  printvektor2komplex ("x0p D0     ", L2_21p, 1);
  printvektor2komplex ("x0p D0     ", L3_21p, 1);
  printtext ("\n");
  printtext ("-------------------------------- die Lösungen aus Faktor 1.73 ----------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("x0p D0     ", L1_17p, 1);
  printvektor2komplex ("x0p D0     ", L2_17p, 1);
  printvektor2komplex ("x0p D0     ", L3_17p, 1);
  printtext ("\n");
  printtext ("-------------------------------- die Lösungen aus Faktor -1 ----------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("x0p D0     ", L1_1pm, 1);
  printvektor2komplex ("x0p D0     ", L2_1pm, 1);
  printvektor2komplex ("x0p D0     ", L3_1pm, 1);
  printtext ("\n");
  printtext ("-------------------------------- die Lösungen aus Faktor  1 ----------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("x0p D0     ", L1_1p, 1);
  printvektor2komplex ("x0p D0     ", L2_1p, 1);
  printvektor2komplex ("x0p D0     ", L3_1p, 1);
  printtext ("\n");
  }

void kubischweg1 (ckomplexk x1k, ckomplexk x2k, ckomplexk& x3k)
  {
  ckomplexk ak, bk, ck, ak3, y1k, y2k, y3k, dpyk, bla, bla2, x1d, x2d, pk, qk, pkp, qkp, ad, bd, ad2, pd, xlp, y1dp, y2dp, x1dp, x2dp, xdp, z1kp, z2kp, z3kp, y1kp, y2kp, y3kp, x1kp, x2kp, x3kp;

  // Parameter der normalen kubischen Gleichung, kubischer Offset
  ak= -(x1k + x2k + x3k);
  bk= x1k*x2k + x2k*x3k + x3k*x1k;
  ck= -(x1k*x2k*x3k);
  ak3= ak/3;

  // Lösungen (zentriert) der reduzierten kubischen Gleichung (Hintransformation)
  y1k= x1k + ak3;
  y2k= x2k + ak3;
  y3k= x3k + ak3;

  // Differenzenproduktquadrat der Lösungen der reduzierten kubischen Gleichung
  dpyk= (y1k-y2k)*(y2k-y3k)*(y3k-y1k);
  dpyk= dpyk*dpyk;

  // quadratische Lösungen aus zentrierten kubischen Lösungen: y1k, y2k, y3k -> dx1k, dx2k
  bla= (2*y1k - y2k - y3k)*(-y1k + 2*y2k - y3k)*(-y1k - y2k + 2*y3k)/sqrtr (real (27));
  bla2= y1k*y2k*y3k*sqrtr (real (27));  // ungenauer als bla und funktioniert nicht bei den xk weil keine Differenzigkeit

  x1d= bla*ik - y1k*y2k*y2k - y2k*y3k*y3k - y3k*y1k*y1k + y1k*y1k*y2k + y2k*y2k*y3k + y3k*y3k*y1k;
  x2d= bla*ik + y1k*y2k*y2k + y2k*y3k*y3k + y3k*y1k*y1k - y1k*y1k*y2k - y2k*y2k*y3k - y3k*y3k*y1k;

  // Koeffizienten der reduzierten kubischen Gleichung aus den zentrierten Lösungen der kubischen Gleichung
  pk= y1k*y2k + y2k*y3k + y3k*y1k;
  qk= y1k*y2k*y3k*-1;

  pkp= ak*ak/-3 + bk;
  qkp= ak*(ak*ak/real (4.5) - bk)/3 + ck;

  // Übergabe der kubischen Parameter an die eingebettete quadratische Gleichung
  ad= qkp;
  bd= pkp*pkp*pkp/-27;
  ad2= ad/2;

  // Parameter der reduzierten quadratischen Gleichung aus den Parametern der normalen quadratischen Gleichung
  pd= bd - ad*ad/4;

  // Lösung der normalen linearen Gleichung aus den Parametern der reduzierten quadratischen Gleichung
  xlp= -pd;

  // Rückübergabe der linearen Lösungen an die quadratischen Lösungen
  y1dp=  sqrtr (xlp);
  y2dp= -sqrtr (xlp);

  // Rücktransformation der Lösungen der reduzierten quadratischen Gleichung in die Lösungen der normalen quadratischen Gleichung
  x1dp= y1dp - ad2;
  x2dp= y2dp - ad2;

  // Rückübergabe der quadratischen Lösungen an die kubischen Lösungen
  xdp= x1dp;
  cbrtr (xdp, z1kp, z2kp, z3kp);
  y1kp= z1kp - pk/(z1kp*3);
  y2kp= z2kp - pk/(z2kp*3);
  y3kp= z3kp - pk/(z3kp*3);

  // Rücktransformation der Lösungen der reduzierten kubischen Gleichung in die Lösungen der normalen kubischen Gleichung
  x1kp= y1kp - ak3;
  x2kp= y2kp - ak3;
  x3kp= y3kp - ak3;

  // Variablenausgabe
  printvektor2komplex ("x1k        ", x1k, 0);
  printvektor2komplex ("x2k        ", x2k, 0);
  printvektor2komplex ("x3k        ", x3k, 0);
  printtext ("\n");
  printvektor2komplex ("ak         ", ak, 1);
  printvektor2komplex ("bk         ", bk, 1);
  printvektor2komplex ("ck         ", ck, 1);
  printtext ("\n");
  printvektor2komplex ("y1k        ", y1k, 0);
  printvektor2komplex ("y2k        ", y2k, 0);
  printvektor2komplex ("y3k        ", y3k, 0);
  printtext ("\n");
  printvektor2komplex ("pkp        ", pkp, 1);
  printvektor2komplex ("qkp        ", qkp, 1);
  printtext ("\n");
  printvektor2komplex ("ad         ", ad, 1);
  printvektor2komplex ("bd         ", bd, 1);
  printtext ("\n");
  printvektor2komplex ("pd         ", pd, 1);
  printvektor2komplex ("dpyk²/-108 ", dpyk/-108, 0);
  printvektor2komplex ("xlp = D    ", xlp, 1);
  printtext ("\n");
  printvektor2komplex ("y1dp       ", y1dp, 0);
  printvektor2komplex ("y2dp       ", y2dp, 0);
  printtext ("\n");
  printvektor2komplex ("x1dp       ", x1dp, 0);
  printvektor2komplex ("x2dp       ", x2dp, 0);
  printtext ("\n");
  printvektor2komplex ("x1d/√-108  ", x1d/sqrtr (ckomplexk (-108)), 0);
  printvektor2komplex ("x2d/√-108  ", x2d/sqrtr (ckomplexk (-108)), 0);
  printtext ("\n");
  printvektor2komplex ("z1kp       ", z1kp, 0);
  printvektor2komplex ("z2kp       ", z2kp, 0);
  printvektor2komplex ("z3kp       ", z3kp, 0);
  printtext ("\n");
  printvektor2komplex ("y1kp       ", y1kp, 0);
  printvektor2komplex ("y2kp       ", y2kp, 0);
  printvektor2komplex ("y3kp       ", y3kp, 0);
  printtext ("\n");
  printvektor2komplex ("x1kp       ", x1kp, 0);
  printvektor2komplex ("x2kp       ", x2kp, 0);
  printvektor2komplex ("x3kp       ", x3kp, 0);
  printtext ("\n");
  }

void kubischweg2 (ckomplexk x1, ckomplexk x2, ckomplexk& x3)
  {
  ckomplexk ak, bk, ck, ak3, pk, qk, xl, x1d, x2d, u1p, u2p, u3p, v1p, v2p, v3p, y1p, y2p, y3p, x1p, x2p, x3p, u1, u2, u3, v1, v2, v3;

  // Parameter der normalen kubischen Gleichung, kubischer Offset
  ak= -(x1 + x2 + x3);
  bk= x1*x2 + x2*x3 + x3*x1;
  ck= -(x1*x2*x3);
  ak3= ak/3;

  // Parameter der reduzierten kubischen Gleichung
  pk= ak*ak/-3 + bk;
  qk= ak*(ak*ak/real (4.5) - bk)/3 + ck;

  // Lösungen der eingebetteten quadratischen Gleichung
  xl= pk*pk*pk/27 + qk*qk/4;
  x1d= -qk/2 + sqrtr (xl);
  x2d= -qk/2 - sqrtr (xl);

  // Lösungen u v
  cbrtr (x1d, u1p, u2p, u3p);
  cbrtr (x2d, v1p, v2p, v3p);

  // Rückübergabe der quadratischen Lösungen an die kubischen Lösungen
  y1p= u1p - pk/(u1p*3);
  y2p= u2p - pk/(u2p*3);
  y3p= u3p - pk/(u3p*3);

  // Rücktransformation der Lösungen der reduzierten kubischen Gleichung in die Lösungen der normalen kubischen Gleichung
  x1p= y1p - ak3;
  x2p= y2p - ak3;
  x3p= y3p - ak3;

  // die 3 Lösungen für u aus den Lösungen der normalen kubischen Gleichung
  u1= (x1     + x2*e32 + x3*e31)/3;
  u2= (x1*e31 + x2     + x3*e32)/3;
  u3= (x1*e32 + x2*e31 + x3    )/3;

  // die 3 Lösungen für v aus den Lösungen der normalen kubischen Gleichung
  v1= (x1     + x2*e31 + x3*e32)/3;
  v2= (x1*e32 + x2     + x3*e31)/3;
  v3= (x1*e31 + x2*e32 + x3    )/3;

  // Variablenausgabe
  printvektor2komplex ("ak         ", ak, 1);
  printvektor2komplex ("bk         ", bk, 1);
  printvektor2komplex ("ck         ", ck, 1);
  printtext ("\n");
  printvektor2komplex ("pk         ", pk, 1);
  printvektor2komplex ("qk         ", qk, 1);
  printtext ("\n");
  printvektor2komplex ("xl         ", xl, 1);
  printtext ("\n");
  printvektor2komplex ("x1d        ", x1d, 0);
  printvektor2komplex ("x2d        ", x2d, 0);
  printtext ("\n");
  printvektor2komplex ("u1p        ", u1p, 1);
  printvektor2komplex ("u2p        ", u2p, 1);
  printvektor2komplex ("u3p        ", u3p, 1);
  printtext ("\n");
  printvektor2komplex ("v1p        ", v1p, 1);
  printvektor2komplex ("v2p        ", v2p, 1);
  printvektor2komplex ("v3p        ", v3p, 1);
  printtext ("\n");
  printvektor2komplex ("u1         ", u1, 1);
  printvektor2komplex ("u2         ", u2, 1);
  printvektor2komplex ("u3         ", u3, 1);
  printtext ("\n");
  printvektor2komplex ("v1         ", v1, 1);
  printvektor2komplex ("v2         ", v2, 1);
  printvektor2komplex ("v3         ", v3, 1);
  printtext ("\n");
  printvektor2komplex ("y1p        ", y1p, 0);
  printvektor2komplex ("y2p        ", y2p, 0);
  printvektor2komplex ("y3p        ", y3p, 0);
  printtext ("\n");
  printvektor2komplex ("x1p        ", x1p, 0);
  printvektor2komplex ("x2p        ", x2p, 0);
  printvektor2komplex ("x3p        ", x3p, 0);
  printtext ("\n");
  }

void kubischeingabezw ()
  {
  ckomplexk x1, x2, x3;

  vektor2eingabek (x1);
  vektor2eingabek (x2);
  vektor2eingabek (x3);

//  kubischzwischenwerte (x1, x2, x3);
  kubischweg1 (x1, x2, x3);
  }

//--------------------------------------------------------------------------- quartische Gleichung ----------------------------------------------------------------------------------------------------------------------------------------

void quartischzwischenwerte (ckomplexk qx1, ckomplexk qx2, ckomplexk qx3, ckomplexk& qx4)
  {
  ckomplexk qax, qbx, qcx, qdx, qpp, qqp, qrp, kpp, kqp, dax, dbx, D3p, dx1, dx2, kx1, kx2, kx3, kx1q, kx2q, kx3q, kxqoff, kax, kbx, kcx;
  ckomplexk u, v, m1, m2, n1qp, n2qp, n1r, n2r, Dd1, Dd2, d1y1, d1y2, d2y1, d2y2, d1x1, d1x2, d2x1, d2x2;
  ckomplexk diffpd, diffpk, diffpq, kresxa, kresxb, kresxc, kap, kbp, kcp;

  // Lösungen der kubischen x-Resolvente aus den quartischen Lösungen: qx1, qx2, qx3, qx4 -> kx1q, kx2q, kx3q
  kx1q= qx1*qx2 + qx3*qx4;
  kx2q= qx1*qx3 + qx2*qx4;
  kx3q= qx1*qx4 + qx3*qx2;
  kxqoff= (kx1q + kx2q + kx3q)/-3;

  // Parameter der kubischen Gleichung aus der x-Resolvente: kx1q, kx2q, kx3q -> kresxa, kresxb, kresxc
  kresxa= -(kx1q + kx2q + kx3q);
  kresxb= kx1q*kx2q + kx2q*kx3q + kx3q*kx1q;
  kresxc= -(kx1q*kx2q*kx3q);

  // quartische Parameter aus den quartischen Lösungen: qx1, qx2, qx3, qx4 -> qax, qbx, qcx, qdx
  qax= -(qx1 + qx2 + qx3 + qx4);
  qbx= qx1*qx2 + qx1*qx3 + qx1*qx4 + qx2*qx3 + qx2*qx4 + qx3*qx4;
  qcx= -(qx1*qx2*qx3 + qx1*qx2*qx4 + qx1*qx3*qx4 + qx2*qx3*qx4);
  qdx= qx1*qx2*qx3*qx4;

  printtext ("-------------------------------- Parameter der quartischen Gleichung ---------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("qax           ", qax, 1);
  printvektor2komplex ("qbx           ", qbx, 1);
  printvektor2komplex ("qcx           ", qcx, 1);
  printvektor2komplex ("qdx           ", qdx, 1);
  printtext ("\n");

  // zentrierte quartische Parameter aus den quartischen Parametern: qax, qbx, qcx, qdx -> qpp, qqp, qrp
  qpp= qax*qax*3/-8 + qbx;
  qqp= qax*(qax*qax - qbx*4)/8 + qcx;
  qrp= qax*((qax*qbx - qcx*4)*16 - qax*qax*qax*3)/256 + qdx;

  printtext ("-------------------------------- Parameter der reduzierten quartischen Gleichung ---------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("qpp           ", qpp, 1);
  printvektor2komplex ("qqp           ", qqp, 1);
  printvektor2komplex ("qrp           ", qrp, 1);
  printtext ("\n");

  // Parameter der kubischen Resolvente aus den zentrierten quartischen Parametern: qpp, qqp, qrp -> kap, kbp, kcp
  kap= qpp/-2;
  kbp= -qrp;
  kcp= qpp*qrp/2 - qqp*qqp/8;

  // Parameter der zentrierten kubischen Gleichung aus den zentrierten quartischen Parametern: qpp, qqp, qrp -> kpp, kqp
  kpp= (qpp*qpp + qrp*12)/-3;
  kqp= qpp*(qrp*36 - qpp*qpp)/real (13.5) - qqp*qqp;

  printtext ("-------------------------------- Parameter der reduzierten kubischen Gleichung der kubischen Resolvente3 -------------------------------------------------------------------------------\n");
  printvektor2komplex ("kpp           ", kpp, 1);
  printvektor2komplex ("kqp           ", kqp, 1);
  printtext ("\n");

  printtext ("-------------------------------- Parameter der kubischen Gleichung der x-Resolvente ------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("kresxa        ", kresxa, 1);
  printvektor2komplex ("kresxb        ", kresxb, 1);
  printvektor2komplex ("kresxc        ", kresxc, 1);
  printtext ("\n");
  printtext ("-------------------------------- Parameter der kubischen Resolvente ------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("kap           ", kap, 1);
  printvektor2komplex ("kbp           ", kbp, 1);
  printvektor2komplex ("kcp           ", kcp, 1);
  printtext ("\n");

  // die dreifache lineare Lösung x (Diskriminante) aus den zentrierten kubischen Paramentern: kpp, kqp -> lx3
  D3p= kqp*kqp*real (182.25) + kpp*kpp*kpp*27;

  printtext ("-------------------------------- Die Diskriminante aus den Parametern der reduzierten Gleichung der kubischen Resolvente ----------------------------------------------------------------\n");
  printvektor2komplex ("D3p           ", D3p, 1);

  // D3p, kqp -> dx1                dx1, kx1 Division 0/0 muss vermieden werden deshalb Betrag möglichst groß, andere Lösung auswählen
  dx1= kqp*real (-13.5) - sqrtr (D3p);
  dx2= kqp*real (-13.5) + sqrtr (D3p);
  dax= -(dx1 + dx2);
  dbx= dx1*dx2;

  // dx1, kpp -> kx1
  cbrtr (dx2, kx1, kx2, kx3);
  kx1= kx1 - kpp*3/kx1;
  kx2= kx2 - kpp*3/kx2;
  kx3= kx3 - kpp*3/kx3;
  kax= -(kx1 + kx2 + kx3);
  kbx= kx1*kx2 + kx2*kx3 + kx3*kx1;
  kcx= -(kx1*kx2*kx3);

  diffpd= dx1 - dx2;
  diffpk= (kx1 - kx2)*(kx2 - kx3)*(kx3 - kx1);
  diffpq= (qx1 - qx2)*(qx1 - qx3)*(qx1 - qx4)*(qx2 - qx3)*(qx2 - qx4)*(qx3 - qx4);
  printvektor2komplex ("diffpd²/4     ", diffpd*diffpd/4, 1);
  printvektor2komplex ("diffpk²/-108  ", diffpk*diffpk/-108, 1);
  printvektor2komplex ("diffpq²*-6.75 ", diffpq*diffpq*-real (6.75), 1);
  printtext ("\n");

  printtext ("-------------------------------- Lösung der quadratischen Resolvente --------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("dx1           ", dx1, 1);
  printvektor2komplex ("dx2           ", dx2, 1);
  printtext ("\n");
  printvektor2komplex ("dax           ", dax, 1);
  printvektor2komplex ("kcx           ", kcx, 1);
  printvektor2komplex ("kqp*27        ", kqp*27, 1);
  printtext ("\n");
  printvektor2komplex ("dbx           ", dbx, 1);
  printvektor2komplex ("kbx³/-27      ", kbx*kbx*kbx/-27, 1);
  printvektor2komplex ("kpp³*-27      ", kpp*kpp*kpp*-27, 1);
  printtext ("\n");

  printtext ("-------------------------------- Lösung der kubischen Resolvente aus den Parametern ------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("kx1           ", kx1, 1);
  printvektor2komplex ("kx2           ", kx2, 1);
  printvektor2komplex ("kx3           ", kx3, 1);
  printtext ("\n");
  printtext ("-------------------------------- Lösung der (kubischen x-Resolvente + offset)*3 ------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("kx1q*3 + off  ", (kx1q + kxqoff)*3, 1);
  printvektor2komplex ("kx2q*3 + off  ", (kx2q + kxqoff)*3, 1);
  printvektor2komplex ("kx3q*3 + off  ", (kx3q + kxqoff)*3, 1);
  printvektor2komplex ("offset        ", kxqoff, 1);
  printtext ("\n");
  printvektor2komplex ("kbx           ", kbx, 1);
  printvektor2komplex ("kpp*9         ", kpp*9, 1);
  printvektor2komplex ("kcx           ", kcx, 1);
  printvektor2komplex ("kqp*27        ", kqp*27, 1);
  printtext ("\n");

  // kx1, qpp -> m1, m2
  m1=  sqrtr ((kx1 - qpp*2)*3);
  m2= -sqrtr ((kx1 - qpp*2)*3);

  // kx1, qpp, qqp -> n1, n2    Division durch 0 deshalb     kx1 <> 2qpp
  n1qp= (kx1 + qpp - qqp/sqrtr ((kx1 - qpp*2)/27))*6;
  n2qp= (kx1 + qpp + qqp/sqrtr ((kx1 - qpp*2)/27))*6;

  // kx1, qpp, qrp -> n1, n2
  n1r= (kx1 + qpp + sqrtr ((kx1 + qpp)*(kx1 + qpp) - qrp*36))*6;
  n2r= (kx1 + qpp - sqrtr ((kx1 + qpp)*(kx1 + qpp) - qrp*36))*6;

  printtext ("-------------------------------- die Parameter der quadratischen Gleichungen ------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("m1            ", m1, 1);
  printvektor2komplex ("n1qp          ", n1qp, 1);
  printvektor2komplex ("n1r           ", n1r, 1);
  printvektor2komplex ("m2            ", m2, 1);
  printvektor2komplex ("n2qp          ", n2qp, 1);
  printvektor2komplex ("n2r           ", n2r, 1);
  printtext ("\n");

  Dd1= sqrtr (m1*m1 - n1qp);
  Dd2= sqrtr (m2*m2 - n2qp);

  printtext ("-------------------------------- die Determinanten der quadratischen Gleichungen ------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("Dd1           ", Dd1, 1);
  printvektor2komplex ("Dd2           ", Dd2, 1);
  printtext ("\n");

  d1y1= (m1 + Dd1)/-6;
  d1y2= (m1 - Dd1)/-6;
  d2y1= (m2 + Dd2)/-6;
  d2y2= (m2 - Dd2)/-6;

  printtext ("-------------------------------- Lösungen der quadratischen Gleichungen -------------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("d1y1          ", d1y1, 1);
  printvektor2komplex ("d1y2          ", d1y2, 1);
  printvektor2komplex ("d2y1          ", d2y1, 1);
  printvektor2komplex ("d2y2          ", d2y2, 1);
  printtext ("\n");

  d1x1= d1y1 - qax/4;
  d1x2= d1y2 - qax/4;
  d2x1= d2y1 - qax/4;
  d2x2= d2y2 - qax/4;

  printtext ("-------------------------------- Lösungen der quartischen Gleichung ------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("d1x1           ", d1x1, 1);
  printvektor2komplex ("d1x2           ", d1x2, 1);
  printvektor2komplex ("d2x1           ", d2x1, 1);
  printvektor2komplex ("d2x2           ", d2x2, 1);
  printtext ("\n");
  }

void quartischwegdiffp (ckomplexk x1s, ckomplexk x2s, ckomplexk x3s, ckomplexk& x4s)
  {
  ckomplexk aq, bq, cq, dq, pq, qq, rq, ak, bk, ck, pk, qk, ad, bd, pd, x1l, y1d, y2d, ad2, x1d, x2d, xd, z1k, z2k, z3k, y1k, y2k, y3k, ak3, x1k, x2k, x3k, xk;
  ckomplexk z, u, a1, a2, b1, b2, y1q, y2q, y3q, y4q, aq4, x1q, x2q, x3q, x4q;
  ckomplexk dpyq, dpyk, dpyd, x1ks, x2ks, x3ks, bla, x1ds, x2ds;

  // quartische Parameter aus den quartischen Lösungen: x1s, x2s, x3s, x4s -> aq, bq, cq, dq
  aq= -(x1s + x2s + x3s + x4s);
  bq= x1s*x2s + x1s*x3s + x1s*x4s + x2s*x3s + x2s*x4s + x3s*x4s;
  cq= -(x1s*x2s*x3s + x1s*x2s*x4s + x1s*x3s*x4s + x2s*x3s*x4s);
  dq= x1s*x2s*x3s*x4s;

  // normal -> zentriert: aq, bq, cq, dq -> pq, qq, rq
  pq= aq*aq*3/-8 + bq;
  qq= aq*(aq*aq - bq*4)/8 + cq;
  rq= aq*((aq*bq - cq*4)*16 - aq*aq*aq*3)/256 + dq;

  // Parameter der kubischen Resolvente diffp aus den zentrierten quartischen Parametern: qpp, qqp, qrp -> akp, bkp, ckp
  ak= -pq;
  bk= rq*-4;
  ck= pq*rq*4 - qq*qq;

  // normal -> reduziert
  pk= ak*ak/-3 + bk;
  qk= ak*(ak*ak/real (4.5) - bk)/3 + ck;

  // Parameter der quadratischen Resolvente
  ad= qk;
  bd= pk*pk*pk/-27;

  // Parameter der reduzierten quadratischen Gleichung aus den Parametern der normalen quadratischen Gleichung
  pd= bd - ad*ad/4;

  // Lösung der normalen linearen Gleichung aus den Parametern der reduzierten quadratischen Gleichung
  x1l= -pd;

  // Rückübergabe der linearen Lösungen an die quadratischen Lösungen
  y1d=  sqrtr (x1l);
  y2d= -sqrtr (x1l);

  // Rücktransformation der Lösungen der reduzierten quadratischen Gleichung in die Lösungen der normalen quadratischen Gleichung
  ad2= ad/2;
  x1d= y1d - ad2;
  x2d= y2d - ad2;

  // Rückübergabe der quadratischen Lösungen an die kubischen Lösungen
  xd= x1d;
  cbrtr (xd, z1k, z2k, z3k);
  y1k= z1k - pk/(z1k*3);
  y2k= z2k - pk/(z2k*3);
  y3k= z3k - pk/(z3k*3);

  // Rücktransformation der Lösungen der reduzierten kubischen Gleichung in die Lösungen der normalen kubischen Gleichung
  ak3= ak/3;
  x1k= y1k - ak3;
  x2k= y2k - ak3;
  x3k= y3k - ak3;

  // Rückübergabe der kubischen Lösungen an die quartischen Lösungen (diffp)
  xk= x1k;

  z= xk;
  u= sqrtr (z - pq);

  a1=  u;
  a2= -u;
  b1= (z - qq/u)/2;
  b2= (z + qq/u)/2;

  quadratisch (a1, b1, y1q, y2q);
  quadratisch (a2, b2, y3q, y4q);

  // Rücktransformation der zentrierten quartischen Lösungen in die Lösungen der normalen quartischen Gleichung
  aq4= aq/4;
  x1q= y1q - aq4;
  x2q= y2q - aq4;
  x3q= y3q - aq4;
  x4q= y4q - aq4;

  // ---------------------------------------- Rückrechnungen ---------------------------------------------------------------------

  // Differenzenproduktquadrat der Lösungen der reduzierten quartischen Gleichung
  dpyq= (y1q-y2q)*(y1q-y3q)*(y1q-y4q)*(y2q-y3q)*(y2q-y4q)*(y3q-y4q);
  dpyq= dpyq*dpyq;

  // Differenzenproduktquadrat der Lösungen der reduzierten kubischen Gleichung
  dpyk= (y1k-y2k)*(y2k-y3k)*(y3k-y1k);
  dpyk= dpyk*dpyk;

  // Differenzenproduktquadrat der Lösungen der reduzierten quadratischen Gleichung
  dpyd= y1d-y2d;
  dpyd= dpyd*dpyd;

  // Lösungen der kubischen Resolvente aus den zentrierten quartischen Lösungen: y1q, y2q, y3q, y4q -> x1ks, x2ks, x3ks
  x1ks= y1q*y2q + y3q*y4q;
  x2ks= y1q*y3q + y2q*y4q;
  x3ks= y1q*y4q + y3q*y2q;

  // Lösungen der quadratischen Resolvente aus den zentrierten kubischen Lösungen: y1k, y2k, y3k -> x1ds, x2ds
  bla= (2*y1k - y2k - y3k)*(-y1k + 2*y2k - y3k)*(-y1k - y2k + 2*y3k)/sqrtr (real (27));
  x1ds= bla*ik - y1k*y2k*y2k - y2k*y3k*y3k - y3k*y1k*y1k + y1k*y1k*y2k + y2k*y2k*y3k + y3k*y3k*y1k;
  x2ds= bla*ik + y1k*y2k*y2k + y2k*y3k*y3k + y3k*y1k*y1k - y1k*y1k*y2k - y2k*y2k*y3k - y3k*y3k*y1k;

  // Variablenausgabe
  printtext ("********************************************************************************************** quartischwegdiffp **********************************************************************************************************\n");
  printvektor2komplex ("aq         ", aq, 0);
  printvektor2komplex ("bq         ", bq, 0);
  printvektor2komplex ("cq         ", cq, 0);
  printvektor2komplex ("dq         ", dq, 0);
  printtext ("\n");
  printvektor2komplex ("pq         ", pq, 1);
  printvektor2komplex ("qq         ", qq, 1);
  printvektor2komplex ("rq         ", rq, 1);
  printtext ("\n");
  printvektor2komplex ("ak         ", ak, 0);
  printvektor2komplex ("bk         ", bk, 0);
  printvektor2komplex ("ck         ", ck, 0);
  printtext ("\n");
  printvektor2komplex ("pk         ", pk, 1);
  printvektor2komplex ("qk         ", qk, 1);
  printtext ("\n");
  printvektor2komplex ("ad         ", ad, 1);
  printvektor2komplex ("bd         ", bd, 1);
  printtext ("\n");
  printvektor2komplex ("pd         ", pd, 1);
  printtext ("\n");
  printvektor2komplex ("x1l = D    ", x1l, 1);
  printvektor2komplex ("dpyq/-108  ", dpyq/-108, 1);
  printvektor2komplex ("dpyk/-108  ", dpyk/-108, 1);
  printvektor2komplex ("dpyd/4     ", dpyd/4, 1);
  printtext ("\n");
  printvektor2komplex ("y1d        ", y1d, 0);
  printvektor2komplex ("y2d        ", y2d, 0);
  printtext ("\n");
  printvektor2komplex ("x1d        ", x1d, 0);
  printvektor2komplex ("x2d        ", x2d, 0);
  printtext ("\n");
  printvektor2komplex ("x1ds/√-108 ", x1ds/sqrtr (ckomplexk (-108)), 0);
  printvektor2komplex ("x2ds/√-108 ", x2ds/sqrtr (ckomplexk (-108)), 0);
  printtext ("\n");
  printvektor2komplex ("y1k        ", y1k, 0);
  printvektor2komplex ("y2k        ", y2k, 0);
  printvektor2komplex ("y3k        ", y3k, 0);
  printtext ("\n");
  printvektor2komplex ("x1k        ", x1k, 0);
  printvektor2komplex ("x2k        ", x2k, 0);
  printvektor2komplex ("x3k        ", x3k, 0);
  printtext ("\n");
  printvektor2komplex ("x1ks       ", x1ks, 0);
  printvektor2komplex ("x2ks       ", x2ks, 0);
  printvektor2komplex ("x3ks       ", x3ks, 0);
  printtext ("\n");
  printvektor2komplex ("y1q        ", y1q, 0);
  printvektor2komplex ("y2q        ", y2q, 0);
  printvektor2komplex ("y3q        ", y3q, 0);
  printvektor2komplex ("y4q        ", y4q, 0);
  printtext ("\n");
  printvektor2komplex ("x1q        ", x1q, 0);
  printvektor2komplex ("x2q        ", x2q, 0);
  printvektor2komplex ("x3q        ", x3q, 0);
  printvektor2komplex ("x4q        ", x4q, 0);
  printtext ("\n");
  }

void quartischwegpdfw2 (ckomplexk x1s, ckomplexk x2s, ckomplexk x3s, ckomplexk& x4s)
  {
  ckomplexk aq, bq, cq, dq, pq, qq, rq, ak, bk, ck, pk, qk, ad, bd, pd, x1l, y1d, y2d, ad2, x1d, x2d, xd, z1k, z2k, z3k, y1k, y2k, y3k, ak3, x1k, x2k, x3k, xk;
  ckomplexk z, u, a1, a2, b1, b2, y1q, y2q, y3q, y4q, aq4, x1q, x2q, x3q, x4q;
  ckomplexk dpyq, dpyk, dpyd, x1ks, x2ks, x3ks, bla, x1ds, x2ds;

  // quartische Parameter aus den quartischen Lösungen: x1s, x2s, x3s, x4s -> aq, bq, cq, dq
  aq= -(x1s + x2s + x3s + x4s);
  bq= x1s*x2s + x1s*x3s + x1s*x4s + x2s*x3s + x2s*x4s + x3s*x4s;
  cq= -(x1s*x2s*x3s + x1s*x2s*x4s + x1s*x3s*x4s + x2s*x3s*x4s);
  dq= x1s*x2s*x3s*x4s;

  // zentrierte quartische Parameter aus den quartischen Parametern: aq, bq, cq, dq -> pq, qq, rq
  pq= aq*aq*3/-8 + bq;
  qq= aq*(aq*aq - bq*4)/8 + cq;
  rq= aq*((aq*bq - cq*4)*16 - aq*aq*aq*3)/256 + dq;

  // Parameter der kubischen Resolvente pdfw2 aus den zentrierten quartischen Parametern: qpp, qqp, qrp -> akp, bkp, ckp
  ak= pq*2;
  bk= pq*pq - rq*4;
  ck= qq*qq*-1;

  // Parameter der reduzierten kubischen Gleichung aus den Parametern der kubischen Gleichung
  pk= ak*ak/-3 + bk;
  qk= ak*(ak*ak/real (4.5) - bk)/3 + ck;

  // Parameter der quadratischen Resolvente
  ad= qk;
  bd= pk*pk*pk/-27;

  // Parameter der reduzierten quadratischen Gleichung aus den Parametern der normalen quadratischen Gleichung
  pd= bd - ad*ad/4;

  // Lösung der normalen linearen Gleichung aus den Parametern der reduzierten quadratischen Gleichung
  x1l= -pd;

  // Rückübergabe der linearen Lösungen an die quadratischen Lösungen
  y1d=  sqrtr (x1l);
  y2d= -sqrtr (x1l);

  // Rücktransformation der Lösungen der reduzierten quadratischen Gleichung in die Lösungen der normalen quadratischen Gleichung
  ad2= ad/2;
  x1d= y1d - ad2;
  x2d= y2d - ad2;

  // Rückübergabe der quadratischen Lösungen an die kubischen Lösungen
  xd= x1d;
  cbrtr (xd, z1k, z2k, z3k);
  y1k= z1k - pk/(z1k*3);
  y2k= z2k - pk/(z2k*3);
  y3k= z3k - pk/(z3k*3);

  // Rücktransformation der Lösungen der reduzierten kubischen Gleichung in die Lösungen der normalen kubischen Gleichung
  ak3= ak/3;
  x1k= y1k - ak3;
  x2k= y2k - ak3;
  x3k= y3k - ak3;

  // Rückübergabe der kubischen Lösungen an die quartischen Lösungen (pdfw2)
  xk= x1k;

  z= xk;
  u= sqrtr (z);

  a1=  u;
  a2= -u;
  b1= (z + pq - qq/u)/2;
  b2= (z + pq + qq/u)/2;

  quadratisch (a1, b1, y1q, y2q);
  quadratisch (a2, b2, y3q, y4q);

  // Rücktransformation der zentrierten quartischen Lösungen in die Lösungen der normalen quartischen Gleichung
  aq4= aq/4;
  x1q= y1q - aq4;
  x2q= y2q - aq4;
  x3q= y3q - aq4;
  x4q= y4q - aq4;

  // ---------------------------------------- Rückrechnungen ---------------------------------------------------------------------

  // Differenzenproduktquadrat der Lösungen der reduzierten quartischen Gleichung
  dpyq= (y1q-y2q)*(y1q-y3q)*(y1q-y4q)*(y2q-y3q)*(y2q-y4q)*(y3q-y4q);
  dpyq= dpyq*dpyq;

  // Differenzenproduktquadrat der Lösungen der reduzierten kubischen Gleichung
  dpyk= (y1k-y2k)*(y2k-y3k)*(y3k-y1k);
  dpyk= dpyk*dpyk;

  // Differenzenproduktquadrat der Lösungen der reduzierten quadratischen Gleichung
  dpyd= y1d-y2d;
  dpyd= dpyd*dpyd;

  // Lösungen der kubischen Resolvente aus den zentrierten quartischen Lösungen: y1q, y2q, y3q, y4q -> x1ks, x2ks, x3ks
  x1ks= y1q*y2q + y3q*y4q;
  x2ks= y1q*y3q + y2q*y4q;
  x3ks= y1q*y4q + y3q*y2q;

  // Lösungen der quadratischen Resolvente aus den zentrierten kubischen Lösungen: y1k, y2k, y3k -> x1ds, x2ds
  bla= (2*y1k - y2k - y3k)*(-y1k + 2*y2k - y3k)*(-y1k - y2k + 2*y3k)/sqrtr (real (27));
  x1ds= bla*ik - y1k*y2k*y2k - y2k*y3k*y3k - y3k*y1k*y1k + y1k*y1k*y2k + y2k*y2k*y3k + y3k*y3k*y1k;
  x2ds= bla*ik + y1k*y2k*y2k + y2k*y3k*y3k + y3k*y1k*y1k - y1k*y1k*y2k - y2k*y2k*y3k - y3k*y3k*y1k;

  // Variablenausgabe
  printtext ("********************************************************************************************** quartischwegpdfw2 **********************************************************************************************************\n");
  printvektor2komplex ("aq         ", aq, 0);
  printvektor2komplex ("bq         ", bq, 0);
  printvektor2komplex ("cq         ", cq, 0);
  printvektor2komplex ("dq         ", dq, 0);
  printtext ("\n");
  printvektor2komplex ("pq         ", pq, 1);
  printvektor2komplex ("qq         ", qq, 1);
  printvektor2komplex ("rq         ", rq, 1);
  printtext ("\n");
  printvektor2komplex ("ak         ", ak, 0);
  printvektor2komplex ("bk         ", bk, 0);
  printvektor2komplex ("ck         ", ck, 0);
  printtext ("\n");
  printvektor2komplex ("pk         ", pk, 1);
  printvektor2komplex ("qk         ", qk, 1);
  printtext ("\n");
  printvektor2komplex ("ad         ", ad, 1);
  printvektor2komplex ("bd         ", bd, 1);
  printtext ("\n");
  printvektor2komplex ("pd         ", pd, 1);
  printtext ("\n");
  printvektor2komplex ("x1l = D    ", x1l, 1);
  printvektor2komplex ("dpyq/-108  ", dpyq/-108, 1);
  printvektor2komplex ("dpyk/-108  ", dpyk/-108, 1);
  printvektor2komplex ("dpyd/4     ", dpyd/4, 1);
  printtext ("\n");
  printvektor2komplex ("y1d        ", y1d, 0);
  printvektor2komplex ("y2d        ", y2d, 0);
  printtext ("\n");
  printvektor2komplex ("x1d        ", x1d, 0);
  printvektor2komplex ("x2d        ", x2d, 0);
  printtext ("\n");
  printvektor2komplex ("x1ds/√-108 ", x1ds/sqrtr (ckomplexk (-108)), 0);
  printvektor2komplex ("x2ds/√-108 ", x2ds/sqrtr (ckomplexk (-108)), 0);
  printtext ("\n");
  printvektor2komplex ("y1k        ", y1k, 0);
  printvektor2komplex ("y2k        ", y2k, 0);
  printvektor2komplex ("y3k        ", y3k, 0);
  printtext ("\n");
  printvektor2komplex ("x1k        ", x1k, 0);
  printvektor2komplex ("x2k        ", x2k, 0);
  printvektor2komplex ("x3k        ", x3k, 0);
  printtext ("\n");
  printvektor2komplex ("x1ks       ", x1ks, 0);
  printvektor2komplex ("x2ks       ", x2ks, 0);
  printvektor2komplex ("x3ks       ", x3ks, 0);
  printtext ("\n");
  printvektor2komplex ("y1q        ", y1q, 0);
  printvektor2komplex ("y2q        ", y2q, 0);
  printvektor2komplex ("y3q        ", y3q, 0);
  printvektor2komplex ("y4q        ", y4q, 0);
  printtext ("\n");
  printvektor2komplex ("x1q        ", x1q, 0);
  printvektor2komplex ("x2q        ", x2q, 0);
  printvektor2komplex ("x3q        ", x3q, 0);
  printvektor2komplex ("x4q        ", x4q, 0);
  printtext ("\n");
  }

void quartischwegdiffpkurz (ckomplexk aq, ckomplexk bq, ckomplexk cq, ckomplexk dq, ckomplexk& x1, ckomplexk& x2, ckomplexk& x3, ckomplexk& x4)
  {
  ckomplexk pq, qq, rq, pk, qk, xl, x1d, x2d, xd, z1k, z2k, z3k, x1k, x2k, x3k, xk;
  ckomplexk z, u, a1, a2, b1, b2, y1, y2, y3, y4;
  ckomplexk dpy, z1, z2, z3;

  // normal -> zentriert: aq, bq, cq, dq -> pq, qq, rq
  pq= bq - aq*aq*3/8;
  qq= aq*(aq*aq - bq*4)/8 + cq;
  rq= aq*((aq*bq - cq*4)*16 - aq*aq*aq*3)/256 + dq;

  // Resolvente diffp: pq, qq, rq -> pk, qk
  pk= pq*pq/-3 - rq*4;
  qk= pq*(pq*pq/real (4.5) + rq*4)/-3 + pq*rq*4 - qq*qq;

  // Lösung der normalen linearen Gleichung aus den Parametern der reduzierten kubischen Gleichung: pk, qk -> xl
  xl= pk*pk*pk/27 + qk*qk/4;

  // Rücktransformation der Lösung der normalen linearen Gleichung in die Lösungen der normalen quadratischen Gleichung: xl, qk -> x1d, x2d
  x1d= qk/-2 + sqrtr (xl);
  x2d= qk/-2 - sqrtr (xl);

  // Rückübergabe einer quadratischen Lösungen an die kubischen Lösungen: xd, pk -> y1k, y2k, y3k
  xd= x1d;
  cbrtr (xd, z1k, z2k, z3k);

  x1k= z1k - pk/(z1k*3) + pq/3;
  x2k= z2k - pk/(z2k*3) + pq/3;
  x3k= z3k - pk/(z3k*3) + pq/3;

  // Rückübergabe einer kubischen Lösung an die quartischen Lösungen (diffp): xk, pq, qq -> a1, b1, c1, d1
  xk= x2k;

  z= xk;
  u= sqrtr (z - pq);

  a1=  u;
  a2= -u;
  b1= (z - qq/u)/2;
  b2= (z + qq/u)/2;

  quadratisch (a1, b1, y1, y2);
  quadratisch (a2, b2, y3, y4);

  // Rücktransformation der zentrierten quartischen Lösungen in die Lösungen der normalen quartischen Gleichung
  x1= y1 - aq/4;
  x2= y2 - aq/4;
  x3= y3 - aq/4;
  x4= y4 - aq/4;

  // --------------------------------------- Variablenausgabe --------------------------------------------------------------------
  printtext ("********************************************************************************************** quartischwegdiffpkurz ******************************************************************************************************\n");
  printvektor2komplex ("aq         ", aq, 0);
  printvektor2komplex ("bq         ", bq, 0);
  printvektor2komplex ("cq         ", cq, 0);
  printvektor2komplex ("dq         ", dq, 0);
  printtext ("\n");
  printvektor2komplex ("pq         ", pq, 1);
  printvektor2komplex ("qq         ", qq, 1);
  printvektor2komplex ("rq         ", rq, 1);
  printtext ("\n");
  printvektor2komplex ("pk         ", pk, 1);
  printvektor2komplex ("qk         ", qk, 1);
  printtext ("\n");
  printvektor2komplex ("xl (D)     ", xl, 1);
  printtext ("\n");
  printvektor2komplex ("y1d        ",  sqrtr (xl), 0);
  printvektor2komplex ("y2d        ", -sqrtr (xl), 0);
  printtext ("\n");
  printvektor2komplex ("x1d        ", x1d, 0);
  printvektor2komplex ("x2d        ", x2d, 0);
  printtext ("\n");
  printvektor2komplex ("x1k        ", x1k, 0);
  printvektor2komplex ("x2k        ", x2k, 0);
  printvektor2komplex ("x3k        ", x3k, 0);
  printtext ("\n");
  printvektor2komplex ("y1         ", y1, 0);
  printvektor2komplex ("y2         ", y2, 0);
  printvektor2komplex ("y3         ", y3, 0);
  printvektor2komplex ("y4         ", y4, 0);
  printtext ("\n");
  printvektor2komplex ("x1         ", x1, 0);
  printvektor2komplex ("x2         ", x2, 0);
  printvektor2komplex ("x3         ", x3, 0);
  printvektor2komplex ("x4         ", x4, 0);
  printtext ("\n");
  }

void quartischwegz1kurz (ckomplexk x1, ckomplexk x2, ckomplexk x3, ckomplexk& x4)
  {
  ckomplexk aq, bq, cq, dq, pq, qq, rq, pk, qk, xl, x1d, x2d, xd, z1k, z2k, z3k, y1k, y2k, y3k, yk;
  ckomplexk z, u, a1, a2, b1, b2, y1q, y2q, y3q, y4q, aq4, x1q, x2q, x3q, x4q;
  ckomplexk dpx, z1, z2, z3;

  // quartische Parameter aus den quartischen Lösungen: x1s, x2s, x3s, x4s -> aq, bq, cq, dq
  aq= -(x1 + x2 + x3 + x4);
  bq= x1*x2 + x1*x3 + x1*x4 + x2*x3 + x2*x4 + x3*x4;
  cq= -(x1*x2*x3 + x1*x2*x4 + x1*x3*x4 + x2*x3*x4);
  dq= x1*x2*x3*x4;

  // zentrierte quartische Parameter aus den quartischen Parametern: aq, bq, cq, dq -> pq, qq, rq
  pq= bq - aq*aq*3/8;
  qq= aq*(aq*aq - bq*4)/8 + cq;
  rq= aq*((aq*bq - cq*4)*16 - aq*aq*aq*3)/256 + dq;

  // Parameter der reduzierten kubischen Gleichung aus den Parametern der kubischen Gleichung
  pk= (pq*pq + rq*12)/-3;
  qk= pq*(rq*36 - pq*pq)/real (13.5) - qq*qq;

  // Lösung der normalen linearen Gleichung aus den Parametern der reduzierten quadratischen Gleichung
  xl= pk*pk*pk/27 + qk*qk/4;

  // Lösungen der normalen quadratischen Gleichung
  x1d= qk/-2 + sqrtr (xl);
  x2d= qk/-2 - sqrtr (xl);

  // Rückübergabe der quadratischen Lösungen an die kubischen Lösungen
  xd= x2d;
  cbrtr (xd, z1k, z2k, z3k);

  y1k= z1k - pk/(z1k*3);
  y2k= z2k - pk/(z2k*3);
  y3k= z3k - pk/(z3k*3);

  // Rückübergabe der kubischen Lösungen an die quartischen Lösungen (z3)
  yk= y1k;

  z= yk;
  u= sqrtr (z - pq*2/3);

  a1=  u;
  a2= -u;
  b1= (z + pq/3 - qq/u)/2;
  b2= (z + pq/3 + qq/u)/2;

  quadratisch (a1, b1, y1q, y2q);
  quadratisch (a2, b2, y3q, y4q);

  // Rücktransformation der zentrierten quartischen Lösungen in die Lösungen der normalen quartischen Gleichung
  aq4= aq/4;
  x1q= y1q - aq4;
  x2q= y2q - aq4;
  x3q= y3q - aq4;
  x4q= y4q - aq4;

  // ---------------------------------------- Rückrechnungen ---------------------------------------------------------------------

  // 1. Zwischenwert: Differenzenprodukt der Lösungen der normalen quartischen Gleichung
  dpx= (x1-x2)*(x1-x3)*(x1-x4)*(x2-x3)*(x2-x4)*(x3-x4);

  // 2. Zwischenwert: Lösungen der kubischen Resolvente aus den Lösungen der normalen quartischen Gleichung
  z1= y1q*y2q + y3q*y4q;
  z2= y1q*y3q + y2q*y4q;
  z3= y1q*y4q + y3q*y2q;

  // ---------------------------------------------------------- Variablenausgabe --------------------------------------------------------------------------
  printtext ("********************************************************************************************** quartischwegz1 kurz *************************************************************************************************************\n");
  printvektor2komplex ("aq         ", aq, 0);
  printvektor2komplex ("bq         ", bq, 0);
  printvektor2komplex ("cq         ", cq, 0);
  printvektor2komplex ("dq         ", dq, 0);
  printtext ("\n");
  printvektor2komplex ("pq         ", pq, 1);
  printvektor2komplex ("qq         ", qq, 1);
  printvektor2komplex ("rq         ", rq, 1);
  printtext ("\n");
  printvektor2komplex ("pk         ", pk, 1);
  printvektor2komplex ("qk         ", qk, 1);
  printtext ("\n");
  printvektor2komplex ("xl (D)     ", xl, 1);
  printtext ("\n");
  printvektor2komplex ("y1d        ",  sqrtr (xl), 0);
  printvektor2komplex ("y2d        ", -sqrtr (xl), 0);
  printtext ("\n");
  printvektor2komplex ("dpx/√-108  ", dpx/sqrtr (ckomplexk (-108)), 1);
  printtext ("\n");
  printvektor2komplex ("y1k        ", y1k, 0);
  printvektor2komplex ("y2k        ", y2k, 0);
  printvektor2komplex ("y3k        ", y3k, 0);
  printtext ("\n");
  printvektor2komplex ("z1         ", z1, 0);
  printvektor2komplex ("z2         ", z2, 0);
  printvektor2komplex ("z3         ", z3, 0);
  printtext ("\n");
  printvektor2komplex ("y1q        ", y1q, 0);
  printvektor2komplex ("y2q        ", y2q, 0);
  printvektor2komplex ("y3q        ", y3q, 0);
  printvektor2komplex ("y4q        ", y4q, 0);
  printtext ("\n");
  printvektor2komplex ("x1q        ", x1q, 0);
  printvektor2komplex ("x2q        ", x2q, 0);
  printvektor2komplex ("x3q        ", x3q, 0);
  printvektor2komplex ("x4q        ", x4q, 0);
  printtext ("\n");
  }

void quartischwegz3kurz (ckomplexk x1s, ckomplexk x2s, ckomplexk x3s, ckomplexk& x4s)
  {
  ckomplexk aq, bq, cq, dq, pq, qq, rq, pk, qk, xl, x1d, x2d, xd, z1k, z2k, z3k, y1k, y2k, y3k, yk;
  ckomplexk z, u, a1, a2, b1, b2, y1q, y2q, y3q, y4q, aq4, x1q, x2q, x3q, x4q;
  ckomplexk dpyq, dpyk, dpxd, x1ks, x2ks, x3ks, xks3, bla, x1ds, x2ds;

  // quartische Parameter aus den quartischen Lösungen: x1s, x2s, x3s, x4s -> aq, bq, cq, dq
  aq= -(x1s + x2s + x3s + x4s);
  bq= x1s*x2s + x1s*x3s + x1s*x4s + x2s*x3s + x2s*x4s + x3s*x4s;
  cq= -(x1s*x2s*x3s + x1s*x2s*x4s + x1s*x3s*x4s + x2s*x3s*x4s);
  dq= x1s*x2s*x3s*x4s;

  // zentrierte quartische Parameter aus den quartischen Parametern: aq, bq, cq, dq -> pq, qq, rq
  pq= bq - aq*aq*3/8;
  qq= aq*(aq*aq - bq*4)/8 + cq;
  rq= aq*((aq*bq - cq*4)*16 - aq*aq*aq*3)/256 + dq;

  // Parameter der reduzierten kubischen Gleichung aus den Parametern der kubischen Gleichung
  pk= -(pq*pq + rq*12)/3;
  qk= pq*(rq*36 - pq*pq)/real (13.5) - qq*qq;

  // Lösung der normalen linearen Gleichung aus den Parametern der reduzierten quadratischen Gleichung
  xl= pk*pk*pk*27 + qk*qk*real (182.25);

  // Rücktransformation der Lösungen der reduzierten quadratischen Gleichung in die Lösungen der normalen quadratischen Gleichung
  x1d= qk*real (-13.5) + sqrtr (xl);
  x2d= qk*real (-13.5) - sqrtr (xl);

  // Rückübergabe der quadratischen Lösungen an die kubischen Lösungen
  xd= x2d;
  cbrtr (xd, z1k, z2k, z3k);

  y1k= z1k - pk*3/z1k;
  y2k= z2k - pk*3/z2k;
  y3k= z3k - pk*3/z3k;

  // Rückübergabe der kubischen Lösungen an die quartischen Lösungen (z3)
  yk= y1k;

  z= yk;
  u= sqrtr ((z - pq*2)/3);

  a1=  u;
  a2= -u;
  b1= ((z + pq)/3 - qq/u)/2;
  b2= ((z + pq)/3 + qq/u)/2;

  quadratisch (a1, b1, y1q, y2q);
  quadratisch (a2, b2, y3q, y4q);

  // Rücktransformation der zentrierten quartischen Lösungen in die Lösungen der normalen quartischen Gleichung
  aq4= aq/4;
  x1q= y1q - aq4;
  x2q= y2q - aq4;
  x3q= y3q - aq4;
  x4q= y4q - aq4;

  // ---------------------------------------- Rückrechnungen ---------------------------------------------------------------------

  // Differenzenproduktquadrat der Lösungen der reduzierten quartischen Gleichung
  dpyq= (y1q-y2q)*(y1q-y3q)*(y1q-y4q)*(y2q-y3q)*(y2q-y4q)*(y3q-y4q);
  dpyq= dpyq*dpyq;

  // Differenzenproduktquadrat der Lösungen der reduzierten kubischen Gleichung
  dpyk= (y1k-y2k)*(y2k-y3k)*(y3k-y1k);
  dpyk= dpyk*dpyk;

  // Differenzenproduktquadrat der Lösungen der reduzierten quadratischen Gleichung
  dpxd= x1d-x2d;
  dpxd= dpxd*dpxd;

  // Lösungen der kubischen Resolvente aus den zentrierten quartischen Lösungen: y1q, y2q, y3q, y4q -> x1ks, x2ks, x3ks
  x1ks= x1s*x2s + x3s*x4s;
  x2ks= x1s*x3s + x2s*x4s;
  x3ks= x1s*x4s + x3s*x2s;
  xks3= x1ks + x2ks + x3ks;
  x1ks= x1ks*3;
  x2ks= x2ks*3;
  x3ks= x3ks*3;

  // Lösungen der quadratischen Resolvente aus den zentrierten kubischen Lösungen: y1k, y2k, y3k -> x1ds, x2ds
  bla= (2*x1ks - x2ks - x3ks)*(-x1ks + 2*x2ks - x3ks)*(-x1ks - x2ks + 2*x3ks)/sqrtr (real (27));
  x1ds= bla*ik - x1ks*x2ks*x2ks - x2ks*x3ks*x3ks - x3ks*x1ks*x1ks + x1ks*x1ks*x2ks + x2ks*x2ks*x3ks + x3ks*x3ks*x1ks;
  x2ds= bla*ik + x1ks*x2ks*x2ks + x2ks*x3ks*x3ks + x3ks*x1ks*x1ks - x1ks*x1ks*x2ks - x2ks*x2ks*x3ks - x3ks*x3ks*x1ks;

  // ---------------------------------------------------------- Variablenausgabe --------------------------------------------------------------------------
  printtext ("********************************************************************************************** quartischwegz3 *************************************************************************************************************\n");
  printvektor2komplex ("aq         ", aq, 0);
  printvektor2komplex ("bq         ", bq, 0);
  printvektor2komplex ("cq         ", cq, 0);
  printvektor2komplex ("dq         ", dq, 0);
  printtext ("\n");
  printvektor2komplex ("pq         ", pq, 1);
  printvektor2komplex ("qq         ", qq, 1);
  printvektor2komplex ("rq         ", rq, 1);
  printtext ("\n");
  printvektor2komplex ("pk         ", pk, 1);
  printvektor2komplex ("qk         ", qk, 1);
  printtext ("\n");
  printvektor2komplex ("xl = D     ", xl, 1);
  printvektor2komplex ("dpyq*-6.75 ", dpyq*-real (6.75), 1);
  printvektor2komplex ("dpyk/-108  ", dpyk/-108, 1);
  printvektor2komplex ("dpxd/4     ", dpxd/4, 1);
  printtext ("\n");
  printvektor2komplex ("x1d        ", x1d, 0);
  printvektor2komplex ("x2d        ", x2d, 0);
  printtext ("\n");
  printvektor2komplex ("x1ds/√-108 ", x1ds/sqrtr (ckomplexk (-108)), 0);
  printvektor2komplex ("x2ds/√-108 ", x2ds/sqrtr (ckomplexk (-108)), 0);
  printtext ("\n");
  printvektor2komplex ("y1k        ", y1k, 0);
  printvektor2komplex ("y2k        ", y2k, 0);
  printvektor2komplex ("y3k        ", y3k, 0);
  printtext ("\n");
  printvektor2komplex ("x1ks*3-xks3", x1ks - xks3, 0);
  printvektor2komplex ("x2ks*3-xks3", x2ks - xks3, 0);
  printvektor2komplex ("x3ks*3-xks3", x3ks - xks3, 0);
  printtext ("\n");
  printvektor2komplex ("y1q        ", y1q, 0);
  printvektor2komplex ("y2q        ", y2q, 0);
  printvektor2komplex ("y3q        ", y3q, 0);
  printvektor2komplex ("y4q        ", y4q, 0);
  printtext ("\n");
  printvektor2komplex ("x1q        ", x1q, 0);
  printvektor2komplex ("x2q        ", x2q, 0);
  printvektor2komplex ("x3q        ", x3q, 0);
  printvektor2komplex ("x4q        ", x4q, 0);
  printtext ("\n");
  }

void quartischzurueck (ckomplexk x1, ckomplexk x2, ckomplexk x3, ckomplexk x4, ckomplexk& aq, ckomplexk& bq, ckomplexk& cq, ckomplexk& dq)
  {
  ckomplexk y1, y2, y3, y4, dpy, z1, z2, z3;

  // quartische Parameter aus den quartischen Lösungen: x1, x2, x3, x4 -> aq, bq, cq, dq
  aq= -(x1 + x2 + x3 + x4);
  bq= x1*x2 + x1*x3 + x1*x4 + x2*x3 + x2*x4 + x3*x4;
  cq= -(x1*x2*x3 + x1*x2*x4 + x1*x3*x4 + x2*x3*x4);
  dq= x1*x2*x3*x4;

  // reduzierte Lösungen aus den normalen Lösungen: x1, x2, x3, x4 -> y1, y2, y3, y4
  y1= x1 + aq/4;
  y2= x2 + aq/4;
  y3= x3 + aq/4;
  y4= x4 + aq/4;

  // 1. Zwischenwert: Differenzenprodukt der Lösungen der normalen quartischen Gleichung
  dpy= (y1-y2)*(y1-y3)*(y1-y4)*(y2-y3)*(y2-y4)*(y3-y4);

  // 2. Zwischenwert: Lösungen der kubischen Resolvente aus den Lösungen der reduzierten quartischen Gleichung
  z1= y1*y2 + y3*y4;
  z2= y1*y3 + y2*y4;
  z3= y1*y4 + y2*y3;

  // ---------------------------------------------------------- Variablenausgabe --------------------------------------------------------------------------
  printtext ("----------------------------------------------------------- Parameter der normalen quartischen Gleichung --------------------------------------------------------------------\n");
  printvektor2komplex ("a          ", aq, 0);
  printvektor2komplex ("b          ", bq, 0);
  printvektor2komplex ("c          ", cq, 0);
  printvektor2komplex ("d          ", dq, 0);
  printtext ("\n");
  printtext ("----------------------------------------------------------- 1. Zwischenwert (Differenzenprodukt) ----------------------------------------------------------------------------\n");
  printvektor2komplex ("(y1-y2)*(y1-y3)*(y1-y4)*(y2-y3)*(y2-y4)*(y3-y4)", dpy, 1);
  printtext ("\n");
  printtext ("----------------------------------------------------------- 2. Zwischenwert (Produktsumme) ----------------------------------------------------------------------------------\n");
  printvektor2komplex ("y1y2 + y3y4", z1, 0);
  printvektor2komplex ("y1y3 + y2y4", z2, 0);
  printvektor2komplex ("y1y4 + y2y3", z3, 0);
  printtext ("\n");
  }

void quartischweg3 (real aq, real bq, real cq, real dq, ckomplexk& x1, ckomplexk& x2, ckomplexk& x3, ckomplexk& x4)
  {
  real pq, qq, rq, pk, qk, xl, ytrk, l, phi3, yrk, xrk, aq4;
  ckomplexk yk2, yk3, xk2, xk3, y1, y2, y3, y4, diffpxl, diffpyk, diffpyq, diffpy1, diffpy2, diffpy3;
  ckomplexk yk, z, uq, u, v, bed, b1, b2, D1, D2;
  ckomplexk nul1, nul2, nul3, nul4;

  // Parameter reduzierte quartische Gleichung
  pq= aq*aq/8*-3 + bq;
  qq= aq*(aq*aq/8 + bq/-2) + cq;
  rq= aq*(aq*aq*aq/8*(real (3)/-32) + aq*bq/16 + cq/-4) + dq;

  // Parameter der reduzierten kubischen Gleichung Resolvente diffp
  pk= pq*pq/-9 + rq*4/-3;
  qk= pq*(pq*pq/27 + rq*4/-3) + qq*qq/2;

  // Lösung der normalen linearen Gleichung
  xl= pk*pk*pk + qk*qk;

  // das Differenzenprodukt der Lösungen der reduzierten kubischen Gleichung
  diffpxl= -sqrtr (ckomplexk (xl*-108));

  // Lösungen der kubischen Resolvente
  if (xl > 0)                                                     // xl= 0: drei reelle Lösungen der kubischen Resolvente davon eine doppelt, 4 reelle Lösungen der quartischen Gleichung davon eine doppelt
    {                                                             // eine reelle, 2 komplexe Lösungen der kubischen Resolvente, 2 reelle Lösungen der quartischen Gleichung
    if (qk >= 0)                                                  // Fallunterscheidung notwendig, sonst zusätzliche Stern-Artefakte beim Torus
      ytrk= cbrtr (qk + sqrtr (xl));
      else
      ytrk= cbrtr (qk - sqrtr (xl));
    yk2= ckomplexk (ytrk/-2, ytrk*-sqrtr (real (0.75)));
    yk3= ckomplexk (yk2.x, -yk2.y);

    yrk= (ytrk - pk/ytrk);
    yk2= (yk2 - pk/yk2);
    yk3= (yk3 - pk/yk3);
    }
    else
    {
    // 3 reelle Lösungen der kubischen Resolvente, 4 reelle Lösungen der quartischen Gleichung
    l= sqrtr (-pk);                                              // -pk nie unter 0 wegen xl
    phi3= acosr (qk/(pk*-l))/3;
    yrk= l*cosr (phi3)*2;                         // Bereichsüberschreitung acos abfangen lohnt nicht, nur ein Wert 1.000000119 (Float32) sehr selten
    yk2= l*cosr (phi3 - PI2d)*2;
    yk3= l*cosr (phi3 + PI2d)*2;
    }

  // das Differenzenprodukt der Lösungen der reduzierten kubischen Gleichung
  diffpyk= (yrk-yk2)*(yk2-yk3)*(yk3-yrk);

  // Lösung der normalen kubischen Gleichung
  xrk= yrk + pq/3;
  xk2= yk2 + pq/3;
  xk3= yk3 + pq/3;

  // Lösungen der beiden quadratischen Gleichungen (ak=-pq/2 für Rückreduzierung)
  yk= yrk;

  z= yk/2 + pq/6;
  uq= yk/4 - pq/6;
  u= sqrtr (uq);                                                  // u > 0 wegen Ungenauigkeit, Abfangen bringt nur rote Fehlerpixel
  v= sqrtr (z*z - rq);                                            // zzrq < 0 wegen Ungenauigkeit, abfangen bringt nur rote Fehlerpixel

  // Bedingung -2uv = qq
  bed= u*v*-2;
  if (absr (bed + qq) < absr (bed - qq))
    {
    b1= z - v;
    b2= z + v;
    }
    else
    {
    b1= z + v;
    b2= z - v;
    }

  D1= sqrtr (uq - b1);
  D2= sqrtr (uq - b2);

  // Lösungen der reduzierten quartischen Gleichung
  aq4= aq/-4;
  y1= -u - D1;
  y2= -u + D1;
  y3=  u - D2;
  y4=  u + D2;

  // das Differenzenprodukt der Lösungen der reduzierten quartischen Gleichung
  diffpyq= (y1-y2)*(y1-y3)*(y1-y4)*(y2-y3)*(y2-y4)*(y3-y4);

  // Die kubische Resolvente diffp aus den Lösungen der reduzierten quartischen Gleichung
  diffpy1= y1*y2 + y3*y4;
  diffpy2= y1*y3 + y2*y4;
  diffpy3= y1*y4 + y2*y3;

  // Lösungen der normalen quartischen Gleichung
  x1= aq4 + y1;
  x2= aq4 + y2;
  x3= aq4 + y3;
  x4= aq4 + y4;

  // Nullstellen der normalen quartischen Gleichung
  nul1= x1*x1*x1*x1 + x1*x1*x1*aq + x1*x1*bq + x1*cq + dq;
  nul2= x2*x2*x2*x2 + x2*x2*x2*aq + x2*x2*bq + x2*cq + dq;
  nul3= x3*x3*x3*x3 + x3*x3*x3*aq + x3*x3*bq + x3*cq + dq;
  nul4= x4*x4*x4*x4 + x4*x4*x4*aq + x4*x4*bq + x4*cq + dq;

  printtext ("-------------------------------- quartischweg3 ----------------------------------------------------------------------------------------------------------------------------\n");
  printtext ("-------------------------------- Parameter --------------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("a           ", aq, 0);
  printvektor2komplex ("b           ", bq, 0);
  printvektor2komplex ("c           ", cq, 0);
  printvektor2komplex ("d           ", dq, 0);
  printtext ("\n");

  printtext ("-------------------------------- xl ----------------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("xl          ", xl, 0);
  printtext ("\n");

  printtext ("-------------------------------- reduzierte kubische Resolvente diffp ---------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("yrk         ", yrk, 0);
  printvektor2komplex ("yk2         ", yk2, 0);
  printvektor2komplex ("yk3         ", yk3, 0);
  printtext ("\n");

  printtext ("-------------------------------- normale kubische Resolvente diffp -------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("xrk         ", xrk, 0);
  printvektor2komplex ("xk2         ", xk2, 0);
  printvektor2komplex ("xk3         ", xk3, 0);
  printtext ("\n");

  printtext ("-------------------------------- Lösungspolynome der reduzierten quartischen Lösungen ---------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("y1y2 + y3y4 ", diffpy1, 0);
  printvektor2komplex ("y1y3 + y2y4 ", diffpy2, 0);
  printvektor2komplex ("y1y4 + y2y3 ", diffpy3, 0);
  printtext ("\n");

  printtext ("-------------------------------- skalierte normale lineare Lösung -------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("-√(xl*-108) ", diffpxl, 0);
  printtext ("\n");

  printtext ("-------------------------------- Differenzenprodukt der Lösungen der reduzierten kubischen Resolvente diffp ------------------------------------------------------------------------------\n");
  printvektor2komplex ("diffpyk     ", diffpyk, 0);
  printtext ("\n");

  printtext ("-------------------------------- Differenzenprodukt der Lösungen der reduzierten quartischen Gleichung --------------------------------------------------------------------------------------\n");
  printvektor2komplex ("diffpyq     ", diffpyq, 0);
  printtext ("\n");

  printtext ("-------------------------------- Lösungen der normalen quartischen Gleichung -----------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("x1          ", x1, 0);
  printvektor2komplex ("x2          ", x2, 0);
  printvektor2komplex ("x3          ", x3, 0);
  printvektor2komplex ("x4          ", x4, 0);
  printtext ("\n");

  printtext ("-------------------------------- Nullstellen der normalen quartischen Gleichung ---------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("nul1          ", nul1, 0);
  printvektor2komplex ("nul2          ", nul2, 0);
  printvektor2komplex ("nul3          ", nul3, 0);
  printvektor2komplex ("nul4          ", nul4, 0);
  printtext ("\n");
  }

void quartischparameter ()
  {
  ckomplexk a, b, c, d, p, q, r, z1, z2, z3, dp, y1, y2, y3, y4, x1, x2, x3, x4;

  vektor2eingabek (a);
  vektor2eingabek (b);
  vektor2eingabek (c);
  vektor2eingabek (d);

  quartischweg3 (a.x, b.x, c.x, d.x, x1, x2, x3, x4);
  return;

  quartischreduziertk (a, b, c, d, p, q, r);

  kubischeresolventediffp (p, q, r, z1, z2, z3);
  dp= (z1 - z2)*(z2 - z3)*(z3 - z1);
  printtext ("---------------------- Differenzenprodukt der kubischen Resolvente diffp --------------------------------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("dp          ", dp, 0);
  printtext ("\n");

  printtext ("---------------------- kubische Resolvente diffp -------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("z1          ", z1, 0);
  printvektor2komplex ("z2          ", z2, 0);
  printvektor2komplex ("z3          ", z3, 0);
  printtext ("\n");

  kubischeresolventez (p, q, r, z1, z2, z3);
  dp= (z1 - z2)*(z2 - z3)*(z3 - z1);
  printtext ("---------------------- Differenzenprodukt der kubischen Resolvente z --------------------------------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("dp          ", dp, 0);
  printtext ("\n");

  printtext ("---------------------- kubische Resolvente z -------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("z1          ", z1, 0);
  printvektor2komplex ("z2          ", z2, 0);
  printvektor2komplex ("z3          ", z3, 0);
  printtext ("\n");

  quartischreduziertbuchf (p, q, r, y1, y2, y3, y4);
  printtext ("---------------------- quartisch buchf -----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("x1          ", y1 - a/4, 0);
  printvektor2komplex ("x2          ", y2 - a/4, 0);
  printvektor2komplex ("x3          ", y3 - a/4, 0);
  printvektor2komplex ("x3          ", y4 - a/4, 0);
  printtext ("\n");

  //quartischwegdiffpkurz (a, b, c, d, x1, x2, x3, x4);
  //quartischzurück (x1, x2, x3, x4, a, b, c, d);
  }

void quartischloesungen ()
  {
  ckomplexk x1, x2, x3, x4, a, b, c, d;
  cschnittpunkte psp;

  vektor2eingabek (x1);
  vektor2eingabek (x2);
  vektor2eingabek (x3);
  vektor2eingabek (x4);

  quartischzurueck (x1, x2, x3, x4, a, b, c, d);

  quartischdiffpuintrc (a.x, b.x, c.x, d.x, x1, x2, x3, x4);

  printtext ("-------------------------------- quartischdiffpuintrc Lösungen ----------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("x1          ", x1, 0);
  printvektor2komplex ("x2          ", x2, 0);
  printvektor2komplex ("x3          ", x3, 0);
  printvektor2komplex ("x4          ", x4, 0);
  printtext ("\n");

  quartischdiffpuintr (a.x, b.x, c.x, d.x, psp);

  printtext ("-------------------------------- quartischdiffpuintr Lösungen ----------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("anz         ", real (psp.anz), 0);
  printvektor2komplex ("x1          ", psp.abstand[0], 0);
  printvektor2komplex ("x2          ", psp.abstand[1], 0);
  printvektor2komplex ("x3          ", psp.abstand[2], 0);
  printvektor2komplex ("x4          ", psp.abstand[3], 0);
  printtext ("\n");

  psp.anz= 0;
  quartischdiffpvintr (a.x, b.x, c.x, d.x, psp);

  printtext ("-------------------------------- quartischdiffpvintr Lösungen ----------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("anz         ", real (psp.anz), 0);
  printvektor2komplex ("x1          ", psp.abstand[0], 0);
  printvektor2komplex ("x2          ", psp.abstand[1], 0);
  printvektor2komplex ("x3          ", psp.abstand[2], 0);
  printvektor2komplex ("x4          ", psp.abstand[3], 0);
  printtext ("\n");

  psp.anz= 0;
  quartischdiffpfintr (a.x, b.x, c.x, d.x, psp);

  printtext ("-------------------------------- quartischdiffpfintr Lösungen ----------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("anz         ", real (psp.anz), 0);
  printvektor2komplex ("x1          ", psp.abstand[0], 0);
  printvektor2komplex ("x2          ", psp.abstand[1], 0);
  printvektor2komplex ("x3          ", psp.abstand[2], 0);
  printvektor2komplex ("x4          ", psp.abstand[3], 0);
  printtext ("\n");

  psp.anz= 0;
  quartischbuchfintr (a.x, b.x, c.x, d.x, psp);

  printtext ("-------------------------------- quartischbuchfintr Lösungen ----------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("anz         ", real (psp.anz), 0);
  printvektor2komplex ("x1          ", psp.abstand[0], 0);
  printvektor2komplex ("x2          ", psp.abstand[1], 0);
  printvektor2komplex ("x3          ", psp.abstand[2], 0);
  printvektor2komplex ("x4          ", psp.abstand[3], 0);
  printtext ("\n");

  psp.anz= 0;
  quartischlagrangeuintr (a.x, b.x, c.x, d.x, psp);

  printtext ("-------------------------------- quartischlagrangeuintr Lösungen ----------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("anz         ", real (psp.anz), 0);
  printvektor2komplex ("x1          ", psp.abstand[0], 0);
  printvektor2komplex ("x2          ", psp.abstand[1], 0);
  printvektor2komplex ("x3          ", psp.abstand[2], 0);
  printvektor2komplex ("x4          ", psp.abstand[3], 0);
  printtext ("\n");

  psp.anz= 0;
  quartischlagrangecintr (a.x, b.x, c.x, d.x, psp);

  printtext ("-------------------------------- quartischlagrangecintr Lösungen ----------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("anz         ", real (psp.anz), 0);
  printvektor2komplex ("x1          ", psp.abstand[0], 0);
  printvektor2komplex ("x2          ", psp.abstand[1], 0);
  printvektor2komplex ("x3          ", psp.abstand[2], 0);
  printvektor2komplex ("x4          ", psp.abstand[3], 0);
  printtext ("\n");

  //quartischwegdiffpkurz (a, b, c, d, x1, x2, x3, x4);
  //quartisch (a, b, c, d, x1, x2, x3, x4);
  //quartischdiffpint (a, b, c, d, x1, x2, x3, x4);
  }

void quartischeingabezw ()
  {
  ckomplexk x1, x2, x3, x4;

  vektor2eingabek (x1);
  vektor2eingabek (x2);
  vektor2eingabek (x3);
  vektor2eingabek (x4);

//  quartischzwischenwerte (x1, x2, x3, x4);
//  quartischwegdiffp (x1, x2, x3, x4);
//  quartischwegpdfw2 (x1, x2, x3, x4);
//  quartischwegdiffpkurz (x1, x2, x3, x4);
  quartischwegz1kurz (x1, x2, x3, x4);
//  quartischwegz3kurz (x1, x2, x3, x4);
  }

//--------------------------------------------------------------------------- Formeln mit Bezug zur quintischen Gleichung ----------------------------------------------------------------------------------------------------------

void kubischelementar (ckomplexk a, ckomplexk b, ckomplexk c, ckomplexk& x1, ckomplexk& x2, ckomplexk& x3)
  {
  ckomplexk d, f1, f2, f3, r1, r2, r3, f_1, f_2, f_3, r_1, r_2, r_3, ff1, ff2, ff3, f_f1, f_f2, f_f3, dp;
  ckomplexk fr1, fr2, fr3, rr1, rr2, rr3, k;
  real ar, br, cr, dr;

  kubisch (a, b, c, x1, x2, x3);

  printtext ("-------------------------------------------- Berechnung der Zwischenwerte aus den Lösungen ------------------------------------------------------------------\n");
  printvektor2komplex ("x1", x1, 0);
  printvektor2komplex ("x2", x2, 0);
  printvektor2komplex ("x3", x3, 0);
  printtext ("\n");

  r1= x1 + x2*e31 + x3*e32;
  r2= x1 + x2*e32 + x3*e31;
  r3= x1 + x2 + x3;

  r_1= x2 + x1*e31 + x3*e32;
  r_2= x2 + x1*e32 + x3*e31;
  r_3= x2 + x1 + x3;

  printvektor2komplex ("r1", r1, 0);
  printvektor2komplex ("r2", r2, 0);
  printvektor2komplex ("r3", r3, 0);
  printvektor2komplex ("r_1", r_1, 0);
  printvektor2komplex ("r_2", r_2, 0);
  printvektor2komplex ("r_3", r_3, 0);
  printtext ("\n");

  f1= r1*r1*r1;
  f2= r2*r2*r2;
  f3= r3*r3*r3;

  f_1= r_1*r_1*r_1;
  f_2= r_2*r_2*r_2;
  f_3= r_3*r_3*r_3;

  printvektor2komplex ("f1", f1, 0);
  printvektor2komplex ("f2", f2, 0);
  printvektor2komplex ("f3", f3, 0);
  printvektor2komplex ("f_1", f_1, 0);
  printvektor2komplex ("f_2", f_2, 0);
  printvektor2komplex ("f_3", f_3, 0);
  printtext ("\n");

  ff1= f1 + f_1;
  ff2= f2 + f_2;
  ff3= f3 + f_3;

  f_f1= f1 - f_1;
  f_f2= f2 - f_2;
  f_f3= f3 - f_3;

  f_f1= f_f1*f_f1;
  f_f2= f_f2*f_f2;
  f_f3= f_f3*f_f3;

  printvektor2komplex ("ff1", ff1, 0);
  printvektor2komplex ("ff2", ff2, 0);
  printvektor2komplex ("ff3", ff3, 0);
  printvektor2komplex ("f_f1", f_f1, 0);
  printvektor2komplex ("f_f2", f_f2, 0);
  printvektor2komplex ("f_f3", f_f3, 0);
  printtext ("\n");

  dp= (x1-x2)*(x2-x3)*(x3-x1);

  printvektor2komplex ("dp", dp, 0);
  printtext ("\n");

  k= (x1*x1*x2 + x2*x2*x1 + x2*x2*x3 + x3*x3*x2 + x3*x3*x1 + x1*x1*x3)/2;

  printvektor2komplex ("k", k, 0);
  printtext ("\n");

  printtext ("-------------------------------------------- Berechnung der Zwischenwerte aus den Koeffizienten -------------------------------------------------------------\n");
  ar= a.x;
  br= b.x;
  cr= c.x;

  d= a*a*b*b + a*a*a*c*-4 + b*b*b*-4 + a*b*c*18 + c*c*-27;
  dr= ar*ar*br*br + ar*ar*ar*cr*-4 + br*br*br*-4 + ar*br*cr*18 + cr*cr*-27;
  dr= sqrtr (dr);
  d= sqrtr (d);

//  f1= -a*a*a + a*b*9/-2 + c*27/-2 + ik*d*sqrtr (real (6.75));
//  f2= -a*a*a + a*b*9/-2 + c*27/-2 + ik*d*-sqrtr (real (6.75));
  f3= -(a*a*a);

  printvektor2komplex ("f1", f1, 0);
  printvektor2komplex ("f2", f2, 0);
  printvektor2komplex ("f3", f3, 0);
  printtext ("\n");

  fr1= -ar*ar*ar + ar*br*9/-2 + cr*27/-2 + ik*d*sqrtr (real (6.75));
  fr2= -ar*ar*ar + ar*br*9/-2 + cr*27/-2 + ik*d*-sqrtr (real (6.75));
  fr3= -(ar*ar*ar);

  printvektor2komplex ("fr1", fr1, 0);
  printvektor2komplex ("fr2", fr2, 0);
  printvektor2komplex ("fr3", fr3, 0);
  printtext ("\n");

  r1= cbrtr (f1);
  r2= cbrtr (f2);
  r3= cbrtr (f3);

  rr1= cbrtr (fr1);
  rr2= cbrtr (fr2);
  rr3= cbrtr (fr3);

  printvektor2komplex ("r1", r1, 0);
  printvektor2komplex ("r2", r2, 0);
  printvektor2komplex ("r3", r3, 0);
  printtext ("\n");

  printvektor2komplex ("rr1", rr1, 0);
  printvektor2komplex ("rr2", rr2, 0);
  printvektor2komplex ("rr3", rr3, 0);
  printtext ("\n");

  x1= (r1 + r2 + r3)/3;
  x2= (r1*e32 + r2*e31 + r3)/3;
  x3= (r1*e31 + r2*e32 + r3)/3;

  printvektor2komplex ("x1 a", x1, 0);
  printvektor2komplex ("x2 a", x2, 0);
  printvektor2komplex ("x3 a", x3, 0);
  printtext ("\n");
/*
  for (integer lauf1= 0; lauf1 < 3; lauf1++)
  for (integer lauf2= 0; lauf2 < 3; lauf2++)
  for (integer lauf3= 0; lauf3 < 3; lauf3++)
    {
    r1= r1*pown (e31,lauf1);
    r2= r2*pown (e31,lauf2);
    r3= r3*pown (e31,lauf3);

    printvektor2komplex ("r1", r1, 0);
    printvektor2komplex ("r2", r2, 0);
    printvektor2komplex ("r3", r3, 0);
    printtext ("\n");

    x1= (r1 + r2 + r3)/3;
    x2= (r1*e32 + r2*e31 + r3)/3;
    x3= (r1*e31 + r2*e32 + r3)/3;

    printvektor2komplex ("x1", x1, 0);
    printvektor2komplex ("x2", x2, 0);
    printvektor2komplex ("x3", x3, 0);
    printtext ("\n");
    }
*/
  }

// Bestimmung x1-x5 aus c, d, z (bikubische Resolvente)
void quintischnacktresolvente (real c, real d, real z, ckomplexk& x1, ckomplexk& x2, ckomplexk& x3, ckomplexk& x4, ckomplexk& x5, real& pr)
  {
  real m, n, p, q, tv, tw, y, r, v, w;
  ckomplexk v1, v2, v3, v4;
  ckomplexk e51, e52, zp1, zp2, zp3, zp4, zp5, zp6, dp, pr1, pr2, pr3, pr4, pr5;

  
  y= sqrtr (z)/5;
  r= y*d/(y*y*25 - c);
  v= (y*y*y*3 - y*c - r*r)/(y*2);
  w= (y*y*y*3 - y*c + r*r)/(y*2);

  tv= (y*y + v)*r/(y*2);
  tw= (y*y + w)*r/(y*2);

  // 1. und 2. fünfte Einheitswurzeln
  e51= ckomplexk (cosr (PI*2/5), sinr (PI*2/5));
  e52= ckomplexk (cosr (PI*4/5), sinr (PI*4/5));

  m= qnrtr (tv - sqrtr (tv*tv + y*y*y*y*y));
  n= qnrtr (tv + sqrtr (tv*tv + y*y*y*y*y));
  p= qnrtr (tw + sqrtr (tw*tw - y*y*y*y*y));
  q= qnrtr (tw - sqrtr (tw*tw - y*y*y*y*y));

  // Bedingungsgleichung v= m³p + n³q muss erfüllt sein  (m,n) bzw. (p,q) permutieren
  v1= m*m*m*p + n*n*n*q;
  v2= n*n*n*p + m*m*m*q;
  if (absr (v - v1) > 0.1)
    {
    printvektor2komplex ("v  ", v, 1);
//*
    printtext ("\n");
    printvektor2komplex ("v1 ", v1, 1);
    printvektor2komplex ("v2 ", v2, 1);
    printtext ("\n");
    printvektor2komplex ("m  ", m, 1);
    printvektor2komplex ("n  ", n, 1);
    printvektor2komplex ("p  ", p, 1);
    printvektor2komplex ("q  ", q, 1);
    printtext ("\n");
//*/
    }

  x1= -(m + p + q + n);
  x2= -(m*e51 + p*e52 + q/e52 + n/e51);
  x3= -(m*e52 + p/e51 + q*e51 + n/e52);
  x4= -(m/e52 + p*e51 + q/e51 + n*e52);
  x5= -(m/e51 + p/e52 + q*e52 + n*e51);

  pr1= x1*x1*x1*x1*x1 + x1*c*5 + d;
  pr2= x2*x2*x2*x2*x2 + x2*c*5 + d;
  pr3= x3*x3*x3*x3*x3 + x3*c*5 + d;
  pr4= x4*x4*x4*x4*x4 + x4*c*5 + d;
  pr5= x5*x5*x5*x5*x5 + x5*c*5 + d;

  pr= absr (pr1);
  if (absr (pr2) > pr)
    pr= absr (pr2);
  if (absr (pr3) > pr)
    pr= absr (pr3);
  if (absr (pr4) > pr)
    pr= absr (pr4);
  if (absr (pr5) > pr)
    pr= absr (pr5);

//*
  zp1= (x1*x2 + x2*x3 + x3*x4 + x4*x5 + x5*x1);
  zp1= zp1*zp1;
  zp2= (x2*x1 + x1*x3 + x3*x4 + x4*x5 + x5*x2);
  zp2= zp2*zp2;
  zp3= (x1*x3 + x3*x2 + x2*x4 + x4*x5 + x5*x1);
  zp3= zp3*zp3;

  dp= (x1-x2)*(x1-x3)*(x1-x4)*(x1-x5)*(x2-x3)*(x2-x4)*(x2-x5)*(x3-x4)*(x3-x5)*(x4-x5);

  printtext ("-------------------------------- 1. Zwischenwert Differenzenprodukt --------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("(x1-x2)*(x1-x3)*(x1-x4)*(x1-x5)*(x2-x3)*(x2-x4)*(x2-x5)*(x3-x4)*(x3-x5)*(x4-x5)", dp, 0);
  printtext ("\n");
  printtext ("-------------------------------- 2. Zwischenwert bikubische Resolvente --------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("(x1*x2 + x2*x3 + x3*x4 + x4*x5 + x5*x1)", zp1, 0);
  printvektor2komplex ("(x2*x1 + x1*x3 + x3*x4 + x4*x5 + x5*x2)", zp2, 0);
  printvektor2komplex ("(x1*x3 + x3*x2 + x2*x4 + x4*x5 + x5*x1)", zp3, 0);
  printtext ("\n");
  printvektor2komplex ("5z          ", z*5, 0);
  printvektor2komplex ("z           ", z, 0);
  printvektor2komplex ("25y²        ", y*y*25, 0);
  printtext ("\n");

  printvektor2komplex ("y           ", y, 0);
  printvektor2komplex ("r           ", r, 0);
  printvektor2komplex ("v           ", v, 0);
  printvektor2komplex ("w           ", w, 0);
  printtext ("\n");

  printvektor2komplex ("m           ", m, 0);
  printvektor2komplex ("n           ", n, 0);
  printvektor2komplex ("p           ", p, 0);
  printvektor2komplex ("q           ", q, 0);
  printtext ("\n");

  printvektor2komplex ("v1          ", v1, 0);
  printvektor2komplex ("e51         ", e51, 0);
  printvektor2komplex ("e52         ", e52, 0);
  printtext ("\n");
//*/
  }

void quintischparameter ()
  {
  real c, d, z, pr;
  ckomplexk x1, x2, x3, x4, x5, pr1, pr2, pr3, pr4, pr5, cp, dp;

  //vektor2eingabek (c);
  //vektor2eingabek (d);

/*
  for (real lauf3= 0; lauf3 <= 6; lauf3+= 2)
  for (real lauf5= 2; lauf5 <= 14; lauf5+= 2)
  for (real lauf7= 0; lauf7 <= 6; lauf7+= 2)
    {
    z= powr (3, lauf3)*powr (5, lauf5)*powr (7, lauf7);
    quintischnacktresolvente (c, d, z, x1, x2, x3, x4, x5, pr);
    //printf ("z= %24.2Lf  pr= %20.10Lf\n", z, pr);
    printtext ("  l3  ");
    printreal (lauf3);
    printtext ("  l5  ");
    printreal (lauf5);
    printtext ("  l6  ");
    printreal (lauf7);
    printtext ("  z=  ");
    printreal (z);
    printtext ("  pr=  ");
    printreal (pr);
    printtext ("\n");
    }

  return;
//*/

  c= -525;
  d= -61500;
  z= 5625;

  quintischnacktresolvente (c, d, z, x1, x2, x3, x4, x5, pr);

  pr1= x1*x1*x1*x1*x1 + x1*c*5 + d;
  pr2= x2*x2*x2*x2*x2 + x2*c*5 + d;
  pr3= x3*x3*x3*x3*x3 + x3*c*5 + d;
  pr4= x4*x4*x4*x4*x4 + x4*c*5 + d;
  pr5= x5*x5*x5*x5*x5 + x5*c*5 + d;

  dp= -(x1*x2*x3*x4*x5);
  cp= (x1*x2*x3*x4 + x1*x2*x3*x5 + x1*x2*x4*x5 + x1*x3*x4*x5 + x2*x3*x4*x5)/5;

  printtext ("-------------------------------- quintisch Lösungen ----------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("x1          ", x1, 0);
  printvektor2komplex ("x2          ", x2, 0);
  printvektor2komplex ("x3          ", x3, 0);
  printvektor2komplex ("x4          ", x4, 0);
  printvektor2komplex ("x5          ", x5, 0);
  printtext ("\n");

  printtext ("-------------------------------- Nullstellenprobe ----------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("pr           ", pr, 0);
  printtext ("\n");
  printvektor2komplex ("pr1          ", pr1, 0);
  printvektor2komplex ("pr2          ", pr2, 0);
  printvektor2komplex ("pr3          ", pr3, 0);
  printvektor2komplex ("pr4          ", pr4, 0);
  printvektor2komplex ("pr5          ", pr5, 0);
  printtext ("\n");

  printtext ("-------------------------------- Koeffizientenprobe -----------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("cp           ", cp, 0);
  printvektor2komplex ("dp           ", dp, 0);
  }

//--------------------------------------------------------------------------- andere Sachen --------------------------------------------------------------------------------------------------------------------------------------

void polartest ()
  {
  ckomplexk ein;
  ckomplexp austan2, austan, auscos, aus180, aus360;

  vektor2eingabek (ein);

  austan2= polar180 (ein);
  auscos= polarcos180 (ein);
  austan= polartan180 (ein);
  aus360= polar360 (ein);
/*
  printf ("\nPolarkoordinaten:\n");
  printf ("Eingabe:                  %60.40Lf %60.40Lf\n\n", ein.x, ein.y);
  printf ("polartan2:                %60.40Lf %60.40Lf\n", austan2.b, austan2.w*180/M_PIl);
  printf ("polarcos:                 %60.40Lf %60.40Lf\n", auscos.b, auscos.w*180/M_PIl);
  printf ("polartan:                 %60.40Lf %60.40Lf\n", austan.b, austan.w*180/M_PIl);
  printf ("\n");
  printf ("polar180:                 %60.40Lf %60.40Lf\n", aus180.b, aus180.w*180/M_PIl);
  printf ("polar360:                 %60.40Lf %60.40Lf\n", aus360.b, aus360.w*180/M_PIl);
  printf ("\n");
*/
  }

void sqrttest ()
  {
  ckomplexk ein;
  ckomplexk w1, w2, q1, q2;

  vektor2eingabek (ein);

  w1= sqrtr (ein);
  w2= sqrtkr (ein);

  q1= w1*w1;
  q2= w2*w2;

  printtext ("-------------------------------- Parameter der quartischen Gleichung ---------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("Wert          ", ein, 1);
  printtext ("\n");
  printvektor2komplex ("sqrtr         ", w1, 1);
  printvektor2komplex ("sqrtrk        ", w2, 1);
  printtext ("\n");
  printvektor2komplex ("q1            ", q1, 1);
  printvektor2komplex ("q2            ", q2, 1);
  printtext ("\n");
  }

integer entscheidungseingabe ()
  {
  integer scanret, ent;

  printtext ("\n");
  printtext (" [1] quadratisch  K   [2] kubisch  K     [3] quartisch  K\n");
  printtext (" [4] quadratisch  L   [5] kubisch  L     [6] quartisch  L\n");
  printtext (" [7] quadratischw1 L  [8] kubischw1 L    [9] quartischw1 L\n");
  printtext (" [91] sqrttest        [92] quintisch K\n");
  printtext ("\n");

  scanret= scanf ("%lld", &ent);
  scanret++;  // scanret benutzen
  printtext ("\n");
  return ent;
  }

//----------------------------------------------------- Hauptprogramm -----------------------------------------------------------------------------------------------------------------------------------------------------------------

int main ()
  {
  integer ent (entscheidungseingabe ());
  switch (ent)
    {
    case 1:
      quadratischparameter ();
      break;
    case 4:
      quadratischloesungen ();
      break;
    case 7:
      quadratischeingabezw ();
      break;
    case 2:
      kubischparameter ();
      break;
    case 5:
      kubischloesungen ();
      break;
    case 8:
      kubischeingabezw ();
      break;
    case 3:
      quartischparameter ();
      break;
    case 6:
      quartischloesungen ();
      break;
    case 9:
      quartischeingabezw ();
      break;
    case 91:
      sqrttest ();
      break;
    case 92:
      quintischparameter ();
      break;
    }
  return 0;
  }

//******************************************************************** Zeichenkodierung ************************************************************************************************************************
/*

  qk= -pq*(pq*pq/4.5 + rq*4)/3 + rq*pq*4 - qq*qq;  // richtig
  qk= -pq*(pq*pq/4.5 + rq*4)/3 + rq*rq*4 - qq*qq;  // falsch

utf-8 Codierung

  ±        Plusminus   Alt 241 Windows   Alt-177 Linux (dezimaler UTF-8 Code)
  x²       hoch 2                        Alt-178
  x³       hoch 3
  x⁴       hoch 4
  x⁻¹      hoch -1

  φ        phi
  ξ        sigma

  √        Wurzel
  ∛        3. Wurzel
  ¼        1/4
  ½        1/2
  ¾        3/4

  ℝ        R reelle Zahlen        8477
  ℂ        C komplexe Zahlen
  ℍ        H Quaternionen
  ℕ        N natürliche Zahlen
  ℤ        Z ganze Zahlen

  x ∈ ℝ    x Element R     Alt-8712 

  ⊆        Teilmenge


  ÄÖÜ äöü ß  Umlaute

*/
