#ifndef nckbd_h
#define nckbd_h

#include "../../cc/keyboard/vkbd.h"

struct cnckeyboard : public clkeyboard
  {
  cnckeyboard ();
  virtual ~cnckeyboard ();
  void flush ();
  };

#endif
