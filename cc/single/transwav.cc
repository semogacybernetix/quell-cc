#include "single.h"
#include <sys/stat.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>

void putwav (char* pdin, char* pdout)
  {
  struct stat filestat;
  stat (pdin, &filestat);
  unsigned long laengedin= filestat.st_size;
  FILE* din= fopen (pdin, "rb");
  FILE* dout= fopen (pdout, "wb");
  unsigned char header[308]= {};
  wavheader44 (header, laengedin + 264 + 16388);
  header[44]= 0x6A;
  header[45]= 0x3C;
  header[46]= 0xB3;
  header[47]= 0x84;
  strcpy ((char*) header + 48, pdin);
  header[304]= laengedin;
  header[305]= laengedin >> 8;
  header[306]= laengedin >> 16;
  header[307]= laengedin >> 24;
  fwrite (header, 308, 1, dout);
  unsigned long blkgr= laengedin;
  if (blkgr > 16777216)
    blkgr= 16777216;
  unsigned char* blocki= new unsigned char[blkgr];
  unsigned long checksum= 0;
  unsigned long gelesen= 0;
  while (gelesen < laengedin)
    {
    blkgr= laengedin - gelesen;
    if (blkgr > 16777216)
      blkgr= 16777216;
    printf ("reading  ");
    fflush (stdout);
    fread (blocki, blkgr, 1, din);
    printf ("calcing  ");
    fflush (stdout);
    calccrc (checksum, blocki, blkgr);
    printf ("writing  ");
    fflush (stdout);
    fwrite (blocki, blkgr, 1, dout);
    gelesen+= blkgr;
    printf ("%10lu\n", gelesen);
    }
  fclose (din);
  char bchecksum[16388];
  memset (bchecksum, 0x80, 16388);
  bchecksum[0]= checksum;
  bchecksum[1]= checksum >> 8;
  bchecksum[2]= checksum >> 16;
  bchecksum[3]= checksum >> 24;
  fwrite (bchecksum, 16388, 1, dout);
  fclose (dout);
  delete (blocki);
  }

void getwav (char* pdin)
  {
  struct stat filestat;
  stat (pdin, &filestat);
  unsigned long laengedin= filestat.st_size;
  if (laengedin < 268)
    {
    printf ("Datei ist zu kurz\n");
    exit (0);
    }
  FILE* din= fopen (pdin, "rb");
  unsigned char header[65536]= {};
  unsigned long hlaenge= laengedin;
  if (hlaenge > 65536)
    hlaenge= 65536;
  fread (header, hlaenge, 1, din);
  unsigned long anfpos= 0;
  for (unsigned long lsuch= 44; lsuch < hlaenge - 4; lsuch++)
    if ((header[lsuch] == 0x6a) &&
        (header[lsuch + 1] == 0x3c) &&
        (header[lsuch + 2] == 0xb3) &&
 (header[lsuch + 3] == 0x84))
      {
      anfpos= lsuch + 4;
      break;
      }
  if (!anfpos)
    printf ("  Anfangsmarkierung wurde nicht gefunden\n");

  printf ("Anfangsposition:  %lu\n", anfpos);
  char pdout[256]= {};
  strcpy (pdout, (char*) header + anfpos);
  printf ("Dateiname: ");
  printf (pdout);
  printf ("\n");
  unsigned long laengeinheader= header[anfpos + 256] |
                                header[anfpos + 257] << 8 |
                                header[anfpos + 258] << 16 |
                                header[anfpos + 259] << 24;
  signed long laengedif= laengedin - anfpos - 264 - laengeinheader;
  if (laengedif < 0)
    printf ("Datei ist um %lu bytes zu kurz\n", -laengedif);
  FILE* dout= fopen (pdout, "wb");
  fseek (din, anfpos + 260, SEEK_SET);
  unsigned long blkgr= laengeinheader;
  if (blkgr > 16777216)
    blkgr= 16777216;
  unsigned char* blocki= new unsigned char[blkgr];
  unsigned long checksum= 0;
  unsigned long gelesen= 0;
  while (gelesen < laengeinheader)
    {
    unsigned long blkgr= laengeinheader - gelesen;
    if (blkgr > 16777216)
      blkgr= 16777216;
    printf ("reading  ");
    fflush (stdout);
    fread (blocki, blkgr, 1, din);
    printf ("calcing  ");
    fflush (stdout);
    calccrc (checksum, blocki, blkgr);
    printf ("writing  ");
    fflush (stdout);
    fwrite (blocki, blkgr, 1, dout);
    gelesen+= blkgr;
    printf ("%10lu\n", gelesen);
    }
  fread (header, 4, 1, din);
  fclose (din);
  fclose (dout);
  unsigned long gelchecksum= header[0] |
                             header[1] << 8 |
                             header[2] << 16 |
                             header[3] << 24;
  if (checksum != gelchecksum)
    printf ("Checksummenfehler\n");
    else
    printf ("Checksumme OK\n");
  }

int main (int argc, char** argv)
  {
  if (argc == 3)
    {
    putwav (argv[1], argv[2]);
    return 0;
    }
  if (argc == 2)
    {
    getwav (argv[1]);
    return 0;
    }
  printf ("  example:\n");
  printf ("    transwav bug1.vob bug1.wav   #to pack file\n");
  printf ("    transwav bug1.wav            #to extract file\n\n");
  return 0;
  }
