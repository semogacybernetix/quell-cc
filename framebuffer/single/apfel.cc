// Erzeugt eine Apfelmännchengrafik

#include "../../cc/screen/allscr.h"
#include "../../conio/vektorcon.h"

#include <cstdlib>          // random
#include <sys/times.h>      // times (NULL)
#include <unistd.h>         // sysconf, _SC_CLK_TCK

using namespace std;

void zufallsfarben (unsigned char*& pfarbe, integer& panz)
  {
  panz= 256;
  pfarbe= new unsigned char[panz*3];
  pfarbe[0]= 255;
  pfarbe[1]= 0;
  pfarbe[2]= 0;
  for (integer flauf= 1; flauf < panz; flauf++)
    {
    pfarbe[flauf*3]= integer (random () % 256);
    pfarbe[flauf*3 + 1]= integer (random () % 256);
    pfarbe[flauf*3 + 2]= integer (random () % 256);
    //printf ("%10lld  %10lld  %10lld\n", pfarbe[flauf*3], pfarbe[flauf*3 + 1], pfarbe[flauf*3 + 2]);
    }
  }

void monochrom (unsigned char*& pfarbe, integer& panz)
  {
  panz= 256;
  pfarbe= new unsigned char[panz*3];
  for (integer flauf= 0; flauf < panz; flauf++)
    {
    pfarbe[flauf*3]= flauf;
    pfarbe[flauf*3 + 1]= flauf;
    pfarbe[flauf*3 + 2]= flauf;
    //printf ("%10lld  %10lld  %10lld\n", pfarbe[flauf*3], pfarbe[flauf*3 + 1], pfarbe[flauf*3 + 2]);
    }
  }

void rgb (unsigned char*& pfarbe, integer& panz)
  {
  panz= 3;
  pfarbe= new unsigned char[panz*3];
  pfarbe[0]= 255;
  pfarbe[1]= 0;
  pfarbe[2]= 0;
  pfarbe[3]= 0;
  pfarbe[4]= 255;
  pfarbe[5]= 0;
  pfarbe[6]= 0;
  pfarbe[7]= 0;
  pfarbe[8]= 255;
  }

void spektrum256 (unsigned char*& pfarbe, integer& panz)
  {
  panz= 256;
  pfarbe= new unsigned char[panz*3];
  for (integer flauf= 0; flauf < 43; flauf++)
    {
    // rot -> gelb
    pfarbe[flauf*3]= 252;
    pfarbe[flauf*3 + 1]= flauf*6;
    pfarbe[flauf*3 + 2]= 0;
    }
  for (integer flauf= 43; flauf < 85; flauf++)
    {
    // gelb -> grün
    pfarbe[flauf*3]= 246 - (flauf - 43)*6;
    pfarbe[flauf*3 + 1]= 246;
    pfarbe[flauf*3 + 2]= 0;
    }
  for (integer flauf= 85; flauf < 127; flauf++)
    {
    // grün -> blaugrün
    pfarbe[flauf*3]= 0;
    pfarbe[flauf*3 + 1]= 246;
    pfarbe[flauf*3 + 2]= (flauf - 85)*6;
    }
  for (integer flauf= 127; flauf < 170; flauf++)
    {
    // blaugrün -> blau
    pfarbe[flauf*3]= 0;
    pfarbe[flauf*3 + 1]= 252 - (flauf - 127)*6;
    pfarbe[flauf*3 + 2]= 252;
    }
  for (integer flauf= 170; flauf < 213; flauf++)
    {
    // blau -> violett
    pfarbe[flauf*3]= (flauf - 170)*6;
    pfarbe[flauf*3 + 1]= 0;
    pfarbe[flauf*3 + 2]= 252;
    }
  for (integer flauf= 213; flauf < 256; flauf++)
    {
    // violett -> rot
    pfarbe[flauf*3]= 252;
    pfarbe[flauf*3 + 1]= 0;
    pfarbe[flauf*3 + 2]= 252 - (flauf - 213)*6;
    }
  }

void spektrum (unsigned char*& pfarbe, integer& panz, integer pbit)
  {
  integer basis= 1 << pbit;
  panz= basis*6;
  pfarbe= new unsigned char[panz*3];
  integer st= 1 << (8 - pbit);
  for (integer flauf= 0; flauf < basis; flauf++)
    {
    pfarbe[flauf*3]= 255;
    pfarbe[flauf*3 + 1]= flauf*st;
    pfarbe[flauf*3 + 2]= 0;

    pfarbe[(basis+flauf)*3]= 255 - flauf*st;
    pfarbe[(basis+flauf)*3 + 1]= 255;
    pfarbe[(basis+flauf)*3 + 2]= 0;

    pfarbe[(basis*2+flauf)*3]= 0;
    pfarbe[(basis*2+flauf)*3 + 1]= 255;
    pfarbe[(basis*2+flauf)*3 + 2]= flauf*st;

    pfarbe[(basis*3+flauf)*3]= 0;
    pfarbe[(basis*3+flauf)*3 + 1]= 255 - flauf*st;
    pfarbe[(basis*3+flauf)*3 + 2]= 255;

    pfarbe[(basis*4+flauf)*3]= flauf*st;
    pfarbe[(basis*4+flauf)*3 + 1]= 0;
    pfarbe[(basis*4+flauf)*3 + 2]= 255;

    pfarbe[(basis*5+flauf)*3]= 255;
    pfarbe[(basis*5+flauf)*3 + 1]= 0;
    pfarbe[(basis*5+flauf)*3 + 2]= 255 - flauf*st;
    }
  }

void palettetest (unsigned char* pfarbe, integer panz)
  {
  cfbscreen apfelscr ("apfel.bmp", 1920, 1080);
  printtext ("panz: ");
  printinteger (panz);
  for (integer xlauf= 0; xlauf < panz; xlauf++)
    {
    //printf ("%10lld  %10lld  %10lld\n", pfarbe[xlauf*3], pfarbe[xlauf*3 + 1], pfarbe[xlauf*3 + 2]);
    for (integer ylauf= 0; ylauf < 768; ylauf++)
      apfelscr.putpixel (xlauf, ylauf, pfarbe[xlauf*3], pfarbe[xlauf*3 + 1], pfarbe[xlauf*3 + 2]);
    for (integer ylauf= 768; ylauf < 788; ylauf++)
      apfelscr.putpixel (xlauf, ylauf, xlauf % 256, xlauf % 256, xlauf % 256);
    }
  }

void apfel ()
  {
  // Apfelmännchen Variablen anlegen
  //cmemscreen8 apfelscr ("apfel.bmp", 1920, 1080);
  //cbmpdatei apfelscr ("apfel.bmp", 1920, 1080);
  cfbscreen apfelscr ("apfel.bmp", 1920, 1080);
  //cxscreen apfelscr ("apfel.bmp", 1024, 512);
  integer xanz= apfelscr.xanz;
  integer yanz= apfelscr.yanz;
  ckomplexk bildmitte;
  real pixelgr;
  integer iterationen;
  integer fanz;                 // Anzahl Palettenfarben
  unsigned char* farbe;

/*
  // Standardapfelmännchen
  printtext ("Standardapfelmännchen\n");
  bildmitte= ckomplexk (0, 0);
  pixelgr= real (4)/real (yanz);
  zufallsfarben (farbe, fanz);
  iterationen= 256;
//*/

/*
  // Apfelmännchen schiefer Kopf       Float16 Grenzfall
  printtext ("Apfelmännchen schiefer Kopf\n");
  bildmitte= ckomplexk (real (0.4435), real (0.374));
  pixelgr= real (0.01)/real (yanz);
  zufallsfarben (farbe, fanz);
  iterationen= 1024;
//*/

/*
  // Spirale
  printtext ("Spirale\n");
  bildmitte= ckomplexk (real (-0.747162), real (0.087584));
  pixelgr= real (0.001)/real (yanz);
  zufallsfarben (farbe, fanz);
//  spektrum (farbe, fanz, 5);
  iterationen= 1024;
//*/

/*
  // Apfelmännchen                    Float32 Grenzfall
  printtext ("Apfelmännchen Singlegenauigkeit\n");
  bildmitte= ckomplexk (real (0.3514), real (0.3514));
  pixelgr= real (0.000001)/real (yanz);
  spektrum (farbe, fanz, 5);
//  spektrum256 (farbe, fanz);
  iterationen= 2048;
//*/

/*
  // Stern
  printtext ("Stern\n");
  bildmitte= ckomplexk (real (-1.26840686), real (0.124791718));
  pixelgr= real (0.0000003)/real (yanz);
//  spektrum (farbe, fanz, 4);
  spektrum256 (farbe, fanz);
  iterationen= 2048;
//*/

//*
  // prachtvolles Apfelmännchen
  printtext ("prachtvolles Apfelmännchen\n");
  bildmitte= ckomplexk (real (-1.26840686), real (0.124791718));
  pixelgr= real (0.00000003)/real (yanz);
//  spektrum (farbe, fanz, 5);
  spektrum256 (farbe, fanz);
  iterationen= 4096;
//*/

  // Genauigkeit von Realzahlen ausgeben
  printtext ("Realsize:                              ");
  printinteger (sizeof (real));
  printtext ("\n");

  // Genauigkeit der Stoppuhr ausgeben
  signed long ticksps= sysconf (_SC_CLK_TCK);
  printtext ("Genauigkeit der Stopuhr:             ");
  printinteger (ticksps);
  printtext ("  Ticks pro Sekunde\n");

//  printtext ("Stoppuhr Start\n");
  // Stoppuhr starten
  clock_t startticks;
  startticks= times (NULL);

  // Apfelmännchenberechnung beginnen
  ckomplexk bilddiag= pixelgr/2 * ckomplexk (xanz - 1, yanz - 1);
  ckomplexk bildecke= bildmitte - bilddiag;
  ckomplexk poslauf;
//  palettetest (farbe, fanz);
//  exit (0);
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
          apfelscr.putpixel (xlauf, ylauf, farbe[(zanz%fanz)*3], farbe[(zanz%fanz)*3 + 1], farbe[(zanz%fanz)*3 + 2]);
          break;
          }
          else
          {
          apfelscr.putpixel (xlauf, ylauf, 0, 0, 0);
          }
        //zlauf= (zlauf^2.1) + poslauf;
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
  printinteger (startticks);
  printtext ("  ");
  printinteger (stopticks);
  printtext ("              ");
  printinteger (apfelticks);
  printtext ("  Ticks\n");
  printtext ("Berechnungszeit:            ");
  printreal (apfelzeit);
  printtext ("  Sekunden\n");
  printtext ("Rechenleistung:            ");
  printreal (bogomips);
  printtext ("  Bogomips\n");
  printtext ("\n");

  // Bild abspeichern
  //cbmpdatei apfeldatei ("/root/apfel2.bmp", 1920, 1080);
  //cfbscreen apfeldatei ("", 0, 0);
  //apfelscr.putscreen (apfeldatei);
  }

int main()
  {
  apfel ();
  return 0;
  }

