#include "../../cc/screen/allscr.h"
#include "../../xwindow/screen/xscr.h"
#include "../../xwindow/keyboard/xkbd.h"
#include <unistd.h>

void showpic (char* p_name)
  {
  cbmpdatei bilddatei (p_name);
  cxscreen bildschirm ("bmp Bild", bilddatei.xanz, bilddatei.yanz);
  bildschirm.putscreen (bilddatei, 0, 0);
  cxkeyboard keyboard;
    do
    {
    keyboard.flush ();
    usleep (50000);
    }
  while (!keyboard.getkey (0, 0));
  }

int main (int argc, char** argv)
  {
  if (argc != 2)
    return 0;
  showpic (argv[1]);
  return 0;
  }
