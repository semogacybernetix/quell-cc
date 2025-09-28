// Erzeugt eine Apfelmännchengrafik
// Version 0.0 2018.09.09
// Version 0.1 2025.08.04

#include "../class/vektor.h"
#include "../screen/allscr.h"

#include <iostream>         // printf, random
#include <sys/times.h>      // times (NULL)
#include <unistd.h>         // sysconf, _SC_CLK_TCK

using namespace std;

void monochrom  (integer* pfarbe)
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

void apfel ()
  {
  // Genauigkeit der Stoppuhr ausgeben
  signed long ticksps= sysconf (_SC_CLK_TCK);
  printf ("\n");
  printf ("Genauigkeit der Stopuhr: %10ld Ticks pro Sekunde\n", ticksps);

  // Apfelmännchen Variablen anlegen
  cbmpdatei apfelbmp ("/root/cpubenchmark.bmp", 1920, 1080);
//  cmemscreen apfelbmp ("mandelbrot.bmp", 1920, 1080);        // Bildausgabe Bmp-Bild im RAM
//  cfbscreen apfelbmp ("/root/cpubenchmark.bmp", 1920, 1080);
  integer xanz= apfelbmp.xanz;
  integer yanz= apfelbmp.yanz;
  ckomplexk bildmitte;
  real pixelgr;
  integer iterationen;
  integer farbe [768];           // Farbtabelle definieren

/*
  // Standardapfelmännchen
  bildmitte= ckomplexk (0, 0);
  pixelgr= 4.0/real (yanz);
  iterationen= 1*256 - 1;
  zufallsfarben (farbe);
//*/

/*
  // Apfelmännchen schiefer Kopf
  bildmitte= ckomplexk (0.4435, 0.374);
  pixelgr= 0.01/real (yanz);
  iterationen= 4*256 - 1;
  zufallsfarben (farbe);
//*/

/*
  // Spirale
  bildmitte= ckomplexk (-0.747162, 0.087584);
  pixelgr= 0.001/real (yanz);
  iterationen= 4*256 - 1;
  zufallsfarben (farbe);
//*/

//*
  // Stern
  bildmitte= ckomplexk (-1.26840686, 0.124791718);
  pixelgr= 0.0000003/real (yanz);
  iterationen= 8*256 - 1;
  spektrum (farbe);
//*/

/*
  // prachtvolles Apfelmännchen
  bildmitte= ckomplexk (-1.26840686, 0.124791718);
  pixelgr= 0.00000003/real (yanz);
  iterationen= 16*256 - 1;
  spektrum (farbe);
//*/

  printf ("Stoppuhr Start\n\n");
  // Stoppuhr starten
  clock_t startticks;
  startticks= times (NULL);

  // Apfelmännchenberechnung beginnen
  ckomplexk bilddiag= pixelgr/2 * ckomplexk (xanz - 1, yanz - 1);
  ckomplexk bildecke= bildmitte - bilddiag; 
  ckomplexk poslauf;
  for (integer ylauf= 0; ylauf < yanz; ylauf++)
    for (integer xlauf= 0; xlauf < xanz; xlauf++)
      {
      poslauf.x= bildecke.x + pixelgr*xlauf;
      poslauf.y= bildecke.y + pixelgr*ylauf;
      ckomplexk zlauf= poslauf;
      integer zanz= 0;
      while (zanz < iterationen)
        {
        if (zlauf%zlauf >= 4)
          {
          apfelbmp.putpixel (xlauf, ylauf, farbe[zanz%255], farbe[zanz%255 + 256], farbe[zanz%255 + 512]);
          break;
          }
          else
          {
          apfelbmp.putpixel (xlauf, ylauf, farbe[255], farbe[255 + 256], farbe[255 + 512]);
          }
        zlauf= zlauf*zlauf + poslauf;
        zanz++;
        }
      }

  // Stoppuhr stoppen
  clock_t stopticks;
  stopticks= times (NULL);

  // Stopzeit ausgeben
  clock_t apfelticks= stopticks - startticks;
  real apfelzeit= real (apfelticks)/ticksps;
  real bogomips= 10000/apfelzeit;
  printf ("%10ld  %10ld   %10ld Ticks\n", startticks, stopticks, apfelticks);
  printf ("Berechnungszeit:          %14.4Lf Sekunden\n", apfelzeit);
  printf ("Rechenleistung:           %14.4Lf Bogomips\n", bogomips);
  printf ("\n");

  // Bild abspeichern
//  cmemscreen apfelbmp ("mandelbrot.bmp", 1920, 1080);        // Bildausgabe Bmp-Bild im RAM
//    cbmpdatei apfeldatei ("/root/cpubenchmark.bmp", 1920, 1080);
//    apfeldatei.getscreen (apfelbmp, apfelbmp.xanz, apfelbmp.yanz);
  }

int main()
  {
  apfel ();
  return 0;
  }
