// erzeugt ein Testbild zum Testen des Gamma-Wertes eines Bildschirms

#include "../screen/allscr.h"

void zeichnegamma ()
  {
  cbmpdatei gammabmp ("gamma.bmp", 600, 480);
  signed long f= 0;
  signed long xanz (gammabmp.xanz);
  signed long yanz (gammabmp.yanz);
  for (signed long ylauf= 0; ylauf < yanz; ylauf++)
    for (signed long xlauf= 0; xlauf < xanz; xlauf++)
      {
      if (ylauf == 0)
        f= 0;
      if ((ylauf >= 40) && (ylauf < 240))
        {
        if (xlauf == 0)
          f= 42;
        if (xlauf == 100)
          f= 84;
        if (xlauf == 200)
          f= 126;
        if (xlauf == 400)
          f= 168;
        if (xlauf == 500)
          f= 210;
        }
      if ((ylauf >= 240) && (ylauf < 440))
        {
        if ((xlauf >= 0) && (xlauf < 100))
          f= 84*((xlauf + ylauf) % 2);
        if ((xlauf >= 100) && (xlauf < 200))
          f= 168*((xlauf + ylauf) % 2);
        if ((xlauf >= 200) && (xlauf < 300))
          f= 252* ((xlauf + ylauf) % 2);
        if ((xlauf >= 300) && (xlauf < 400))
          f= 84 + 84*((xlauf + ylauf) % 2);
        if ((xlauf >= 400) && (xlauf < 500))
          f= 84 + 168*((xlauf + ylauf) % 2);
        if ((xlauf >= 500) && (xlauf < 600))
          f= 168 + 84*((xlauf + ylauf) % 2);
        }
      if (ylauf == 440)
        f= 255;
      gammabmp.putpixel (xlauf, ylauf, f, f, f);
      }
  }

int main ()
  {
  zeichnegamma ();
  return 0;
  }
