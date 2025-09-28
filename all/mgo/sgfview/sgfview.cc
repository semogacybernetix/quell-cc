#include "../../../cc/screen/allscr.h"
#include "../../../xwindow/screen/xscr.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

struct cxgobrett
  {
  cbmpdatei*      c_feldbmp[65536];
  clscreen*       c_screen;

  unsigned long   c_xanz, c_yanz, c_feldanz, c_satzanz;
  unsigned char*  c_feld;

  cxgobrett (unsigned char p_xanz, unsigned char p_yanz, unsigned char* p_feld);
  ~cxgobrett ();
  void c_zeigefeld (unsigned char* p_feld);

  private:
  void c_putfeld (unsigned short p_pos);
  void c_putamsatz ();
  };

struct cgogame
  {
  unsigned long xanz, yanz, zanz;
  unsigned char* zdata;

  cgogame ();
  cgogame (char* pname);
  ~cgogame ();
  };

bool postupel (FILE* pdatei, unsigned char pc1, unsigned char pc2)
  {
  unsigned char c1, c2;
    do
    {
    if (!fread (&c1, 1, 1, pdatei))
      return false;
    if (c1 == pc1)
      {
      if (!fread (&c2, 1, 1, pdatei))
        return false;
      if (c2 == pc2)
        return true;
      }
    }
  while (c1 != pc1);
  return false;
  }

signed long readmove (FILE* pdatei, unsigned long pgroesse)
  {
  unsigned char c1, c2;
  fread (&c1, 1, 1, pdatei);
  if (c1 != '[')
    return -1;
  fread (&c1, 1, 1, pdatei);
  fread (&c2, 1, 1, pdatei);
  signed long ret= (c1 - 'a') * pgroesse + (c2 - 'a');
  fread (&c2, 1, 1, pdatei);
  return ret;
  }

cgogame::cgogame (char* pname)
  {
  FILE* datei= fopen (pname, "rb");
  postupel (datei, 'S', 'Z');
  unsigned char gr1, gr2;
  fread (&gr1, 1, 1, datei);
  fread (&gr1, 1, 1, datei);
  gr1-= '0';
  fread (&gr2, 1, 1, datei);
  if (gr2 != ']')
    gr1= gr1*10 + gr2 - '0';
  xanz= yanz= gr1;
  zdata= new unsigned char[xanz*yanz*500];
  for (unsigned long plauf= 0; plauf < xanz*yanz; plauf++)
    zdata[plauf]= 0;
  zanz= 0;
/*
  if (!postupel (datei, 'A', 'B'))
    {
    fseek (datei, 0, 0);
    }
*/
  printf ("ppp: %d\n", postupel (datei, ';', 'B'));
  while (postupel (datei, ';', 'B') )
    {
    printf ("zanz: %lu\n", zanz);
    zdata[xanz*yanz*zanz + readmove (datei, xanz*yanz)]= 1;
    zanz++;
    }
  }

cgogame::~cgogame ()
  {
  }

cxgobrett::cxgobrett (unsigned char p_xanz, unsigned char p_yanz, unsigned char* p_feld)
  {
  c_feldbmp[65535]= new cbmpdatei ("bmp/unguel.bmp");
  c_feldbmp[0x14]= new cbmpdatei ("bmp/liobl.bmp");
  c_feldbmp[0x15]= new cbmpdatei ("bmp/liobs.bmp");
  c_feldbmp[0x16]= new cbmpdatei ("bmp/liobw.bmp");
  c_feldbmp[0x18]= new cbmpdatei ("bmp/reobl.bmp");
  c_feldbmp[0x19]= new cbmpdatei ("bmp/reobs.bmp");
  c_feldbmp[0x1a]= new cbmpdatei ("bmp/reobw.bmp");
  c_feldbmp[0x24]= new cbmpdatei ("bmp/liunl.bmp");
  c_feldbmp[0x25]= new cbmpdatei ("bmp/liuns.bmp");
  c_feldbmp[0x26]= new cbmpdatei ("bmp/liunw.bmp");
  c_feldbmp[0x28]= new cbmpdatei ("bmp/reunl.bmp");
  c_feldbmp[0x29]= new cbmpdatei ("bmp/reuns.bmp");
  c_feldbmp[0x2a]= new cbmpdatei ("bmp/reunw.bmp");
  c_feldbmp[0x4]= new cbmpdatei ("bmp/lil.bmp");
  c_feldbmp[0x5]= new cbmpdatei ("bmp/lis.bmp");
  c_feldbmp[0x6]= new cbmpdatei ("bmp/liw.bmp");
  c_feldbmp[0x8]= new cbmpdatei ("bmp/rel.bmp");
  c_feldbmp[0x9]= new cbmpdatei ("bmp/res.bmp");
  c_feldbmp[0xa]= new cbmpdatei ("bmp/rew.bmp");
  c_feldbmp[0x10]= new cbmpdatei ("bmp/obl.bmp");
  c_feldbmp[0x11]= new cbmpdatei ("bmp/obs.bmp");
  c_feldbmp[0x12]= new cbmpdatei ("bmp/obw.bmp");
  c_feldbmp[0x20]= new cbmpdatei ("bmp/unl.bmp");
  c_feldbmp[0x21]= new cbmpdatei ("bmp/uns.bmp");
  c_feldbmp[0x22]= new cbmpdatei ("bmp/unw.bmp");
  c_feldbmp[0]= new cbmpdatei ("bmp/mil.bmp");
  c_feldbmp[1]= new cbmpdatei ("bmp/mis.bmp");
  c_feldbmp[2]= new cbmpdatei ("bmp/miw.bmp");
  c_xanz= p_xanz;
  c_yanz= p_yanz;
  c_feldanz= c_xanz*c_yanz;
  c_satzanz= c_feldanz + 1;
  c_feld= new unsigned char[c_satzanz];
  memcpy (c_feld, p_feld, c_satzanz);
  c_screen= new cxscreen ("gobrett", c_xanz*c_feldbmp[0]->xanz, 10 + c_yanz*c_feldbmp[0]->yanz);
  c_putamsatz ();
  for (unsigned short l_feld= 0; l_feld < c_feldanz; l_feld++)
    c_putfeld (l_feld);
  c_screen->flush ();
  }

cxgobrett::~cxgobrett ()
  {
  delete (c_feldbmp[65535]);
  delete (c_feldbmp[0x14]);
  delete (c_feldbmp[0x15]);
  delete (c_feldbmp[0x16]);
  delete (c_feldbmp[0x18]);
  delete (c_feldbmp[0x19]);
  delete (c_feldbmp[0x1a]);
  delete (c_feldbmp[0x24]);
  delete (c_feldbmp[0x25]);
  delete (c_feldbmp[0x26]);
  delete (c_feldbmp[0x28]);
  delete (c_feldbmp[0x29]);
  delete (c_feldbmp[0x2a]);
  delete (c_feldbmp[0x4]);
  delete (c_feldbmp[0x5]);
  delete (c_feldbmp[0x6]);
  delete (c_feldbmp[0x8]);
  delete (c_feldbmp[0x9]);
  delete (c_feldbmp[0xa]);
  delete (c_feldbmp[0x10]);
  delete (c_feldbmp[0x11]);
  delete (c_feldbmp[0x12]);
  delete (c_feldbmp[0x20]);
  delete (c_feldbmp[0x21]);
  delete (c_feldbmp[0x22]);
  delete (c_feldbmp[0]);
  delete (c_feldbmp[1]);
  delete (c_feldbmp[2]);
  delete (c_screen);
  }

void cxgobrett::c_zeigefeld (unsigned char* p_feld)
  {
  if (c_feld[c_feldanz] != p_feld[c_feldanz])
    {
    c_feld[c_feldanz]= p_feld[c_feldanz];
    c_putamsatz ();
    }
  for (unsigned char l_feld= 0; l_feld < c_feldanz; l_feld++)
    if (p_feld[l_feld] != c_feld[l_feld])
      {
      c_feld[l_feld]= p_feld[l_feld];
      c_putfeld (l_feld);
      }
  c_screen->flush ();
  }

void cxgobrett::c_putamsatz ()
  {
  unsigned short farbe= 255*(c_feld[c_feldanz] - 1);
  for (unsigned long l_y= c_screen->yanz - 10; l_y < c_screen->yanz; l_y++)
    for (unsigned long l_x= 0; l_x < c_screen->xanz; l_x++)
      c_screen->putpixel (l_x, l_y, farbe, farbe, farbe);
  }

void cxgobrett::c_putfeld (unsigned short p_pos)
  {
  unsigned char linksok= p_pos%c_xanz;
  unsigned char rechtsok= linksok + 1 - c_xanz;
  unsigned char obenok= p_pos/c_xanz;
  unsigned char untenok= obenok + 1 - c_yanz;
  unsigned short index= 4*!bool (linksok) + 8*!bool (rechtsok) + 16*!bool (untenok) + 32*!bool (obenok);
  index+= c_feld[p_pos];
  unsigned short xpos= (linksok)*c_feldbmp[0]->xanz;
  unsigned short ypos= (obenok)*c_feldbmp[0]->yanz;
  c_screen->putscreen (*c_feldbmp[index], xpos, ypos);
  }

signed int main (unsigned int argc, char** argv)
  {
  if (argc != 2)
    return 0;
  cgogame gogame (argv[1]);
  unsigned char* brett= new unsigned char[gogame.xanz*gogame.yanz + 1];
  for (unsigned long flauf= 0; flauf < gogame.xanz*gogame.yanz + 1; flauf++)
    {
    brett[flauf]= random () % 3;
    }
  cxgobrett gobrett (gogame.xanz, gogame.yanz, gogame.zdata);
  getchar ();
  return 0;
  }
