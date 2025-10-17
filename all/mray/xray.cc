#include "../../cc/class/game.h"
#include "../../cc/screen/allscr.h"
#include "../../xwindow/screen/xscr.h"
#include "../../xwindow/keyboard/xkbd.h"

void dray ()
  {
  cwelt welt (2520, cvektor3 (0, 100, -1500), cbasis3 (cvektor3 (1,0,0), cvektor3 (0,1,0), cvektor3 (0,0,1)));
  welt.addkoerper (new ckoerper (new csebene, new cparawebene, new cbegrellipse (20, 10), new cschachfeld (cvektor3 (1,0,0), cvektor3 (0,1,0), 1, 1), cvektor3 (0,0,0), cbasis3 (cvektor3 (100,0,0), cvektor3 (0,0,100), cvektor3 (0,100,0))));
  welt.addkoerper (new ckoerper (new cskugel, new cparakugelw, new cbegrkeine (), new cschachfeld (cvektor3 (1,0,1), cvektor3 (1,1,0), 1, 1), cvektor3 (0,1300,0), cbasis3 (cvektor3 (320,0,0), cvektor3 (0,0,-320), cvektor3 (0,320,0))));
//  welt.addkoerper (new ckoerper (new cskugel, new cparakugelw, new cbegrkeine (), new cscreenmannig (new cjpegdatei ("../../xwindow/xdia/bilder/katze.jpg"), 10, 10), cvektor3 (0,1300,0), cbasis3 (cvektor3 (320,0,0), cvektor3 (0,0,-320), cvektor3 (0,320,0))));
  welt.addkoerper (new ckoerper (new cszylinder, new cparawzylinder, new cbegrkeine, new cschachfeld (cvektor3 (1,1,1), cvektor3 (0,1,1), 1, 1), cvektor3 (0,0,0), cbasis3 (cvektor3 (100,0,0), cvektor3 (0,0,100), cvektor3 (0,100,0))));
  cxscreen screen ("ray", 1600, 900);
  cxkeyboard keyboard;
  cflugsimu flugsimu (&welt, &keyboard, &screen);
  flugsimu.fliege ();
  }

void xray18 ()
  {
  cwelt welt (2520, cvektor3 (0, 100, -1500), cbasis3 (cvektor3 (1,0,0), cvektor3 (0,1,0), cvektor3 (0,0,1)));
  welt.addkoerper (new ckoerper (new csebene, new cparawebene, new cbegrellipse (20, 10), new cschachfeld (cvektor3 (255,0,0), cvektor3 (0,255,0), 100, 100), cvektor3 (0,0,0), cbasis3 (cvektor3 (100,0,0), cvektor3 (0,0,100), cvektor3 (0,100,0))));
  welt.addkoerper (new ckoerper (new cskugel, new cparakugelw, new cbegrkeine (), new cschachfeld (cvektor3 (255,0,255), cvektor3 (255,255,0), 100, 100), cvektor3 (0,1300,0), cbasis3 (cvektor3 (320,0,0), cvektor3 (0,0,-320), cvektor3 (0,320,0))));
//  welt.addkoerper (new ckoerper (new cskugel, new cparakugelw, new cbegrkeine (), new cscreenmannig (new cjpegdatei ("../../xwindow/xdia/bilder/katze.jpg"), 10, 10), cvektor3 (0,1300,0), cbasis3 (cvektor3 (320,0,0), cvektor3 (0,0,-320), cvektor3 (0,320,0))));
  welt.addkoerper (new ckoerper (new cszylinder, new cparawzylinder, new cbegrkeine, new cschachfeld (cvektor3 (255,255,255), cvektor3 (0,255,255), 100, 100), cvektor3 (0,0,0), cbasis3 (cvektor3 (100,0,0), cvektor3 (0,0,100), cvektor3 (0,100,0))));
  cxscreen screen ("ray", 1600, 900);
  cxkeyboard keyboard;
  cflugsimu flugsimu (&welt, &keyboard, &screen);
  flugsimu.fliege ();
  }

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

void addkoord (cwelt& pwelt)
  {
  // Körperstandpunkte
  cvektor3 kst1 (0,0,0);
  cvektor3 kst2 (0,1300,0);

  // Körperlagen
  cbasis3 kl1 (cvektor3 (100,0,0), cvektor3 (0,0,100), cvektor3 (0,100,0));
  cbasis3 kl2 (cvektor3 (0,100,0), cvektor3 (100,0,0), cvektor3 (0,0,100));
  cbasis3 kl3 (cvektor3 (0,0,100), cvektor3 (0,100,0), cvektor3 (100,0,0));

  // Begrenzungen
  //cbegrrechteck* ell1= new cbegrrechteck (-100, 100, -10, 10);

  // Texturen
  cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (255,255,0), 6/PI, 6/PI);
  cschachfeld* textur2= new cschachfeld (cvektor3 (255,255,255), cvektor3 (0,255,255), 6/PI, 6/PI);
  cschachfeld* textur3= new cschachfeld (cvektor3 (255,0,255), cvektor3 (0,255,0), 6/PI, 6/PI);

  // Körper addieren
  pwelt.addkoerper (new ckoerper (new cszylinder, new cparawzylinder, new cbegrkeine, textur1, kst1, kl1));
  pwelt.addkoerper (new ckoerper (new cszylinder, new cparawzylinder, new cbegrkeine, textur2, kst1, kl2));
  pwelt.addkoerper (new ckoerper (new cszylinder, new cparawzylinder, new cbegrkeine, textur3, kst1, kl3));

  pwelt.verschiebeauge (cvektor3 (3000, 3000, -7000));
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
  cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (0,255,0), 6/PI, 6/PI);
  cschachfeld* textur2= new cschachfeld (cvektor3 (255,0,255), cvektor3 (255,255,0), 6/PI, 6/PI);
  cschachfeld* textur3= new cschachfeld (cvektor3 (255,255,255), cvektor3 (0,255,255), 6/PI, 6/PI);

  // Körper addieren
  pwelt.addkoerper (new ckoerper (new csebene, new cparawebene, ell1, textur1, kst1, kl1));
  pwelt.addkoerper (new ckoerper (new csebene, new cparawebene, ell1, textur2, kst1, kl2));
  pwelt.addkoerper (new ckoerper (new csebene, new cparawebene, ell1, textur3, kst1, kl3));

  pwelt.verschiebeauge (cvektor3 (10, 50, -300));
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
  //cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (255,255,0), 12/PI, 12/PI);
  cschachfeld* textur2= new cschachfeld (cvektor3 (255,255,255), cvektor3 (0,255,255), 12/PI, 12/PI);
  //cschachfeld* textur3= new cschachfeld (cvektor3 (255,0,255), cvektor3 (0,255,0), 12/PI, 12/PI);

  // Körper addieren
  //pwelt.addkoerper (new ckoerper (new csebene, new cparawebene, ell1, textur1, kst1, kl1));
  //pwelt.addkoerper (new ckoerper (new cskugel, new cparawkugel, new cbegrkeine, new cscreenmannig (new cjpegdatei ("/root/quell-cc/xwindow/xdia/bilder/katze.jpg"), 10), kst2, kl2));
  pwelt.addkoerper (new ckoerper (new cszylinder, new cparawzylinder, ell1, textur2, kst1, kl1));

  pwelt.verschiebeauge (cvektor3 (0, 500, -1000));
  }

void addkugel (cwelt& pwelt)
  {

  // Körperstandpunkte
  cvektor3 kst1 (0,0,0);

  // Körperlagen
  cbasis3 kl1 (cvektor3 (100,0,0), cvektor3 (0,0,100), cvektor3 (0,100,0));

  // Texturen
  //cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (0,255,0), 18/PI, 18/PI);

  // Körper
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelu, new cbegrkeine, textur1, kst1, kl1);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelw, new cbegrkeine, textur1, kst1, kl1);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelu, new cbegrkeine, new cscreenmannig (new cjpegdatei ("/root/quell-cc/xwindow/xdia/bilder/catchick600.jpg"), 2/PI, 2/PI), kst1, kl1);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelw, new cbegrkeine, new cscreenmannig (new cjpegdatei ("/root/quell-cc/xwindow/xdia/bilder/catchick600.jpg"), 12/PI, 12/PI), kst1, kl1);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelw, new cbegrkeine, new cscreenmannig (new cjpegdatei ("/root/quell-cc/xwindow/xdia/bilder/catchick600.jpg"), real (0.5)/PI, real (0.5)/PI), kst1, kl1);
  ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelw, new cbegrkeine, new cscreenmannig (new cjpegdatei ("/root/quell-cc/xwindow/xdia/texturen/karten/mercatorp-n.jpg"), real (1)/PI, real (1)/PI), kst1, kl1);

  // Körper addieren
  pwelt.addkoerper (koerper1);

  // Augposition setzen
  pwelt.setzeposition (cvektor3 (0, 100, -300));
  }

void addtorus (cwelt& pwelt)
  {
  // Körperstandpunkte
  cvektor3 kst1 (0,0,0);

  // Körperlagen
  cbasis3 kl1 (cvektor3 (100,0,0), cvektor3 (0,0,100), cvektor3 (0,100,0));
  //cbasis3 kl1 (cvektor3 (100,0,0), cvektor3 (0,0,400), cvektor3 (0,25,0));          // flacher Ellipsentorus

  // Texturen
  //cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (0,255,0), 80/PI, 10/PI);
  //cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (0,255,0), PI/60, PI/15);
  //cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (0,255,0), PI/80, PI/10);

  // Körper
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorus, new cbegrkeine, textur1, kst1, kl1);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.25)), new cparatorus, new cbegrkeine, new cscreenmannig (new cjpegdatei ("/root/quell-cc/xwindow/xdia/bilder/catchick600.jpg"), real (8/PI), real (2/PI)), kst1, kl1);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorus, new cbegrkeine, new cscreenmannig (new cjpegdatei ("/root/quell-cc/xwindow/xdia/texturen/sechseck1024.jpg"), real (8/PI), real (1/PI)), kst1, kl1);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorus, new cbegrkeine, new cscreenmannig (new cjpegdatei ("/root/quell-cc/xwindow/xdia/texturen/wabe512.jpg"), real (16/PI), real (2/PI)), kst1, kl1);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorus, new cbegrkeine, new cscreenmannig (new cjpegdatei ("/root/quell-cc/xwindow/xdia/texturen/wabe-rs512.jpg"), real (16/PI), real (2/PI)), kst1, kl1);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorus, new cbegrkeine, new cscreenmannig (new cjpegdatei ("/root/quell-cc/xwindow/xdia/texturen/Bergsee.jpg"), real (16/PI), real (2/PI)), kst1, kl1);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorus, new cbegrkeine, new cscreenmannig (new cjpegdatei ("/root/quell-cc/xwindow/xdia/texturen/Meer.jpg"), real (16/PI), real (2/PI)), kst1, kl1);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorus, new cbegrkeine, new cscreenmannig (new cjpegdatei ("/root/quell-cc/xwindow/xdia/texturen/Palmen.jpg"), real (16/PI), real (2/PI)), kst1, kl1);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorus, new cbegrkeine, new cscreenmannig (new cjpegdatei ("/root/quell-cc/xwindow/xdia/texturen/Steine.jpg"), real (16/PI), real (2/PI)), kst1, kl1);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorus, new cbegrkeine, new cscreenmannig (new cjpegdatei ("/root/quell-cc/xwindow/xdia/texturen/Steinmauer.jpg"), real (16/PI), real (2/PI)), kst1, kl1);
  ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorus, new cbegrkeine, new cscreenmannig (new cjpegdatei ("/root/quell-cc/xwindow/xdia/texturen/Steinstrand.jpg"), real (16/PI), real (2/PI)), kst1, kl1);

  pwelt.himmelfarbe= cvektor3 (30,75,90);

  // Körper addieren
  pwelt.addkoerper (koerper1);

  // Augposition setzen
  pwelt.setzeposition (cvektor3 (0, 100, -300));
  }

void fliegethread ()
  {
  //cwelt* welt= new cwelt (450, cvektor3 (0), cbasis3 (1));  // Bildschirmentfernung, Standpunkt, Lage
  cwelt* welt= new cwelt (900, cvektor3 (0), cbasis3 (1));  // Bildschirmentfernung, Standpunkt, Lage

  //addebene (*welt);
  //addkoord (*welt);
  //addebenen90 (*welt);
  //addzylinder (*welt);
  //addkugel (*welt);
  addtorus (*welt);

  //cflugsimu flugsimu (welt, new cxkeyboard, new cxscreen ("xray", 800, 450));
  //cflugsimu flugsimu (welt, new cxkeyboard, new cximagescreen ("xray", 800, 450));
  cflugsimu flugsimu (welt, new cxkeyboard, new cximagescreen ("xray", 1600, 900));

  flugsimu.setframerate (real (20.0));
  flugsimu.threadanz= 12;
  flugsimu.bewstep= real (1);
  flugsimu.drehstep= real (0.0125);

  //flugsimu.fliege ();
  //flugsimu.fliegek ();
  flugsimu.fliegethread ();   // geht nicht mit cxscreen
  //flugsimu.fliegetakt ();
  }

void fliegetakt ()
  {
  //cwelt* welt= new cwelt (225, cvektor3 (0), cbasis3 (1));  // Bildschirmentfernung, Standpunkt, Lage
  cwelt* welt= new cwelt (450, cvektor3 (0), cbasis3 (1));  // Bildschirmentfernung, Standpunkt, Lage

  //addebene (*welt);
  //addkoord (*welt);
  //addebenen90 (*welt);
  //addzylinder (*welt);
  //addkugel (*welt);
  addtorus (*welt);

  //cflugsimu flugsimu (welt, new cxkeyboard, new cxscreen ("xray", 800, 450));
  //cflugsimu flugsimu (welt, new cxkeyboard, new cximagescreen ("xray", 400, 225));
  cflugsimu flugsimu (welt, new cxkeyboard, new cximagescreen ("xray", 800, 450));

  flugsimu.setframerate (real (20));               // Framerate setzen
  flugsimu.threadanz= 12;
  flugsimu.bewstep= 2;
  flugsimu.drehstep= real (0.025);

  //flugsimu.fliege ();
  //flugsimu.fliegek ();
  //flugsimu.fliegethread ();   // geht nicht mit cxscreen
  flugsimu.fliegetakt ();
  }

int main ()
  {
  //xray18 ();
  fliegethread ();
  //fliegetakt ();
  return 0;
  }

