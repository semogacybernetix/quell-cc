#include "single.h"
#include <sys/stat.h>
#include <cstdio>
#include <cmath>
#include <cstring>

float cdata[147][3];

void initcdata2 ()
  {
  for (unsigned long lsamp= 0; lsamp < 147; lsamp++)
    {
    cdata[lsamp][0]= 1;
    cdata[lsamp][1]= 0;
    cdata[lsamp][2]= 0;
    }
  }

void initcdata ()
  {
  for (unsigned long lsamp= 0; lsamp < 147; lsamp++)
    {
    float fl= 1 + lsamp*160/147 - lsamp*160/147.;
    float fr= (lsamp + 1)*160/147. - (lsamp + 1)*160/147;
    cdata[lsamp][0]= fl;
    if ((lsamp + 1)*160/147 - lsamp*160/147 == 2)
      {
      cdata[lsamp][1]= 1;
      cdata[lsamp][2]= fr;
      }
      else
      {
      cdata[lsamp][1]= fr;
      cdata[lsamp][2]= 0;
      }
//    printf ("%4lu    %10f %10f %10f\n",lsamp, cdata[lsamp][0], cdata[lsamp][1], cdata[lsamp][2]);
    }
  }

void convblock (signed short* pblocki, signed short* pblocko, unsigned long panz)
  {
  for (unsigned long lsamp= 0; lsamp < 147; lsamp++)
    {
    unsigned long sampi= lsamp*160/147;
    pblocko[lsamp*2]=     int (rint (cdata[lsamp][0]*pblocki[sampi*2] +
                                     cdata[lsamp][1]*pblocki[sampi*2 + 2] +
                                     cdata[lsamp][2]*pblocki[sampi*2 + 4]));
    pblocko[lsamp*2 + 1]= int (rint (cdata[lsamp][0]*pblocki[sampi*2 + 1] +
                                     cdata[lsamp][1]*pblocki[sampi*2 + 3] +
                                     cdata[lsamp][2]*pblocki[sampi*2 + 5]));
    }
  }

void convert (char* pdin, char* pdout)
  {
  struct stat filestat;
  stat (pdin, &filestat);
  unsigned long laengedin= filestat.st_size;
  laengedin-= 46;
  FILE* din= fopen (pdin, "rb");
  fseek (din, 46, SEEK_SET);
  FILE* dout= fopen (pdout, "wb");
  unsigned char header[44];
  wavheader44 (header, (unsigned long long) laengedin*147/160);
  fwrite (header, 44, 1, dout);
  unsigned long gelesen= 0;
  while (gelesen < laengedin)
    {
    unsigned long blkgr= laengedin - gelesen;
    if (blkgr > 640)
      blkgr= 640;
    signed short blocki[324];
    fread (blocki, blkgr, 1, din);
    signed short blocko[294];
    convblock (blocki, blocko, blkgr*147/640);
    fwrite (blocko, blkgr*147/160, 1, dout);
    gelesen+= blkgr;
    }
  fclose (din);
  fclose (dout);
  }

int main (int argc, char** argv)
  {
  if (!littleendian ())
    {
    printf ("    CPU hat kein littleendian\n");
    return 0;
    }
  if (argc != 3)
    return 0;
  initcdata ();
  convert (argv[1], argv[2]);
  return 0;
  }
