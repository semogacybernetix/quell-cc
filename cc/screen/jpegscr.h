#ifndef jpegscr_h
#define jpegscr_h

#include "vscr.h"

struct cjpegdatei : public clscreen8
  {
  cjpegdatei (const char* pname);
  cjpegdatei (const char* pname, integer px, integer py);
  virtual ~cjpegdatei ();
  void putpixel (integer px, integer py, integer pr, integer pg, integer pb);
  void getpixel (integer px, integer py, integer& pr, integer& pg, integer& pb);
  void hintergrund (unsigned char iwert);
  void putscreen (clscreen8& pscreen);
  void flush ();

  private:
  const char*          name;
  bool                 schreiben;
  unsigned char*       vbild;
  integer              bsize;
  };

#endif
