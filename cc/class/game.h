#ifndef game_h
#define game_h

#include "ray.h"
#include "../screen/vscr.h"
#include "../keyboard/vkbd.h"

struct cflugsimu
  {
  cflugsimu (cwelt* pwelt, clkeyboard* plkeyboard, clscreen8* plscreen);
  void setframedauer (real pfr);
  void welttoscreenl ();
  void welttoscreenz ();
  void welttoscreentakt (integer& renderanz);
  void welttoscreenthread (integer pthreadnr);
  void fliege ();
  void fliegek ();              // mit Körperdrehungen
  void fliegetakt ();           // noch nicht implementiert
  void fliegethread ();
  void fliegespiel (cbasis3& spiegelebenen, ckoerper* bewkugel);
  void fliegespieltakt (cbasis3& spiegelebenen, ckoerper* bewkugel);

  integer  threadanz;              // Anzahl der Threads (von außen setzbar)

  private:
  real         tickms;             // Dauer eines Ticks in Millisekunden
  real         framems;            // Anzeigedauer eines Frames in Millisekunden
  real         frametk;            // Anzeigedauer eines Frames in Ticks
  real         framepos;           // Zeitpunkt

  integer      pixelanz;           // Anzahl der Pixel des screens
  integer      pixelpos;           // momentane Pixelposition beim Rendern

  cwelt*       welt;
  clkeyboard*  keyboard;
  clscreen8*   screen;
  real         xoff, yoff;

  public:
  real     bewstep, drehstep;      // Bewegungsschrittweite, Drehwinkelschrittweite

  private:

  struct cpixel
    {
    integer x, y;
    };

  cpixel*     pixels;              // Pixelarray für zufallsreihenfolgige Renderung

  };

#endif
