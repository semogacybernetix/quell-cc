#ifndef xscr_h
#define xscr_h

#include "../../cc/screen/vscr.h"

// cxscreen ist nicht threadfest
struct cxscreen : public clscreen8
  {
  cxscreen (const char* pname, integer px, integer py);
  virtual ~cxscreen ();
  void putpixel (integer px, integer py, integer pr, integer pg, integer pb);
  void getpixel (integer px, integer py, integer &pr, integer &pg, integer &pb);
  void flush ();

  void getscreen (clscreen8 &pscreen, integer px, integer py);
  void getmaus (integer &paction, integer &px, integer &py, integer &pexp, integer &xmin, integer &ymin, integer &xmax, integer &ymax);
  bool checkexpose ();

  public:
  integer        rshift, gshift, bshift;
  integer        rdepth, gdepth, bdepth;
  integer        ypix1;
  };

struct cxmemoryscreen : public clscreen8
  {
  cxmemoryscreen (const char* pname, integer px, integer py);
  virtual ~cxmemoryscreen ();
  void putpixel (integer px, integer py, integer pr, integer pg, integer pb);
  void putpixelx (integer px, integer py, integer pr, integer pg, integer pb);
  void getpixel (integer px, integer py, integer &pr, integer &pg, integer &pb);
  void flush ();

  void getscreen (clscreen8 &pscreen, integer px, integer py);
  void getmaus (integer &paction, integer &px, integer &py, integer &pexp, integer &xmin, integer &ymin, integer &xmax, integer &ymax);
  bool checkexpose ();

  public:
  integer        rshift, gshift, bshift;
  integer        rdepth, gdepth, bdepth;
  integer        ypix1;
  
  integer*       bildspeicher;
  };

struct cximagescreen : public clscreen8
  {
  cximagescreen (const char* pname, integer px, integer py);
  virtual ~cximagescreen ();
  void putpixel (integer px, integer py, integer pr, integer pg, integer pb);
  void getpixel (integer px, integer py, integer &pr, integer &pg, integer &pb);
  void flush ();

  void getscreen (clscreen8 &pscreen, integer px, integer py);
  void getmaus (integer &paction, integer &px, integer &py, integer &pexp, integer &xmin, integer &ymin, integer &xmax, integer &ymax);
  bool checkexpose ();

  public:
  integer        rshift, gshift, bshift;
  integer        rdepth, gdepth, bdepth;
  integer        ypix1;

  private:
  char*          bild;
  };

#endif
