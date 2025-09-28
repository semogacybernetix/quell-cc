#include <cstdio>
#include <cstdlib>

bool eof= false;

struct clabeltab
  {
  unsigned long anz;
  char* label[65536];
  unsigned long labeladdr[65536];

  clabeltab ()
    {
    anz= 0;
    }

  ~clabeltab ()
    {
    for (unsigned long n= 0; n < anz; n++)
      delete label[n];
    }
  };

bool gleichwort (char* w1, char* w2)
  {
  for (unsigned long n= 0; n < 32; n++)
    if (w1[n] != w2[n])
      return false;
  return true;
  }

void loeschewort (char* pwort, unsigned long ppos)
  {
  for (unsigned long n= ppos; n < 32; n++)
    pwort[n]= 0;
  }

void copywort (char* pwort1, char* pwort2, unsigned long panz)
  {
  for (unsigned long n= 0; n < panz; n++)
    pwort2[n]= pwort1[n];
  }

char* lesewort (FILE* pdatei)
  {
  char* rwort= new char[32];
  loeschewort (rwort, 0);
  unsigned long bnr= 0;
  char buchstabe;
  do
    {
    if (!fread (&buchstabe, 1, 1, pdatei))
      {
      eof= true;
      return rwort;
      }
    if (buchstabe <= 32)
      return rwort;
    rwort[bnr]= buchstabe;
    bnr++;
    }
  while (bnr < 32);
  printf ("Zu langes Wort\n");
  exit (0);
  return rwort;
  }

void printwort (char* pwort)
  {
  char printzeichen[2]= {0};
  for (unsigned long n= 0; n < 32; n++)
    {
    if ((pwort[n] >= 33) && (pwort[n] <= 122))
        printzeichen[0]= pwort[n];
      else
        {
        if (pwort[n] == 0)
          printzeichen[0]= 183;
          else printzeichen[0]= 126;
        }
    printf (printzeichen);
    }
  }

void bauebeftab (clabeltab &ptab)
  {
  ptab.label[ptab.anz]= new char[32];
  loeschewort (ptab.label[ptab.anz], 0);
  copywort ("copy", ptab.label[ptab.anz], 5);
  ptab.labeladdr[ptab.anz]= ptab.anz;
  ptab.anz++;
  ptab.label[ptab.anz]= new char[32];
  loeschewort (ptab.label[ptab.anz], 0);
  copywort ("sub", ptab.label[ptab.anz], 4);
  ptab.labeladdr[ptab.anz]= ptab.anz;
  ptab.anz++;
  ptab.label[ptab.anz]= new char[32];
  loeschewort (ptab.label[ptab.anz], 0);
  copywort ("cond", ptab.label[ptab.anz], 5);
  ptab.labeladdr[ptab.anz]= ptab.anz;
  ptab.anz++;
  }

void bauelabeltab (FILE* pdatei, clabeltab &ptab)
  {
  bauebeftab (ptab);
  unsigned long addr= 0;
  while (!eof)
    {
    char* gelwort= lesewort (pdatei);
    if (gelwort[0] != 0)
      {
      if (gelwort[0] == ':')
        {
        for (unsigned long n= 0; n < 31; n++)
          gelwort[n]= gelwort[n+1];
        gelwort[32]= 0;
        ptab.label[ptab.anz]= gelwort;
        ptab.labeladdr[ptab.anz]= addr;
        ptab.anz++;
        }
        else addr++;
      }
    }
  }

bool labeltabok (clabeltab &ptab)
  {
  for (unsigned long wn= 0; wn < ptab.anz - 1; wn++)
    for (unsigned long ws= wn + 1; ws < ptab.anz; ws++)
      if (gleichwort (ptab.label[wn], ptab.label[ws]))
        {
        printf ("mehrfache Label\n");
        printwort (ptab.label[wn]);
        printf ("  ");
        printwort (ptab.label[ws]);
        printf ("\n%5lu %5lu\n", wn, ws);
        return false;
        }
  return true;
  }

void printlabeltab (clabeltab &ptab)
  {
  for (unsigned long n= 0; n < ptab.anz; n++)
    {
    printwort (ptab.label[n]);
    printf ("  %5lu\n", ptab.labeladdr[n]);
    }
  printf ("\n");
  }

void schreibezelle (FILE* pdatei, unsigned long pdata)
  {
  unsigned char data;
  data= pdata >> 24;
  fwrite (&data, 1, 1, pdatei);
  data= (pdata >> 16) & 0xff;
  fwrite (&data, 1, 1, pdatei);
  data= (pdata >> 8) & 0xff;
  fwrite (&data, 1, 1, pdatei);
  data= pdata & 0xff;
  fwrite (&data, 1, 1, pdatei);
  }

bool uebersetzewort (char* pwort, clabeltab &ptab, unsigned long &pwert)
  {
  for (unsigned long n= 0; n < ptab.anz; n++)
    if (gleichwort (pwort, ptab.label[n]))
      {
      pwert= ptab.labeladdr[n];
      return true;
      }
  printwort (pwort);
  printf ("  ");
  printf ("Label nicht definiert\n");
  return false;
  }

bool parse (FILE* pdatei, clabeltab &ptab)
  {
  FILE* dout= fopen ("ram", "wb");
  char* gelwort;
  unsigned long bwert;
  while (!eof)
    {
    do
      {
      gelwort= lesewort (pdatei);
      }
    while (!eof && ((gelwort[0] == ':') || (gelwort[0] == 0)));
    if ((gelwort[0] == ':') || (gelwort[0] == 0))
      return true;
    if ((gelwort[0] == '-') || ((gelwort[0] >= 0x30) && (gelwort[0] <= 0x39)))
      {
      sscanf (gelwort, "%ld", &bwert);
      }
      else
        if (!uebersetzewort (gelwort, ptab, bwert))
          exit (0);
    schreibezelle (dout, bwert);
//    printwort (gelwort);
//    printf ("  ");
//    printf ("%10ld\n", bwert);
    }
  fclose (dout);
  return true;
  }

void uebersetze (char* pname)
  {
  FILE* datei= fopen (pname, "rb");
  clabeltab labeltab;
  bauelabeltab (datei, labeltab);
  if (!labeltabok (labeltab))
    exit (0);
//  printlabeltab (labeltab);
  fseek (datei, 0, 0);
  eof= false;
  parse (datei, labeltab);
  fclose (datei);
  }

int main (int argc, char** argv)
  {
  if (argc != 2)
    return 0;
  uebersetze (argv[1]);
  }
