// erstellt Testbilder für Farbräume

#include "../screen/allscr.h"
#include "single.h"
#include "../class/vektor.h"

#include <cstdio>
#include <cstring>

void zeichnecubecut (double ischnitt)
  {
  char name[1000];
  char zahl[1000];
  sprintf (name, "cubecut-");
  sprintf (zahl, "%f", ischnitt);
  strcat (name, zahl);
  strcat (name, "-cmyk.ps");
  cpsdatei hsybild (name, 767, 767);
  cvektor3 px (2, -1, -1);
  cvektor3 py (0, 0, 0);
  cvektor3 pz (1, 1, 1);
  cbasis3 huebasis (px, py, pz);
  huebasis= normiere (huebasis);
  cbasis3 transbasis (~huebasis);
  for (signed long laufy= 0; laufy < 767; laufy++)
    {
    for (signed long laufx= 0; laufx < 767; laufx++)
      {
      double kx= double (laufx - 383)/460;
      double ky= double (laufy - 383)/460;
      cvektor3 vkreis= cvektor3 (kx, ky, ischnitt);
      cvektor3 vrgb= transbasis*vkreis;
      double rot= vrgb.x;
      double grn= vrgb.y;
      double blu= vrgb.z;
      if ((rot < 0) || (grn < 0) || (blu < 0) || (rot > 1) || (grn > 1) || (blu > 1))
        rot= grn= blu= 1;
      signed long prot= lrint (rot*255);
      signed long pgrn= lrint (grn*255);
      signed long pblu= lrint (blu*255);
      hsybild.putpixel (laufx, laufy, prot, pgrn, pblu);
      }
    }
  }

void zeichnecubecutbmp (double ischnitt)
  {
  char name[1000];
  char zahl[1000];
  sprintf (name, "cubecut-");
  sprintf (zahl, "%f", ischnitt);
  strcat (name, zahl);
  strcat (name, ".bmp");
  cbmpdatei hsybild (name, 767, 767);
  cvektor3 px (2, -1, -1);
  cvektor3 py (0, 0, 0);
  cvektor3 pz (1, 1, 1);
  cbasis3 huebasis (px, py, pz);
  huebasis= normiere (huebasis);
  cbasis3 transbasis (~huebasis);
  for (signed long laufy= 0; laufy < 767; laufy++)
    {
    for (signed long laufx= 0; laufx < 767; laufx++)
      {
      double kx= double (laufx - 383)/460;
      double ky= double (laufy - 383)/460;
      cvektor3 vkreis= cvektor3 (kx, ky, ischnitt);
      cvektor3 vrgb= transbasis*vkreis;
      double rot= vrgb.x;
      double grn= vrgb.y;
      double blu= vrgb.z;
      if ((rot < 0) || (grn < 0) || (blu < 0) || (rot > 1) || (grn > 1) || (blu > 1))
        rot= grn= blu= 1;
      signed long prot= lrint (rot*255);
      signed long pgrn= lrint (grn*255);
      signed long pblu= lrint (blu*255);
      hsybild.putpixel (laufx, laufy, prot, pgrn, pblu);
      }
    }
  }

void zeichnehellcut (double ihell)
  {
  char name[1000];
  char zahl[1000];
  sprintf (name, "hellcut-");
  sprintf (zahl, "%f", ihell);
  strcat (name, zahl);
  strcat (name, "-cmyk.ps");
  cpsdatei hsybild (name, 767, 767);
  double fx= rgbtoy (1.0, 0.0, 0.0);
  double fy= rgbtoy (0.0, 1.0, 0.0);
  double fz= rgbtoy (0.0, 0.0, 1.0);
  cvektor3 pz (fx, fy, fz);
  cvektor3 py= cvektor3 (1, 0, 0) ^ pz;
  cvektor3 px= pz ^ py;
  cbasis3 huebasis (px, py, pz);
  huebasis= normiere (huebasis);
  cbasis3 transbasis (~huebasis);
  double invhell= ihell/rgbtoy (transbasis.z.x, transbasis.z.y, transbasis.z.z);
  for (signed long laufy= 0; laufy < 767; laufy++)
    {
    for (signed long laufx= 0; laufx < 767; laufx++)
      {
      double kx= double (laufx - 300)/400;
      double ky= double (laufy - 500)/400;
      cvektor3 vkreis= cvektor3 (kx, ky, invhell);
      cvektor3 vrgb= transbasis*vkreis;
      double rot= vrgb.x;
      double grn= vrgb.y;
      double blu= vrgb.z;
      if ((rot < 0) || (grn < 0) || (blu < 0) || (rot > 1) || (grn > 1) || (blu > 1))
        rot= grn= blu= 1;
      signed long prot= lrint (rot*255);
      signed long pgrn= lrint (grn*255);
      signed long pblu= lrint (blu*255);
      hsybild.putpixel (laufx, laufy, prot, pgrn, pblu);
      }
    }
  }

void zeichnehuecut (double ihue)
  {
  char name[1000];
  char zahl[1000];
  sprintf (name, "huecut-");
  sprintf (zahl, "%f", ihue);
  strcat (name, zahl);
  strcat (name, "-cmyk.ps");
  cpsdatei hsybild (name, 767, 767);
  cvektor3 pz (1, 1, 1);
  cvektor3 px (2, -1, -1);
  cvektor3 py (0, 0, 0);
  cbasis3 huebasis (px, py, pz);
  huebasis= normiere (huebasis);
  px= cos (ihue) * huebasis.x + sin (ihue) * huebasis.y;
  py= cvektor3 (1, 1, 1);
  pz= px ^ py;
  huebasis= normiere (cbasis3 (px, py, pz));
  cbasis3 transbasis (~huebasis);
  for (signed long laufy= 0; laufy < 767; laufy++)
    {
    for (signed long laufx= 0; laufx < 767; laufx++)
      {
      double kx= double (laufx - 383)/440;
      double ky= double (laufy)/440;
      cvektor3 vkreis= cvektor3 (kx, ky, 0);
      cvektor3 vrgb= transbasis*vkreis;
      double rot= vrgb.x;
      double grn= vrgb.y;
      double blu= vrgb.z;
      if ((rot < 0) || (grn < 0) || (blu < 0) || (rot > 1) || (grn > 1) || (blu > 1))
        rot= grn= blu= 1;
      signed long prot= lrint (rot*255);
      signed long pgrn= lrint (grn*255);
      signed long pblu= lrint (blu*255);
      hsybild.putpixel (laufx, laufy, prot, pgrn, pblu);
      }
    }
  }

// Rechteck Farbton (Sättigung, Helligkeit)
void zeichnerH (double ihue)
  {
  char name[1000];
  char zahl[1000];
  sprintf (name, "R-SY-");
  sprintf (zahl, "%f", ihue);
  strcat (name, zahl);
  strcat (name, "-cmyk.ps");
  cpsdatei hsybild (name, 1024, 768);
  for (signed long laufy= 0; laufy < 768; laufy++)
    {
    for (signed long laufx= 0; laufx < 1024; laufx++)
      {
      double sat= double (laufx)/1024;
      double hell= double (laufy)/768;
      double rot, grn, blu;
      hsytorgb (ihue, sat, hell, rot, grn, blu);
      if ((rot > 1) || (grn > 1) || (blu > 1) || (rot < 0) || (grn < 0) || (blu < 0))
        {
     rot= grn= blu= 1;
     }
      signed long prot= lrint (rot*255);
      signed long pgrn= lrint (grn*255);
      signed long pblu= lrint (blu*255);
      hsybild.putpixel (laufx, laufy, prot, pgrn, pblu);
      }
    }
  }

// Rechteck (Farbton) Sättigung (Helligkeit)
void zeichnerS (double isat)
  {
  char name[1000];
  char zahl[1000];
  sprintf (name, "R-HY-");
  sprintf (zahl, "%f", isat);
  strcat (name, zahl);
  strcat (name, "-cmyk.ps");
  cpsdatei hsybild (name, 1024, 768);
  for (signed long laufy=0; laufy < 768; laufy++)
    {
    for (signed long laufx=0; laufx < 1024; laufx++)
      {
      double hue= double (laufx)*M_PI/512;
      double hell= double (laufy)/768;
      double rot, grn, blu;
      hsytorgb (hue, isat, hell, rot, grn, blu);
      if ((rot > 1) || (grn > 1) || (blu > 1) || (rot < 0) || (grn < 0) || (blu < 0))
        rot= grn= blu= 1;
      signed long prot= lrint (rot*255);
      signed long pgrn= lrint (grn*255);
      signed long pblu= lrint (blu*255);
      hsybild.putpixel (laufx, laufy, prot, pgrn, pblu);
      }
    }
  }

// Rechteck (Farbton, Sättigung) Helligkeit
void zeichnerY (double ihell)
  {
  char name[1000];
  char zahl[1000];
  sprintf (name, "R-HS-");
  sprintf (zahl, "%f", ihell);
  strcat (name, zahl);
  strcat (name, "-cmyk.ps");
  cpsdatei hsybild (name, 1024, 768);
  for (signed long laufy=0; laufy < 768; laufy++)
    {
    for (signed long laufx=0; laufx < 1024; laufx++)
      {
      double hue= (double) (laufx)*M_PI/512;
      double sat= (double) (laufy)/768;
      double rot, grn, blu;
      hsytorgb (hue, sat, ihell, rot, grn, blu);
      if ((rot > 1) || (grn > 1) || (blu > 1) || (rot < 0) || (grn < 0) || (blu < 0))
        rot= grn= blu= 1;
      signed long prot= lrint (rot*255);
      signed long pgrn= lrint (grn*255);
      signed long pblu= lrint (blu*255);
      hsybild.putpixel (laufx, laufy, prot, pgrn, pblu);
      }
    }
  }

void zeichnekS (double isat)
  {
  char name[1000];
  char zahl[1000];
  sprintf (name, "K-HY-");
  sprintf (zahl, "%f", isat);
  strcat (name, zahl);
  strcat (name, "-cmyk.ps");
  cpsdatei hsybild (name, 767, 767);
  for (signed long laufy= 0; laufy < 767; laufy++)
    {
    for (signed long laufx= 0; laufx < 767; laufx++)
      {
      double kx= double (laufx - 383)/400;
      double ky= double (laufy - 383)/400;
      double phue= atan2 (ky, kx);
      double phell= sqrt (kx*kx + ky*ky);
      double rot, grn, blu;
      hsytorgb (phue, isat, phell, rot, grn, blu);
      if ((rot < 0) || (grn < 0) || (blu < 0) || (rot > 1) || (grn > 1) || (blu > 1))
        rot= grn= blu= 1;
      signed long prot= lrint (rot*255);
      signed long pgrn= lrint (grn*255);
      signed long pblu= lrint (blu*255);
      hsybild.putpixel (laufx, laufy, prot, pgrn, pblu);
      }
    }
  }

void zeichnekSbmp (double isat)
  {
  char name[1000];
  char zahl[1000];
  sprintf (name, "K-HY-");
  sprintf (zahl, "%f", isat);
  strcat (name, zahl);
  strcat (name, ".bmp");
  cbmpdatei hsybild (name, 767, 767);
  for (signed long laufy= 0; laufy < 767; laufy++)
    {
    for (signed long laufx= 0; laufx < 767; laufx++)
      {
      double kx= double (laufx - 383)/400;
      double ky= double (laufy - 383)/400;
      double phue= atan2 (ky, kx);
      double phell= sqrt (kx*kx + ky*ky);
      double rot, grn, blu;
      hsytorgb (phue, isat, phell, rot, grn, blu);
      if ((rot < 0) || (grn < 0) || (blu < 0) || (rot > 1) || (grn > 1) || (blu > 1))
        rot= grn= blu= 1;
      signed long prot= lrint (rot*255);
      signed long pgrn= lrint (grn*255);
      signed long pblu= lrint (blu*255);
      hsybild.putpixel (laufx, laufy, prot, pgrn, pblu);
      }
    }
  }

void zeichnekY (double ihell)
  {
  char name[1000];
  char zahl[1000];
  sprintf (name, "K-HS-");
  sprintf (zahl, "%f", ihell);
  strcat (name, zahl);
  strcat (name, "-cmyk.ps");
  cpsdatei hsybild (name, 767, 767);
  for (signed long laufy= 0; laufy < 767; laufy++)
    {
    for (signed long laufx= 0; laufx < 767; laufx++)
      {
      double kx= double (laufx - 383)/400;
      double ky= double (laufy - 383)/400;
      double phue= atan2 (ky, kx);
      double psat= sqrt (kx*kx + ky*ky);
      double rot, grn, blu;
      hsytorgb (phue, psat, ihell, rot, grn, blu);
      if ((rot < 0) || (grn < 0) || (blu < 0) || (rot > 1) || (grn > 1) || (blu > 1))
        rot= grn= blu= 1;
      signed long prot= lrint (rot*255);
      signed long pgrn= lrint (grn*255);
      signed long pblu= lrint (blu*255);
      hsybild.putpixel (laufx, laufy, prot, pgrn, pblu);
      }
    }
  }

void zeichnekYbmp (double ihell)
  {
  char name[1000];
  char zahl[1000];
  sprintf (name, "K-HS-");
  sprintf (zahl, "%f", ihell);
  strcat (name, zahl);
  strcat (name, ".bmp");
  cbmpdatei hsybild (name, 767, 767);
  for (signed long laufy= 0; laufy < 767; laufy++)
    {
    for (signed long laufx= 0; laufx < 767; laufx++)
      {
      double kx= double (laufx - 383)/400;
      double ky= double (laufy - 383)/400;
      double phue= atan2 (ky, kx);
      double psat= sqrt (kx*kx + ky*ky);
      double rot, grn, blu;
      hsytorgb (phue, psat, ihell, rot, grn, blu);
      if ((rot < 0) || (grn < 0) || (blu < 0) || (rot > 1) || (grn > 1) || (blu > 1))
        rot= grn= blu= 1;
      signed long prot= lrint (rot*255);
      signed long pgrn= lrint (grn*255);
      signed long pblu= lrint (blu*255);
      hsybild.putpixel (laufx, laufy, prot, pgrn, pblu);
      }
    }
  }

void zeichnespektrumRS (double ihell)
  {
  char name[1000];
  char zahl[1000];
  sprintf (name, "spektrum-R-HS-");
  sprintf (zahl, "%f", ihell);
  strcat (name, zahl);
  strcat (name, "-cmyk.ps");
  cpsdatei hsybild (name, 1024, 768);
  for (signed long laufy=0; laufy < 768; laufy++)
    {
    for (signed long laufx=0; laufx < 1024; laufx++)
      {
      double hue= double (laufx)*M_PI/512;
      double sat= double (laufy)/768*0.6154796;
      double rot, grn, blu;
      hsytorgb (hue, sat, ihell, rot, grn, blu);
      if ((rot > 1) || (grn > 1) || (blu > 1) || (rot < 0) || (grn < 0) || (blu < 0))
        rot= grn= blu= 1;
      signed long prot= lrint (rot*255);
      signed long pgrn= lrint (grn*255);
      signed long pblu= lrint (blu*255);
      hsybild.putpixel (laufx, laufy, prot, pgrn, pblu);
      }
    }
  }

void zeichnespektrumkY (double ihell)
  {
  char name[1000];
  char zahl[1000];
  sprintf (name, "spektrum-K-HS-");
  sprintf (zahl, "%f", ihell);
  strcat (name, zahl);
  strcat (name, "-cmyk.ps");
  cpsdatei hsybild (name, 767, 767);
  double satmax= 0.38;
  for (signed long laufy= 0; laufy < 767; laufy++)
    {
    for (signed long laufx= 0; laufx < 767; laufx++)
      {
      double kx= double (laufx - 383)*satmax/383;
      double ky= double (laufy - 383)*satmax/383;
      double phue= atan2 (ky, kx);
      double psat= sqrt (kx*kx + ky*ky);
      double rot, grn, blu;
      hsytorgb (phue, psat, ihell, rot, grn, blu);
      double prad= sqrt (kx*kx + ky*ky);
      if (prad > satmax)
        rot= grn= blu= 1;
      if ((rot < 0) || (grn < 0) || (blu < 0) || (rot > 1) || (grn > 1) || (blu > 1))
        rot= grn= blu= 1;
      signed long prot= lrint (rot*255);
      signed long pgrn= lrint (grn*255);
      signed long pblu= lrint (blu*255);
      hsybild.putpixel (laufx, laufy, prot, pgrn, pblu);
      }
    }
  }

void testsuite ()
  {
  zeichnecubecutbmp (1/sqrt(3));
  return;
  zeichnecubecut (sqrt(3)/2);
  zeichnecubecut (2/sqrt(3));
  zeichnehellcut (0.114);
  zeichnehellcut (0.299);
  zeichnehellcut (0.5);
  zeichnehellcut (0.587);
  for (signed long lauf= 0; lauf < 12; lauf++)
	zeichnerH (lauf*M_PI/6);
  for (signed long lauf= 0; lauf < 6; lauf++)
	zeichnehuecut (lauf*M_PI/6);
  zeichnekS (0.1);
  zeichnekS (0.6154796);
  zeichnekS (0.7);
  zeichnekY (0.114);
  zeichnekY (0.299);
  zeichnekY (0.5);
  zeichnekY (0.587);
  zeichnespektrumkY (0.5);
  zeichnerS (0.1);
  zeichnerS (0.6154796);
  zeichnerS (0.7);
  zeichnerY (0.114);
  zeichnerY (0.299);
  zeichnerY (0.5);
  zeichnerY (0.587);
  }

int main ()
  {
//  zeichnecubecutbmp (sqrt(3)/2);
//  zeichnekYbmp (0.114);
//  zeichnekSbmp (0.6154796);
  testsuite ();
//  zeichnespektrumkY (0.5);
//  zeichnecubecut (0.86);
//  zeichnehuecut (M_PI/6);
  return 0;
  }
