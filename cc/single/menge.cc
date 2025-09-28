#include <cstdio>

class crelation
  {
  bool data[256];

  public:
  const int anz;

  crelation (const int panz)
    : anz (panz)
    {
    for (int y= 0; y < anz; y++)
      for (int x= 0; x < anz; x++)
        put (x, y, false);
    }

  bool get (const int x, const int y) const
    {
    return data[x + y*anz];
    }

  void put (const int x, const int y, const bool z)
    {
    data[x + y*anz]= z == true;
    }

  };

class cdelta : public crelation
  {
  public:

  cdelta (const int panz)
    : crelation (panz)
    {
    for (int y= 0; y < anz; y++)
      for (int x= 0; x < anz; x++)
        if (x == y)
          put (x, y, true);
    }

  };

class creins : public crelation
  {
  public:

  creins (const int panz)
    : crelation (panz)
    {
    for (int y= 0; y < anz; y++)
      for (int x= 0; x < anz; x++)
        put (x, y, true);
    }

  };

bool rteil (const crelation &r1, const crelation &r2)
  {
  for (int y= 0; y < r1.anz; y++)
    for (int x= 0; x < r1.anz; x++)
      if (r1.get (x, y) > r2.get (x, y))
        return false;
  return true;
  }

bool rgleich (const crelation &r1, const crelation &r2)
  {
  return rteil (r1, r2) & rteil (r2, r1);
  }

crelation rumkehr (const crelation &r1)
  {
  crelation r2 (r1.anz);
  for (int y= 0; y < r1.anz; y++)
    for (int x= 0; x < r1.anz; x++)
      r2.put (x, y, r1.get (y, x));
  return r2;
  }

crelation rschnitt (const crelation &r1, const crelation &r2)
  {
  crelation r3 (r1.anz);
  for (int y= 0; y < r1.anz; y++)
    for (int x= 0; x < r1.anz; x++)
      r3.put (x, y, r1.get (x, y) & r2.get (x, y));
  return r3;
  }

crelation rverein (const crelation &r1, const crelation &r2)
  {
  crelation r3 (r1.anz);
  for (int y= 0; y < r1.anz; y++)
    for (int x= 0; x < r1.anz; x++)
      r3.put (x, y, r1.get (x, y) | r2.get (x, y));
  return r3;
  }

crelation rkreis (const crelation &r1, const crelation &r2)
  {
  crelation r3 (r1.anz);
  for (int y= 0; y < r1.anz; y++)
    for (int x= 0; x < r1.anz; x++)
      if (r1.get (x, y))
        for (int z= 0; z < r1.anz; z++)
          if (r2.get (y, z))
            r3.put (x, z, true);
  return r3;
  }

bool reflexiv (const crelation &r1)
  {
  return rteil (cdelta (r1.anz), r1);
  }

bool transitiv (const crelation &r1)
  {
  return rteil (rkreis (r1, r1), r1);
  }

bool symmetrisch (const crelation &r1)
  {
  return rgleich (r1, rumkehr (r1));
  }

bool antisymmetrisch (const crelation &r1)
  {
  return rgleich (cdelta (r1.anz), rschnitt (r1, rumkehr (r1)));
  }

bool aequivalent (const crelation &r1)
  {
  return reflexiv (r1) & symmetrisch (r1) & transitiv (r1);
  }

bool ordnung (const crelation &r1)
  {
  return reflexiv (r1) & antisymmetrisch (r1) & transitiv (r1);
  }

bool linear (const crelation &r1)
  {
  return ordnung (r1) & rgleich ( rverein (r1, rumkehr (r1)), creins (r1.anz));
  }

bool rassoziativ (const crelation &r1)
  {
  for (int x= 0; x < r1.anz; x++)
    for (int y= 0; y < r1.anz; y++)
      for (int z= 0; z < r1.anz; z++)
        if (r1.get (r1.get (x, y), z) != r1.get (x, r1.get (y, z)))
          return false;
  return true;
  }

class coperation
  {
  char data[256];

  public:
  const int anz;

  coperation (const int panz)
    : anz (panz)
    {
    for (int y= 0; y < anz; y++)
      for (int x= 0; x < anz; x++)
        put (x, y, 0);
    }

  char get (const int x, const int y) const
    {
    return data[x + y*anz];
    }

  void put (const int x, const int y, const char z)
    {
    data[x + y*anz]= z;
    }

  };

bool oassoziativ (const coperation &o1)
  {
  for (int x= 0; x < o1.anz; x++)
    for (int y= 0; y < o1.anz; y++)
      for (int z= 0; z < o1.anz; z++)
        if (o1.get (o1.get (x, y), z) != o1.get (x, o1.get (y, z)))
          return false;
  return true;
  }

void rout (const crelation &r1, char* name1)
  {
  FILE* datei= fopen (name1,"wb");
  for (int y= 0; y < r1.anz; y++)
    {
    for (int x= 0; x < r1.anz; x++)
      fprintf (datei, "%d", r1.get (x, y));
    fprintf (datei, "\n");
    }
  fprintf (datei, "\n");
  if (reflexiv (r1)) fprintf (datei, "      reflexiv\n");
    else             fprintf (datei, "nicht reflexiv\n");
  if (symmetrisch (r1)) fprintf (datei, "      symmetrisch\n");
    else                fprintf (datei, "nicht symmetrisch\n");
  if (antisymmetrisch (r1)) fprintf (datei, "      antisymmetrisch\n");
    else                    fprintf (datei, "nicht antisymmetrisch\n");
  if (transitiv (r1)) fprintf (datei, "      transitiv\n");
    else              fprintf (datei, "nicht transitiv\n");
  if (aequivalent (r1)) fprintf (datei, "      aequivalent\n");
    else             fprintf (datei, "nicht aequivalent\n");
  if (ordnung (r1)) fprintf (datei, "      ordnung\n");
    else             fprintf (datei, "nicht ordnung\n");
  if (linear (r1)) fprintf (datei, "      linear\n");
    else             fprintf (datei, "nicht linear\n");
  if (rassoziativ (r1)) fprintf (datei, "      assoziativ\n");
    else             fprintf (datei, "nicht assoziativ\n");
  fclose (datei);
  }

void testrel ()
  {
  int anz= 4;
  crelation r1 (anz);
  for (int n= 0; n < 1 << (anz*anz); n++)
    {
    for (int y= 0; y < r1.anz; y++)
      for (int x= 0; x < r1.anz; x++)
        r1.put (x, y, n & ( 1 << (x + r1.anz*y)));
    if (linear (r1))
      {
      printf ("%7d ", n);
      if (reflexiv (r1)) printf ("r"); else printf ("-");
      if (symmetrisch (r1)) printf ("s"); else printf ("-");
      if (antisymmetrisch (r1)) printf ("a"); else printf ("-");
      if (transitiv (r1)) printf ("t"); else printf ("-");
      if (aequivalent (r1)) printf ("e"); else printf ("-");
      if (ordnung (r1)) printf ("o"); else printf ("-");
      if (linear (r1)) printf ("l"); else printf ("-");
      if (rassoziativ (r1)) printf ("a"); else printf ("-");
      printf ("\n");
      }
    }
  }

int main ()
  {
  testrel ();
  return 0;
  }
