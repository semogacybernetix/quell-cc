#include "fbscr.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <linux/fb.h>

cfbscreen::cfbscreen (const char* pname, integer px, integer py)
  {
  pname+= 0;                                                      // pname benutzen, damit der Compiler nicht meckert
  px+= 0;
  py+= 0;
  dbuffer= open ("/dev/fb0", O_RDWR);
  fb_var_screeninfo info;
  ioctl (dbuffer, FBIOGET_VSCREENINFO, &info);

  // Auflösung des Framebuffers setzen
  xanz= px;
  yanz= py;
  fbxanz= info.xres;
  yanz1= yanz - 1;
  zanz=  info.bits_per_pixel/8;
  fbsize8= info.xres*info.yres*zanz;

  info.xoffset= 0;                                                // xoffset, yoffset werden haben keine Auswirkung
  info.yoffset= 0;
  ioctl (dbuffer, FBIOPAN_DISPLAY, &info);
  fbuffer8= (unsigned char*) mmap (0, fbsize8, PROT_READ|PROT_WRITE, MAP_SHARED, dbuffer, 0);
  }

cfbscreen::~cfbscreen ()
  {
  fb_var_screeninfo info;
  ioctl (dbuffer, FBIOPAN_DISPLAY, &info);
  munmap (fbuffer8, fbsize8);
  close (dbuffer);
  }

void cfbscreen::getpixel (integer px, integer py, integer& pr, integer& pg, integer& pb)
  {
  integer pos= zanz*((yanz1 - py)*fbxanz + px);
  unsigned char* bfbuffer= &fbuffer8[pos];
  pb= bfbuffer[0];
  pg= bfbuffer[1];
  pr= bfbuffer[2];
  }

void cfbscreen::putpixel (integer px, integer py, integer pr, integer pg, integer pb)
  {
  integer pos= zanz*((yanz1 - py)*fbxanz + px);
  unsigned char* bfbuffer= &fbuffer8[pos];
  if (zanz == 4)                                                  // Farbtiefe 32 Bit  8 Bit pro Farbe
    {
    bfbuffer[0]= (unsigned char) (pb);
    bfbuffer[1]= (unsigned char) (pg);
    bfbuffer[2]= (unsigned char) (pr);
    }
  if (zanz == 2)                                                  // Farbtiefe 16 Bit  5 Bit pro Farbe
    {
    bfbuffer[0]= (unsigned char) (pb >> 3);
    bfbuffer[1]= (unsigned char) (pr & 0b11111000);
    //bfbuffer[0]|= (unsigned char) (pg >> 2 << 5);                 // das niedrigste Grünbit wird nicht benutzt, da die höhere Grünauflösung bei Graustufen einen Grünstich bewirkt oder bei Abrundung einen Violettstich
    bfbuffer[0]|= (unsigned char) (pg >> 3 << 6);                 // Grün wird auch mit 5 Bit Auflösung benutzt um grünstichiges Grau zu vermeiden
    bfbuffer[1]|= (unsigned char) (pg >> 5);
    }
  }

void cfbscreen::flush ()
  {
  }
