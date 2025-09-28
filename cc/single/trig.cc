#include <cmath>
#include <cstdio>

void inab ()
  {
  signed long retf= 0;
  retf+= 0;
  long double dx, dy, dz;
  printf ("\n");
  printf ("x: ");
  retf= scanf ("%Lf", &dx);
  printf ("y: ");
  retf= scanf ("%Lf", &dy);
  printf ("z: ");
  retf= scanf ("%Lf", &dz);

  long double dbetrag= sqrtl (dx*dx + dy*dy + dz*dz);
  dx= dx/dbetrag;
  dy= dy/dbetrag;
  dz= dz/dbetrag;

  long double dalpha= acosl (dx);
  long double dbeta= acosl (dy);
  long double dc= acosl (dx*dy / sqrtl ((dx*dx + dz*dz) * (dy*dy + dz*dz)));
  long double da= asinl (sinl (dalpha) * sinl (dc));
  long double db= asinl (sinl (dbeta) * sinl (dc));

  long double t1= cosl (da) * cosl (db) - cosl (dc);
  long double t2= sinl (dalpha) * sinl (dc) - sinl (da);
  long double t3= cosl (da) * sinl (dbeta) - cosl (dalpha);
  long double t4= sinl (dalpha) * sinl (dbeta) * cosl (dc) - cosl (dalpha) * cosl (dbeta);
  long double t5= sinl (da) * cosl (db) * sinl (dbeta) - sinl (db) * cosl (dbeta);
  long double t6= cosl (dalpha) * cosl (db) * sinl (dc) - sinl (db) * cosl (dc);

  printf ("\n");
  printf ("Seite dx %24.20Lf\n", dx);
  printf ("Seite dy %24.20Lf\n", dy);
  printf ("Seite dz %24.20Lf\n", dz);
  printf ("Winkel da %24.20Lf\n", da/M_PIl*180);
  printf ("Winkel db %24.20Lf\n", db/M_PIl*180);
  printf ("Winkel dc %24.20Lf\n", dc/M_PIl*180);
  printf ("dalpha %24.20Lf\n", dalpha/M_PIl*180);
  printf ("dbeta: %24.20Lf\n", dbeta/M_PIl*180);
  printf ("\n");
  printf ("%24.20Lf\n", t1);
  printf ("%24.20Lf\n", t2);
  printf ("%24.20Lf\n", t3);
  printf ("%24.20Lf\n", t4);
  printf ("%24.20Lf\n", t5);
  printf ("%24.20Lf\n", t6);
  printf ("\n");
  }

int main ()
  {
  inab ();
  return 0;
  }
