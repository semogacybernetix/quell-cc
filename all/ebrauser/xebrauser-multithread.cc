// Version multithread

// Version ab Benutzung der Symmetriefunktion für symmetrische Stellungen
// letzte Version vor Implementierung der Multicoreversion
/*
2015.09.16
Klassen auslagern verringert Performance stark. Fehler Segfault in diederstellungen gefunden char bla = short* blubb[22] Compiler meckert nicht
Symmetrie ausnutzen bringt keinen Performance Gewinn, maximalen Bewertungswert erniedrigt um ungültige Stellungen markieren zu können
Problem Pattstellungen: Sie werden immer wieder neu bewertet, weil mit 0 (Remis) gekennzeichnet und deshalb immer wieder getestet wird, ob sie in
den höheren Ebenen nicht doch eine Gewinnstellung sein könnten

2015.09.19
Multithreading geschafft, noch Ungleichgewichte in den Threads, Verbesserung durch Zufallsbijektion und damit statistische Ausgleichung
*/

#include "../../cc/screen/allscr.h"
#include "../../xwindow/screen/xscr.h"

#include <cstring>    // memset
#include <iostream>   // abs, printf
#include <pthread.h>  // threads

using namespace std;

//------------------------------ Klasse Schachbrett ------------------------------------------------------------------------

struct cxschachbrett
  {
  cbmpdatei*  feldbmp[128];  // Bilder der Figuren schwarz und weiß
  cxscreen*   bscreen;
  signed long brett[65];  // auf dem 65. Feld steht welche Farbe am Zug ist

  cxschachbrett ()
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

  ~cxschachbrett ()
    {
    delete (bscreen);
    }

  void putfeld (signed long pfeldnr)
    {
    signed long linie, reihe;
    linie= pfeldnr % 8;
    reihe= pfeldnr/8;
    bscreen->putscreen (*feldbmp[brett[pfeldnr]], 1 + 65*linie, 1 + 65*reihe);
    }

  void putamsatz ()
    {
    bscreen->putscreen (*feldbmp[brett[64]], 1, 521);
    }

  void putbrett (signed long* pbrett)
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

  void refresh ()
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

  signed long getgezogen (signed long* pvonfeld, signed long* phinfeld)
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

  };

//----------------------------- Klasse cvier ----------------------------------------------------------------------------------------

struct cvier
  {
  // Daten die während einer Endspielberechnung konstant bleiben
  const signed long endfarbe= 65*65*65*65;      // Anzahl der Stellungen einer Farbe
  const signed long endmax= 65*65*65*65*2;      // Anzahl aller Stellungen
  const signed long bewmax= (1 << 15) - 1;      // Bewertungswert für gewonnene Stellung für weiss, -bewmax: Bewertungswert für gewonnenene Stellung für schwarz
  const signed long bewmin=  3;                 // längste Zugfolge, um Platz für patt, illegal Markierungen zu haben
  const signed long stillegal= -1;              // Bewertung illegale Stellung
  const signed long stpatt= 2;                  // Bewertung Pattstellung
  const signed long unbewertet= 0;              // Bewertung unbewertete Stellung

  signed long  dieder[8][65];
  signed long  gangart[5];    // bitcodiert: Bit 0: König, 1:Springer, 2:Läufer, 3:Turm, 0 = leeres Feld, Index: Nummer der Figur, 0: keine Figur (leeres Feld)
  signed long  figurnrfb[5];  // Figurnummerfarbe: Betrag ist die Figurnummer, Vorzeichen die Farbe, Index: Nummer der Figur
  signed long  maxposw;
  signed long  maxposs;

  // sich während einer Berechnung ändernde Daten
  // signed long  brett[65];     // 64. Feld bedeutet das die Figur nicht auf dem Brett steht (geschlagen wurde)
  // signed long  amzug;         // 1: weiss am Zug, -1: schwarz am Zug
  // signed long  standort[5];  // Standorte der Figuren
  // signed long  hinfeld[65];   // Liste der Hinfelder (Zugmöglichkeiten einer Figur)
  // signed long  hinpos[257];   // Lister der Folgepositionen (Zugmöglichkeiten einer Stellung)

  // Endspielarray
  signed short* endspiel;

  // Threadverwaltung
  signed long  threadanz;
  signed long* passret;
  signed long  passnr;
  signed long  passfarbe;

  cvier ()
    {
    endspiel= (signed short*) (calloc (endmax, sizeof (short)));
    initdieder ();
    passfarbe= 0;
    }

  ~cvier ()
    {
    free (endspiel);
//    delete (passret);  // invalid nextsize (fast)
    }

  void setthreadanz (signed long pthreadanz)
    {
    threadanz= pthreadanz;
    passret= new signed long (threadanz);
    }

  // Die Symmetrietabellen initialisieren
  void initdieder ()
    {
    signed long fx, fy;
    for (signed long flauf= 0; flauf < 64; flauf++)
      {
      fx= flauf%8;
      fy= flauf/8;
      dieder[0][flauf]= 8*fy + fx;
      dieder[1][flauf]= 8*fy + 7 - fx;
      dieder[2][flauf]= 8*(7 - fy) + fx;
      dieder[3][flauf]= 8*(7 - fy) + 7 - fx;
      dieder[4][flauf]= 8*fx + fy;
      dieder[5][flauf]= 8*fx + 7 - fy;
      dieder[6][flauf]= 8*(7 - fx) + fy;
      dieder[7][flauf]= 8*(7 - fx) + 7 - fy;
      }
    // Figuren außerhalb des Brettes auf sich selbst diedern
    for (signed long slauf= 0; slauf < 8; slauf++)
      dieder[slauf][64]= 64;
    }

  // Initialisierung Gangart[], Farbe[] bei Endspielberechnungsbeginn
  void initfiguren (signed long pfig1, signed long pfig2, signed long pfig3, signed long pfig4)
    {
    gangart[0]= 0;
    gangart[1]= abs (pfig1);
    gangart[2]= abs (pfig2);
    gangart[3]= abs (pfig3);
    gangart[4]= abs (pfig4);
    // zur Nummer das Vorzeichen (Farbe) hinzufügen
    figurnrfb[0]= 0;
    figurnrfb[1]= 1*pfig1/abs (pfig1);
    figurnrfb[2]= 2*pfig2/abs (pfig2);
    figurnrfb[3]= 3*pfig3/abs (pfig3);
    figurnrfb[4]= 4*pfig4/abs (pfig4);
    }

  // Stellungsnummer aus den Figurenstandorten ermitteln (Umkehrfunktion zu setstandorte)
  signed long getnumber (signed long* pstandort, signed long pamzug)
    {
    return pstandort[1] + pstandort[2]*65 + pstandort[3]*4225 + pstandort[4]*274625 + (1 - pamzug)/2*17850625;
    }

  // illegale Stellungen markieren
  // Stellungen mit Figuren mit gleichem Brettfeld als ungültig markieren
  bool stellungillegal (signed long pstellungsnr)
    {
    signed long lstandort[5];
    lstandort[1]= pstellungsnr % 65;
    lstandort[2]= (pstellungsnr % 4225)/65;
    if ((lstandort[1] != 64) && (lstandort[2] == lstandort[1]))
      return 1;
    lstandort[3]= (pstellungsnr % 274625)/4225;
    if ((lstandort[3] != 64) && ((lstandort[3] == lstandort[2]) || (lstandort[3] == lstandort[1])))
      return 1;
    lstandort[4]= (pstellungsnr % 17850625)/274625;
    if ((lstandort[4] != 64) && ((lstandort[4] == lstandort[3]) || (lstandort[4] == lstandort[2]) || (lstandort[4] == lstandort[1])))
      return 1;
    return 0;
    }

  // Stellungsnummer -> Standorte, Amzug  (Umkehrfunktion zu getnumber) Rückgabewert 0 wenn ungültige Standorte (Figuren auf gleichem Feld)
  // standort[0] undefiniert
  void setstandorte (signed long pstellungsnr, signed long* pstandort, signed long* pamzug)
    {
    pstandort[1]= pstellungsnr % 65;
    pstandort[2]= (pstellungsnr % 4225)/65;
    pstandort[3]= (pstellungsnr % 274625)/4225;
    pstandort[4]= (pstellungsnr % 17850625)/274625;
    *pamzug= 1 - (pstellungsnr/17850625)*2;
    }

  void setzugbrett (signed long* pstandort, signed long* pbrett)
    {
    memset (&*pbrett, 0, 64*sizeof (*pbrett));
    pbrett[pstandort[1]]= figurnrfb[1]/abs (figurnrfb[1]);
    pbrett[pstandort[2]]= figurnrfb[2]/abs (figurnrfb[2]);
    pbrett[pstandort[3]]= figurnrfb[3]/abs (figurnrfb[3]);
    pbrett[pstandort[4]]= figurnrfb[4]/abs (figurnrfb[4]);
    }

  // Standorte -> Brett zur Zugausführung
  void setbrett (signed long* pstandort, signed long* pbrett)
    {
    memset (&*pbrett, 0, 64*sizeof (*pbrett));
    pbrett[pstandort[1]]= figurnrfb[1];
    pbrett[pstandort[2]]= figurnrfb[2];
    pbrett[pstandort[3]]= figurnrfb[3];
    pbrett[pstandort[4]]= figurnrfb[4];
    }

// --------------------------- Zuggenerator ---------------------------------------------

signed long sgn (signed long pwert)
  {
  if (pwert > 0)
    return 1;
  if (pwert < 0)
    return -1;
  return 0;
  }

bool linksok (signed long pfeld)
  {
  return (pfeld % 8);
  }

bool dlinksok (signed long pfeld)
  {
  return ((pfeld % 8) > 1);
  }

bool rechtsok (signed long pfeld)
  {
  return ((pfeld % 8) < 7);
  }

bool drechtsok (signed long pfeld)
  {
  return ((pfeld % 8) < 6);
  }

bool obenok (signed long pfeld)
  {
  return (pfeld < 56);
  }

bool dobenok (signed long pfeld)
  {
  return (pfeld < 48);
  }

bool untenok (signed long pfeld)
  {
  return (pfeld > 7);
  }

bool duntenok (signed long pfeld)
  {
  return (pfeld > 15);
  }

void testekoenig (signed long pfeldnr, const signed long* pbrett, signed long* phinfeld)
  {
  signed long farbe= pbrett[pfeldnr];
  if (linksok (pfeldnr))
    if (farbe != pbrett[pfeldnr - 1])
      {
      phinfeld[phinfeld[64]]= pfeldnr - 1;
      phinfeld[64]++;
      }
  if (rechtsok (pfeldnr))
    if (farbe != pbrett[pfeldnr + 1])
      {
      phinfeld[phinfeld[64]]= pfeldnr + 1;
      phinfeld[64]++;
      }
  if (obenok (pfeldnr) && (farbe != pbrett[pfeldnr + 8]))
    {
    phinfeld[phinfeld[64]]= pfeldnr + 8;
    phinfeld[64]++;
    }
  if (untenok (pfeldnr) && (farbe != pbrett[pfeldnr - 8]))
    {
    phinfeld[phinfeld[64]]= pfeldnr - 8;
    phinfeld[64]++;
    }
  if (obenok (pfeldnr) && linksok (pfeldnr) && ((farbe*pbrett[pfeldnr + 7]) <= 0))
    {
    phinfeld[phinfeld[64]]= pfeldnr + 7;
    phinfeld[64]++;
    }
  if (obenok (pfeldnr) && rechtsok (pfeldnr) && ((farbe*pbrett[pfeldnr + 9]) <= 0))
    {
    phinfeld[phinfeld[64]]= pfeldnr + 9;
    phinfeld[64]++;
    }
  if (untenok (pfeldnr) && linksok (pfeldnr) && ((farbe*pbrett[pfeldnr - 9]) <= 0))
    {
    phinfeld[phinfeld[64]]= pfeldnr - 9;
    phinfeld[64]++;
    }
  if (untenok (pfeldnr) && rechtsok (pfeldnr) && ((farbe*pbrett[pfeldnr - 7]) <= 0))
    {
    phinfeld[phinfeld[64]]= pfeldnr - 7;
    phinfeld[64]++;
    }
  }

void testespringer (signed long pfeldnr, const signed long* pbrett, signed long* phinfeld)
  {
  signed long farbe= pbrett[pfeldnr];
  if (drechtsok (pfeldnr) && obenok (pfeldnr) && ((farbe*pbrett[pfeldnr + 10]) <= 0))
    {
    phinfeld[phinfeld[64]]= pfeldnr + 10;
    phinfeld[64]++;
    }
  if (rechtsok (pfeldnr) && dobenok (pfeldnr) && ((farbe*pbrett[pfeldnr + 17]) <= 0))
    {
    phinfeld[phinfeld[64]]= pfeldnr + 17;
    phinfeld[64]++;
    }
  if (linksok (pfeldnr) && dobenok (pfeldnr) && ((farbe*pbrett[pfeldnr + 15]) <= 0))
    {
    phinfeld[phinfeld[64]]= pfeldnr + 15;
    phinfeld[64]++;
    }
  if (dlinksok (pfeldnr) && obenok (pfeldnr) && ((farbe*pbrett[pfeldnr + 6]) <= 0))
    {
    phinfeld[phinfeld[64]]= pfeldnr + 6;
    phinfeld[64]++;
    }
  if (dlinksok (pfeldnr) && untenok (pfeldnr) && ((farbe*pbrett[pfeldnr - 10]) <= 0))
    {
    phinfeld[phinfeld[64]]= pfeldnr - 10;
    phinfeld[64]++;
    }
  if (linksok (pfeldnr) && duntenok (pfeldnr) && ((farbe*pbrett[pfeldnr - 17]) <= 0))
    {
    phinfeld[phinfeld[64]]= pfeldnr - 17;
    phinfeld[64]++;
    }
  if (rechtsok (pfeldnr) && duntenok (pfeldnr) && ((farbe*pbrett[pfeldnr - 15]) <= 0))
    {
    phinfeld[phinfeld[64]]= pfeldnr - 15;
    phinfeld[64]++;
    }
  if (drechtsok (pfeldnr) && untenok (pfeldnr) && ((farbe*pbrett[pfeldnr - 6]) <= 0))
    {
    phinfeld[phinfeld[64]]= pfeldnr - 6;
    phinfeld[64]++;
    }
  }

void testeturm (signed long pfeldnr, const signed long* pbrett, signed long* phinfeld)
  {
  signed long farbe= pbrett[pfeldnr];
  signed long feldlauf;
  feldlauf= pfeldnr;
  while (linksok (feldlauf) && ((farbe*pbrett[feldlauf - 1]) <= 0))
    {
    phinfeld[phinfeld[64]]= feldlauf - 1;
    phinfeld[64]++;
    if (farbe*pbrett[feldlauf - 1] != 0)
      break;
    feldlauf--;
    }
  feldlauf= pfeldnr;
  while (rechtsok (feldlauf) && ((farbe*pbrett[feldlauf + 1]) <= 0))
    {
    phinfeld[phinfeld[64]]= feldlauf + 1;
    phinfeld[64]++;
    if (farbe*pbrett[feldlauf + 1] != 0)
      break;
    feldlauf++;
    }
  feldlauf= pfeldnr;
  while (obenok (feldlauf) && ((farbe*pbrett[feldlauf + 8]) <= 0))
    {
    phinfeld[phinfeld[64]]= feldlauf + 8;
    phinfeld[64]++;
    if (farbe*pbrett[feldlauf + 8] != 0)
      break;
    feldlauf+= 8;
    }
  feldlauf= pfeldnr;
  while (untenok (feldlauf) && ((farbe*pbrett[feldlauf - 8]) <= 0))
    {
    phinfeld[phinfeld[64]]= feldlauf - 8;
    phinfeld[64]++;
    if (farbe*pbrett[feldlauf - 8] != 0)
      break;
    feldlauf-= 8;
    }
  }

void testelaeufer (signed long pfeldnr, const signed long* pbrett, signed long* phinfeld)
  {
  signed long farbe= pbrett[pfeldnr];
  signed long feldlauf;
  feldlauf= pfeldnr;
  while (linksok (feldlauf) && obenok (feldlauf) && ((farbe*pbrett[feldlauf + 7]) <= 0))
    {
    phinfeld[phinfeld[64]]= feldlauf + 7;
    phinfeld[64]++;
    if (farbe*pbrett[feldlauf + 7] != 0)
      break;
    feldlauf+= 7;
    }
  feldlauf= pfeldnr;
  while (rechtsok (feldlauf) && obenok (feldlauf) && ((farbe*pbrett[feldlauf + 9]) <= 0))
    {
    phinfeld[phinfeld[64]]= feldlauf + 9;
    phinfeld[64]++;
    if (farbe*pbrett[feldlauf + 9] != 0)
      break;
    feldlauf+= 9;
    }
  feldlauf= pfeldnr;
  while (linksok (feldlauf) && untenok (feldlauf) && ((farbe*pbrett[feldlauf - 9]) <= 0))
    {
    phinfeld[phinfeld[64]]= feldlauf - 9;
    phinfeld[64]++;
    if (farbe*pbrett[feldlauf - 9] != 0)
      break;
    feldlauf-= 9;
    }
  feldlauf= pfeldnr;
  while (rechtsok (feldlauf) && untenok (feldlauf) && ((farbe*pbrett[feldlauf - 7]) <= 0))
    {
    phinfeld[phinfeld[64]]= feldlauf - 7;
    phinfeld[64]++;
    if (farbe*pbrett[feldlauf - 7] != 0)
      break;
    feldlauf-= 7;
    }
  }

// Bit 0,1,2,3: König, Springer, Läufer, Turm
void testefigur (signed long pfeldnr, const signed long* pbrett, signed long* phinfeld)
  {
  phinfeld[64]= 0;
  if (gangart[abs (pbrett[pfeldnr])] & 1)
    testekoenig (pfeldnr, &*pbrett, &*phinfeld);
  if (gangart[abs (pbrett[pfeldnr])] & 2)
    testespringer (pfeldnr, &*pbrett, &*phinfeld);
  if (gangart[abs (pbrett[pfeldnr])] & 4)
    testelaeufer (pfeldnr, &*pbrett, &*phinfeld);
  if (gangart[abs (pbrett[pfeldnr])] & 8)
    testeturm (pfeldnr, &*pbrett, &*phinfeld);
  }

// Folgepositionen aller möglichen Züge in hinpos sammeln
void testepos (signed long pstellungsnr, signed long* phinpos)
  {
  signed long standort[5];
  signed long amzug;
  phinpos[256]= 0;
  setstandorte (pstellungsnr, &*standort, &amzug);
  signed long brett[65];
  setzugbrett (&*standort, &*brett);
  signed long hinfeld[65];
  for (signed long figurlauf= 1; figurlauf < 5; figurlauf++)
    if ((standort[figurlauf] != 64) && (figurnrfb[figurlauf]*amzug > 0))
      {
      // alle Züge der Figur ermitteln
      testefigur (standort[figurlauf], &*brett, &*hinfeld);
      // Zug ausführen und Stellungsnummer der entstehenden Stellung in die Stellungsliste eintragen
      setbrett (&*standort, &*brett);
      for (signed long feldlauf= 0; feldlauf < hinfeld[64]; feldlauf++)
        {
        standort[figurlauf]= hinfeld[feldlauf];  // neuer Standort der gezogenen Figur
        standort[abs (brett[hinfeld[feldlauf]])]= 64;  // der neue Standort der auf dem Hinfeld befindlichen Figur ist außerhalb des Bretts (Figur wurde geschlagen)
        amzug= -amzug;
        phinpos[phinpos[256]]= getnumber (&*standort, amzug);
        phinpos[256]++;
        setstandorte (pstellungsnr, &*standort, &amzug);
        }
      }
  }

// symmetrische Stellungen bewerten
void  bewertediederstellungen (signed long ppos)
  {
  signed long standort[5];
  signed long amzug;
  signed short bew= endspiel[ppos];
  signed long feld1, feld2, feld3, feld4;
  setstandorte (ppos, &*standort, &amzug);
  feld1= standort[1];
  feld2= standort[2];
  feld3= standort[3];
  feld4= standort[4];
  for (signed long symlauf= 1; symlauf < 8; symlauf++)
    {
    standort[1]= dieder[symlauf][feld1];
    standort[2]= dieder[symlauf][feld2];
    standort[3]= dieder[symlauf][feld3];
    standort[4]= dieder[symlauf][feld4];
    endspiel[getnumber (&*standort, amzug)]= bew;
    }
  }

// illegale Positionen setzen (2 Figuren stehen auf gleichem Feld)
signed long setillegalpos ()
  {
  printf (" illegale Positionen markieren\n");
  memset (endspiel, 0, endmax*sizeof (*endspiel));
  signed long bewanz= 0;
  for (signed long poslauf=0; poslauf < endmax; poslauf++)
    {
    if (!(poslauf % 1000000))
      {
      printf ("%10ld %11.3Lf\n", poslauf, (long double) (bewanz/1000.));
      fflush (stdout);
      }
    if (stellungillegal (poslauf))
      {
      endspiel[poslauf]= stillegal;
      bewanz++;
      }
    }
  printf ("\n");
  return bewanz;
  }

// Gewinnpositionen setzen (König wurde gerade geschlagen (bewmax, -bewmax))
// erste Figur gegen erste Figur
signed long setendpos11 ()
  {
  printf ("Ebene: -1 Gewinnpositionen setzen\n");
  signed long standort[5];
  signed long amzug;
  signed long bewanz= 0;
  for (signed long poslauf=0; poslauf < endmax; poslauf++)
    {
    if (!(poslauf % 1000000))
      {
      printf ("%10ld %11.3Lf\n", poslauf, (long double) (bewanz/1000.));
      fflush (stdout);
      }
    if (endspiel[poslauf] == 0)
      {
      setstandorte (poslauf, &*standort, &amzug);
      // Gewinnstellung für weiss, wenn weißer König existiert und schwarzer König geschlagen ist und schwarz am Zug ist
      if ((standort[1] != 64) && (standort[2] == 64) && (amzug == -1))
        {
        endspiel[poslauf]= bewmax;
        bewanz++;
        }
      // Gewinnstellung für schwarz, wenn schwarzer König existiert und weißer König geschlagen ist und weiß am Zug ist
      if ((standort[1] == 64) && (standort[2] != 64) && (amzug == 1))
        {
        endspiel[poslauf]= -bewmax;
        bewanz++;
        }
      }
    }
  printf ("\n");
  return bewanz;
  }

signed long setpattpos ()
  {
  printf ("Ebene: -1 Gewinnpositionen setzen\n");
  signed long standort[5];
  signed long amzug;
  signed long bewanz= 0;
  for (signed long poslauf=0; poslauf < endmax; poslauf++)
    {
    if (!(poslauf % 1000000))
      {
      printf ("%10ld %11.3Lf\n", poslauf, (long double) (bewanz/1000.));
      fflush (stdout);
      }
    if (endspiel[poslauf] == 0)
      {
      setstandorte (poslauf, &*standort, &amzug);
      // Gewinnstellung für weiss, wenn weißer König existiert und schwarzer König geschlagen ist und schwarz am Zug ist
      if ((standort[1] != 64) && (standort[2] == 64) && (amzug == -1))
        {
        endspiel[poslauf]= bewmax;
        bewanz++;
        }
      // Gewinnstellung für schwarz, wenn schwarzer König existiert und weißer König geschlagen ist und weiß am Zug ist
      if ((standort[1] == 64) && (standort[2] != 64) && (amzug == 1))
        {
        endspiel[poslauf]= -bewmax;
        bewanz++;
        }
      }
    }
  printf ("\n");
  return bewanz;
  }

void pass ()
  {
  passnr++;
  signed long lthreadnr= passnr - 1;
  signed long bewanz= 0;
  signed long amzug= 0;
  signed long standort[5];
  signed long hinpos[257];
  // Grenzen für Threadzuteilung ausrechnen
  signed long anfpos= (endfarbe*lthreadnr)/threadanz + endfarbe*passfarbe;
  signed long endpos= (endfarbe*(lthreadnr + 1))/threadanz + endfarbe*passfarbe;
  //  printf ("pass: Thread %2ld/%2ld gestartet\n", lthreadnr, threadanz);
  for (signed long poslauf= anfpos; poslauf < endpos; poslauf++)
    {
    // bearbeitete Stellungen ausgeben
    if (!(poslauf % 1000000))
      {
      printf ("%10ld %11.3Lf\n", poslauf, (long double) (bewanz/1000.));
      fflush (stdout);
      }
    if (endspiel[poslauf] == 0)
      {
      // alle Folgepositionen einer Stellung ermitteln
      testepos (poslauf, &*hinpos);
      // extpos auf die schlechteste Bewertung setzen
      signed long extpos= -bewmax*amzug;
      // Schleife um die beste Folgeposition zu ermitteln
      for (signed long zposlauf= 0; zposlauf < hinpos[256]; zposlauf++)
        {
        signed long bewertung= endspiel[hinpos[zposlauf]];
        // extpos= max oder min (extpos, bewertung) je nach zugfarbe
        extpos= (extpos + bewertung + amzug*abs (extpos - bewertung))/2;
        }

       if (abs (extpos) >= bewmin)
        {
        endspiel[poslauf]= extpos - extpos/abs (extpos);  // Position  eine Stufe höher bewerten
        bewanz++;
//        bewertediederstellungen (poslauf);  // die ermittelte Bewertung in die anderen 7 symmetrischen Positionen speichern
//        bewanz+= 7;
        // Pattstellungen als Remis kennzeichnen (Zugfarbe wechseln und kucken ob das eine Stellung ist, in der die gegnerischen Mattfiguren geschlagen werden können)

        if (abs (endspiel[poslauf]) == bewmax - 2)
          {
          if (endspiel[getnumber (&*standort, -amzug)] != -amzug*(bewmax - 1))
            {
            endspiel[poslauf]= 2;
            bewanz--;
//            bewertediederstellungen (poslauf);  // die ermittelte Bewertung in die anderen 7 symmetrischen Positionen speichern
//            bewanz-= 7;
            }
          }  // if (abs....

        }
      }
    }
  passret[lthreadnr]= bewanz;
  printf ("Thread %2ld/%2ld         %10ld\n", lthreadnr, threadanz, passret[lthreadnr]);
  }

//----------------------------------------------------------------------------------------------------------------------------------
// Anzeige, Visualisierung, Verwaltung der Endspieldatenbank

  void saveendspiel (const char* pname)
    {
    signed char header[64];
    memset (header, 0, 64);
    header[0]= 4;
    header[1]= figurnrfb[1]/abs (figurnrfb[1]) * gangart[1];
    header[2]= figurnrfb[2]/abs (figurnrfb[2]) * gangart[2];
    header[3]= figurnrfb[3]/abs (figurnrfb[3]) * gangart[3];
    header[4]= figurnrfb[4]/abs (figurnrfb[4]) * gangart[4];
    header[8]= maxposw;
    header[9]= maxposw >> 8;
    header[10]= maxposw >> 16;
    header[11]= maxposw >> 24;
    header[12]= maxposs;
    header[13]= maxposs >> 8;
    header[14]= maxposs >> 16;
    header[15]= maxposs >> 24;
    FILE* datei= fopen (pname, "wb");
    fwrite (header, 1, 64, datei);
    fwrite (endspiel, 1, endmax*sizeof (*endspiel), datei);
    fclose (datei);
    }

  void ladeendspiel (const char* pname)
    {
    signed long fret= 0;
    fret+= 0;               // Variable benutzen, damit der Compiler nicht meckert
    FILE* datei= fopen (pname, "rb");
    signed char header[64];
    fret= fread (header, 64, 1, datei);
    fret= fread (endspiel, 1, endmax*sizeof (*endspiel), datei);
    fclose (datei);
    initfiguren (header[1], header[2], header[3], header[4]);
    maxposw= ((unsigned char) (header[11]) << 24) | ((unsigned char) (header[10]) << 16) | ((unsigned char) header[9] << 8) | ((unsigned char) header[8]);
    maxposs= ((unsigned char) (header[15]) << 24) | ((unsigned char) (header[14]) << 16) | ((unsigned char) header[13] << 8) | ((unsigned char) header[12]);
    printf ("maxposw: %11ld %8d Matt in %6.1f\n", maxposw, endspiel[maxposw],  ((bewmax - 2) - endspiel[maxposw])/2.);
    printf ("maxposs: %11ld %8d Matt in %6.1f\n", maxposs, endspiel[maxposs], -((bewmax - 2) + endspiel[maxposs])/2.);
    }

  signed long ziehebesterst (signed long ppos)
    {
    if (abs (endspiel[ppos]) >= bewmax - 2)
      return ppos;
    signed long hinpos[257];
    testepos (ppos, &*hinpos);
    signed long bestpos= ppos, bestbew= 0;
    signed long standort[65];
    memset (standort, 0, 65*sizeof (*standort));
    signed long amzug= 0;
    setstandorte (ppos, &*standort, &amzug);
    switch (amzug)
      {
      case 1:
        bestbew= -bewmax;
        for (signed long poslauf= 0; poslauf < hinpos[256]; poslauf++)
          {
          if (endspiel[hinpos[poslauf]] > bestbew)
            {
            bestbew= endspiel[hinpos[poslauf]];
            bestpos= hinpos[poslauf];
            }
          }
    break;
      case -1:
        bestbew= bewmax;
        for (signed long poslauf= 0; poslauf < hinpos[256]; poslauf++)
          {
          if (endspiel[hinpos[poslauf]] < bestbew)
            {
            bestbew= endspiel[hinpos[poslauf]];
            bestpos= hinpos[poslauf];
            }
          }
    break;
      }
    signed long bestarray[256];
    signed long bestanz= 0;
    for (signed long bestlauf= 0; bestlauf < hinpos[256]; bestlauf++)
      {
      if (endspiel[hinpos[bestlauf]] == bestbew)
        {
        bestarray[bestanz]= bestlauf;
        bestanz++;
        }
      }
    bestpos= hinpos[bestarray[random () % bestanz]];
//    bestpos= hinpos[bestarray[0 % bestanz]];
    if (abs (bestbew) < bewmax - 1)
      return bestpos;
    amzug= -amzug;
    return getnumber (&*standort, amzug);
    }

  // Schachbrett Brett mit bmp-Indexen aus der Stellungsnummer versehen
  void setvisbrett (signed long ppos, signed long *pbrett)
    {
    // leere Felder initialisieren
    for (signed long ly= 0; ly < 8; ly++)
      for (signed long lx= 0; lx < 8; lx++)
        {
        if ((lx + ly + 1) & 1)
          pbrett[8*ly + lx]= 0;
          else
          pbrett[8*ly + lx]= 32;
        }
    signed long standort[65];
    memset (standort, 0, 65*sizeof (*standort));
    signed long amzug= 0;
    setstandorte (ppos, &*standort, &amzug);
    // Gangart und Farbe setzen
    signed long bmppos1= gangart[1]*2;
    if (figurnrfb[1] > 0)
      bmppos1++;
    signed long bmppos2= gangart[2]*2;
    if (figurnrfb[2] > 0)
      bmppos2++;
    signed long bmppos3= gangart[3]*2;
    if (figurnrfb[3] > 0)
      bmppos3++;
    signed long bmppos4= gangart[4]*2;
    if (figurnrfb[4] > 0)
      bmppos4++;
    pbrett[standort[1]]+= bmppos1;
    pbrett[standort[2]]+= bmppos2;
    pbrett[standort[3]]+= bmppos3;
    pbrett[standort[4]]+= bmppos4;
    pbrett[64]= 65 + amzug;
    }

  // Hinzugfelder der besten Züge anzeigen
  void setbestfelder (signed long ppos, signed long pvonfeld, signed long* pbrett)
    {
    // Folgepositionen ermitteln
    signed long hinpos[257];
    testepos (ppos, &*hinpos);
    signed long standort[65];
    memset (standort, 0, 65*sizeof (*standort));
    signed long amzug= 0;
    setstandorte (ppos, &*standort, &amzug);
    signed long af1, af2, af3, af4;
    // Figurfelder speichern
    af1= standort[1];
    af2= standort[2];
    af3= standort[3];
    af4= standort[4];
    // Beste Bewertung unter den Folgepositionen finden
    signed long extpos= -bewmax*amzug;
    for (signed long zposlauf= 0; zposlauf < hinpos[256]; zposlauf++)
      {
      signed long bewertung= endspiel[hinpos[zposlauf]];
      extpos= (extpos + bewertung + amzug*abs (extpos - bewertung))/2;
      }
    signed long feldbrett[64];
    memset (feldbrett, 0, 64*sizeof(*feldbrett));
    //  besten bzw. schlechtesten Zug heraussuchen
    for (signed long zposlauf= 0; zposlauf < hinpos[256]; zposlauf++)
      {
      if ((abs (extpos) < bewmax - 1) && (endspiel[hinpos[zposlauf]] == extpos))
        {
        setstandorte (hinpos[zposlauf], &*standort, &amzug);
        setbrett (&*standort, &*pbrett);
        if ((standort[1] != 64) && (standort[1] != af1)) feldbrett[standort[1]]= 1;
        if ((standort[2] != 64) && (standort[2] != af2)) feldbrett[standort[2]]= 2;
        if ((standort[3] != 64) && (standort[3] != af3)) feldbrett[standort[3]]= 3;
        if ((standort[4] != 64) && (standort[4] != af4)) feldbrett[standort[4]]= 4;
        }
      }
    setstandorte (ppos, &*standort, &amzug);
    // Figur ermitteln, auf die mit Rechts geklickt wurde um deren beste Züge im Brett zu speichern
    signed long figurvonfeld= 0;
    if (standort[1] == pvonfeld)
      figurvonfeld= 1;
    if (standort[2] == pvonfeld)
      figurvonfeld= 2;
    if (standort[3] == pvonfeld)
      figurvonfeld= 3;
    if (standort[4] == pvonfeld)
      figurvonfeld= 4;
    setvisbrett (ppos, pbrett);
    for (signed long feldlauf= 0; feldlauf < 64; feldlauf++)
      {
      if (feldbrett[feldlauf] != 0)
        {
        if (feldbrett[feldlauf] == figurvonfeld)
          pbrett[feldlauf]= 68;
        if (0 == figurvonfeld)
          pbrett[feldlauf]= 68;
        }
      }
    }

  signed long ziehpos (signed long ppos, signed long pvonfeld, signed long phinfeld)
    {
    signed long standort[65];
    signed long amzug= 0;
    if (pvonfeld == phinfeld)
      {
      setstandorte (ppos, &*standort, &amzug);
      //amzug*= -1;
      return getnumber (&*standort, amzug);
      }
    setstandorte (ppos, &*standort, &amzug);
    signed long brett[65];
    setbrett (&*standort, &*brett);
    standort[abs (brett[phinfeld])]= 64;
    standort[abs (brett[pvonfeld])]= phinfeld;
    amzug*= -1;
    return getnumber (&*standort, amzug);
    }

  void brauseendspiel (signed long ppos)
    {
    signed long brett[65];
    signed long standort[65];
    signed long amzug;
    cxschachbrett schachbrett;
    signed long action;
    signed long vonfeld= 0, hinfeld= 0;
    while (1)
      {
      setbestfelder (ppos, vonfeld, brett);
      setvisbrett (ppos, brett);
      schachbrett.putbrett (brett);
      if (endspiel[ppos] == 0)
        printf ("Stellung: %10ld Remis\n", ppos);
      if (endspiel[ppos] == bewmax - 2)
        printf ("Stellung: %10ld Matt\n", ppos);
      if (endspiel[ppos] == -(bewmax - 2))
        printf ("Stellung: %10ld Matt s\n", ppos);
      if (endspiel[ppos] == bewmax - 1)
        printf ("Stellung: %10ld Schlagposition w\n", ppos);
      if (endspiel[ppos] == -(bewmax - 1))
        printf ("Stellung: %10ld Schlagposition s\n", ppos);
      if (endspiel[ppos] == bewmax)
        printf ("Stellung: %10ld Gewinn w\n", ppos);
      if (endspiel[ppos] == -bewmax)
        printf ("Stellung: %10ld Gewinn s\n", ppos);
      if (abs (endspiel[ppos]) == 1)
        printf ("Stellung: %10ld ungültige Stellung\n", ppos);
      if ((endspiel[ppos] > 0) && (endspiel[ppos] < bewmax - 2))
          printf ("Stellung: %10ld Matt in %6.1f\n", ppos,  ((bewmax - 2) - abs (endspiel[ppos]))/2.);
      if ((endspiel[ppos] < 0) && (endspiel[ppos] > -(bewmax - 2)))
          printf ("Stellung: %10ld Matt in %6.1f\n", ppos, -((bewmax - 2) - abs (endspiel[ppos]))/2.);
      do
        {
        setstandorte (ppos, &*standort, &amzug);
        action= schachbrett.getgezogen (&vonfeld, &hinfeld);
        if (action == 2)
          {
          if (vonfeld == 0)
            ppos= maxposw;
          if (vonfeld == 1)
            ppos= maxposs;
          }
        if (action == 3)
          {
          setbestfelder (ppos, vonfeld, brett);
          schachbrett.putbrett (brett);
          }
        if (action == -3)
          {
          setvisbrett (ppos, brett);
          schachbrett.putbrett (brett);
          }
        }
      while ((action >= 2) || (action == -3) || (action == 0));
      if (abs (action) == 1)
        {
        ppos= ziehpos (ppos, vonfeld, hinfeld);
        setvisbrett (ppos, brett);
        schachbrett.putbrett (brett);
        ppos= ziehebesterst (ppos);
        }
      }
    }

// längste Zugfolge bei geschlagener 3. und 4. Figur (um 2-Steiner Maximalposition zu bekommen)
  void getextrempos2 ()
    {
    signed long bestposw= 0, bestposs= 0;
    signed long bestbeww= bewmax;
    signed long bestbews= -bewmax;
    signed long standort[65];
    signed long amzug;
    for (signed long poslauf= 0; poslauf < endmax; poslauf++)
      {
      setstandorte (poslauf, &*standort, &amzug);
      if ((standort[4] != 64) || (standort[3] != 64))
        continue;
      if (endspiel[poslauf] != 0)
        {
        if ((endspiel[poslauf] > 0) && (endspiel[poslauf] < bestbeww))
          {
          bestbeww= endspiel[poslauf];
          bestposw= poslauf;
          }
        if ((endspiel[poslauf] < 0) && (endspiel[poslauf] > bestbews))
          {
          bestbews= endspiel[poslauf];
          bestposs= poslauf;
          }
        }
      }
    maxposw= bestposw;
    maxposs= bestposs;
    printf ("maxposw: %11ld %8d Matt in %6.1f\n", maxposw, endspiel[maxposw],  ((bewmax - 2) - endspiel[maxposw])/2.);
    printf ("maxposs: %11ld %8d Matt in %6.1f\n", maxposs, endspiel[maxposs], -((bewmax - 2) + endspiel[maxposs])/2.);
    }

// längste Zugfolge bei geschlagener 4. Figur (um 3-Steiner Maximalposition zu bekommen)
  void getextrempos3 ()
    {
    signed long bestposw= 0, bestposs= 0;
    signed long bestbeww= bewmax;
    signed long bestbews= -bewmax;
    signed long standort[65];
    signed long amzug;
    for (signed long poslauf= 0; poslauf < endmax; poslauf++)
      {
      setstandorte (poslauf, &*standort, &amzug);
      if (standort[4] != 64)
        continue;
      if (endspiel[poslauf] != 0)
        {
        if ((endspiel[poslauf] > 0) && (endspiel[poslauf] < bestbeww))
          {
          bestbeww= endspiel[poslauf];
          bestposw= poslauf;
          }
        if ((endspiel[poslauf] < 0) && (endspiel[poslauf] > bestbews))
          {
          bestbews= endspiel[poslauf];
          bestposs= poslauf;
          }
        }
      }
    maxposw= bestposw;
    maxposs= bestposs;
    printf ("maxposw: %11ld %8d Matt in %6.1f\n", maxposw, endspiel[maxposw],  ((bewmax - 2) - endspiel[maxposw])/2.);
    printf ("maxposs: %11ld %8d Matt in %6.1f\n", maxposs, endspiel[maxposs], -((bewmax - 2) + endspiel[maxposs])/2.);
    }

  void getextrempos ()
    {
    signed long bestposw= 0, bestposs= 0;
    signed long bestbeww= bewmax;
    signed long bestbews= -bewmax;
    for (signed long poslauf= 0; poslauf < endmax; poslauf++)
      {
      if (endspiel[poslauf] != 0)
        {
        if ((endspiel[poslauf] > 0) && (endspiel[poslauf] < bestbeww))
          {
          bestbeww= endspiel[poslauf];
          bestposw= poslauf;
          }
        if ((endspiel[poslauf] < 0) && (endspiel[poslauf] > bestbews))
          {
          bestbews= endspiel[poslauf];
          bestposs= poslauf;
          }
        }
      }
    maxposw= bestposw;
    maxposs= bestposs;
    printf ("maxposw: %11ld %8d Matt in %6.1f\n", maxposw, endspiel[maxposw],  ((bewmax - 2) - endspiel[maxposw])/2.);
    printf ("maxposs: %11ld %8d Matt in %6.1f\n", maxposs, endspiel[maxposs], -((bewmax - 2) + endspiel[maxposs])/2.);
    }

  void testdieder ()
    {
    for (signed long lauf= 0; lauf < endmax; lauf++)
      {
      printf ("Position: %11ld   Bewertung %11d\n", lauf, endspiel[lauf]);
      signed long standort[5];
      signed long amzug;
      signed long feld1, feld2, feld3, feld4;
      setstandorte (lauf, &*standort, &amzug);
      feld1= standort[1];
      feld2= standort[2];
      feld3= standort[3];
      feld4= standort[4];
      signed long dstellung;
      for (signed long symlauf= 1; symlauf < 8; symlauf++)
        {
        standort[1]= dieder[symlauf][feld1];
        standort[2]= dieder[symlauf][feld2];
        standort[3]= dieder[symlauf][feld3];
        standort[4]= dieder[symlauf][feld4];
        dstellung= getnumber (&*standort, amzug);
        printf ("  Diederstellung: %11ld Bewertung: %8d   \n", dstellung, endspiel[dstellung]);
        }
      }
    }

  };

// ------------------------------------------------------ Threadprogrammierung -----------------------------------------------------------
cvier steiner;

void* arbeit (void*)
  {
  steiner.pass ();
  return 0;
  }

signed long tiefe;

void* threadrekursiv (void*)
  {
  if (tiefe <= 0)
    return 0;
//  printf("Start Thread %2ld\n", tiefe);
  signed long loctiefe= tiefe;
  pthread_t thid;
  signed long thres;
  if (loctiefe > 1)
    {
    tiefe--;
    thres= pthread_create (&thid, NULL, threadrekursiv, NULL);
    if (thres)
      printf ("Threaderzeugung fehlgeschlagen\n");
    }
  arbeit (0);
  if (loctiefe > 1)
    {
//    printf("Warten Thread        %4ld auf %2ld\n", loctiefe, loctiefe - 1);
    pthread_join (thid, NULL);
    }
//  printf("Exit Thread %4ld\n", loctiefe);
  return 0;
  }

// ------------------------------------------------------ Hauptprogramm -----------------------------------------------------------
int main (int argc, char** argv)
  {
  if (argc != 2)
    {
    printf ("Endspieldatei angeben\n");
    return 0;
    }
///*
  steiner.initfiguren (1, -1, 12, -8);
  steiner.setthreadanz (4);
  printf ("analysiere...\n");
  signed long illegalpos= steiner.setillegalpos ();
  printf ("%9ld illegale Positionen\n\n", illegalpos);
  signed long bewanz= steiner.setendpos11 ();
  signed long sum= 0;
  signed long ebene= 0;
    do
    {
    sum+= bewanz;
    printf ("Ebene:%2ld                bewertet: %10.6f Mio     Summe: %10.6f Mio\n", ebene, bewanz/1.e6, sum/1.e6);
    ebene++;
    steiner.passnr= 0;
    steiner.passfarbe= 0;
    tiefe= steiner.threadanz;
    threadrekursiv (0);
    bewanz= 0;
    for (signed long tlauf= 0; tlauf < steiner.threadanz; tlauf++)
      bewanz+= steiner.passret[tlauf];
    steiner.passnr= 0;
    steiner.passfarbe= 1;
    tiefe= steiner.threadanz;
    threadrekursiv (0);
    for (signed long tlauf= 0; tlauf < steiner.threadanz; tlauf++)
      bewanz+= steiner.passret[tlauf];
    }
  while (bewanz);
  printf ("%10.6f Millionen Stellungen bewertet\n", sum/1.e6);
  printf ("\n");

  steiner.getextrempos ();
  steiner.saveendspiel (argv[1]);
//*/
  steiner.ladeendspiel (argv[1]);
  steiner.brauseendspiel (steiner.maxposw);
  return 0;
  }
