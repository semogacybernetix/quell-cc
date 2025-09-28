#include "../../cc/class/game.h"
#include "../../cc/class/ray.h"
#include "../../cc/screen/allscr.h"
#include "../../framebuffer/screen/fbscr.h"
#include "../../xwindow/keyboard/xkbd.h"

void addkatzenturm (cwelt& pwelt)
  {
  // Körperstandpunkte
  cvektor3 kst1 (0,0,0);
  cvektor3 kst2 (0,1300,0);

  // Körperlagen
  cbasis3 kl1 (cvektor3 (100,0,0), cvektor3 (0,0,100), cvektor3 (0,100,0));
  cbasis3 kl2 (cvektor3 (320,0,0), cvektor3 (0,0,320), cvektor3 (0,320,0));

  // Begrenzungen
  cbegrellipse* ell1= new cbegrellipse (100, 200);

  // Texturen
  cschachfeld* textur1= new cschachfeld (cvektor3 (1,0,0), cvektor3 (0,1,0), 1, 1);
  cschachfeld* textur2= new cschachfeld (cvektor3 (1,1,1), cvektor3 (0,1,1), 1, 1);

  // Körper addieren
  pwelt.addkoerper (new ckoerper (new csebene, new cparawebene, ell1, textur1, kst1, kl1));
  pwelt.addkoerper (new ckoerper (new cskugel, new cparawkugel, new cbegrkeine, new cscreenmannig (new cjpegdatei ("/root/quell-cc/xwindow/xdia/bilder/katze.jpg"), 10), kst2, kl2));
  pwelt.addkoerper (new ckoerper (new cszylinder, new cparawzylinder, ell1, textur2, kst1, kl1));

  pwelt.verschiebeauge (cvektor3 (0, 500, -10000));
  }

void addebenen90 (cwelt& pwelt)
  {
  // Körperstandpunkte
  cvektor3 kst1 (0,0,0);

  // Körperlagen
  cbasis3 kl1 (cvektor3 (10,0,0), cvektor3 (0,10,0), cvektor3 (0,0,10));
  cbasis3 kl2 (cvektor3 (0,10,0), cvektor3 (0,0,10), cvektor3 (10,0,0));
  cbasis3 kl3 (cvektor3 (0,0,10), cvektor3 (10,0,0), cvektor3 (0,10,0));

  // Begrenzungen
  cbegrellipse* ell1= new cbegrellipse (10, 10);

  // Texturen
  cschachfeld* textur1= new cschachfeld (cvektor3 (1,0,0), cvektor3 (0,1,0), 1, 1);
  cschachfeld* textur2= new cschachfeld (cvektor3 (1,0,1), cvektor3 (1,1,0), 1, 1);
  cschachfeld* textur3= new cschachfeld (cvektor3 (1,1,1), cvektor3 (0,1,1), 1, 1);

  // Körper addieren
  pwelt.addkoerper (new ckoerper (new csebene, new cparawebene, ell1, textur1, kst1, kl1));
  pwelt.addkoerper (new ckoerper (new csebene, new cparawebene, ell1, textur2, kst1, kl2));
  pwelt.addkoerper (new ckoerper (new csebene, new cparawebene, ell1, textur3, kst1, kl3));

  pwelt.verschiebeauge (cvektor3 (0, 0, -2250));
  }

int main ()
  {
  cwelt* welt= new cwelt (2250, cvektor3 (0), cbasis3 (1));  // Bildschirmentfernung, Standpunkt, Lage
  //addkatzenturm (*welt);
  addebenen90 (*welt);
  cflugsimu flugsimu (welt, new cxkeyboard, new cfbscreen ("fbray", 800, 450));
  flugsimu.fliege ();
  return 0;
  }
