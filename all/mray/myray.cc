#include "../../cc/ray/ray.h"
#include "../../dos/io/screen/mystscr.h"
#include "../../dos/io/keyboard/hwkbd.h"

void fliegen ()
  {
  cwelt welt (639, cvektor3 (0, 100, -1500), cbasis3 (cvektor3 (1,0,0), cvektor3 (0,1,0), cvektor3 (0,0,1)));
  welt.addkoerper (new ckoerper (new csebene, new cparawebene, new cschachfeld (cvektor3 (1,0,0), cvektor3 (0,1,0)), cvektor3 (0,0,0), cbasis3 (cvektor3 (100,0,0), cvektor3 (0,0,100), cvektor3 (0,100,0))));
  welt.addkoerper (new ckoerper (new cskugel, new cparawkugel, new cschachfeld (cvektor3 (1,0,1), cvektor3 (1,1,0)), cvektor3 (0,1300,0), cbasis3 (cvektor3 (0,0,320), cvektor3 (0,320,0), cvektor3 (320,0,0))));
  welt.addkoerper (new ckoerper (new csezylinder, new cparawezylinder, new cschachfeld (cvektor3 (1,1,1), cvektor3 (0,1,1)), cvektor3 (0,0,0), cbasis3 (cvektor3 (100,0,0), cvektor3 (0,0,100), cvektor3 (0,100,0))));
  cmystscreen screen ("ray", 640, 480);
  cdoskeyboard keyboard;
  cflugsimu flugsimu (&welt, &keyboard, &screen);
  flugsimu.fliege ();
  }

int main ()
  {
  fliegen ();
  return 0;
  }
