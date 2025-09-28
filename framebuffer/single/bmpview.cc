#include "../../cc/screen/bmpscr.h"
#include "../screen/fbscr.h"
#include <cstdio>

void showpic (char* p_name)
  {
  cbmpdatei bilddatei (p_name);
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
