// Version multithread 2018 abgeleitet von multithread2015-geht

// Version ab Benutzung der Symmetriefunktion für symmetrische Stellungen
// letzte Version vor Implementierung der Multicoreversion

/*
2015.09.16
Klassen auslagern verringert Performance stark. Fehler Segfault in diederstellungen gefunden char bla = short* blubb[22] Compiler meckert nicht
Symmetrie ausnutzen bringt keinen Performance Gewinn, maximalen Bewertungswert erniedrigt um ungültige Stellungen markieren zu können
Problem Pattstellungen: Sie werden immer wieder neu bewertet, weil mit 0 (Remis) gekennzeichnet und deshalb immer wieder getestet wird, ob sie in
den höheren Ebenen nicht doch eine Gewinnstellung sein könnten

2015.09.19
harter Nachteil Threads: nicht kompatibel mit Klassendesign, weil Threadfunktion keine Memberfunktion sein darf
Multithreading geschafft, noch Ungleichgewichte in den Threads, Verbesserung durch Zufallsbijektion und damit statistische Ausgleichung

2018.04.14 kleinere Kosmetik, Ausgangsversion für weitere Programmierungen

2024.07.08 Fehler behoben, das Endlosschleife bei 5 oder mehr Threads auftritt: passret nicht dynamisch allozieren sondern statisch anlegen
*/

#include <cstring>       // memset
#include <iostream>      // abs, printf
#include <pthread.h>     // threads
#include <sys/times.h>   // Zeitmessung
#include <unistd.h>      // Zeitmessung

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
  // signed long  hinpos[257];   // Liste der Folgepositionen (Zugmöglichkeiten einer Stellung)

  // Endspielarray
  signed short* endspiel;

  // Threadverwaltung
  signed long  threadanz;
  signed long  passret[1000]; // maximal 1000 Threads
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
    }

  void setthreadanz (signed long pthreadanz)
    {
    threadanz= pthreadanz;
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

// Ein Feld in gerader Richtung
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

// Ein Feld in schräger Richtung
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
  if (!setstandorte (pstellungsnr, &*standort, &amzug))
    return;
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

// -------------------- Gewinnpositionen setzen (König wurde gerade geschlagen (bewmax, -bewmax)) --------------------------------------------
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
      if ((standort[1] != 64) && (standort[2] == 64) && (amzug == -1))     // Gewinnstellung für weiss wenn weißer König existiert, schwarzer König geschlagen ist und schwarz am Zug ist (reguläres Spiel mit 2 Königen)
//      if ((standort[2] == 64) && (amzug == -1))                          // Gewinnstellung für weiss wenn schwarzer König geschlagen ist und schwarz am Zug ist (3 weiße Figuren gegen schwarzen König)
//      if ((standort[2] == 64) && (amzug == -1) && (standort[4] == 64))     // Gewinnstellung für weiss wenn schwarzer König geschlagen ist und schwarz am Zug ist und die 3.Figur fehlt (2 weiße Figuren gegen schwarzen König)
        {
        endspiel[poslauf]= bewmax;
        bewanz++;
        }
      if ((standort[1] == 64) && (standort[2] != 64) && (amzug == 1))      // Gewinnstellung für schwarz wenn weißer König geschlagen ist, schwarzer König existiert und weiß am Zug ist (reguläres Spiel mit 2 Königen)
//      if ((standort[1] == 64) && (standort[2] != 64) && (standort[3] == 64) && (standort[4] == 64) && (amzug == 1))
          // Gewinnstellung für schwarz, wenn schwarzer König existiert alle anderen Figuren (weiß) geschlagen sind und weiß am Zug ist (schwarzer König gegen 3 weiße Figuren)
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

// ---------------------------------------------------------------------------------------------------------------------------------------------
void pass ()
  {
  // Variablen
  signed long bewanz= 0;
  signed long standort[5];
  signed long amzug;
  signed long hinpos[257];

  passnr++;
  signed long lthreadnr= passnr - 1;   //lokale Threadnummer festlegen
  
  //Grenzen ausrechnen
  signed long anfpos= (endfarbe*lthreadnr)/threadanz + endfarbe*passfarbe;
  signed long endpos= (endfarbe*(lthreadnr + 1))/threadanz + endfarbe*passfarbe;

  printf ("pass: Thread %2ld/%2ld gestartet  [%10ld  %10ld]\n", lthreadnr + 1, threadanz, anfpos, endpos - 1);
  for (signed long poslauf= anfpos; poslauf < endpos; poslauf++)
    {
    // bearbeitete Stellungen ausgeben
    if ((poslauf - anfpos) % 1000000 == 999999)
      {
      printf ("Thread:%3ld  %10ld %11.3Lf\n", lthreadnr + 1, poslauf - anfpos + 1, (long double) (bewanz/1000.));
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
  printf ("Thread %2ld/%2ld  beendet  passret:%10ld  ", lthreadnr + 1, threadanz, passret[lthreadnr]);
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
    pbrett[64]= 129 + amzug;    // Index für bmp-Amzug setzen
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

  };         // struct cvier

//------------ globaler Raum ------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------ Threadprogrammierung -----------------------------------------------------------

cvier            steiner;
signed long      rektiefe;                      // Rekursionstiefe
tms              zeit;
clock_t          startzeit, stopzeit;           // Zeitmessung

void* arbeit (void*)
  {
  steiner.pass ();
  printf ("Zeit: %5ld\n", times (&zeit) - startzeit);
  return 0;
  }

void* threadrekursiv (void*)
  {
  if (rektiefe == 0)
    return 0;

//  printf("Start Thread %2ld\n", rektiefe);
  signed long loctiefe= rektiefe;            // loktiefe: lokale Tiefe
  pthread_t thid;
  signed long thres;
  if (loctiefe > 1)
    {
    rektiefe--;
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
// Bit 0,1,2,3,4 : Fers (schräg ein Feld) (1), Wesir (gerade ein Feld) (2), Springer (4), Läufer (8), Turm (16)

// 1 Fers, 2 Wesir, 3 König
// 4 Springer, 5 Fersspringer, 6 Wesirspringer, 7 Königsspringer
// 8 Läufer, 10 Wesirläufer
// 16 Turm, 17 Fersturm
// 12 Janus, 20 Marshall, 24 Dame
// 14 Wesirjanus, 21 Fersmarshall, 28 Amazone

int main ()
  {
  long double ticksprosek=  (long double) (sysconf (_SC_CLK_TCK));
  char dateiname[256];

// --------------------- reguläres Spiel (1 gegen 1)
  steiner.initfiguren (3, -3, 24, -16);  // Dame gegen Turm                            35/18
//  steiner.initfiguren (3, -3, 24, -8);   // Dame gegen Läufer
//  steiner.initfiguren (3, -3, 24, -4);   // Dame gegen Springer
//  steiner.initfiguren (3, -3, 16, -8);   // Turm gegen Läufer
//  steiner.initfiguren (3, -3, 16, -4);   // Turm gegen Springer

//  steiner.initfiguren (3, -3, 24, -12);   // Dame gegen Janus
//  steiner.initfiguren (3, -3, 24, -20);   // Dame gegen Marschall
//  steiner.initfiguren (3, -3, 24, -17);   // Dame gegen Fersturm
//  steiner.initfiguren (3, -3, 24, -10);   // Dame gegen Wesirläufer
//  steiner.initfiguren (3, -3, 24, -5);   // Dame gegen Fersspringer
//  steiner.initfiguren (3, -3, 24, -6);   // Dame gegen Wesirspringer

//  steiner.initfiguren (3, -3, 12, -16);   // Janus gegen Turm
//  steiner.initfiguren (3, -3, 12, -20);   // Janus gegen Marshall

//  steiner.initfiguren (2, -2, 20, -6);   // Geradekönig + Marschall gegen Geradekönig + Geradespringer
//  steiner.initfiguren (1, -1, 12, -5);   //Schräg-König + Springerläufer gegen Schrägkönig + Schrägspringer

// ---------------------- reguläres Spiel (2 gegen 0)
//  steiner.initfiguren (3, -3,  8,  8);   // König gegen 2 Läufer                    19
//  steiner.initfiguren (3, -3,  8,  4);   // König gegen Läufer Springer             33

// ---------------------- 3 Figuren gegen König
//  steiner.initfiguren (4, -3, 4, 16);  // Springer, Springer, Turm gegen König       15
//  steiner.initfiguren (8, -3, 8, 16);  // Läufer, Läufer, Turm gegen König           21 nur gleichfarbige Läufer
//  steiner.initfiguren (4, -3, 8, 16);  // Springer, Läufer, Turm gegen König         15

//  steiner.initfiguren (4, -3, 4, 8);  // Springer, Springer, Läufer gegen König      29 + Remis
//  steiner.initfiguren (4, -3, 8, 8);  // Springer, Läufer, Läufer gegen König         1 + Remis
//  steiner.initfiguren (4, -3, 4, 4);  // 3 Springer  gegen König                     17 + Remis
//  steiner.initfiguren (8, -3, 8, 8);  // 3 Läufer  gegen König                        1 + Remis
//  steiner.initfiguren (16, -3, 16, 16);  // 2 Türme gegen König                       8

  sprintf (dateiname, "/root/Endspiel/dame-turm.end");

  steiner.setthreadanz (4);                  // +++++++++++++++++++++++++++++++++ Anzahl der parallel laufenden Threads definieren +++++++++++++++++++++++++++++++++++++++++++++++++++

  printf ("analysiere...\n");
  startzeit= times (&zeit);  // Startzeit speichern
  signed long bewanz= steiner.setendpos ();
  signed long sum= 0;
  signed long ebene= 0;
    do
    {
    sum+= bewanz;
    printf ("Ebene:%3ld                bewertet: %10.6f Mio     Summe: %10.6f Mio\n\n", ebene, bewanz/1.e6, sum/1.e6);
    ebene++;
    steiner.passnr= 0;
    steiner.passfarbe= 0;
    rektiefe= steiner.threadanz;
    threadrekursiv (0);
    printf ("\n");
    bewanz= 0;
    for (signed long tlauf= 0; tlauf < steiner.threadanz; tlauf++)
      {
//      printf ("schwarz: tlauf: %5ld  passret: %5ld\n", tlauf, steiner.passret[tlauf]);
      bewanz+= steiner.passret[tlauf];
      }
    steiner.passnr= 0;
    steiner.passfarbe= 1;
    rektiefe= steiner.threadanz;
    threadrekursiv (0);
    for (signed long tlauf= 0; tlauf < steiner.threadanz; tlauf++)
      {
//      printf ("weiss: tlauf: %5ld  passret: %5ld\n", tlauf, steiner.passret[tlauf]);
      bewanz+= steiner.passret[tlauf];
      }
    printf ("bewanz: %5ld\n\n", bewanz);
    }
  while (bewanz);
  stopzeit= times (&zeit);  // Stoppzeit speichern
  long double berechnungsdauer= (stopzeit - startzeit)/ticksprosek;
  printf ("%10.6f Millionen Stellungen bewertet\n\n", sum/1.e6);
  printf ("Sekundenbruchteile %10.0Lf \n", ticksprosek);
  printf ("Berechnungsdauer   %13.2Lf Sekunden\n\n", berechnungsdauer);
  steiner.getextrempos ();
  printf ("\nBerechnung fertig, Abspeichern\n");
  steiner.saveendspiel (dateiname);
  printf ("Spiel abgespeichert\n");
  return 0;
  }

/*
Dame-Turm Endspiel zum Benchmark


  Treads     Sekunden

Ryzen 5600G              6/12
    1         75.89
    2         38.41
    3         26.58
    4         20.38
    5         16.77
    6         14.08
    7         15.66
    8         14.28
    9         13.17
   10         12.24
   11         11.30
   12         10.56  10.49  10.39
   13         11.60
   14         11.64

Core I3 13100T  4/8
    1         68.25
    2         35.79
    3         25.93
    4         19.53
    5         19.87
    6         17.35
    7         15.75
    8         13.98  13.95  13.98
    9         14.94
   10         15.14

HP-Notebook Ryzen 5 3500U
    1        102.92
    2         53.98
    3         39.40
    4         31.31
    5         31.87
    6         28.16
    7         26.06
    8         24.24  24.18  24.20
    9         25.04
   10         25.12

Core I3 9100T            4/4
    1         95.28
    2         49.68
    3         34.63
    4         27.46  27.44  27.44
    5         29.08
    6         28.64

Jetson Nano Orin
    1        188.34
    2         94.03
    3         66.30
    4         47.96
    5         39.47
    6         35.83   36.10  36.04
    7         39.26
    8         39.08

Odroid H4 N97        4/4
    1        100.93
    2         63.70
    3         47.75
    4         37.37  37.38  37.34
    5         38.89
    6         38.97

Orange Pi 5          8/8
    1        161.76
    2         82.66
    3         57.52
    4         44.51
    5         52.38
    6         48.01
    7         42.17
    8         38.05  38.12  37.90
    9         39.37
   10         38.31
   12         39.63

Raspberry Pi 5       4/4
    1        153.76
    2         77.54
    3         54.08
    4         40.90  40.92  41.07
    5         43.07
    6         43.34

Pentium Silver J5040   4/4
    1        155.38
    2         83.94
    3         57.81
    4         43.66  43.70  43.65
    5         45.98
    6         44.88

Pentium Gold G5420T    2/4
    1        112.89
    2         57.44
    3         56.26
    4         49.79  49.80  49.80
    5         50.21
    6         49.91

Core2 Quad Q9550   2.83 MHz
    1        204.00
    2        103.71
    3         73.91
    4         55.56  55.54  55.57
    5         58.83
    6         57.07

Jetson Nano Xavier
    1        336.99
    2        169.41
    3        117.63
    4         88.41  88.43  88.14
    5         94.41
    6         91.47

Raspberry Pi 4 Model B Rev 1.1
    1        361.79
    2        184.34
    3        128.60
    4         97.72  97.23  97.50
    5         98.90
    6        103.87

AMD A4-5000              4/4
    1        453.70
    2        230.98
    3        158.88
    4        121.03  120.82
    5        122.68
    6        125.14

Odroid M1
    1        454.26
    2        232.22
    3        162.07
    4        123.50  123.67  123.54
    5        127.38
    6        125.96

Radxa Rock 3 Model A
    1        516.17
    2        274.39
    3        194.85
    4        158.79  158.20  157.45
    5        162.03
    6        164.81

Rasperry Pi3 Model B Rev 1.2

    1        833.54
    2        428.95
    3        296.55
    4        224.95  224.96  224.88
    5        231.73
    6        237.34

*/
