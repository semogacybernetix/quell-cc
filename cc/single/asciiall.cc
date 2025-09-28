// Dieses Programm gibt den Ascii-Zeichensatz mit Steuerzeichen auf der Konsole aus
// dadurch Cursorsprünge oder Abnormitäten

#include <iostream>

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
    cout << char (nlauf) << "  ";
    }
  cout << endl << endl;
  }

int main ()
  {
  printascii ();
  }
