#include "single.h"
#include <sys/stat.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>

void frescue (char* pdin)
  {
  struct stat filestat;
  stat (pdin, &filestat);
  signed long laengedin= filestat.st_size;
  printf ("\nDateilänge: %ld\n\n", laengedin);
  FILE* din= fopen (pdin, "rb");
  FILE* dout= fopen ("rescue.fil", "wb");
  signed long maxblock=1 << 10;
  signed char* blocki= new signed char[maxblock];
  signed long maxfehler= laengedin/maxblock + 1;
  signed long* fehlerliste= new signed long[maxfehler];
  signed long fehleranz= 0;
  signed long gelesen= 0;
  while (gelesen*maxblock < laengedin)
    {
    signed long blkgr= laengedin - gelesen*maxblock;
    if (blkgr > maxblock)
      blkgr= maxblock;
    printf ("Block %5ld: %10ld  ", gelesen, blkgr);
    fflush (stdout);
    fseek (din, gelesen*maxblock, SEEK_SET);
    signed long readanz= fread (blocki, 1, blkgr, din);
    printf ("%10ld", readanz);
    if (readanz != blkgr)
      {
      printf ("  Lesefehler");
      fehlerliste[fehleranz]= gelesen*maxblock;
      fehleranz++;
      }
    printf ("\n");
    fseek (dout, gelesen*maxblock, SEEK_SET);
    fwrite (blocki, 1, blkgr, dout);
    gelesen++;
    }
  fclose (din);
  fclose (dout);
  delete [] blocki;
  for (signed long flauf= 0; flauf < fehleranz; flauf++)
    {
    printf (" %10ld\n", fehlerliste[flauf]);
    }
  printf ("\n %ld Lesefehler\n", fehleranz);
  }

int main (int argc, char** argv)
  {
  if (argc == 2)
    {
    frescue (argv[1]);
    return 0;
    }
  printf ("    frescue filename  #to make a rescuecopy from the file\n\n");
  return 0;
  }
