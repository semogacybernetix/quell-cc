#include <X11/Xlib.h>
#include <cstdio>
#include <unistd.h>
#include <setjmp.h>

#include "jpeglib.h"  // muss unter den anderen includes stehen, sonst Übersetzungsfehler

unsigned long* bildpuffer;
unsigned long* pufferpos;
signed long xanz;
signed long yanz;
unsigned long ftiefe;
int row_stride;

void putscanline (unsigned char* pbuffer)
  {
  for (signed long xlauf= 0; xlauf < xanz; xlauf++)
    {
    unsigned char red= pbuffer[0];
    unsigned char green= pbuffer[1];
    unsigned char blue= pbuffer[2];
    *pufferpos= (red << 16) | (green << 8) | (blue << 0);
    pbuffer+= 3;
    pufferpos++;
    }
  }

struct my_error_mgr
  {
  struct jpeg_error_mgr pub; /* "public" fields */
  jmp_buf setjmp_buffer; /* for return to caller */
  };

typedef struct my_error_mgr * my_error_ptr;

METHODDEF (void)
my_error_exit (j_common_ptr cinfo)
  {
  my_error_ptr myerr = (my_error_ptr) cinfo->err;
  (*cinfo->err->output_message) (cinfo);
  longjmp(myerr->setjmp_buffer, 1);
  }

void readjpegfile (char * filename)
  {
  struct jpeg_decompress_struct cinfo;
  struct my_error_mgr jerr;
  FILE * infile;
  JSAMPARRAY buffer;
  int row_stride;

  if ((infile = fopen(filename, "rb")) == NULL)
    {
    fprintf(stderr, "can't open %s\n", filename);
    return;
    }

  Display* display0= XOpenDisplay (0);
  ftiefe= XDefaultDepth (display0, 0);
  if (ftiefe < 15)
    {
    printf ("Farbtiefe ist kleiner als 15 Bit\n");
    return;
    }

  cinfo.err = jpeg_std_error(&jerr.pub);
  jerr.pub.error_exit = my_error_exit;
  if (setjmp(jerr.setjmp_buffer))
    {
    jpeg_destroy_decompress(&cinfo);
    fclose(infile);
    return;
    }
  jpeg_create_decompress(&cinfo);
  jpeg_stdio_src(&cinfo, infile);
  (void) jpeg_read_header(&cinfo, TRUE);
  (void) jpeg_start_decompress(&cinfo);

  xanz= cinfo.output_width;
  yanz= cinfo.output_height;

  bildpuffer= new unsigned long[xanz*yanz];
  pufferpos= bildpuffer;

  row_stride = cinfo.output_width * cinfo.output_components;
  buffer = (*cinfo.mem->alloc_sarray)
  ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

  while (cinfo.output_scanline < cinfo.output_height)
    {
    (void) jpeg_read_scanlines(&cinfo, buffer, 1);
    putscanline (buffer[0]);
    }

  Visual* visual0= XDefaultVisual (display0, 0);
  XImage* image= XCreateImage (display0, visual0, ftiefe, ZPixmap, 0, (char*)bildpuffer, xanz, yanz, 8, 0);
  Window window0= XCreateWindow (display0, XDefaultRootWindow (display0), 0, 0,
                                 xanz, yanz, 0, ftiefe, InputOutput, 0, 0, 0);
  GC gc0= XCreateGC (display0, window0, 0, 0);
  XStoreName (display0, window0, filename);
  XMapRaised (display0, window0);
  XPutImage (display0, window0, gc0, image, 0, 0, 0, 0, xanz, yanz);
  delete[] bildpuffer;
  char keytab[32];
  bool taste= 0;
    do
    {
    usleep (50000);
    XQueryKeymap (display0, keytab);
    for (signed long klauf= 0; klauf < 32; klauf++)
      taste|= keytab[klauf];
    }
  while (!taste);

  (void) jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
  fclose(infile);
  }

int main (int argc, char** argv)
  {
  if (argc != 2)
    {
    printf ("JPEG-Datei als Parameter\n");
    return 0;
    }
  readjpegfile (argv[1]);
  return 0;
  }
