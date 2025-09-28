#include "../../cc/class/ray.h"
#include "../../cc/screen/allscr.h"
#include <cstdio>

void welttoscreen (cwelt& pwelt, clscreen& pscreen)
  {
  float xoff ((1 - pscreen.xanz)/float (2));
  float yoff ((1 - pscreen.yanz)/float (2));
  for (unsigned short ypp= 0; ypp < pscreen.yanz; ++ypp)
    for (unsigned short xpp= 0; xpp < pscreen.xanz; ++xpp)
      {
      cvektor3 fb= pwelt.getpunkt (cvektor2 (xpp + xoff, ypp + yoff));
      unsigned short r= (unsigned short) (fb.x*pscreen.rmax + .5);
      unsigned short g= (unsigned short) (fb.y*pscreen.gmax + .5);
      unsigned short b= (unsigned short) (fb.z*pscreen.bmax + .5);
      pscreen.putpixel (xpp, ypp, r, g, b);
      }
  }

void fliegen ()
  {
  // Standpunkt
  cvektor3 stand (-60, 60, -4479);
  
  // Blickrichtung
  cbasis3 blick (cvektor3 (1,0,0), cvektor3 (0,1,0), cvektor3 (0,0,1));
  
  // Welt
  cwelt welt (640, stand, blick);

  // Texturen
  cschachfeld textur1 (cvektor3 (1,0,0), cvektor3 (0,1,0));
  cschachfeld textur2 (cvektor3 (1,1,0), cvektor3 (1,0,1));
  cschachfeld textur3 (cvektor3 (0,1,1), cvektor3 (1,1,1));
  
  // Körperstandpunkte
  cvektor3 kst1 (0,-110,0);
  cvektor3 kst2 (-90,400,300);
  cvektor3 kst3 (-50,-100,0);
  
  // Körperlagen
  cbasis3 kp1 (cvektor3 (100,0,0), cvektor3 (0,0,100), cvektor3 (0,100,0));
  cbasis3 kp2 (cvektor3 (0,0,320), cvektor3 (0,320,0), cvektor3 (320,0,0));
  cbasis3 kp3 (cvektor3 (100,0,0), cvektor3 (0,100,0), cvektor3 (0,0,100));

  // Körper zur Welt hinzufügen
  welt.addkoerper (new ckoerper (new csebene, new cparawebene, new cbegrkeine (), &textur1, kst1, kp1));
  welt.addkoerper (new ckoerper (new cskugel, new cparawkugel, new cbegrkeine (), &textur2, kst2, kp2));
  welt.addkoerper (new ckoerper (new csezylinder, new cparawezylinder, new cbegrkeine (), &textur3, kst3, kp3));
  unsigned long bildanz= 500;
  cvideodatei videodatei ("out.rvd", 320, 240, bildanz, 50);
  for (unsigned long lbild= 0; lbild < bildanz; lbild++)
    {
    videodatei.selectpage (lbild);
    welttoscreen (welt, videodatei);
    printf ("%6lu\n", lbild);
    welt.dreheauge (getrotx (-.002));
    welt.verschiebeauge (20*welt.augbasis.z);
    }
  }

int main ()
  {
  fliegen ();
  return 0;
  }
