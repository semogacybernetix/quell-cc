#ifndef bmpscr_h
#define bmpscr_h

#include "vscr.h"

struct cbmpdatei : public clscreen8
  {
  cbmpdatei (const char* pname);
  cbmpdatei (const char* pname, integer px, integer py);
  ~cbmpdatei ();

  void getpixel (integer px, integer py, integer& pr, integer& pg, integer& pb);
  void putpixel (integer px, integer py, integer pr, integer pg, integer pb);
  void flush ();

  private:
  const char*           name;
  bool                  schreiben;
  unsigned char         head[0x36];
  unsigned char*        vbild;
  integer           zeile;
  integer           bsize;
  };

#endif
