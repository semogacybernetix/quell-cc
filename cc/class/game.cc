#include "game.h"
#include "gruppe.h"                        // Besuchsliste der Kugel beim Spiel
#include "../../conio/vektorcon.h"         // printtext, printreal

#include <iostream>                        // cout, printf, scanf
#include <unistd.h>                        // usleep
#include <sys/times.h>                     // tms, times
#include <thread>

using namespace std;                       // cout

tms flugsimuzeit;

//--------------------------------- Thread -------------------------------------------------

signed long rektiefe;         // globale Variable für threadrekursiv (lässt sich nicht lokal definieren, weil sie threadübergreifend sein muss und nicht pro Instanz)
cflugsimu* flugsimuthread;

void arbeit (signed long pthreadnr)
  {
  flugsimuthread->welttoscreenthread (pthreadnr);
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

//---------------------------------------------------- cflugsimu ----------------------------------------------------------

cflugsimu::cflugsimu (cwelt* pwelt, clkeyboard* plkeyboard, clscreen8* plscreen)
  : welt (pwelt), keyboard (plkeyboard), screen (plscreen),
    xoff (real ((1 - screen->xanz))/2), yoff (real ((1 - screen->yanz))/2),
    bewstep (1), drehstep (50)

  {
  pixelanz= screen->xanz*screen->yanz;
  pixelpos= 0;
  flugsimuthread= this;
  threadanz= 1;
  setframedauer (100);      // Framedauer auf 100 ms setzen
  framepos= real (times (&flugsimuzeit));

  // pixelarray erzeugen
  srand48 (56);
  pixels= new cpixel[pixelanz];

  for (integer n= 0; n < pixelanz; n++)
    {
    pixels[n].x= n % screen->xanz;
    pixels[n].y= n / screen->xanz;
    }
  for (integer n2= 0; n2 < pixelanz; n2++)
    {
    integer z= random () % pixelanz;
    cpixel s= pixels[n2];
    pixels[n2]= pixels[z];
    pixels[z]= s;
    }
  }

void cflugsimu::setframedauer (real pfr)          // (Dauer eines Frames in Millisekunden) setzen
  {
  tickms= 1000/real (sysconf (_SC_CLK_TCK));
  framems= pfr;
  frametk= framems/tickms;
  }

void cflugsimu::welttoscreenl ()               // linearer Pixeldurchgang
  {
  for (integer ypp= 0; ypp < screen->yanz; ++ypp)
    for (integer xpp= 0; xpp < screen->xanz; ++xpp)
      {
      cvektor3 fb= welt->getpunkt (cvektor2 (real (xpp) + xoff, real (ypp) + yoff));
      integer r= integer (fb.x);
      integer g= integer (fb.y);
      integer b= integer (fb.z);
      screen->putpixel (xpp, ypp, r, g, b);
      }
  }

void cflugsimu::welttoscreenz ()              // zufallsreihenfolgiger Pixeldurchgang
  {
  integer nanz= screen->xanz*screen->yanz;
  integer xpp, ypp;
  cvektor3 fb;

  for (integer n= 0; n < nanz; n++)
    {
    xpp= pixels[n].x;
    ypp= pixels[n].y;
    fb= welt->getpunkt (cvektor2 (real (xpp) + xoff, real (ypp) + yoff));
    integer r= integer (fb.x);
    integer g= integer (fb.y);
    integer b= integer (fb.z);
    screen->putpixel (xpp, ypp, r, g, b);
    }
  }

void cflugsimu::welttoscreentakt (integer& renderanz)           // zufallsreihenfolgiger Pixeldurchgang
  {
  integer xpp, ypp;
  cvektor3 fb;
  renderanz= 0;

  for (integer n= 0; n < pixelanz; n++)
    {
    if (real (times (&flugsimuzeit)) - framepos > frametk)
      break;
    xpp= pixels[pixelpos].x;
    ypp= pixels[pixelpos].y;
    fb= welt->getpunkt (cvektor2 (real (xpp) + xoff, real (ypp) + yoff));
    integer r= integer (fb.x);
    integer g= integer (fb.y);
    integer b= integer (fb.z);
    screen->putpixel (xpp, ypp, r, g, b);
    pixelpos= (pixelpos + 1) % pixelanz;
    renderanz++;
    }

  screen->flush ();
  while (real (times (&flugsimuzeit)) - framepos < frametk);
  framepos= framepos + frametk;                           // Zeitposition für den Beginn des nächsten Frames berechnen
  }

void cflugsimu::welttoscreenthread (integer pthreadnr)
  {
//  printf ("Threadnr    %lld\n", pthreadnr);
  integer nanz= screen->xanz*screen->yanz;
  integer panz= nanz/threadanz;
  integer ug= (pthreadnr - 1)*panz;
  integer og= ug + panz;
  integer xpp, ypp;
  cvektor3 fb;
  for (integer n= ug; n < og; n++)
    {
//    xpp= pixels[n].x;
//    ypp= pixels[n].y;
    xpp= n % screen->xanz;
    ypp= n/screen->xanz;
    fb= welt->getpunkt (cvektor2 (real (xpp) + xoff, real (ypp) + yoff));
    integer r= integer (fb.x);
    integer g= integer (fb.y);
    integer b= integer (fb.z);
  //  printf ("putpixel   thread: %lld  xpp: %lld  ypp: %lld\n", pthreadnr, xpp, ypp);
    screen->putpixel (xpp, ypp, r, g, b);
    }
  }

// Tastenbelegung

void cflugsimu::fliegethread ()                     // Multithreadfliegen
  {
  cvektor3 flugw (0, 0, 0);
  cvektor4 drehaw;
  cbasis3 achsbasis;

  tms zeit;
  real ticksps= real (sysconf (_SC_CLK_TCK));
  clock_t zeitpos= times (&zeit);
  printtext ("ticks/sek: ");
  printreal (ticksps);
  printtext ("\n");

  integer koerper= 0;
  integer framezeit;
  keyboard->putkey (19, 5, 1);
    do
    {
    if (keyboard->getkey (19, 5))
      {
      rektiefe= threadanz;
//      printf ("vor arbeit %ld\n", rektiefe);
      threadrekursiv (0);
      screen->flush ();
      //welttoscreenz ();
      framezeit= (times (&zeit) - zeitpos)*10;
      //cout << "Zeit: " << framezeit << "  fps: " << 1/framezeit << endl;
//      printf ("Zeit: %5.2Lf  fps: %5.2Lf\n", framezeit, 1/framezeit);
      printinteger (framezeit);
      printtext (" ms    ");
      printinteger (1000/framezeit);
      printtext (" fps\n");
      flugw= eulerwinkelfrommatrix (welt->augbasis);
      flugw= 180/PI*flugw;
      drehaw= winkelachsefrommatrix (welt->augbasis);

      //nwinkel= 180/PI*drehaw.r;
      // Zeile löschen \r
      //printf ("Eulerwinkel: %15.9Lf %15.9Lf %15.9Lf          drehaw: %12.9Lf %12.9Lf %12.9Lf          Drehwinkel:%12.4Lf\n", flugw.x, flugw.y, flugw.z, drehaw.i, drehaw.j, drehaw.ij, nwinkel);
      //printf ("                          augdrehaw: %12.9Lf %12.9Lf %12.9Lf          Drehwinkel:%12.4Lf\n", welt->augdrehaw.i, welt->augdrehaw.j, welt->augdrehaw.ij, welt->augdrehaw.r/PI*180);
      //drehmatrixausgabe (welt->augbasis);

      fflush (stdout);
      zeitpos= times (&zeit);
      }
      else
        usleep (50000);

    keyboard->flush ();
    if (koerper == 0)
      {
      // Bewegungen
      if (keyboard->getkey (2, 2)) welt->verschiebeauge (cvektor3 (0, 0, bewstep));
      if (keyboard->getkey (2, 3)) welt->verschiebeauge (cvektor3 (0, 0, -bewstep));
      if (keyboard->getkey (3, 2)) welt->verschiebeauge (cvektor3 (bewstep, 0, 0));
      if (keyboard->getkey (3, 3)) welt->verschiebeauge (cvektor3 (-bewstep, 0, 0));
      if (keyboard->getkey (4, 2)) welt->verschiebeauge (cvektor3 (0, bewstep, 0));
      if (keyboard->getkey (4, 3)) welt->verschiebeauge (cvektor3 (0, -bewstep, 0));

      // Bewegungszoomfaktor ändern
      if (keyboard->getkey (5, 2)) bewstep*= real (1.4142);
      if (keyboard->getkey (5, 3)) bewstep/= real (1.4142);

      // Drehzoomquotient ändern
      if (keyboard->getkey (7, 2)) drehstep*= real (1.4142);
      if (keyboard->getkey (7, 3)) drehstep/= real (1.4142);

      // Drehungen
      if (keyboard->getkey (8, 2))
        {
        welt->dreheaugex (drehstep);
        welt->augdrehaw=winkelachsefrommatrix (welt->augbasis);
        }
      if (keyboard->getkey (8, 3))
        {
        welt->dreheaugex (-drehstep);
        welt->augdrehaw=winkelachsefrommatrix (welt->augbasis);
        }
      if (keyboard->getkey (9, 2))
        {
        welt->dreheaugey (-drehstep);
        welt->augdrehaw=winkelachsefrommatrix (welt->augbasis);
        }
      if (keyboard->getkey (9, 3))
        {
        welt->dreheaugey (drehstep);
        welt->augdrehaw=winkelachsefrommatrix (welt->augbasis);
        }
      if (keyboard->getkey (10, 2))
        {
        welt->dreheaugez (drehstep);
        welt->augdrehaw=winkelachsefrommatrix (welt->augbasis);
        }
      if (keyboard->getkey (10, 3))
        {
        welt->dreheaugez (-drehstep);
        welt->augdrehaw=winkelachsefrommatrix (welt->augbasis);
        }
      if (keyboard->getkey (7, 1)) welt->dreheaugenorm (drehstep);
      if (keyboard->getkey (8, 1)) welt->dreheaugeein (drehstep);
      if (keyboard->getkey (9, 1)) welt->dreheaugeachse (-drehstep);
      if (keyboard->getkey (10, 1)) welt->dreheaugeachse (drehstep);
      }

      if (keyboard->getkey (1, 1))
        {
        koerper= 0;
        usleep (250000);
        }
    }
  while (!keyboard->getkey (0, 0));
  }

void cflugsimu::fliege ()                              // ohne Körper drehen zu können
  {
  cvektor3 flugw (0, 0, 0);
  cvektor4 drehaw;
  cbasis3 achsbasis;

  tms zeit;
  real ticksps= real (sysconf (_SC_CLK_TCK));
  clock_t ticks= times (&zeit);
  printtext ("ticks/sek: ");
  printreal (ticksps);
  printtext ("\n");

  integer koerper= 0;
  integer framezeit;
  keyboard->putkey (19, 5, 1);
    do
    {
    if (keyboard->getkey (19, 5))
      {
      welttoscreenz ();
      //welttoscreentakt ();
      screen->flush ();
      framezeit= (times (&zeit) - ticks)*10;
      //cout << "Zeit: " << framezeit << "  fps: " << 1/framezeit << endl;
//      printf ("Zeit: %5.2Lf  fps: %5.2Lf\n", framezeit, 1/framezeit);
      printtext ("Frame: ");
      printinteger (framezeit);
      printtext (" ms  fps: ");
      printreal (1000/real (framezeit));
      printtext ("\n");
      flugw= eulerwinkelfrommatrix (welt->augbasis);
      flugw= 180/PI*flugw;
      drehaw= winkelachsefrommatrix (welt->augbasis);

      //nwinkel= 180/PI*drehaw.r;
      // Zeile löschen \r
      //printf ("Eulerwinkel: %15.9Lf %15.9Lf %15.9Lf          drehaw: %12.9Lf %12.9Lf %12.9Lf          Drehwinkel:%12.4Lf\n", flugw.x, flugw.y, flugw.z, drehaw.i, drehaw.j, drehaw.ij, nwinkel);
      //printf ("                          augdrehaw: %12.9Lf %12.9Lf %12.9Lf          Drehwinkel:%12.4Lf\n", welt->augdrehaw.i, welt->augdrehaw.j, welt->augdrehaw.ij, welt->augdrehaw.r/PI*180);
      //drehmatrixausgabe (welt->augbasis);

      fflush (stdout);
      ticks= times (&zeit);
      }
      else
        usleep (50000);

    keyboard->flush ();
    if (koerper == 0)
      {
      // Bewegungen
      if (keyboard->getkey (2, 2)) welt->verschiebeauge (cvektor3 (0, 0, bewstep));
      if (keyboard->getkey (2, 3)) welt->verschiebeauge (cvektor3 (0, 0, -bewstep));
      if (keyboard->getkey (3, 2)) welt->verschiebeauge (cvektor3 (bewstep, 0, 0));
      if (keyboard->getkey (3, 3)) welt->verschiebeauge (cvektor3 (-bewstep, 0, 0));
      if (keyboard->getkey (4, 2)) welt->verschiebeauge (cvektor3 (0, bewstep, 0));
      if (keyboard->getkey (4, 3)) welt->verschiebeauge (cvektor3 (0, -bewstep, 0));

      // Bewegungszoomfaktor ändern
      if (keyboard->getkey (5, 2)) bewstep*= real (1.4142);
      if (keyboard->getkey (5, 3)) bewstep/= real (1.4142);

      // Drehzoomquotient ändern
      if (keyboard->getkey (7, 2)) drehstep*= real (1.4142);
      if (keyboard->getkey (7, 3)) drehstep/= real (1.4142);

      // Drehungen
      if (keyboard->getkey (8, 2))
        {
        welt->dreheaugex (drehstep);
        welt->augdrehaw=winkelachsefrommatrix (welt->augbasis);
        }
      if (keyboard->getkey (8, 3))
        {
        welt->dreheaugex (-drehstep);
        welt->augdrehaw=winkelachsefrommatrix (welt->augbasis);
        }
      if (keyboard->getkey (9, 2))
        {
        welt->dreheaugey (-drehstep);
        welt->augdrehaw=winkelachsefrommatrix (welt->augbasis);
        }
      if (keyboard->getkey (9, 3))
        {
        welt->dreheaugey (drehstep);
        welt->augdrehaw=winkelachsefrommatrix (welt->augbasis);
        }
      if (keyboard->getkey (10, 2))
        {
        welt->dreheaugez (drehstep);
        welt->augdrehaw=winkelachsefrommatrix (welt->augbasis);
        }
      if (keyboard->getkey (10, 3))
        {
        welt->dreheaugez (-drehstep);
        welt->augdrehaw=winkelachsefrommatrix (welt->augbasis);
        }
      if (keyboard->getkey (7, 1)) welt->dreheaugenorm (drehstep);
      if (keyboard->getkey (8, 1)) welt->dreheaugeein (drehstep);
      if (keyboard->getkey (9, 1)) welt->dreheaugeachse (-drehstep);
      if (keyboard->getkey (10, 1)) welt->dreheaugeachse (drehstep);
      }

      if (keyboard->getkey (1, 1))
        {
        koerper= 0; usleep (250000);
        }
    }
  while (!keyboard->getkey (0, 0));
  }

void cflugsimu::fliegek ()              // mit Körperdrehungen
  {
  cvektor3 flugw (0, 0, 0);
  cvektor4 drehaw;
  real nwinkel;
  //tms zeit;
  //real ticksps= real (sysconf (_SC_CLK_TCK));
  //clock_t ticks= times (&zeit);
  //cout << "ticks/sek: " << ticksps << endl;
  signed long koerper= 0;
  keyboard->putkey (19, 5, 1);
    do
    {
    if (keyboard->getkey (19, 5))  // wenn eine Taste gedrückt wird (egal welche)
      {
      welttoscreenz ();
      screen->flush ();
      //cout << "Zeit: " << (times (&zeit) - ticks)/ticksps << endl;
      flugw= eulerwinkelfrommatrix (welt->augbasis);
      nwinkel= 180/PI*acosr (cosr (flugw.x)*cosr(flugw.y));
      flugw= 180/PI*flugw;
      drehaw= winkelachsefrommatrix (welt->augbasis);
      drehaw.r*= 180/PI;
//      printf ("\r%15.9Lf %12.9Lf %12.9Lf W:%15.9Lf %12.9Lf %12.9Lf %12.9Lf w:%15.9Lf",
//              flugw.x, flugw.y, flugw.z, drehaw.r, drehaw.i, drehaw.j, drehaw.ij, nwinkel);
      nwinkel+= 0;
      fflush (stdout);
      //ticks= times (&zeit);
      }
      else usleep (50000);
    keyboard->flush ();
    if (koerper == 0)
      {
      if (keyboard->getkey (2, 2)) welt->verschiebeauge (cvektor3 (0, 0, bewstep));
      if (keyboard->getkey (2, 3)) welt->verschiebeauge (cvektor3 (0, 0, -bewstep));
      if (keyboard->getkey (3, 2)) welt->verschiebeauge (cvektor3 (bewstep, 0, 0));
      if (keyboard->getkey (3, 3)) welt->verschiebeauge (cvektor3 (-bewstep, 0, 0));
      if (keyboard->getkey (4, 2)) welt->verschiebeauge (cvektor3 (0, bewstep, 0));
      if (keyboard->getkey (4, 3)) welt->verschiebeauge (cvektor3 (0, -bewstep, 0));
      if (keyboard->getkey (8, 2)) welt->dreheaugex (drehstep);
      if (keyboard->getkey (8, 3)) welt->dreheaugex (-drehstep);
      if (keyboard->getkey (9, 2)) welt->dreheaugey (-drehstep);
      if (keyboard->getkey (9, 3)) welt->dreheaugey (drehstep);
      if (keyboard->getkey (10, 2)) welt->dreheaugez (drehstep);
      if (keyboard->getkey (10, 3)) welt->dreheaugez (-drehstep);
      if (keyboard->getkey (8, 1)) welt->dreheaugeein (drehstep);
      if (keyboard->getkey (7, 1)) welt->dreheaugenorm (-drehstep);
      }
    if (koerper == 1)
      {
      printtext ("k0 drehstep ");
      printreal (drehstep);
      printtext ("\n");
      if (keyboard->getkey (2, 2)) welt->koerperliste.koerper[0]->verschiebe (cvektor3 (0, 0, bewstep));
      if (keyboard->getkey (2, 3)) welt->koerperliste.koerper[0]->verschiebe (cvektor3 (0, 0, -bewstep));
      if (keyboard->getkey (3, 2)) welt->verschiebeauge (cvektor3 (bewstep, 0, 0));
      if (keyboard->getkey (3, 3)) welt->verschiebeauge (cvektor3 (-bewstep, 0, 0));
      if (keyboard->getkey (4, 2)) welt->verschiebeauge (cvektor3 (0, bewstep, 0));
      if (keyboard->getkey (4, 3)) welt->verschiebeauge (cvektor3 (0, -bewstep, 0));
      if (keyboard->getkey (8, 2)) welt->koerperliste.koerper[0]->drehe (getrotx (drehstep));
      if (keyboard->getkey (8, 3)) welt->koerperliste.koerper[0]->drehe (getrotx (-drehstep));
      if (keyboard->getkey (9, 2)) welt->koerperliste.koerper[0]->drehe (getroty (drehstep));
      if (keyboard->getkey (9, 3)) welt->koerperliste.koerper[0]->drehe (getroty (-drehstep));
      if (keyboard->getkey (10, 2)) welt->koerperliste.koerper[0]->drehe (getrotz (drehstep));
      if (keyboard->getkey (10, 3)) welt->koerperliste.koerper[0]->drehe (getrotz (-drehstep));
      if (keyboard->getkey (8, 1)) welt->koerperliste.koerper[0]->dreheein ();
      }
    if (koerper == 2)
      {
      printtext ("k1 drehstep ");
      printreal (drehstep);
      printtext ("\n");
      if (keyboard->getkey (2, 2)) welt->koerperliste.koerper[1]->verschiebe (cvektor3 (0, 0, bewstep));
      if (keyboard->getkey (2, 3)) welt->koerperliste.koerper[1]->verschiebe (cvektor3 (0, 0, -bewstep));
      if (keyboard->getkey (3, 2)) welt->verschiebeauge (cvektor3 (bewstep, 0, 0));
      if (keyboard->getkey (3, 3)) welt->verschiebeauge (cvektor3 (-bewstep, 0, 0));
      if (keyboard->getkey (4, 2)) welt->verschiebeauge (cvektor3 (0, bewstep, 0));
      if (keyboard->getkey (4, 3)) welt->verschiebeauge (cvektor3 (0, -bewstep, 0));
      if (keyboard->getkey (8, 2)) welt->koerperliste.koerper[1]->drehe (getrotx (drehstep));
      if (keyboard->getkey (8, 3)) welt->koerperliste.koerper[1]->drehe (getrotx (-drehstep));
      if (keyboard->getkey (9, 2)) welt->koerperliste.koerper[1]->drehe (getroty (drehstep));
      if (keyboard->getkey (9, 3)) welt->koerperliste.koerper[1]->drehe (getroty (-drehstep));
      if (keyboard->getkey (10, 2)) welt->koerperliste.koerper[1]->drehe (getrotz (drehstep));
      if (keyboard->getkey (10, 3)) welt->koerperliste.koerper[1]->drehe (getrotz (-drehstep));
      if (keyboard->getkey (8, 1)) welt->koerperliste.koerper[1]->dreheein ();
      }
    if (koerper == 3)
      {
      printtext ("k2 drehstep ");
      printreal (drehstep);
      printtext ("\n");
      if (keyboard->getkey (2, 2)) welt->koerperliste.koerper[2]->verschiebe (cvektor3 (0, 0, bewstep));
      if (keyboard->getkey (2, 3)) welt->koerperliste.koerper[2]->verschiebe (cvektor3 (0, 0, -bewstep));
      if (keyboard->getkey (3, 2)) welt->verschiebeauge (cvektor3 (bewstep, 0, 0));
      if (keyboard->getkey (3, 3)) welt->verschiebeauge (cvektor3 (-bewstep, 0, 0));
      if (keyboard->getkey (4, 2)) welt->verschiebeauge (cvektor3 (0, bewstep, 0));
      if (keyboard->getkey (4, 3)) welt->verschiebeauge (cvektor3 (0, -bewstep, 0));
      if (keyboard->getkey (8, 2)) welt->koerperliste.koerper[2]->drehe (getrotx (drehstep));
      if (keyboard->getkey (8, 3)) welt->koerperliste.koerper[2]->drehe (getrotx (-drehstep));
      if (keyboard->getkey (9, 2)) welt->koerperliste.koerper[2]->drehe (getroty (drehstep));
      if (keyboard->getkey (9, 3)) welt->koerperliste.koerper[2]->drehe (getroty (-drehstep));
      if (keyboard->getkey (10, 2)) welt->koerperliste.koerper[2]->drehe (getrotz (drehstep));
      if (keyboard->getkey (10, 3)) welt->koerperliste.koerper[2]->drehe (getrotz (-drehstep));
      if (keyboard->getkey (8, 1)) welt->koerperliste.koerper[2]->dreheein ();
      }

      // Bewegungszoomfaktor ändern
      if (keyboard->getkey (5, 2)) bewstep*= real (1.4142);
      if (keyboard->getkey (5, 3)) bewstep/= real (1.4142);

      // Drehzoomquotient ändern
      if (keyboard->getkey (7, 2)) drehstep*= real (1.4142);
      if (keyboard->getkey (7, 3)) drehstep/= real (1.4142);


    if (keyboard->getkey (5, 2))
      {
      bewstep*= real (1.4142);
      usleep (250000);
      }
    if (keyboard->getkey (5, 3))
      {
      bewstep/= real (1.4142);
      usleep (250000);
      }
    if (keyboard->getkey (7, 3))
      {
      if (drehstep > 2) drehstep/= real (1.4142);
      usleep (250000);
      }
    if (keyboard->getkey (7, 2))
      {
      if (drehstep < 256)
        drehstep*= real (1.4142);
      usleep (250000);
      }

    // Körper auswählen
    if (keyboard->getkey (0, 1)) {koerper= 0; usleep (250000);}
    if (keyboard->getkey (1, 1)) {koerper= 1; usleep (250000);}
    if (keyboard->getkey (2, 1)) {koerper= 2; usleep (250000);}
    if (keyboard->getkey (3, 1)) {koerper= 3; usleep (250000);}
    }
  while (!keyboard->getkey (0, 0));
  }

void cflugsimu::fliegetakt ()
  {
  cvektor3 flugw (0, 0, 0);
  cvektor4 drehaw;
  cbasis3 achsbasis;

  tms zeit;
  clock_t zeitpos= times (&zeit);
  integer framedauer, renderanz;
  integer frameanz= 0;
  integer pixelsum= 0;

  integer koerper= 0;
  keyboard->putkey (19, 5, 1);
    do
    {
    if (1)
      {
      //welt->aktualisiere ();
      welttoscreentakt (renderanz);
      screen->flush ();
      pixelsum= pixelsum + renderanz;
      frameanz++;
      framedauer= (times (&zeit) - zeitpos)*integer (tickms);
//      cout << "Zeit: " << framezeit << "  fps: " << 1/framezeit << endl;
      printinteger (framedauer);
      printtext (" ms    ");
      printinteger (1000/framedauer);
      printtext (" fps    ");
      printinteger (renderanz);
      printtext (" Pixel    ");                                // Die Anzahl der Pixel, die während der Framedauer geschafft wurden zu berechnen
      printreal (real (pixelsum)/real (frameanz));
      printtext (" Pixel    ");                                  // durchschnittliche Anzahl der Pixel pro Frame
      printinteger (frameanz);
      printtext ("\n");                                  // durchschnittliche Anzahl der Pixel pro Frame
      //printf ("Zeit: %5.2Lf  fps: %5.2Lf\n", framezeit, 1/framezeit);
      //zeitpos= real (times (&zeit));
      flugw= eulerwinkelfrommatrix (welt->augbasis);
      flugw= 180/PI*flugw;
      drehaw= winkelachsefrommatrix (welt->augbasis);

      //nwinkel= 180/PI*drehaw.r;
      // Zeile löschen \r
      //printf ("Eulerwinkel: %15.9Lf %15.9Lf %15.9Lf          drehaw: %12.9Lf %12.9Lf %12.9Lf          Drehwinkel:%12.4Lf\n", flugw.x, flugw.y, flugw.z, drehaw.i, drehaw.j, drehaw.ij, nwinkel);
      //printf ("                          augdrehaw: %12.9Lf %12.9Lf %12.9Lf          Drehwinkel:%12.4Lf\n", welt->augdrehaw.i, welt->augdrehaw.j, welt->augdrehaw.ij, welt->augdrehaw.r/PI*180);
      //drehmatrixausgabe (welt->augbasis);

      fflush (stdout);
      zeitpos= times (&zeit);
      }
      else
        usleep (0);

    keyboard->flush ();
    if (koerper == 0)
      {
      // Bewegungen
      if (keyboard->getkey (2, 2)) welt->verschiebeauge (cvektor3 (0, 0, bewstep));
      if (keyboard->getkey (2, 3)) welt->verschiebeauge (cvektor3 (0, 0, -bewstep));
      if (keyboard->getkey (3, 2)) welt->verschiebeauge (cvektor3 (bewstep, 0, 0));
      if (keyboard->getkey (3, 3)) welt->verschiebeauge (cvektor3 (-bewstep, 0, 0));
      if (keyboard->getkey (4, 2)) welt->verschiebeauge (cvektor3 (0, bewstep, 0));
      if (keyboard->getkey (4, 3)) welt->verschiebeauge (cvektor3 (0, -bewstep, 0));

      // Bewegungszoomfaktor ändern
      if (keyboard->getkey (5, 2)) bewstep*= real (1.4142);
      if (keyboard->getkey (5, 3)) bewstep/= real (1.4142);

      // Drehzoomquotient ändern
      if (keyboard->getkey (7, 2)) drehstep*= real (1.4142);
      if (keyboard->getkey (7, 3)) drehstep/= real (1.4142);

      // Drehungen
      if (keyboard->getkey (8, 2))
        {
        welt->dreheaugex (drehstep);
        welt->augdrehaw=winkelachsefrommatrix (welt->augbasis);
        }
      if (keyboard->getkey (8, 3))
        {
        welt->dreheaugex (-drehstep);
        welt->augdrehaw=winkelachsefrommatrix (welt->augbasis);
        }
      if (keyboard->getkey (9, 2))
        {
        welt->dreheaugey (-drehstep);
        welt->augdrehaw=winkelachsefrommatrix (welt->augbasis);
        }
      if (keyboard->getkey (9, 3))
        {
        welt->dreheaugey (drehstep);
        welt->augdrehaw=winkelachsefrommatrix (welt->augbasis);
        }
      if (keyboard->getkey (10, 2))
        {
        welt->dreheaugez (drehstep);
        welt->augdrehaw=winkelachsefrommatrix (welt->augbasis);
        }
      if (keyboard->getkey (10, 3))
        {
        welt->dreheaugez (-drehstep);
        welt->augdrehaw=winkelachsefrommatrix (welt->augbasis);
        }

      if (keyboard->getkey (7, 1)) welt->dreheaugenorm (drehstep);
      if (keyboard->getkey (8, 1)) welt->dreheaugeein (drehstep);
      if (keyboard->getkey (9, 1)) welt->dreheaugeachse (-drehstep);
      if (keyboard->getkey (10, 1)) welt->dreheaugeachse (drehstep);
      }

      if (keyboard->getkey (1, 1))
        {
        koerper= 0;
        usleep (0);
        }
    }
  while (!keyboard->getkey (0, 0));
  }

void cflugsimu::fliegespiel (cbasis3& spiegelebenen, ckoerper* bewkugel)
  {
  cvektor3 flugw (0, 0, 0);
  cvektor4 drehaw;
  cbasis3 achsbasis;

  // Bewegungskugel initialisieren
  cvektor3 bewkugelpos;
  integer zeitpos;
  cbasis3 spiegbasis1, spiegbasis2, spiegbasis3;
  spiegbasis1= getspiegbasis (spiegelebenen.x);
  spiegbasis2= getspiegbasis (spiegelebenen.y);
  spiegbasis3= getspiegbasis (spiegelebenen.z);

  tms zeit;
  real ticksps= real (sysconf (_SC_CLK_TCK));
  clock_t ticks= times (&zeit);
  printtext ("ticks/sek: ");
  printreal (ticksps);
  printtext ("\n");
  integer koerper= 0;
  real framezeit;
  keyboard->putkey (19, 5, 1);
    do
    {
    if (1)
      {
      welt->aktualisiere ();
      welttoscreenz ();
      screen->flush ();
      framezeit= real (times (&zeit) - ticks)/ticksps;
      zeitpos= times (&zeit);
      //cout << "Zeit: " << framezeit << "  fps: " << 1/framezeit << endl;
//      printf ("Zeit: %5.2Lf  fps: %5.2Lf\n", framezeit, 1/framezeit);
      printtext ("Zeit: ");
      printreal (framezeit);
      printtext ("  fps: ");
      printreal (1/framezeit);
      printtext ("\n");
      flugw= eulerwinkelfrommatrix (welt->augbasis);
      flugw= 180/PI*flugw;
      drehaw= winkelachsefrommatrix (welt->augbasis);

      //nwinkel= 180/PI*drehaw.r;
      // Zeile löschen \r
      //printf ("Eulerwinkel: %15.9Lf %15.9Lf %15.9Lf          drehaw: %12.9Lf %12.9Lf %12.9Lf          Drehwinkel:%12.4Lf\n", flugw.x, flugw.y, flugw.z, drehaw.i, drehaw.j, drehaw.ij, nwinkel);
      //printf ("                          augdrehaw: %12.9Lf %12.9Lf %12.9Lf          Drehwinkel:%12.4Lf\n", welt->augdrehaw.i, welt->augdrehaw.j, welt->augdrehaw.ij, welt->augdrehaw.r/PI*180);
      //drehmatrixausgabe (welt->augbasis);

      fflush (stdout);
      ticks= times (&zeit);
      }
      else
        usleep (50000);

    keyboard->flush ();
    if (koerper == 0)
      {
      // Bewegungen
      if (keyboard->getkey (2, 2)) welt->verschiebeauge (cvektor3 (0, 0, bewstep));
      if (keyboard->getkey (2, 3)) welt->verschiebeauge (cvektor3 (0, 0, -bewstep));
      if (keyboard->getkey (3, 2)) welt->verschiebeauge (cvektor3 (bewstep/3, 0, 0));
      if (keyboard->getkey (3, 3)) welt->verschiebeauge (cvektor3 (-bewstep/3, 0, 0));
      if (keyboard->getkey (4, 2)) welt->verschiebeauge (cvektor3 (0, bewstep/3, 0));
      if (keyboard->getkey (4, 3)) welt->verschiebeauge (cvektor3 (0, -bewstep/3, 0));

      // Bewegungszoomfaktor ändern
      if (keyboard->getkey (1, 2)) bewstep*= real (2.5);
      if (keyboard->getkey (1, 3)) bewstep/= real (2.5);

      // Drehzoomquotient ändern
      if (keyboard->getkey (11, 2)) drehstep/= 2;
      if (keyboard->getkey (11, 3)) drehstep*= 2;

      // Drehungen
      if (keyboard->getkey (8, 2))
        {
        welt->dreheaugex (PI/drehstep/real (1.5));
        welt->augdrehaw=winkelachsefrommatrix (welt->augbasis);
        }
      if (keyboard->getkey (8, 3))
        {
        welt->dreheaugex (-PI/drehstep/real (1.5));
        welt->augdrehaw=winkelachsefrommatrix (welt->augbasis);
        }
      if (keyboard->getkey (9, 2))
        {
        welt->dreheaugey (-PI/drehstep);
        welt->augdrehaw=winkelachsefrommatrix (welt->augbasis);
        }
      if (keyboard->getkey (9, 3))
        {
        welt->dreheaugey (PI/drehstep/real (0.7));
        welt->augdrehaw=winkelachsefrommatrix (welt->augbasis);
        }
      if (keyboard->getkey (10, 2))
        {
        welt->dreheaugez (PI/drehstep/real (0.7));
        welt->augdrehaw=winkelachsefrommatrix (welt->augbasis);
        }
      if (keyboard->getkey (10, 3))
        {
        welt->dreheaugez (-PI/drehstep);
        welt->augdrehaw=winkelachsefrommatrix (welt->augbasis);
        }

      // an den Spiegelebenen spiegeln
      if (keyboard->getkey (1, 1))
        {
        bewkugelpos= bewkugel->stoppos;
        bewkugel->startpos= bewkugelpos;
        bewkugelpos= spiegbasis1*bewkugelpos;
        bewkugel->stoppos= bewkugelpos;
        bewkugel->startzeit= real (zeitpos);
        bewkugel->stopzeit= bewkugel->startzeit + 500;
        }
      if (keyboard->getkey (2, 1))
        {
        bewkugelpos= bewkugel->stoppos;
        bewkugel->startpos= bewkugelpos;
        bewkugelpos= spiegbasis2*bewkugelpos;
        bewkugel->stoppos= bewkugelpos;
        bewkugel->startzeit= real (zeitpos);
        bewkugel->stopzeit= bewkugel->startzeit + 500;
        }
      if (keyboard->getkey (3, 1))
        {
        bewkugelpos= bewkugel->stoppos;
        bewkugel->startpos= bewkugelpos;
        bewkugelpos= spiegbasis3*bewkugelpos;
        bewkugel->stoppos= bewkugelpos;
        bewkugel->startzeit= real (zeitpos);
        bewkugel->stopzeit= bewkugel->startzeit + 500;
        }

      /*
      if (keyboard->getkey (2, 1)) welt->dreheaugenorm (PI/drehstep);
      if (keyboard->getkey (3, 1)) welt->dreheaugenorm (PI/drehstep);
      */

      if (keyboard->getkey (7, 1)) welt->dreheaugenorm (PI/drehstep);
      if (keyboard->getkey (8, 1)) welt->dreheaugeein (PI/drehstep);
      if (keyboard->getkey (9, 1)) welt->dreheaugeachse (-PI/drehstep);
      if (keyboard->getkey (10, 1)) welt->dreheaugeachse (PI/drehstep);
      }

      if (keyboard->getkey (1, 1))
        {
        koerper= 0;
        usleep (250000);
        }

    }
  while (!keyboard->getkey (0, 0));
  }

void cflugsimu::fliegespieltakt (cbasis3& spiegelebenen, ckoerper* bewkugel)
  {
  cvektor3 flugw (0, 0, 0);
  cvektor4 drehaw;
  cbasis3 achsbasis;

  // Bewegungskugel initialisieren
  cvektor3 bewkugelpos;
  cvektor3liste besuchsliste (1000);
  real zeitpos;
  cbasis3 spiegbasis1, spiegbasis2, spiegbasis3;
  spiegbasis1= getspiegbasis (spiegelebenen.x);
  spiegbasis2= getspiegbasis (spiegelebenen.y);
  spiegbasis3= getspiegbasis (spiegelebenen.z);

  // Bewegungskugel
  real kzoom= 100;
  cschachfeld* textur1= new cschachfeld (cvektor3 (0,255,0), cvektor3 (255,0,0), PI/6, PI/6);
  ckoerper* beskugel= new ckoerper (new cskugel, new cparawkugel, new cbegrkeine, textur1, nullv3, real (0.1)*kzoom*einsb3);

  integer renderanz;
  tms zeit;
  real ticksps= real (sysconf (_SC_CLK_TCK));
  clock_t ticks= times (&zeit);
  //cout << "ticks/sek: " << ticksps << endl;

  integer koerper= 0;
  real framezeit;
  keyboard->putkey (19, 5, 1);
    do
    {
    if (1)
      {
      welt->aktualisiere ();
      welttoscreentakt (renderanz);
      screen->flush ();
      framezeit= real (times (&zeit) - ticks)/ticksps;
//      cout << "Zeit: " << framezeit << "  fps: " << 1/framezeit << endl;
      printtext ("Zeit: ");
      printreal (framezeit);
      printtext ("  fps: ");
      printreal (1/framezeit);
      //printf ("Zeit: %5.2Lf  fps: %5.2Lf\n", framezeit, 1/framezeit);
      zeitpos= real (times (&zeit));
      flugw= eulerwinkelfrommatrix (welt->augbasis);
      flugw= 180/PI*flugw;
      drehaw= winkelachsefrommatrix (welt->augbasis);

      //nwinkel= 180/PI*drehaw.r;
      // Zeile löschen \r
      //printf ("Eulerwinkel: %15.9Lf %15.9Lf %15.9Lf          drehaw: %12.9Lf %12.9Lf %12.9Lf          Drehwinkel:%12.4Lf\n", flugw.x, flugw.y, flugw.z, drehaw.i, drehaw.j, drehaw.ij, nwinkel);
      //printf ("                          augdrehaw: %12.9Lf %12.9Lf %12.9Lf          Drehwinkel:%12.4Lf\n", welt->augdrehaw.i, welt->augdrehaw.j, welt->augdrehaw.ij, welt->augdrehaw.r/PI*180);
      //drehmatrixausgabe (welt->augbasis);

      fflush (stdout);
      ticks= times (&zeit);
      }
      else
        usleep (0);

    keyboard->flush ();
    if (koerper == 0)
      {
      // Bewegungen
      if (keyboard->getkey (2, 2)) welt->verschiebeauge (cvektor3 (0, 0, bewstep));
      if (keyboard->getkey (2, 3)) welt->verschiebeauge (cvektor3 (0, 0, -bewstep));
      if (keyboard->getkey (3, 2)) welt->verschiebeauge (cvektor3 (bewstep, 0, 0));
      if (keyboard->getkey (3, 3)) welt->verschiebeauge (cvektor3 (-bewstep, 0, 0));
      if (keyboard->getkey (4, 2)) welt->verschiebeauge (cvektor3 (0, bewstep, 0));
      if (keyboard->getkey (4, 3)) welt->verschiebeauge (cvektor3 (0, -bewstep, 0));

      // Bewegungszoomfaktor ändern
      if (keyboard->getkey (5, 2)) bewstep*= real (1.4142);
      if (keyboard->getkey (5, 3)) bewstep/= real (1.4142);

      // Drehzoomquotient ändern
      if (keyboard->getkey (7, 2)) drehstep*= real (1.4142);
      if (keyboard->getkey (7, 3)) drehstep/= real (1.4142);

      // Drehungen
      if (keyboard->getkey (8, 2))
        {
        welt->dreheaugex (drehstep);
        welt->augdrehaw=winkelachsefrommatrix (welt->augbasis);
        }
      if (keyboard->getkey (8, 3))
        {
        welt->dreheaugex (-drehstep);
        welt->augdrehaw=winkelachsefrommatrix (welt->augbasis);
        }
      if (keyboard->getkey (9, 2))
        {
        welt->dreheaugey (-drehstep);
        welt->augdrehaw=winkelachsefrommatrix (welt->augbasis);
        }
      if (keyboard->getkey (9, 3))
        {
        welt->dreheaugey (drehstep);
        welt->augdrehaw=winkelachsefrommatrix (welt->augbasis);
        }
      if (keyboard->getkey (10, 2))
        {
        welt->dreheaugez (drehstep);
        welt->augdrehaw=winkelachsefrommatrix (welt->augbasis);
        }
      if (keyboard->getkey (10, 3))
        {
        welt->dreheaugez (-drehstep);
        welt->augdrehaw=winkelachsefrommatrix (welt->augbasis);
        }

      // an Spiegelebene 1 spiegeln
      if (keyboard->getkey (1, 1))
        {
        if (zeitpos > bewkugel->stopzeit)
          {
          bewkugelpos= bewkugel->stoppos;
          if (besuchsliste.elposition (bewkugelpos) < 0)
            {
            // Besuchskugel erzeugen
            beskugel= new ckoerper (new cskugel, new cparawkugel, new cbegrkeine, textur1, bewkugel->startpos, real (0.08)*kzoom*einsb3);
            beskugel->startpos= bewkugelpos;
            beskugel->stoppos= spiegbasis1*bewkugelpos;
            beskugel->startzeit= zeitpos;
            beskugel->stopzeit= beskugel->startzeit + 500;
            welt->addkoerper (beskugel);
            }
          besuchsliste.elementhinzu (bewkugelpos, 0);
          bewkugel->startpos= bewkugelpos;
          bewkugelpos= spiegbasis1*bewkugelpos;
          bewkugel->stoppos= bewkugelpos;
          bewkugel->startzeit= zeitpos;
          bewkugel->stopzeit= bewkugel->startzeit + 500;
          }
        }

      // an Spiegelebene 2 spiegeln
      if (keyboard->getkey (2, 1))
        {
        if (zeitpos > bewkugel->stopzeit)
          {
          bewkugelpos= bewkugel->stoppos;
          if (besuchsliste.elposition (bewkugelpos) < 0)
            {
            // Besuchskugel erzeugen
            beskugel= new ckoerper (new cskugel, new cparawkugel, new cbegrkeine, textur1, bewkugel->startpos, real (0.08)*kzoom*einsb3);
            beskugel->startpos= bewkugelpos;
            beskugel->stoppos= spiegbasis2*bewkugelpos;
            beskugel->startzeit= zeitpos;
            beskugel->stopzeit= beskugel->startzeit + 500;
            welt->addkoerper (beskugel);
            }
          besuchsliste.elementhinzu (bewkugelpos, 0);
          bewkugel->startpos= bewkugelpos;
          bewkugelpos= spiegbasis2*bewkugelpos;
          bewkugel->stoppos= bewkugelpos;
          bewkugel->startzeit= zeitpos;
          bewkugel->stopzeit= bewkugel->startzeit + 500;
          }
        }

      // an Spiegelebene 3 spiegeln
      if (keyboard->getkey (3, 1))
        {
        if (zeitpos > bewkugel->stopzeit)
          {
          bewkugelpos= bewkugel->stoppos;
          if (besuchsliste.elposition (bewkugelpos) < 0)
            {
            // Besuchskugel erzeugen
            beskugel= new ckoerper (new cskugel, new cparawkugel, new cbegrkeine, textur1, bewkugel->startpos, real (0.08)*kzoom*einsb3);
            beskugel->startpos= bewkugelpos;
            beskugel->stoppos= spiegbasis3*bewkugelpos;
            beskugel->startzeit= zeitpos;
            beskugel->stopzeit= beskugel->startzeit + 500;
            welt->addkoerper (beskugel);
            }
          besuchsliste.elementhinzu (bewkugelpos, 0);
          bewkugel->startpos= bewkugelpos;
          bewkugelpos= spiegbasis3*bewkugelpos;
          bewkugel->stoppos= bewkugelpos;
          bewkugel->startzeit= zeitpos;
          bewkugel->stopzeit= bewkugel->startzeit + 500;
          }
        }

      if (keyboard->getkey (7, 1)) welt->dreheaugenorm (drehstep);
      if (keyboard->getkey (8, 1)) welt->dreheaugeein (drehstep);
      if (keyboard->getkey (9, 1)) welt->dreheaugeachse (-drehstep);
      if (keyboard->getkey (10, 1)) welt->dreheaugeachse (drehstep);
      }

      if (keyboard->getkey (1, 1))
        {
        koerper= 0;
        usleep (0);
        }
    }
  while (!keyboard->getkey (0, 0));
  }

