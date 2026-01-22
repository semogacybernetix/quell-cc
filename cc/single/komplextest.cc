// Dieses Programm testet die komplexe Rechnung von cvektor2

#include "../class/vektor.h"

#include <cstdio>

using namespace std;

void dateneingabe (real& p1r, real& p1i, real& p2r, real& p2i)
  {
  integer ret;
  printf ("\n");
  printf ("Z1 real:         ");
  ret= scanf ("%Lf", &p1r);
  printf ("Z1 imaginär      ");
  ret= scanf ("%Lf", &p1i);
  printf ("\n");
  printf ("Z2 real:         ");
  ret= scanf ("%Lf", &p2r);
  printf ("Z2 imaginär      ");
  ret= scanf ("%Lf", &p2i);
  printf ("\n");
  ret*= 1;          //ret benutzen, damit Compiler nicht meckert unbenutzte Variable
  }

void testekomplex ()
  {
  ckomplexk v1, v2, v31, v41, v42, v43, v44, v51, v52, v6, v7, v8, v9, luc, v10, v11, v12, v13;

  dateneingabe (v1.x, v1.y, v2.x, v2.y);

  v11= v1^integer (v2.x);
  v12= v1^v2.x;
  v13= v1^v2;
  v31= powr (v1, v2);

  v11= 7/v1;
  v12= v11*v1;
  v13= v11/v1;

  v41= v13^(1/v2);
  v42= v31^(1/v2);
  v43= powr (v13, 1/v2);
  v44= powr (v31, 1/v2);

  v51= logr (v13)/logr (v1);
  v52= logr (v31)/logr (v1);

  v6= expr  (v1);
  v7= logr  (v6);
  v8= logr  (v1);
  v9= expr  (v8);
  luc= ckomplexk (0.5 + sqrtl (1.25), 0);
  v10= powr (luc, v1) + powr (-luc, -v1);

/*
  printf ("p1                        %40.20Lf %40.20Lf\n", v1.x, v1.y);
  printf ("p2                        %40.20Lf %40.20Lf\n", v2.x, v2.y);
  printf ("\n");
  printf ("p1^integer (p2.x)         %40.20Lf %40.20Lf\n", v11.x, v11.y);
  printf ("p1^p2.x                   %40.20Lf %40.20Lf\n", v12.x, v12.y);
  printf ("p1^p2                     %40.20Lf %40.20Lf\n", v13.x, v13.y);
  printf ("powr (p1, p2)           %40.20Lf %40.20Lf\n", v31.x, v31.y);
  printf ("\n");
  printf ("p2√p3               = p1  %40.20Lf %40.20Lf\n", v41.x, v41.y);
  printf ("p2√p3               = p1  %40.20Lf %40.20Lf\n", v42.x, v41.y);
  printf ("p2√p3               = p1  %40.20Lf %40.20Lf\n", v43.x, v41.y);
  printf ("p2√p3               = p1  %40.20Lf %40.20Lf\n", v44.x, v41.y);
  printf ("\n");
  printf ("logv pv1 (p3)       = p2  %40.20Lf %40.20Lf\n", v51.x, v51.y);
  printf ("logv pv1 (p3)       = p2  %40.20Lf %40.20Lf\n", v52.x, v52.y);
  printf ("\n");
  printf ("exp (p1)                  %40.20Lf %40.20Lf\n", v6.x, v6.y);
  printf ("logzurück                 %40.20Lf %40.20Lf\n", v7.x, v7.y);
  printf ("\n");
  printf ("log (p1)                  %40.20Lf %40.20Lf\n", v8.x, v8.y);
  printf ("expzurück                 %40.20Lf %40.20Lf\n", v9.x, v9.y);
  printf ("\n");
  printf ("lucas (p1)                %40.20Lf %40.20Lf\n", v10.x, v10.y);
  printf ("\n");
*/
  }
  
int main ()
  {
  testekomplex ();
  return 0;
  }

/*
-----------------------------------------------------------------------------------------------
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
-----------------------------------------------------------------------------------------------
*/
