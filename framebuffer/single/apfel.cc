// Erzeugt eine Apfelmännchengrafik

#include "../../cc/screen/allscr.h"
#include "../../conio/vektorcon.h"

#include <cstdlib>          // random
#include <sys/times.h>      // times (NULL)
#include <unistd.h>         // sysconf, _SC_CLK_TCK
#include <iostream>         // cout
#include <thread>           // hardware_concurrency ()
#include <mutex>            // mutex

using namespace std;

//--------------------------------- Apfelklasse Deklaration -------------------------------------------------
struct capfel
  {
  clscreen8*        screen;

  integer           threadanz;              // Anzahl der Threads (von außen setzbar)

  integer           xanz= screen->xanz;
  integer           yanz= screen->yanz;
  ckomplexk         bildmitte;
  real              pixelgr;
  integer           iterationen;
  integer           akpixel;
  mutex             mutexpixel;

  integer fanz;                 // Anzahl Palettenfarben
  unsigned char* farbe;

  capfel (clscreen8* pscreen);
  ~capfel ();

  void zufallsfarben (unsigned char*& pfarbe, integer& panz);
  void monochrom (unsigned char*& pfarbe, integer& panz);
  void rgb (unsigned char*& pfarbe, integer& panz);
  void spektrum256 (unsigned char*& pfarbe, integer& panz);
  void spektrum (unsigned char*& pfarbe, integer& panz, integer pbit);
  void palettetest (unsigned char* pfarbe, integer panz);

  void berechnethreadblock (integer pthreadnr);                              // segmentierter linearer Pixeldurchgang
  void berechnethreadkamm (integer pthreadnr);                               // verzahnter Pixeldurchgang
  void berechnethreadmutex (integer pthreadnr);                              // mit Mutex
  void berechne ();
  };

//--------------------------------- Thread -------------------------------------------------

signed long rektiefe;         // globale Variable für threadrekursiv (lässt sich nicht lokal definieren, weil sie threadübergreifend sein muss und nicht pro Instanz)
capfel* apfelthread;          // Zeiger auf das erzeugte Objekt um global zugreifbar zu sein

void arbeit (signed long pthreadnr)
  {
  //apfelthread->berechnethreadblock (pthreadnr);
  //apfelthread->berechnethreadkamm (pthreadnr);
  apfelthread->berechnethreadmutex (pthreadnr);
  }

void* threadrekursiv (void*)
  {
  signed long lokaltiefe= rektiefe;   // rektiefe kopieren, da sie jederzeit von einer anderen Instanz von threadrekursiv geändert werden kann

                                      // Für den Fall, dass threadrekursiv von außen mit weniger als einem Thread aufgerufen wird
  if (lokaltiefe < 1)
    return 0;

  pthread_t threadid;                 // id des erzeugten Threads
  signed long threadreturnwert;       // Rückgabe ob Threaderzeugung funktioniert hat

  if (lokaltiefe > 1)                 // neuen Aufruf von threadrekursiv erzeugen falls Tiefe mindestens 2 ist
    {
    rektiefe--;
    threadreturnwert= pthread_create (&threadid, NULL, threadrekursiv, NULL);
    if (threadreturnwert != 0)
      {
      //printf ("threadrekursiv-%ld:----Aufruf threadrekursiv mit Tiefe  %3ld fehlgeschlagen\n", lokaltiefe, lokaltiefe - 1);
      }
    }

  arbeit (lokaltiefe);               // Arbeitsfunktion aufrufen

  if (lokaltiefe > 1)                // auf Beendigung von neuem Aufruf warten
    pthread_join (threadid, NULL);

  return 0;
  }

//--------------------------------- Thread-Ende -------------------------------------------------------------------------------------

//--------------------------------- Apfelklasse Definition -------------------------------------------------

capfel::capfel (clscreen8* plscreen)
  : screen (plscreen)
  {
  threadanz= 1;
  apfelthread= this;
  };

capfel::~capfel ()
  {
  }

//------------------------------------------------------------  Paletten -------------------------------------------------------------

void capfel::zufallsfarben (unsigned char*& pfarbe, integer& panz)
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

void capfel::monochrom (unsigned char*& pfarbe, integer& panz)
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

void capfel::rgb (unsigned char*& pfarbe, integer& panz)
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

void capfel::spektrum256 (unsigned char*& pfarbe, integer& panz)
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

void capfel::spektrum (unsigned char*& pfarbe, integer& panz, integer pbit)
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

void capfel::palettetest (unsigned char* pfarbe, integer panz)
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

// ----------------------------------------------- Apfelmännchenberechnung ------------------------------------------------------------------------------

void capfel::berechnethreadblock (integer pthreadnr)                              // Pixelblock pro Thread
  {
  //printf ("Threadnr    %lld\n", pthreadnr);
  ckomplexk bilddiag= pixelgr/2 * ckomplexk (xanz - 1, yanz - 1);
  ckomplexk bildecke= bildmitte - bilddiag;
  ckomplexk poslauf;
  integer nanz= screen->xanz*screen->yanz;
  integer panz= nanz/threadanz;
  integer ug= (pthreadnr - 1)*panz;
  integer og= ug + panz;
  integer xpp, ypp;
  cvektor3 fb;

  for (integer n= ug; n < og; n++)
    {
    //xpp= pixels[n].x;
    //ypp= pixels[n].y;
    xpp= n % screen->xanz;
    ypp= n/screen->xanz;

    poslauf.x= bildecke.x + pixelgr*xpp;
    poslauf.y= bildecke.y + pixelgr*ypp;
    ckomplexk zlauf= poslauf;
    integer zanz= 0;
    while (zanz < iterationen)
      {
      if (zlauf%zlauf >= 4)
        {
        screen->putpixel (xpp, ypp, farbe[(zanz%fanz)*3], farbe[(zanz%fanz)*3 + 1], farbe[(zanz%fanz)*3 + 2]);
        break;
        }
        else
        {
        screen->putpixel (xpp, ypp, 0, 0, 0);
        }
      //zlauf= (zlauf^2.1) + poslauf;
      zlauf= zlauf*zlauf + poslauf;
      zanz++;
      }
    }
  //printf ("putpixel   thread: %lld  xpp: %lld  ypp: %lld\n", pthreadnr, xpp, ypp);
  }

void capfel::berechnethreadkamm (integer pthreadnr)                              // verzahnter Pixeldurchgang
  {
  //printf ("Threadnr    %lld\n", pthreadnr);
  ckomplexk bilddiag= pixelgr/2 * ckomplexk (xanz - 1, yanz - 1);
  ckomplexk bildecke= bildmitte - bilddiag;
  ckomplexk poslauf;
  integer nanz= screen->xanz*screen->yanz;
  integer xpp, ypp;
  cvektor3 fb;

  for (integer n= pthreadnr-1; n < nanz; n+= threadanz)
    {
    //xpp= pixels[n].x;
    //ypp= pixels[n].y;
    xpp= n % screen->xanz;
    ypp= n/screen->xanz;

    poslauf.x= bildecke.x + pixelgr*xpp;
    poslauf.y= bildecke.y + pixelgr*ypp;
    ckomplexk zlauf= poslauf;
    integer zanz= 0;
    while (zanz < iterationen)
      {
      if (zlauf%zlauf >= 4)
        {
        screen->putpixel (xpp, ypp, farbe[(zanz%fanz)*3], farbe[(zanz%fanz)*3 + 1], farbe[(zanz%fanz)*3 + 2]);
        break;
        }
        else
        {
        screen->putpixel (xpp, ypp, 0, 0, 0);
        }
      //zlauf= (zlauf^2.1) + poslauf;
      zlauf= zlauf*zlauf + poslauf;
      zanz++;
      }
    }
  //printf ("putpixel   thread: %lld  xpp: %lld  ypp: %lld\n", pthreadnr, xpp, ypp);
  }

void capfel::berechnethreadmutex (integer pthreadnr)                              // mit Mutex
  {
  //printf ("Threadnr    %lld\n", pthreadnr);
  pthreadnr= pthreadnr + 1;                                                       // pthreadnr benutzen
  ckomplexk bilddiag= pixelgr/2 * ckomplexk (xanz - 1, yanz - 1);
  ckomplexk bildecke= bildmitte - bilddiag;
  ckomplexk poslauf;
  integer nanz= screen->xanz*screen->yanz;
  integer xpp, ypp;
  cvektor3 fb;
  integer lauf;

  while (akpixel < nanz)
    {
    unique_lock<mutex> m1 (mutexpixel);
    lauf= akpixel;
    akpixel++;
    m1.unlock ();
    //xpp= pixels[lauf].x;
    //ypp= pixels[lauf].y;
    xpp= lauf % screen->xanz;
    ypp= lauf/screen->xanz;

    poslauf.x= bildecke.x + pixelgr*xpp;
    poslauf.y= bildecke.y + pixelgr*ypp;
    ckomplexk zlauf= poslauf;
    integer zanz= 0;
    while (zanz < iterationen)
      {
      if (zlauf%zlauf >= 4)
        {
        screen->putpixel (xpp, ypp, farbe[(zanz%fanz)*3], farbe[(zanz%fanz)*3 + 1], farbe[(zanz%fanz)*3 + 2]);
        break;
        }
        else
        {
        screen->putpixel (xpp, ypp, 0, 0, 0);
        }
      //zlauf= (zlauf^2.1) + poslauf;
      zlauf= zlauf*zlauf + poslauf;
      zanz++;
      }
    }
  //printf ("putpixel   thread: %lld  xpp: %lld  ypp: %lld\n", pthreadnr, xpp, ypp);
  }

void capfel::berechne ()
  {
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

/*
  // prachtvolles Apfelmännchen
  printtext ("prachtvolles Apfelmännchen\n");
  bildmitte= ckomplexk (real (-1.26840686), real (0.124791718));
  pixelgr= real (0.00000003)/real (yanz);
//  spektrum (farbe, fanz, 5);
  spektrum256 (farbe, fanz);
  iterationen= 4096;
//*/

//*
  // Benchmark, CPU-Auslastung
  printtext ("Benchmark\n");
  bildmitte= ckomplexk (real (0.2787531301468137), real (-0.0105268499341));
  pixelgr= 1e-16;
//  spektrum (farbe, fanz, 5);
  spektrum256 (farbe, fanz);
  iterationen= 1000000;
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

// threadige Apfelmännchenberechnung
  akpixel= 0;                               // aktuellen Pixel auf 0 setzen
  rektiefe= threadanz;
  //printf ("vor arbeit %ld\n", rektiefe);
  threadrekursiv (0);

  // Stoppuhr stoppen
  clock_t stopticks;
  stopticks= times (NULL);

  // Stopzeit ausgeben
  clock_t apfelticks= stopticks - startticks;
  real apfelzeit= real (apfelticks)/ticksps;
  real bogomips= 10000/apfelzeit;
  printtext ("                                                ");
  printinteger (apfelticks);
  printtext ("  Ticks\n");
  printtext ("Berechnungszeit:");
  printreal (apfelzeit);
  printtext ("  Sekunden\n");
  printtext ("Rechenleistung: ");
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
  //capfel apfel (new cmemscreen8 ("apfel.bmp", 1920, 1080));
  //capfel apfel (new cbmpdatei ("apfel.bmp", 1920, 1080));
  //capfel apfel (new cxscreen ("apfel.bmp", 1024, 512));
  capfel apfel (new cfbscreen ("apfel.bmp", 1920, 1080));

  apfel.threadanz= thread::hardware_concurrency ();
  //apfel.threadanz= 3;
  cout << "\nThreads:                               " << apfel.threadanz << endl;
  apfel.berechne ();
  return 0;
  }
