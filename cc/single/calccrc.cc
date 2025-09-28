// dieses Programm berechnet die CRC-32 Checksumme mit dem Ethernet-Genereatorpolynom $04C11DB7 einer Datei

#include "single.h"

#include <cstdio>
#include <sys/stat.h>
#include <sys/times.h>
#include <unistd.h>

unsigned long calcdatei (char* pname)
  {
  signed long fret= 0;
  fret+= 0;
  tms zeit;
  float ticksps= float (sysconf (_SC_CLK_TCK));
  FILE* din= fopen (pname, "rb");
  struct stat filestat;
  stat (pname, &filestat);
  unsigned long dlaenge= filestat.st_size;
  unsigned long blkgr= dlaenge;
  if (blkgr > 16777216)
    blkgr= 16777216;
  unsigned char* puffer;
  puffer= new unsigned char[blkgr];
  unsigned long checksum= 0;
  unsigned long bwritten= 0;
  unsigned long wlaenge;
  unsigned long timestart= times (&zeit);
  while (bwritten < dlaenge)
    {
    unsigned long timepos= times (&zeit);
    wlaenge= dlaenge - bwritten;
    if (wlaenge > blkgr)
      wlaenge= blkgr;
    printf ("reading ");
    fflush (stdout);
    fret= fread (puffer, wlaenge, 1, din);
    unsigned long timepos2= times (&zeit);
    printf ("%5.1f MB/s  ", wlaenge/1048576.*ticksps/(timepos2 - timepos));
    printf ("calcing ");
    fflush (stdout);
    calccrc (checksum, puffer, wlaenge);
    bwritten+= wlaenge;
    unsigned long timepos3= times (&zeit);
    printf ("%5.1f MB/s ", wlaenge/1048576.*ticksps/(timepos3 - timepos2));
    printf ("%5.1f/", wlaenge/1048576.*ticksps/(timepos3 - timepos));
    printf ("%5.1f MB/s ", bwritten/1048576.*ticksps/(timepos3 - timestart));
    printf ("%4lu MB ", (bwritten + 524288) >> 20);
    printf ("%7.1fs\n", (timepos3 - timestart)/ticksps);
    }
  fclose (din);
  delete (puffer);
  return checksum;
  }

int main (int argc, char** argv)
  {
  if (argc != 2)
    return 0;
  printf ("Checksumme: %08lX\n", calcdatei (argv[1]));
  return 0;
  }
