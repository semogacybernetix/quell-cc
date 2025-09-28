/*
Dieses Programm undossisiert bzw. entdossisiert eine Textdatei d.h.
  Das Dateiformat wird von Dos-Text in Unix-Text umgewandelt d.h.
    Die Carriage-Returns (0x13) werden entfernt, die Line-Feeds (0x10) werden gelassen
  Der Zeichensatz wird von Dos in Ansi konvertiert d.h.
    Die Dos-Umlaute werden in Ansi-Umlaute konvertiert
  Außerdem werden Verschönerungen durchgeführt d.h.
    Tabs werden durch Leerzeichen ersetzt
    überflüssige Leerzeichen am Zeilenende werden entfernt
    überflüssige Leerzeilen am Dateiende werden entfernt
    eine nichtabgeschlossene letzte Zeile wird abgeschlossen (ein Line Feed (0x10) wird am Zeilen- bzw. Dateiende hinzugefügt)
*/

#include <iostream>
#include <cstring>
#include <cstdio>
#include <sys/stat.h>

using namespace std;

signed long replaceumlaut (unsigned char* ppuffer, signed long panz)
  {
  signed long umlanz= 0;
  signed long wlauf= 0;
  for (signed long dlauf= 0; dlauf < panz; dlauf++)
    {
    if ((ppuffer[dlauf] == 'a') && (ppuffer[dlauf + 1] == 'e'))
      {
      ppuffer[wlauf]= 0xe4;
      wlauf++;
      dlauf+= 2;
      umlanz++;
      }
    if ((ppuffer[dlauf] == 'o') && (ppuffer[dlauf + 1] == 'e'))
      {
      ppuffer[wlauf]= 0xf6;
      wlauf++;
      dlauf+= 2;
      umlanz++;
      }
    if (((ppuffer[dlauf] == 'u') && (ppuffer[dlauf + 1] == 'e')) &&
        ((dlauf == 0) ||
  ((ppuffer[dlauf - 1] != 'a') && (ppuffer[dlauf - 1] != 'e') &&
   (ppuffer[dlauf - 1] != 'A') && (ppuffer[dlauf - 1] != 'E'))))
      {
      ppuffer[wlauf]= 0xfc;
      wlauf++;
      dlauf+= 2;
      umlanz++;
      }
    if ((ppuffer[dlauf] == 'A') && (ppuffer[dlauf + 1] == 'E'))
      {
      ppuffer[wlauf]= 0xc4;
      wlauf++;
      dlauf+= 2;
      umlanz++;
      }
    if ((ppuffer[dlauf] == 'O') && (ppuffer[dlauf + 1] == 'E'))
      {
      ppuffer[wlauf]= 0xd6;
      wlauf++;
      dlauf+= 2;
      umlanz++;
      }
    if (((ppuffer[dlauf] == 'U') && (ppuffer[dlauf + 1] == 'E')) &&
        ((dlauf == 0) ||
  ((ppuffer[dlauf - 1] != 'A') && (ppuffer[dlauf - 1] != 'E'))))
      {
      ppuffer[wlauf]= 0xdc;
      wlauf++;
      dlauf+= 2;
      umlanz++;
      }
    if ((ppuffer[dlauf] == 'A') && (ppuffer[dlauf + 1] == 'e'))
      {
      ppuffer[wlauf]= 0xc4;
      wlauf++;
      dlauf+= 2;
      umlanz++;
      }
    if ((ppuffer[dlauf] == 'O') && (ppuffer[dlauf + 1] == 'e'))
      {
      ppuffer[wlauf]= 0xd6;
      wlauf++;
      dlauf+= 2;
      umlanz++;
      }
    if ((ppuffer[dlauf] == 'U') && (ppuffer[dlauf + 1] == 'e'))
      {
      ppuffer[wlauf]= 0xdc;
      wlauf++;
      dlauf+= 2;
      umlanz++;
      }
    ppuffer[wlauf]= ppuffer[dlauf];
    wlauf++;
    }
  cout.width (6);
  cout << umlanz << " Umlaute ersetzt." << endl;
  return wlauf;
  }

signed long replacetab (unsigned char* ppuffer, signed long panz)
  {
  signed long tabanz= 0;
  for (signed long dlauf= 0; dlauf < panz; dlauf++)
    if (ppuffer[dlauf] == 9)
      {
      ppuffer[dlauf]= 0x20;
      tabanz++;
      }
  cout.width (6);
  cout << tabanz << " Tabs durch Leerzeichen ersetzt." << endl;
  return panz;
  }

signed long removecr (unsigned char* ppuffer, signed long panz)
  {
  signed long cranz= 0;
  signed long wlauf= 0;
  for (signed long dlauf= 0; dlauf < panz; dlauf++)
    if (ppuffer[dlauf] != 0xd)
      {
      ppuffer[wlauf]= ppuffer[dlauf];
      wlauf++;
      }
    else
      cranz++;
  cout.width (6);
  cout << cranz << " Dosreturns entfernt." << endl;
  return wlauf;
  }

signed long removespace (unsigned char* ppuffer, signed long panz)
  {
  signed long spanz= 0;
  signed long wlauf= 0;
  signed long tlauf= 0;
  for (signed long dlauf= 0; dlauf < panz; dlauf++)
    {
    switch (ppuffer[dlauf])
      {
      case 0x0A:
        ppuffer[tlauf]= ppuffer[dlauf];
        spanz+= wlauf - tlauf;
        tlauf++;
        wlauf= tlauf;
        break;
      case 0x20:
        ppuffer[wlauf]= ppuffer[dlauf];
        wlauf++;
        break;
      default:
        ppuffer[wlauf]= ppuffer[dlauf];
        wlauf++;
        tlauf= wlauf;
        break;
      }
    }
  cout.width (6);
  cout << spanz << " Leerzeichen am Zeilenende entfernt." << endl;
  return wlauf;
  }

signed long removeline (unsigned char* ppuffer, signed long panz)
  {
  signed long lianz= 0;
  signed long wlauf= 0;
  for (signed long dlauf= 0; dlauf < panz; dlauf++)
    if (ppuffer[dlauf] != 0x0A)
      wlauf= dlauf;
  wlauf++;
  if (wlauf == panz)
    ppuffer[panz]= 0x0A;
  wlauf++;
  lianz= panz - wlauf;
  cout.width (6);
  cout << lianz << " Leerzeilen am Dateiende entfernt." << endl;
  return wlauf;
  }

signed long convertumlaute (unsigned char* ppuffer, signed long panz)
  {
  signed long umlanz= 0;
  for (signed long ulauf= 0; ulauf < panz; ulauf++)
    switch (ppuffer[ulauf])
      {
      case 0x84: // dieser Umlaut verändert das UTF-8-Ä (C3 84) wenn keine Vorsichtsmaßnahmen ergriffen werden
        if (ulauf <= 0)
          {
          ppuffer[ulauf]= 0xE4; // Ansi-'ä'
          umlanz++;
          }
          else
          {
          if (ppuffer[ulauf - 1] != 0xC3)
            {
            ppuffer[ulauf]= 0xE4; // Ansi-'ä'
            umlanz++;
            }
          }
        break;
      case 0x94:
        ppuffer[ulauf]= 0xF6; // Ansi-'ö'
        umlanz++;
        break;
      case 0x81:
        ppuffer[ulauf]= 0xFC; // Ansi-'ü'
        umlanz++;
        break;
      case 0xE1:
        ppuffer[ulauf]= 0xDF; // Ansi-'ß'
        umlanz++;
        break;
      case 0x8E:
        ppuffer[ulauf]= 0xC4; // Ansi-'Ä';
        umlanz++;
        break;
      case 0x99:
        ppuffer[ulauf]= 0xD6; // Ansi-'Ö'
        umlanz++;
        break;
      case 0x9A:
        ppuffer[ulauf]= 0xDC; // Ansi-'Ü'
        umlanz++;
        break;
      }
  cout.width (6);
  cout << umlanz << " Umlaute konvertiert." << endl;
  return panz;
  }

int main (int argc, char** argv)
  {
  FILE* din= fopen (argv[1], "rb");
  if (!din)
    {
    cout << "Die als Parameter angegebene Datei mit einem Namen von 0 Byte Länge existiert in diesem Verzeichnis leider nicht" << endl << endl;
    return (0);
    }
  struct stat filestat;
  stat (argv[1], &filestat);
  signed long dlaenge= filestat.st_size;
  unsigned char* puffer= new unsigned char[dlaenge + 1];
  signed long ret= fread (puffer, 1, dlaenge, din);
  if (ret != 0)
    fclose (din);
  if (argc == 2)
    {
    dlaenge= removecr (puffer, dlaenge);
    dlaenge= replacetab (puffer, dlaenge);
    dlaenge= convertumlaute (puffer, dlaenge);
    dlaenge= removespace (puffer, dlaenge);
    dlaenge= removeline (puffer, dlaenge);
    }
  FILE* dout= fopen (argv[1], "wb");
  fwrite (puffer, 1, dlaenge, dout);
  fclose (dout);
  cout << endl;
  delete (puffer);
  return 0;
  }
