#include "memscr.h"

cmemscreen8::cmemscreen8 (const char* pname, integer px, integer py)
  : clscreen8 (px, py)
  {
  pname= pname;
  vbild= new unsigned long[xanz*yanz];
  }

cmemscreen8::~cmemscreen8 ()
  {
  delete (vbild);
  }

void cmemscreen8::putpixel (integer px, integer py, integer pr, integer pg, integer pb)
  {
  if ((px < 0) || (py < 0) || (px >= xanz) || (py >= yanz))
    return;
  integer pos= py*xanz + px;
  unsigned char* bvbild= (unsigned char*) &vbild[pos];
  bvbild[0]= (unsigned char) (pb);
  bvbild[1]= (unsigned char) (pg);
  bvbild[2]= (unsigned char) (pr);
  }

void cmemscreen8::getpixel (integer px, integer py, integer& pr, integer& pg, integer& pb)
  {
  if ((px < 0) || (py < 0) || (px >= xanz) || (py >= yanz))
    {
    pr= 0;
    pg= 0;
    pb= 0;
    return;
    }
  integer pos= py*xanz + px;
  unsigned char* bvbild= (unsigned char*) &vbild[pos];
  pb= bvbild[0];
  pg= bvbild[1];
  pr= bvbild[2];
  }

void cmemscreen8::flush ()
  {
  }
