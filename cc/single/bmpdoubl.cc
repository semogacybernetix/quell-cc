/*
Bildverdopplung mit anschließender Glättung

*/

#include "../../cc/screen/allscr.h"

#include <cstdio>
#include <iostream>

void doublgewichtung (clscreen& pquell, clscreen& pziel)
  {
  /*
  // Glättung mit glatter Diagonallinie (0.5 0.1847 0.1306)
  double gewor= 0.5;
  double gewhv= 0.5/(2 + sqrt (0.5));
  double gewdi= sqrt (0.125)/(2 + sqrt (0.5));
  */
  // beste Glättung nach intuitiven Beobachten (bester Kompromiss zwischen Rasterung und Unschärfe) (0.6 0.2 0.0)
  double gewor= 0.6;
  double gewhv= 0.2;
  double gewdi= 0.0;
  double pix1r, pix1g, pix1b = 0;
  double pix2r, pix2g, pix2b = 0;
  double pix3r, pix3g, pix3b = 0;
  double pix4r, pix4g, pix4b = 0;
  double pixpr, pixpg, pixpb = 0;
  for (signed long ylauf= 0; ylauf < pquell.yanz; ylauf++)
    for (signed long xlauf= 0; xlauf < pquell.xanz; xlauf++)
      {
      pquell.getpixel (xlauf, ylauf, pix1r, pix1g, pix1b);
      // erster Pixel
      if ((ylauf > 0) && (xlauf > 0))
        {
        pquell.getpixel (xlauf - 1, ylauf,     pix2r, pix2g, pix2b);
        pquell.getpixel (xlauf,     ylauf - 1, pix3r, pix3g, pix3b);
        pquell.getpixel (xlauf - 1, ylauf - 1, pix4r, pix4g, pix4b);
        pixpr= gewor*pix1r + gewhv*pix2r + gewhv*pix3r + gewdi*pix4r;
        pixpg= gewor*pix1g + gewhv*pix2g + gewhv*pix3g + gewdi*pix4g;
        pixpb= gewor*pix1b + gewhv*pix2b + gewhv*pix3b + gewdi*pix4b;
        pziel.putpixel (xlauf*2, ylauf*2, pixpr, pixpg, pixpb);
        }
      // zweiter Pixel
      if ((ylauf > 0) && (xlauf < pquell.xanz - 1))
        {
        pquell.getpixel (xlauf    , ylauf - 1, pix2r, pix2g, pix2b);
        pquell.getpixel (xlauf + 1, ylauf    , pix3r, pix3g, pix3b);
        pquell.getpixel (xlauf + 1, ylauf - 1, pix4r, pix4g, pix4b);
        pixpr= gewor*pix1r + gewhv*pix2r + gewhv*pix3r + gewdi*pix4r;
        pixpg= gewor*pix1g + gewhv*pix2g + gewhv*pix3g + gewdi*pix4g;
        pixpb= gewor*pix1b + gewhv*pix2b + gewhv*pix3b + gewdi*pix4b;
        pziel.putpixel (xlauf*2 + 1, ylauf*2, pixpr, pixpg, pixpb);
        }
      // dritter Pixel
      if ((ylauf < pquell.yanz - 1) && (xlauf > 0))
        {
        pquell.getpixel (xlauf - 1, ylauf    , pix2r, pix2g, pix2b);
        pquell.getpixel (xlauf    , ylauf + 1, pix3r, pix3g, pix3b);
        pquell.getpixel (xlauf - 1, ylauf + 1, pix4r, pix4g, pix4b);
        pixpr= gewor*pix1r + gewhv*pix2r + gewhv*pix3r + gewdi*pix4r;
        pixpg= gewor*pix1g + gewhv*pix2g + gewhv*pix3g + gewdi*pix4g;
        pixpb= gewor*pix1b + gewhv*pix2b + gewhv*pix3b + gewdi*pix4b;
        pziel.putpixel (xlauf*2, ylauf*2 + 1, pixpr, pixpg, pixpb);
        }
      // vierter Pixel
      if ((ylauf < pquell.yanz - 1) && (xlauf < pquell.xanz - 1))
        {
        pquell.getpixel (xlauf + 1, ylauf    , pix2r, pix2g, pix2b);
        pquell.getpixel (xlauf    , ylauf + 1, pix3r, pix3g, pix3b);
        pquell.getpixel (xlauf + 1, ylauf + 1, pix4r, pix4g, pix4b);
        pixpr= gewor*pix1r + gewhv*pix2r + gewhv*pix3r + gewdi*pix4r;
        pixpg= gewor*pix1g + gewhv*pix2g + gewhv*pix3g + gewdi*pix4g;
        pixpb= gewor*pix1b + gewhv*pix2b + gewhv*pix3b + gewdi*pix4b;
        pziel.putpixel (xlauf*2 + 1, ylauf*2 + 1, pixpr, pixpg, pixpb);
        }
      }       
  
  }
  
double volzelle (double a0, double ax, double ay, double a1, double xu, double xo, double yu, double yo)
  {
  double f0= a0*(xo-xu)*(yo-yu);
  double f1= 0.5*((ax-a0)*(yo-yu)*(xo*xo-xu*xu)+(ay-a0)*(xo-xu)*(yo*yo-yu*yu));
  double f2= 0.25*(a0+a1-ax-ay)*(xo*xo-xu*xu)*(yo*yo-yu*yu);
  return f0 + f1 + f2;
  }

void doubllinear (clscreen& pquell, clscreen& pziel)
  {
  for (signed long ylauf= 0; ylauf < pquell.yanz; ylauf++)
    for (signed long xlauf= 0; xlauf < pquell.xanz; xlauf++)
      {
      double fr0, fg0, fb0;
      double frx, fgx, fbx;
      double fry, fgy, fby;
      double fr1, fg1, fb1;
      double frout, fgout, fbout;
      double x00, y00, x01, y01, x10, y10, x11, y11;
      double xmin, ymin, xplu, yplu;
      double zpixr, zpixg, zpixb;
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
      frout= zpixr*4;
      fgout= zpixg*4;
      fbout= zpixb*4;
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
      frout= zpixr*4;
      fgout= zpixg*4;
      fbout= zpixb*4;
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
      frout= zpixr*4;
      fgout= zpixg*4;
      fbout= zpixb*4;
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
      frout= zpixr*4;
      fgout= zpixg*4;
      fbout= zpixb*4;
      pziel.putpixel (xlauf*2 + 1, ylauf*2 + 1, frout, fgout, fbout);
      }  
  }

void doublinterpol (clscreen& pquell, clscreen& pziel)
  {
  double fr, fg, fb, frx, fgx, fbx, fry, fgy, fby, frxy, fgxy, fbxy;
  for (signed long ylauf= 0; ylauf < pquell.yanz; ylauf++)
    for (signed long xlauf= 0; xlauf < pquell.xanz; xlauf++)
      {
      // Nachbarpixel einlesen
      pquell.getpixel (xlauf, ylauf, fr, fg, fb);
      pquell.getpixel (xlauf + 1 , ylauf, frx, fgx, fbx);
      pquell.getpixel (xlauf, ylauf + 1, fry, fgy, fby);
      pquell.getpixel (xlauf + 1, ylauf + 1, frxy, fgxy, fbxy);

      // linker oberer Pixel
      pziel.putpixel (xlauf*2, ylauf*2, fr, fg, fb);
      // rechter oberer Pixel
      pziel.putpixel (xlauf*2 + 1, ylauf*2, (fr + frx)/2, (fg + fgx)/2, (fb + fbx)/2);
      // linker unterer Pixel
      pziel.putpixel (xlauf*2, ylauf*2 + 1, (fr + fry)/2, (fg + fgy)/2, (fb + fby)/2);
      // rechter unterer Pixel
      pziel.putpixel (xlauf*2 + 1, ylauf*2 + 1, (fr + frx + fry + frxy)/4, (fg + fgx + fgy + fgxy)/4, (fb + fbx + fby + fbxy)/4);
      }  
  }

void doublraster (clscreen& pquell, clscreen& pziel)
  {
  double fr, fg, fb;
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
  
void transform (char* p_quelle, char* p_ziel, char* pent)
  {
  cbmpdatei quelldatei (p_quelle);
  cbmpdatei zieldatei (p_ziel, quelldatei.xanz*2, quelldatei.yanz*2);
  signed long ent;
  sscanf (pent, "%ld", &ent);
  if (ent == 0)
    doublraster (quelldatei, zieldatei);
  if (ent == 1)
    doublinterpol (quelldatei, zieldatei);
  if (ent == 2)
    doubllinear (quelldatei, zieldatei);
  if (ent == 3)
    doublgewichtung (quelldatei, zieldatei);
  }
  
int main (int argc, char** argv)
  {
  if (argc != 4)
    return 0;
  transform (argv[1], argv[2], argv[3]);
  return 0;
  }
