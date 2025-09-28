#include "vscr.h"

using namespace std;

clscreen8::clscreen8 ()
  : xanz (0), yanz (0)
  {
  }

clscreen8::clscreen8 (integer px, integer py)
  : xanz (px), yanz (py)
  {
  }

void clscreen8::putscreen (clscreen8& pscreen, integer px, integer py)       // den Bildschirminhalt des screens auf einen anderen screen ausgeben (Schnittmenge der Bildschirmbereiche)
  {
  integer r, g, b;

  for (integer laufy= 0; laufy < pscreen.yanz; laufy++)
    for (integer laufx= 0; laufx < pscreen.xanz; laufx++)
      {
      pscreen.getpixel (laufx, laufy, r, g, b);
      putpixel (px + laufx, py + laufy, r, g, b);
      }
  }
