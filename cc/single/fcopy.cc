#include <cstdio>
#include <sys/stat.h>
#include <sys/times.h>
#include <unistd.h>

void copy (char* pquelle, unsigned long ppos, char* pziel, unsigned long plaenge)
  {
  tms zeit;
  float ticksps= float (sysconf (_SC_CLK_TCK));
  FILE* din= fopen (pquelle, "rb");
  fseek (din, ppos, SEEK_SET);
  FILE* dout;
  dout= fopen (pziel, "ab");
  unsigned long blkgr= plaenge;
  if (blkgr > 16777216)
    blkgr= 16777216;
  unsigned char* puffer;
  puffer= new unsigned char[blkgr];
  unsigned long bwritten= 0;
  unsigned long wlaenge;
  unsigned long timestart= times (&zeit);
  while (bwritten < plaenge)
    {
    unsigned long timepos= times (&zeit);
    wlaenge= plaenge - bwritten;
    if (wlaenge > blkgr)
      wlaenge= blkgr;
    printf ("reading ");
    fflush (stdout);
    fread (puffer, wlaenge, 1, din);
    unsigned long timepos2= times (&zeit);
    printf ("%5.1f MB/s  ", wlaenge/1048576.*ticksps/(timepos2 - timepos));
    printf ("writing ");
    fflush (stdout);
    fwrite (puffer, wlaenge, 1, dout);
    bwritten+= wlaenge;
    unsigned long timepos3= times (&zeit);
    printf ("%5.1f MB/s ", wlaenge/1048576.*ticksps/(timepos3 - timepos2));
    printf ("%5.1f/", wlaenge/1048576.*ticksps/(timepos3 - timepos));
    printf ("%5.1f MB/s ", bwritten/1048576.*ticksps/(timepos3 - timestart));
    printf ("%4lu MB ", (bwritten + 524288) >> 20);
    printf ("%7.1fs\n", (timepos3 - timestart)/ticksps);
    }
  fclose (din);
  fclose (dout);
  delete (puffer);
  }

int main (int argc, char** argv)
  {
  if ((argc < 3) || (argc > 5))
    {
    printf ("         fcopy  Quelldatei Zieldatei\n");
    printf ("         fcopy  Quelldatei Position Zieldatei\n");
    printf ("         fcopy  Quelldatei Position Zieldatei Laenge\n\n");
    return 0;
    }
  unsigned long position= 0, laenge;
  char* ziel;
  if (argc  == 3)
    ziel= argv[2];
    else
    ziel= argv[3];
  if (argc > 3)
    sscanf (argv[2], "%lu", &position);
  if (argc == 5)
    sscanf (argv[4], "%lu", &laenge);
    else
    {
    struct stat filestat;
    stat (argv[1], &filestat);
    laenge= filestat.st_size - position;
    }
  copy (argv[1], position, ziel, laenge);
  return 0;
  }
