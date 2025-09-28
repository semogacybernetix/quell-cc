// Version multithread 2018 abgeleitet von multithread2015-geht

// Version ab Benutzung der Symmetriefunktion für symmetrische Stellungen
// letzte Version vor Implementierung der Multicoreversion
// 0 leer, 1 Koenig, 2 Springer, 4 Läufer, 8 Turm
// 12 Dame 10 Marshall, 6 Janus
// 14 Amazone
// 3 Superspringer, 5 Superläufer, 9 Superturm

/*
2015.09.16
Klassen auslagern verringert Performance stark. Fehler Segfault in diederstellungen gefunden char bla = short* blubb[22] Compiler meckert nicht
Symmetrie ausnutzen bringt keinen Performance Gewinn, maximalen Bewertungswert erniedrigt um ungültige Stellungen markieren zu können
Problem Pattstellungen: Sie werden immer wieder neu bewertet, weil mit 0 (Remis) gekennzeichnet und deshalb immer wieder getestet wird, ob sie in
den höheren Ebenen nicht doch eine Gewinnstellung sein könnten

2015.09.19
Multithreading geschafft, noch Ungleichgewichte in den Threads, Verbesserung durch Zufallsbijektion und damit statistische Ausgleichung

2018.04.14 kleinere Kosmetik, Ausgangsversion für weitere Programmierungen
*/

#include "../../cc/screen/allscr.h"
#include "../../xwindow/screen/xscr.h"

#include <cstring>    // memset
#include <iostream>   // abs, printf

//------------------------------ Klasse Schachbrett ------------------------------------------------------------------------

struct cxschachbrett
  {
  cbmpdatei*  feldbmp[256];  // Bilder der Figuren schwarz und weiß
  cxscreen*   bscreen;
  signed long brett[65];  // auf dem 65. Feld steht welche Farbe am Zug ist

  cxschachbrett ()
    {
// --------------------------- dunkle Felder --------------------------------------------------------------------------------------------

    feldbmp[0]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/ld.bmp");          // leeres dunkles Feld
                                                                                    // leeres Feld hat keine Farbe

    feldbmp[2]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/fsd.bmp");         // Fers schwarz dunkles Feld
    feldbmp[3]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/fwd.bmp");         // Fers weiß dunkles Feld

    feldbmp[4]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/wsd.bmp");         // Wesir schwarz dunkles Feld
    feldbmp[5]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/wwd.bmp");         // Wesir weiß dunkles Feld

    feldbmp[6]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/ksd.bmp");         // König schwarz dunkles Feld
    feldbmp[7]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/kwd.bmp");         // König weiß dunkles Feld

    feldbmp[8]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/ssd.bmp");         // Springer schwarz dunkles Feld
    feldbmp[9]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/swd.bmp");         // Springer weiß dunkles Feld

    feldbmp[10]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/ssd.bmp");        // Fersspringer schwarz dunkles Feld
    feldbmp[11]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/swd.bmp");        // Fersspringer weiß dunkles Feld

    feldbmp[12]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/ssd.bmp");        // Wesirspringer schwarz dunkles Feld
    feldbmp[13]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/swd.bmp");        // Wesirspringer weiß dunkles Feld

    feldbmp[14]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/gssd.bmp");       // Königsspringer schwarz dunkles Feld
    feldbmp[15]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/gswd.bmp");       // Königsspringer weiß dunkles Feld

    feldbmp[16]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/lsd.bmp");        // Läufer schwarz dunkel
    feldbmp[17]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/lwd.bmp");        // Läufer weiß dunkel

    feldbmp[20]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/glsd.bmp");       // Wesirläufer schwarz dunkel
    feldbmp[21]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/glwd.bmp");       // Wesirläufer schwarz hell

    feldbmp[24]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/esd.bmp");        // Janus   (Erzbischof)
    feldbmp[25]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/ewd.bmp");

    feldbmp[28]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/kasd.bmp");       // Wesirjanus
    feldbmp[29]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/kawd.bmp");

    feldbmp[32]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/tsd.bmp");        // Turm
    feldbmp[33]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/twd.bmp");

    feldbmp[34]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/gtsd.bmp");       // Fersturm
    feldbmp[35]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/gtwd.bmp");

    feldbmp[40]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/basd.bmp");       // Marshall
    feldbmp[41]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/bawd.bmp");

    feldbmp[42]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/gbasd.bmp");      // Fersmarschall
    feldbmp[43]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/gbawd.bmp");

    feldbmp[48]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/dsd.bmp");        // Dame
    feldbmp[49]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/dwd.bmp");

    feldbmp[56]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/gdsd.bmp");       // Amazone
    feldbmp[57]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/gdwd.bmp");

// --------------------------- helle Felder --------------------------------------------------------------------------------------------

    feldbmp[64]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/lh.bmp");              // leeres dunkles Feld
                                                                                         // leeres Feld hat keine Farbe

    feldbmp[64 + 2]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/fsh.bmp");         // Fers schwarz dunkles Feld
    feldbmp[64 + 3]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/fwh.bmp");         // Fers weiß dunkles Feld

    feldbmp[64 + 4]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/wsh.bmp");         // Wesir schwarz dunkles Feld
    feldbmp[64 + 5]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/wwh.bmp");         // Wesir weiß dunkles Feld

    feldbmp[64 + 6]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/ksh.bmp");         // König schwarz dunkles Feld
    feldbmp[64 + 7]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/kwh.bmp");         // König weiß dunkles Feld

    feldbmp[64 + 8]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/ssh.bmp");         // Springer schwarz dunkles Feld
    feldbmp[64 + 9]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/swh.bmp");         // Springer weiß dunkles Feld

    feldbmp[64 + 10]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/ssh.bmp");        // Fersspringer schwarz dunkles Feld
    feldbmp[64 + 11]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/swh.bmp");        // Fersspringer weiß dunkles Feld

    feldbmp[64 + 12]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/ssh.bmp");        // Wesirspringer schwarz dunkles Feld
    feldbmp[64 + 13]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/swh.bmp");        // Wesirspringer weiß dunkles Feld

    feldbmp[64 + 14]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/gssh.bmp");       // Königsspringer schwarz dunkles Feld
    feldbmp[64 + 15]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/gswh.bmp");       // Königsspringer weiß dunkles Feld

    feldbmp[64 + 16]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/lsh.bmp");        // Läufer schwarz dunkel
    feldbmp[64 + 17]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/lwh.bmp");        // Läufer weiß dunkel

    feldbmp[64 + 20]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/glsh.bmp");       // Wesirläufer schwarz dunkel
    feldbmp[64 + 21]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/glwh.bmp");       // Wesirläufer schwarz hell

    feldbmp[64 + 24]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/esh.bmp");        // Janus   (Erzbischof)
    feldbmp[64 + 25]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/ewh.bmp");

    feldbmp[64 + 28]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/kash.bmp");       // Wesirjanus
    feldbmp[64 + 29]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/kawh.bmp");

    feldbmp[64 + 32]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/tsh.bmp");        // Turm
    feldbmp[64 + 33]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/twh.bmp");

    feldbmp[64 + 34]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/gtsh.bmp");       // Fersturm
    feldbmp[64 + 35]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/gtwh.bmp");

    feldbmp[64 + 40]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/bash.bmp");       // Marshall
    feldbmp[64 + 41]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/bawh.bmp");

    feldbmp[64 + 42]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/gbash.bmp");      // Fersmarschall
    feldbmp[64 + 43]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/gbawh.bmp");

    feldbmp[64 + 48]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/dsh.bmp");        // Dame
    feldbmp[64 + 49]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/dwh.bmp");

    feldbmp[64 + 56]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/gdsh.bmp");       // Amazone
    feldbmp[64 + 57]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/gdwh.bmp");

// --------------------------- Grafikelemente Brett ----------------------------------------------------------------------------------------

    feldbmp[128]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/samzug.bmp");
    feldbmp[130]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/wamzug.bmp");
    feldbmp[134]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/menuleiste.bmp");
    feldbmp[136]= new cbmpdatei ("/root/quell-cc/all/ebrauser/sfig/lr.bmp");              // oranges Hervorhebungsfeld

    bscreen= new cxscreen ("xebrauser", 521, 534);
    memset (brett, -1, 64*sizeof(*brett));
    bscreen->putscreen (*feldbmp[134], 26, 521);                      // Menüleiste zeichen
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
      bscreen->putscreen (*feldbmp[brett[64]], 1, 521);        // zeichnen, welche Farbe gerade am Zug ist
      bscreen->putscreen (*feldbmp[134], 26, 521);             // Menüleiste zeichnen
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
    integer mausx, mausy;
    integer feldx, feldy;
    integer expxmin, expxmax, expymin, expymax, expose;
    integer action;
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
  const signed long endfarbe= 65*65*65*65;
  const signed long endmax= 65*65*65*65*2;
  const signed long bewmax= (1 << 15) - 4;   // bewmax + 1: ungültige Stellungen
  signed long  dieder[8][65];
  signed long  gangart[5];    // bitcodiert: König, Springer, Läufer, Turm, 0 = leeres Feld
  signed long  figurnrfb[5];  // Figurnummerfarbe Betrag ist die Figurnummer, Vorzeichen die Farbe
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

  // Stellungsnummer -> Standorte, Amzug  (Umkehrfunktion zu getnumber) Rückgabewert 0 wenn ungültige Standorte (Figuren auf gleichem Feld)
  // standort[0] undefiniert
  // undefinierte Werte wenn Rückgabe 0 deswegen immer mit if setstandorte
  bool setstandorte (signed long pstellungsnr, signed long* pstandort, signed long* pamzug)
    {
    pstandort[1]= pstellungsnr % 65;
    pstandort[2]= (pstellungsnr % 4225)/65;
    // Stellungen mit Figuren mit gleichem Brettfeld als ungültig markieren
    if ((pstandort[1] != 64) && (pstandort[2] == pstandort[1]))
      return 0;
    pstandort[3]= (pstellungsnr % 274625)/4225;
    if ((pstandort[3] != 64) && ((pstandort[3] == pstandort[2]) || (pstandort[3] == pstandort[1])))
      return 0;
    pstandort[4]= (pstellungsnr % 17850625)/274625;
    if ((pstandort[4] != 64) && ((pstandort[4] == pstandort[3]) || (pstandort[4] == pstandort[2]) || (pstandort[4] == pstandort[1])))
      return 0;
    *pamzug= 1 - (pstellungsnr/17850625)*2;
    return 1;
    }

  // Standorte -> Brett
  void setbrett (signed long* pstandort, signed long* pbrett)
    {
    memset (&*pbrett, 0, 64*sizeof (*pbrett));
    pbrett[pstandort[1]]= figurnrfb[1];
    pbrett[pstandort[2]]= figurnrfb[2];
    pbrett[pstandort[3]]= figurnrfb[3];
    pbrett[pstandort[4]]= figurnrfb[4];
    }

// --------------------------- Zuggenerator ---------------------------------------------

bool linksok (signed long pfeld)
  {
  return (pfeld % 8);
  }

bool dlinksok (signed long pfeld)
  {
  if ((pfeld % 8) > 1) return 1;
  return 0;
  }

bool rechtsok (signed long pfeld)
  {
  if ((pfeld % 8) < 7) return 1;
  return 0;
  }

bool drechtsok (signed long pfeld)
  {
  if ((pfeld % 8) < 6) return 1;
  return 0;
  }

bool obenok (signed long pfeld)
  {
  if (pfeld < 56) return 1;
  return 0;
  }

bool dobenok (signed long pfeld)
  {
  if (pfeld < 48) return 1;
  return 0;
  }

bool untenok (signed long pfeld)
  {
  if (pfeld > 7) return 1;
  return 0;
  }

bool duntenok (signed long pfeld)
  {
  if (pfeld > 15) return 1;
  return 0;
  }

void testewesir (signed long pfeldnr, const signed long* pbrett, signed long* phinfeld)
  {
  signed long farbe= pbrett[pfeldnr];
  if (linksok (pfeldnr) && ((farbe*pbrett[pfeldnr - 1]) <= 0))
    {
    phinfeld[phinfeld[64]]= pfeldnr - 1;
    phinfeld[64]++;
    }
  if (rechtsok (pfeldnr) && ((farbe*pbrett[pfeldnr + 1]) <= 0))
    {
    phinfeld[phinfeld[64]]= pfeldnr + 1;
    phinfeld[64]++;
    }
  if (obenok (pfeldnr) && ((farbe*pbrett[pfeldnr + 8]) <= 0))
    {
    phinfeld[phinfeld[64]]= pfeldnr + 8;
    phinfeld[64]++;
    }
  if (untenok (pfeldnr) && ((farbe*pbrett[pfeldnr - 8]) <= 0))
    {
    phinfeld[phinfeld[64]]= pfeldnr - 8;
    phinfeld[64]++;
    }
  }

void testefers (signed long pfeldnr, const signed long* pbrett, signed long* phinfeld)
  {
  signed long farbe= pbrett[pfeldnr];
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

// Bit 0,1,2,3,4 : Fers, Wesir, Springer, Läufer, Turm
void testefigur (signed long pfeldnr, const signed long* pbrett, signed long* phinfeld)
  {
  phinfeld[64]= 0;
  if (gangart[abs (pbrett[pfeldnr])] & 1)
    testefers (pfeldnr, &*pbrett, &*phinfeld);
  if (gangart[abs (pbrett[pfeldnr])] & 2)
    testewesir (pfeldnr, &*pbrett, &*phinfeld);
  if (gangart[abs (pbrett[pfeldnr])] & 4)
    testespringer (pfeldnr, &*pbrett, &*phinfeld);
  if (gangart[abs (pbrett[pfeldnr])] & 8)
    testelaeufer (pfeldnr, &*pbrett, &*phinfeld);
  if (gangart[abs (pbrett[pfeldnr])] & 16)
    testeturm (pfeldnr, &*pbrett, &*phinfeld);
  }

// Folgepositionen aller möglichen Züge in hinpos sammeln
void testepos (signed long pstellungsnr, signed long* phinpos)
  {
  signed long standort[5];
  signed long amzug;
  phinpos[256]= 0;
  if (!setstandorte (pstellungsnr, &*standort, &amzug)) return;
  signed long brett[65];
  setbrett (&*standort, &*brett);
  signed long hinfeld[65];
  for (signed long figurlauf= 1; figurlauf < 5; figurlauf++)
    if ((standort[figurlauf] != 64) && (figurnrfb[figurlauf]*amzug > 0))
      {
      testefigur (standort[figurlauf], &*brett, &*hinfeld);
      for (signed long feldlauf= 0; feldlauf < hinfeld[64]; feldlauf++)
        {
        standort[figurlauf]= hinfeld[feldlauf];
        standort[abs (brett[hinfeld[feldlauf]])]= 64;
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
  if (setstandorte (ppos, &*standort, &amzug))
    {
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
  }

// Gewinnpositionen setzen (König wurde gerade geschlagen (bewmax, -bewmax))
signed long setendpos ()
  {
  printf ("Ebene: -1 Gewinnpositionen setzen\n");
  memset (endspiel, 0, endmax*sizeof (*endspiel));
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
    if (setstandorte (poslauf, &*standort, &amzug))
      {
//      if ((standort[1] != 64) && (standort[2] == 64) && (amzug == -1))     // Gewinnstellung für weiss, wenn weißer König existiert und schwarzer König geschlagen ist und schwarz am Zug ist
      if ((standort[1] == 64) && (amzug == -1))     // Gewinnstellung für weiss, wenn schwarzer König geschlagen ist und schwarz am Zug ist
        {
        endspiel[poslauf]= bewmax;
        bewanz++;
        }
//      if ((standort[1] == 64) && (standort[2] != 64) && (amzug == 1))      // Gewinnstellung für schwarz, wenn schwarzer König existiert und weißer König geschlagen ist und weiß am Zug ist
      if ((standort[1] != 64) && (standort[2] == 64) && (standort[3] == 64) && (standort[4] == 64) && (amzug == 1))      // Gewinnstellung für schwarz, wenn schwarzer König existiert alle weißen Figuren geschlagen sind und weiß am Zug ist
        {
        endspiel[poslauf]= -bewmax;
        bewanz++;
        }
      }
      else  // if setstandorte
        endspiel[poslauf] = -bewmax -1;   // ungültige Stellungen markieren
    }
  printf ("\n");
  return bewanz;
  }

void pass ()
  {
  passnr++;
  signed long lthreadnr= passnr - 1;
  signed long bewanz= 0;
  signed long standort[5];
  signed long amzug;
  signed long hinpos[257];
  //Grenzen ausrechnen
  signed long anfpos= (endfarbe*lthreadnr)/threadanz + endfarbe*passfarbe;
  signed long endpos= (endfarbe*(lthreadnr + 1))/threadanz + endfarbe*passfarbe;
  printf ("pass: Thread %2ld/%2ld gestartet\n", lthreadnr, threadanz);
  for (signed long poslauf= anfpos; poslauf < endpos; poslauf++)
    {
    // bearbeitete Stellungen ausgeben
    if (!(poslauf % 1000000))
      {
      printf ("%10ld %11.3Lf\n", poslauf, (long double) (bewanz/1000.));
      fflush (stdout);
      }

    //
//    if ((endspiel[poslauf] == 0) && (setstandorte (poslauf, &*standort, &amzug)) && (standort[1] != 64) && (standort[2] != 64))  // beide Könige da
    if ((endspiel[poslauf] == 0) && (setstandorte (poslauf, &*standort, &amzug)))  // beide Könige (standort1, standort2) müssen nicht da sein (allgemeiner)
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

       if (extpos != 0)
        {
        endspiel[poslauf]= extpos - extpos/abs (extpos);  // Position  eine Stufe höher bewerten
        bewanz++;
//        bewertediederstellungen (poslauf);  // die ermittelte Bewertung in die anderen 7 symmetrischen Positionen speichern
//        bewanz+= 7;
        // Pattstellungen als Remis kennzeichnen (Zugfarbe wechseln und kucken ob das eine Schlagstellung ist)
        if (abs (endspiel[poslauf]) == bewmax - 2)
          {
          if (endspiel[getnumber (&*standort, -amzug)] != amzug*(1 - bewmax))
            {
            endspiel[poslauf]= 0;
            bewanz--;
//            bewertediederstellungen (poslauf);  // die ermittelte Bewertung in die anderen 7 symmetrischen Positionen speichern
//            bewanz-= 7;
            }
          }
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
    fret+= 0;                 // Variable benutzen
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
        if ((lx + ly + 1) & 1)                          // Brett kariert färben
          pbrett[8*ly + lx]= 0;
          else
          pbrett[8*ly + lx]= 64;
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
    pbrett[64]= 129 + amzug;
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
          pbrett[feldlauf]= 136;                     // oranges Hervorhebungsfeld
        if (0 == figurvonfeld)
          pbrett[feldlauf]= 136;                     // oranges Hervorhebungsfeld
        }
      }
    }

  signed long ziehpos (signed long ppos, signed long pvonfeld, signed long phinfeld)
    {
    signed long standort[65]= {0};
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
      if (setstandorte (lauf, &*standort, &amzug))
        {
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
    }

  };

// ------------------------------------------------------ Hauptprogramm -----------------------------------------------------------
int main (int argc, char** argv)
  {
  cvier steiner;
  if (argc != 2)
    {
    printf ("Endspieldatei angeben\n");
    return 0;
    }
  steiner.ladeendspiel (argv[1]);
  steiner.brauseendspiel (steiner.maxposw);
  return 0;
  }
