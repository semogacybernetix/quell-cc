/*
Der Inhalt eines Verzeichnisses (Liste von Datei- und Verzeichnisnamen)
wird in eine Datei geschrieben. Die Codierung der Datei (Ascii, CP1251, ISO-8859-15, UTF8,...)
entspricht der Codierung der Dateiname im Filesystem
*/


#include <dirent.h>
#include <iostream>
#include <string.h>

using namespace std;

void printdir ()
  {
  DIR* verzeichnis= opendir (".");
  dirent* eintrag;
  while (1)
    {
    eintrag= readdir (verzeichnis);
    if (!eintrag)
      break;
    cout << eintrag->d_name << "\n";
    }
  closedir (verzeichnis);
  }

void dirtofile (char* pname)
  {
  FILE* dout= fopen (pname, "wb");
  char unixlinesep (10);
  DIR* verzeichnis= opendir (".");
  dirent* eintrag;
  while (1)
    {
    eintrag= readdir (verzeichnis);
    if (!eintrag)
      break;
    cout << eintrag->d_name << "\n";
	signed long dlaenge= 0;
	while (eintrag->d_name[dlaenge])
	  dlaenge++;
	fwrite (eintrag->d_name, 1, dlaenge, dout);
	fwrite (&unixlinesep, 1, 1, dout); 
    }
  closedir (verzeichnis);
  fclose (dout);
  }

void createfilenames ()
  {
  const char* cp1252text= "CP1252-Euro-e-.txt";
  const char* iso8859_15text= "ISO8859-15-Euro-e-.txt";
  const char* utf8text= "UTF8-Euro-eee-.txt";
  char* cp1252filename= new char [256];
  char* iso8859_15filename= new char [256];
  char* utf8filename= new char [256];
  strcpy (cp1252filename, cp1252text);
  strcpy (iso8859_15filename, iso8859_15text);
  strcpy (utf8filename, utf8text);
  cp1252filename[12]= 0x80;  // Das Eurozeichen in CP1252 codiert
  iso8859_15filename[16]= 0xA4;  // Das Eurozeichen in ISO8859-15 codiert
  utf8filename[10]= 0xE2;  // Das Eurozeichen in UTF8 codiert
  utf8filename[11]= 0x82;  // Das Eurozeichen in UTF8 codiert
  utf8filename[12]= 0xAC;  // Das Eurozeichen in UTF8 codiert
  FILE* file_cp1252= fopen (cp1252filename, "wb");
  fclose (file_cp1252);
  FILE* file_iso8859_15= fopen (iso8859_15filename, "wb");
  fclose (file_iso8859_15);
  FILE* file_utf8= fopen (utf8filename, "wb");
  fclose (file_utf8);
  }
  
int main (int argc, char** argv)
  {
//  printdir ();
  if (argv[1])
    {
    dirtofile (argv[1]);
	return 0;
	}
  createfilenames ();
  return 0;
  }
