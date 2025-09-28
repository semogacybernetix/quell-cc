// Erzeugt eine Apfelmännchengrafik
// Version 0.0 2018.09.09
// Version 0.1 2018.09.11 objektorientiert

#include "single.h"
#include "../class/vektor.h"
#include "../screen/allscr.h"

#include <iostream>         // printf, random
#include <sys/times.h>      // times (NULL)
#include <unistd.h>         // sysconf, _SC_CLK_TCK

//--------------------------------------------- Farbtabellen ---------------------------------------

void zufallsfarben (integer* pfarbe)
  {
  pfarbe[0]= 255;
  pfarbe[256]= 0;
  pfarbe[512]= 0;
  pfarbe[  0 + 255]= 0;
  pfarbe[256 + 255]= 0;
  pfarbe[512 + 255]= 0;
  for (integer flauf= 1; flauf < 255; flauf++)
    {
    pfarbe[flauf]= integer (random () % 256);
    pfarbe[256 + flauf]= integer (random () % 256);
    pfarbe[512 + flauf]= integer (random () % 256);
    //printf ("%10lld  %10lld  %10lld\n", pfarbe[flauf], pfarbe[256 + flauf], pfarbe[512 + flauf]);
    }
  }

void monochrom (integer* pfarbe)
  {
  for (integer flauf= 0; flauf < 128; flauf++)
    {
    pfarbe[flauf]= 128 + flauf;
    pfarbe[256 + flauf]= 128 + flauf;
    pfarbe[512 + flauf]= 128 + flauf;
    pfarbe[128 + flauf]= 255 - flauf;
    pfarbe[128 + 256 + flauf]= 255 - flauf;
    pfarbe[128 + 512 + flauf]= 255 - flauf;
    }
  pfarbe[  0 + 255]= 0;
  pfarbe[256 + 255]= 0;
  pfarbe[512 + 255]= 0;
  }

void spektrumsinus (integer* pfarbe)
  {
  real r, g, b;
  for (integer flauf= 0; flauf < 255; flauf++)
    {
    // Hilfswerte
    real winkel= flauf*M_PI/3;
    real hcos= cos (winkel)/sqrt (6);
    real hsin= sin (winkel)/sqrt (2);
   
    // unskalierte RGB-Werte
    r= 1 + 2*hcos;
    g= 1 - hcos + hsin;
    b= 1 - hcos - hsin;
    
    printf (" winkel: %10.2Lf, %10.2Lf, %10.2Lf %10.2Lf\n", winkel, r, g, b);

    pfarbe[flauf]= r*140;
    pfarbe[256 + flauf]= g*140;
    pfarbe[512 + flauf]= b*140;
    }
  pfarbe[  0 + 255]= 0;
  pfarbe[256 + 255]= 0;
  pfarbe[512 + 255]= 0;
  }

void spektrum (integer* pfarbe)
  {
  for (integer flauf= 0; flauf < 42; flauf++)
    {
    // rot -> gelb
    pfarbe[flauf]= 252;
    pfarbe[256 + flauf]= flauf*6;
    pfarbe[512 + flauf]= 0;
    }
  for (integer flauf= 42; flauf < 84; flauf++)
    {
    // gelb -> grün
    pfarbe[flauf]= 246 - (flauf - 42)*6;
    pfarbe[256 + flauf]= 248;
    pfarbe[512 + flauf]= 0;
    }
  for (integer flauf= 84; flauf < 127; flauf++)
    {
    // grün -> blaugrün
    pfarbe[flauf]= 0;
    pfarbe[256 + flauf]= 252;
    pfarbe[512 + flauf]= (flauf - 84)*6;
    }
  for (integer flauf= 127; flauf < 170; flauf++)
    {
    // blaugrün -> blau
    pfarbe[flauf]= 0;
    pfarbe[256 + flauf]= 252 - (flauf - 127)*6;
    pfarbe[512 + flauf]= 252;
    }
  for (integer flauf= 170; flauf < 212; flauf++)
    {
    // blau -> violett
    pfarbe[flauf]= (flauf - 170)*6;
    pfarbe[256 + flauf]= 0;
    pfarbe[512 + flauf]= 252;
    }
  for (integer flauf= 212; flauf < 255; flauf++)
    {
    // violett -> rot
    pfarbe[flauf]= 246;
    pfarbe[256 + flauf]= 0;
    pfarbe[512 + flauf]= 252 - (flauf - 212)*6;
    }
  pfarbe[  0 + 255]= 0;
  pfarbe[256 + 255]= 0;
  pfarbe[512 + 255]= 0;
  }

void spektrummanuell (integer* pfarbe)
  {
  integer z= 140;
  pfarbe[z + 000]= 255;
  pfarbe[z + 256]= 0;
  pfarbe[z + 512]= 0;
  z++;
  pfarbe[z + 000]= 255;
  pfarbe[z + 256]= 127;
  pfarbe[z + 512]= 0;
  z++;
  pfarbe[z + 000]= 255;
  pfarbe[z + 256]= 200;
  pfarbe[z + 512]= 0;
  z++;
  pfarbe[z + 000]= 255;
  pfarbe[z + 256]= 255;
  pfarbe[z + 512]= 0;
  z++;
  pfarbe[z + 000]= 178;
  pfarbe[z + 256]= 255;
  pfarbe[z + 512]= 0;
  z++;
  pfarbe[z + 000]= 0;
  pfarbe[z + 256]= 255;
  pfarbe[z + 512]= 0;
  z++;
  pfarbe[z + 000]= 0;
  pfarbe[z + 256]= 255;
  pfarbe[z + 512]= 160;
  z++;
  pfarbe[z + 000]= 0;
  pfarbe[z + 256]= 255;
  pfarbe[z + 512]= 255;
  z++;
  pfarbe[z + 000]= 0;
  pfarbe[z + 256]= 160;
  pfarbe[z + 512]= 255;
  z++;
  pfarbe[z + 000]= 0;
  pfarbe[z + 256]= 0;
  pfarbe[z + 512]= 255;
  z++;
  pfarbe[z + 000]= 150;
  pfarbe[z + 256]= 0;
  pfarbe[z + 512]= 255;
  z++;
  pfarbe[z + 000]= 255;
  pfarbe[z + 256]= 0;
  pfarbe[z + 512]= 255;
  z++;
  for (integer flauf= 999; flauf < 255; flauf++)
    {
    pfarbe[flauf]= integer (random () % 6);
    pfarbe[256 + flauf]= integer (random () % 6);
    pfarbe[512 + flauf]= integer (random () % 6);
    }
  pfarbe[255 + 000]= 0;
  pfarbe[255 + 256]= 0;
  pfarbe[255 + 512]= 0;
  }

//--------------------------- Fraktalobjekt --------------------------------------------------------

struct mjfraktal
  {
  cvektor2      bildmitte;
  real          bildgr;
  integer       iterationen;
  integer       farbtabelle[768];
  
  mjfraktal ()
    {
    bildmitte= cvektor2 (0, 0);  // Standardapfelmännchen
    bildgr= 4;
    iterationen= 500;
    spektrummanuell (farbtabelle);
    }
  
  };

//----------------------------- Fraktale -----------------------------------------------------------

void standardapfel (mjfraktal& pfraktal)
  {
  pfraktal.bildmitte= cvektor2 (0, 0);  // Standardapfelmännchen
  pfraktal.bildgr= 4.0;
  pfraktal.iterationen= 500;
  spektrummanuell (pfraktal.farbtabelle);
  }

void apfelschief (mjfraktal& pfraktal)
  {
  pfraktal.bildmitte= cvektor2 (0.4435, 0.374);   // Apfelmännchen schiefer Kopf
  pfraktal.bildgr= 0.01;
  pfraktal.iterationen= 500;
  spektrum (pfraktal.farbtabelle);
  }

void spirale (mjfraktal& pfraktal)
  {
  pfraktal.bildmitte= cvektor2 (-0.747162, 0.087584);  // Spirale
  pfraktal.bildgr= 0.0001;
  pfraktal.iterationen= 1000;
  spektrumsinus (pfraktal.farbtabelle);
  }

void baum (mjfraktal& pfraktal)
  {
  pfraktal.bildmitte= cvektor2 (0.296635, 0.02093);  // Baum
  pfraktal.bildgr= 0.00003;
  pfraktal.iterationen= 1000;
  spektrummanuell (pfraktal.farbtabelle);
  }

void stern (mjfraktal& pfraktal)
  {
  pfraktal.bildmitte= cvektor2 (-1.26840686, 0.124791718);  // Stern
  pfraktal.bildgr= 0.0000003;
  pfraktal.iterationen= 2000;
  spektrum (pfraktal.farbtabelle);
  }

void papfel (mjfraktal& pfraktal)
  {
  pfraktal.bildmitte= cvektor2 (-1.26840686, 0.124791718);  // prachtvolles Apfelmännchen
  pfraktal.bildgr= 0.00000003;
  pfraktal.iterationen= 4000;
  spektrum (pfraktal.farbtabelle);
  }

void sapfel (mjfraktal& pfraktal)
  {
  pfraktal.bildmitte= cvektor2 (-1.99998588115, 0);  // extremes Spitzenapfelmännchen
  pfraktal.bildgr= 10e-10;
  pfraktal.iterationen= 4000;
  zufallsfarben (pfraktal.farbtabelle);
  }

//------------------------------------------------ Fraktalberechnung ------------------------------------------------------

void apfel ()
  {
  // Zeichenebene erzeugen
  cbmpdatei apfelbmp ("fraktal.bmp", 1920, 1080);
  integer xanz= apfelbmp.xanz;
  integer yanz= apfelbmp.yanz;
  
  // Fraktaldaten aus Fraktalobjekt auslesen
  mjfraktal fraktal;
  sapfel (fraktal);
  cvektor2 bildmitte= fraktal.bildmitte;  // Objekt
  real pixelgr= fraktal.bildgr/yanz;
  integer iterationen= fraktal.iterationen;
  integer farbe[768];
  for (integer lauf= 0; lauf < 768; lauf++)
    farbe[lauf]= fraktal.farbtabelle[lauf];

  // Genauigkeit der Stoppuhr ausgeben
  signed long ticksps= sysconf (_SC_CLK_TCK);
  printf ("\n");
  printf ("Genauigkeit der Stopuhr: %10ld Ticks pro Sekunde\n", ticksps);

  // Stoppuhr starten
  clock_t startticks;
  startticks= times (NULL);

//--------------------------------- Mandelbrot-Menge berechnen ----------------------------------------
//*
  cvektor2 bilddiag= pixelgr/2 * cvektor2 (xanz - 1, yanz - 1);
  cvektor2 bildecke= bildmitte - bilddiag; 
  cvektor2 poslauf, zsum;
  for (integer ylauf= 0; ylauf < yanz; ylauf++)
    for (integer xlauf= 0; xlauf < xanz; xlauf++)
      {
      poslauf.x= bildecke.x + pixelgr*xlauf;
      poslauf.y= bildecke.y + pixelgr*ylauf;
      zsum= poslauf;
      for (integer zlauf= 0; zlauf < iterationen; zlauf++)
        {
        if (zsum%zsum >= 4)
          {
          apfelbmp.putpixel (xlauf, ylauf, farbe[zlauf%255], farbe[zlauf%255 + 256], farbe[zlauf%255 + 512]);
          break;
          }
        zsum= zsum*zsum + poslauf;
        }
      }
//*/
//--------------------------------- Julia-Menge berechnen ----------------------------------------
/*
  cvektor2 julia;
  julia= cvektor2 (0, 0);
  julia= cvektor2 (0.1, 0.1);
  julia= cvektor2 (5, 5);
  julia= cvektor2 (1, 1);
  julia= cvektor2 (-1.26840686, 0.124791718);  // prachtvolles Apfelmännchen
  julia= cvektor2 (-1.26840686, 0.124791718);  // Stern
  julia= cvektor2 (0.296635, 0.02093);  // Baum
  julia= cvektor2 (-0.747162, 0.087584);  // Spirale
  julia= cvektor2 (0.4435, 0.374);   // Apfelmännchen schiefer Kopf

  cvektor2 bilddiag= pixelgr/2 * cvektor2 (xanz - 1, yanz - 1);
  cvektor2 bildecke= bildmitte - bilddiag; 
  cvektor2 poslauf, zsum;
  for (integer ylauf= 0; ylauf < yanz; ylauf++)
    for (integer xlauf= 0; xlauf < xanz; xlauf++)
      {
      poslauf.x= bildecke.x + pixelgr*xlauf;
      poslauf.y= bildecke.y + pixelgr*ylauf;
      zsum= poslauf;
      for (integer zlauf= 0; zlauf < iterationen; zlauf++)
        {
        if (zsum%zsum >= 4)
          {
          apfelbmp.putpixel (xlauf, ylauf, farbe[zlauf%255], farbe[zlauf%255 + 256], farbe[zlauf%255 + 512]);
          break;
          }
        zsum= zsum*zsum + julia;
        }
      }
//*/

  // Stoppuhr stoppen
  clock_t stopticks;
  stopticks= times (NULL);

  // Stopzeit ausgeben
  clock_t apfelticks= stopticks - startticks;
  real apfelzeit= real (apfelticks)/ticksps;
  real bogomips= 1000/apfelzeit;
  printf ("%10ld  %10ld   %10ld Ticks\n", startticks, stopticks, apfelticks);
  printf ("Berechnungszeit:          %14.4Lf Sekunden\n", apfelzeit);
  printf ("Rechenleistung:           %14.4Lf Bogomips\n", bogomips);
  printf ("\n");
  }

int main()
  {
  apfel ();
  return 0;
  }
