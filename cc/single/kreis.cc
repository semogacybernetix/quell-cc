#include "../screen/allscr.h"

#include <cstdio>
#include <cstdlib>
#include <cmath>

double kreis (double x)
  {
  return (x*sqrt (1 - x*x) + asin (x))/2;
  }

double kreispixel (double pradius,double px, double py)
  {
  px= abs (px);
  py= abs (py);
  if ( px > py)
    {
    double swap= px;
    px= py;
    py= swap;
    }
  double xf= (px + 0.5);
  double yf= (py + 0.5);
  if (sqrt (xf*xf + yf*yf) <= pradius + 0.5)
    return 1;
  xf= (abs (px) - 0.5);
  yf= (abs (py) - 0.5);
  if (sqrt (xf*xf + yf*yf) >= pradius + 0.5)
    return 0;
  double qanz= pradius*2 + 1;
  if (true)
    {
    double limit= py*2 - 1;
    double xmax= sqrt (qanz*qanz - limit*limit);
    if ((px*2 + 1) < xmax)
      {
      double b= (px*2 + 1)/qanz;
      double a= (px*2 - 1)/qanz;
      double v= limit/qanz;
      double f= (kreis (b) - kreis (a) - v*(b - a))*qanz*qanz/4;
      double drueber= kreispixel (pradius, px, py + 1);
      return f - drueber;
      }
    if ((px*2 - 1) < xmax)
      {
      double b= xmax/qanz;
      double a= (px*2 - 1)/qanz;
      double v= limit/qanz;
      double f= (kreis (b) - kreis (a) - v*(b - a))*qanz*qanz/4;
      return f;
      }
    }
  return 0.5;
  }

void plottepixel (char* pname, double pradius)
  {
  double qanz= pradius*2 + 1;
  cbmpdatei xscreen (pname, qanz + 40, qanz + 40);
  for (double ylauf= -pradius - 20; ylauf <= pradius + 20; ylauf++)
    for (double xlauf= -pradius - 20; xlauf <= pradius + 20; xlauf++)
      {
      double farbe= int (255*kreispixel (pradius, xlauf, ylauf) + 0.5);
      xscreen.putpixel (xlauf + pradius + 20, ylauf + pradius + 20, farbe, farbe, farbe);
      }
  }

void plottedigpixel (char* pname, double pradius)
  {
  double qanz= pradius*2 + 1;
  cbmpdatei xscreen (pname, qanz + 40, qanz + 40);
  for (double ylauf= -pradius - 20; ylauf <= pradius + 20; ylauf++)
    for (double xlauf= -pradius - 20; xlauf <= pradius + 20; xlauf++)
      {
      double farbe= 255*int (kreispixel (pradius, xlauf, ylauf) + 0.5);
      xscreen.putpixel (xlauf + pradius+20, ylauf + pradius+20, farbe, farbe, farbe);
      }
  }

int main (int argc, char** argv)
  {
  if (argc != 3)
    {
    printf ("kreis <Radius[Pixel]> <BMP-Datei>\n");
    return 0;
    }
  double radius;
  sscanf (argv[1], "%lf", &radius);
  plottepixel (argv[2], radius);
  //plottedigpixel (argv[1], radius);
  return 0;
  }
