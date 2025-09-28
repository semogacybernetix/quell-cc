#include <iostream>
#include <cstring>
#include <cstdio>
#include <sys/stat.h>

using namespace std;

signed long replaceumlaut (char* ppuffer, signed long panz)
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

signed long replacetab (char* ppuffer, signed long panz)
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

signed long removecr (char* ppuffer, signed long panz)
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

signed long removespace (char* ppuffer, signed long panz)
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

signed long removeline (char* ppuffer, signed long panz)
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

void removeumlaute (char* pname1, char* pname2)
  {
  FILE* din= fopen (pname1, "rb");
  FILE* dout= fopen (pname2, "wb");
  unsigned char dwert;
  while (fread (&dwert, 1, 1, din))
    {
    switch (dwert)
      {
      case 13:
        break;
      case 0x84:
        fputc ('ä', dout);
        break;
      case 0x94:
        fputc ('ö', dout);
        break;
      case 0x81:
        fputc ('ü', dout);
        break;
      case 0xE1:
        fputc ('ß', dout);
        break;
      case 0x8E:
        fputc ('Ä', dout);
        break;
      case 0x99:
        fputc ('Ö', dout);
        break;
      case 0x9A:
        fputc ('Ü', dout);
        break;
      default:
        fputc (dwert, dout);
        break;
      }
    }
  fclose (dout);
  fclose (din);
  }

int main (int argc, char** argv)
  {
  FILE* din= fopen (argv[1], "rb");
  if (!din)
    {
    cout << "Datei existiert nicht." << endl << endl;
    return (0);
    }
  struct stat filestat;
  stat (argv[1], &filestat);
  signed long dlaenge= filestat.st_size;
  char* puffer= new char[dlaenge + 1];
  fread (puffer, 1, dlaenge, din);
  fclose (din);
  if (argc == 2)
    {
    dlaenge= removecr (puffer, dlaenge);
    dlaenge= replacetab (puffer, dlaenge);
    dlaenge= removespace (puffer, dlaenge);
    dlaenge= removeline (puffer, dlaenge);
//    dlaenge= replaceumlaut (puffer, dlaenge);
    }
  else
    {
    for (signed long arglauf= 2; arglauf < argc; arglauf++)
      {
      }
    }
  FILE* dout= fopen (argv[1], "wb");
  fwrite (puffer, 1, dlaenge, dout);
  fclose (dout);
  cout << endl;
  delete (puffer);
  return 0;
  }
