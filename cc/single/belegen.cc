#include <cstdlib>  // malloc
#include <cstdio>   // printf

int main ()
  {
  signed long long anz= 1;
  anz <<= 30;
  printf ("%lld Bytes belegt\n", anz);
  signed char* bla;
  bla= (signed char*) (malloc (anz));
  for (signed long lauf= 0; lauf < anz; lauf++)
    bla[lauf]= 0;
  printf ("Speicher gefüllt\n");
  while (1);
  free (bla);
  }
