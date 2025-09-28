// objektorientierte Threadprogrammierung

#include <thread>
#include <iostream>        // printf, cout
#include <unistd.h>        // sleep

using namespace std;    // sonst werden die Memberfunktionen nicht erkannt

//--------------------------------------------------- Rekursion --------------------------------------------------------

signed long rektiefe; // Rekursionstiefe

void* arbeit (void*)
  {
  return 0;
  }

void* threadrekursiv (void*)
  {
  if (rektiefe < 1)
    return 0;
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

//--------------------------------------------------- Rekursion --------------------------------------------------------

struct cmultiarbeit : public thread
  {
  signed long maxparallel ();
  };

signed long cmultiarbeit::maxparallel ()
  {
  return hardware_concurrency ();
  }
    
//----------------------------------------------------------------------------------------
int main ()
  {
  cmultiarbeit multiarbeit;
  printf ("Hardwareprozesse: %ld\n", multiarbeit.maxparallel ());
  return 0;
  }
