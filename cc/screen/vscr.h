#ifndef vscr_h
#define vscr_h

#include "../class/vektor.h"

struct clscreen8                                         // abstrakte Basisklasse eines Screens mit 8 Bit Farbtiefe pro Farbe
  {
  clscreen8 ();
  clscreen8 (integer px, integer py);                    // Auflösung des screens: x mal y

  virtual void getpixel (integer px, integer py, integer& pr, integer& pg, integer& pb)= 0;
  virtual void putpixel (integer px, integer py, integer pr, integer pg, integer pb)= 0;
  void putscreen (clscreen8& pscreen, integer px, integer py);
  virtual void flush ()= 0;

  integer xanz, yanz;
  };

#endif
