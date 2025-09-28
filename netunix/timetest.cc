#include <stdio.h>
#include <sys/times.h>

void echotime ()
  {
  tms zeit;
  signed long frame= times (&zeit);
  unsigned long dif;
  while (1)
    {
    while (frame > times (&zeit));
    dif= times (&zeit) - frame;
    if (dif > 0)
      printf ("%10ld\n", dif);
    frame+= 1;
    }
  }

int main ()
  {
  echotime ();
  return 0;
  }
