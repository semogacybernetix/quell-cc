#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>

using namespace std;

int main ()
  {
  Display* display0= XOpenDisplay (0);
  signed long depth= XDefaultDepth (display0, 0);
  cout << "Farbtiefe: " << depth << endl;
//  XVisualInfo* visinfo= XGetVisualInfo (display0, );
  Screen* defaultscreen= DefaultScreenOfDisplay (display0);
  int backingstore= DoesBackingStore (defaultscreen);
  cout << "Backingstore: ";
  switch (backingstore)
    {
    case WhenMapped:
      cout << "when mapped" << endl;
      break;
    case NotUseful:
      cout << "not useful" << endl;
      break;
    case Always:
      cout << "always" << endl;
      break;
    }
  return 0;
  }
