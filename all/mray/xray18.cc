#include "../../cc/class/ray.h"
#include "../../cc/class/game.h"
#include "../../cc/screen/allscr.h"
#include "../../xwindow/screen/xscr.h"
#include "../../xwindow/keyboard/xkbd.h"

void fliegen ()
  {
  cwelt welt (2520, cvektor3 (0, 100, -1500), cbasis3 (cvektor3 (1,0,0), cvektor3 (0,1,0), cvektor3 (0,0,1)));
  welt.addkoerper (new ckoerper (new csebene, new cparawebene, new cbegrellipse (20, 10), new cschachfeld (cvektor3 (1,0,0), cvektor3 (0,1,0), 100, 100), cvektor3 (0,0,0), cbasis3 (cvektor3 (100,0,0), cvektor3 (0,0,100), cvektor3 (0,100,0))));
//  welt.addkoerper (new ckoerper (new cskugel, new cparawkugel, new cbegrkeine (), new cschachfeld (cvektor3 (1,0,1), cvektor3 (1,1,0), 100, 100), cvektor3 (0,1300,0), cbasis3 (cvektor3 (320,0,0), cvektor3 (0,0,-320), cvektor3 (0,320,0))));
  welt.addkoerper (new ckoerper (new cskugel, new cparawkugel, new cbegrkeine (), new cscreenmannig (new cjpegdatei ("../../xwindow/xdia/bilder/katze.jpg"), 10), cvektor3 (0,1300,0), cbasis3 (cvektor3 (320,0,0), cvektor3 (0,0,-320), cvektor3 (0,320,0))));
  welt.addkoerper (new ckoerper (new cszylinder, new cparawzylinder, new cbegrkeine, new cschachfeld (cvektor3 (1,1,1), cvektor3 (0,1,1), 100, 100), cvektor3 (0,0,0), cbasis3 (cvektor3 (100,0,0), cvektor3 (0,0,100), cvektor3 (0,100,0))));
  cxscreen screen ("ray", 1600, 900);
  cxkeyboard keyboard;
  cflugsimu flugsimu (&welt, &keyboard, &screen);
  flugsimu.fliege ();
  }

int main ()
  {
  fliegen ();
  return 0;
  }
