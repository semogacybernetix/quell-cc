#include "../../cc/screen/allscr.h"
#include "../screen/xscr.h"

#include <stdio.h>
#include <iostream>

using namespace std;

float shortfunc (float px, float pa, float pb, float pc)
  {
  return pa*px*px*px + pb*px*px + pc*px;
  }

void berechneshort (float* peingabe, float* pausgabe)
  {
  float y2= peingabe[0];
  float dy1= peingabe[1];
  float dy2= peingabe[2];
  
  cout << "  y2: " << y2 << "  dy1: " << dy1 << "  dy2: " << dy2 << endl;
  
  float a= dy2 + dy1 - 2*y2;
  float b= 3*y2 - 2*dy1 - dy2;
  float c= dy1;
  
  cout << "a: " << a << "  b: " << b << " c: " << c << endl;

  pausgabe[0]= a;
  pausgabe[1]= b;
  pausgabe[2]= c;
  }

float berechnemittleresteigung (signed long pyv, signed long py, signed long pyn, signed long pbreite)
  {
  float steig1= (py - pyv) / float (pbreite);
  float steig2= (pyn - py) / float (pbreite);
  return 0.5*(steig1 + steig2);
  }

void berechnesteigwerte (signed long* pwerte, float* psteig, signed long panz, signed long pbreite)
  {
  for (signed long plauf= 0; plauf < panz; plauf++)
    {
    signed long vor, nach;
    if (plauf == 0)
        vor= 0;
      else
        vor= 1;
    if (plauf == panz - 1)
        nach= 0;
      else
        nach= 1;
    signed long yv= pwerte [plauf - vor];
    signed long yy= pwerte [plauf];
    signed long yn= pwerte [plauf + nach];
    psteig[plauf]= berechnemittleresteigung (yv, yy, yn, pbreite);
    }
  }

void berechnesplinewerte (signed long* pwerte, signed long panz, signed long pbreite, float* psteig, float* pa, float* pb, float* pc)
  {
  for (signed long balkenlauf= 0; balkenlauf < panz; balkenlauf++)
    {
    float* eingabe= new float[3];
    float* ausgabe= new float[3];
    signed long nach;
    if (balkenlauf == panz - 1)
        nach= 0;
      else
        nach= 1;
    eingabe[0]= (pwerte[balkenlauf + nach] - pwerte[balkenlauf])/ float (pbreite);
    eingabe[1]= psteig[balkenlauf];
    eingabe[2]= psteig[balkenlauf + nach];
    berechneshort (eingabe, ausgabe);
    pa[balkenlauf]= ausgabe[0];
    pb[balkenlauf]= ausgabe[1];
    pc[balkenlauf]= ausgabe[2];
    }
  }
  
void zeichnekubspline (signed long* pwerte, signed long panz)
  {
  signed long balkenbreite= 40;
  cxscreen bildschirm ("kub-Spline", 640, 480);
  float* steigwerte= new float[panz];
  berechnesteigwerte (pwerte, steigwerte, panz, balkenbreite);
  float* kuba= new float[panz];
  float* kubb= new float[panz];
  float* kubc= new float[panz];
  berechnesplinewerte (pwerte, panz, balkenbreite, steigwerte, kuba, kubb, kubc);
  for (signed long wertelauf= 0; wertelauf < panz; wertelauf++)
    {
    signed long xbegin= wertelauf*balkenbreite;
    signed long xnbegin= xbegin + balkenbreite;
    for (signed long ylauf= 0; ylauf < pwerte[wertelauf]; ylauf++)
      bildschirm.putpixel (xbegin, ylauf, 0, bildschirm.gmax, 0);
    for (signed long balkenlauf= xbegin; balkenlauf < xnbegin; balkenlauf++)
      {
      float xber= (balkenlauf - xbegin)/ float (balkenbreite);
      float yber= shortfunc (xber, kuba[wertelauf], kubb[wertelauf], kubc[wertelauf]);
      signed long yscreen= int (pwerte[wertelauf] + yber*balkenbreite + 0.5);
//      bildschirm.putpixel (balkenlauf - balkenbreite/2 , pwerte[wertelauf], bildschirm.rmax, bildschirm.gmax, bildschirm.bmax);
//    bildschirm.putpixel (balkenlauf - balkenbreite/2, pwerte[wertelauf] + int ((balkenlauf- balkenbreite/2)*steigwerte[wertelauf] + 0.5), bildschirm.rmax, 0, 0);
      bildschirm.putpixel (balkenlauf, yscreen, bildschirm.rmax, bildschirm.gmax, bildschirm.bmax);
      }
    }
  bildschirm.flush ();
  getchar ();
  }

int main (int argc, char** argv)
  {
  if (argc > 1)
    {
    printf ("zuviele Parameter\n");
    return 0;
    }
  argv+= 0;  // Variable benutzen, sonst Compilermecckern dass unbenutzt
  signed long anz= 10;
  signed long* werte= new signed long[anz];
  werte[0]=3*40;
  werte[1]=5*40;
  werte[2]=2*40;
  werte[3]=2*40;
  werte[4]=1*40;
  werte[5]=9*40;
  werte[6]=2*40;
  werte[7]=4*40;
  werte[8]=4*40;
  werte[9]=4*40;
  
  zeichnekubspline (werte, anz);
  }
