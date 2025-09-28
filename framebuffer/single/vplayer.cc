#include "../screen/fbscr.h"

#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include <sys/times.h>
#include <stdio.h>

void playfile (char* pname)
  {
  signed long fret= 0;
  fret+= 0;                      // benutzen wegen Compilermeckern
  FILE* datei= fopen (pname, "rb");
  unsigned char head[20];
  fret= fread (head, 20, 1, datei);
  if ((head[0] != 0x9c) | (head[1] != 0x2e) | (head[2] != 0x0f) | 
      (head[3] != 0x64))
    {
    printf ("kein rvd (raw video) Format\n");
    return;
    }
  unsigned long xanz= head[4] | head[5] << 8;
  unsigned long yanz= head[8] | head[9] << 8;
  unsigned long zanz= head[12] | head[13] << 8 | head[14] << 16 | head[15] << 24;
  unsigned long tsize= head[16] | head[17] << 8 | head[18] << 16 | head[19] << 24;
  unsigned long stime= (tsize + 5) / 10;
  unsigned long bildgr= xanz*yanz*4;
  unsigned long zeilegr= xanz*4;
  unsigned char* puffer= new unsigned char[bildgr];
  cfbscreen fbscreen ("", 0, 0);
  tms zeit;
  signed long timestart= times (&zeit) + 2;
  for (unsigned long lbild= 0; lbild < zanz; lbild++)
    {
    if (timestart <= times (&zeit))
      {
      printf ("%10ld\n", times (&zeit) - timestart);
      timestart = times (&zeit);
      }
    while (timestart > times (&zeit));
    timestart+= stime;
    fret= fread (puffer, bildgr, 1, datei);
    for (unsigned long lzeile= 0; lzeile < yanz; lzeile++)
      memcpy (fbscreen.fbuffer8 + lzeile*fbscreen.xanz*4, puffer + lzeile*zeilegr, zeilegr);
    }
  fclose (datei);
  delete (puffer);
  }

int main (int argc, char** argv)
  {
  if (argc != 2)
    return 0;
  playfile (argv[1]);
  return 0;
  }
