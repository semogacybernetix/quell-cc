#include "cxschachbrett.h"

#include <cstdlib>    // abs
#include <cstring>    // memset

//------------------------------ Klasse Schachbrett ------------------------------------------------------------------------

cxschachbrett::cxschachbrett ()
  {
  feldbmp[0]= new cbmpdatei ("sfig/ld.bmp");
  feldbmp[2]= new cbmpdatei ("sfig/ksd.bmp");
  feldbmp[3]= new cbmpdatei ("sfig/kwd.bmp");
  feldbmp[4]= new cbmpdatei ("sfig/ssd.bmp");
  feldbmp[5]= new cbmpdatei ("sfig/swd.bmp");
  feldbmp[6]= new cbmpdatei ("sfig/gssd.bmp");
  feldbmp[7]= new cbmpdatei ("sfig/gswd.bmp");
  feldbmp[8]= new cbmpdatei ("sfig/lsd.bmp");
  feldbmp[9]= new cbmpdatei ("sfig/lwd.bmp");
  feldbmp[10]= new cbmpdatei ("sfig/glsd.bmp");
  feldbmp[11]= new cbmpdatei ("sfig/glwd.bmp");
  feldbmp[12]= new cbmpdatei ("sfig/esd.bmp");
  feldbmp[13]= new cbmpdatei ("sfig/ewd.bmp");
  feldbmp[14]= new cbmpdatei ("sfig/kasd.bmp");
  feldbmp[15]= new cbmpdatei ("sfig/kawd.bmp");
  feldbmp[16]= new cbmpdatei ("sfig/tsd.bmp");
  feldbmp[17]= new cbmpdatei ("sfig/twd.bmp");
  feldbmp[18]= new cbmpdatei ("sfig/gtsd.bmp");
  feldbmp[19]= new cbmpdatei ("sfig/gtwd.bmp");
  feldbmp[20]= new cbmpdatei ("sfig/basd.bmp");
  feldbmp[21]= new cbmpdatei ("sfig/bawd.bmp");
  feldbmp[22]= new cbmpdatei ("sfig/gbasd.bmp");
  feldbmp[23]= new cbmpdatei ("sfig/gbawd.bmp");
  feldbmp[24]= new cbmpdatei ("sfig/dsd.bmp");
  feldbmp[25]= new cbmpdatei ("sfig/dwd.bmp");
  feldbmp[28]= new cbmpdatei ("sfig/gdsd.bmp");
  feldbmp[29]= new cbmpdatei ("sfig/gdwd.bmp");

  feldbmp[32]= new cbmpdatei ("sfig/lh.bmp");
  feldbmp[34]= new cbmpdatei ("sfig/ksh.bmp");
  feldbmp[35]= new cbmpdatei ("sfig/kwh.bmp");
  feldbmp[36]= new cbmpdatei ("sfig/ssh.bmp");
  feldbmp[37]= new cbmpdatei ("sfig/swh.bmp");
  feldbmp[38]= new cbmpdatei ("sfig/gssh.bmp");
  feldbmp[39]= new cbmpdatei ("sfig/gswh.bmp");
  feldbmp[40]= new cbmpdatei ("sfig/lsh.bmp");
  feldbmp[41]= new cbmpdatei ("sfig/lwh.bmp");
  feldbmp[42]= new cbmpdatei ("sfig/glsh.bmp");
  feldbmp[43]= new cbmpdatei ("sfig/glwh.bmp");
  feldbmp[44]= new cbmpdatei ("sfig/esh.bmp");
  feldbmp[45]= new cbmpdatei ("sfig/ewh.bmp");
  feldbmp[46]= new cbmpdatei ("sfig/kash.bmp");
  feldbmp[47]= new cbmpdatei ("sfig/kawh.bmp");
  feldbmp[48]= new cbmpdatei ("sfig/tsh.bmp");
  feldbmp[49]= new cbmpdatei ("sfig/twh.bmp");
  feldbmp[50]= new cbmpdatei ("sfig/gtsh.bmp");
  feldbmp[51]= new cbmpdatei ("sfig/gtwh.bmp");
  feldbmp[52]= new cbmpdatei ("sfig/bash.bmp");
  feldbmp[53]= new cbmpdatei ("sfig/bawh.bmp");
  feldbmp[54]= new cbmpdatei ("sfig/gbash.bmp");
  feldbmp[55]= new cbmpdatei ("sfig/gbawh.bmp");
  feldbmp[56]= new cbmpdatei ("sfig/dsh.bmp");
  feldbmp[57]= new cbmpdatei ("sfig/dwh.bmp");
  feldbmp[60]= new cbmpdatei ("sfig/gdsh.bmp");
  feldbmp[61]= new cbmpdatei ("sfig/gdwh.bmp");

  feldbmp[64]= new cbmpdatei ("sfig/samzug.bmp");
  feldbmp[66]= new cbmpdatei ("sfig/wamzug.bmp");
  feldbmp[67]= new cbmpdatei ("sfig/menuleiste.bmp");
  feldbmp[68]= new cbmpdatei ("sfig/lr.bmp");

  bscreen= new cxscreen ("xebrauser", 521, 534);
  memset (brett, -1, 64*sizeof(*brett));
  bscreen->putscreen (*feldbmp[67], 26, 521);
  while (bscreen->checkexpose ());
  }

cxschachbrett::~cxschachbrett ()
  {
  delete (bscreen);
  }

void cxschachbrett::putfeld (signed long pfeldnr)
  {
  signed long linie, reihe;
  linie= pfeldnr % 8;
  reihe= pfeldnr/8;
  bscreen->putscreen (*feldbmp[brett[pfeldnr]], 1 + 65*linie, 1 + 65*reihe);
  }

void cxschachbrett::putamsatz ()
  {
  bscreen->putscreen (*feldbmp[brett[64]], 1, 521);
  }

void cxschachbrett::putbrett (signed long* pbrett)
  {
  for (signed long feldlauf= 0; feldlauf < 64; feldlauf++)
    if (pbrett[feldlauf] != brett[feldlauf])
      {
      brett[feldlauf]= pbrett[feldlauf];
      putfeld (feldlauf);
      }
  if (pbrett[64] != brett[64])
    {
    brett[64]= pbrett[64];
    putamsatz ();
    bscreen->putscreen (*feldbmp[67], 26, 521);    // Menüleiste zeichnen
    }
  }

void cxschachbrett::refresh ()
  {
    do
    {
    while (bscreen->checkexpose ());
    signed long lbrett[65];
    memcpy (lbrett, brett, 65*sizeof (*lbrett));
    memset (brett, -1, 65*sizeof (*brett));  // Alle Felder unterschiedlich machen um vollen Refresh zu haben
    putbrett (lbrett);
    }
  while (bscreen->checkexpose ());
  }

signed long cxschachbrett::getgezogen (signed long* pvonfeld, signed long* phinfeld)
  {
  signed long mausx, mausy;
  signed long feldx, feldy;
  signed long expxmin, expxmax, expymin, expymax, expose;
  signed long action;
    do
    {
    bscreen->getmaus (action, mausx, mausy, expose, expxmin, expxmax, expymin, expymax);
    if (expose)
    refresh ();
    if (abs (action) != 1)
      {
      if ((mausx % 65 == 0) || (mausy % 65 == 0))
        return 0;
      feldx= mausx/65;
      feldy= mausy/65;
      if ((feldx > 7) || (feldy > 7))
        return 0;
      *pvonfeld= feldx + 8*feldy;
      return action;
      }
    }
  while (action < 0);
  if ((mausx % 65 == 0) || (mausy % 65 == 0))
    return 0;
  feldx= mausx/65;
  feldy= mausy/65;
  if ((feldx > 7) || (feldy > 7))
    return 0;
  *pvonfeld= feldx + 8*feldy;
    do
    {
    bscreen->getmaus (action, mausx, mausy, expose, expxmin, expxmax, expymin, expymax);
    if (expose)
      refresh ();
    }
  while (action > 0);
  if ((mausx % 65 == 0) || (mausy % 65 == 0))
    return 0;
  feldx= mausx/65;
  feldy= mausy/65;
  if ((feldx > 7) || (feldy > 7))
    return 0;
  *phinfeld= feldx + 8*feldy;
  return 1;
  }
