#include <iostream>         // cout, time_t
#include <sys/times.h>      // tms
#include <unistd.h>         // sysconf, _SC_CLK_TCK, usleep

using namespace std;

void menschenzeit ()
  {
  //  time_t                 // Datentyp für die Epochzeit (Sekunden seit 1970.01.01 00:00 GMT) (im Grunde long long)
  //  time (time_t*);        // Epochzeit zurückgeben und im als Parameter angegebenen Zeiger speichern, falls dieser nicht NULL ist
  //  tm*                    // struct für die einzelnen Zeitkomponenten (Tag, Monat, Jahr)

  cout << endl;
  time_t epochzeit= time (NULL);             // Epochzeit holen
  cout << "Größe von Epochzeit (time_t)[Bits]:  " << 8*sizeof (epochzeit) << endl;
  cout << "Epochzeit:   " << epochzeit << endl;

  tm* zeitstruct= gmtime (&epochzeit);       // Epochzeit in Komponenten zerlegen und in struct speichern
  char* zeitstring= asctime (zeitstruct);    // Zeit im Zeitstruct in einen Zeitstring umgewandeln
  cout << zeitstring;

  zeitstruct= localtime (&epochzeit);  // Epochzeit in Lokalzeit umwandeln, dann in Komponenten zerlegen und in Komponentenstruct speichern
  zeitstring= asctime (zeitstruct);    // Zeit im Zeitstruct in einen Zeitstring umgewandeln
  cout << zeitstring;

  cout << endl;
  }

void menschentestzeit ()
  {

  time_t epochzeit;
  tm* zeitstruct;
  char* zeitstring;

  epochzeit= -1500000000;
  zeitstruct= localtime (&epochzeit);
  zeitstring= asctime (zeitstruct);
  cout << "1.5 Milliarden Sekunden vor Epochenbeginn:   " << zeitstring;

  epochzeit= 0;
  zeitstruct= localtime (&epochzeit);
  zeitstring= asctime (zeitstruct);
  cout << "Epochenbeginn:[MEZ]                          " << zeitstring;

  epochzeit= 1500000000;
  zeitstruct= localtime (&epochzeit);
  zeitstring= asctime (zeitstruct);
  cout << "1.5 Millarden Sekunden nach Epochenbeginn:   " << zeitstring;

  epochzeit= 1525000000;
  zeitstruct= localtime (&epochzeit);
  zeitstring= asctime (zeitstruct);
  cout << "1.525 Millarden Sekunden nach Epochenbeginn: " << zeitstring;

  cout << endl;
  }


void computerzeit ()
  {
  signed long ticksps= sysconf (_SC_CLK_TCK);
  cout << "Ticks pro Sekunde: " << ticksps << endl;

  tms zeitstruct;
  clock_t ticks= times (&zeitstruct);       // Ticks zurückgeben und (user time, systemtime, ...) in zeitstruct speichern

  cout << "Größe von Ticks (clock_t)[Bits]:  " << 8*sizeof (ticks) << endl;
  cout << "Ticks: " << ticks << "  Sekunden: " << ticks/ticksps << "  Minuten: " << ticks/ticksps/60 << "  Stunden: " << ticks/ticksps/3600 << "  Tage: " << ticks/ticksps/86400 << endl;
  cout << endl;

  clock_t lticks;
  lticks= times (NULL);
  lticks= lticks/100*100 + 100;
  while (true)
    {
    while (lticks > times (NULL));
    cout << lticks << endl;
    lticks+= 100;
    }

  }

void testewarten ()
  {
  signed long wartung= 0;
  while (true)
    {
    cout << wartung << endl;
    wartung++;
    usleep (1000000);
    }
  }


int main()
  {
  menschenzeit ();
  menschentestzeit ();
  computerzeit ();
  testewarten ();
  return 0;
  }
