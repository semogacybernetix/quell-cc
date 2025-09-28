#include "../screen/allscr.h"
#include "single.h"
#include "../class/vektor.h"

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>

void separatespot (char* iname, double iwinkel, double ibereich)
  {
  cbmpdatei eingabebild (iname);
  printf ("xanz: %d\n", eingabebild.xanz);
  printf ("yanz: %d\n", eingabebild.yanz);
  char psname1[1000];
  char psname2[1000];
  sprintf (psname1, iname);
  sprintf (psname2, iname);
  strcat (psname1, ".spot-1.ps");
  strcat (psname2, ".spot-2.ps");
  cpsdatei psbild1 (psname1, eingabebild.xanz, eingabebild.yanz);
  cpsdatei psbild2 (psname2, eingabebild.xanz, eingabebild.yanz);
  psbild1.hintergrund (255);
  psbild2.hintergrund (255);
  for (unsigned short laufy= 0; laufy < eingabebild.yanz; laufy++)
    for (unsigned short laufx= 0; laufx < eingabebild.xanz; laufx++)
      {
      double rot, grn, blu;
      double hue, sat, hel;
	  unsigned short prot, pgrn, pblu;
	  eingabebild.getpixel (laufx, laufy, prot, pgrn, pblu);
	  rot= double (prot)/255;
	  grn= double (pgrn)/255;
	  blu= double (pblu)/255;
      rgbtohsy (rot, grn, blu, hue, sat, hel);
	  if ((hue - iwinkel > -ibereich) && (hue - iwinkel < ibereich))
        psbild1.putpixel (laufx, laufy, prot, pgrn, pblu);
		else
        psbild2.putpixel (laufx, laufy, prot, pgrn, pblu);
	  }
  }

void separatergb (char* iname, double isat)
  {
  cbmpdatei eingabebild (iname);
  printf ("xanz: %d\n", eingabebild.xanz);
  printf ("yanz: %d\n", eingabebild.yanz);
  char psname1[1000];
  char psname2[1000];
  sprintf (psname1, iname);
  sprintf (psname2, iname);
  strcat (psname1, ".rgb-1.ps");
  strcat (psname2, ".rgb-2.ps");
  cpsdatei psbild1 (psname1, eingabebild.xanz, eingabebild.yanz);
  cpsdatei psbild2 (psname2, eingabebild.xanz, eingabebild.yanz);
  psbild1.hintergrund (255);
  psbild2.hintergrund (255);
  for (unsigned short laufy= 0; laufy < eingabebild.yanz; laufy++)
    for (unsigned short laufx= 0; laufx < eingabebild.xanz; laufx++)
      {
      double rot, grn, blu;
      double hue, sat, hel;
	  unsigned short prot, pgrn, pblu;
	  eingabebild.getpixel (laufx, laufy, prot, pgrn, pblu);
	  rot= double (prot)/255;
	  grn= double (pgrn)/255;
	  blu= double (pblu)/255;
      rgbtohsy (rot, grn, blu, hue, sat, hel);
	  if (sat < isat)
        psbild1.putpixel (laufx, laufy, prot, pgrn, pblu);
		else
        psbild2.putpixel (laufx, laufy, prot, pgrn, pblu);
	  }
  }

int main (int argc, char** argv)
  {
  if (argc > 3)
    {
    double par1 (0), par2 (0);
	sscanf (argv[3], "%lf", &par1);
	if (argc > 4)
	  sscanf (argv[4], "%lf", &par2);
	switch (argv[2][0])
      {
      case 0x30:
        separatespot (argv[1], par1, par2);
        break;
      case 0x31:
        separatergb (argv[1], par1);
        break;
      }
    return 0;
    }
  return 0;
  }
