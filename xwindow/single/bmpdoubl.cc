// Dieses Programm verdoppelt die Aufloesung eines Bildes und interpoliert die Zwischenwerte

#include "../../cc/screen/allscr.h"
#include "../screen/xscr.h"
#include "../keyboard/xkbd.h"

#include <stdio.h>
#include <iostream>

using namespace std;

long double volzelle (long double a0, long double ax, long double ay, long double a1, long double xu, long double xo, long double yu, long double yo)
  {
  long double f0= a0*(xo-xu)*(yo-yu);
  long double f1= 0.5*((ax-a0)*(yo-yu)*(xo*xo-xu*xu)+(ay-a0)*(xo-xu)*(yo*yo-yu*yu));
  long double f2= 0.25*(a0+a1-ax-ay)*(xo*xo-xu*xu)*(yo*yo-yu*yu);
  return f0 + f1 + f2;
  }

// Verdopplung des Pixels durch vierfache Kopie

void doubleshit (clscreen& pquell, clscreen& pziel)
  {
  long double fr, fg, fb;
  for (signed long ylauf= 0; ylauf < pquell.yanz; ylauf++)
    for (signed long xlauf= 0; xlauf < pquell.xanz; xlauf++)
      {
      pquell.getpixel (xlauf, ylauf, fr, fg, fb);
      pziel.putpixel (xlauf*2, ylauf*2, fr, fg, fb);
      pziel.putpixel (xlauf*2 + 1, ylauf*2, fr, fg, fb);
      pziel.putpixel (xlauf*2, ylauf*2 + 1, fr, fg, fb);
      pziel.putpixel (xlauf*2 + 1, ylauf*2 + 1, fr, fg, fb);
      }
  }
  
// Verdopplung des Pixels durch lineare Approximation

void doublepic (clscreen& pquell, clscreen& pziel)
  {
  for (signed long ylauf= 0; ylauf < pquell.yanz; ylauf++)
    for (signed long xlauf= 0; xlauf < pquell.xanz; xlauf++)
      {
      long double fr0, fg0, fb0;
      long double frx, fgx, fbx;
      long double fry, fgy, fby;
      long double fr1, fg1, fb1;
      long double frout, fgout, fbout;
      signed long x00, y00, x01, y01, x10, y10, x11, y11;
      signed long xmin, ymin, xplu, yplu;
      long double zpixr, zpixg, zpixb;
      xmin= xlauf - 1;
      if (xmin < 0) xmin= 0;
      ymin= ylauf - 1;
      if (ymin < 0) ymin= 0;
      xplu= xlauf + 1;
      if (xplu >= pquell.xanz) xplu= xlauf;
      yplu= ylauf + 1;
      if (yplu >= pquell.yanz) yplu= ylauf;
//--------- das ist der linke untere Pixel ---------------
      x00= xmin;
      y00= ymin;
      x01= xlauf;
      y01= ymin;
      x10= xmin;
      y10= ylauf;
      x11= xlauf;
      y11= ylauf;
      pquell.getpixel (x00, y00, fr0, fg0, fb0);
      pquell.getpixel (x01, y01, frx, fgx, fbx);
      pquell.getpixel (x10, y10, fry, fgy, fby);
      pquell.getpixel (x11, y11, fr1, fg1, fb1);
      zpixr= volzelle (fr0, frx, fry, fr1, 0.5, 1, 0.5, 1);
      zpixg= volzelle (fg0, fgx, fgy, fg1, 0.5, 1, 0.5, 1);
      zpixb= volzelle (fb0, fbx, fby, fb1, 0.5, 1, 0.5, 1);
      frout= zpixr*4 + 0.5;
      fgout= zpixg*4 + 0.5;
      fbout= zpixb*4 + 0.5;
      pziel.putpixel (xlauf*2, ylauf*2, frout, fgout, fbout);
//--------- das ist der rechte untere Pixel ---------------
      x00= xlauf;
      y00= ymin;
      x01= xplu;
      y01= ymin;
      x10= xlauf;
      y10= ylauf;
      x11= xplu;
      y11= ylauf;
      pquell.getpixel (x00, y00, fr0, fg0, fb0);
      pquell.getpixel (x01, y01, frx, fgx, fbx);
      pquell.getpixel (x10, y10, fry, fgy, fby);
      pquell.getpixel (x11, y11, fr1, fg1, fb1);
      zpixr= volzelle (fr0, frx, fry, fr1, 0, 0.5, 0.5, 1);
      zpixg= volzelle (fg0, fgx, fgy, fg1, 0, 0.5, 0.5, 1);
      zpixb= volzelle (fb0, fbx, fby, fb1, 0, 0.5, 0.5, 1);
      frout= zpixr*4 + 0.5;
      fgout= zpixg*4 + 0.5;
      fbout= zpixb*4 + 0.5;
      pziel.putpixel (xlauf*2 + 1, ylauf*2, frout, fgout, fbout);
//--------- das ist der linke obere Pixel ---------------
      x00= xmin;
      y00= ylauf;
      x01= xlauf;
      y01= ylauf;
      x10= xmin;
      y10= yplu;
      x11= xlauf;
      y11= yplu;
      pquell.getpixel (x00, y00, fr0, fg0, fb0);
      pquell.getpixel (x01, y01, frx, fgx, fbx);
      pquell.getpixel (x10, y10, fry, fgy, fby);
      pquell.getpixel (x11, y11, fr1, fg1, fb1);
      zpixr= volzelle (fr0, frx, fry, fr1, 0.5, 1, 0, 0.5);
      zpixg= volzelle (fg0, fgx, fgy, fg1, 0.5, 1, 0, 0.5);
      zpixb= volzelle (fb0, fbx, fby, fb1, 0.5, 1, 0, 0.5);
      frout= zpixr*4 + 0.5;
      fgout= zpixg*4 + 0.5;
      fbout= zpixb*4 + 0.5;
      pziel.putpixel (xlauf*2, ylauf*2 + 1, frout, fgout, fbout);
//--------- das ist der rechte obere Pixel ---------------
      x00= xlauf;
      y00= ylauf;
      x01= xplu;
      y01= ylauf;
      x10= xlauf;
      y10= yplu;
      x11= xplu;
      y11= yplu;
      pquell.getpixel (x00, y00, fr0, fg0, fb0);
      pquell.getpixel (x01, y01, frx, fgx, fbx);
      pquell.getpixel (x10, y10, fry, fgy, fby);
      pquell.getpixel (x11, y11, fr1, fg1, fb1);
      zpixr= volzelle (fr0, frx, fry, fr1, 0, 0.5, 0, 0.5);
      zpixg= volzelle (fg0, fgx, fgy, fg1, 0, 0.5, 0, 0.5);
      zpixb= volzelle (fb0, fbx, fby, fb1, 0, 0.5, 0, 0.5);
      frout= zpixr*4 + 0.5;
      fgout= zpixg*4 + 0.5;
      fbout= zpixb*4 + 0.5;
      pziel.putpixel (xlauf*2 + 1, ylauf*2 + 1, frout, fgout, fbout);
      }  
  }

void showbmpdatei (char* p_name, char* pname2)
  {
  // BMP-Datei anzeigen
  cbmpdatei bilddatei (p_name);
  cxscreen bildschirm ("Originalbild", bilddatei.xanz, bilddatei.yanz);
  bildschirm.putscreen (bilddatei, 0, 0);
  bildschirm.flush ();
  
// BMP-Datei linear verdoppeln
  cbmpdatei doppelbild (pname2, bilddatei.xanz*2, bilddatei.yanz*2);
  doublepic (bilddatei, doppelbild);
  doppelbild.flush ();

  //BMP-Doppelbild konstant anzeigen
  cxscreen doppelschirm ("Konstante Verdoppelung", bilddatei.xanz*2, bilddatei.yanz*2);
  doubleshit (bilddatei, doppelschirm);
  doppelschirm.flush ();

  //BMP-Doppelbild linear anzeigen
  cxscreen doppelschirm2 ("Lineare Verdoppelung", bilddatei.xanz*2, bilddatei.yanz*2);
  doppelschirm2.putscreen (doppelbild, 0, 0);
  doppelschirm2.flush ();

  getchar ();
  }

void showjpgdatei (char* p_name, char* pname2)
  {
  // JPG-Datei anzeigen
  cjpegdatei bilddatei (p_name);
  cxscreen bildschirm ("Originalbild", bilddatei.xanz, bilddatei.yanz);
  bildschirm.putscreen (bilddatei, 0, 0);
  bildschirm.flush ();
  
// JPG-Datei linear verdoppeln
  cbmpdatei doppelbild (pname2, bilddatei.xanz*2, bilddatei.yanz*2);
  doublepic (bilddatei, doppelbild);
  doppelbild.flush ();

  //BMP-Doppelbild konstant anzeigen
  cxscreen doppelschirm ("Konstante Verdoppelung", bilddatei.xanz*2, bilddatei.yanz*2);
  doubleshit (bilddatei, doppelschirm);
  doppelschirm.flush ();

  //BMP-Doppelbild linear anzeigen
  cxscreen doppelschirm2 ("Lineare Verdoppelung", bilddatei.xanz*2, bilddatei.yanz*2);
  doppelschirm2.putscreen (doppelbild, 0, 0);
  doppelschirm2.flush ();

  getchar ();
  }

void transform (char* p_quelle, char* p_ziel)
  {
  cjpegdatei quelldatei (p_quelle);
  cbmpdatei zieldatei (p_ziel, quelldatei.xanz*2, quelldatei.yanz*2);
  doublepic (quelldatei, zieldatei);
  }
  
int main (int argc, char** argv)
  {
  if (argc != 3)
    {
    printf ("jpgdoubl <JPG-Datei> <zu erzeugende BMP-Datei>\n");
    return 0;
    }
  showbmpdatei (argv[1], argv[2]);
  return 0;
  }
