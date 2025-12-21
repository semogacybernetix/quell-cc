#include "../../cc/screen/jpegscr.h"
#include "../../cc/screen/bmpscr.h"

void makemercator (char* p_name)
  {
  // jpeg-Datei einlesen und in eine bmp-Datei speichern
  cjpegdatei jpgdatei (p_name);
  cbmpdatei bmpdatei ("mercator.bmp", jpgdatei.xanz, jpgdatei.yanz);
  bmpdatei.putscreen (jpgdatei, 0, 0);

  // bmp-Datei bearbeiten (Linien ziehen)
  integer r, g, b;

  // Nullmeridian zeichnen
  for (integer laufy= 0; laufy < bmpdatei.yanz; laufy++)
    {
    //bmpdatei.getpixel (bmpdatei.xanz/2, laufy, 0,0,b);
    bmpdatei.putpixel (bmpdatei.xanz/2, laufy, 0, 0, 0);
    //bmpdatei.getpixel (bmpdatei.xanz/2-1, laufy, r,g,b);
    bmpdatei.putpixel (bmpdatei.xanz/2-1, laufy, 0,0,0);
    }

  // 180°meridian zeichnen
  for (integer laufy= 0; laufy < bmpdatei.yanz; laufy++)
    {
    //bmpdatei.getpixel (0, laufy, r,g,b);
    bmpdatei.putpixel (0, laufy, 255, 255, 255);
    //bmpdatei.getpixel (bmpdatei.xanz-1, laufy, r,g,b);
    bmpdatei.putpixel (bmpdatei.xanz-1, laufy, 255,255,255);
    }

  // Äquator zeichnen
  for (integer laufx= 0; laufx < bmpdatei.xanz; laufx++)
    {
    bmpdatei.getpixel (laufx, bmpdatei.yanz/2, r,g,b);
    bmpdatei.putpixel (laufx, bmpdatei.yanz/2, 255-r, 255-g, 255-b);
    bmpdatei.getpixel (laufx, bmpdatei.yanz/2-1, r,g,b);
    bmpdatei.putpixel (laufx, bmpdatei.yanz/2-1, 255-r,255-g,255-b);
    }

  // Längengrade zeichnen
  for (integer laufx= 1; laufx < 36; laufx++)
    {
    real lm= real (bmpdatei.xanz-1)/2;
    real lg= real (bmpdatei.xanz*laufx)/72;

    for (integer laufy= 0; laufy < bmpdatei.yanz; laufy++)
      {
      bmpdatei.getpixel (integer (lm + lg), laufy, r,g,b);
      bmpdatei.putpixel (integer (lm + lg), laufy, 255-r, 255-g, 255-b);
      bmpdatei.getpixel (integer (lm - lg), laufy, r,g,b);
      bmpdatei.putpixel (integer (lm - lg), laufy, 255-r, 255-g, 255-b);
      }
    }

  // Breitengrade zeichnen
  //real pxrad= PI2/real (bmpdatei.xanz);
  for (integer laufy= 1; laufy < 36; laufy++)
    {
    real bm= real (bmpdatei.yanz-1)/2;
    //real bg= tanhr (laufy*5/180*PI)/PI*180/360*bmpdatei.xanz;
    real bg= atanhr (PI*real (laufy)/36)/PI*real (bmpdatei.xanz)/2;

    for (integer laufx= 0; laufx < bmpdatei.xanz; laufx++)
      {
      bmpdatei.getpixel (laufx, integer (bm + bg), r,g,b);
      bmpdatei.putpixel (laufx, integer (bm + bg), 255-r, 255-g, 255-b);
      bmpdatei.getpixel (laufx, integer (bm - bg), r,g,b);
      bmpdatei.putpixel (laufx, integer (bm - bg), 255-r, 255-g, 255-b);
      }
    }

  }

int main (int argc, char** argv)
  {
  if (argc != 2)
    return 0;
  makemercator (argv[1]);
  return 0;
  }
