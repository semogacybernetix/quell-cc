#include "single.h"
#include <cstdio>
#include <cmath>

void writeheader (FILE* dout, unsigned long plaenge)
  {
  unsigned char header[44];
  wavheader44 (header, plaenge);
  fwrite (header, 44, 1, dout);
  }

void makekonst (char* pname, signed short pwert, float psek)
  {
  FILE* datei= fopen (pname, "wb");
  unsigned long takte= (unsigned long) (psek*44100 + 0.5);
  writeheader (datei, takte*4);
  for (unsigned long n= 0; n < takte; n++)
    {
    signed short swert= pwert;
    unsigned char s0= swert;
    unsigned char s1= swert >> 8;
    fwrite (&s0, 1, 1, datei);
    fwrite (&s1, 1, 1, datei);
    fwrite (&s0, 1, 1, datei);
    fwrite (&s1, 1, 1, datei);
//    printf ("%5lu  %5d\n", n, swert);
    }
  fclose (datei);
  }

void makekamm (char* pname, float psek)
  {
  FILE* datei= fopen (pname, "wb");
  unsigned long takte= (unsigned long) (psek*44100 + 0.5);
  writeheader (datei, takte*4);
  for (unsigned long n= 0; n < takte; n++)
    {
    signed short swert;
    if (n & 1)
      swert= -32768;
      else
      swert= 32767;
    unsigned char s0= swert;
    unsigned char s1= swert >> 8;
    fwrite (&s0, 1, 1, datei);
    fwrite (&s1, 1, 1, datei);
    fwrite (&s0, 1, 1, datei);
    fwrite (&s1, 1, 1, datei);
//    printf ("%5lu  %5d\n", n, swert);
    }
  fclose (datei);
  }

void makenadel (char* pname, float psek)
  {
  FILE* datei= fopen (pname, "wb");
  unsigned long takte= (unsigned long) (psek*44100 + 0.5);
  writeheader (datei, takte*4);
  for (unsigned long n= 0; n < takte; n++)
    {
    signed short swert= 0;
    if (!(n % 44100))
      swert= 32767;
    unsigned char s0= swert;
    unsigned char s1= swert >> 8;
    fwrite (&s0, 1, 1, datei);
    fwrite (&s1, 1, 1, datei);
    fwrite (&s0, 1, 1, datei);
    fwrite (&s1, 1, 1, datei);
//    printf ("%5lu  %5d\n", n, swert);
    }
  fclose (datei);
  }

void makerampe (char* pname)
  {
  FILE* datei= fopen (pname, "wb");
  unsigned long takte= 65536*16;
  writeheader (datei, takte*4);
  for (unsigned long n= 0; n < takte; n++)
    {
    signed short swert1= n;
    signed short swert2= ~n;
    unsigned char s0= swert1;
    unsigned char s1= swert1 >> 8;
    unsigned char s2= swert2;
    unsigned char s3= swert2 >> 8;
    fwrite (&s0, 1, 1, datei);
    fwrite (&s1, 1, 1, datei);
    fwrite (&s2, 1, 1, datei);
    fwrite (&s3, 1, 1, datei);
//    printf ("%5lu  %5d\n", n, swert);
    }
  fclose (datei);
  }

void makezufall (char* pname, float psek)
  {
  FILE* datei= fopen (pname, "wb");
  unsigned long takte= (unsigned long) (psek*44100 + 0.5);
  writeheader (datei, takte*4);
  for (unsigned long n= 0; n < takte; n++)
    {
    unsigned char s0= zufall ();
    unsigned char s1= zufall ();
    unsigned char s2= zufall ();
    unsigned char s3= zufall ();
    fwrite (&s0, 1, 1, datei);
    fwrite (&s1, 1, 1, datei);
    fwrite (&s2, 1, 1, datei);
    fwrite (&s3, 1, 1, datei);
//    printf ("%5lu  %5d\n", n, swert);
    }
  fclose (datei);
  }

void makesinus (char* pname, float pfreq, float pamp, float psek)
  {
  FILE* datei= fopen (pname, "wb");
  unsigned long takte= (unsigned long) (psek*44100 + 0.5);
  writeheader (datei, takte*4);
  float ffakt= M_PI*pfreq/22050;
  for (unsigned long n= 0; n < takte; n++)
    {
    float fsample= pamp/ffakt*(cos(ffakt*n) - cos(ffakt*(n + 1)));
    signed short swert= (signed short) (rint (fsample));
    unsigned char s0= swert;
    unsigned char s1= swert >> 8;
    fwrite (&s0, 1, 1, datei);
    fwrite (&s1, 1, 1, datei);
    fwrite (&s0, 1, 1, datei);
    fwrite (&s1, 1, 1, datei);
//    printf ("%5lu  %5d\n", n, swert);
    }
  fclose (datei);
  }

void makedur (char* pname, float pfreq, float pamp, float psek)
  {
  FILE* datei= fopen (pname, "wb");
  unsigned long takte= (unsigned long) (psek*44100 + 0.5);
  writeheader (datei, takte*4);
  float ffakt1= M_PI*pfreq/22050;
  float ffakt2= M_PI*pfreq*4/3/22050;
  float ffakt3= M_PI*pfreq*5/3/22050;
  for (unsigned long n= 0; n < takte; n++)
    {
    float fsample1= pamp/ffakt1*(cos(ffakt1*n) - cos(ffakt1*(n + 1)));
    float fsample2= pamp/ffakt2*(cos(ffakt2*n) - cos(ffakt2*(n + 1)));
    float fsample3= pamp/ffakt3*(cos(ffakt3*n) - cos(ffakt3*(n + 1)));
    float fsample= (fsample1 + fsample2 + fsample3)/3;
    signed short swert= (signed short) (rint (fsample));
    unsigned char s0= swert;
    unsigned char s1= swert >> 8;
    fwrite (&s0, 1, 1, datei);
    fwrite (&s1, 1, 1, datei);
    fwrite (&s0, 1, 1, datei);
    fwrite (&s1, 1, 1, datei);
//    printf ("%5lu  %5d\n", n, swert);
    }
  fclose (datei);
  }

void makemoll (char* pname, float pfreq, float pamp, float psek)
  {
  FILE* datei= fopen (pname, "wb");
  unsigned long takte= (unsigned long) (psek*44100 + 0.5);
  writeheader (datei, takte*4);
  float ffakt1= M_PI*pfreq/22050;
  float ffakt2= M_PI*pfreq*12/10/22050;
  float ffakt3= M_PI*pfreq*15/10/22050;
  for (unsigned long n= 0; n < takte; n++)
    {
    float fsample1= pamp/ffakt1*(cos(ffakt1*n) - cos(ffakt1*(n + 1)));
    float fsample2= pamp/ffakt2*(cos(ffakt2*n) - cos(ffakt2*(n + 1)));
    float fsample3= pamp/ffakt3*(cos(ffakt3*n) - cos(ffakt3*(n + 1)));
    float fsample= (fsample1 + fsample2 + fsample3)/3;
    signed short swert= (signed short) (rint (fsample));
    unsigned char s0= swert;
    unsigned char s1= swert >> 8;
    fwrite (&s0, 1, 1, datei);
    fwrite (&s1, 1, 1, datei);
    fwrite (&s0, 1, 1, datei);
    fwrite (&s1, 1, 1, datei);
//    printf ("%5lu  %5d\n", n, swert);
    }
  fclose (datei);
  }

int main (int argc, char** argv)
  {
  if (argc != 5)
    {
    printf ("wavegen datei freq ampl dauer\n\n");
    return 0;
    }
  float freq, amp, zeit;
  sscanf (argv[2], "%f", &freq);
  sscanf (argv[3], "%f", &amp);
  sscanf (argv[4], "%f", &zeit);
  printf ("%f %f %f\n", freq, amp, zeit);
// makerampe (argv[1]);
// makekonst (argv[1], 0, zeit);
// makekamm (argv[1], 0, zeit);
//  makenadel (argv[1], zeit);
  makesinus (argv[1], freq, amp, zeit);
  return 0;
  }
