#include "single.h"

#include <cstdio>
#include <cstring>
#include <cmath>

// CRC-IBM           $8005
// CRC-CCITT         $1021
// CRC-Ethernet  $04C11DB7

// Farbraumkonvertierung
// 1. ist eine Bijektion
// 2. Die Kanäle sind unabhängig. z.B. Änderung der Farbsättigung ändert nicht die Helligkeit
// Problem: Wegen des Farbwürfel-Achsenmodells haben die Grundfarben (rot, grün, blau) eine höhere Sättigung als die Mischfarben (gelb, cyan, magenta)
// Problem: Farbraum wird zu stark ausgenutzt. Viele Farbwerte befinden sich an den Grenzen des Farbraums z.B. #800000 (maximale Sättigung)
// Bei irgendwelchen Farbtransformationen z.B. Komplementärfarbe bilden wird dann der Farbraum überschritten

// alte CCIR Deklaration mit schwachem Fernsehblauleuchtstoff
// return long double (0.299)*irot + long double (0.587)*igrn + long double (0.114)*iblu;
// per Augensichtung auf Fujitsu/Siemens Monitor ermittelte Werte

using namespace std;

signed long zufall ()
  {
  static signed long data[32]= {29,87,191,237,200,8,74,82,196,183,78,79,41,122,173,109,240,34,63,108,180,173,156,176,53,30,37,8,49,240,159,255};
  static signed long op1= 0;
  static signed long op2= 19;
  static signed long op3= 31;
  op1= (op1 + 1) % 32;
  op2= (op2 + 1) % 32;
  op3= (op3 + 1) % 32;
  return data[op3%32]= data[op1%32] + data[op2%32];
  }

void calccrc (unsigned long& pchecksum, unsigned char* pblock, unsigned long plaenge)
  {
  static unsigned long generator= 0x4C11DB7;
  for (unsigned long blauf= 0; blauf < plaenge; blauf++)
    {
    unsigned char dwert= pblock[blauf];
    for (signed char lbit= 7; lbit >= 0; lbit--)
      {
      if (pchecksum & 0x80000000)
        {
        pchecksum<<= 1;
        pchecksum|= bool (dwert & (1 << lbit));
        pchecksum^= generator;
        }
        else
        {
        pchecksum<<= 1;
        pchecksum|= bool (dwert & (1 << lbit));
        }
      }
    }
  }

void wavheader44 (unsigned char* pheader, unsigned long plaenge)
  {
  strcpy ((char*) pheader, "RIFF");
  unsigned long laenge= plaenge + 0x24;
  pheader[4]= laenge & 255;
  pheader[5]= (laenge >> 8) & 255;
  pheader[6]= (laenge >> 16) & 255;
  pheader[7]= (laenge >> 24) & 255;
  strcpy ((char*) pheader + 8 , "WAVEfmt ");
  unsigned char pheader16[20]= {0x10,0,0,0, 1,0,2,0, 0x44,0xac,0,0, 0x10,0xb1,2,0, 4,0,0x10,0};
  memcpy (pheader + 16, pheader16, 20);
  strcpy ((char*) pheader + 36, "data");
  pheader[40]= plaenge & 255;
  pheader[41]= (plaenge >> 8) & 255;
  pheader[42]= (plaenge >> 16) & 255;
  pheader[43]= (plaenge >> 24) & 255;
  }

long double rgbtoy (long double irot, long double igrn, long double iblu)
  {
  return 0.299*irot + 0.490*igrn + 0.211*iblu;
  }

void rgbtohsy (long double irot, long double igrn, long double iblu, long double& ohue, long double& osat, long double& ohel)
  {
  // Hilfswerte
  long double hlang= irot*irot + igrn*igrn + iblu*iblu;
  long double hsat= hlang - irot*igrn - irot*iblu - igrn*iblu;

  // Farbwinkel
  if (hsat > 0)
    {
    ohue= (irot - 0.5*igrn - 0.5*iblu)/sqrt (hsat);
    if (ohue < -1)
      ohue= -1;
      else 
      if (ohue > 1)
        ohue= 1;
    }
    else
    ohue= 0;
  ohue= acos (ohue);
  if ((igrn - iblu) < 0)
    ohue= -ohue;

  // Sättigung
  if (hlang > 0)
    {
    osat= (irot + igrn + iblu)/sqrt (3*hlang);
    if (osat > 1)
      osat= 1;
      else
      if (osat < -1)
        osat= -1;
    osat= acos (osat);
    }
    else
    osat= 0;

  // Helligkeit
  ohel= rgbtoy (irot, igrn, iblu);
  }

void rgbtoabc (long double irot, long double igrn, long double iblu, long double& ohel, long double& osat, long double& ofar)
  {
  // Hilfswerte
  long double hlang= irot*irot + igrn*igrn + iblu*iblu;
  long double hsat= hlang - irot*igrn - irot*iblu - igrn*iblu;

  // Farbwinkel
  if (hsat > 0)
    {
    ofar= (irot - 0.5*igrn - 0.5*iblu)/sqrt (hsat);
    if (ofar < -1)
      ofar= -1;
      else 
      if (ofar > 1)
        ofar= 1;
    }
    else
    ofar= 0;
  ofar= acos (ofar);
  if ((igrn - iblu) < 0)
    ofar= -ofar;

  // Sättigung
  long double hmin= irot;
  if (igrn < hmin)
    hmin= igrn;
  if (iblu < hmin)
    hmin= iblu;
  long double hmax= irot;
  if (igrn > hmax)
    hmax= igrn;
  if (iblu > hmax)
    hmax= iblu;
  if (hmax > 0)
    osat= 1 - hmin/hmax;
	else osat= 0;

  // Helligkeit
  ohel= rgbtoy (irot, igrn, iblu);
  }

void hsytorgb (long double ihue, long double isat, long double ihel,
               long double& orot, long double& ogrn, long double& oblu)
  {
  // Hilfswerte
  long double hcos= cos (ihue)/sqrt (6);
  long double hsin= sin (ihue)/sqrt (2);
  long double hscale= sqrt (3) * tan (isat);

  // unskalierte RGB-Werte
  orot= 1 + hscale*2*hcos;
  ogrn= 1 - hscale*(hcos - hsin);
  oblu= 1 - hscale*(hcos + hsin);

  // endgültige RGB-Werte
  long double k= ihel/rgbtoy (orot, ogrn, oblu);
  orot= orot*k;
  ogrn= ogrn*k;
  oblu= oblu*k;
  }

void abctorgb (long double ihel, long double isat, long double ifar,
               long double& orot, long double& ogrn, long double& oblu)
  {
  // Hilfswerte
  long double hcos= cos (ifar)/sqrt (6);
  long double hsin= sin (ifar)/sqrt (2);

  // unskalierte RGB-Werte
  orot= 1 + 2*hcos;
  ogrn= 1 - hcos + hsin;
  oblu= 1 - hcos - hsin;

  // Sättigungsskalierung der RGB-Werte
  long double hmax= orot;
  if (ogrn > hmax)
    hmax= ogrn;
  if (oblu > hmax)
    hmax= oblu;
  long double hmin= orot;
  if (ogrn < hmin)
    hmin= ogrn;
  if (oblu < hmin)
    hmin= oblu;

  long double uist= hmax - hmin;
  long double usoll= isat*hmax;
  long double sfak= usoll/uist;
  orot= hmax - (hmax - orot)*sfak;
  ogrn= hmax - (hmax - ogrn)*sfak;
  oblu= hmax - (hmax - oblu)*sfak;

  // Helligkeitsskalierung der RGB-Werte
  long double k= ihel/rgbtoy (orot, ogrn, oblu);
  orot= orot*k;
  ogrn= ogrn*k;
  oblu= oblu*k;
 }
