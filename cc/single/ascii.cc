// Dieses Programm gibt den Ascii-Zeichensatz ohne Steuerzeichen auf der Konsole aus
// keine Cursorsprünge oder Abnormitäten

#include <iostream>

using namespace std;

void printascii ()
  {
  cout.setf (ios::hex, ios::basefield);
  for (signed long nlauf= 0; nlauf < 0x100; nlauf++)
    {
    if (!(nlauf % 0x10))
      {
      cout.width (4);
      cout << endl << nlauf << "    ";
      }
    if (((nlauf >= 0x20) && (nlauf < 0x80)) || (nlauf >= 0xa0))
      cout << char (nlauf) << "  ";
    else
      cout << " " << "  ";
    }
  cout << endl << endl;
  }

int main ()
  {
  printascii ();
  }
