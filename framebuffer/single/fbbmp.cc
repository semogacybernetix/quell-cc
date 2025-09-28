#include "../../cc/screen/bmpscr.h"
#include "../screen/fbscr.h"

#include <cstdio>

void showpic (char* p_name)
  {
  cbmpdatei bmpdatei (p_name);
  cfbscreen bildschirm ("jpeg Bild", bmpdatei.xanz, bmpdatei.yanz);
  signed long xanz= bmpdatei.xanz;
  if (xanz > bildschirm.xanz)
    xanz= bildschirm.xanz;
  signed long yanz= bmpdatei.yanz;
  if (yanz > bildschirm.yanz)
    yanz= bildschirm.yanz;
  signed long bmpadd= -bmpdatei.zeile - xanz*3; 
  char* bmppos= bmpdatei.vbild + bmpdatei.zeile*(yanz - 1);
  unsigned long* screenpos= bildschirm.fbuffer32;
  signed long screenadd= bildschirm.xanz;
  for (signed long ylauf= 0; ylauf < yanz; ylauf++)
    {
    for (signed long xlauf= 0; xlauf < xanz; xlauf++)  
      {  
      unsigned char red= bmppos[2];
      unsigned char green= bmppos[1];
      unsigned char blue= bmppos[0];
      screenpos[xlauf]= ( red << 16) | (green << 8) | (blue << 0);
      bmppos+= 3;
      }
    bmppos+= bmpadd;
    screenpos+= screenadd;
    }
  }

int main (int argc, char** argv)
  {
  if (argc != 2)
    return 0;
  showpic (argv[1]);
  getchar ();
  return 0;
  }
