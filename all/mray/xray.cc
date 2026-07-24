#include "../../cc/class/game.h"
#include "../../cc/screen/allscr.h"
#include "../../xwindow/keyboard/xkbd.h"
#include "../../framebuffer/keyboard/nckbd.h"

void addmulti (cwelt& pwelt)
  {
  // Körperstandpunkte
  cvektor3 kst1 (0,0,0);

  // Körperlagen
  cbasis3 kl1 (cvektor3 (10,0,0), cvektor3 (0,10,0), cvektor3 (0,0,10));
  cbasis3 kl2 (cvektor3 (10,0,0), cvektor3 (0,0,10), cvektor3 (0,100,0));

  // Texturen
  //cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (0,255,0), 1, 1);
  //cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (0,255,0), 20/PI, 20/PI);
  //cschachfeld* textur1= new cschachfeld (cvektor3 (255,127,0), cvektor3 (0,255,255), 1, 1);
  //cschachfeldf* textur1= new cschachfeldf (cvektor3 (255,127,0), cvektor3 (0,255,255), 1, 1);

  // Begrenzungen
  //cbegrkreis* begr1= new cbegrkreis (-1, 1, -1, 1);
  //cbegrrechteck* begr1= new cbegrrechteck (-1, 1, -1, 1);

  // Körper
  //ckoerper* koerper1= new ckoerper (new csebene, new cparaebenew, new cbegrkeine, textur1, kst1, kl1);
  //ckoerper* koerper1= new ckoerper (new csebene, new cparaebenepol, new cbegrkeine, textur1, kst1, kl1);
  //ckoerper* koerper1= new ckoerper (new csebene, new cparaebenepolw, new cbegrkeine, textur1, kst1, kl1);
  //ckoerper* koerper1= new ckoerper (new cshyper (0), new cparakegelw, new cbegrkeine, textur1, kst1, kl1);
  //ckoerper* koerper1= new ckoerper (new cshyper (1), new cparaebenepol, new cbegrkeine, textur1, kst1, kl1);
  //ckoerper* koerper1= new ckoerper (new csrpara, new cparaebenepol, new cbegrkeine, textur1, kst1, kl1);
  //ckoerper* koerper1= new ckoerper (new csrpara, new cparaebenepol, begkreis1, textur1, kst1, kl1);
  //ckoerper* koerper1= new ckoerper (new cshpara, new cparaebenepol, new cbegrkeine, textur1, kst1, kl1);
  //ckoerper* koerper1= new ckoerper (new cshpara, new cparaebenepol, begkreis1, textur1, kst1, kl1);

  // Bilder
  ckoerper* koerper1= new ckoerper (new csebene, new cparaebenew, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Bilder/catchick600.jpg"), 2/PI, 2/PI), kst1, kl1);
  //ckoerper* koerper1= new ckoerper (new csebene, new cparaebenepolw, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Bilder/catchick600.jpg"), 5/PI, 5/PI), kst1, kl1);
  //ckoerper* koerper1= new ckoerper (new cshyper (0), new cparakegelw, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Bilder/catchick600.jpg"), 5/PI, 5/PI), kst1, kl1);

  // Bilder
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugel_gnom, new cbegrkeine, textur1, kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugel_mercator_z, new cbegrkeine, textur2, kstobj, kl1);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugel_mercator_z, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Bilder/catchick600.jpg"), 2/PI, 2/PI), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugel_mercator_z, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Bilder/catchick600.jpg"), 12/PI, 12/PI), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugel_mercator_z, new cbegrkeine, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Bilder/catchick600.jpg"), 1/PI, 0), kstobj, klobj);

  // experimentelle Texturiereungen
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugelm2, new cbegrkeine, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Texturen/1080 linien.jpg"), real (0.3183), 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugel_stereo_xyz, new cbegrkeine, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Texturen/1080 quadrat.jpg"), real (0.1), 0), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cskugel, new cparakugel_stereo_xyz, new cbegrkeine, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Texturen/1080 linien.jpg"), real (0.1), 0), kstobj, klobj);

  // Körper addieren
  pwelt.addkoerper (koerper1);

  // Augposition setzen
  pwelt.setzeposition (cvektor3 (0, 0, -100));
  pwelt.setzelage (cbasis3 (cvektor3 (1,0,0), cvektor3 (0,1,0), cvektor3 (0,0,1)));
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
  pwelt.addkoerper (new ckoerper (new cskugel, new cparakugel_mercator_z, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Bilder/catchick600.jpg"), 10, 10), kst2, kl2));
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
  //cschachfeld* textur2= new cschachfeld (cvektor3 (255,255,255), cvektor3 (0,0,0), 12/PI, 12/PI);
  //cschachfeld* textur3= new cschachfeld (cvektor3 (255,0,255), cvektor3 (0,255,0), 12/PI, 12/PI);

  // Körper addieren
  //pwelt.addkoerper (new ckoerper (new csebene, new cparawebene, ell1, textur1, kst1, kl1));
  //pwelt.addkoerper (new ckoerper (new cskugel, new cparakugel_mercator_xyz, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Bilder/catchick600.jpg"), 10, 10), kst2, kl1));
  pwelt.addkoerper (new ckoerper (new cszylinder, new cparazylinderw, new (cbegrkeine), new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Bilder/catchick600.jpg"), 2/PI, 2/PI), kst2, kl1));

  pwelt.verschiebeauge (cvektor3 (0, 500, -1000));
  }

void adderdkarte (cwelt& pwelt)
  {

//************************************************************ Kugel *******************************************************************************
/*
  // ---------------------------------------------------------------- Kugelparametrisierung der Texturen (Karten) ---------------------------------
  //clpara* para1= new cparakugel_platt_z;
  //clpara* para1= new cparakugel_mercator_z;
  //clpara* para1= new cparakugel_zlamb;

  //clpara* para1= new cparakugel_gnom_z;
  //clpara* para1= new cparakugel_stereo_z;
  clpara* para1= new cparakugel_stereo_z (51, 7);
  //clpara* para1= new cparakugel_mitten_z;
  //clpara* para1= new cparakugel_lamb_z;

  // ---------------------------------------------------------------- Körpereigenschaften --------------------------------------------------------
  // Begrenzung
  clbegr* begr1= new cbegrkeine;
  //clbegr* begr1= new cbegrrechteck (0, 1, 0, 1);    // für (6732 Mercator-blz Straßennetz.jpg)

  // Kugel Standort, Lage
  cvektor3 st1 (0,0,0);
  cvektor3 stauge (500,0,0);
  cbasis3 lag1 (cvektor3 (100,0,0), cvektor3 (0,100,0), cvektor3 (0,0,100));
  cbasis3 lagauge (cvektor3 (0,1,0), cvektor3 (0,0,1), cvektor3 (-1,0,0));
  clschnitt* schnitt1= new cskugel;
//*/

//************************************************************ Ebenenprojektionen *****************************************************************
//*
  // ---------------------------------------------------------------- Kugelparametrisierung der Texturen (Karten) ---------------------------------
  clpara* parakugel= new cparakugel_platt_xyz;
  //clpara* parakugel= new cparakugel_mercator_z;
  //clpara* parakugel= new cparakugel_zlamb;
  //clpara* parakugel= new cparakugel_gnom;
  //clpara* parakugel= new cparakugel_stereo_z (51, 7);
  //clpara* parakugel= new cparakugel_mitten_xyz;
  //clpara* parakugel= new cparakugel_lamb_xyz;

  // ---------------------------------------------------------------- Projektionen in die Ebene ---------------------------------------------------
  // Polarprojektionen zwischenständig
  //clpara* para1= new cparaebene_gnom_kugel (parakugel, real (52.5), real (13.5));
  //clpara* para1= new cparaebene_stereo_kugel (parakugel, 52.5, 13.5);
  //clpara* para1= new cparaebene_mitten_kugel (parakugel, real (52.5), real (13.5));
  //clpara* para1= new cparaebene_lamb_kugel (parakugel, real (52.5), real (13.5));

  // Zylinderprojektionen zwischenständig
  //clpara* para1= new cparaebene_platt_kugel (parakugel, real (52.5), real (13.5), real (0));
  //clpara* para1= new cparaebene_mercator_kugel (parakugel, real (52.5), real (13.5), real (0));
  //clpara* para1= new cparaebene_zlamb_kugel (parakugel, real (52.5), real (13.5), real (0));

  // Zylinderprojektionen normal
  //clpara* para1= new cparaebene_platt_kugel (parakugel, 0, 0, 0);
  clpara* para1= new cparaebene_mercator_kugel (parakugel, 0, 0, 0);

  // ---------------------------------------------------------------- Körpereigenschaften --------------------------------------------------------
  // Begrenzung
  clbegr* begr1= new cbegrkeine;
  //clbegr* begr1= new cbegrrechteck (0, 1, 0, 1);    // für (6732 Mercator-blz Straßennetz.jpg)

  // Kartenprojektion Standort, Lage
  cvektor3 st1 (0,0,0);
  cvektor3 stauge (0,0,-500);
  cbasis3 lag1 (cvektor3 (100,0,0), cvektor3 (0,100,0), cvektor3 (0,0,100));
  cbasis3 lagauge (cvektor3 (1,0,0), cvektor3 (0,1,0), cvektor3 (0,0,1));
  clschnitt* schnitt1= new csebene;
//*/

  // ---------------------------------------------------------------- Texturen (Karten) ----------------------------------------------------------
  // Plattkarten
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Zylkarten platt/0400 platt hellblau.jpg"), real (0.3183), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Zylkarten platt/0648 platt Mondkarte.jpg"), real (0.3183), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Zylkarten platt/1000 platt dunkelblau.jpg"), real (0.3183), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Zylkarten platt/1436 platt-z politisch.jpg"), real (0.3183), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Zylkarten platt/1466 platt 35 045 politisch.jpg"), real (0.3183), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Zylkarten platt/2044 platt-z hellblau.jpg"), real (0.3183), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Zylkarten platt/2048 platt-v dunkelblau.jpg"), real (0.3183), 0), st1, lag1);
  ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Zylkarten platt/4000 platt kontrast.jpg"), real (0.3183), 0), st1, lag1);

  // Mercatorkarten
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Zylkarten Mercator/0262 Mercator-blza physisch.jpg"), real (0.3183), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Zylkarten Mercator/0400 Mercator quer.jpg"), real (0.3183), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Zylkarten Mercator/0400 Mercator schief.jpg"), real (0.3183), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Zylkarten Mercator/0576 Mercator Gradnetz.jpg"), real (0.3183), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Zylkarten Mercator/0677 Mercator-blza monochrom.jpg"), real (0.3183), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Zylkarten Mercator/1008 Mercator-blza physisch mittelblau.jpg"), real (0.3183), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Zylkarten Mercator/1200 Mercator-bv politisch rand.jpg"), real (0.3183), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Zylkarten Mercator/2054 Mercator-blza physisch hellblau.jpg"), real (0.3183), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Zylkarten Mercator/2400 Mercator-blza physisch dunkelblau.jpg"), real (0.3183), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Zylkarten Mercator/2768 Mercator-bl85 braun.jpg"), real (0.3183), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Zylkarten Mercator/3821 Mercator-blz politisch.jpg"), real (0.3183), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Zylkarten Mercator/4000 Mercator 45 135 kontrast.jpg"), real (0.3183), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Zylkarten Mercator/4000 Mercator kontrast.jpg"), real (0.3183), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Zylkarten Mercator/6732 Mercator-blz Straßennetz.jpg"), real (0.3183), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Zylkarten Mercator/7682 Mercator-blz politisch.jpg"), real (0.3183), 0), st1, lag1);

  // Zylinderkarten flächentreu (zlamb)
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Zylkarten lamb/3999 lamb kontrast.jpg"), real (0.3183), 0), st1, lag1);

  // Polkarten gnomonisch
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten gnom/0400 gnom 90 000 hellblau.jpg"), real (0.3183), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten gnom/3000 gnom 90 000 weltall.jpg"), real (0.3183), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten gnom/4000 gnom 00 000 kontrast.jpg"), real (0.3183), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten gnom/4000 gnom 51 007 kontrast.jpg"), real (0.3183), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten gnom/4000 gnom 90 000 kontrast.jpg"), real (0.3183), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten gnom/5000 gnom 90 000 graublau.jpg"), real (0.3183), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten gnom/5000 gnom 90 000 kontrast.jpg"), real (0.3183), 0), st1, lag1);

  // Polkarten flächentreu
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten lamb/0800 lamb 90 000 0.9812 strich.jpg"), real (0.9812), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten lamb/0800 lamb-90 000 0.9812 strich.jpg"), real (0.9812), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten lamb/1024 lamb 00 000 0.7070 dunkelblau.jpg"), real (0.7070), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten lamb/1024 lamb-47 180 0.7090 dunkelblau.jpg"), real (0.7090), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten lamb/1024 lamb 90 000 0.7090 dunkelblau.jpg"), real (0.7090), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten lamb/2058 lamb 00 000 0.7023 blaugrau.jpg"), real (0.7023), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten lamb/2600 lamb 00 000 0.6930 kontrast.jpg"), real (0.6930), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten lamb/2600 lamb 51 007 0.6930 kontrast.jpg"), real (0.6930), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten lamb/2600 lamb 90 000 0.6930 kontrast.jpg"), real (0.6930), 0), st1, lag1);

  // Polkarten stereografisch
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten stereo/0339 stereo 00 000 0.2690 rot.jpg"), real (0.269), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten stereo/0339 stereo 00 180 0.2690 rot.jpg"), real (0.269), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten stereo/0400 stereo-90 000 0.4124 hellblau.jpg"), real (0.4124), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten stereo/1003 stereo 90 000 0.2981 rechteck.jpg"), real (0.2981), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten stereo/2048 stereo 00 000 1.0000 dunkelblau.jpg"), real (1.0000), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten stereo/2048 stereo 90 000 1.0000 dunkelblau.jpg"), real (1.0000), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten stereo/4000 stereo 00 000 0.6372 kontrast.jpg"), real (0.6372), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten stereo/4000 stereo 00 000 0.3187 kontrast.jpg"), real (0.3187), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten stereo/4000 stereo 51 007 0.6372 kontrast.jpg"), real (0.6372), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten stereo/4000 stereo 51 007 0.3187 kontrast.jpg"), real (0.3187), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten stereo/4000 stereo 90 000 0.6372 kontrast.jpg"), real (0.6372), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten stereo/4000 stereo 90 000 0.3187 kontrast.jpg"), real (0.3187), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten stereo/5000 stereo 90 000 0.2550 graublau.jpg"), real (0.2550), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten stereo/5000 stereo 90 000 0.2550 kontrast.jpg"), real (0.2550), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten stereo/5000 stereo 90 000 0.2550 weltraum.jpg"), real (0.2550), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten stereo/9999 stereo-90 000 0.0509 kontrast.jpg"), real (0.0509), 0), st1, lag1);

  // Polkarten mittenabstandstreu
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten mitten/1024 mitten 52 013 dunkelblau.jpg"), real (0.3183), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten mitten/4000 mitten 00 000 kontrast.jpg"), real (0.3185), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten mitten/4000 mitten 51 007 kontrast.jpg"), real (0.3185), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten mitten/4000 mitten 90 000 kontrast.jpg"), real (0.3185), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten mitten/4096 mitten 00 000 dunkelblau.jpg"), real (0.3183), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten mitten/4096 mitten 90 000 dunkelblau.jpg"), real (0.3183), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten mitten/4096 mitten-35 149 dunkelblau.jpg"), real (0.3183), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentexturp (new cjpegdatei ("/root/quell-cc/media/Polkarten mitten/4096 mitten-90 000 dunkelblau.jpg"), real (0.3183), 0), st1, lag1);

  // Polkarten mittenabstandstreu 2 Karten (mitten_xyz, platt_xyz)
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentextur2pm (new cjpegdatei ("/root/quell-cc/media/Polkarten mitten/4096 mitten 90 000 dunkelblau.jpg"), real (0.3183), 0, new cjpegdatei ("/root/quell-cc/media/Polkarten mitten/4096 mitten-90 000 dunkelblau.jpg"), real (0.3183), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentextur2zm (new cjpegdatei ("/root/quell-cc/media/Polkarten mitten/4096 mitten 90 000 dunkelblau.jpg"), real (0.3183), 0, new cjpegdatei ("/root/quell-cc/media/Polkarten mitten/4096 mitten-90 000 dunkelblau.jpg"), real (0.3183), 0), st1, lag1);

  // Polkarten stereografisch 2 Karten
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentextur2zs (new cjpegdatei ("/root/quell-cc/media/Polkarten stereo/0339 stereo 00 000 0.2690 rot.jpg"), real (0.269), 0, new cjpegdatei ("/root/quell-cc/media/Polkarten stereo/0339 stereo 00 180 0.2690 rot.jpg"), real (0.269), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentextur2zs (new cjpegdatei ("/root/quell-cc/media/Polkarten stereo/5000 stereo 90 000 0.2550 kontrast.jpg"), real (0.255), 0, new cjpegdatei ("/root/quell-cc/media/Polkarten stereo/9999 stereo-90 000 0.0509 kontrast.jpg"), real (0.0509), 0), st1, lag1);
  //ckoerper* koerper1= new ckoerper (schnitt1, para1, begr1, new cscreentextur2zs (new cjpegdatei ("/root/quell-cc/media/Polkarten stereo/4000 stereo 90 000 0.6372 kontrast.jpg"), real (0.6366), 0, new cjpegdatei ("/root/quell-cc/media/Polkarten stereo/9999 stereo-90 000 0.0509 kontrast.jpg"), real (0.0509), 0), st1, lag1);

  // Körper addieren
  pwelt.addkoerper (koerper1);

  // Augposition setzen
  pwelt.setzeposition (stauge);
  pwelt.setzelage (lagauge);

  // Hintergrundfarbe setzen
  pwelt.himmelfarbe= cvektor3 (0, 0, 50);
  }

void adderdemond (cwelt& pwelt)
  {
  // Daten Himmelskörper
  real re= 6371;
  real rm= real (1737.4);
  real em= 384400;

  //real re= 100;
  //real rm= 100;
  //real em= real (8108.4);

  // Körperstandpunkte
  cvektor3 kstobj (0,0,0);
  cvektor3 kstobj2 (-em,0,0);
  //cvektor3 kstauge (20000,0,0);
  cvektor3 kstauge (6371 + 35786,0,0);                                // geostationäre Umlaufbahn

  // Körperlagen
  cbasis3 klobj (cvektor3 (re,0,0), cvektor3 (0,re,0), cvektor3 (0,0,-re));
  cbasis3 klobj2 (cvektor3 (rm,0,0), cvektor3 (0,rm,0), cvektor3 (0,0,-rm));
  cbasis3 klauge (cvektor3 (0,1,0), cvektor3 (0,0,-1), cvektor3 (-1,0,0));

  ckoerper* koerper1= new ckoerper (new cskugel, new cparakugel_platt_xyz, new cbegrkeine, new cscreentextur2zm (new cjpegdatei ("/root/quell-cc/media/Polkarten mitten/4096 mitten 90 000 dunkelblau.jpg"), real (0.3183), 0, new cjpegdatei ("/root/quell-cc/media/Polkarten mitten/4096 mitten-90 000 dunkelblau.jpg"), real (0.3183), 0), kstobj, klobj);
  ckoerper* koerper2= new ckoerper (new cskugel, new cparakugel_platt_xyz, new cbegrkeine, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Zylkarten platt/0648 platt Mondkarte.jpg"), real (0.3183), 0), kstobj2, klobj2);

  // Körper addieren
  pwelt.addkoerper (koerper1);
  pwelt.addkoerper (koerper2);

  // Augposition setzen
  pwelt.setzeposition (kstauge);
  pwelt.setzelage (klauge);

  // Hintergrundfarbe setzen
  pwelt.himmelfarbe= cvektor3 (22, 22, 12);
  }

void addebzyl (cwelt& pwelt)
  {
  // Körperstandpunkte
  cvektor3 kstobj (0,0,0);
  cvektor3 kstauge (500,0,0);

  // Körperlagen
  cbasis3 klobj (cvektor3 (100,0,0), cvektor3 (0,100,0), cvektor3 (0,0,-100));
  cbasis3 klauge (cvektor3 (0,1,0), cvektor3 (0,0,-1), cvektor3 (-1,0,0));

  //cbasis3 kl1 (cvektor3 (100,0,0), cvektor3 (0,0,400), cvektor3 (0,25,0));          // flacher Ellipsentorus

  // Texturen
  cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (0,255,0), 20/PI, 20/PI);
  //cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (0,255,0), 800/PI, 10/PI);
  //cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (0,255,0), PI/60, PI/15);
  //cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (0,255,0), PI/80, PI/10);

  // Begrenzungen
  //cbegrrechteck* reck1= new cbegrrechteck (-4, 4, real (-0.3), real (1));

  // Körper
  ckoerper* koerper1= new ckoerper (new csebzyl, new cparaebenepolw, new cbegrkeine, textur1, kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new csebzyl, new cparaebenepolw, reck1, textur1, kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new csebzyl, new cparaebenepolw, reck1, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Bilder/catchick600.jpg"), 6/PI, 6/PI), kstobj, klobj);
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
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorusu, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/Steinstrand.jpg"), real (16/PI), real (2/PI)), kstobj, klobj);

  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.5)), new cparatoruss, new cbegrkeine, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Zylkarten platt/2044 platt-z physisch.jpg"), real (1/PI), real (0)), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.5)), new cparatoruss, new cbegrkeine, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Zylkarten platt/2044 platt-zts physisch.jpg"), real (1/PI), real (0)), kstobj, klobj);

  // Körper addieren
  pwelt.addkoerper (koerper1);

  // Augposition setzen
  pwelt.setzeposition (kstauge);
  pwelt.setzelage (klauge);

  // Hintergrundfarbe setzen
  //pwelt.himmelfarbe= cvektor3 (30, 75, 90);
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
  //cschachfeld* textur2= new cschachfeld (cvektor3 (255,0,0), cvektor3 (0,255,0), 800/PI, 10/PI);
  //cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (0,255,0), PI/60, PI/15);
  //cschachfeld* textur1= new cschachfeld (cvektor3 (255,0,0), cvektor3 (0,255,0), PI/80, PI/10);

  // Körper
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorusu, new cbegrkeine, textur1, kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.0125)), new cparatorusu, new cbegrkeine, textur2, kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorusu, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/sechseck1024.jpg"), real (8/PI), real (1/PI)), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorusu, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/wabe512.jpg"), real (16/PI), real (2/PI)), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorusu, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/wabe-rs512.jpg"), real (16/PI), real (2/PI)), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorusu, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/Steinmauer.jpg"), real (16/PI), real (2/PI)), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorusu, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/Steine.jpg"), real (16/PI), real (2/PI)), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.25)), new cparatorusrl, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Bilder/catchick600.jpg"), real (8/PI), real (2/PI)), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorusrl, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/Bergsee.jpg"), real (8/PI), real (1/PI)), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorusrl, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/Meer.jpg"), real (16/PI), real (2/PI)), kstobj, klobj);
  ///ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorusrl, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/Meer.jpg"), real (8/PI), real (1/PI)), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorusrl, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/Palmen.jpg"), real (16/PI), real (2/PI)), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorusrl, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/Steinstrand.jpg"), real (16/PI), real (2/PI)), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorusrl, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/Steinstrand.jpg"), real (8/PI), real (1/PI)), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorusrl, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/mallorca1.jpg"), real (16/PI), real (2/PI)), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorusrl, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/mallorca2.jpg"), real (16/PI), real (2/PI)), kstobj, klobj);
  ckoerper* koerper1= new ckoerper (new cstorus (real (0.125)), new cparatorusrl, new cbegrkeine, new cscreentextur (new cjpegdatei ("/root/quell-cc/media/Texturen/mallorca3.jpg"), real (16/PI), real (2/PI)), kstobj, klobj);

  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.5)), new cparatoruss, new cbegrkeine, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Zylkarten platt/2044 platt-z physisch.jpg"), real (1/PI), real (0)), kstobj, klobj);
  //ckoerper* koerper1= new ckoerper (new cstorus (real (0.5)), new cparatoruss, new cbegrkeine, new cscreentexturz (new cjpegdatei ("/root/quell-cc/media/Zylkarten platt/2044 platt-zts physisch.jpg"), real (1/PI), real (0)), kstobj, klobj);

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

  //addmulti (*welt);
  //addkoord (*welt);
  //addebenen90 (*welt);
  //addzylinder (*welt);
  adderdkarte (*welt);
  //adderdemond (*welt);
  //addebzyl (*welt);
  //addtorus (*welt);
  //addtorusoktaeder (*welt);

  //cflugsimu flugsimu (welt, new cxkeyboard, new cxscreen ("xray", 800, 450), 800);                     // cxscreen: Fehlerpixel mit xraythread

  //cflugsimu flugsimu (welt, new cxkeyboard, new cximagescreen ("xray", 512, 256), 512);                // weißer Balken rechts oben
  //cflugsimu flugsimu (welt, new cxkeyboard, new cximagescreen ("xray", 1024, 512), 1024);              // weißer Balken rechts oben
  //cflugsimu flugsimu (welt, new cxkeyboard, new cximagescreen ("xray", 768, 576), 768);                // weißer Balken rechts oben
  //cflugsimu flugsimu (welt, new cxkeyboard, new cximagescreen ("xray", 768, 512), 768);                // weißer Balken rechts oben
  //cflugsimu flugsimu (welt, new cxkeyboard, new cximagescreen ("xray", 1280, 768), 1280);               // Fehler unterer Rand

  //cflugsimu flugsimu (welt, new cxkeyboard, new cximagescreen ("xray", 320, 200), 320);
  //cflugsimu flugsimu (welt, new cxkeyboard, new cximagescreen ("xray", 900, 600), 900);
  cflugsimu flugsimu (welt, new cxkeyboard, new cximagescreen ("xray", 1350, 1000), 1350);
  //cflugsimu flugsimu (welt, new cxkeyboard, new cximagescreen ("xray", 1920, 1080), 1920);

  //cflugsimu flugsimu (welt, new cnckeyboard, new cfbscreen ("xray", 512, 256), 512);
  //cflugsimu flugsimu (welt, new cnckeyboard, new cfbscreen ("xray", 1024, 512), 1024);
  //cflugsimu flugsimu (welt, new cnckeyboard, new cfbscreen ("xray", 1920, 960), 1920);
  //cflugsimu flugsimu (welt, new cnckeyboard, new cfbscreen ("xray", 1920, 1080), 1920);

  flugsimu.setframerate (50);
  flugsimu.threadanz= 20;
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
