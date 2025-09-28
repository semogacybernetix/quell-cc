#include <sys/times.h>
#include <unistd.h>
#include <cstdio>

void takte ()
  {
  tms zeit;
  float ticksps= float (sysconf (_SC_CLK_TCK));
  printf ("ticks/sek: %f\n", ticksps);
  clock_t ticks= times (&zeit);
  while (1)
    {
    usleep (1000000);
    printf ("Zeit: %f\n", (times (&zeit) - ticks)/ticksps);
    ticks= times (&zeit);
    }
  }

void ticke ()
  {
  tms zeit;
  float ticksps= float (sysconf (_SC_CLK_TCK));
  printf ("ticks/sek: %f\n", ticksps);
  signed long ticks= times (&zeit);
  while (1)
    {
    unsigned long long loops= 0;
    while (times (&zeit) == ticks)
      loops++;
    ticks= times (&zeit);
    printf ("Zeit: %10lu  loops: %20llu\n", ticks, loops);
    }
  }

void zeittest ()
  {
  tms zeit;
  float ticksps= float (sysconf (_SC_CLK_TCK));
  printf ("ticks/sek: %f\n", ticksps);
  signed long sumlost= 0;
  signed long ticksperframe= 12;
  while (1)
    {
    signed long ultimatum= times (&zeit)/ticksperframe + 1;
    unsigned long long loops= 0;
    while (times (&zeit)/ticksperframe < ultimatum)
      {
      usleep (1000);
      loops++;
      }
    signed long framelost= times (&zeit)/ticksperframe - ultimatum;
    sumlost+= framelost;
    printf ("Zeit: %10lu  loops: %20llu  Framelost: %10lu  Sumlost %10lu\n", times (&zeit), loops, framelost, sumlost);
    }
  }

int main ()
  {
  zeittest ();
  return 0;
  }
