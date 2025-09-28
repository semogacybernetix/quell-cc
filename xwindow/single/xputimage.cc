#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>


void putpixel (char* imagedata, signed long px, signed long py, signed long pr, signed long pg, signed long pb)
  {
  signed long pos;
  pos = 4*(px + py*640);
  imagedata[pos]= pr;
  imagedata[pos+1]= pg;
  imagedata[pos+2]= pb;
  }

int main ()
  {
  Display* display;
  int screen_number, depth, bitmap_pad, status;
  unsigned long white;
  unsigned long black;
  Window root, win;
  GC gc;
  Visual* visual;
  XImage* image;
  char* image_data;
  unsigned int image_width, image_height, image_byte_size;
 
  image_width = 640;
  image_height = 480;

  display = XOpenDisplay (NULL);
  if (! display)
    {
    return 1;
    }

  screen_number= DefaultScreen (display);
  depth= DefaultDepth (display, screen_number);
  visual= DefaultVisual (display, screen_number);
  gc= DefaultGC (display, screen_number);
  bitmap_pad = BitmapPad (display);
  white= WhitePixel (display, screen_number);
  black= BlackPixel (display, screen_number);
  root= DefaultRootWindow (display);

  win= XCreateSimpleWindow (display, root, 50, 50, 800, 800, 0, black, white);
  XMapWindow (display, win);
  image= XCreateImage (display, visual, depth, ZPixmap, 0, NULL, image_width, image_height, bitmap_pad, 0);

  printf("depth : %d\nbitmap_pad : %d\nimage bpp : %d\n", depth, bitmap_pad, image->bits_per_pixel);

  image_byte_size= image_width*image_height*image->bits_per_pixel/8;
  image_data= (char*) malloc (image_byte_size);
  image->data= image_data;   // hier wird der Grafikspeicher an das XImage gebunden

  for (signed long i = 0; i < image_byte_size; i++)
    image_data[i] = 0;

  XPutImage (display, win, gc, image, 0, 0, 50, 50, image_width, image_height);

  for (signed long lauf= 0; lauf < 480; lauf++)
    putpixel (image_data, lauf, lauf, 255, 255, 255);
  getchar ();
  XPutImage (display, win, gc, image, 0, 0, 50, 50, image_width, image_height);
  getchar ();
  status= XDestroyImage (image);
  status= XCloseDisplay (display);
  printf ("%d\n\n", status);
  return 0;
  }
