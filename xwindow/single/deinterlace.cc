#include "../../cc/screen/allscr.h"

#include <stdio.h>
#include <iostream>

using namespace std;

// Bestimmt das Volumen einer über einem quadratischem Pixel
// Die a-Werte sind die Höhen der Ecken
// Die xy-Werte sind die Integrationsgrenzen

float volzelle (float a0, float ax, float ay, float a1, float xu, float xo, float yu, float yo)
  {
  float f0= a0*(xo-xu)*(yo-yu);
  float f1= 0.5*((ax-a0)*(yo-yu)*(xo*xo-xu*xu)+(ay-a0)*(xo-xu)*(yo*yo-yu*yu));
  float f2= 0.25*(a0+a1-ax-ay)*(xo*xo-xu*xu)*(yo*yo-yu*yu);
  return f0 + f1 + f2;
  }

// x-Richtung nach rechts, y-Richtung nach oben
void volmainpixel (cbmpdatei& p_frame, signed long px, signed long py, long double& pr, long double& pg, long double& pb)
  {
  signed long sx, sy;
  long double a0r, a0g,a0b, axr, axg, axb, ayr, ayg, ayb, a1r, a1g, a1b;
  float zr, zg, zb;
  zr= zg= zb= 0;
  // linkes unteres Teilstück
  if (px > 1)
         sx= px - 1;
    else sx= px;
  if (py > 1)
         sy= py - 1;
    else sy= py;
  p_frame.getpixel (sx, sy, a0r, a0g, a0b);
  p_frame.getpixel (px, sy, axr, axg, axb);
  p_frame.getpixel (sx, py, ayr, ayg, ayb);
  p_frame.getpixel (px, py, a1r, a1g, a1b);
  zr+= 2*volzelle (a0r, axr, ayr, a1r, 0.5, 1, 0.75, 1);
  zg+= 2*volzelle (a0g, axg, ayg, a1g, 0.5, 1, 0.75, 1);
  zb+= 2*volzelle (a0b, axb, ayb, a1b, 0.5, 1, 0.75, 1);
  // rechtes unteres Teilstück
  if (px < p_frame.xanz - 2)
         sx= px + 1;
    else sx= px;
  if (py > 1)
         sy= py - 1;
    else sy= py;
  p_frame.getpixel (px, sy, a0r, a0g, a0b);
  p_frame.getpixel (sx, sy, axr, axg, axb);
  p_frame.getpixel (px, py, ayr, ayg, ayb);
  p_frame.getpixel (sx, py, a1r, a1g, a1b);
  zr+= 2*volzelle (a0r, axr, ayr, a1r, 0, 0.5, 0.75, 1);
  zg+= 2*volzelle (a0g, axg, ayg, a1g, 0, 0.5, 0.75, 1);
  zb+= 2*volzelle (a0b, axb, ayb, a1b, 0, 0.5, 0.75, 1);
  // linkes oberes Teilstück
  if (px > 1)
         sx= px - 1;
    else sx= px;
  if (py < p_frame.yanz - 2)
         sy= py + 1;
    else sy= py;
  p_frame.getpixel (sx, py, a0r, a0g, a0b);
  p_frame.getpixel (px, py, axr, axg, axb);
  p_frame.getpixel (sx, sy, ayr, ayg, ayb);
  p_frame.getpixel (px, sy, a1r, a1g, a1b);
  zr+= 2*volzelle (a0r, axr, ayr, a1r, 0.5, 1, 0, 0.25);
  zg+= 2*volzelle (a0g, axg, ayg, a1g, 0.5, 1, 0, 0.25);
  zb+= 2*volzelle (a0b, axb, ayb, a1b, 0.5, 1, 0, 0.25);
  // rechtes oberes Teilstück
  if (px < p_frame.xanz - 2)
         sx= px + 1;
    else sx= px;
  if (py < p_frame.yanz - 2)
         sy= py + 1;
    else sy= py;
  p_frame.getpixel (px, py, a0r, a0g, a0b);
  p_frame.getpixel (sx, py, axr, axg, axb);
  p_frame.getpixel (px, sy, ayr, ayg, ayb);
  p_frame.getpixel (sx, sy, a1r, a1g, a1b);
  zr+= 2*volzelle (a0r, axr, ayr, a1r, 0, 0.5, 0, 0.25);
  zg+= 2*volzelle (a0g, axg, ayg, a1g, 0, 0.5, 0, 0.25);
  zb+= 2*volzelle (a0b, axb, ayb, a1b, 0, 0.5, 0, 0.25);
  pr= int (zr + 0.5);
  pg= int (zg + 0.5);
  pb= int (zb + 0.5);
  }
  
// x-Richtung nach rechts, y-Richtung nach oben
void voluntererzwischenpixel (cbmpdatei& p_frame, signed long px, signed long py, long double& pr, long double& pg, long double& pb)
  {
  signed long sx, sy;
  long double a0r, a0g,a0b, axr, axg, axb, ayr, ayg, ayb, a1r, a1g, a1b;
  float zr, zg, zb;
  zr= zg= zb= 0;
  // linkes Teilstück
  if (px > 1)
         sx= px - 1;
    else sx= px;
  if (py > 1)
         sy= py - 1;
    else sy= py;
  p_frame.getpixel (sx, sy, a0r, a0g, a0b);
  p_frame.getpixel (px, sy, axr, axg, axb);
  p_frame.getpixel (sx, py, ayr, ayg, ayb);
  p_frame.getpixel (px, py, a1r, a1g, a1b);
  zr+= 2*volzelle (a0r, axr, ayr, a1r, 0.5, 1, 0.25, 0.75);
  zg+= 2*volzelle (a0g, axg, ayg, a1g, 0.5, 1, 0.25, 0.75);
  zb+= 2*volzelle (a0b, axb, ayb, a1b, 0.5, 1, 0.25, 0.75);
  // rechtes Teilstück
  if (px < p_frame.xanz - 2)
         sx= px + 1;
    else sx= px;
  if (py > 1)
         sy= py - 1;
    else sy= py;
  p_frame.getpixel (px, sy, a0r, a0g, a0b);
  p_frame.getpixel (sx, sy, axr, axg, axb);
  p_frame.getpixel (px, py, ayr, ayg, ayb);
  p_frame.getpixel (sx, py, a1r, a1g, a1b);
  zr+= 2*volzelle (a0r, axr, ayr, a1r, 0, 0.5, 0.25, 0.75);
  zg+= 2*volzelle (a0g, axg, ayg, a1g, 0, 0.5, 0.25, 0.75);
  zb+= 2*volzelle (a0b, axb, ayb, a1b, 0, 0.5, 0.25, 0.75);
  pr= int (zr + 0.5);
  pg= int (zg + 0.5);
  pb= int (zb + 0.5);
  }
  
// x-Richtung nach rechts, y-Richtung nach oben
void volobererzwischenpixel (cbmpdatei& p_frame, signed long px, signed long py, long double& pr, long double& pg, long double& pb)
  {
  signed long sx, sy;
  long double a0r, a0g,a0b, axr, axg, axb, ayr, ayg, ayb, a1r, a1g, a1b;
  float zr, zg, zb;
  zr= zg= zb= 0;
  // linkes Teilstück
  if (px > 1)
         sx= px - 1;
    else sx= px;
  if (py < p_frame.yanz - 2)
         sy= py + 1;
    else sy= py;
  p_frame.getpixel (sx, py, a0r, a0g, a0b);
  p_frame.getpixel (px, py, axr, axg, axb);
  p_frame.getpixel (sx, sy, ayr, ayg, ayb);
  p_frame.getpixel (px, sy, a1r, a1g, a1b);
  zr+= 2*volzelle (a0r, axr, ayr, a1r, 0.5, 1, 0.25, 0.75);
  zg+= 2*volzelle (a0g, axg, ayg, a1g, 0.5, 1, 0.25, 0.75);
  zb+= 2*volzelle (a0b, axb, ayb, a1b, 0.5, 1, 0.25, 0.75);
  // rechtes Teilstück
  if (px < p_frame.xanz - 2)
         sx= px + 1;
    else sx= px;
  if (py < p_frame.yanz - 2)
         sy= py + 1;
    else sy= py;
  p_frame.getpixel (px, py, a0r, a0g, a0b);
  p_frame.getpixel (sx, py, axr, axg, axb);
  p_frame.getpixel (px, sy, ayr, ayg, ayb);
  p_frame.getpixel (sx, sy, a1r, a1g, a1b);
  zr+= 2*volzelle (a0r, axr, ayr, a1r, 0, 0.5, 0.25, 0.75);
  zg+= 2*volzelle (a0g, axg, ayg, a1g, 0, 0.5, 0.25, 0.75);
  zb+= 2*volzelle (a0b, axb, ayb, a1b, 0, 0.5, 0.25, 0.75);
  pr= int (zr + 0.5);
  pg= int (zg + 0.5);
  pb= int (zb + 0.5);
  }
  
void averageframe1 (cbmpdatei& p_frame1, cbmpdatei& p_frameav)
  {
  long double pr, pg, pb;
  long double pr2, pg2, pb2;
  // Bildteil
  for (signed long ylauf= 0; ylauf < p_frame1.yanz; ylauf++)
    for (signed long xlauf= 0; xlauf < p_frame1.xanz; xlauf++)
      {
      p_frame1.getpixel (xlauf, ylauf, pr, pg, pb);
      p_frameav.putpixel (xlauf, ylauf*2, pr, pg, pb);
      p_frame1.getpixel (xlauf, ylauf + 1, pr2, pg2, pb2);
      p_frameav.putpixel (xlauf, ylauf*2 + 1, (pr + pr2)/2, (pg + pg2)/2, (pb + pb2)/2);
      }
  }
  
void averageframe2 (cbmpdatei& p_frame2, cbmpdatei& p_frameav)
  {
  long double pr, pg, pb;
  long double pr2, pg2, pb2;
  for (signed long ylauf= 0; ylauf < p_frame2.yanz; ylauf++)
    for (signed long xlauf= 0; xlauf < p_frame2.xanz; xlauf++)
      {
      p_frame2.getpixel (xlauf, ylauf, pr, pg, pb);
      p_frameav.putpixel (xlauf, ylauf*2 + 1, pr, pg, pb);
      p_frame2.getpixel (xlauf, ylauf - 1, pr2, pg2, pb2);
      p_frameav.putpixel (xlauf, ylauf*2, (pr + pr2)/2, (pg + pg2)/2, (pb + pb2)/2);
      }
  }
  
void interpolateframe1 (cbmpdatei& p_frame1, cbmpdatei& p_frameip)
  {
  long double pr, pg, pb;
  for (signed long ylauf= 0; ylauf < p_frame1.yanz; ylauf++)
    for (signed long xlauf= 0; xlauf < p_frame1.xanz; xlauf++)
      {
      volmainpixel (p_frame1, xlauf, ylauf, pr, pg, pb);
      p_frameip.putpixel (xlauf, ylauf*2, pr, pg, pb);
      volobererzwischenpixel (p_frame1, xlauf, ylauf, pr, pg, pb);
      p_frameip.putpixel (xlauf, ylauf*2 + 1, pr, pg, pb);
      }
  }
  
void interpolateframe2 (cbmpdatei& p_frame2, cbmpdatei& p_frameip)
  {
  long double pr, pg, pb;
  for (signed long ylauf= 0; ylauf < p_frame2.yanz; ylauf++)
    for (signed long xlauf= 0; xlauf < p_frame2.xanz; xlauf++)
      {
      voluntererzwischenpixel (p_frame2, xlauf, ylauf, pr, pg, pb);
      p_frameip.putpixel (xlauf, ylauf*2, pr, pg, pb);
      volmainpixel (p_frame2, xlauf, ylauf, pr, pg, pb);
      p_frameip.putpixel (xlauf, ylauf*2 + 1, pr, pg, pb);
      }
  }
  
void maskframe (cbmpdatei& p_frame)
  {
  // oberste und unterste 2 Zeile werden schwarz maskiert
  for (signed long xlauf= 0; xlauf < p_frame.xanz; xlauf++)
    {
    p_frame.putpixel (xlauf, 0, 0, 0, 0);
    p_frame.putpixel (xlauf, 1, 0, 0, 0);
    p_frame.putpixel (xlauf, p_frame.yanz - 1, 0, 0, 0);
    p_frame.putpixel (xlauf, p_frame.yanz - 2, 0, 0, 0);
    }
  }
  
void splitframe (cbmpdatei& p_quelle, cbmpdatei& p_frame1, cbmpdatei& p_frame2)
  {
  cout << endl;
  cout << "Bild Breite:  " << p_quelle.xanz << endl;
  cout << "Bild Hoehe:   " << p_quelle.yanz << endl;
  cout << endl;
 long double fr, fg, fb;
  for (signed long ylauf= 0; ylauf < p_quelle.yanz; ylauf++)
    for (signed long xlauf= 0; xlauf < p_quelle.xanz; xlauf++)
      {
      p_quelle.getpixel (xlauf, ylauf, fr, fg, fb);
      if (ylauf%2 == 0)
        p_frame1.putpixel (xlauf, ylauf/2, fr,fg, fb);
        else
        p_frame2.putpixel (xlauf, ylauf/2, fr,fg, fb);
	    }
  }
  
void extractaverage (char* p_quelle)
  {
  cbmpdatei framei (p_quelle);
  cbmpdatei frame1 ("frame1.bmp", framei.xanz, framei.yanz/2);
  cbmpdatei frame2 ("frame2.bmp", framei.xanz, framei.yanz/2);
  splitframe (framei, frame1, frame2);
  cbmpdatei frame1ip("frame1av.bmp", framei.xanz, framei.yanz);
  averageframe1 (frame1, frame1ip);
  maskframe (frame1ip);
  cbmpdatei frame2ip("frame2av.bmp", framei.xanz, framei.yanz);
  averageframe2 (frame2, frame2ip);
  maskframe (frame2ip);
  }
  
void extractlinear (char* p_quelle)
  {
  cbmpdatei framei (p_quelle);
  cbmpdatei frame1 ("frame1.bmp", framei.xanz, framei.yanz/2);
  cbmpdatei frame2 ("frame2.bmp", framei.xanz, framei.yanz/2);
  splitframe (framei, frame1, frame2);
  cbmpdatei frame1ip("frame1ip.bmp", framei.xanz, framei.yanz);
  interpolateframe1 (frame1, frame1ip);
  maskframe (frame1ip);
  cbmpdatei frame2ip("frame2ip.bmp", framei.xanz, framei.yanz);
  interpolateframe2 (frame2, frame2ip);
  maskframe (frame2ip);
  }
  
void aviinfo (char* p_quelle, char* p_ziel)
  {
  cavidatei quelldatei (p_quelle);
  cout << endl;
  cout << "Bild Breite:  " << quelldatei.xanz << endl;
  cout << "Bild Hoehe:   " << quelldatei.yanz << endl;
  cout << "Frames:       " << quelldatei.frameanz << endl;
  cout << endl;
  cbmpdatei zieldatei (p_ziel, quelldatei.xanz, quelldatei.yanz);
  zieldatei.putscreen (quelldatei, 0, 0);
  }

int main (int argc, char** argv)
  {
  if (argc != 3)
    return 0;

  aviinfo (argv[1], argv[2]);
  //splitframe (argv[1], argv[2]);
  extractaverage (argv[1]);
  extractlinear (argv[1]);
  return 0;
  }
