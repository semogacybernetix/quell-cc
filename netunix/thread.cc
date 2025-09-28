#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/times.h>
#include <signal.h>

using namespace std;

/*
void signalterm ()
  {
  tms zeit;
  cout << "term " << times (&zeit) << endl; 
  exit (0);
  }

void signalint ()
  {
  tms zeit;
  cout << "int " << times (&zeit) << endl; 
  exit (0);
  }
*/

void waituntil (clock_t pzeit)
  {
  tms zeit;
  while (times (&zeit) < pzeit)
    usleep (5000);
  }

void* phallo (void*)
  {
  tms zeit;
  signed long startzeit= times (&zeit);
  startzeit= startzeit - startzeit%100 + 100;
  while (1)
    {
    waituntil (startzeit);
    cout << "langsam    " << startzeit << endl;
    startzeit+= 100;
    }
  return 0;
  }

void* phier (void*)
  {
  tms zeit;
  signed long startzeit= times (&zeit);
  startzeit= startzeit - startzeit%100 + 100 + 10;
  while (1)
    {
    waituntil (startzeit);
    cout << "  schnell  " << startzeit << endl;
    startzeit+= 30;
    }
  return 0;
  }

int main ()
  {
//  signal (SIGTERM, sterm);
//  signal (SIGINT,sint);
  pthread_t thid;
  int thr;
  thr= pthread_create (&thid, NULL, phallo, NULL);
  if (thr)
    {
    cout << "Thread phallo konnte nicht erzeugt werden" << endl;
    exit (0);
    }
/*
  thr= pthread_create (&thid, NULL, phier, NULL);
  if (thr)
    {
    cout << "Thread phier konnte nicht erzeugt werden" << endl;
    exit (0);
    }
  pause ();
*/
  phier (0);
  return 0;
  }
