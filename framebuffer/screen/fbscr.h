#ifndef fbscr_h
#define fbscr_h

#include "../../cc/screen/vscr.h"

struct cfbscreen : public clscreen8
  {
  cfbscreen (const char* pname, integer px, integer py);
  virtual ~cfbscreen ();
  void getpixel (integer px, integer py, integer& pr, integer& pg, integer& pb);
  void putpixel (integer px, integer py, integer pr, integer pg, integer pb);
  void flush ();

  unsigned char*  fbuffer8;
  signed long   fbsize8;

  private:
  int             dbuffer;
  integer         yanz1;
  integer         zanz;      // Bytes Farbtiefe
  // signed long     xof, yof;      // gespeicherter Offset bei framebuffer Hardwarscrolling
  };

#endif
