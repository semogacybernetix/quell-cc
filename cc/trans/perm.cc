//2023.02.26
//2024.02.11
//2025.05.05

#include <cstdio>
#include <ctime>

using namespace std;
unsigned char data[32]= {29,87,191,237,200,8,74,82,196,183,78,79,41,122,173,109,240,34,63,108,180,173,156,176,53,30,37,8,49,240,159,255};
unsigned char op1= 0;
unsigned char op2= 19;
unsigned char op3= 31;

unsigned char zufall ()
  {
  op1= (op1 + 1) & 31;
  op2= (op2 + 1) & 31;
  op3= (op3 + 1) & 31;
  return data[op3]= (unsigned char) (data[op1] + data[op2]);
  }

unsigned long lzufall ()
  {
  unsigned long z0= zufall ();
  unsigned long z1= zufall ();
  unsigned long z2= zufall ();
  unsigned long z3= zufall ();
  unsigned long ret= (z0 << 24) | (z1 << 16) | (z2 << 8) | z3;
  return ret;
  }

void permident (unsigned long* pperm, unsigned long panz)
  {
  for (unsigned long ecount= 0; ecount < panz; ecount++)
    pperm[ecount]= ecount;
  }

void permutiere (unsigned long* pperm, unsigned long panz)
  {
  for (unsigned long ecount= 0; ecount < panz; ecount++)
    {
    unsigned long z= lzufall () % panz;
    unsigned long el= pperm[ecount];
    pperm[ecount]= pperm[z];
    pperm[z]= el;
    }
  }

void trans (char* pname1, char* pname2)
  {
  unsigned char permtab[256][256];
  for (unsigned long bcount= 0; bcount < 256; bcount++)
    for (unsigned long pcount= 0; pcount < 256; pcount++)
      permtab[pcount][bcount]= (unsigned char) (bcount);
  for (unsigned long pcount= 0; pcount < 256; pcount++)
    {
    unsigned char* ltab= permtab[pcount];
    for (unsigned long ecount= 0; ecount < 256; ecount++)
      {
      unsigned char z= zufall ();
      unsigned char el= ltab[ecount];
      ltab[ecount]= ltab[z];
      ltab[z]= el;
      }
    }
  FILE* din= fopen (pname1, "rb");
  fseek (din, 0L, SEEK_END);
  unsigned long fsize= ftell (din);
  fseek (din, 0L, SEEK_SET);
  unsigned long blkgr, blkanz, fblkgr;
  if (fsize < 2113599)
    {
    blkgr= fsize;
    blkanz= 1;
    fblkgr= blkgr;
    }
    else
    {
    blkgr= ((fsize + lzufall ()) & 0xffff) + 0x10000;
    blkanz= fsize/blkgr - 20;
    fblkgr= fsize - (blkanz - 1)*blkgr;
    }
  time_t zeit;
  time_t starttime= time (NULL);
  tm* startstruct= localtime (&starttime);
  char* startstring= asctime (startstruct);
  printf ("\n");
  printf ("Start: ");
  printf ("%s", startstring);
  printf ("fsize:    %10lu\n", fsize);
  printf ("fblkgr:   %10lu\n", fblkgr);
  printf ("blkgr:    %10lu\n", blkgr);
  printf ("blkanz:   %10lu\n", blkanz);
  FILE* dout= fopen (pname2, "wb");
  unsigned char* fbuf= new unsigned char[fblkgr];
  unsigned long* perm= new unsigned long[fblkgr];
  permident (perm, fblkgr);
  for (unsigned long blkcount= 0; blkcount < blkanz; blkcount++)
    {
    if (blkcount == 1)
      {
      fblkgr= blkgr;
      delete (fbuf);
      delete (perm);
      fbuf= new unsigned char[fblkgr];
      perm= new unsigned long[fblkgr];
      permident (perm, fblkgr);
      }
    permutiere (perm, fblkgr);
    unsigned long sekunden= (time_t (&zeit) - starttime);
    unsigned long sec= sekunden % 60;
    unsigned long min= sekunden / 60;
    printf ("\rBlock: %13ld  %02ld:%02ld ", blkcount + 1, min, sec);
    fflush (stdout);
    unsigned long fret= fread (fbuf, fblkgr, 1, din);
    fret++;
    for (unsigned long bcount= 0; bcount < fblkgr; bcount++)
      {
      unsigned char data= permtab[zufall ()][fbuf[perm[bcount]]];
      fwrite (&data, 1, 1, dout);
      }
    }
  fclose (dout);
  fclose (din);
  delete (fbuf);
  delete (perm);
  time_t stoptime= time (NULL);
  tm* stopstruct= localtime (&stoptime);
  char* stopstring= asctime (stopstruct);
  printf ("\n");
  printf ("Stop: ");
  printf ("%s", stopstring);
  printf ("\n");
  }

void retrans (char* pname1, char* pname2)
  {
  unsigned char permtab[256][256];
  for (unsigned long bcount= 0; bcount < 256; bcount++)
    for (unsigned long pcount= 0; pcount < 256; pcount++)
      permtab[pcount][bcount]= (unsigned char) (bcount);
  for (unsigned long pcount= 0; pcount < 256; pcount++)
    {
    unsigned char* ltab= permtab[pcount];
    for (unsigned long ecount= 0; ecount < 256; ecount++)
      {
      unsigned char z= zufall ();
      unsigned char el= ltab[ecount];
      ltab[ecount]= ltab[z];
      ltab[z]= el;
      }
    }
  unsigned char upermtab[256][256];
  for (unsigned long upcount= 0; upcount < 256; upcount++)
    {
    unsigned char* ltab= permtab[upcount];
    unsigned char* lutab= upermtab[upcount];
    for (unsigned long ecount= 0; ecount < 256; ecount++)
      {
      unsigned char sn= 0;
      while (ltab[sn] != ecount)
        sn++;
      lutab[ecount]= sn;
      }
    }
  FILE* din= fopen (pname1, "rb");
  fseek (din, 0L, SEEK_END);
  unsigned long fsize= ftell (din);
  fseek (din, 0L, SEEK_SET);
  unsigned long blkgr, blkanz, fblkgr;
  if (fsize < 2113599)
    {
    blkgr= fsize;
    blkanz= 1;
    fblkgr= blkgr;
    }
    else
    {
    blkgr= ((fsize + lzufall ()) & 0xffff) + 0x10000;
    blkanz= fsize/blkgr - 20;
    fblkgr= fsize - (blkanz - 1)*blkgr;
    }
  time_t zeit;
  time_t starttime= time (NULL);
  tm* startstruct= localtime (&starttime);
  char* startstring= asctime (startstruct);
  printf ("\n");
  printf ("Start: ");
  printf ("%s", startstring);
  printf ("fsize:    %10lu\n", fsize);
  printf ("fblkgr:   %10lu\n", fblkgr);
  printf ("blkgr:    %10lu\n", blkgr);
  printf ("blkanz:   %10lu\n", blkanz);
  FILE* dout= fopen (pname2, "wb");
  unsigned char* fbuf= new unsigned char[fblkgr];
  unsigned long* perm= new unsigned long[fblkgr];
  permident (perm, fblkgr);
  for (unsigned long blkcount= 0; blkcount < blkanz; blkcount++)
    {
    if (blkcount ==  1)
      {
      fblkgr= blkgr;
      delete (fbuf);
      delete (perm);
      fbuf= new unsigned char[fblkgr];
      perm= new unsigned long[fblkgr];
      permident (perm, fblkgr);
      }
    permutiere (perm, fblkgr);
    unsigned long sekunden= (time (&zeit) - starttime);
    unsigned long sec= sekunden % 60;
    unsigned long min= sekunden / 60;
    printf ("\rBlock: %13ld  %02ld:%02ld ", blkcount + 1, min, sec);
    fflush (stdout);
    for (unsigned long bcount= 0; bcount < fblkgr; bcount++)
      {
      unsigned char data;
      unsigned long fret= fread (&data, 1, 1, din);
      fret++;
      fbuf[perm[bcount]]= upermtab[zufall ()][data];
      }
    fwrite (fbuf, fblkgr, 1, dout);
    }
  fclose (dout);
  fclose (din);
  delete (fbuf);
  delete (perm);
  time_t stoptime= time (NULL);
  tm* stopstruct= localtime (&stoptime);
  char* stopstring= asctime (stopstruct);
  printf ("\n");
  printf ("Stop: ");
  printf ("%s", stopstring);
  printf ("\n");
  }

int main (int argc, char** argv)
  {
  if ((argc != 4) && (argc != 5))
    return 0;
  if (argv[3][0] == '}')
    trans (argv[1], argv[2]);
  if (argv[3][0] == '{')
    retrans (argv[1], argv[2]);
  return 0;
  }
