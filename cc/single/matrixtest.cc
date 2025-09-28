// Dieses Programm testet Matrizenfunktionen

#include "../class/vektor.h"

#include <cstdio>

void printvektor2 (cvektor2 pv)
  {
  printf ("\n");
  printf ("%18.6Lf\n", pv.x);
  printf ("%18.6Lf\n", pv.y);
  printf ("\n");
  }

void printbasis2 (cbasis2 pb)
  {
  printf ("\n");
  printf ("%18.6Lf %18.6Lf\n", pb.x.x, pb.y.x);
  printf ("%18.6Lf %18.6Lf\n", pb.x.y, pb.y.y);
  printf ("\n");
  }

void printbasis3 (cbasis3 pb)
  {
  printf ("\n");
  printf ("%18.6Lf %18.6Lf %18.6Lf\n", pb.x.x, pb.y.x, pb.z.x);
  printf ("%18.6Lf %18.6Lf %18.6Lf\n", pb.x.y, pb.y.y, pb.z.y);
  printf ("%18.6Lf %18.6Lf %18.6Lf\n", pb.x.z, pb.y.z, pb.z.z);
  printf ("\n");
  }

void matrixtest ()
  {
  cvektor3 vec31 (5, 3, 7);
  cvektor3 vec32 (4, -3, 5);
  cvektor3 vec33 (6, 9, -2);
  cbasis3 bas31 (vec31, vec32, vec33);
  cvektor3 vec41 (-9, 8, 5);
  cvektor3 vec42 (3, 2, 9);
  cvektor3 vec43 (1, 2, -6);
  cbasis3 bas32 (vec41, vec42, vec43);
  cvektor3 vec51 (1, 0, 0);
  cvektor3 vec52 (0, 1, 0);
  cvektor3 vec53 (0, 0, 1);
  cbasis3 eins (vec51, vec52, vec53);
  cbasis3 liinv= eins/bas31;
  cbasis3 reinv= eins|bas31;
  cbasis3 bas33=bas32*bas31;
  cbasis3 bas1z= bas33/bas32;
  cbasis3 bas2z= bas33|bas31;
  
  printf ("B1:\n");
  printbasis3 (bas31);
  printf ("B2:\n");
  printbasis3 (bas32);
  printf ("links Inverses von B1:\n");
  printbasis3 (liinv);
  printf ("rechts Inverses von B1:\n");
  printbasis3 (reinv);
  printf ("B1*B2\n");
  printbasis3 (bas33);
  printf ("B1:\n");
  printbasis3 (bas1z);
  printf ("B2:\n");
  printbasis3 (bas2z);
  }
  
int main ()
  {
  matrixtest ();
  return 0;
  }
