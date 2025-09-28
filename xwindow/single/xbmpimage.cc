#include "../../cc/screen/bmpscr.h"

#include <X11/Xlib.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>

void imagewindow (char* dateiname)
  {
  // Eingabescreen und Ausgabescreen erzeugen
  cbmpdatei bmpdatei (dateiname);
  Display* display0= XOpenDisplay (0);
  Window window0= XCreateWindow (display0, XDefaultRootWindow (display0), 0, 0, bmpdatei.xanz, bmpdatei.yanz, 0, 24, InputOutput, 0, 0, 0);
  XMapRaised (display0, window0);
  GC gc0= XCreateGC (display0, window0, 0, 0);
  Visual* visual0= XDefaultVisual (display0, 0);

  // Bilddaten auf den Bildschirm kopieren
  char* idata= (char*) malloc (bmpdatei.xanz*bmpdatei.yanz*32);
  long double red= 0, green= 0, blue= 0;
  signed long zeile= bmpdatei.xanz*4;
  for (signed long ylauf= 0; ylauf < bmpdatei.yanz; ylauf++)
    for (signed long xlauf= 0; xlauf < bmpdatei.xanz; xlauf++)
      {
      bmpdatei.getpixel (xlauf, ylauf, red, green, blue);
      idata[(bmpdatei.yanz - 1 - ylauf)*zeile + xlauf*4 + 0]= blue;
      idata[(bmpdatei.yanz - 1 - ylauf)*zeile + xlauf*4 + 1]= green;
      idata[(bmpdatei.yanz - 1 - ylauf)*zeile + xlauf*4 + 2]= red;
      }
  
  //Bilddaten anzeigen
  XImage* image= XCreateImage (display0, visual0, 24, ZPixmap, 0, idata, bmpdatei.xanz, bmpdatei.yanz, 8, 0);
  XPutImage (display0, window0, gc0, image, 0, 0, 0, 0, bmpdatei.xanz, bmpdatei.yanz);
  XFlush (display0);
  getchar ();
  }

int main (int argc, char** argv)
  {
  if (argc != 2)
    {
    printf ("BMP-Datei angeben\n");
    return 0;
    }
  imagewindow (argv[1]);
  return 0;
  }
