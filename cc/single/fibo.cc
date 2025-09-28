// Dieses Programm berechnet die Lucaszahlen

#include <cmath>
#include <cstdio>

void fibo_f ()
  {
  float gs= 0.5 + sqrtf (1.25);
  for (float glauf= -10; glauf <= 30; glauf++)
    {
    float l1= powf (gs, glauf);
    float l2= powf (-gs, -glauf);
    float lucas= l1 + l2;
    printf ("%5.0f  %50.30f %50.30f %50.30f\n", glauf, lucas, l1, l2);
    }
  }

void fibo_d ()
  {
  double gs= 0.5 + sqrt (1.25);
  for (double glauf= -10; glauf <= 30; glauf++)
    {
    double l1= pow (gs, glauf);
    double l2= pow (-gs, -glauf);
    double lucas= l1 + l2;
    printf ("%5.0lf  %50.30lf %50.30lf %50.30lf\n", glauf, lucas, l1, l2);
    }
  }

void fibo_ld ()
  {
  long double gs= 0.5 + sqrtl (1.25);
  for (long double glauf= -10; glauf <= 30; glauf++)
    {
    long double l1= powl (gs, glauf);
    long double l2= powl (-gs, -glauf);
    long double lucas= l1 + l2;
    printf ("%5.0Lf  %50.30Lf %50.30Lf %50.30Lf\n", glauf, lucas, l1, l2);
    }
  }

void fibo16 ()
  {
//  _Float16 gs= _Float16 (0.5) + _Float16 (sqrtf (1.25));
  for (_Float16 glauf= -10; glauf <= 30; glauf++)
    {
//    _Float16 l1= _Float16 (powf (gs, glauf));
//    _Float16 l2= _Float16 (powf (-gs, -glauf));
//    _Float16 lucas= l1 + l2;
//    printf ("%5.0f  %50.30f %50.30f %50.30f\n", glauf, lucas, l1, l2);
    }
  }

void fibo128 ()
  {
  char zahl0[128];
  char zahl1[128];
  char zahl2[128];
  char zahl3[128];
  _Float128 gs= 0.5 + sqrtl (1.25);

  for (_Float128 glauf= -10; glauf <= 30; glauf++)
    {
    _Float128 l1= powl (gs, glauf);
    _Float128 l2= powl (-gs, -glauf);
    _Float128 lucas= l1 + l2;


    snprintf (zahl0, sizeof zahl0, "%5.0Lf", glauf);
    snprintf (zahl1, sizeof zahl1, "%50.30Lf", lucas);
    snprintf (zahl2, sizeof zahl2, "%50.30Lf", l1);
    snprintf (zahl3, sizeof zahl3, "%50.30Lf", l2);

    printf ("%s  %s %s %s\n", zahl0, zahl1, zahl2, zahl3);
    }
  }

int main ()
  {
//  fibo_ld ();
//  printf ("\n");
  fibo128 ();
  return 0;
  }
