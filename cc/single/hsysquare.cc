// zeichnet ein Testbild welches das Spektrum durchläuft

#include "../screen/allscr.h"
#include "single.h"
#include "../class/vektor.h"

#include <cstdio>
#include <cstring>


void rectfill (clscreen& iscreen, signed long ix, signed long iy, signed long ixd, signed long iyd, cvektor3& ifarbe)
  {
  for (signed long ylauf= 0; ylauf < iyd; ylauf++)
    for (signed long xlauf= 0; xlauf < ixd; xlauf++)
      {
      signed long rot= lrint (255*ifarbe.x);
      signed long grn= lrint (255*ifarbe.y);
      signed long blu= lrint (255*ifarbe.z);
      iscreen.putpixel (ix + xlauf, iy + ylauf, rot, grn, blu);
      }
  }

void zeichnesquare ()
  {
  cpsdatei hsybild ("ps-hue-100.ps", 767, 767);
  hsybild.hintergrund (0xff);
  cvektor3 hsyfarbe (0, 0, 0);
  cvektor3 rgbfarbe (0, 0, 0);
  for (signed long laufhue= 0; laufhue < 100; laufhue++)
    {
    hsyfarbe.x= (laufhue + 0.5)/50*M_PI;
    hsyfarbe.y= 0.38;
    hsyfarbe.z= 0.5;
    hsytorgb (hsyfarbe.x, hsyfarbe.y, hsyfarbe.z, rgbfarbe.x, rgbfarbe.y, rgbfarbe.z);
    signed long rectx= 50*(laufhue%10);
    signed long recty= 50*(laufhue/10);
    rectfill (hsybild, 120 + rectx, 600 - recty, 45, 45, rgbfarbe);
    }
  }

int main ()
  {
  zeichnesquare ();
  return 0;
  }
