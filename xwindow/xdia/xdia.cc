#include <iostream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <dirent.h>
#include <sys/times.h>
#include <unistd.h>
#include <stdlib.h>
#include <setjmp.h>
#include <stdio.h>
#include <string.h>
#include <jpeglib.h>

using namespace std;

struct my_error_mgr
  {
  struct jpeg_error_mgr pub;
  jmp_buf setjmp_buffer;
  };

typedef struct my_error_mgr* my_error_ptr;

METHODDEF (void) my_error_exit (j_common_ptr cinfo)
  {
  my_error_ptr myerr = (my_error_ptr) cinfo->err;
  (*cinfo->err->output_message) (cinfo);
  longjmp(myerr->setjmp_buffer, 1);
  }

struct cimage
  {
  signed long xanz, yanz, ftiefe;
  unsigned char* data;

  cimage (signed long px, signed long py, unsigned char* pdata)
    : xanz (px), yanz (py), data (pdata)
    {
    }
  };

struct cfenster
  {
  Display*   display;
  Visual*    visual;
  GC         gc;
  Window     window;
  Colormap   cmap;
  XEvent     event;
  bool       raised;

  signed long xanz,yanz;
  signed long ftiefe;
  unsigned long rbyte, gbyte, bbyte;
  unsigned long rpos, gpos, bpos;
  unsigned long rtiefe, gtiefe, btiefe;
  unsigned long rcut, gcut, bcut;

  cfenster (Display* pdisplay, signed long px, signed long py);
  ~cfenster ();
  bool tasteunten ();
  unsigned char* transimage8 (cimage& pimage);
  unsigned char* transimage8d (cimage& pimage);
  unsigned char* transimage16 (cimage& pimage);
  unsigned char* transimage24 (cimage& pimage);
  void raise (bool pon);
  bool zeigebild (cimage& pimage, signed long endzeit);
  };

cfenster::cfenster (Display* pdisplay, signed long px, signed long py)
  : xanz (px), yanz (py)
  {
  display= pdisplay;
  Screen* screen= DefaultScreenOfDisplay (display);
  visual= DefaultVisualOfScreen (screen);
  gc= DefaultGCOfScreen (screen);
  ftiefe= DefaultDepthOfScreen (screen);
  XSetWindowAttributes attr;
  attr.event_mask= ExposureMask | KeyPressMask | KeyReleaseMask;
  unsigned long mask= CWEventMask;
  switch (ftiefe)
    {
    case 8:
      {
      cmap= XCreateColormap (display, XDefaultRootWindow (display), visual, AllocAll);
      XColor defs[256];
      for (unsigned short cn= 0; cn < 256; ++cn)
        {
        defs[cn].pixel= cn;
        defs[cn].red= 9362*(cn >> 5);
        defs[cn].green= 9362*((cn >> 2) & 7);
        defs[cn].blue= 21845*(cn & 3);
        defs[cn].flags= DoRed | DoGreen | DoBlue;
        }
      XStoreColors (display, cmap, defs, 256);
      mask|= CWColormap;
      attr.colormap= cmap;
      break;
      }
    case 15: case 16: case 24: case 32:
      {
      unsigned long redmask= visual->red_mask;
      rpos= 0;
      while (!(redmask & 1))
        {
        rpos++;
        redmask >>= 1;
        }
      rbyte= rpos >> 3;
      rtiefe= 0;
      while (redmask & 1)
        {
        rtiefe++;
        redmask >>= 1;
        }
      rcut= 8 - rtiefe;
      unsigned long greenmask= visual->green_mask;
      gpos= 0;
      while (!(greenmask & 1))
        {
        gpos++;
        greenmask >>= 1;
        }
      gbyte= gpos >> 3;
      gtiefe= 0;
      while (greenmask & 1)
        {
        gtiefe++;
        greenmask >>= 1;
        }
      gcut= 8 - gtiefe;
      unsigned long bluemask= visual->blue_mask;
      bpos= 0;
      while (!(bluemask & 1))
        {
        bpos++;
        bluemask >>= 1;
        }
      bbyte= bpos >> 3;
      btiefe= 0;
      while (bluemask & 1)
        {
        btiefe++;
        bluemask >>= 1;
        }
      bcut= 8 - btiefe;
      break;
      }
    }
  window= XCreateWindow (display, XDefaultRootWindow (display), 0, 0, xanz, yanz, 0, ftiefe, InputOutput, visual, mask, &attr);
  XStoreName (display, window, "xdia");
  XCheckMaskEvent (display, ExposureMask, &event);
  raised= 0;
  }

cfenster::~cfenster ()
  {
  if (ftiefe == 8)
    XFreeColormap (display, cmap);
  XDestroyWindow (display, window);
  }

bool cfenster::tasteunten ()
  {
  char keytab[32];
  XQueryKeymap (display, keytab);
  for (signed long klauf= 0; klauf < 32; klauf++)
    if (keytab[klauf])
      return 1;
  return 0;
  }

unsigned char* cfenster::transimage8 (cimage& pimage)
  {
  unsigned char* data= new unsigned char[pimage.xanz*pimage.yanz];
  unsigned char* pufferpos= data;
  unsigned char* pbuffer= pimage.data;
  for (signed long ylauf= 0; ylauf < pimage.yanz; ylauf++)
    for (signed long xlauf= 0; xlauf < pimage.xanz; xlauf++)
      {
      unsigned char red= pbuffer[0] >> 5;
      unsigned char green= pbuffer[1] >> 5;
      unsigned char blue= pbuffer[2] >> 6;
      *pufferpos= (red << 5) | (green << 2) | (blue << 0);
      pbuffer+= 3;
      pufferpos++;
      }
  return (unsigned char*) data;
  }

unsigned char* cfenster::transimage8d (cimage& pimage)
  {
  unsigned char* data= new unsigned char[pimage.xanz*pimage.yanz];
  unsigned char* pufferpos= data;
  unsigned char* pbuffer= pimage.data;
  for (signed long ylauf= 0; ylauf < pimage.yanz; ylauf++)
    for (signed long xlauf= 0; xlauf < pimage.xanz; xlauf++)
      {
      signed long red= (pbuffer[0] + (random () >> 26) - 32) >> 5;
      signed long green= (pbuffer[1] + (random () >> 26) - 32) >> 5;
      signed long blue= (pbuffer[2] + (random () >> 25) - 64) >> 6;
      if (red < 0) red= 0;
      if (green < 0) green= 0;
      if (blue < 0) blue= 0;
      if (red > 255) red= 255;
      if (green > 255) green= 255;
      if (blue > 255) blue= 255;
      *pufferpos= (red << 5) | (green << 2) | (blue << 0);
      pbuffer+= 3;
      pufferpos++;
      }
  return (unsigned char*) data;
  }

unsigned char* cfenster::transimage16 (cimage& pimage)
  {
  unsigned short* data= new unsigned short[pimage.xanz*pimage.yanz];
  unsigned short* pufferpos= data;
  unsigned char* pbuffer= pimage.data;
  for (signed long ylauf= 0; ylauf < pimage.yanz; ylauf++)
    for (signed long xlauf= 0; xlauf < pimage.xanz; xlauf++)
      {
      unsigned char red= pbuffer[0] >> rcut;
      unsigned char green= pbuffer[1] >> gcut;
      unsigned char blue= pbuffer[2] >> bcut;
      *pufferpos= (red << rpos) | (green << gpos) | (blue << bpos);
      pbuffer+= 3;
      pufferpos++;
      }
  return (unsigned char*) data;
  }

unsigned char* cfenster::transimage24 (cimage& pimage)
  {
  unsigned char* data= new unsigned char[4*pimage.xanz*pimage.yanz];
  unsigned char* pufferpos= data;
  unsigned char* pbuffer= pimage.data;
  for (signed long ylauf= 0; ylauf < pimage.yanz; ylauf++)
    for (signed long xlauf= 0; xlauf < pimage.xanz; xlauf++)
      {
      pufferpos[rbyte]= pbuffer[0];
      pufferpos[gbyte]= pbuffer[1];
      pufferpos[bbyte]= pbuffer[2];
      pbuffer+= 3;
      pufferpos+= 4;
      }
  return data;
  }

void cfenster::raise (bool pon)
  {
  if ((pon && raised) || !(pon || raised))
    return;
  if (pon)
    {
    XMapRaised (display, window);
    raised= 1;
    }
    else
    {
    XUnmapWindow (display, window);
    raised= 0;
    }
  }

bool cfenster::zeigebild (cimage& pimage, signed long endzeit)
  {
  char* image= NULL;
  switch (ftiefe)
    {
    case 8:
      image= (char*) transimage8d (pimage);
      break;
    case 15: case 16:
      image= (char*) transimage16 (pimage);
      break;
    case 24: case 32:
      image= (char*) transimage24 (pimage);
      break;
    default:
      cout << "irrwitzige Farbtiefe von " << ftiefe << " Bit <- Fehler!\n";
      exit (32);
      break;
    }
  XImage* ximage= XCreateImage (display, visual, ftiefe, ZPixmap, 0, image, pimage.xanz, pimage.yanz, 8, 0);
  raise (1);
  XPutImage (display, window, gc, ximage, 0, 0, 0, 0, xanz, yanz);
  XFlush (display);
  tms zeit;
  signed long minzeit= times (&zeit) + 20;
  while (times (&zeit) < endzeit)
    {
    while (XCheckMaskEvent (display, ExposureMask, &event))
      XPutImage (display, window, gc, ximage, event.xexpose.x, event.xexpose.y, event.xexpose.x, event.xexpose.y, event.xexpose.width, event.xexpose.height);
    XFlush (display);
    while (XCheckMaskEvent (display, KeyPressMask | KeyReleaseMask, &event))
      if (times (&zeit) >= minzeit)
        {
        XDestroyImage (ximage);
        return 1;
        }
    if (tasteunten () && (times (&zeit) >= minzeit))
      {
      XDestroyImage (ximage);
      return 1;
      }
    usleep (20000);
    }
  XDestroyImage (ximage);
  return 0;
  }

struct cbilder
  {
  signed long anz;
  char** bnamen;

  cbilder (char* pverz);
  ~cbilder ();
  };

cbilder::cbilder (char* pverz)
  {
  signed long verzlaenge= 0;
  while (pverz[verzlaenge] != 0)
    verzlaenge++;
  char* verzn;
  if (pverz[verzlaenge - 1] != '/')
    {
    verzlaenge++;
    verzn= new char[verzlaenge];
    memcpy (verzn, pverz, verzlaenge - 1);
    verzn[verzlaenge - 1]= '/';
    }
    else
    {
    verzn= new char[verzlaenge];
    memcpy (verzn, pverz, verzlaenge);
    }
  DIR* verzeichnis= opendir (verzn);
  if (!verzeichnis)
    {
    cout << "  xdia: error opening directory\n\n";
    exit (16);
    }
  dirent* eintrag;
  anz= 0;
  while (1)
    {
    eintrag= readdir (verzeichnis);
    if (!eintrag)
      break;
    if (eintrag->d_name[0] == '.')
      continue;
    anz++;
    }
  rewinddir (verzeichnis);
  bnamen= new char*[anz];
  signed long bildz= 0;
  while (1)
    {
    eintrag= readdir (verzeichnis);
    if (!eintrag)
      break;
    if (eintrag->d_name[0] == '.')
      continue;
    signed long elaenge= 0;
    while (eintrag->d_name[elaenge] != 0)
      elaenge++;
    bnamen[bildz]= new char[verzlaenge + elaenge + 1];
    strcpy (bnamen[bildz], verzn);
    strcpy (bnamen[bildz] + verzlaenge, eintrag->d_name);
    bildz++;
    }
  closedir (verzeichnis);
  delete [] verzn;
  }

cbilder::~cbilder ()
  {
  for (signed long blauf= 0; blauf < anz; blauf++)
    delete [] bnamen[blauf];
  delete [] bnamen;
  }

cimage decodejpeg (char* pname)
  {
  FILE* infile= fopen (pname, "rb");
  if (infile == NULL)
    {
    cout << "kann Datei nicht oeffnen: " << pname << endl;
    return cimage (0, 0, NULL);
    }
  jpeg_decompress_struct cinfo;
  my_error_mgr jerr;
  cinfo.err= jpeg_std_error (&jerr.pub);
  jerr.pub.error_exit= my_error_exit;
  if (setjmp (jerr.setjmp_buffer))
    {
    jpeg_destroy_decompress (&cinfo);
    fclose (infile);
    return cimage (0, 0, NULL);
    }
  jpeg_create_decompress (&cinfo);
  jpeg_stdio_src (&cinfo, infile);
  jpeg_read_header (&cinfo, 1);
  jpeg_start_decompress (&cinfo);
  signed long xanz= cinfo.output_width;
  signed long yanz= cinfo.output_height;
  signed long rowstride = cinfo.output_width * cinfo.output_components;
  unsigned char* bildpuffer= new unsigned char[rowstride*yanz];
  unsigned char* pufferpos= bildpuffer;
  JSAMPARRAY buffer = (*cinfo.mem->alloc_sarray) ((j_common_ptr) &cinfo, JPOOL_IMAGE, rowstride, 1);
  while (cinfo.output_scanline < cinfo.output_height)
    {
    jpeg_read_scanlines (&cinfo, buffer, 1);
    memcpy (pufferpos, buffer[0], rowstride);
    pufferpos+= rowstride;
    }
  jpeg_finish_decompress (&cinfo);
  jpeg_destroy_decompress (&cinfo);
  fclose (infile);
  return cimage (xanz, yanz, bildpuffer);
  }

bool tasteunten (Display* pdisplay)
  {
  char keytab[32];
  XQueryKeymap (pdisplay, keytab);
  for (signed long klauf= 0; klauf < 32; klauf++)
    if (keytab[klauf])
      return 1;
  return 0;
  }

void zeigebilder (cbilder& pbilder, unsigned long pidletime, unsigned long pshowtime)
  {
  tms zeit;
  Display* display= XOpenDisplay (NULL);
  signed long bildpos= 0;
  while (1)
    {
    cfenster* fenster= new cfenster (display, 1024, 768);
    signed long endzeit= times (&zeit);
    while (1)
      {
      cimage image= decodejpeg (pbilder.bnamen[bildpos]);
      endzeit+= pshowtime*100;
      bool ret= fenster->zeigebild (image, endzeit);
      delete [] image.data;
      if (ret)
        break;
      bildpos+= 1;
      bildpos= bildpos % pbilder.anz;
      }
    delete fenster;
    endzeit+= pidletime*100;
    while (times (&zeit) < endzeit)
      {
      if (tasteunten (display))
        endzeit= times (&zeit) + pidletime*100;
      usleep (20000);
      }
    }
  }

int main (int argc, char** argv)
  {
  if (argc != 4)
    {
    cout << "  xdia <picturedir> <idletime> <showtime>\n";
    cout << "  eg: xdia pictures 10 5\n\n";
    return 1;
    }
  unsigned long idletime, showtime;
  if(!sscanf (argv[2], "%lu", &idletime))
    {
    cout << "  xdia: parseerror argument 2\n\n";
    return 2;
    }
  if(!sscanf (argv[3], "%lu", &showtime))
    {
    cout << "  xdia: parseerror argument 3\n\n";
    return 3;
    }
  cbilder bilder (argv[1]);
  zeigebilder (bilder, idletime, showtime);
  return 0;
  }
