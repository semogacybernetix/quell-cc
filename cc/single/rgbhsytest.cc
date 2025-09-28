#include "../screen/allscr.h"
#include "single.h"
#include "../class/vektor.h"

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>

void testergbhsy ()
  {
  for (signed long lrot= 0; lrot < 256; lrot++)
    for (signed long lgrn= 0; lgrn < 256; lgrn++)
      for (signed long lblu= 0; lblu < 256; lblu++)
	    {
		float rot, grn, blu;
		float hue, sat, hel;
		signed long zrot, zgrn, zblu;
		rot= float (lrot)/255;
		grn= float (lgrn)/255;
		blu= float (lblu)/255;
		rgbtohsy (rot, grn, blu, hue, sat, hel);
		hsytorgb (hue, sat, hel, rot, grn, blu);
		zrot= lrint (rot*255);
		zgrn= lrint (grn*255);
		zblu= lrint (blu*255);
		if ((zrot != lrot) | (zgrn != lgrn) | (zblu != lblu))
		  {
		  printf ("Fehler: %3ld %3ld %3ld    %3ld %3ld %3ld\n", lrot, lgrn, lblu, zrot, zgrn, zblu);
		  }
		}
    
  }

int main (int argc, char** argv)
  {
  testergbhsy ();
  return 0;
  }
