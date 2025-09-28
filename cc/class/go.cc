#include "go.h"

#include <cstring>    // memcpy
#include <cstdlib>    // calloc
#include <cstdio>     // fread

bool cgoanalyse::c_gruppefrei (unsigned char p_feldnr)
  {
  unsigned char feldalt= c_feld[p_feldnr];
  unsigned char feldneu= feldalt | c_mask;
  c_feld[p_feldnr]= feldneu;
  unsigned char randok= p_feldnr%c_xanz;
  if (randok)
    {
    unsigned char daneben= (unsigned char) (p_feldnr - 1);
    unsigned char felddaneben= c_feld[daneben];
    if ((felddaneben == c_leer) ||
       ((felddaneben != feldalt) && (felddaneben != feldneu) && ((felddaneben & 3) == feldalt)) ||
       ((felddaneben == feldalt) && c_gruppefrei (daneben)))
      return true;
    }
  randok= (unsigned char) (randok + 1 - c_xanz);
  if (randok)
    {
    unsigned char daneben= (unsigned char) (p_feldnr + 1);
    unsigned char felddaneben= c_feld[daneben];
    if ((felddaneben == c_leer) ||
       ((felddaneben != feldalt) && (felddaneben != feldneu) && ((felddaneben & 3) == feldalt)) ||
       ((felddaneben == feldalt) && c_gruppefrei (daneben)))
      return true;
    }
  randok= p_feldnr/c_xanz;
  if (randok)
    {
    unsigned char daneben= (unsigned char) (p_feldnr - c_xanz);
    unsigned char felddaneben= c_feld[daneben];
    if ((felddaneben == c_leer) ||
       ((felddaneben != feldalt) && (felddaneben != feldneu) && ((felddaneben & 3) == feldalt)) ||
       ((felddaneben == feldalt) && c_gruppefrei (daneben)))
      return true;
    }
  randok= (unsigned char) (randok + 1 - c_yanz);
  if (randok)
    {
    unsigned char daneben= (unsigned char) (p_feldnr + c_xanz);
    unsigned char felddaneben= c_feld[daneben];
    if ((felddaneben == c_leer) ||
       ((felddaneben != feldalt) && (felddaneben != feldneu) && ((felddaneben & 3) == feldalt)) ||
       ((felddaneben == feldalt) && c_gruppefrei (daneben)))
      return true;
    }
  return false;
  }

bool cgoanalyse::c_setze (unsigned char p_satz)
  {
  c_feld[p_satz]= *c_zamsatz;
  unsigned char linksok=     p_satz%c_xanz;
  unsigned char rechtsok=    (unsigned char) (linksok + 1 - c_xanz);
  unsigned char obenok=      p_satz/c_xanz;
  unsigned char untenok=     (unsigned char) (obenok +  1 - c_yanz);
  unsigned char links=       (unsigned char) (p_satz - 1);
  unsigned char rechts=      (unsigned char) (p_satz + 1);
  unsigned char oben=        (unsigned char) (p_satz - c_xanz);
  unsigned char unten=       (unsigned char) (p_satz + c_xanz);
  unsigned char gegenfarbe=  *c_zamsatz ^ c_invfarbe;
  unsigned char gefmask= 0;
  if (linksok && (c_feld[links] == gegenfarbe))
    {
    c_mask= 8;
    if (!c_gruppefrei (links))
      gefmask|= 8;
    }
  if (rechtsok && (c_feld[rechts] == gegenfarbe))
    {
    c_mask= 16;
    if (!c_gruppefrei (rechts))
      gefmask|= 16;
    }
  if (obenok && (c_feld[oben] == gegenfarbe))
    {
    c_mask= 32;
    if (!c_gruppefrei (oben))
      gefmask|= 32;
    }
  if (untenok && (c_feld[unten] == gegenfarbe))
    {
    c_mask= 64;
    if (!c_gruppefrei (unten))
      gefmask|= 64;
    }
  if (!gefmask)
    {
    c_mask= 128;
    if (!c_gruppefrei (p_satz))
      return false;
    }
  for (unsigned char l_feld= 0; l_feld < c_feldanz; l_feld++)
    if (c_feld[l_feld] & gefmask)
        c_feld[l_feld]= c_leer;
      else
        c_feld[l_feld]&= 7;
  *c_zamsatz= gegenfarbe;
  return true;
  }

bool cgoanalyse::c_addfeld ()
  {
  bool add= false;
  unsigned long* zbaumpos= (unsigned long*) &c_zorigin;
  for (unsigned char l_feld= 0; l_feld < c_satzanz; l_feld++)
    {
    if (!*zbaumpos)
      {
      *zbaumpos= (unsigned long) calloc (3, 4);
      add= true;
      }
    zbaumpos= (unsigned long*) *zbaumpos + c_feld[l_feld];
    }
  if (!*zbaumpos)
    {
    *zbaumpos= 255;
    add= true;
    }
  if (add)
    c_anzstellungen++;
  return add;
  }

void cgoanalyse::c_addstellungen ()
  {
  unsigned char* afeld= new unsigned char[c_satzanz];
  memcpy (afeld, c_feld, c_satzanz);
  *c_zamsatz^= c_invfarbe;
  if (c_addfeld ())
    c_addstellungen ();
  memcpy (c_feld, afeld, c_satzanz);
  for (unsigned char l_satz= 0; l_satz < c_feldanz; l_satz++)
    {
    if ((c_feld[l_satz] != c_leer) || (l_satz == c_notset))
      continue;
    if (c_setze (l_satz))
      {
      if ((c_feld[c_killgroup1] != c_leer) &&
          (c_feld[c_killgroup2] != c_leer) &&
          (c_feld[c_killgroup3] != c_leer))
        if (c_addfeld ())
          c_addstellungen ();
      }
      else
      {
      memcpy (c_feld, afeld, c_satzanz);
      c_setbewertung (1);
      continue;
      }
    memcpy (c_feld, afeld, c_satzanz);
    }
  }

void cgoanalyse::c_setanfangsfeld (unsigned char p_feld)
  {
  unsigned long* zbaumpos= c_zorigin;
  for (unsigned long l_feld= 0; l_feld < c_satzanz; l_feld++)
    {
    if (l_feld < p_feld)
      {
      zbaumpos= (unsigned long*) zbaumpos[c_feld[l_feld]];
      continue;
      }
    if (zbaumpos[0])
      {
      c_feld[l_feld]= 0;
      zbaumpos= (unsigned long*) zbaumpos[0];
      continue;
      }
    if (zbaumpos[1])
      {
      c_feld[l_feld]= 1;
      zbaumpos= (unsigned long*) zbaumpos[1];
      continue;
      }
    c_feld[l_feld]= 2;
    zbaumpos= (unsigned long*) zbaumpos[2];
    }
  }

bool cgoanalyse::c_setnextfeld (unsigned long* p_baumpos, unsigned char p_feld)
  {
  if (p_feld == c_satzanz)
    return false;
  if (c_setnextfeld ((unsigned long*) p_baumpos[c_feld[p_feld]], (unsigned char) (p_feld + 1)))
    return true;
  unsigned char feld= c_feld[p_feld];
  if (feld == c_weiss)
    return false;
  if (feld == c_schwarz)
    {
    if (p_baumpos[c_weiss])
      {
      c_feld[p_feld]= c_weiss;
      c_setanfangsfeld ((unsigned char) (p_feld + 1));
      return true;
      }
      else
      return false;
 }
  if (p_baumpos[c_schwarz])
    {
    c_feld[p_feld]= c_schwarz;
    c_setanfangsfeld ((unsigned char) (p_feld + 1));
    return true;
    }
  if (p_baumpos[c_weiss])
    {
    c_feld[p_feld]= c_weiss;
    c_setanfangsfeld ((unsigned char) (p_feld + 1));
    return true;
    }
  return false;
  }

unsigned char cgoanalyse::c_getbewertung ()
  {
  unsigned long* zbaumpos= c_zorigin;
  for (unsigned char l_feld= 0; l_feld < c_feldanz; l_feld++)
    zbaumpos= (unsigned long*) zbaumpos[c_feld[l_feld]];
  return (unsigned char) zbaumpos[*c_zamsatz];
  }

void cgoanalyse::c_setbewertung (unsigned char p_bewertung)
  {
  unsigned long* zbaumpos= c_zorigin;
  for (unsigned char l_feld= 0; l_feld < c_feldanz; l_feld++)
    zbaumpos= (unsigned long*) zbaumpos[c_feld[l_feld]];
  zbaumpos[*c_zamsatz]= (unsigned long) p_bewertung;
  }

unsigned char cgoanalyse::c_bewertemin ()
  {
  unsigned char* afeld= new unsigned char[c_satzanz];
  memcpy (afeld, c_feld, c_satzanz);
  *c_zamsatz^= c_invfarbe;
  unsigned char bewmin= c_getbewertung ();
  *c_zamsatz^= c_invfarbe;
  if (bewmin == 1)
    return 1;
  for (unsigned char l_satz= 0; l_satz < c_feldanz; l_satz++)
    {
    if ((c_feld[l_satz] != c_leer) || (l_satz == c_notset))
      continue;
    if (c_setze (l_satz))
      {
      unsigned char bewertung= c_getbewertung ();
      if (bewertung == 1)
        {
        memcpy (c_feld, afeld, c_satzanz);
 return 1;
 }
      if (bewertung < bewmin)
        bewmin= bewertung;
      }
    memcpy (c_feld, afeld, c_satzanz);
    }
  return bewmin;
  }

unsigned char cgoanalyse::c_bewertemax ()
  {
  unsigned char* afeld= new unsigned char[c_satzanz];
  memcpy (afeld, c_feld, c_satzanz);
  *c_zamsatz^= c_invfarbe;
  unsigned char bewmax= c_getbewertung ();
  *c_zamsatz^= c_invfarbe;
  if (bewmax == 255)
    return 255;
  for (unsigned char l_satz= 0; l_satz < c_feldanz; l_satz++)
    {
    if ((c_feld[l_satz] != c_leer) || (l_satz == c_notset))
      continue;
    if (c_setze (l_satz))
      {
      unsigned char bewertung= c_getbewertung ();
      if (bewertung == 255)
        {
        memcpy (c_feld, afeld, c_satzanz);
 return 255;
 }
      if (bewertung > bewmax)
        bewmax= bewertung;
      }
    memcpy (c_feld, afeld, c_satzanz);
    }
  return bewmax;
  }

bool cgoanalyse::c_bewerteebene (unsigned char p_bewfarbe, bool p_min)
  {
  c_setanfangsfeld (0);
  bool bewertet= false;
  if (p_min)
    {
      do
      {
      if ((*c_zamsatz == p_bewfarbe) && (c_getbewertung () == 255))
        {
        unsigned char bewertung;
        bewertung= c_bewertemin ();
        if (bewertung != 255)
          {
          c_setbewertung ((unsigned char) (bewertung + 1));
          bewertet= true;
          }
        }
      }
    while (c_setnextfeld (c_zorigin, 0));
    return bewertet;
    }
    do
    {
    if ((*c_zamsatz == p_bewfarbe) && (c_getbewertung () == 255))
      {
      unsigned char bewertung;
      bewertung= c_bewertemax ();
      if (bewertung != 255)
        {
        c_setbewertung ((unsigned char) (bewertung + 1));
        bewertet= true;
        }
      }
    }
  while (c_setnextfeld (c_zorigin, 0));
  return bewertet;
  }

void cgoanalyse::c_bewertealles ()
  {
  unsigned char bewfarbe= c_feld[c_killgroup1];
  unsigned char beftiefe= 0;
  bool min= false;
  while (c_bewerteebene (bewfarbe, min))
    {
    beftiefe++;
    printf ("Bewertungstiefe: %4d\n", beftiefe);
    bewfarbe^= c_invfarbe;
    min^= true;
    }
  }

bool lookfor (FILE* p_datei, unsigned char p_token)
  {
  signed long fret;
  unsigned char rtoken;
  if (!(fret= fread (&rtoken, 1, 1, p_datei)))
    return false;
  while (rtoken != p_token)
    if (!(fret= fread (&rtoken, 1, 1, p_datei)))
      return false;
  return true;
  }

cgoanalyse::cgoanalyse (char* p_name)
  {
  signed long fret= 0;  // initialisieren, damit Compiler nicht meckert dass unitialisiert
  fret++;               // benutzen, damit Compiler nicht meckert dass unbenutzt
  unsigned char token, gr1, gr2;
  FILE* datei= fopen (p_name, "rb");
  lookfor (datei, 'x');
  fret= fread (&token, 1, 1, datei);
  c_xanz= (unsigned char) (token - '1' + 1);
  lookfor (datei, 'y');
  fret= fread (&token, 1, 1, datei);
  c_yanz= (unsigned char) (token - '1' + 1);
  c_feldanz= (unsigned char) (c_xanz*c_yanz);
  c_satzanz= (unsigned char) (c_feldanz + 1);
  c_zorigin= 0;
  c_ausgangsstellung= new unsigned char[c_satzanz];
  c_anzstellungen= 0;
  lookfor (datei, 's');
  fret= fread (&token, 1, 1, datei);
  if (token == 'w')
    c_ausgangsstellung[c_feldanz]= c_weiss;
    else
    c_ausgangsstellung[c_feldanz]= c_schwarz;
  lookfor (datei, 'k');
  fret= fread (&gr1, 1, 1, datei);
  fret= fread (&gr2, 1, 1, datei);
  gr1= (unsigned char) (gr1 + 1 - '1');
  gr2= (unsigned char) (gr2 + 1 - '1');
  c_killgroup1= (unsigned char) (gr1*10 + gr2);
  lookfor (datei, 'k');
  fret= fread (&gr1, 1, 1, datei);
  fret= fread (&gr2, 1, 1, datei);
  gr1= (unsigned char) (gr1 + 1 - '1');
  gr2= (unsigned char) (gr2 + 1 - '1');
  c_killgroup2= (unsigned char) (gr1*10 + gr2);
  lookfor (datei, 'k');
  fret= fread (&gr1, 1, 1, datei);
  fret= fread (&gr2, 1, 1, datei);
  gr1= (unsigned char) (gr1 + 1 - '1');
  gr2= (unsigned char) (gr2 + 1 - '1');
  c_killgroup3= (unsigned char) (gr1*10 + gr2);
  lookfor (datei, 'n');
  fret= fread (&gr1, 1, 1, datei);
  fret= fread (&gr2, 1, 1, datei);
  gr1= (unsigned char) (gr1 + 1 - '1');
  gr2= (unsigned char) (gr2 + 1 - '1');
//  c_notset= (((gr1*10) % 256) + gr2);
  c_notset= (unsigned char) (gr1*10);
  unsigned char* feld= new unsigned char[c_feldanz];
  for (unsigned char l_feld= 0; l_feld < c_feldanz; l_feld++)
    {
    do
      fret= fread (&token, 1, 1, datei);
    while ((token != '.') && (token != 'b') && (token != 'w'));
    switch (token)
      {
      case '.':
        {
        feld[l_feld]= c_leer;
        break;
        }
      case 'b':
        {
        feld[l_feld]= c_schwarz;
        break;
        }
      case 'w':
        {
        feld[l_feld]= c_weiss;
        break;
        }
      }
    }
  fclose (datei);
  for (unsigned char l_y= 0; l_y < c_yanz; l_y++)
    for (unsigned char l_x= 0; l_x < c_xanz; l_x++)
      c_ausgangsstellung[l_x + c_xanz*l_y]= feld[l_x + c_xanz*(c_yanz - l_y - 1)];
  delete (feld);
  c_feld= new unsigned char[c_satzanz];
  c_zamsatz= &c_feld[c_feldanz];
  memcpy (c_feld, c_ausgangsstellung, c_satzanz);
  c_addfeld ();
  }
