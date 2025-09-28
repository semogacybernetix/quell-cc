#include "../../cc/screen/allscr.h"
#include "../screen/xscr.h"

#include <stdio.h>
#include <iostream>

using namespace std;

float volzelle (float a0, float ax, float ay, float a1, float xu, float xo,
float yu, float yo)
  {
  float f0= a0*(xo-xu)*(yo-yu);
  float f1= 0.5*((ax-a0)*(yo-yu)*(xo*xo-xu*xu)+(ay-a0)*(xo-xu)*(yo*yo-yu*yu));
  float f2= 0.25*(a0+a1-ax-ay)*(xo*xo-xu*xu)*(yo*yo-yu*yu);
  return f0 + f1 + f2;
  }

void calc ()
  {
  float y0, y1, d0, d1;
  float fa, fb, fc, ga, gb, gc;
  cout << "y0 ";
  cin >> y0;
  cout << "y1 ";
  cin >> y1;
  cout << "d0 ";
  cin >> d0;
  cout << "d1 ";
  cin >> d1;
  fa= 2*(y1 - y0) - 0.5*(3*d0 + d1);
  fb= d0;
  fc= y0;
  ga= 2*(y0 - y1) + 0.5*(3*d1 + d0);
  gb= d1;
  gc= y1;
  cout << endl;
  cout << "fa: " << fa << "   fb: " << fb << "   fc: " << fc << endl;
  cout << "ga: " << ga << "   gb: " << gb << "   gc: " << gc << endl;
  cout << endl;
  float f12, g12, d012, d112;
  f12= fa*.25 + fb*.5 + fc; 
  g12= ga*.25 - gb*.5 + gc; 
  d012= fa + fb;
  d112= -ga + gb;
  cout << "f(1/2): " << f12 << "   g(-1/2): " << g12 << endl;
  cout << "f'(1/2): " << d012 << "   g'(-1/2): " << d112 << endl;
  }

void quadspline (signed long panz, float* pstuetz, float* pspline)
  {
  for (signed long plauf= 0; plauf < panz; ++plauf)
    {
    signed long pminus, pplus, pminus2, pplus2;
    float steig, steigminus, steigplus;
    pminus2= plauf - 2;
    if (pminus2 < 0) pminus2= 0;
    pminus= plauf - 1;
    if (pminus < 0) pminus= 0;
    pplus= plauf + 1;
    if (pplus >= panz) pplus= plauf;
    pplus2= plauf + 2;
    if (pplus2 >= panz) pplus2= plauf;
    steigminus= 0.5*(pstuetz[plauf] - pstuetz[pminus2]);
    steig= 0.5*(pstuetz[pplus] - pstuetz[pminus]);
    steigplus= 0.5*(pstuetz[pplus2] - pstuetz[plauf]);
    pspline[4*plauf + 0]= 2*(pstuetz[pminus] - pstuetz[plauf]) + 0.5*(3*steig + steigminus);
    pspline[4*plauf + 1]= 2*(pstuetz[pplus] - pstuetz[plauf]) - 0.5*(3*steig + steigplus);
    pspline[4*plauf + 2]= steig;
    pspline[4*plauf + 3]= pstuetz[plauf];
    }
  }

void volspline (signed long panz, float* pstuetz, float* pspline)
  {
  for (signed long plauf= 0; plauf < panz; ++plauf)
    {
    signed long pminus, pplus;
    pminus= plauf - 1;
    if (pminus < 0) pminus= 0;
    pplus= plauf + 1;
    if (pplus >= panz) pplus= plauf;
    float yminus, yplus, ww;
    yminus= 0.5*(pstuetz[pminus] + pstuetz[plauf]);
    yplus= 0.5*(pstuetz[pplus] + pstuetz[plauf]);
    ww= pstuetz[plauf];
    pspline[4*plauf + 0]= 3*yminus + 3*yplus - 6*ww;
    pspline[4*plauf + 1]= yplus - yminus;
    pspline[4*plauf + 2]= 0.25*(6*ww - yminus - yplus);
    pspline[4*plauf + 3]= pstuetz[plauf];
    }
  }

void zeichnespline (signed long panz, float* pstuetz, clscreen& pscreen)
  {
  float smin, smax;
  float* qspline;
  qspline= new float[4*panz];
  quadspline (panz, pstuetz, qspline);  
  smin= pstuetz[0];
  smax= pstuetz[0];
  
  for (signed long plauf= 1; plauf < panz; ++plauf)
    {
    if (pstuetz[plauf] < smin)
      smin= pstuetz[plauf];
    if (pstuetz[plauf] > smax)
      smax= pstuetz[plauf];
    }
  signed long scalex, scaley;
  scalex= 40;
  scaley= scalex;
  for (signed long plauf= 0; plauf < panz; ++plauf)
    {
    signed long sxhalb=scalex/2 + 1;
    signed long ymax= int (pstuetz[plauf]*scaley + 0.5);
    for (signed long ylauf= 0; ylauf < ymax; ++ylauf)
      pscreen.putpixel (sxhalb + scalex* plauf, ylauf, 0, pscreen.gmax, 0);
    for (signed long qlauf= 0; qlauf < sxhalb; ++qlauf)
      {
      float qx= qlauf/float(scalex);
      float qyminus= qspline[4*plauf+0]*qx*qx - qspline[4*plauf+2]*qx + qspline[4*plauf+3];
      float qyplus=  qspline[4*plauf+1]*qx*qx + qspline[4*plauf+2]*qx + qspline[4*plauf+3];
      signed long syminus= int (scaley*qyminus + 0.5);
      signed long syplus= int (scaley*qyplus + 0.5);
      signed long sxminus= sxhalb + plauf*scalex - qlauf;
      signed long sxplus= sxhalb + plauf*scalex + qlauf;
      pscreen.putpixel (sxminus, syminus, pscreen.rmax, pscreen.gmax, pscreen.bmax);
      pscreen.putpixel (sxplus, syplus, pscreen.rmax, pscreen.gmax, pscreen.bmax);
      }
    }
  pscreen.flush ();
  }

void zeichnevolspline (signed long panz, float* pstuetz, clscreen& pscreen)
  {
  float smin, smax;
  float* qspline;
  qspline= new float[4*panz];
  volspline (panz, pstuetz, qspline);  
  smin= pstuetz[0];
  smax= pstuetz[0];
  
  for (signed long plauf= 1; plauf < panz; ++plauf)
    {
    if (pstuetz[plauf] < smin)
      smin= pstuetz[plauf];
    if (pstuetz[plauf] > smax)
      smax= pstuetz[plauf];
    }
  signed long scalex, scaley;
  scalex= 40;
  scaley= scalex;
  for (signed long plauf= 0; plauf < panz; ++plauf)
    {
    signed long sxhalb=scalex/2 + 1;
    signed long ymax= int (pstuetz[plauf]*scaley + 0.5);
    for (signed long ylauf= 0; ylauf < ymax; ++ylauf)
      pscreen.putpixel (sxhalb + scalex* plauf, ylauf, 0, pscreen.gmax, 0);
    for (signed long qlauf= 0; qlauf < sxhalb; ++qlauf)
      {
      float qx= qlauf/float(scalex);
      float qyminus= qspline[4*plauf+0]*qx*qx - qspline[4*plauf+1]*qx + qspline[4*plauf+2];
      float qyplus=  qspline[4*plauf+0]*qx*qx + qspline[4*plauf+1]*qx + qspline[4*plauf+2];
      signed long syminus= int (scaley*qyminus + 0.5);
      signed long syplus= int (scaley*qyplus + 0.5);
      signed long sxminus= sxhalb + plauf*scalex - qlauf;
      signed long sxplus= sxhalb + plauf*scalex + qlauf;
      pscreen.putpixel (sxminus, syminus, pscreen.rmax, pscreen.gmax, pscreen.bmax);
      pscreen.putpixel (sxplus, syplus, pscreen.rmax, pscreen.gmax, pscreen.bmax);
      }
    }
  pscreen.flush ();
  }

int main (int argc, char** argv)
  {
  if (argc > 1)
    {
    printf ("zuviele Parameter\n");
    return 0;
    }
  argv+= 0;  // Variable benutzen, sonst Compilermecckern dass unbenutzt
  //  calc ();
  cxscreen bildschirm ("Q-Spline", 640, 480);
  float pstuetz[10];
  pstuetz[0]= 3;
  pstuetz[1]= 5;
  pstuetz[2]= 2;
  pstuetz[3]= 2;
  pstuetz[4]= 1;
  pstuetz[5]= 9;
  pstuetz[6]= 2;
  pstuetz[7]= 4;
  pstuetz[8]= 4;
  pstuetz[9]= 4;

  zeichnespline (10, pstuetz, bildschirm);
  getchar ();
  return 0;
  }
