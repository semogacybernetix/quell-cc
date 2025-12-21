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
  for (integer lauf= 0; lauf < bmpdatei.yanz; lauf++)
    {
    //bmpdatei.getpixel (bmpdatei.xanz/2, lauf, 0,0,b);
    bmpdatei.putpixel (bmpdatei.xanz/2, lauf, 0, 0, 0);
    //bmpdatei.getpixel (bmpdatei.xanz/2-1, lauf, r,g,b);
    bmpdatei.putpixel (bmpdatei.xanz/2-1, lauf, 0,0,0);
    }

  // 180°meridian zeichnen
  for (integer lauf= 0; lauf < bmpdatei.yanz; lauf++)
    {
    //bmpdatei.getpixel (0, lauf, r,g,b);
    bmpdatei.putpixel (0, lauf, 255, 255, 255);
    //bmpdatei.getpixel (bmpdatei.xanz-1, lauf, r,g,b);
    bmpdatei.putpixel (bmpdatei.xanz-1, lauf, 255,255,255);
    }

  // Äquator zeichnen
  for (integer lauf= 0; lauf < bmpdatei.xanz; lauf++)
    {
    bmpdatei.getpixel (lauf, bmpdatei.yanz/2, r,g,b);
    bmpdatei.putpixel (lauf,bmpdatei.yanz/2, 255-r, 255-g, 255-b);
    bmpdatei.getpixel (lauf,bmpdatei.yanz/2-1, r,g,b);
    bmpdatei.putpixel (lauf,bmpdatei.yanz/2-1, 255-r,255-g,255-b);
    }

  //real fg;    // Anzahl Pixel für 5° Abstand der Längengrade
  //fg= real (bmpdatei.xanz)/72;
  }

int main (int argc, char** argv)
  {
  if (argc != 2)
    return 0;
  makemercator (argv[1]);
  return 0;
  }
