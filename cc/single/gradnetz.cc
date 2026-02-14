#include "../../cc/screen/jpegscr.h"
#include "../../cc/screen/bmpscr.h"

void gradl (clscreen8* pscreen)
  {
  real farbe;

  // Längengrade zeichnen
  real lmitte= real (pscreen->xanz-1)/2;
  for (integer laufx= -36; laufx <= 36; laufx++)
    {
    real lg= real (pscreen->xanz*laufx)/72;
    real putx= lmitte + lg;
    farbe= (putx - floorr (putx))*255;
    integer putxi= integer (floorr (putx));

    for (integer laufy= 0; laufy < pscreen->yanz; laufy++)
      pscreen->putpixel (putxi, laufy, integer (farbe), integer (farbe), integer (farbe));
    if (farbe != 0)
      for (integer laufy= 0; laufy < pscreen->yanz; laufy++)
        pscreen->putpixel (putxi+1,laufy, 255-integer (farbe), 255-integer (farbe), 255-integer (farbe));

    // Nullmeridian zeichnen
    if (laufx == 0)
      {
      for (integer laufy= 0; laufy < pscreen->yanz; laufy++)
        pscreen->putpixel (putxi, laufy, integer (255-farbe), 0, 0);
      if (farbe != 0)
        for (integer laufy= 0; laufy < pscreen->yanz; laufy++)
          pscreen->putpixel (putxi+1,laufy, integer (farbe), 0, 0);
      }

    // -180° Meridian zeichnen
    if (laufx == -36)
      {
      for (integer laufy= 0; laufy < pscreen->yanz; laufy++)
        pscreen->putpixel (putxi, laufy, 0, integer (255-farbe), 0);
      if (farbe != 0)
        for (integer laufy= 0; laufy < pscreen->yanz; laufy++)
          pscreen->putpixel (putxi+1,laufy, 0, integer (farbe), 0);
      }

    // 180° Meridian zeichnen
    if (laufx == 36)
      {
      for (integer laufy= 0; laufy < pscreen->yanz; laufy++)
        pscreen->putpixel (putxi, laufy, 0, 0, integer (255-farbe));
      if (farbe != 0)
        for (integer laufy= 0; laufy < pscreen->yanz; laufy++)
          pscreen->putpixel (putxi+1,laufy, 0, 0, integer (farbe));
      }
    }
  }

void gradbmercator (clscreen8* pscreen)
  {
  real farbe;

  // Breitengrade zeichnen
  real pxrad= PI2/real (pscreen->xanz);
  real bmitte= real (pscreen->yanz-1)/2;
  for (integer laufy= -17; laufy < 18; laufy++)
    {
    real bg= atanhr (sinr (real (laufy)/36*PI))/pxrad;
    real puty= bmitte + bg;
    farbe= (puty - floorr (puty))*255;
    integer putyi= integer (floorr (puty));

    for (integer laufx= 0; laufx < pscreen->xanz; laufx++)
      pscreen->putpixel (laufx, putyi, integer (farbe), integer (farbe), integer (farbe));
    if (farbe != 0)
      for (integer laufx= 0; laufx < pscreen->xanz; laufx++)
        pscreen->putpixel (laufx, putyi+1, 255 - integer (farbe), 255-integer (farbe), 255-integer (farbe));

    // Äquator zeichnen
    if (laufy == 0)
      {
      for (integer laufx= 0; laufx < pscreen->xanz; laufx++)
        pscreen->putpixel (laufx, putyi, 255 - integer (farbe), 0, 0);
      if (farbe != 0)
        for (integer laufx= 0; laufx < pscreen->xanz; laufx++)
          pscreen->putpixel (laufx, putyi+1, integer (farbe), 0, 0);
      }
    }
  }

void gradbplatt (clscreen8* pscreen)
  {
  real farbe;

  // Breitengrade zeichnen
  real pxrad= PI2/real (pscreen->xanz);
  real bmitte= real (pscreen->yanz-1)/2;
  for (integer laufy= -36; laufy < 36; laufy++)
    {
    real bg= real (laufy)/36*PI/pxrad;
    real puty= bmitte + bg;
    farbe= (puty - floorr (puty))*255;
    integer putyi= integer (floorr (puty));

    for (integer laufx= 0; laufx < pscreen->xanz; laufx++)
      pscreen->putpixel (laufx, putyi, 0, 255-integer (farbe), 0);
    if (farbe != 0)
      for (integer laufx= 0; laufx < pscreen->xanz; laufx++)
        pscreen->putpixel (laufx, putyi+1, 0, 255-integer (farbe), 0);

    // Äquator zeichnen
    if (laufy == 0)
      {
      for (integer laufx= 0; laufx < pscreen->xanz; laufx++)
        pscreen->putpixel (laufx, putyi, 255 - integer (farbe), 0, 0);
      if (farbe != 0)
        for (integer laufx= 0; laufx < pscreen->xanz; laufx++)
          pscreen->putpixel (laufx, putyi+1, integer (farbe), 0, 0);
      }
    }
  }

void zeichnegradnetz (char* p_name)
  {
  // jpeg-Datei einlesen und in eine bmp-Datei speichern
  cjpegdatei jpgdatei (p_name);
  cbmpdatei bmpdatei ("mercator.bmp", jpgdatei.xanz, jpgdatei.yanz);
  bmpdatei.putscreen (jpgdatei, 0, 0);

  // Gradnetz in bmp-Datei zeichnen
  // Längengrade
  //gradl (&bmpdatei);

  // Breitengrade
  gradbplatt (&bmpdatei);
  //gradbmercator (&bmpdatei);
  }

int main (int argc, char** argv)
  {
  if (argc != 2)
    return 0;
  zeichnegradnetz (argv[1]);
  return 0;
  }
