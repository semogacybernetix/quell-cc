#include "../../cc/class/game.h"
#include "../../cc/screen/allscr.h"
#include "../../xwindow/keyboard/xkbd.h"
#include "../../framebuffer/keyboard/nckbd.h"

void addebene (cwelt& pwelt)
  {
  // Körperstandpunkte
  cvektor3 kst1 (0,0,0);

  // Körperlagen
  cbasis3 kl1 (cvektor3 (10,0,0), cvektor3 (0,0,10), cvektor3 (0,10,0));

  // Texturen
  //cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (0,255,0), 1, 1);
  cschachfeld* textur1= new cschachfeld (cvektor3 (255,127,0), cvektor3 (0,255,255), 1, 1);

  // Körper
  //ckoerper* koerper1= new ckoerper (new csebene, new cparaebenew, new cbegrkeine, textur1, kst1, kl1);
  //ckoerper* koerper1= new ckoerper (new cshyper (1), new cparaebenew, new cbegrkeine, textur1, kst1, kl1);
  ckoerper* koerper1= new ckoerper (new cshpara, new cparaebenew, new cbegrkeine, textur1, kst1, kl1);

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
  pwelt.addkoerper (new ckoerper (new cszylinder, new cparazylinderw, new cbegrkeine, textur1, kst1, kl1));
  pwelt.addkoerper (new ckoerper (new cszylinder, new cparazylinderw, new cbegrkeine, textur2, kst1, kl2));
  pwelt.addkoerper (new ckoerper (new cszylinder, new cparazylinderw, new cbegrkeine, textur3, kst1, kl3));

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
  pwelt.addkoerper (new ckoerper (new csebene, new cparaebenew, ell1, textur1, kst1, kl1));
  pwelt.addkoerper (new ckoerper (new csebene, new cparaebenew, ell1, textur2, kst1, kl2));
  pwelt.addkoerper (new ckoerper (new csebene, new cparaebenew, ell1, textur3, kst1, kl3));

  pwelt.verschiebeauge (cvektor3 (10, 50, -300));
  }

void addkatzenturm (cwelt& pwelt)
  {
  // Körperstandpunkte
  cvektor3 kst1 (0,0,0);
  cvektor3 kst2 (0,1300,0);

  // Körperlagen
  cbasis3 kl1 (cvektor3 (100,0,0), cvektor3 (0,0,100), cvektor3 (0,100,0));
  cbasis3 kl2 (cvektor3 (320,0,0), cvektor3 (0,0,320), cvektor3 (0,320,0));

  // Begrenzungen
  cbegrellipse* ell1= new cbegrellipse (100, 200);

  // Texturen
  cschachfeld* textur1= new cschachfeld (cvektor3 (1,0,0), cvektor3 (0,1,0), 1, 1);
  cschachfeld* textur2= new cschachfeld (cvektor3 (1,1,1), cvektor3 (0,1,1), 1, 1);

  // Körper addieren
  pwelt.addkoerper (new ckoerper (new csebene, new cparaebenew, ell1, textur1, kst1, kl1));
  pwelt.addkoerper (new ckoerper (new cskugel, new cparakugelw, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Bilder/katze.jpg"), 10, 10), kst2, kl2));
  pwelt.addkoerper (new ckoerper (new cszylinder, new cparazylinderw, ell1, textur2, kst1, kl1));

  pwelt.verschiebeauge (cvektor3 (0, 500, -10000));
  }

void addzylinder (cwelt& pwelt)
  {
  // Körperstandpunkte
  cvektor3 kst1 (0,0,0);
  cvektor3 kst2 (0,1300,0);

  // Körperlagen
  //cbasis3 kl1 (cvektor3 (100,0,0), cvektor3 (0,0,100), cvektor3 (0,100,0));
  cbasis3 kl1 (cvektor3 (20,0,0), cvektor3 (0,0,20), cvektor3 (0,20,0));
  //cbasis3 kl2 (cvektor3 (320,0,0), cvektor3 (0,0,320), cvektor3 (0,320,0));

  // Begrenzungen
  //cbegrrechteck* ell1= new cbegrrechteck (-100, 100, -10, 10);

  // Texturen
  //cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (255,255,0), 12/PI, 12/PI);
  cschachfeld* textur2= new cschachfeld (cvektor3 (255,255,255), cvektor3 (0,0,0), 12/PI, 12/PI);
  //cschachfeld* textur3= new cschachfeld (cvektor3 (255,0,255), cvektor3 (0,255,0), 12/PI, 12/PI);

  // Körper addieren
  //pwelt.addkoerper (new ckoerper (new csebene, new cparawebene, ell1, textur1, kst1, kl1));
  //pwelt.addkoerper (new ckoerper (new cskugel, new cparakugelw, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Bilder/katze.jpg"), 10, 10), kst2, kl1));
  //pwelt.addkoerper (new ckoerper (new cszylinder, new cparawzylinder, ell1, textur2, kst1, kl1));
  pwelt.addkoerper (new ckoerper (new cszylinder, new cparazylinderw, new (cbegrkeine), textur2, kst1, kl1));

  pwelt.verschiebeauge (cvektor3 (0, 500, -1000));
  }

void addkugel (cwelt& pwelt)
  {
  // Körperstandpunkte
  cvektor3 kstobj (0,0,0);
  cvektor3 kstauge (500,0,0);

  // Körperlagen
  cbasis3 klobj (cvektor3 (100,0,0), cvektor3 (0,100,0), cvektor3 (0,0,-100));
  cbasis3 klauge (cvektor3 (0,1,0), cvektor3 (0,0,-1), cvektor3 (-1,0,0));

  // Texturen
  //cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (0,255,0), 18/PI, 18/PI);
  //cschachfeld* textur2= new cschachfeld (cvektor3 (255,255,0), cvektor3 (255,0,255), 18/PI, 18/PI);

  // Begrenzungen
  //cbegrrechteck* begr1= new cbegrrechteck (-10, 10, real (-2.4), real (2.4));    // für (6732 Mercator-blz Straßennetz.jpg)

  // Bilder
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelg, new cbegrkeine, textur1, kstkugel, klkugel);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelw, new cbegrkeine, textur2, kstobj, kl1);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelw, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Bilder/catchick600.jpg"), 2/PI, 2/PI), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelw, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Bilder/catchick600.jpg"), 12/PI, 12/PI), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelw, new cbegrkeine, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Bilder/catchick600.jpg"), real (1)/PI, 0), kstobj, klobj);

  // Plattkarten
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugel, new cbegrkeine, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Plattkarten/0400 platt hellblau.jpg"), real (1)/PI, 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugel2, new cbegrkeine, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Plattkarten/1000 platt dunkelblau.jpg"), real (1)/PI, 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugel2, new cbegrkeine, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Plattkarten/1436 platt-z politisch.jpg"), real (1)/PI, 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugel, new cbegrkeine, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Plattkarten/1466 platt schief.jpg"), real (1)/PI, 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugel2, new cbegrkeine, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Plattkarten/2044 platt-z physisch.jpg"), real (1)/PI, 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugel, new cbegrkeine, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Plattkarten/2048 platt-v dunkelblau.jpg"), real (1)/PI, 0), kstobj, klobj);

  // Mercatorkarten
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelw2, new cbegrkeine, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Mercatorkarten/0262 Mercator-blza physisch.jpg"), real (1)/PI, 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelw, new cbegrkeine, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Mercatorkarten/0400 Mercator quer.jpg"), real (1)/PI, 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelw, new cbegrkeine, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Mercatorkarten/0576 Mercator Gradnetz.jpg"), real (1)/PI, 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelw, new cbegrkeine, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Mercatorkarten/0677 Mercator-blza monochrom.jpg"), real (1)/PI, 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelw, new cbegrkeine, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Mercatorkarten/1008 Mercator-blza physisch mittelblau.jpg"), real (1)/PI, 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelw, new cbegrkeine, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Mercatorkarten/1200 Mercator-bv politisch rand.jpg"), real (1)/PI, 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelw, new cbegrkeine, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Mercatorkarten/2054 Mercator-blza physisch hellblau.jpg"), real (1)/PI, 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelw2, new cbegrkeine, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Mercatorkarten/2400 Mercator-blza physisch dunkelblau.jpg"), real (1)/PI, 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelw, new cbegrkeine, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Mercatorkarten/2768 Mercator-bl85 braun.jpg"), real (1)/PI, 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelw, new cbegrkeine, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Mercatorkarten/3821 Mercator-blz politisch.jpg"), real (1)/PI, 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelw, new cbegrkeine, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Mercatorkarten/6732 Mercator-blz Straßennetz.jpg"), real (1)/PI, 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelw2, new cbegrkeine, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Mercatorkarten/7682 Mercator-blz politisch.jpg"), real (1)/PI, 0), kstobj, klobj);

  // Polkarten gnomonisch
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelg, new cbegrkeine, new cscreentexturpol (new cjpegdatei ("/root/quell-cc/media/Polkarten/0400 gnom hellblau.jpg"), real (1)/PI, 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelg, new cbegrkeine, new cscreentexturpol (new cjpegdatei ("/root/quell-cc/media/Polkarten/3000 gnom weltall.jpg"), real (1)/PI, 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelg, new cbegrkeine, new cscreentexturpol (new cjpegdatei ("/root/quell-cc/media/Polkarten/5000 gnom Nordpol.jpg"), real (1)/PI, 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelg, new cbegrkeine, new cscreentexturpol (new cjpegdatei ("/root/quell-cc/media/Polkarten/5000 gnom Nordpol kontrast.jpg"), real (1)/PI, 0), kstobj, klobj);

  // Polkarten stereografisch
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugels, new cbegrkeine, new cscreentexturpol (new cjpegdatei ("/root/quell-cc/media/Polkarten/0339 stereo 00 rot.jpg"), real (0.133), 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugels, new cbegrkeine, new cscreentexturpol (new cjpegdatei ("/root/quell-cc/media/Polkarten/0339 stereo 180 rot.jpg"), real (0.133), 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugels, new cbegrkeine, new cscreentexturpol (new cjpegdatei ("/root/quell-cc/media/Polkarten/0400 stereo bla.jpg"), real (0.08), 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugels, new cbegrkeine, new cscreentexturpol (new cjpegdatei ("/root/quell-cc/media/Polkarten/0400 stereo hellblau.jpg"), real (0.206), 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugels, new cbegrkeine, new cscreentexturpol (new cjpegdatei ("/root/quell-cc/media/Polkarten/2048 stereo 00.jpg"), real (0.5), 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugels, new cbegrkeine, new cscreentexturpol (new cjpegdatei ("/root/quell-cc/media/Polkarten/2048 stereo Nordpol.jpg"), real (0.5), 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugels, new cbegrkeine, new cscreentexturpol (new cjpegdatei ("/root/quell-cc/media/Polkarten/4000 stereo 00.jpg"), real (1)/PI, 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugels, new cbegrkeine, new cscreentexturpol (new cjpegdatei ("/root/quell-cc/media/Polkarten/4000 stereo Berlin kontrast.jpg"), real (1)/PI, 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugels, new cbegrkeine, new cscreentexturpol (new cjpegdatei ("/root/quell-cc/media/Polkarten/4000 stereo nordpol.jpg"), real (1)/PI, 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugels, new cbegrkeine, new cscreentexturpol (new cjpegdatei ("/root/quell-cc/media/Polkarten/5000 stereo Nordpol kontrast.jpg"), real (0.1275), 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugels, new cbegrkeine, new cscreentexturpol (new cjpegdatei ("/root/quell-cc/media/Polkarten/5000 stereo Nordpol physisch.jpg"), real (0.1275), 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugels, new cbegrkeine, new cscreentexturpol (new cjpegdatei ("/root/quell-cc/media/Polkarten/5000 stereo Nordpol weltraum.jpg"), real (0.1275), 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugels, new cbegrkeine, new cscreentexturpol (new cjpegdatei ("/root/quell-cc/media/Polkarten/9999 stereo Südpol Riemann.jpg"), real (0.02545), 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugel, new cbegrkeine, new cscreentextur22s (new cjpegdatei ("/root/quell-cc/media/Polkarten/0339 stereo 00 rot.jpg"), real (1)/PI, 0, new cjpegdatei ("/root/quell-cc/media/Polkarten/0339 stereo 180 rot.jpg"), real (1)/PI, 0), kstobj, klobj);

  // Polkarten flächentreu
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelf, new cbegrkeine, new cscreentexturpol (new cjpegdatei ("/root/quell-cc/media/Polkarten/0800 lamb nordpol sw.jpg"), real (0.694), 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelf, new cbegrkeine, new cscreentexturpol (new cjpegdatei ("/root/quell-cc/media/Polkarten/0800 lamb Südpol sw.jpg"), real (0.694), 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelf, new cbegrkeine, new cscreentexturpol (new cjpegdatei ("/root/quell-cc/media/Polkarten/1024 lamb 00 physisch.jpg"), real (0.5), 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelf, new cbegrkeine, new cscreentexturpol (new cjpegdatei ("/root/quell-cc/media/Polkarten/1024 lamb nordpol.jpg"), real (0.5), 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelf, new cbegrkeine, new cscreentexturpol (new cjpegdatei ("/root/quell-cc/media/Polkarten/1024 lamb schräg physisch.jpg"), real (0.5), 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelf, new cbegrkeine, new cscreentexturpol (new cjpegdatei ("/root/quell-cc/media/Polkarten/2600 lamb 00 kontrast.jpg"), real (0.49), 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelf, new cbegrkeine, new cscreentexturpol (new cjpegdatei ("/root/quell-cc/media/Polkarten/2600 lamb nordpol kontrast.jpg"), real (0.49), 0), kstobj, klobj);
  ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelf, new cbegrkeine, new cscreentexturpol (new cjpegdatei ("/root/quell-cc/media/Polkarten/2600 lamb schräg kontrast.jpg"), real (0.49), 0), kstobj, klobj);

  // Polkarten mittenabstandstreu
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelm, new cbegrkeine, new cscreentexturpol (new cjpegdatei ("/root/quell-cc/media/Polkarten/1024 mitten Berlin.jpg"), real (1)/PI, 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelm, new cbegrkeine, new cscreentexturpol (new cjpegdatei ("/root/quell-cc/media/Polkarten/4096 mitten 00.jpg"), real (1)/PI, 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelm, new cbegrkeine, new cscreentexturpol (new cjpegdatei ("/root/quell-cc/media/Polkarten/4096 mitten Canberra.jpg"), real (1)/PI, 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelm, new cbegrkeine, new cscreentexturpol (new cjpegdatei ("/root/quell-cc/media/Polkarten/4096 mitten Südpol.jpg"), real (1)/PI, 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelm, new cbegrkeine, new cscreentexturpol (new cjpegdatei ("/root/quell-cc/media/Polkarten/4096 mitten Nordpol.jpg"), real (1)/PI, 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelm, new cbegrkeine, new cscreentextur2 (new cjpegdatei ("/root/quell-cc/media/Polkarten/4096 mitten Nordpol.jpg"), real (1)/PI, 0, new cjpegdatei ("/root/quell-cc/media/Polkarten/4096 mitten Südpol.jpg"), real (1)/PI, 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugel2, new cbegrkeine, new cscreentextur22 (new cjpegdatei ("/root/quell-cc/media/Polkarten/4096 mitten Nordpol.jpg"), real (1)/PI, 0, new cjpegdatei ("/root/quell-cc/media/Polkarten/4096 mitten Südpol.jpg"), real (1)/PI, 0), kstobj, klobj);

  // Körper addieren
  pwelt.addkoerper (koerper1);

  // Augposition setzen
  pwelt.setzeposition (kstauge);
  pwelt.setzelage (klauge);

  // Hintergrundfarbe setzen
  pwelt.himmelfarbe= cvektor3 (22, 22, 12);
  }

void addtorus (cwelt& pwelt)
  {
  // Körperstandpunkte
  cvektor3 kstobj (0,0,0);
  cvektor3 kstauge (500,0,0);

  // Körperlagen
  cbasis3 klobj (cvektor3 (100,0,0), cvektor3 (0,100,0), cvektor3 (0,0,-100));
  cbasis3 klauge (cvektor3 (0,1,0), cvektor3 (0,0,-1), cvektor3 (-1,0,0));

  //cbasis3 kl1 (cvektor3 (100,0,0), cvektor3 (0,0,400), cvektor3 (0,25,0));          // flacher Ellipsentorus

  // Texturen
  //cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (0,255,0), 80/PI, 10/PI);
  //cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (0,255,0), 800/PI, 10/PI);
  //cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (0,255,0), PI/60, PI/15);
  //cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (0,255,0), PI/80, PI/10);

  // Körper
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorusu, new cbegrkeine, textur1, kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.0125)), new cparatorusu, new cbegrkeine, textur1, kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.25)), new cparatorusu, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Bilder/catchick600.jpg"), real (8/PI), real (2/PI)), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorusu, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/sechseck1024.jpg"), real (8/PI), real (1/PI)), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorusu, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/wabe512.jpg"), real (16/PI), real (2/PI)), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorusu, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/wabe-rs512.jpg"), real (16/PI), real (2/PI)), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorusu, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/Bergsee.jpg"), real (16/PI), real (2/PI)), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorusu, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/Meer.jpg"), real (16/PI), real (2/PI)), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorusu, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/Palmen.jpg"), real (16/PI), real (2/PI)), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorusu, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/Steine.jpg"), real (16/PI), real (2/PI)), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorusu, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/Steinmauer.jpg"), real (16/PI), real (2/PI)), kstobj, klobj);
  ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorusu, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/Steinstrand.jpg"), real (16/PI), real (2/PI)), kstobj, klobj);

  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.5)), new cparatoruss, new cbegrkeine, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Plattkarten/2044 platt-z physisch.jpg"), real (1/PI), real (0)), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.5)), new cparatoruss, new cbegrkeine, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Plattkarten/2044 platt-zts physisch.jpg"), real (1/PI), real (0)), kstobj, klobj);

  // Körper addieren
  pwelt.addkoerper (koerper1);

  // Augposition setzen
  pwelt.setzeposition (kstauge);
  pwelt.setzelage (klauge);

  // Hintergrundfarbe setzen
  pwelt.himmelfarbe= cvektor3 (30, 75, 90);
  }

void addtorusoktaeder (cwelt& pwelt)
  {
  // Körperstandpunkte
  cvektor3 kstobj (0,0,0);

  // Körperlagen
  cbasis3 kl1 (cvektor3 (100,0,0), cvektor3 (0,0,100), cvektor3 (0,100,0));
  cbasis3 kl2 (cvektor3 (0,0,100), cvektor3 (0,100,0), cvektor3 (100,0,0));
  cbasis3 kl3 (cvektor3 (0,100,0), cvektor3 (100,0,0), cvektor3 (0,0,100));
  //cbasis3 kl1 (cvektor3 (100,0,0), cvektor3 (0,0,400), cvektor3 (0,25,0));          // flacher Ellipsentorus

  // Texturen
  cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (0,255,0), 80/PI, 10/PI);
  cschachfeld* textur2= new cschachfeld (cvektor3 (255,0,255), cvektor3 (255,255,0), 80/PI, 10/PI);
  cschachfeld* textur3= new cschachfeld (cvektor3 (255,127,0), cvektor3 (0,255,255), 80/PI, 10/PI);
  //cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (0,255,0), 800/PI, 20/PI);
  //cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (0,255,0), PI/60, PI/15);
  //cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (0,255,0), PI/80, PI/10);

  // Körper
  ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatoruss, new cbegrkeine, textur1, kstobj, kl1);
  ckoerper* koerper2= new ckoerper (new cstorus (real (0.125)), new cparatoruss, new cbegrkeine, textur2, kstobj, kl2);
  ckoerper* koerper3= new ckoerper (new cstorus (real (0.125)), new cparatoruss, new cbegrkeine, textur3, kstobj, kl3);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.0125)), new cparatorus, new cbegrkeine, textur1, kstobj, kl1);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.25)), new cparatorus, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Bilder/catchick600.jpg"), real (8/PI), real (2/PI)), kstobj, kl1);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorus, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/sechseck1024.jpg"), real (8/PI), real (1/PI)), kstobj, kl1);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorus, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/wabe512.jpg"), real (16/PI), real (2/PI)), kstobj, kl1);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorus, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/wabe-rs512.jpg"), real (16/PI), real (2/PI)), kstobj, kl1);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorus, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/Bergsee.jpg"), real (16/PI), real (2/PI)), kstobj, kl1);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorus, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/Meer.jpg"), real (16/PI), real (2/PI)), kstobj, kl1);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorus, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/Palmen.jpg"), real (16/PI), real (2/PI)), kstobj, kl1);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorus, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/Steine.jpg"), real (16/PI), real (2/PI)), kstobj, kl1);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorus, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/Steinmauer.jpg"), real (16/PI), real (2/PI)), kstobj, kl1);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorus, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/Steinstrand.jpg"), real (16/PI), real (2/PI)), kstobj, kl1);

  //pwelt.himmelfarbe= cvektor3 (30,75,90);

  // Körper addieren
  pwelt.addkoerper (koerper1);
  pwelt.addkoerper (koerper2);
  pwelt.addkoerper (koerper3);

  // Augposition setzen
  pwelt.setzeposition (cvektor3 (0, 100, -300));
  }

void fliege ()
  {
  cwelt* welt= new cwelt (cvektor3 (0), cbasis3 (1));  // Standpunkt, Lage

  //addebene (*welt);
  //addkoord (*welt);
  //addebenen90 (*welt);
  //addzylinder (*welt);
  //addkugel (*welt);
  addtorus (*welt);

  //cflugsimu flugsimu (welt, new cxkeyboard, new cxscreen ("xray", 800, 450), 450);                    // cxscreen: Fehlerpixel mit xraythread

  //cflugsimu flugsimu (welt, new cxkeyboard, new cximagescreen ("xray", 320, 200), 320);
  //cflugsimu flugsimu (welt, new cxkeyboard, new cximagescreen ("xray", 512, 256), 512);
  //cflugsimu flugsimu (welt, new cxkeyboard, new cximagescreen ("xray", 1024, 512), 1024);
  //cflugsimu flugsimu (welt, new cxkeyboard, new cximagescreen ("xray", 675, 500), 750);
  cflugsimu flugsimu (welt, new cxkeyboard, new cximagescreen ("xray", 1350, 1000), 1350);
  //cflugsimu flugsimu (welt, new cxkeyboard, new cximagescreen ("xray", 1920, 1080), 1920);

  //cflugsimu flugsimu (welt, new cnckeyboard, new cfbscreen ("xray", 512, 256), 512);
  //cflugsimu flugsimu (welt, new cnckeyboard, new cfbscreen ("xray", 1024, 512), 1024);
  //cflugsimu flugsimu (welt, new cnckeyboard, new cfbscreen ("xray", 1920, 960), 1920);
  //cflugsimu flugsimu (welt, new cnckeyboard, new cfbscreen ("xray", 1920, 1080), 1920);

  flugsimu.setframerate (50);
  flugsimu.threadanz= 12;
  flugsimu.bewstep= real (2);
  flugsimu.drehstep= real (0.0125);

  //flugsimu.fliege ();
  //flugsimu.fliegek ();
  //flugsimu.fliegetakt ();
  flugsimu.fliegethread ();   // geht nicht mit cxscreen
  }

int main ()
  {
  fliege ();
  return 0;
  }
