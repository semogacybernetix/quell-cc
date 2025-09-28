// ein Test zum Schreiben von Dateien

#include <cstdio>
#include <cmath>

int main ()
  {
  FILE* bla= fopen ("hallo.txt", "wb");
  fprintf (bla, "huhu\n");
  fprintf (bla, "huhu2\n");
  fclose (bla);
  return 0;
  }
