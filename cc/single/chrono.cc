#include <iostream>         // printf
#include <chrono>           // highres clock

using namespace std;
using namespace std::chrono;

void chronotest ()
  {
  auto start= high_resolution_clock::now ();
  auto stop= high_resolution_clock::now ();

  std::chrono::duration dauer= duration_cast<nanoseconds> (stop - start);
  //std::chrono::duration<double, std::nano> dauer= stop - start;

  cout << endl << "Dauer: " << dauer.count () << endl << endl;
  if (dauer > nanoseconds (80))
    cout << "mehr als 80 ns" << endl;
    else
    cout << "weniger als 81 ns" << endl;
  }

int main ()
  {
  chronotest ();
  return 0;
  }
