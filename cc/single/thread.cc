#include <iostream>        // printf, cout
#include <vector>          // emplace_back
#include <thread>          // thread ()
#include <mutex>           // mutex

using namespace std;
using namespace chrono;

mutex autoschlüssel;

void autofahren (signed long pname)
  {
  unique_lock<mutex> autosperre (autoschlüssel);
  cout << pname << " fährt Auto" << endl;
  this_thread::sleep_for (seconds (4));
  cout << pname << " hat das Autofahren beendet" << endl;
  autosperre.unlock ();
  }

int main (int argc, char** argv)
  {
  signed long threadanz;
  if (argc != 2)
    {
    printf ("Anzahl Threads angeben\n");
    return 0;
    }
  sscanf (argv[1], "%ld", &threadanz);

// Einzelthreads abarbeiten
/*
  thread t1 (autofahren, 1);
  thread t2 (autofahren, 2);
  thread t3 (autofahren, 3);
  t1.join ();
  t2.join ();
  t3.join ();
//*/

// n Threads abarbeiten mit Zeiger
/*
  thread* ath[1000];
  for (signed long lauf= 0; lauf < threadanz; lauf++)
    ath[lauf]= new thread (autofahren, lauf);

  for (signed long lauf= 0; lauf < threadanz; lauf++)
    ath[lauf]->join ();
//*/

// n Threads abarbeiten mit Vektorklasse
//*
  vector<thread> threads;
  for (signed long lauf= 0; lauf < threadanz; lauf++)
    threads.emplace_back (autofahren, lauf);

  for (auto& t: threads)
    t.join ();
//*/

  return 0;
  }
