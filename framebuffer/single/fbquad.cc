#include "../screen/fbscr.h"

int main ()
  {
  cfbscreen fbscreen ("", 1024, 1024);
  //while (1)
  for (signed long ly= 0; ly < 1024; ly++)
    for (signed long lx= 0; lx < 1280; lx++)
      {
      fbscreen.putpixel (lx, ly, lx, ly, 255 - (lx + ly + labs (lx - ly))/2);        // Spektrum
      /*
      signed long zuf1= random () & 255;
      signed long zuf2= random () & 255;
      signed long zuf3= random () & 255;
      signed long zuf4= (zuf1 + zuf2 + zuf3)/3;
      //fbscreen.putpixel (lx, ly, zuf4, zuf4, zuf4);                                  // Grau-Rauschen
      fbscreen.putpixel (lx, ly, zuf1, zuf2, zuf3);                                  // Farb-Rauschen
      //*/
      }
  return 0;
  }
