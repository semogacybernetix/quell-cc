/*
Funktionsprinzip:
1. Es gibt eine Funktion die Arbeit parallelisierbar ausführen kann. Als Parameter bekommt sie eine Instanznummer übergeben, um die Arbeit aufteilen zu können.
2. Die Arbeitsfunktion wird von einer rekursiven Funktion aufgerufen, die dann beendet ist, wenn alle Threads sich beendet haben.
*/

#include <thread>
#include <iostream>        // printf, cout
#include <unistd.h>        // sleep

signed long threadanz;
signed long rektiefe;

// als Funktionsparameter wird die Nummer des Threads übergeben, mit der der Arbeitsprozess gestartet wird
// Returnwert von arbeit sinnlos, weil die Rekursionsfunktion ihn bekommt
void arbeit (signed long pthreadnr)
  {
  printf ("    arbeit-%ld:  beginne und warte\n", pthreadnr);
  sleep ((unsigned short) (2 + (threadanz - pthreadnr + 1)*1));
//  sleep ((unsigned short) (2 + (pthreadnr)*1));
  printf ("    arbeit-%ld:  beendet\n", pthreadnr);
  }

void* threadrekursiv (void*)
  {
  signed long lokaltiefe= rektiefe;   // rektiefe kopieren, da sie jederzeit von einer anderen Instanz von threadrekursiv geändert werden kann
  
  // Für den Fall, dass threadrekursiv von außen mit weniger als einem Thread aufgerufen wird
  if (lokaltiefe < 1)
    {
    printf("threadrekursiv-%ld:----Sofortreturn\n", lokaltiefe);
    return 0;
    }

  pthread_t threadid;             // id des erzeugten Threads
  signed long threadreturnwert;   // Rückgabe ob Threaderzeugung funktioniert hat
  
  // neuen Aufruf von threadrekursiv erzeugen falls Tiefe mindestens 2 ist
  if (lokaltiefe > 1)
    {
    printf("threadrekursiv-%ld:----Aufruf threadrekursiv mit Tiefe  %3ld\n", lokaltiefe, lokaltiefe - 1);
    rektiefe--;
    threadreturnwert= pthread_create (&threadid, NULL, threadrekursiv, NULL);
    if (threadreturnwert != 0)
      printf ("threadrekursiv-%ld:----Aufruf threadrekursiv mit Tiefe  %3ld fehlgeschlagen\n", lokaltiefe, lokaltiefe - 1);
    }
  
  // Arbeitsfunktion aufrufen
  printf("threadrekursiv-%ld:----Aufruf arbeit mit Tiefe %3ld\n", lokaltiefe, lokaltiefe);
  arbeit (lokaltiefe);
  
  // auf Beendigung von neuem Aufruf warten
  if (lokaltiefe > 1)
    {
    printf("threadrekursiv-%ld:----warte auf Beendigung threadrekursiv-%ld\n", lokaltiefe, lokaltiefe - 1);
    pthread_join (threadid, NULL);
    printf("threadrekursiv-%ld:----Aufruf threadrekursiv-%ld beendet\n", lokaltiefe, lokaltiefe - 1);
    }
  printf("threadrekursiv-%ld:----return\n", lokaltiefe);
  return 0;
  }

//----------------------------------------------------------------------------------------
int main (int argc, char** argv)
  {
  if (argc != 2)
    {
    printf ("Anzahl Threads angeben\n");
    return 0;
    }
  sscanf (argv[1], "%ld", &threadanz);
  rektiefe= threadanz;
  threadrekursiv (0);
  return 0;
  }
