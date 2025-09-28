#include <stdio.h>
#include <unistd.h>

using namespace std;

extern "C"
  {
  #include "jpeglib.h"
  #include <X11/Xlib.h>
  }

#include <setjmp.h>
#include "../screen/fbscr.h"

cfbscreen fbscreen ("bla", 1024, 768);
unsigned long* screenpos= fbscreen.fbuffer32;
unsigned long* nscreenpos= fbscreen.fbuffer32 + fbscreen.xanz*fbscreen.yanz;
signed long zeileadd= fbscreen.xanz;
signed long xanz;
int row_stride;     

void putscanline (unsigned char* pbuffer)
  {
  if (screenpos >= nscreenpos)
    return;
  for (signed long xlauf= 0; xlauf < xanz; xlauf++)
    {
    unsigned char red= pbuffer[0];
    unsigned char green= pbuffer[1];
    unsigned char blue= pbuffer[2];
    screenpos[xlauf]= (red << 16) | (green << 8) | (blue << 0);
    pbuffer+= 3;
    }
  screenpos+= zeileadd;
  }

void putscanline2 (unsigned char* pbuffer)
  {
  if (screenpos >= nscreenpos)
    return;
  for (signed long xlauf= 0; xlauf < xanz; xlauf++)
    {
    unsigned char gray= *pbuffer;
    screenpos[xlauf]= (gray << 16) | (gray << 8) | (gray << 0);
    pbuffer++;
    }
  screenpos+= zeileadd;
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

  if ((infile = fopen(filename, "rb")) == NULL)
    {
    fprintf(stderr, "can't open %s\n", filename);
    return;
    }
  cinfo.err = jpeg_std_error (&jerr.pub);
  jerr.pub.error_exit = my_error_exit;
  if (setjmp (jerr.setjmp_buffer))
    {
    jpeg_destroy_decompress (&cinfo);
    fclose(infile);
    return;
    }
  jpeg_create_decompress (&cinfo);
  jpeg_stdio_src (&cinfo, infile);
  (void) jpeg_read_header (&cinfo, TRUE);
  (void) jpeg_start_decompress (&cinfo);
  xanz= cinfo.output_width;
  row_stride = cinfo.output_width * cinfo.output_components;
  xanz= cinfo.output_width;
  if (xanz > fbscreen.xanz)
    xanz= fbscreen.xanz;
  buffer = (*cinfo.mem->alloc_sarray) ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
  unsigned long ymax= cinfo.output_height;
  if (cinfo.output_components == 3)
    while (cinfo.output_scanline < ymax)
      {
      (void) jpeg_read_scanlines(&cinfo, buffer, 1);
      putscanline (buffer[0]);
      }
  if (cinfo.output_components == 1)
    while (cinfo.output_scanline < ymax)
      {
      (void) jpeg_read_scanlines(&cinfo, buffer, 1);
      putscanline2 (buffer[0]);
      }
  (void) jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
  fclose(infile);
  }

int main (int argc, char** argv)
  {
  readjpegfile (argv[1]);
  getchar ();
  return 0;
  }
