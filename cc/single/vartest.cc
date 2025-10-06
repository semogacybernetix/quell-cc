#include <cstdio>

using namespace std;

void gibwert (signed long p)
  {
  printf ("%ld\n", p);
  printf ("\n");
  }

void gibvariable (signed long& p)
  {
  printf ("%ld\n", p);
  printf ("\n");
  }

void gibzeiger (signed long *p)
  {
  printf ("%ld\n", *p);
  printf ("%ld\n", p[0]);
  printf ("\n");
  }

int main ()
  {
  signed long var= 14;
  signed long arr[1]= {35};
  signed long* zei= new signed long (1);
  zei[0]= 67;
  *zei= 78;

  gibwert (5);
  gibwert (var);
  gibwert (arr[0]);
  gibwert (*arr);
  gibwert (zei[0]);
  gibwert (*zei);

  gibvariable (var);
  gibvariable (arr[0]);
  gibvariable (*arr);
  gibvariable (zei[0]);
  gibvariable (*zei);

  gibzeiger (&var);
  gibzeiger (arr);
  gibzeiger (&arr[0]);
  gibzeiger (zei);
  gibzeiger (&zei[0]);

// gibvariable ist schlecht, weil die Übergabe genauso aussieht als wenn der Wert anstatt der Variable übergeben wird. Also lässt sich beim Aufruf einer Funktion nicht
// unterscheiden, ob der Wert der Variablen oder die Variable selber übergeben wird.
// in der Funktion selber kann nicht unterschieden werden ob eine fremde Variable oder eine funktionseigene Variable benutzt wird.
// deshalb gibzeiger benutzen. Variablenübergabe erkennbar an &var, in der Funktion sind fremde Variablen durch einen Stern erkennbar gekennzeichnet.
// Referenzübergabe & nie benutzen

//  signal (SIGTERM, sterm);
//  signal (SIGINT,sint);
  return 0;
  }
