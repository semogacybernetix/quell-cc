#include <cstdio>

unsigned long gzufall= 34520;

unsigned long zufall ()
  {
  gzufall= (gzufall*2349786 + 34988764) % 12498673;
  return gzufall;
  }

unsigned long filesize (char* pname)
  {
  FILE* din= fopen (pname, "rb");
  unsigned long anz= 0;
  unsigned char data;
  while (fread (&data, 1, 1, din))
    anz++;
  fclose (din);
  return anz;
  }

unsigned long* zdata (unsigned long panz)
  {
  unsigned long* zd= new unsigned long[panz];
  unsigned char* cfeld= new unsigned char[panz];
  for (unsigned long n= 0; n < panz; n++)
    cfeld[n]= 0;
  unsigned long pos;
  unsigned long ord= 0;
  for (unsigned long n2= 0; n2 < panz; n2++)
    {
    unsigned char zversuch= 0;
      do
      {
      pos= zufall () % panz;
      zversuch++;
      }
    while ((zversuch < 10) && cfeld[pos]);
    if (cfeld[pos])
      {
      while (cfeld[ord])
        ord++;
      zd[n2]= ord;
      cfeld[ord]= 1;
      //printf ("ord %4lu\n", ord);
      }
      else
      {
      zd[n2]= pos;
      cfeld[pos]= 1;
      //printf ("pos %4lu %2d\n", pos, zversuch);
      }
    }
  return zd;
  }

void trans (char* pname1, char* pname2)
  {
  unsigned long fsize= filesize (pname1);
  char grtype= fsize % 34;
  for (unsigned long n= 0; n < unsigned (8 + grtype); n++)
    zufall ();
  unsigned long tlsize= 34* (5 + zufall () % 52);
  FILE* din= fopen (pname1, "rb");
  FILE* dout= fopen (pname2, "wb");
  unsigned long* zd= zdata (fsize);
  printf ("*");
  fflush (stdout);
  unsigned char data;
  for (unsigned long n2= 0; n2 < fsize; n2++)
    {
    fseek (din, zd[n2], SEEK_SET);
    fread (&data, 1, 1, din);
    data+= zufall ();
    fwrite (&data, 1, 1, dout);
    }
  for (unsigned long n3= 0; n3 < tlsize; n3++)
    {
    unsigned char data= zufall ();
    fwrite (&data, 1, 1, dout);
    }
  fclose (din);
  fclose (dout);
  delete (zd);
  printf ("-\n");
  }

void retrans (char* pname1, char* pname2)
  {
  unsigned long fsize= filesize (pname1);
  unsigned char grtype= fsize % 34;
  for (unsigned long n= 0; n < unsigned (8 + grtype); n++)
    zufall();
  unsigned long tlsize= 34* (5 + zufall () % 52);
  fsize-= tlsize;
  FILE* din= fopen (pname1, "rb");
  FILE* dout= fopen (pname2, "wb");
  unsigned long* zd= zdata (fsize);
  printf ("*");
  fflush (stdout);
  unsigned char data;
  for (unsigned long n2= 0; n2 < fsize; n2++)
    {
    fread (&data, 1, 1, din);
    data-= zufall ();
    fseek (dout, zd[n2], SEEK_SET);
    fwrite (&data, 1, 1, dout);
    }
  fclose (din);
  fclose (dout);
  delete (zd);
  printf ("-\n");
  }

int main (int argc, char** argv)
  {
  if (argc != 4)
    return 0;
  if (argv[3][0] == '}')
    trans (argv[1], argv[2]);
  if (argv[3][0] == '{')
    retrans (argv[1], argv[2]);
  return 0;
  }
