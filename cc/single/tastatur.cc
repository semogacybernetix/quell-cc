#include <curses.h>
#include <unistd.h>

void tastatur ()
  {
  int ein;

  initscr ();
  for (unsigned long lauf= 0; lauf < 5;)
    {
    ein= getch ();
    //usleep (100000);
    printf ("%d\n", ein);
    }
  endwin ();
  }

int main ()
  {
  tastatur ();
  return 0;
  }
