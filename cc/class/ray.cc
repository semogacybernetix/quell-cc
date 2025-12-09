#include "ray.h"

#include <iostream>        // die Weltdaten aus einer Datei lesen
#include <sys/times.h>     // tms, times

using namespace std;       // cout

//********************************************************* Schnittpunktberechnungsobjekte ************************************************************************************************************************************************

// ---------------------------- Ebene -----------------------------------------------
csebene::csebene ()
  {
  z= 0;
  }

void csebene::init (const cvektor3 &pov)
  {
  z= -pov.z;
  }

void csebene::berechne (const cvektor3 &prv, cschnittpunkte &psp)
  {
  real s1= z/prv.z;
  if (s1 > 0)
    psp.add (s1);
  }

// ---------------------------- Zylinder -----------------------------------------------

cszylinder::cszylinder ()
  {
  ov= cvektor3 (0, 0, 0);
  }

void cszylinder::init (const cvektor3 &pov)
  {
  ov= pov;
  c= ov.x*ov.x + ov.y*ov.y - 1;
  }

void cszylinder::berechne (const cvektor3 &prv, cschnittpunkte &psp)
  {
  real a= prv.x*prv.x + prv.y*prv.y;
  real b= -prv.x*ov.x - prv.y*ov.y;

  real d= b*b - a*c;
  if (d < 0)
    return;

  real e= sqrtr (d);
  real s1= (b + e)/a;
  real s2= (b - e)/a;

  if (s1 > 0)
    psp.add (s1);
  if (s2 > 0)
    psp.add (s2);
  }

// ---------------------------- Kugel -----------------------------------------------

cskugel::cskugel ()
  {
  ov= cvektor3 (0, 0, 0);
  }

void cskugel::init (const cvektor3 &pov)
  {
  ov= pov;
  c= ov%ov - 1;
  }

void cskugel::berechne (const cvektor3 &prv, cschnittpunkte &psp)
  {
  //real a= prv%prv;
  //real b= -(prv%ov);
  real a= prv.x*prv.x + prv.y*prv.y + prv.z*prv.z;
  real b= -prv.x*ov.x - prv.y*ov.y - prv.z*ov.z;

  real d= b*b - a*c;
  if (d < 0)
    return;

  real e= sqrtr (d);
  real s1= (b + e)/a;
  real s2= (b - e)/a;

  if (s1 > 0)
    psp.add (s1);
  if (s2 > 0)
    psp.add (s2);
  }

/*
void cskugel::berechne (const cvektor3 &prv, cschnittpunkte &psp)
  {
  ckomplexk x1, x2;

  real a= prv%prv;
  real b= prv%ov;

  quadratisch (2*b/a, c/a, x1, x2);

  if (ag (x1) < 1e-8)
    psp.add (x1.x);
  if (ag (x2) < 1e-8)
    psp.add (x2.x);
  }
*/

// ---------------------------- zweischaliges Hyperboloid, Kegel, einschaliges Hyperboloid -----------------------------------------------

cshyper::cshyper (const real &pf)                                 // dieser Wert wählt zwischen den Körpern aus (-1, 0, 1)
  {
  f= pf;
  ov= cvektor3 (0, 0, 0);
  }

void cshyper::init (const cvektor3 &pov)
  {
  ov= pov;
  c= ov.x*ov.x + ov.y*ov.y - ov.z*ov.z + f;
  }

void cshyper::berechne (const cvektor3 &prv, cschnittpunkte &psp)
  {
  real a= prv.x*prv.x + prv.y*prv.y - prv.z*prv.z;
  real b= -prv.x*ov.x - prv.y*ov.y + prv.z*ov.z;
  if (a == 0)
    {
    if (b == 0)
      return;
    real s3= c/b/2;
    if (s3 > 0)
      psp.add (s3);
    return;
    }

  real d= b*b - a*c;
  if (d < 0)
    return;

  real e= sqrtr (d);
  real s1= (b + e)/a;
  real s2= (b - e)/a;

  if (s1 > 0)
    psp.add (s1);
  if (s2 > 0)
    psp.add (s2);
  }

// ---------------------------- Rotationsparaboloid ----------------------------------------

csrpara::csrpara ()
  {
  ov= cvektor3 (0, 0, 0);
  }

void csrpara::init (const cvektor3 &pov)
  {
  ov= pov;
  c= ov.x*ov.x + ov.y*ov.y - ov.z;
  }

void csrpara::berechne (const cvektor3 &prv, cschnittpunkte &psp)
  {
  real a= prv.x*prv.x + prv.y*prv.y;
  real b= -prv.x*ov.x - prv.y*ov.y + prv.z/2;

  real d= b*b - a*c;
  if (d < 0)
    return;

  real e= sqrtr (d);
  real s1= (b + e)/a;
  real s2= (b - e)/a;

  if (s1 > 0)
    psp.add (s1);
  if (s2 > 0)
    psp.add (s2);
  }

// ---------------------------- hyperbolisches Paraboloid ----------------------------------

cshpara::cshpara ()
  {
  ov= cvektor3 (0, 0, 0);
  }

void cshpara::init (const cvektor3 &pov)
  {
  ov= pov;
  c= ov.x*ov.x - ov.y*ov.y - ov.z;
  }

void cshpara::berechne (const cvektor3 &prv, cschnittpunkte &psp)
  {
  real a= prv.x*prv.x - prv.y*prv.y;
  real b= -prv.x*ov.x + prv.y*ov.y + prv.z/2;
  if (a == 0)
    {
    if (b == 0)
      return;
    real s3= c/b/2;
    if (s3 > 0)
      psp.add (s3);
    return;
    }

  real d= b*b - a*c;
  if (d < 0)
    return;

  real e= sqrtr (d);
  real s1= (b + e)/a;
  real s2= (b - e)/a;

  if (s1 > 0)
    psp.add (s1);
  if (s2 > 0)
    psp.add (s2);
  }

// ---------------------------- Torus -----------------------------------------------

cstorus::cstorus (const real pr)
  : r (pr)
  {
  }

void cstorus::init (const cvektor3 &pov)
  {
  ov= pov;
  }

void cstorus::berechne (const cvektor3 &rv, cschnittpunkte& psp)
  {
  real rq1, rvq, rov, ovq;
  real rxq, ryq, rzq, oxq, oyq, ozq;
  real rxox, ryoy, rzoz, rxry, ryrz, rzrx, oxoy, oyoz, ozox;
  real sroxy, sroyz, srozx, proxy, proyz, prozx;
  real A, B, C, D, E;

  rq1= 1 - r*r;
  rvq= rv%rv;
  rov= rv%ov;
  ovq= ov%ov;
  rxq= rv.x*rv.x;
  ryq= rv.y*rv.y;
  rzq= rv.z*rv.z;
  oxq= ov.x*ov.x;
  oyq= ov.y*ov.y;
  ozq= ov.z*ov.z;
  rxox=rv.x*ov.x;
  ryoy=rv.y*ov.y;
  rzoz=rv.z*ov.z;
  rxry=rv.x*rv.y;
  ryrz=rv.y*rv.z;
  rzrx=rv.z*rv.x;
  oxoy=ov.x*ov.y;
  oyoz=ov.y*ov.z;
  ozox=ov.z*ov.x;
  sroxy= rv.x*ov.y + rv.y*ov.x;
  sroyz= rv.y*ov.z + rv.z*ov.y;
  srozx= rv.z*ov.x + rv.x*ov.z;
  proxy= rv.x*ov.y*rv.y*ov.x;
  proyz= rv.y*ov.z*rv.z*ov.y;
  prozx= rv.z*ov.x*rv.x*ov.z;

  A= rxq*rxq + ryq*ryq + rzq*rzq + (rxry*rxry + ryrz*ryrz + rzrx*rzrx)*2;
  B= (rxq*rxox + ryq*ryoy + rzq*rzoz + rxry*sroxy + ryrz*sroyz + rzrx*srozx)*4;
  C= (rq1*rvq + sroxy*sroxy + sroyz*sroyz + srozx*srozx + (proxy + proyz + prozx - rxq - ryq)*2 + (rxq*oxq + ryq*oyq + rzq*ozq)*3)*2;
  D= (rq1*rov + oxq*rxox + oyq*ryoy + ozq*rzoz + oxoy*sroxy + oyoz*sroyz + ozox*srozx - (rxox + ryoy)*2)*4;
  E= rq1*(rq1 + ovq*2) + oxq*oxq + oyq*oyq + ozq*ozq + (oxoy*oxoy + oyoz*oyoz + ozox*ozox)*2 - (oxq + oyq)*4;

  //quartischdiffpuintr (B/A, C/A, D/A, E/A, psp);
  //quartischdiffpvintr (B/A, C/A, D/A, E/A, psp);
  quartischdiffpfintr (B/A, C/A, D/A, E/A, psp);
  //quartischbuchfintr (B/A, C/A, D/A, E/A, psp);
  //quartischlagrangeuintr (B/A, C/A, D/A, E/A, psp);
  //quartischlagrangecintr (B/A, C/A, D/A, E/A, psp);

/*
  ckomplexk x1, x2, x3, x4;
  //quartisch (B/A, C/A, D/A, E/A, x1, x2, x3, x4);
  quartischdiffpuintrc (B/A, C/A, D/A, E/A, x1, x2, x3, x4);

  if (arg (x1) < quantr)
    psp.add (x1.x);
  if (arg (x2) < quantr)
    psp.add (x2.x);
  if (arg (x3) < quantr)
    psp.add (x3.x);
  if (arg (x4) < quantr)
    psp.add (x4.x);
//*/
  }

// ************************************************************************ Parametrisierungen der Oberflächen ***************************************************************************************************************************

//----------- Ebene winkeltreu -------------------------

cvektor2 cparaebenew::berechne (const cvektor3 &pv)
  {
  return cvektor2 (pv.x, pv.y);
  }

//----------- Ebene polar ------------------------------

cvektor2 cparaebenepol::berechne (const cvektor3 &pv)
  {
  return cvektor2 (atan2r (pv.y, pv.x), sqrtr (pv.x*pv.x + pv.y*pv.y));
  }

//----------- Ebene polar winkeltreu -------------------

cvektor2 cparaebenepolw::berechne (const cvektor3 &pv)
  {
  return cvektor2 (atan2r (pv.y, pv.x), logr (sqrtr (pv.x*pv.x + pv.y*pv.y)));
  }

//----------- Zylinder winkeltreu-------------------------------

cvektor2 cparazylinderw::berechne (const cvektor3 &pv)
  {
  return cvektor2 (atan2r (pv.y, pv.x), pv.z);
  }

//----------- Kugel normal ------------------------------------------------------------------------------------------------------------

cvektor2 cparakugel::berechne (const cvektor3 &pv)
  {
  return cvektor2 (atan2r (pv.y, pv.x), asinr (pv.z));
  }

//----------- Kugel winkeltreu ------------------------

cvektor2 cparakugelw::berechne (const cvektor3 &pv)
  {
  return cvektor2 (atan2r (pv.y, pv.x), atanhr (pv.z));
  }

//----------- Kugel stereografisch vom Südpol ------------------------

cvektor2 cparakugels::berechne (const cvektor3 &pv)
  {
  return cvektor2 (pv.x/(1 + pv.z), pv.y/(1 + pv.z));
  }

//----------- Kugel gnomonisch vom Südpol ------------------------

cvektor2 cparakugelg::berechne (const cvektor3 &pv)
  {
  return cvektor2 (pv.x/pv.z, pv.y/pv.z);
  }

//----------- Hyperboloid normal -----------------------

cvektor2 cparahypere::berechne (const cvektor3 &pv)
  {
  return cvektor2 (atan2r (pv.y, pv.x), asinhr (pv.z));
  }

//----------- Hyperboloid nicht normal -----------------------

cvektor2 cparahyperz::berechne (const cvektor3 &pv)
  {
  return cvektor2 (atan2r (pv.y, pv.x), acoshr (absr (pv.z)));
  }

//------------------ Kegel ------------------------------------

cvektor2 cparakegelw::berechne (const cvektor3 &pv)
  {
  return cvektor2 (atan2r (pv.y, pv.x), logr (absr (pv.z)));
  }

//----------- Rotationsparaboloid ----------------------

cvektor2 cpararpara::berechne (const cvektor3 &pv)
  {
  return cvektor2 (atan2r (pv.y, pv.x), sqrtr (pv.z));
  }

//----------- Torus signed ----------------------------
/*
cvektor2 cparatorus::berechne (const cvektor3 &pv)
  {
  cvektor3 mitte= normiere (cvektor3 (pv.x, pv.y, 0));
  real wi= winkelb (mitte, pv - mitte);
  if (pv.z >= 0)
    return cvektor2 (atan2r (pv.y, pv.x), wi);
    else
    return cvektor2 (atan2r (pv.y, pv.x), -wi);
  }
/*/
//----------- Torus unsigned ----------------------------

cvektor2 cparatorus::berechne (const cvektor3 &pv)
  {
  cvektor3 mitte= normiere (cvektor3 (pv.x, pv.y, 0));
  real wi= winkelb (mitte, pv - mitte);
  if (pv.z >= 0)
    return cvektor2 (PI + atan2r (pv.y, pv.x), wi);
    else
    return cvektor2 (PI + atan2r (pv.y, pv.x), PI2-wi);
  }

// ************************************************************************** Begrenzungsobjekte *******************************************************************************************************************************************

// -------------------- keine Begrenzung ------------------------------------

integer cbegrkeine::sichtbar (const cvektor2 &pv)
  {
  return 1;
  while (!(pv == pv));        // Variable benutzen, damit Compiler nicht meckert unused variable
  }

// -------------------- Rechteck ------------------------------------

cbegrrechteck::cbegrrechteck (const real plinks, const real prechts, const real punten, const real poben)
  {
  links= plinks;
  rechts= prechts;
  oben= poben;
  unten= punten;
  }

integer cbegrrechteck::sichtbar (const cvektor2 &pv)
  {
  if (pv.x < links)
    return 0;
  if (pv.x > rechts)
    return 0;
  if (pv.y < unten)
    return 0;
  if (pv.y > oben)
    return 0;
  return 1;
  }

// -------------------- Kreis ------------------------------------

cbegrkreis::cbegrkreis (const real plinks, const real prechts, const real pinnen, const real paussen)
  {
  links= plinks;
  rechts= prechts;
  innen= pinnen;
  aussen= paussen;
  }

integer cbegrkreis::sichtbar (const cvektor2 &pv)
  {
  real r= sqrtr (pv.x*pv.x + pv.y*pv.y);
  if (r > aussen)
    return 0;
  if (r < innen)
    return 0;
  real w= atan2r (pv.y, pv.x);
  if (w < links)
    return 0;
  if (w > rechts)
    return 0;
  return 1;
  }

// -------------------- Ellipse ------------------------------------

cbegrellipse::cbegrellipse (const real pha, const real phb)
  {
  ha= pha;
  hb= phb;
  }

integer cbegrellipse::sichtbar (const cvektor2 &pv)
  {
  real xh= pv.x/ha;
  real yh= pv.y/hb;
  if (xh*xh + yh*yh > 1)
    return 0;
  return 1;
  }

//*********************************************************************** Mannigfaltigkeiten ********************************************************************************************************************************************

clmannig::clmannig ()
  {
  }

cvektor3 clmannig::getpixel (const cvektor2 &pv)
  {
  //return getpunkt (pv);
  return cvektor3 (255,255,0);
  while (pv.x != pv.x);                                           // pv benutzen
  }

cvektor3 clmannig::getpixel16 (const cvektor2 &pv)
  {
  cvektor3 sum (0, 0, 0);
  real xm (pv.x - 1);
  real ym (pv.y - 1);
  for (integer yl= 0; yl < 4; yl++)
    {
    xm= pv.x - 1;
    for (integer xl= 0; xl < 4; xl++)
      {
      //sum= sum + getpunkt (cvektor2 (real (xm + drand48 ()/4), real (ym + drand48 ()/4)));
      sum= sum + getpunkt (cvektor2 (real (xm), real (ym)));
      xm= xm + real (0.25);
      }
    ym= ym + real (0.25);
    }
  return sum/16;
  }

// ************************************************************************************************ Färbungen  **************************************************************************************************************************

//------------------------- einfarbige Texturierung ---------------------------------

cmonochrom::cmonochrom (const cvektor3 &pfarbe)
  {
  farbe= pfarbe;
  }

cvektor3 cmonochrom::getpunkt (const cvektor2 &pv)
  {
  return farbe;
  while (pv.x != pv.x);                                           // pv benutzen, weil sonst der Compiler meckert
  }

//------------------------- Schachfeld ---------------------------------

cschachfeld::cschachfeld (const cvektor3 &pfb1, const cvektor3 &pfb2, const real &pkx, const real &pky)
  {
  fb1= pfb1;
  fb2= pfb2;
  kx= pkx;
  ky= pky;
  }

cvektor3 cschachfeld::getpunkt (const cvektor2 &pv)
  {
  if (integer (absr (floorr (pv.x*kx) + floorr (pv.y*ky))) & 1)
    return fb2;
    else
    return fb1;
  }

//------------------------- Texturierung aus einem Screen (bmpdatei, jpegdatei) ---------------------------------

cscreenmannig::cscreenmannig (clscreen8* pscreen, const real pkx, const real pky)
  : screen (pscreen), kx (pkx), ky (pky), xmax (real (screen->xanz) - 1), ymax (real (screen->yanz) - 1)
  {
  }

// nicht zentriertes Bild, gezoomt, periodisch
cvektor3 cscreenmannig::getpunkt (const cvektor2 &pv)
  {
  integer x= integer (modr (absr (pv.x*kx*ymax), xmax));
  integer y= integer (modr (absr (pv.y*ky*ymax), ymax));

  integer r, g, b;
  screen->getpixel (x, y, r, g, b);
  return cvektor3 (real (r), real (g), real (b));
  }

// zentriertes Bild, nicht gezoomt, nicht periodisch
cscreenmannigz::cscreenmannigz (clscreen8* pscreen, const real pkx, const real pky)
  : screen (pscreen), kx (pkx), ky (pky), xmax (real (screen->xanz) - 1), ymax (real (screen->yanz) - 1)
  {
  xz= real (screen->xanz)/2;
  yz= real (screen->yanz)/2;
  }

cvektor3 cscreenmannigz::getpunkt (const cvektor2 &pv)
  {
  integer x= integer (pv.x*kx*xz + xz);
  integer y= integer (pv.y*ky*yz + yz);

  integer r, g, b;
  screen->getpixel (x, y, r, g, b);
  return cvektor3 (real (r), real (g), real (b));
  }

// ***************************************************************** Geometrische Gebilde ***********************************************************************************

// ------------------------ ckörper --------------------------------------------------------------------------

ckoerper::ckoerper (clschnitt* pschnitt, clpara* ppara, clbegr* pbegr, clmannig* pmannig, const cvektor3 &ppos, const cbasis3 &pbasis)
  : koerperpos (ppos), schnitt (pschnitt), para (ppara), begr (pbegr), mannig (pmannig), koerperbasis (pbasis),
    drehbasis (cvektor3 (1, 0, 0), cvektor3 (0, 1, 0), cvektor3 (0, 0, 1)),
    augpos (0, 0, 0),
    augbasis (cvektor3 (1, 0, 0), cvektor3 (0, 1, 0), cvektor3 (0, 0, 1)),
    transbasis (cvektor3 (1, 0, 0), cvektor3 (0, 1, 0), cvektor3 (0, 0, 1)),
    transpos (0, 0, 0)
  {
  startzeit= 0;
  stopzeit= 0;
  startpos= koerperpos;
  stoppos= koerperpos;
  }

void ckoerper::setzeauge (const cvektor3 &paugpos, const cbasis3 &paugbasis)
  {
  augpos= paugpos;
  augbasis= paugbasis;
  const cbasis3 gkoerperbasis (drehbasis*koerperbasis);
  transbasis= augbasis/gkoerperbasis;
  transpos= (augpos - koerperpos)/gkoerperbasis;
  schnitt->init (transpos);
  }

void ckoerper::drehe (const cbasis3 &pdrehbasis)
  {
  drehbasis= normiere (transp (transp (augbasis*pdrehbasis)/transp (augbasis)) * drehbasis);
  const cbasis3 gkoerperbasis (drehbasis*koerperbasis);
  transbasis= augbasis/gkoerperbasis;
  transpos= (augpos - koerperpos)/gkoerperbasis;
  schnitt->init (transpos);
  }

void ckoerper::dreheein ()
  {
  cvektor4 aw (winkelachsefrommatrix (koerperbasis));
  if (aw.r < 0.01745329)
    aw.r= -aw.r;
    else
    aw.r*= real (-0.2);
  cbasis3 db (matrixfromquaternion (quaternionfromwinkelachse (aw)));
  drehe (db);
  }

void ckoerper::verschiebe (const cvektor3 &pv)
  {
  koerperpos= koerperpos + augbasis*pv;
  }

void ckoerper::setzepos (const cvektor3 &pv)
  {
  koerperpos= pv;

  const cbasis3 gkoerperbasis (drehbasis*koerperbasis);
  transpos= (augpos - koerperpos)/gkoerperbasis;
  schnitt->init (transpos);
  }

void ckoerper::begrenze (const cvektor3 &ptransrich, const integer pnr, cschnittpunkte &psp)              // parametrisiert und begrenzt den Körper
  {
  psp.mannigpos[pnr]= para->berechne (transpos + psp.abstand[pnr]*ptransrich);
  psp.sichtbar[pnr]= begr->sichtbar (psp.mannigpos[pnr]);
  }

cvektor3 ckoerper::faerbe (const integer pnr, cschnittpunkte &psp)
  {
  return mannig->getpunkt (psp.mannigpos[pnr]);
  }

void ckoerper::aktualisiere ()
  {
  tms zeit;
  real bewpos= 0;
  real zeitpos;
  clock_t zeitint= times (&zeit);
  zeitpos= real (zeitint);
  //printf ("Zeit: %5.2Lf  \n", zeitpos);
  if (zeitpos > startzeit)
    {
    if (zeitpos < stopzeit)
      {
      bewpos= (zeitpos - startzeit)/(stopzeit - startzeit);
      koerperpos= (1 - bewpos)*startpos + bewpos*stoppos;
      }
      else
      koerperpos= stoppos;
    }

  const cbasis3 gkoerperbasis (drehbasis*koerperbasis);
  transpos= (augpos - koerperpos)/gkoerperbasis;
  schnitt->init (transpos);
  }

// ------------------------ ckörperliste --------------------------------------------------------------------------

ckoerperliste::ckoerperliste () : anz (0) {}

void ckoerperliste::add (ckoerper* pkoerper)
  {
  koerper[anz++]= pkoerper;
  }

void ckoerperliste::setzeauge (const cvektor3 &paugpos, const cbasis3 &paugbasis)
  {
  for (integer klauf= 0; klauf < anz; klauf++)
    koerper[klauf]->setzeauge (paugpos, paugbasis);
  }

//----------------------------- Welt ---------------------------------------------------------------------------------------------------------

cwelt::cwelt (const cvektor3 &paugpos, const cbasis3 &paugbasis)
  : abstand (1), augpos (paugpos), augbasis (paugbasis)
  {
  augdrehaw= cvektor4 (0, 0, 0, 0);
  himmelfarbe= cvektor3 (0, 0, 255);
  }

cwelt::cwelt (const char* pname)
  : abstand (1), augpos (0,0,0),
    augbasis (cvektor3 (0,0,0), cvektor3 (0,0,0), cvektor3 (0,0,0))
  {
  augdrehaw= cvektor4 (0, 0, 0, 0);
  FILE* datei= fopen (pname, "rb");
  integer anz;
  anz= fread (&augpos, sizeof (augpos), 1, datei);
  anz= fread (&augbasis, sizeof (augbasis), 1, datei);
  anz= fread (&anz, sizeof (anz), 1, datei);
  himmelfarbe= cvektor3 (0, 0, 255);
  }

cvektor3 cwelt::getpunkt (const cvektor2 &pv)
  {
  cvektor3 sv (pv.x, pv.y, abstand);                                                        // Ebenenprojektion
  //cvektor3 sv (sin(pv.x/abstand*2*PI), pv.y/abstand*2*PI, cos (pv.x/abstand*2*PI));         // Zylinderprojektion

  // Schnittpunkte erstellen, Schnittpunkte parametrisieren, Objekt begrenzen
  cschnittpunkte schnittpunkte;
  for (integer klauf= 0; klauf < koerperliste.anz; klauf++)
    {
    integer lschnittanz= schnittpunkte.anz;

    // Richtungsvektor ermitteln
    cvektor3 transrich= koerperliste.koerper[klauf]->transbasis*sv;

    // Schnittpunkt von der Schnittpunktberechnungsroutine des Körpers berechnen lassen und in Schnittpunkte eintragen lassen
    // Die Schnittpunktroutine darf den Schnittpunkt nur eintragen, wenn er vor dem Auge liegt (schnittpunkte.abstand > 0)
    koerperliste.koerper[klauf]->schnitt->berechne (transrich, schnittpunkte);

    // Mannigfaltigkeit begrenzen (Schnittpunkte ausserhalb der Grenzen als nicht sichtbar markieren)
    for (integer knrlauf= lschnittanz; knrlauf < schnittpunkte.anz; knrlauf++)
      {
      schnittpunkte.koerpernr[knrlauf]= klauf;
      koerperliste.koerper[klauf]->begrenze (transrich, knrlauf, schnittpunkte);
      }
    }
  if (schnittpunkte.anz == 0)
    return himmelfarbe;                                                                    // bei keinem Schnittpunkt Hintergrundfarbe zurückgeben

  // nahsten sichtbaren Schnittpunkt heraussuchen
  integer kmin= -1;
  for (signed long nlauf= 0; nlauf < schnittpunkte.anz; nlauf++)
    if (schnittpunkte.sichtbar[nlauf])
      {
      if (kmin == -1)
        kmin= nlauf;
        else
        if (schnittpunkte.abstand[nlauf] < schnittpunkte.abstand[kmin])  // Schnittpunkt markieren wenn er näher ist
          kmin= nlauf;
      }

  // bei keinem Schnittpunkt Hintergrundfarbe zurückgeben
  if (kmin == -1)
    return himmelfarbe;

  // Farbe des nahsten Schnittpunkts zurückgeben
  return koerperliste.koerper[schnittpunkte.koerpernr[kmin]]->faerbe (kmin, schnittpunkte);
  }

void cwelt::addkoerper (ckoerper* pkoerper)
  {
  pkoerper->setzeauge (augpos, augbasis);
  koerperliste.add (pkoerper);
  }

void cwelt::setzeposition (const cvektor3 &pv)
  {
  augpos= pv;
  koerperliste.setzeauge (augpos, augbasis);
  }

void cwelt::verschiebeauge (const cvektor3 &pv)
  {
  augpos= augpos + augbasis*pv;
  koerperliste.setzeauge (augpos, augbasis);
  }

void cwelt::setzelage (const cbasis3 &pb)
  {
  augbasis= normiere (pb);
  koerperliste.setzeauge (augpos, augbasis);
  }

void cwelt::dreheauge (const cbasis3 &pb)
  {
  augbasis= normiere (augbasis*pb);
  koerperliste.setzeauge (augpos, augbasis);
  }

void cwelt::dreheaugex (const real pwinkel)
  {
  augbasis= normiere (augbasis*getrotx(pwinkel));
  koerperliste.setzeauge (augpos, augbasis);
  }

void cwelt::dreheaugey (const real pwinkel)
  {
  augbasis= normiere (augbasis*getroty(pwinkel));
  koerperliste.setzeauge (augpos, augbasis);
  }

void cwelt::dreheaugez (const real pwinkel)
  {
  augbasis= normiere (augbasis*getrotz(pwinkel));
  koerperliste.setzeauge (augpos, augbasis);
  }

void cwelt::dreheaugeachse (const real pwinkel)
  {
  augdrehaw.r= pwinkel;
  cbasis3 achsdrehbasis (matrixfromwinkelachse (augdrehaw));
  augbasis= normiere (achsdrehbasis*augbasis);
  koerperliste.setzeauge (augpos, augbasis);
  }

void cwelt::dreheaugenorm (const real pwinkel)
  {
  cvektor3 flugw (eulerwinkelfrommatrix (augbasis));
  cbasis3 bnorm (getroty (flugw.x));
  cvektor4 aw (winkelachsefrommatrix (augbasis/bnorm));
  if (aw.r < 0.01745329)
    aw.r= -aw.r;
    else
    aw.r*= real (-0.2);
  cbasis3 db (matrixfromwinkelachse (aw));
  augbasis= normiere (augbasis*db);
  koerperliste.setzeauge (augpos, augbasis);
  while (pwinkel != pwinkel);                                     // wegen unused variable, wird später noch benutzt?
  }

void cwelt::dreheaugeein (const real pwinkel)
  {
  cvektor4 aw (winkelachsefrommatrix (augbasis));
  if (aw.r < 0.01745329)
    aw.r= -aw.r;
  else
    aw.r*= real (-0.2);
  cbasis3 db (matrixfromwinkelachse (aw));
  augbasis= normiere (augbasis*db);
  koerperliste.setzeauge (augpos, augbasis);
  while (pwinkel != pwinkel);                                     // wegen unused variable, wird später noch benutzt?
  }

void cwelt::aktualisiere ()
  {
  for (integer lauf= 0; lauf < koerperliste.anz; lauf++)
    koerperliste.koerper[lauf]->aktualisiere ();
  }

//---------------------------------- Bildklassen --------------------------------------------------------------------------

cpunkt::cpunkt ()
  : pos (0,0), farbe (0,0,0)
  {}

cpunktscreen::cpunktscreen (integer px, integer py)
  : xanz (px), yanz (py)
  {
  vbild= new cpunkt[xanz*yanz];
  }

cpunktscreen::~cpunktscreen ()
  {
  delete (vbild);
  }

void cpunktscreen::fuelle (clmannig &pmannig)
  {
  const real xoff (real (-xanz)/2);
  const real yoff (real (-yanz)/2);
  for (integer ny= 0; ny < yanz; ++ny)
    for (integer nx= 0; nx < xanz; ++nx)
      {
      //vbild[ny*xanz + nx].pos.x= real (real (nx) + xoff + drand48 ());
      //vbild[ny*xanz + nx].pos.y= real (real (ny) + yoff + drand48 ());
      vbild[ny*xanz + nx].pos.x= real (real (nx) + xoff);
      vbild[ny*xanz + nx].pos.y= real (real (ny) + yoff);
      vbild[ny*xanz + nx].farbe= pmannig.getpunkt (vbild[ny*xanz + nx].pos);
      }
  }

void cpunktscreen::plotte (clscreen8 &plscreen)
  {
  for (integer ny= 0; ny < plscreen.yanz; ++ny)
    for (integer nx= 0; nx < plscreen.xanz; ++nx)
      {
      //integer vx= (integer) (real(nx)/(plscreen.xanz-1)*(xanz-1) + 0.5);
      //integer vy= (integer) (real(ny)/(plscreen.yanz-1)*(yanz-1) + 0.5);
      //plscreen.putpixel (nx, ny, vbild[vy*xanz + vx].farbe);
      }
  plscreen.flush ();
  }

