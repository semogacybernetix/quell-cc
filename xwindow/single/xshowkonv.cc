#include "../screen/xscr.h"

#include <cstdio>
#include <cmath>

signed long flttoint (float px)
  {
  if (px >= 0)
    return int (px + 0.5);
  return int (px - 0.5);
  }


float psieps (float peps, float px)
  {
  if (fabs (px) > peps)
    return 0;
  return 1 - fabs (px/peps);
  }

void showkonv (float pepsilon)
  {
  cxscreen xscreen ("Zacken-Konvergenz", 1024, 768);
  signed long zoom= 100;
  for (signed long lxpic= 0; lxpic < 1024; lxpic++)
    {
    float realx= (lxpic - 511)/float (zoom);
    float epsilon= pepsilon;
    signed long bereich= flttoint (6/epsilon);
    float sumrealy= 0;
    for (signed long laufn= -bereich; laufn <= bereich; laufn++)
      {
      float realy= sin (laufn*epsilon)*psieps (epsilon, realx - laufn*epsilon);
      sumrealy+= realy;
      signed long ypic= 384 + flttoint (zoom*realy);
      xscreen.putpixel (lxpic, ypic, 255, 0, 0);
      }
    xscreen.putpixel (lxpic, 384 + flttoint (zoom*sumrealy), 0, 255, 0);
    sumrealy-= sin (realx);
    xscreen.putpixel (lxpic, 384 + flttoint (zoom*4/epsilon*sumrealy), 255, 255, 255);
    }
  xscreen.flush ();
  getchar ();
  }

signed int main (int argc, char** argv)
  {
  float epsilon= 0.5;
  if (argc == 2)
    sscanf(argv[1], "%f", &epsilon);
  printf ("epsilon=%f\n", epsilon);
  showkonv (epsilon);
  return 0;
  }
