#include <X11/Xlib.h>
#include <unistd.h>
#include <cstdio>

void scankeys ()
  {
  Display* display0= XOpenDisplay (0);
  char keytab[32];
  bool taste= 0;
  while (1)
    {
    while (!taste)
      {
      taste= 0;
      XQueryKeymap (display0, keytab);
      for (signed long tlauf=0; tlauf < 32; tlauf++)
        {
        if (keytab[tlauf])
          {
          taste= 1;
          printf ("%10ld %4x\n", tlauf, (unsigned char) (keytab[tlauf]));
          }
        }
      usleep (50000);
      }
    while (taste)
      {
      taste= 0;
      XQueryKeymap (display0, keytab);
      for (signed long tlauf= 0; tlauf < 32; tlauf++)
        {
        if (keytab[tlauf])
          taste= 1;
        }
      usleep (50000);
      }
    }
  }

int main ()
  {
  scankeys ();
  return 0;
  }
