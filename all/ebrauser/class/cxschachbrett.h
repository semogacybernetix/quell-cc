#ifndef cxschachbrett_h
#define cxschachbrett_h

#include "../../cc/screen/allscr.h"
#include "../../xwindow/screen/xscr.h"

//------------------------------ Klasse Schachbrett ------------------------------------------------------------------------

struct cxschachbrett
  {
  cbmpdatei*  feldbmp[128];  // Bilder der Figuren schwarz und weiß
  cxscreen*   bscreen;
  signed long brett[65];  // auf dem 65. Feld steht welche Farbe am Zug ist

  cxschachbrett ();
  ~cxschachbrett ();
  void putfeld (signed long pfeldnr);
  void putamsatz ();
  void putbrett (signed long* pbrett);
  void refresh ();
  signed long getgezogen (signed long* pvonfeld, signed long* phinfeld);
  };

#endif
