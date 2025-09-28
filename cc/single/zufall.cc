#include "signal.h"
#include <cstdio>
#include <cstdlib>        // exit

unsigned long long z= 0;
unsigned char zufaelle[1048576];
unsigned long long zpos= 0;

void sint (int x)
  {
  zufaelle[zpos]= (unsigned char) (z);
  zpos++;
  printf("%16llX   %X\n", z, zufaelle[zpos - 1]);
  x++;                          // x benutzen, damit der Compiler nicht meckert
  }

void term (int x)
  {
  FILE* dbin= fopen ("zuf", "ab");
  fwrite (zufaelle, zpos, 1, dbin);
  fclose (dbin);
  printf ("\nDatei geschrieben\n");
  exit (0);
  x++;                          // x benutzen, damit der Compiler nicht meckert
  }

int main ()
  {
  signal (SIGINT, sint);
  signal (SIGTERM, term);
  while (1)
    z++;
  return 0;
  }
