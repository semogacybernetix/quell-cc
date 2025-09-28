#ifndef memscr_h
#define memscr_h

#include "vscr.h"

struct cmemscreen8 : public clscreen8
  {
  cmemscreen8 (const char* pname, integer px, integer py);
  virtual ~cmemscreen8 ();
  void getpixel (integer px, integer py, integer& pr, integer& pg, integer& pb);
  void putpixel (integer px, integer py, integer pr, integer pg, integer pb);
  void flush ();

  private:
  unsigned long* vbild;
  };

#endif
