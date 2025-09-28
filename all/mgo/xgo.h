#ifndef xgo_h
#define xgo_h

#include "../../cc/class/go.h"
#include "../../cc/screen/allscr.h"

struct cxgobrett
  {
  cbmpdatei*      c_feldbmp[65536];
  clscreen*       c_screen;

  unsigned char   c_xanz, c_yanz, c_feldanz, c_satzanz;
  unsigned char*  c_feld;

  cxgobrett (unsigned char p_xanz, unsigned char p_yanz, unsigned char* p_feld);
  ~cxgobrett ();
  void c_zeigefeld (unsigned char* p_feld);

  private:
  void c_putfeld (signed short p_pos);
  void c_putamsatz ();
  };

struct cxgobrauser
  {
  void c_brause (cgoanalyse& p_goanalyse);
  };

#endif
