#include "xgo.h"
#include "../../xwindow/screen/xscr.h"

#include <cstdio>
#include <cstring>

cxgobrett::cxgobrett (unsigned char p_xanz, unsigned char p_yanz, unsigned char* p_feld)
  {
  c_feldbmp[65535]= new cbmpdatei ("gobmp/unguel.bmp");
  c_feldbmp[0x14]= new cbmpdatei ("gobmp/liobl.bmp");
  c_feldbmp[0x15]= new cbmpdatei ("gobmp/liobs.bmp");
  c_feldbmp[0x16]= new cbmpdatei ("gobmp/liobw.bmp");
  c_feldbmp[0x18]= new cbmpdatei ("gobmp/reobl.bmp");
  c_feldbmp[0x19]= new cbmpdatei ("gobmp/reobs.bmp");
  c_feldbmp[0x1a]= new cbmpdatei ("gobmp/reobw.bmp");
  c_feldbmp[0x24]= new cbmpdatei ("gobmp/liunl.bmp");
  c_feldbmp[0x25]= new cbmpdatei ("gobmp/liuns.bmp");
  c_feldbmp[0x26]= new cbmpdatei ("gobmp/liunw.bmp");
  c_feldbmp[0x28]= new cbmpdatei ("gobmp/reunl.bmp");
  c_feldbmp[0x29]= new cbmpdatei ("gobmp/reuns.bmp");
  c_feldbmp[0x2a]= new cbmpdatei ("gobmp/reunw.bmp");
  c_feldbmp[0x4]= new cbmpdatei ("gobmp/lil.bmp");
  c_feldbmp[0x5]= new cbmpdatei ("gobmp/lis.bmp");
  c_feldbmp[0x6]= new cbmpdatei ("gobmp/liw.bmp");
  c_feldbmp[0x8]= new cbmpdatei ("gobmp/rel.bmp");
  c_feldbmp[0x9]= new cbmpdatei ("gobmp/res.bmp");
  c_feldbmp[0xa]= new cbmpdatei ("gobmp/rew.bmp");
  c_feldbmp[0x10]= new cbmpdatei ("gobmp/obl.bmp");
  c_feldbmp[0x11]= new cbmpdatei ("gobmp/obs.bmp");
  c_feldbmp[0x12]= new cbmpdatei ("gobmp/obw.bmp");
  c_feldbmp[0x20]= new cbmpdatei ("gobmp/unl.bmp");
  c_feldbmp[0x21]= new cbmpdatei ("gobmp/uns.bmp");
  c_feldbmp[0x22]= new cbmpdatei ("gobmp/unw.bmp");
  c_feldbmp[0]= new cbmpdatei ("gobmp/mil.bmp");
  c_feldbmp[1]= new cbmpdatei ("gobmp/mis.bmp");
  c_feldbmp[2]= new cbmpdatei ("gobmp/miw.bmp");
  c_xanz= p_xanz;
  c_yanz= p_yanz;
  c_feldanz= c_xanz*c_yanz;
  c_satzanz= c_feldanz + 1;
  c_feld= new unsigned char[c_satzanz];
  memcpy (c_feld, p_feld, c_satzanz);
  c_screen= new cxscreen ("gobrett", c_xanz*c_feldbmp[0]->xanz, 10 + c_yanz*c_feldbmp[0]->yanz);
  c_putamsatz ();
  for (signed long l_feld= 0; l_feld < c_feldanz; l_feld++)
    c_putfeld (l_feld);
  c_screen->flush ();
  }

cxgobrett::~cxgobrett ()
  {
  /*
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
  */
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
  signed short farbe= 255*(c_feld[c_feldanz] - 1);
  for (signed long l_y= c_screen->yanz - 10; l_y < c_screen->yanz; l_y++)
    for (signed long l_x= 0; l_x < c_screen->xanz; l_x++)
      c_screen->putpixel (l_x, l_y, farbe, farbe, farbe);
  }

void cxgobrett::c_putfeld (signed short p_pos)
  {
  unsigned char linksok= p_pos%c_xanz;
  unsigned char rechtsok= linksok + 1 - c_xanz;
  unsigned char obenok= p_pos/c_xanz;
  unsigned char untenok= obenok + 1 - c_yanz;
  signed short index= 4*!bool (linksok) + 8*!bool (rechtsok) + 16*!bool (untenok) + 32*!bool (obenok);
  index+= c_feld[p_pos];
  signed short xpos= (linksok)*c_feldbmp[0]->xanz;
  signed short ypos= (obenok)*c_feldbmp[0]->yanz;
  c_screen->putscreen (*c_feldbmp[index], xpos, ypos);
  }

void cxgobrauser::c_brause (cgoanalyse& p_goanalyse)
  {
  signed long rets= 0;  // initialisieren, damit Compiler nicht meckert dass unitialisiert
  rets++;               // benutzen, damit Compiler nicht meckert dass unbenutzt
  cxgobrett xgobrett (p_goanalyse.c_xanz, p_goanalyse.c_yanz, p_goanalyse.c_ausgangsstellung);
  memcpy (p_goanalyse.c_feld, p_goanalyse.c_ausgangsstellung, p_goanalyse.c_satzanz);
  unsigned char* afeld= new unsigned char[p_goanalyse.c_satzanz*256];
  unsigned char index= 0;
    do
    {
    memcpy (afeld + p_goanalyse.c_satzanz*index, p_goanalyse.c_feld, p_goanalyse.c_satzanz);
    unsigned char bewertung= p_goanalyse.c_getbewertung ();
    printf ("\nBewertung: %4d  Satztiefe: %d\n\n", bewertung, index);
    if (index)
      printf ("zurueck:  -2\n");
    *p_goanalyse.c_zamsatz^= p_goanalyse.c_invfarbe;
    bewertung= p_goanalyse.c_getbewertung ();
    printf ("Passen:   -1  Bewertung: %4d\n", bewertung);
    *p_goanalyse.c_zamsatz^= p_goanalyse.c_invfarbe;
    for (unsigned char l_satz= 0; l_satz < p_goanalyse.c_feldanz; l_satz++)
      {
      if ((l_satz == p_goanalyse.c_notset) || (p_goanalyse.c_feld[l_satz] != p_goanalyse.c_leer))
        continue;
      if (p_goanalyse.c_setze (l_satz))
        {
        if ((p_goanalyse.c_feld[p_goanalyse.c_killgroup1] != p_goanalyse.c_leer) &&
            (p_goanalyse.c_feld[p_goanalyse.c_killgroup2] != p_goanalyse.c_leer) &&
            (p_goanalyse.c_feld[p_goanalyse.c_killgroup3] != p_goanalyse.c_leer))
          {
          bewertung= p_goanalyse.c_getbewertung ();
          printf ("Satz:   %4d  Bewertung: %4d\n", l_satz, bewertung);
          }
          else
          printf ("Satz:   %4d  Bewertung: %4d\n", l_satz, 0);
        }
      memcpy (p_goanalyse.c_feld, afeld + p_goanalyse.c_satzanz*index, p_goanalyse.c_satzanz);
      }
      signed long satznr;
      rets= scanf ("%ld", &satznr);
    switch (satznr)
      {
      case (signed long) -3:
        delete (afeld);
        return;
      case (signed long) -2:
        if (index)
          index--;
        memcpy (p_goanalyse.c_feld, afeld + p_goanalyse.c_satzanz*index, p_goanalyse.c_satzanz);
        break;
      case (signed long) -1:
        *p_goanalyse.c_zamsatz^= p_goanalyse.c_invfarbe;
        index++;
        break;
      default:
        if ((satznr < p_goanalyse.c_feldanz) &&
            (p_goanalyse.c_feld[satznr] == p_goanalyse.c_leer) &&
            (satznr != p_goanalyse.c_notset))
          {
          if (!p_goanalyse.c_setze (satznr) ||
             (p_goanalyse.c_feld[p_goanalyse.c_killgroup1] == p_goanalyse.c_leer) ||
             (p_goanalyse.c_feld[p_goanalyse.c_killgroup2] == p_goanalyse.c_leer) ||
             (p_goanalyse.c_feld[p_goanalyse.c_killgroup3] == p_goanalyse.c_leer))
            {
            memcpy (p_goanalyse.c_feld, afeld + p_goanalyse.c_satzanz*index, p_goanalyse.c_satzanz);
            continue;
            }
          index++;
          }
      }
    xgobrett.c_zeigefeld (p_goanalyse.c_feld);
    }
  while (1);
  }
