#include "../../cc/class/ray.h"
#include "../../xwindow/screen/xscr.h"
#include "../../cc/screen/allscr.h"
#include "../../xwindow/keyboard/xkbd.h"

void fliegen ()
  {
  // Standpunkt
  cvektor3 stand (0, 100, -1000);
  
  // Blickrichtung
  cbasis3 blick (cvektor3 (1,0,0), cvektor3 (0,1,0), cvektor3 (0,0,1));
  
  // Welt
  cwelt welt (2670, stand, blick);

  // Texturen
  cschachfeld textur1 (cvektor3 (1,0,0), cvektor3 (0,1,0));
  cschachfeld textur2 (cvektor3 (1,0,1), cvektor3 (1,1,0));
  cschachfeld textur3 (cvektor3 (1,1,1), cvektor3 (0,1,1));
  
  // Begrenzungen
  
  // Körperstandpunkte
  cvektor3 kst1 (0,0,0);
  cvektor3 kst2 (0,500,0);
  cvektor3 kst3 (0,0,0);
  
  // Körperlagen
  cbasis3 kl1 (cvektor3 (100,0,0), cvektor3 (0,100,0), cvektor3 (0,0,100));
  cbasis3 kl2 (cvektor3 (100,0,0), cvektor3 (0,0,100), cvektor3 (0,-100,0));
  cbasis3 kl3 (cvektor3 (100,0,0), cvektor3 (0,0,100), cvektor3 (0,100,0));
  
  // Körper
  ckoerper* koe1= new ckoerper (new cskugel, new cparawkugel, new cbegrkeine (), &textur1, kst2, kl2);
  ckoerper* koe2= new ckoerper (new cskugel, new cparawkugel, new cbegrkeine (), &textur2, kst1, kl1);
  
  // Körper zur Welt hinzufügen
  welt.addkoerper (koe1);
  welt.addkoerper (koe2);
  cflugsimu flugsimu (&welt, new cxkeyboard, new cxscreen ("xray", 480, 270));
  flugsimu.fliege ();
  }

int main ()
  {
  fliegen ();
  return 0;
  }
