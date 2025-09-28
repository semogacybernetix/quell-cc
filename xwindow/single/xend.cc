#include <cstdio>
#include <X11/Xlib.h>

void window ()
  {
  Display* display0= XOpenDisplay (0);
  Window window0= XCreateWindow (display0, XDefaultRootWindow (display0), 0, 0, 500, 200, 0, 24, InputOutput, 0, 0, 0);
  XMapRaised (display0, window0);
  XFlush (display0);
  }

void mauswindow ()
  {
  XSetWindowAttributes attr0;
  attr0.event_mask= ExposureMask | ButtonPressMask | ButtonReleaseMask;
  unsigned long mask0= CWEventMask;
  Display* display0= XOpenDisplay (0);
  Window window0= XCreateWindow (display0, XDefaultRootWindow (display0), 0, 0, 500, 200, 0, XDefaultDepth (display0, 0), InputOutput, 0, mask0, &attr0);
  XMapRaised (display0, window0);
  XFlush (display0);

  int schleife= 1;
  XEvent report;
  while (schleife)
    {
    XNextEvent (display0, &report);
    if (report.type == ButtonPress)
      printf (" X: %4d Y: %4d B: %4d\n", report.xbutton.x, report.xbutton.y, report.xbutton.button);
    if (report.type == ButtonRelease)
      printf (" X: %4d Y: %4d B: %4d\n", report.xbutton.x, report.xbutton.y, report.xbutton.button);
    if (report.type == Expose)
      printf ("Expose  X: %4d Y: %4d xanz: %4d yanz: %4d\n", report.xexpose.x, report.xexpose.y, report.xexpose.width, report.xexpose.height);
    }

  }

int main ()
  {
  mauswindow ();
  return 0;
  }
