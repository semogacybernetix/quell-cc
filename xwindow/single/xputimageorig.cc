#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>


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
  unsigned int image_width, image_height, image_byte_size, i, j;
  image_width = 640;
  image_height = 482;
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
  // Fill image data with random data
  for (i = 0; i < image_byte_size; i++)
    image_data[i] = (char) (random() % 256);
  Pixmap pixmap;
  pixmap= XCreatePixmap (display, root, image_width, image_height, depth);
  for (j= 0; j < 1000; j++)
    {
    for (i= 0; i < image_byte_size; i++)
      {
      image_data[i] = (char) (random() % 256);
      }
    
    // The following does not leak
    //XPutImage (display, win, gc, image, 0, 0, 50, 50, image_width, image_height);
    
    // The following does leak
    XPutImage (display, pixmap, gc, image, 0, 0, 0, 0, image_width, image_height);
    XCopyArea (display, pixmap, win, gc, 0,0, image_width, image_height, 50, 50);
    }
  status = XDestroyImage (image);
  // Comment the following line to allow valgrind to print interesting output
  status= XCloseDisplay (display);
  printf ("%d\n\n", status);
  return 0;
  }
