#include "../../cc/screen/jpegscr.h"
#include "../../cc/screen/bmpscr.h"

void makemercator (char* p_name)
  {
  // jpeg-Datei einlesen und in eine bmp-Datei speichern
  cjpegdatei jpgdatei (p_name);
  cbmpdatei bmpdatei ("mercator.bmp", jpgdatei.xanz, jpgdatei.yanz);
  bmpdatei.putscreen (jpgdatei, 0, 0);

  // bmp-Datei bearbeiten (Linien ziehen)
  real farbe1;

  // Längengrade zeichnen
  real lmitte= real (bmpdatei.xanz-1)/2;
  for (integer laufx= -36; laufx <= 36; laufx++)
    {
    real lg= real (bmpdatei.xanz*laufx)/72;
    real putx= lmitte + lg;
    farbe1= (putx - floorr (putx))*255;
    integer putxi= integer (floorr (putx));

    for (integer laufy= 0; laufy < bmpdatei.yanz; laufy++)
      bmpdatei.putpixel (putxi, laufy, integer (farbe1), integer (farbe1), integer (farbe1));
    if (farbe1 != 0)
      for (integer laufy= 0; laufy < bmpdatei.yanz; laufy++)
        bmpdatei.putpixel (putxi+1,laufy, 255-integer (farbe1), 255-integer (farbe1), 255-integer (farbe1));

    // Nullmeridian zeichnen
    if (laufx == 0)
      {
      for (integer laufy= 0; laufy < bmpdatei.yanz; laufy++)
        bmpdatei.putpixel (putxi, laufy, integer (255-farbe1), 0, 0);
      if (farbe1 != 0)
        for (integer laufy= 0; laufy < bmpdatei.yanz; laufy++)
          bmpdatei.putpixel (putxi+1,laufy, integer (farbe1), 0, 0);
      }

    // -180° Meridian zeichnen
    if (laufx == -36)
      {
      for (integer laufy= 0; laufy < bmpdatei.yanz; laufy++)
        bmpdatei.putpixel (putxi, laufy, 0, integer (255-farbe1), 0);
      if (farbe1 != 0)
        for (integer laufy= 0; laufy < bmpdatei.yanz; laufy++)
          bmpdatei.putpixel (putxi+1,laufy, 0, integer (farbe1), 0);
      }

    // 180° Meridian zeichnen
    if (laufx == 36)
      {
      for (integer laufy= 0; laufy < bmpdatei.yanz; laufy++)
        bmpdatei.putpixel (putxi, laufy, 0, 0, integer (255-farbe1));
      if (farbe1 != 0)
        for (integer laufy= 0; laufy < bmpdatei.yanz; laufy++)
          bmpdatei.putpixel (putxi+1,laufy, 0, 0, integer (farbe1));
      }
    }

  // Breitengrade zeichnen
  real pxrad= PI2/real (bmpdatei.xanz);
  real bmitte= real (bmpdatei.yanz-1)/2;
  for (integer laufy= -17; laufy < 18; laufy++)
    {
    real bg= atanhr (sinr (real (laufy)/36*PI))/pxrad;
    real puty= bmitte + bg;
    farbe1= (puty - floorr (puty))*255;
    integer putyi= integer (floorr (puty));

    for (integer laufx= 0; laufx < bmpdatei.xanz; laufx++)
      bmpdatei.putpixel (laufx, putyi, integer (farbe1), integer (farbe1), integer (farbe1));
    if (farbe1 != 0)
      for (integer laufx= 0; laufx < bmpdatei.xanz; laufx++)
        bmpdatei.putpixel (laufx, putyi+1, 255 - integer (farbe1), 255-integer (farbe1), 255-integer (farbe1));

    // Äquator zeichnen
    if (laufy == 0)
      {
      for (integer laufx= 0; laufx < bmpdatei.xanz; laufx++)
        bmpdatei.putpixel (laufx, putyi, 255 - integer (farbe1), 0, 0);
      if (farbe1 != 0)
        for (integer laufx= 0; laufx < bmpdatei.xanz; laufx++)
          bmpdatei.putpixel (laufx, putyi+1, integer (farbe1), 0, 0);
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
