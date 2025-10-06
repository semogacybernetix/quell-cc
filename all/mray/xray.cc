#include "../../cc/class/game.h"
#include "../../cc/screen/allscr.h"
#include "../../xwindow/screen/xscr.h"
#include "../../xwindow/keyboard/xkbd.h"

void addebene (cwelt& pwelt)
  {
  // Körperstandpunkte
  cvektor3 kst1 (0,0,0);

  // Körperlagen
  cbasis3 kl1 (cvektor3 (100,0,0), cvektor3 (0,0,100), cvektor3 (0,100,0));

  // Texturen
  cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (0,255,0), 1, 1);

  // Körper
  ckoerper* koerper1= new ckoerper (new csebene, new cparawebene, new cbegrkeine, textur1, kst1, kl1);

  // Körper addieren
  pwelt.addkoerper (koerper1);

  // Augposition setzen
  pwelt.setzeposition (cvektor3 (0, 100, 0));
  }

void addkugel (cwelt& pwelt)
  {
  // Körperstandpunkte
  cvektor3 kst1 (0,0,0);

  // Körperlagen
  cbasis3 kl1 (cvektor3 (100,0,0), cvektor3 (0,0,100), cvektor3 (0,100,0));

  // Texturen
  cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (0,255,0), PI/30, PI/30);

  // Körper
  ckoerper* koerper1= new ckoerper (new cskugel, new cparakugel, new cbegrkeine, textur1, kst1, kl1);

  // Körper addieren
  pwelt.addkoerper (koerper1);

  // Augposition setzen
  pwelt.setzeposition (cvektor3 (0, 100, -300));
  }

void addkatzenkugel (cwelt& pwelt)
  {
  // Körperstandpunkte
  cvektor3 kst1 (0,0,0);

  // Körperlagen
  cbasis3 kl1 (cvektor3 (100,0,0), cvektor3 (0,0,100), cvektor3 (0,100,0));

  // Körper addieren
  pwelt.addkoerper (new ckoerper (new cskugel, new cparawkugel, new cbegrkeine, new cscreenmannig (new cjpegdatei ("/root/quell-cc/xwindow/xdia/bilder/katze.jpg"), real (0.8)), kst1, kl1));

  pwelt.verschiebeauge (cvektor3 (0, 5, -200));
  }

void addtorus (cwelt& pwelt)
  {
  // Körperstandpunkte
  cvektor3 kst1 (0,0,0);

  // Körperlagen
  cbasis3 kl1 (cvektor3 (100,0,0), cvektor3 (0,0,100), cvektor3 (0,100,0));
  //cbasis3 kl1 (cvektor3 (100,0,0), cvektor3 (0,0,400), cvektor3 (0,25,0));          // flacher Ellipsentorus

  // Texturen
  //cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (0,255,0), PI/60, PI/30);
  //cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (0,255,0), PI/60, PI/15);
  cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (0,255,0), PI/80, PI/10);

  // Körper
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.5)), new cparatorus (real (0.5)), new cbegrkeine, textur1, kst1, kl1);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.25)), new cparatorus (real (0.25)), new cbegrkeine, textur1, kst1, kl1);
  ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorus (real (0.125)), new cbegrkeine, textur1, kst1, kl1);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.5)), new cparatorus (real (0.5)), new cbegrkeine, new cscreenmannig (new cjpegdatei ("/root/quell-cc/xwindow/xdia/bilder/katze.jpg"), real (3/PI)), kst1, kl1);

  // Körper addieren
  pwelt.addkoerper (koerper1);

  // Augposition setzen
  pwelt.setzeposition (cvektor3 (0, 100, -300));
  }

void addkoord (cwelt& pwelt)
  {
  // Körperstandpunkte
  cvektor3 kst1 (0,0,0);

  // Körperlagen
  cbasis3 kl1 (cvektor3 (100,0,0), cvektor3 (0,100,0), cvektor3 (0,0,100));

  // Begrenzungen
  //cbegrellipse* ell1= new cbegrellipse (10, 20);

  // Texturen
  cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (127,127,127), 1, 1);

  // Körper
  ckoerper* koerper1= new ckoerper (new csebene, new cparawebene, new cbegrkeine, textur1, kst1, kl1);

  // Körper addieren
  pwelt.addkoerper (koerper1);

  pwelt.verschiebeauge (cvektor3 (0, 100, -100));
  }

void addebenen90 (cwelt& pwelt)
  {
  // Körperstandpunkte
  cvektor3 kst1 (0,0,0);

  // Körperlagen
  cbasis3 kl1 (cvektor3 (10,0,0), cvektor3 (0,10,0), cvektor3 (0,0,10));
  cbasis3 kl2 (cvektor3 (0,10,0), cvektor3 (0,0,10), cvektor3 (10,0,0));
  cbasis3 kl3 (cvektor3 (0,0,10), cvektor3 (10,0,0), cvektor3 (0,10,0));

  // Begrenzungen
  cbegrellipse* ell1= new cbegrellipse (10, 10);

  // Texturen
  cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (0,255,0), 255, 255);
  cschachfeld* textur2= new cschachfeld (cvektor3 (255,0,255), cvektor3 (255,255,0), 255, 255);
  cschachfeld* textur3= new cschachfeld (cvektor3 (255,255,255), cvektor3 (0,255,255), 255, 255);

  // Körper addieren
  pwelt.addkoerper (new ckoerper (new csebene, new cparawebene, ell1, textur1, kst1, kl1));
  pwelt.addkoerper (new ckoerper (new csebene, new cparawebene, ell1, textur2, kst1, kl2));
  pwelt.addkoerper (new ckoerper (new csebene, new cparawebene, ell1, textur3, kst1, kl3));

  pwelt.verschiebeauge (cvektor3 (0, 0, -2250));
  }

void addzylinder (cwelt& pwelt)
  {
  // Körperstandpunkte
  cvektor3 kst1 (0,0,0);
  cvektor3 kst2 (0,1300,0);

  // Körperlagen
  cbasis3 kl1 (cvektor3 (100,0,0), cvektor3 (0,0,100), cvektor3 (0,100,0));
  cbasis3 kl2 (cvektor3 (320,0,0), cvektor3 (0,0,320), cvektor3 (0,320,0));

  // Begrenzungen
  cbegrrechteck* ell1= new cbegrrechteck (-100, 100, -10, 10);

  // Texturen
  //cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (255,255,0), 255, 255);
  cschachfeld* textur2= new cschachfeld (cvektor3 (255,255,255), cvektor3 (0,255,255), 255, 255);
  //cschachfeld* textur3= new cschachfeld (cvektor3 (255,0,255), cvektor3 (0,255,0), 255, 255);

  // Körper addieren
  //pwelt.addkoerper (new ckoerper (new csebene, new cparawebene, ell1, textur1, kst1, kl1));
  //pwelt.addkoerper (new ckoerper (new cskugel, new cparawkugel, new cbegrkeine, new cscreenmannig (new cjpegdatei ("/root/quell-cc/xwindow/xdia/bilder/katze.jpg"), 10), kst2, kl2));
  pwelt.addkoerper (new ckoerper (new cszylinder, new cparawzylinder, ell1, textur2, kst1, kl1));

  pwelt.verschiebeauge (cvektor3 (0, 500, -1000));
  }

void fliegethread ()
  {
  cwelt* welt= new cwelt (450, cvektor3 (0), cbasis3 (1));  // Bildschirmentfernung, Standpunkt, Lage
  welt->himmelfarbe= cvektor3 (0,0,255);

  //addebene (*welt);
  //addkugel (*welt);
  addtorus (*welt);
  //addebenen90 (*welt);
  //addzylinder (*welt);
  //addkatzenkugel (*welt);

  //cflugsimu flugsimu (welt, new cxkeyboard, new cxscreen ("xray", 800, 450));
  cflugsimu flugsimu (welt, new cxkeyboard, new cximagescreen ("xray", 800, 450));

  flugsimu.setframedauer (1000/real (30));               // Framerate setzen
  flugsimu.threadanz= 8;
  flugsimu.bewstep= 2;
  flugsimu.drehstep= real (0.025);

  //flugsimu.fliege ();
  //flugsimu.fliegek ();
  flugsimu.fliegethread ();   // geht nicht mit cxscreen
  //flugsimu.fliegetakt ();
  }

void fliegetakt ()
  {
  cwelt* welt= new cwelt (225, cvektor3 (0), cbasis3 (1));  // Bildschirmentfernung, Standpunkt, Lage
  welt->himmelfarbe= cvektor3 (0,0,255);

  //addebene (*welt);
  //addkugel (*welt);
  addtorus (*welt);
  //addebenen90 (*welt);
  //addzylinder (*welt);
  //addkatzenkugel (*welt);

  //cflugsimu flugsimu (welt, new cxkeyboard, new cxscreen ("xray", 800, 450));
  cflugsimu flugsimu (welt, new cxkeyboard, new cximagescreen ("xray", 400, 225));

  flugsimu.setframedauer (24);               // Framerate setzen
  flugsimu.threadanz= 8;
  flugsimu.bewstep= 2;
  flugsimu.drehstep= real (0.025);

  //flugsimu.fliege ();
  //flugsimu.fliegek ();
  //flugsimu.fliegethread ();   // geht nicht mit cxscreen
  flugsimu.fliegetakt ();
  }

int main ()
  {
  fliegethread ();
  //fliegetakt ();
  return 0;
  }
