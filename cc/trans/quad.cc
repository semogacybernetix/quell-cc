#include <cstdio>
#include <sys/stat.h>

unsigned long gzufall= 34250;

unsigned long zufall ()
  {
  gzufall= (gzufall*2349786 + 34988764) % 12498673;
  return gzufall;
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
    unsigned long z= zufall () % panz;
    unsigned long tmp= pperm[ecount];
    pperm[ecount]= pperm[z];
    pperm[z]= tmp;
    }
  }

void trans (char* pname1, char* pname2)
  {
  unsigned long fsize, fblkgr, blkgr, maxblkgr, blkanz;
  struct stat filestat;
  stat (pname1, &filestat);
  fsize= filestat.st_size;
  if (fsize < 0x20000)
    {
    blkgr= fsize;
    blkanz= 1;
    fblkgr= blkgr;
    }
    else
    {
    blkgr= (fsize & 0xffff) + 0x10000;
    blkanz= fsize/blkgr + 1;
    fblkgr= fsize - (blkanz - 1)*blkgr;
    if (fblkgr < 0x10000)
      {
      blkanz--;
      fblkgr+= blkgr;
      }
    }
  if (fblkgr > blkgr)
    maxblkgr= fblkgr;
    else
    maxblkgr= blkgr;
  printf ("fsize:    %10lu\n", fsize);
  printf ("fblkgr:   %10lu\n", fblkgr);
  printf ("blkgr:    %10lu\n", blkgr);
  printf ("blkanz:   %10lu\n", blkanz);
  FILE* din= fopen (pname1, "rb");
  FILE* dout= fopen (pname2, "wb");
  char* fbuf= new char[maxblkgr];
  unsigned long* perm= new unsigned long[maxblkgr];
  permident (perm, fblkgr);
  for (unsigned long blkcount= 0; blkcount < blkanz; blkcount++)
    {
    if (blkcount == 1)
      {
      fblkgr= blkgr;
      permident (perm, fblkgr);
      }
    permutiere (perm, fblkgr);
    printf ("*");
    fflush (stdout);
    fread (fbuf, fblkgr, 1, din);
    for (unsigned long bcount= 0; bcount < fblkgr; bcount++)
      {
      char data= fbuf[perm[bcount]] + zufall ();
      fwrite (&data, 1, 1, dout);
      }
    }
  fclose (dout);
  fclose (din);
  delete (fbuf);
  delete (perm);
  printf ("\n");
  }

void retrans (char* pname1, char* pname2)
  {
  unsigned long fsize, fblkgr, blkgr, maxblkgr, blkanz;
  struct stat filestat;
  stat (pname1, &filestat);
  fsize= filestat.st_size;
  if (fsize < 0x20000)
    {
    blkgr= fsize;
    blkanz= 1;
    fblkgr= blkgr;
    }
    else
    {
    blkgr= (fsize & 0xffff) + 0x10000;
    blkanz= fsize/blkgr + 1;
    fblkgr= fsize - (blkanz - 1)*blkgr;
    if (fblkgr < 0x10000)
      {
      blkanz--;
      fblkgr+= blkgr;
      }
    }
  if (fblkgr > blkgr)
    maxblkgr= fblkgr;
    else
    maxblkgr= blkgr;
  printf ("fsize:    %10lu\n", fsize);
  printf ("fblkgr:   %10lu\n", fblkgr);
  printf ("blkgr:    %10lu\n", blkgr);
  printf ("blkanz:   %10lu\n", blkanz);
  FILE* din= fopen (pname1, "rb");
  FILE* dout= fopen (pname2, "wb");
  char* fbuf= new char[maxblkgr];
  unsigned long* perm= new unsigned long[maxblkgr];
  permident (perm, fblkgr);
  for (unsigned long blkcount= 0; blkcount < blkanz; blkcount++)
    {
    if (blkcount ==  1)
      {
      fblkgr= blkgr;
      permident (perm, fblkgr);
      }
    permutiere (perm, fblkgr);
    printf ("*");
    fflush (stdout);
    for (unsigned long bcount= 0; bcount < fblkgr; bcount++)
      {
      char data;
      fread (&data, 1, 1, din);
      fbuf[perm[bcount]]= data - zufall ();
      }
    fwrite (fbuf, fblkgr, 1, dout);
    }
  fclose (dout);
  fclose (din);
  delete (fbuf);
  delete (perm);
  printf ("\n");
  }

int main (int argc, char** argv)
  {
  if ((argc != 4) && (argc != 5))
    return 0;
  if (argc == 5)
    sscanf (argv[4], "%lu", &gzufall);
  if (argv[3][0] == '}')
    trans (argv[1], argv[2]);
  if (argv[3][0] == '{')
    retrans (argv[1], argv[2]);
  return 0;
  }
