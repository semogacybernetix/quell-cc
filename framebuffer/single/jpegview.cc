#include "../../cc/screen/jpegscr.h"
#include "../screen/fbscr.h"
#include <stdio.h>

void showpic (char* p_name)
  {
  cjpegdatei bilddatei (p_name);
  cfbscreen bildschirm ("jpeg Bild", bilddatei.xanz, bilddatei.yanz);
  bildschirm.putscreen (bilddatei, 0, 0);
  }

int main (int argc, char** argv)
  {
  if (argc != 2)
    return 0;
  showpic (argv[1]);
  getchar ();
  return 0;
  }
