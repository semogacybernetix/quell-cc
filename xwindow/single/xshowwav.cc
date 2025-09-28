#include "../screen/xscr.h"
#include "../keyboard/xkbd.h"

#include <cstdio>
#include <cstdlib>

bool readsample (FILE* din, signed short& pleft, signed short& pright)
  {
  signed long fret= 0;
  fret++;                 // Variable benutzen, damit Compiler nicht meckert
  unsigned char llow, lhigh, rlow, rhigh;
  if (!fread (&llow, 1, 1, din))
    return false;
  fret= fread (&lhigh, 1, 1, din);
  fret= fread (&rlow, 1, 1, din);
  fret= fread (&rhigh, 1, 1, din);
  pleft= (lhigh << 8) | llow;
  pright= (rhigh << 8) | rlow;
  return true;
  }

void writesample (FILE* din, signed short pleft, signed short pright)
  {
  unsigned char llow, lhigh, rlow, rhigh;
  llow= pleft;
  lhigh= pleft >> 8;
  rlow= pright;
  rhigh= pright >> 8;
  fwrite (&llow, 1, 1, din);
  fwrite (&lhigh, 1, 1, din);
  fwrite (&rlow, 1, 1, din);
  fwrite (&rhigh, 1, 1, din);
  }

void maxpegel (char* pname)
  {
  signed short lmom;
  signed short rmom;
  signed short lmax= 0;
  signed short rmax= 0;
  FILE* din= fopen (pname, "rb");
  fseek (din, 0x2c, 0);
  while (readsample (din, lmom, rmom))
    {
    if (abs (lmom) > lmax)
      lmax= abs (lmom);
    if (abs (rmom) > rmax)
      rmax= abs (rmom);
    }
  printf ("max l: %5d max r: %5d\n", lmax, rmax);
  }

void diffwav (char* pname1, char* pname2)
  {
  signed long fret= 0;
  fret++;                 // Variable benutzen, damit Compiler nicht meckert
  signed short lmom1= 0;
  signed short rmom1= 0;
  signed short lmom2;
  signed short rmom2;
  FILE* din= fopen (pname1, "rb");
  FILE* dout= fopen (pname2, "wb");
  unsigned char* header[0x2c];
  fret= fread (header, 0x2c, 1, din);
  fwrite (header, 0x2c, 1, dout);
  while (readsample (din, lmom2, rmom2))
    {
    writesample (dout, lmom2 - lmom1, rmom2 - rmom1);
    lmom1= lmom2;
    rmom1= rmom2;
    }
  }

void intwav (char* pname1, char* pname2)
  {
  signed long fret= 0;
  fret++;                 // Variable benutzen, damit Compiler nicht meckert
  signed short lmom1= 0;
  signed short rmom1= 0;
  signed short lmom2;
  signed short rmom2;
  FILE* din= fopen (pname1, "rb");
  FILE* dout= fopen (pname2, "wb");
  unsigned char* header[0x2c];
  fret= fread (header, 0x2c, 1, din);
  fwrite (header, 0x2c, 1, dout);
  while (readsample (din, lmom2, rmom2))
    {
    lmom1+= lmom2;
    rmom1+= rmom2;
    writesample (dout, lmom1, rmom1);
    }
  }

void showwav (char* pname)
  {
  signed short blockl[1024];
  signed short blockr[1024];
  cxscreen xscreen ("Welle", 1024, 768);
  cxkeyboard keyboard;
  FILE* din= fopen (pname, "rb");
  fseek (din, 0x2c, 0);
//  for (unsigned long lsamp= 0; lsamp < 1024; lsamp++)
//    xscreen.putpixel (lsamp, 384, xscreen.rmax, xscreen.gmax, xscreen.bmax);
  keyboard.putkey (0, 0, 0);
  while (!keyboard.getkey (0, 0))
  {
  for (unsigned long lsamp= 0; lsamp < 1024; lsamp++)
    {
    readsample (din, blockl[lsamp], blockr[lsamp]);
    xscreen.putpixel (lsamp, 384 + blockl[lsamp]/85, xscreen.rmax, xscreen.gmax, 0);
    xscreen.putpixel (lsamp, 384 + blockr[lsamp]/85, 0, xscreen.gmax, xscreen.bmax);
    }
  xscreen.flush ();
    do
    {
    keyboard.flush ();
    if (keyboard.getkey (0, 0))
      break;
    }
  while (!keyboard.getkey (19, 5));
  for (unsigned long lsamp= 0; lsamp < 1024; lsamp++)
    {
    xscreen.putpixel (lsamp, 384 + blockl[lsamp]/85, 0, 0, 0);
    xscreen.putpixel (lsamp, 384 + blockr[lsamp]/85, 0, 0, 0);
    }
  }
  fclose (din);
  }

signed int main (int argc, char** argv)
  {
  if (argc != 2)
    return 0;
//  diffwav (argv[1], argv[2]);
//  intwav (argv[1], argv[2]);
//  return 0;
  maxpegel (argv[1]);
  showwav (argv[1]);
  return 0;
  }
