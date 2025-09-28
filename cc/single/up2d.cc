#include <iostream>

using namespace std;

void berechneup ()
  {
  float a0, ax, ay, a1, xu, xo, yu, yo;
  cout << "a0 ";
  cin >> a0;
  cout << "ax ";
  cin >> ax;
  cout << "ay ";
  cin >> ay;
  cout << "a1 ";
  cin >> a1;
  cout << "xu ";
  cin >> xu;
  cout << "xo ";
  cin >> xo;
  cout << "yu ";
  cin >> yu;
  cout << "yo ";
  cin >> yo;
  cout << "a0: " << a0 << " ";
  cout << "ax: " << ax << " ";
  cout << "ay: " << ay << " ";
  cout << "a1: " << a1 << " ";
  cout << "xu: " << xu << " ";
  cout << "xo: " << xo << " ";
  cout << "yu: " << yu << " ";
  cout << "yo: " << yo << " ";
  cout << endl << endl;
  float f0= a0*(xo-xu)*(yo-yu);
  float f1= 0.5*((ax-a0)*(yo-yu)*(xo*xo-xu*xu)+(ay-a0)*(xo-xu)*(yo*yo-yu*yu));
  float f2= 0.25*(a0+a1-ax-ay)*(xo*xo-xu*xu)*(yo*yo-yu*yu);
  float f= f0 + f1 + f2;
  cout << "f: " << f << endl << endl;
  }

int main ()
  {
  berechneup ();
  return 0;
  }
