#include "../screen/allscr.h"
#include "single.h"
#include "../class/vektor.h"

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
/*
void erzeugejpgbild (char* iname)
  {
  cjpegdatei eingabebild (iname);
  printf ("xanz: %d\n", eingabebild.xanz);
  printf ("yanz: %d\n", eingabebild.yanz);
  char psname[1000];
  sprintf (psname, iname);
  strcat (psname, ".ps");
  cpsdatei psbild (psname, eingabebild.xanz, eingabebild.yanz);
  for (integer laufy= 0; laufy < eingabebild.yanz; laufy++)
    for (integer laufx= 0; laufx < eingabebild.xanz; laufx++)
      {
      integer rot, grn, blu;
	  eingabebild.getpixel (laufx, laufy, rot, grn, blu);
	  psbild.putpixel (laufx, laufy, rot, grn, blu);
	  }
  }

void erzeugemonobild (char* iname)
  {
  cjpegdatei eingabebild (iname);
  printf ("xanz: %d\n", eingabebild.xanz);
  printf ("yanz: %d\n", eingabebild.yanz);
  char psname[1000];
  sprintf (psname, iname);
  strcat (psname, "-m.ps");
  cpsdatei psbild (psname, eingabebild.xanz, eingabebild.yanz);
  for (integer laufy= 0; laufy < eingabebild.yanz; laufy++)
    for (integer laufx= 0; laufx < eingabebild.xanz; laufx++)
      {
      integer prot, pgrn, pblu, phel;
	  real rot, grn, blu, hel;
	  eingabebild.getpixel (laufx, laufy, prot, pgrn, pblu);
	  rot= real (prot)/255;
	  grn= real (pgrn)/255;
	  blu= real (pblu)/255;
	  hel= rgbtoy (rot, grn, blu);
	  phel= lrint (hel*255);
	  psbild.putpixel (laufx, laufy, phel, phel, phel);
	  }
  }

void erzeugedichromatbild (char* iname, char* pcol)
  {
  cjpegdatei eingabebild (iname);
  printf ("xanz: %d\n", eingabebild.xanz);
  printf ("yanz: %d\n", eingabebild.yanz);
  char psname0[1000];
  sprintf (psname0, iname);
  strcat (psname0, "-hsy-dc.bmp");
  cbmpdatei psbild0 (psname0, eingabebild.xanz, eingabebild.yanz);
  for (integer laufy= 0; laufy < eingabebild.yanz; laufy++)
    for (integer laufx= 0; laufx < eingabebild.xanz; laufx++)
      {
      integer prot, pgrn, pblu;
	  real rot, grn, blu, hel, sat, col;
	  eingabebild.getpixel (laufx, laufy, prot, pgrn, pblu);
	  rot= real (prot)/255;
	  grn= real (pgrn)/255;
	  blu= real (pblu)/255;
	  rgbtoabc (rot, grn, blu, hel, sat, col);
//	  rgbtohsy (rot, grn, blu, col, sat, hel);
	  hel*= 0.7;
//	  sat*= 0.6442676; //0.6442676;
      real dcol;
	  sscanf (pcol, "%lf", &dcol);
	  dcol= dcol/180*M_PI;
	  sat= sat*cos (col - dcol);
	  col= dcol;
	  if (sat < 0)
	    {
		sat= -sat;
		col= col + M_PI;
		}
      abctorgb (hel, sat, col, rot, grn, blu);
//      hsytorgb (col, sat, hel, rot, grn, blu);
	  prot= lrint (rot*255);
	  pgrn= lrint (grn*255);
	  pblu= lrint (blu*255);
	  psbild0.putpixel (laufx, laufy, prot, pgrn, pblu);
	  }
  }

void erzeugedichromat3bild (char* iname)
  {
  cjpegdatei eingabebild (iname);
  printf ("xanz: %d\n", eingabebild.xanz);
  printf ("yanz: %d\n", eingabebild.yanz);
  char psname0[1000];
  char psname1[1000];
  char psname2[1000];
  char psname3[1000];
  sprintf (psname0, iname);
  sprintf (psname1, iname);
  sprintf (psname2, iname);
  sprintf (psname3, iname);
  strcat (psname0, "-rgb-m.bmp");
  strcat (psname1, "-rgb-dc-0.bmp");
  strcat (psname2, "-rgb-dc-120.bmp");
  strcat (psname3, "-rgb-dc--120.bmp");
  cbmpdatei psbild0 (psname0, eingabebild.xanz, eingabebild.yanz);
  cbmpdatei psbild1 (psname1, eingabebild.xanz, eingabebild.yanz);
  cbmpdatei psbild2 (psname2, eingabebild.xanz, eingabebild.yanz);
  cbmpdatei psbild3 (psname3, eingabebild.xanz, eingabebild.yanz);
  for (integer laufy= 0; laufy < eingabebild.yanz; laufy++)
    for (integer laufx= 0; laufx < eingabebild.xanz; laufx++)
      {
      integer prot, pgrn, pblu;
	  eingabebild.getpixel (laufx, laufy, prot, pgrn, pblu);
	  integer dc0= (prot + pgrn + pblu + 1)/3;
	  integer dc1= (pgrn + pblu + 1)/2;
	  integer dc2= (pblu + prot + 1)/2;
	  integer dc3= (prot + pgrn + 1)/2;
	  psbild0.putpixel (laufx, laufy, dc0, dc0, dc0);
	  psbild1.putpixel (laufx, laufy, prot, dc1, dc1);
	  psbild2.putpixel (laufx, laufy, dc2, pgrn, dc2);
	  psbild3.putpixel (laufx, laufy, dc3, dc3, pblu);
	  }
  }

void transform1color (char* iname, real ihue)
  {
  cjpegdatei eingabebild (iname);
  printf ("xanz: %d\n", eingabebild.xanz);
  printf ("yanz: %d\n", eingabebild.yanz);
  char psname[1000];
  char zahl[1000];
  sprintf (psname, iname);
  sprintf (zahl, "-%f", ihue);
  strcat (psname, zahl);
  strcat (psname, "-1c.ps");
  cpsdatei opsdatei (psname, eingabebild.xanz, eingabebild.yanz);
  for (integer laufy= 0; laufy < eingabebild.yanz; laufy++)
    for (integer laufx= 0; laufx < eingabebild.xanz; laufx++)
      {
      real rot, grn, blu;
      real hue, sat, hel;
	  integer prot, pgrn, pblu;
	  eingabebild.getpixel (laufx, laufy, prot, pgrn, pblu);
	  rot= real (prot)/255;
	  grn= real (pgrn)/255;
	  blu= real (pblu)/255;
      rgbtohsy (rot, grn, blu, hue, sat, hel);
	  hel*= 0.7;
	  sat*= 0.6442676;
	  hue= ihue;
      hsytorgb (hue, sat, hel, rot, grn, blu);
	  prot= lrint (rot*255);
	  pgrn= lrint (grn*255);
	  pblu= lrint (blu*255);
	  opsdatei.putpixel (laufx, laufy, prot, pgrn, pblu);
	  }
  }

void separate1color (char* iname)
  {
  cjpegdatei eingabebild (iname);
  printf ("xanz: %ld\n", eingabebild.xanz);
  printf ("yanz: %ld\n", eingabebild.yanz);
  char psname1[1000];
  char psname2[1000];
  sprintf (psname1, iname);
  sprintf (psname2, iname);
  strcat (psname1, "-1.ps");
  strcat (psname2, "-2.ps");
  cpsdatei psbild1 (psname1, eingabebild.xanz, eingabebild.yanz);
  cpsdatei psbild2 (psname2, eingabebild.xanz, eingabebild.yanz);
  for (integer laufy= 0; laufy < eingabebild.yanz; laufy++)
    for (integer laufx= 0; laufx < eingabebild.xanz; laufx++)
      {
      real rot, grn, blu;
      real hue, sat, hel;
	  integer prot, pgrn, pblu, pwht, pcol;
	  eingabebild.getpixel (laufx, laufy, prot, pgrn, pblu);
	  rot= real (prot)/255;
	  grn= real (pgrn)/255;
	  blu= real (pblu)/255;
      rgbtohsy (rot, grn, blu, hue, sat, hel);
	  hel*= 0.7;
	  sat*= 0.6442676;
	  hue= 0;
      hsytorgb (hue, sat, hel, rot, grn, blu);
	  prot= lrint (rot*255);
	  pgrn= lrint (grn*255);
	  pblu= lrint (blu*255);
      pwht= prot;
      pcol= 255 - prot + pgrn;
      psbild1.putpixel (laufx, laufy, pwht, pwht, pwht);
      psbild2.putpixel (laufx, laufy, pcol, pcol, pcol);
	  }
  }

void transform2color (char* iname, real ihue)
  {
  cjpegdatei eingabebild (iname);
  printf ("xanz: %ld\n", eingabebild.xanz);
  printf ("yanz: %ld\n", eingabebild.yanz);
  char psname[1000];
  char zahl[1000];
  sprintf (psname, iname);
  sprintf (zahl, "-%lf", ihue);
  strcat (psname, zahl);
  strcat (psname, "-2c.ps");
  cpsdatei psbild (psname, eingabebild.xanz, eingabebild.yanz);
  for (integer laufy= 0; laufy < eingabebild.yanz; laufy++)
    for (integer laufx= 0; laufx < eingabebild.xanz; laufx++)
      {
      real rot, grn, blu;
      real hue, sat, hel;
	  real prot, pgrn, pblu;
	  eingabebild.getpixel (laufx, laufy, prot, pgrn, pblu);
	  rot= real (prot)/255;
	  grn= real (pgrn)/255;
	  blu= real (pblu)/255;
      rgbtohsy (rot, grn, blu, hue, sat, hel);
	  hel*= 0.8;
	  sat= sat*0.8*cos (hue - ihue);
	  hue= ihue;
      hsytorgb (hue, sat, hel, rot, grn, blu);
	  prot= lrint (rot*255);
	  pgrn= lrint (grn*255);
	  pblu= lrint (blu*255);
	  psbild.putpixel (laufx, laufy, prot, pgrn, pblu);
	  }
  }
*/
void transformgegenfarbe (char* iname)
  {
  cjpegdatei eingabebild (iname);
  printf ("xanz: %ld\n", eingabebild.xanz);
  printf ("yanz: %ld\n", eingabebild.yanz);
  char psname[1000]= "bla.jpg";
  cbmpdatei psbild (psname, eingabebild.xanz, eingabebild.yanz);

  for (integer laufy= 0; laufy < eingabebild.yanz; laufy++)
    for (integer laufx= 0; laufx < eingabebild.xanz; laufx++)
      {
      real rot, grn, blu;
      real hue, sat, hel;
	  real prot, pgrn, pblu;
	  eingabebild.getpixel (laufx, laufy, prot, pgrn, pblu);
	  rot= real (prot)/255;
	  grn= real (pgrn)/255;
	  blu= real (pblu)/255;
      rgbtohsy (rot, grn, blu, hue, sat, hel);
	  //hel*= 0.62;
	  //sat*= 0.6442676;
	  hue-= M_PI;
      hsytorgb (hue, sat, hel, rot, grn, blu);
	  prot= lrint (rot*255);
	  pgrn= lrint (grn*255);
	  pblu= lrint (blu*255);
	  if (prot < 0)
	    prot= 0;
	  if (pgrn < 0)
	    pgrn= 0;
	  if (pblu < 0)
	    pblu= 0;
	  if (prot > 255)
	    prot= 255;
	  if (pgrn > 255)
	    pgrn= 255;
	  if (pblu > 255)
	    pblu= 255;
	  psbild.putpixel (laufx, laufy, prot, pgrn, pblu);
	  }
  
  }
/*
void huescan (char* iname)
  {
  for (signed long lhue= 0; lhue < 12; lhue++)
    {
	real hue= lhue*M_PI/12;
	transform2color (iname, hue);
	}
  }
*/
int main (int argc, char** argv)
  {
  transformgegenfarbe (argv[1]);
  return 0;
  if (argc > 2)
    {
    transformgegenfarbe (argv[1]);
    real par1 (0), par2 (0);
	if (argc > 3)
      sscanf (argv[3], "%Lf", &par1);
	if (argc > 4)
	  sscanf (argv[4], "%Lf", &par2);
    switch (argv[2][0])
      {
      /*
	  case 0x30:
        erzeugemonobild (argv[1]);
        break;
      case 0x31:
        erzeugedichromatbild (argv[1], argv[3]);
        break;
      case 0x32:
        erzeugedichromat3bild (argv[1]);
        break;
      case 0x33:
        transform1color (argv[1], par1);
        break;
      case 0x34:
        transform2color (argv[1], par1);
        break;
      case 0x35:
        erzeugejpgbild (argv[1]);
        break;
      case 0x36:
        separate1color (argv[1]);
        break;
      */
      case 0x37:
        transformgegenfarbe (argv[1]);
        break;
      /*
	  case 0x38:
        huescan (argv[1]);
        break;
	  */
      }
    return 0;
    }
  return 0;
  }
