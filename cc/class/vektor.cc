/*
problematische Spezialfälle

norm (nullvektor): welcher Vektor soll zurückgegeben werden?
  1. der Nullvektor
  2. der Einsvektor

winkelachse von 180° Drehungen: welche der beiden Achsen soll zurückgegeben werden?
  1. die mit den wenigsten Minuszeichen
  2. die mit positiven ersten von 0 verschiedenen Wert

*/

#include "vektor.h"
#include "../../conio/vektorcon.h"     // zum Debuggen

//------------------------------------------- Schnittpunkte Klasse ---------------------------------------------------------
cschnittpunkte::cschnittpunkte ()
  {
  anz= 0;
  }

void cschnittpunkte::add (const real &pf)
  {
  abstand[anz]= pf;
  anz++;
  }

//------------------------------------------- cvektor2 ---------------------------------------------------------
cvektor2::cvektor2 () {}

cvektor2::cvektor2 (const real &px, const real &py)
  : x (px), y (py) {}

//------------------------------------------- ckomplexk ---------------------------------------------------------
ckomplexk::ckomplexk () {}

ckomplexk::ckomplexk (const real &pr)
  : cvektor2 (pr, 0) {}

ckomplexk::ckomplexk (const real &px, const real &py)
  : cvektor2 (px, py) {}

//------------------------------------------- ckomplexp ---------------------------------------------------------
ckomplexp::ckomplexp () {}

ckomplexp::ckomplexp (const real &pr)
  : b (pr), w (0)
  {
  if (b < 0)
    {
    b= -b;
    w= PI;
    return;
    }
  if (b == 0)     // falls die Null ein Minusvorzeichen hat, dieses entfernen
    b= 0;
  }

ckomplexp::ckomplexp (const real &pb, const real &pw)
  : b (pb), w (pw)
  {
  if (b < 0)
    {
    b= -b;
    w= w + PI;
    if (w > PI*2)
      w= w - PI*2;
    return;
    }
  if (b == 0)     // Vorzeichen von b und Winkel entfernen
    {
    b= 0;
    w= 0;
    }
  }

//------------------------------------------- basis2 ---------------------------------------------------------
cbasis2::cbasis2 () {}

cbasis2::cbasis2 (const real &pk)
  : x (pk, 0), y (0, pk) {}

cbasis2::cbasis2 (const cvektor2 &pv)
  : x (pv.x, 0), y (0, pv.y) {}

cbasis2::cbasis2 (const cvektor2 &px, const cvektor2 &py)
  : x (px), y (py) {}

//------------------------------------------- cvektor3 ---------------------------------------------------------
cvektor3::cvektor3 () {}

cvektor3::cvektor3 (const real &pr)
  : x (pr), y (pr), z (pr) {}

cvektor3::cvektor3 (const real &px, const real &py, const real &pz)
  : x (px), y (py), z (pz) {}

//------------------------------------------- cbasis3 ---------------------------------------------------------
cbasis3::cbasis3 () {}

cbasis3::cbasis3 (const real &pk)
  : x (pk, 0, 0), y (0, pk, 0), z (0, 0, pk) {}

cbasis3::cbasis3 (const cvektor3 &pv)
  : x (pv.x, 0, 0), y (0, pv.y, 0), z (0, 0, pv.z) {}

cbasis3::cbasis3 (const cvektor3 &px, const cvektor3 &py, const cvektor3 &pz)
  : x (px), y (py), z (pz) {}

//------------------------------------------- cvektor4 ---------------------------------------------------------
cvektor4::cvektor4 () {}

cvektor4::cvektor4 (const real &pr, const real &pi, const real &pj, const real &pij)
  : r (pr), i (pi), j (pj), ij (pij) {}

cvektor4::cvektor4 (const real &pr, const cvektor3 &pv)
  : r (pr), i (pv.x), j (pv.y), ij (pv.z) {}

//------------------------------------------- cquaternion ---------------------------------------------------------
cquaternion::cquaternion (const real &pr, const real &pi, const real &pj, const real &pij)
  {
  r= pr;
  i= pi;
  j= pj;
  ij= pij;
  }

//------------------------------------------- cvektor7 ---------------------------------------------------------
cvektor7::cvektor7 () {}

cvektor7::cvektor7 (const real &pr, const real &pi, const real &pj, const real &pij, const real &pji, const real &piji, const real &pjij)
  : r (pr), i (pi), j (pj), ij (pij), ji (pji), iji (piji), jij (pjij) {}

//------------------------------------------- cvektor8 ---------------------------------------------------------
cvektor8::cvektor8 () {}

cvektor8::cvektor8 (const real &pr, const real &pi, const real &pj, const real &pij, const real &po, const real &pio, const real &pjo, const real &pijo)
  : r (pr), i (pi), j (pj), ij (pij), o (po), io (pio), jo (pjo), ijo (pijo) {}

//--------------------- integer Funktionen ------------------------------------------------------------------------------

void swap (integer& a, integer& b)
  {
  integer c;
  c= a;
  a= b;
  b= c;
  }

integer max (integer a, integer b)
  {
  if (a >= b)
    return a;
  return b;
  }

void savemax (integer& pmax, integer pr)
  {
  pmax= max (pmax, pr);
  }

//--------------------- real Funktionen -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------ fmodr ------------------------------------------------------------------------
_Float32 fmodr (const _Float32& a, const _Float32& b)
  {
  return fmodf (a, b);
  }

_Float64 fmodr (const _Float64& a, const _Float64& b)
  {
  return fmod (a, b);
  }

long double fmodr (const long double& a, const long double& b)
  {
  return fmodl (a, b);
  }

//------------------------------------------------------------------------------------ floorr ------------------------------------------------------------------------
_Float32 floorr (const _Float32& a)
  {
  return floorf (a);
  }

_Float64 floorr (const _Float64& a)
  {
  return floor (a);
  }

long double floorr (const long double& a)
  {
  return floorl (a);
  }

//------------------------------------------------------------------------------------ fabsr --------------------------------------------------------------------------
_Float32 fabsr (const _Float32& a)
  {
  return fabsf (a);
  }

_Float64 fabsr (const _Float64& a)
  {
  return fabs (a);
  }

long double fabsr (const long double& a)
  {
  return fabsl (a);
  }

//------------------------------------------------------------------------------------ sqrtr ------------------------------------------------------------------------
_Float32 sqrtr (const _Float32& a)
  {
  return sqrtf (a);
  }

_Float64 sqrtr (const _Float64& a)
  {
  return sqrt (a);
  }

long double sqrtr (const long double& a)
  {
  return sqrtl (a);
  }

//------------------------------------------------------------------------------------ cbrtr ------------------------------------------------------------------------
_Float32 cbrtr (const _Float32& a)
  {
  return cbrtf (a);
  }

_Float64 cbrtr (const _Float64& a)
  {
  return cbrt (a);
  }

long double cbrtr (const long double& a)
  {
  return cbrtl (a);
  }

//------------------------------------------------------------------------------------ quinr ------------------------------------------------------------------------
_Float32 qnrtr (const _Float32& a)
  {
  if (a >= 0)
    return powf (a, _Float32 (0.2));
    else
    return -powf (-a, _Float32 (0.2));
  }

_Float64 qnrtr (const _Float64& a)
  {
  if (a >= 0)
    return pow (a, _Float64 (0.2));
    else
    return -pow (-a, _Float64 (0.2));
  }

long double qnrtr (const long double& a)
  {
  if (a >= 0)
    return powl (a, (long double) (0.2));
    else
    return -powl (-a, (long double) (0.2));
  }

//------------------------------------------------------------------------------------ expr ------------------------------------------------------------------------
_Float32 expr (const _Float32& a)
  {
  return expf (a);
  }

_Float64 expr (const _Float64& a)
  {
  return exp (a);
  }

long double expr (const long double& a)
  {
  return expl (a);
  }

//------------------------------------------------------------------------------------ logr ------------------------------------------------------------------------
_Float32 logr (const _Float32& a)
  {
  return logf (a);
  }

_Float64 logr (const _Float64& a)
  {
  return log (a);
  }

long double logr (const long double& a)
  {
  return logl (a);
  }

//------------------------------------------------------------------------------------ powr ------------------------------------------------------------------------
_Float32 powr (const _Float32& a, const _Float32& b)
  {
  return powf (a, b);
  }

_Float64 powr (const _Float64& a, const _Float64& b)
  {
  return pow (a, b);
  }

long double powr (const long double& a, const long double& b)
  {
  return powl (a, b);
  }

//------------------------------------------------------------------------------------ sinr ------------------------------------------------------------------------
_Float32 sinr (const _Float32& a)
  {
  return sinf (a);
  }

_Float64 sinr (const _Float64& a)
  {
  return sin (a);
  }

long double sinr (const long double& a)
  {
  return sinl (a);
  }

//------------------------------------------------------------------------------------ cosr ------------------------------------------------------------------------
_Float32 cosr (const _Float32& a)
  {
  return cosf (a);
  }

_Float64 cosr (const _Float64& a)
  {
  return cos (a);
  }

long double cosr (const long double& a)
  {
  return cosl (a);
  }

//------------------------------------------------------------------------------------ asinr ------------------------------------------------------------------------
_Float32 asinr (const _Float32& a)
  {
  return asinf (a);
  }

_Float64 asinr (const _Float64& a)
  {
  return asin (a);
  }

long double asinr (const long double& a)
  {
  return asinl (a);
  }

//------------------------------------------------------------------------------------ acosr ------------------------------------------------------------------------
_Float32 acosr (const _Float32& a)
  {
  return acosf (a);
  }

_Float64 acosr (const _Float64& a)
  {
  return acos (a);
  }

long double acosr (const long double& a)
  {
  return acosl (a);
  }

//------------------------------------------------------------------------------------ atanr ------------------------------------------------------------------------
_Float32 atanr (const _Float32& a)
  {
  return atanf (a);
  }

_Float64 atanr (const _Float64& a)
  {
  return atan (a);
  }

long double atanr (const long double& a)
  {
  return atanl (a);
  }

//------------------------------------------------------------------------------------ atan2r ------------------------------------------------------------------------
_Float32 atan2r (const _Float32& a, const _Float32& b)
  {
  return atan2f (a, b);
  }

_Float64 atan2r (const _Float64& a, const _Float64& b)
  {
  return atan2 (a, b);
  }

long double atan2r (const long double& a, const long double& b)
  {
  return atan2l (a, b);
  }

//------------------------------------------------------------------------------------ asinhr ------------------------------------------------------------------------
_Float32 asinhr (const _Float32& a)
  {
  return asinhf (a);
  }

_Float64 asinhr (const _Float64& a)
  {
  return asinh (a);
  }

long double asinhr (const long double& a)
  {
  return asinhl (a);
  }

//------------------------------------------------------------------------------------ acoshr ------------------------------------------------------------------------
_Float32 acoshr (const _Float32& a)
  {
  return acoshf (a);
  }

_Float64 acoshr (const _Float64& a)
  {
  return acosh (a);
  }

long double acoshr (const long double& a)
  {
  return acoshl (a);
  }

//------------------------------------------------------------------------------------ atanhr ------------------------------------------------------------------------
_Float32 atanhr (const _Float32& a)
  {
  return atanhf (a);
  }

_Float64 atanhr (const _Float64& a)
  {
  return atanh (a);
  }

long double atanhr (const long double& a)
  {
  return atanhl (a);
  }

//--------------------- cvektor2 Vektor Funktionen ------------------------------------------------------------------------------------------------------------------------------------------------

real absv (const cvektor2 pv)
  {
  return sqrtr (pv%pv);
  }

// Kreuzfunktion: unärer Operator, senkrechten Vektor in positver Orientierung ermitteln
cvektor2 senk (const cvektor2 &pv)
  {
  return cvektor2 (-pv.y, pv.x);
  }

//---------- cvektor2 Vektor Operatoren ----------------------------------------------------------------------------------------------

// Vektorvergleich
integer operator == (const cvektor2 &pv1, const cvektor2 &pv2)
  {
  return (pv1.x == pv2.x) && (pv1.y == pv2.y);
  }

// Vorzeichen des Vektors ändern
cvektor2 operator - (const cvektor2 &pv)
  {
  return cvektor2 (-pv.x, -pv.y);
  }

// Vektoraddition
cvektor2 operator + (const cvektor2 &pv1, const cvektor2 &pv2)
  {
  return cvektor2 (pv1.x + pv2.x, pv1.y + pv2.y);
  }

// Vektorsubtraktion
cvektor2 operator - (const cvektor2 &pv1, const cvektor2 &pv2)
  {
  return cvektor2 (pv1.x - pv2.x, pv1.y - pv2.y);
  }

// Skalarlinksmultiplikation
cvektor2 operator * (const real &pf, const cvektor2 &pv)
  {
  return cvektor2 (pf*pv.x, pf*pv.y);
  }

// Skalarrechtsmultiplikation
cvektor2 operator * (const cvektor2 &pv, const real &pf)
  {
  return cvektor2 (pf*pv.x, pf*pv.y);
  }

// Skalardivision
cvektor2 operator / (const cvektor2 &pv, const real &pf)
  {
  return cvektor2 (pv.x/pf, pv.y/pf);
  }

// Skalarprodukt
real operator % (const cvektor2 &pv1, const cvektor2 &pv2)
  {
  return pv1.x*pv2.x + pv1.y*pv2.y;
  }

//--------------------- ckomplexk Funktionen für kartesischkomplexe Zahlen -----------------------------------------------------------------

// komplexer Kehrwert
ckomplexk kw (const ckomplexk pv)
  {
  real z= pv%pv;
  return ckomplexk (pv.x, -pv.y)/z;
  }

ckomplexk sqrtvk (const ckomplexk pv)
  {
  real bet= sqrtr (pv.x*pv.x + pv.y*pv.y);
  real re= sqrtr ((bet + pv.x)/2);
  real im= sqrtr ((bet - pv.x)/2);
  if (pv.y < 0)
    im= -im;
  return ckomplexk (re, im);
  }

ckomplexk sqrtv (const ckomplexk pv)
  {
  ckomplexp vpol= polar180 (pv);
  vpol.b= sqrtr (vpol.b);
  vpol.w= vpol.w/2;
  return kartes (vpol);
  }

ckomplexk cbrtv (const ckomplexk pv)
  {
  ckomplexp vpol= polar180 (pv);
  vpol.b= cbrtr (vpol.b);
  vpol.w= vpol.w/3;
  return kartes (vpol);
  }

void cbrtv (const ckomplexk pv, ckomplexk& x1, ckomplexk& x2, ckomplexk& x3)
  {
  ckomplexp vpol= polar180 (pv);
  vpol.b= cbrtr (vpol.b);
  vpol.w= vpol.w/3;

  x1= kartes (vpol);
  x2= kartes (ckomplexp (vpol.b, vpol.w + PI23));
  x3= kartes (ckomplexp (vpol.b, vpol.w - PI23));
  }

ckomplexk qnrtv (const ckomplexk pv)
  {
  ckomplexp vpol= polar180 (pv);
  vpol.b= cbrtr (vpol.b);
  vpol.w= vpol.w/5;
  return kartes (vpol);
  }

ckomplexk expv (const ckomplexk pv)
  {
  return kartes (ckomplexp (expr (pv.x), (pv.y)));                // keine Einschränkung Bijektivitätsbereich
  }

ckomplexk logv (const ckomplexk pv)                               // Rückgabe eingeschränkt auf waagerechten ]-pi, pi] Streifen
  {
  ckomplexp lv= polar180 (pv);
  if (lv.b > 0)
    lv.b= logr (lv.b);
    else
    lv.b= real (-1e10);
  return ckomplexk (lv.b, lv.w);
  }

ckomplexk coshv (const ckomplexk pv)
  {
  return (expv (pv) + expv (-pv))/2;
  }

ckomplexk sinhv (const ckomplexk pv)
  {
  return (expv (pv) - expv (-pv))/2;
  }

ckomplexk cosv (const ckomplexk pv)
  {
  return (expv (pv*ik) + expv (-pv*ik))/2;
  }

ckomplexk sinv (const ckomplexk pv)
  {
  return ik*(expv (pv*ik) - expv (-pv*ik))/-2;
  }

// ------------- ckomplexk Operatoren für kartesischkomplexe Zahlen ---------------------------------------------------------

ckomplexk operator - (const ckomplexk &pv)
  {
  return ckomplexk (-pv.x, -pv.y);
  }

ckomplexk operator + (const ckomplexk &pv1, const ckomplexk &pv2)
  {
  return ckomplexk (pv1.x + pv2.x, pv1.y + pv2.y);
  }

ckomplexk operator - (const ckomplexk &pv1, const ckomplexk &pv2)
  {
  return ckomplexk (pv1.x - pv2.x, pv1.y - pv2.y);
  }

// Skalarlinksmultiplikation
ckomplexk operator * (const real &pf, const ckomplexk &pv)
  {
  return ckomplexk (pf*pv.x, pf*pv.y);
  }

// Skalarrechtsmultiplikation
ckomplexk operator * (const ckomplexk &pv, const real &pf)
  {
  return ckomplexk (pf*pv.x, pf*pv.y);
  }

// Skalardivision
ckomplexk operator / (const ckomplexk &pv, const real &pf)
  {
  return ckomplexk (pv.x/pf, pv.y/pf);
  }

// Skalar durch kartesischkomplexe Zahl
ckomplexk operator / (const real &pf, const ckomplexk &pv)
  {
  real q= pv.x*pv.x + pv.y*pv.y;
  return ckomplexk (pv.x*pf/q, pv.y*pf/-q);
  }

// kartesischkomplexe Multiplikation
ckomplexk operator * (const ckomplexk &pv1, const ckomplexk &pv2)
  {
  return ckomplexk (pv1.x*pv2.x - pv1.y*pv2.y, pv1.x*pv2.y + pv1.y*pv2.x);
  }

// kartesischkomplexe Division
ckomplexk operator / (const ckomplexk &pv1, const ckomplexk &pv2)
  {
  real q= pv2.x*pv2.x + pv2.y*pv2.y;
  return ckomplexk ((pv1.x*pv2.x + pv1.y*pv2.y)/q, (pv1.y*pv2.x - pv1.x*pv2.y)/q);
  }

// kartesischkomplexe Potenz von ganzer Zahl
ckomplexk operator ^ (const ckomplexk &pv, const integer &pn)
  {
  ckomplexk ret= einsk;
  integer bpn= llabs (pn);

  for (integer lauf= 0; lauf < bpn; lauf++)
    ret= ret*pv;

  if (pn >= 0)
    return ret;
  return kw (ret);
  }

// kartesischkomplexe Potenz von reeller Zahl
ckomplexk operator ^ (const ckomplexk &pv, const real &pr)
  {
  ckomplexp ret= polar180 (pv);
  ret.b= powr (ret.b, pr);
  ret.w= ret.w*pr;
  return kartes (ret);
  }

// kartesischkomplexe Potenz von kartesischkomplexer Zahl
ckomplexk operator ^ (const ckomplexk &pv1, const ckomplexk &pv2)
  {
  return expv (pv2*logv (pv1));                                   // Bijektivitätsbereich: waagerechter ]-pi,pi] Streifen in der rechten Halbebene ohne y-Achse
  }

ckomplexk potenz (const ckomplexk pv1, const ckomplexk pv2)
  {
  ckomplexk ret, retx, rety;

  retx= pv1^pv2.x;
  rety= cosv (logv (pv1)*pv2.y) + ik*sinv (logv (pv1)*pv2.y);
  return retx*rety;
  }

//--------------------- ckomplexp Funktionen für polarkomplexe Zahlen -----------------------------------------------------------------

// komplexer Kehrwert
ckomplexp kw (const ckomplexp pv)
  {
  return ckomplexp (1/pv.b, -pv.w);
  }

ckomplexp sqrtv (const ckomplexp pv)
  {
  return ckomplexp (sqrtr (pv.b), pv.w/2);
  }

ckomplexp cbrtv (const ckomplexp pv)
  {
  return ckomplexp (cbrtr (pv.b), pv.w/3);
  }

ckomplexp expv (const ckomplexp pv)
  {
  return ckomplexp (expr (pv.b), (pv.w));
  }

ckomplexp logv (const ckomplexp pv)
  {
  real retb;

  if (pv.b > 0)
    retb= logr (pv.b);
    else
    retb= real (-1e10);
  return ckomplexp (retb, pv.w);
  }

ckomplexp coshv (const ckomplexp pv)
  {
  return (expv (pv) + expv (ew2*pv))/2;
  }

ckomplexp sinhv (const ckomplexp pv)
  {
  return (expv (pv) - expv (ew2*pv))/2;
  }

ckomplexp cosv (const ckomplexp pv)
  {
  return (expv (pv*ew4) + expv (pv/ew4))/2;
  }

ckomplexp sinv (const ckomplexp pv)
  {
  return (expv (pv*ew4) - expv (pv/ew4))/ew4/2;
  }

// ------------------------------------------------- ckomplexp Operatoren für polarkomplexe Zahlen ----------------------------------

ckomplexp operator - (const ckomplexp &pv)
  {
  return pv*-1;
  }

ckomplexp operator + (const ckomplexp &pv1, const ckomplexp &pv2)
  {
  return polar180 (kartes (pv1) + kartes (pv2));
  }

ckomplexp operator - (const ckomplexp &pv1, const ckomplexp &pv2)
  {
  return polar180 (kartes (pv1) - kartes (pv2));
  }

// Skalarmultiplikation
ckomplexp operator * (const real &pf, const ckomplexp &pv)
  {
  if (pf >= 0)
    return ckomplexp (pf*pv.b, pv.w);
    else
    {
    if (pv.w <= 0)
      return ckomplexp (-pf*pv.b, pv.w + PI);
      else
      return ckomplexp (-pf*pv.b, pv.w - PI);
    }
  }

// Skalardivision
ckomplexp operator / (const ckomplexp &pv, const real &pf)
  {
  if (pf >= 0)
    return ckomplexp (pv.b/pf, pv.w);
    else
    {
    if (pv.w <= 0)
      return ckomplexp (-pv.b/pf, pv.w + PI);
      else
      return ckomplexp (-pv.b/pf, pv.w - PI);
    }
  }

// Skalar durch polarkomplexe Zahl
ckomplexp operator / (const real &pf, const ckomplexp &pv)
  {
  if (pf >= 0)
    return ckomplexp (pf/pv.b, -pv.w);
    else
    if (pv.w >= 0)
      return ckomplexp (-pf/pv.b,  PI - pv.w);
      else
      return ckomplexp (-pf/pv.b, -PI - pv.w);
  }

ckomplexp operator * (const ckomplexp &pv1, const ckomplexp &pv2)
  {
  return ckomplexp (pv1.b*pv2.b, pv1.w + pv2.w);
  }

ckomplexp operator / (const ckomplexp &pv1, const ckomplexp &pv2)
  {
  return ckomplexp (pv1.b/pv2.b, pv1.w - pv2.w);
  }

ckomplexp operator ^ (const ckomplexp &pv, const real &pr)
  {
  return ckomplexp (powr (pv.b, pr), pv.w*pr);
  }

ckomplexp operator ^ (const ckomplexp &pv1, const ckomplexp &pv2)
  {
  return expv (pv2*logv (pv1));                                   // problematisch wegen Periodizität der exp, log Funktion

/*                                                                // zerlegte Berechung um bijektiven Bereich zu erweitern
  ckomplexp ret, retx, rety;
  retx= pv1^pv2.x;
  rety= ckomplexp (cosr (pv2.y), sinr (pv2.y));
  return retx*rety;
*/
  }

//--------------------- gemischtkomplexe Funktionen (Mischung: kartesischkomplex, polarkomplex) --------------------------------------------

real arg (const ckomplexk pv)
  {
  return fabsr (atan2r (pv.y, pv.x));
  }

ckomplexk kartes (const ckomplexp pv)
  {
  return ckomplexk (pv.b*cosr (pv.w), pv.b*sinr (pv.w));
  }

ckomplexp polar225 (const ckomplexk pv)                           // Winkelrückgabe [0, 2pi[
  {
  ckomplexp ret= polar180 (pv);

  if (ret.w < -PI34)
    ret.w= ret.w + PI*2;
  return ret;
  }

ckomplexp polar360 (const ckomplexk pv)                           // Winkelrückgabe [0, 2pi[
  {
  ckomplexp ret= polar180 (pv);

  if (ret.w < 0)
    ret.w= ret.w + PI*2;
  return ret;
  }

ckomplexp polar180 (const ckomplexk pv)                           // Winkelrückgabe ]-pi, pi]
  {
  return ckomplexp (absv (pv), atan2r (pv.y, pv.x));
  }

ckomplexp polarcos180 (const ckomplexk pv)                        // Winkelrückgabe ]-pi, pi]
  {
  real phi= 0;
  real laenge (absv (pv));
  if (laenge <= 0)
    return ckomplexp (0, 0);
  phi= acosr (pv.x/laenge);
  if (pv.y < 0)
    phi= -phi;
  return ckomplexp (laenge, phi);
  }

ckomplexp polartan180 (const ckomplexk pv)                        // Winkelrückgabe ]-pi, pi]
  {
  real phi= PI/4;

  if (fabsr (pv.x) > fabsr (pv.y))                                // pv.x = 0 geht weiter
    {
    phi= atanr (pv.y/pv.x);

    if (pv.x < 0)
      {                                                           // Klammer wegen ambigious else
      if (pv.y >= 0)  // 180° statt -180°
        phi+= PI;
        else
        phi-= PI;
      }

    return ckomplexp (absv (pv), phi);
    }

  if (fabsr (pv.x) < fabsr (pv.y))  // pv.y = 0 geht weiter
    {
    phi= atanr (pv.x/pv.y);

    if (pv.y >= 0)
      phi= PI/2 - phi;
      else
      phi= PI/-2 - phi;

    return ckomplexp (absv (pv), phi);
    }

    if (fabsr (pv.x) == 0)                                        // Die Beträge von x und y sind ab dieser Stelle gleich deshalb ist pv der Nullvektor
      return (ckomplexp (0, 0));

    if (pv.x < 0)                                                 // linke Hälfte also +-135°
      phi= PI*real (0.75);

    if (pv.y < 0)                                                 // untere Hälfte also -45° oder -135°
      phi= -phi;

  return ckomplexp (absv (pv), phi);
  }

// ------------------------------------------------- Operatoren für Kugelkoordinaten -----------------------------------------------------

// Winkel zwischen zwei 3-dimensionalen Einheitsvektoren in Kugelkoordinaten
real operator | (const ckugelk &pv1, const ckugelk &pv2)
  {
  return acosr (sinr (pv1.y)*sinr (pv2.y) + cosr (pv1.y)*cosr (pv2.y)*cosr (pv1.x - pv2.x));
  }

//---------- cvektor2, cbasis2 ----------------------------------------------------------------------------------

// Matrix mal Vektor
// Erklärung: die Koordinaten des Vektors beziehen sich auf das Koordinatensystem der Matrix. Die Multiplikation rechnet die kanonischen Koordinaten aus.
cvektor2 operator * (const cbasis2 &pb, const cvektor2 &pv)
  {
  return pv.x*pb.x + pv.y*pb.y;
  }

// Vektor mal transponierte Matrix
cvektor2 operator & (const cvektor2 &pv, const cbasis2 &pb)
  {
  return cvektor2 (pv%pb.x, pv%pb.y);
  }

// Vektor durch eine Matrix teilen
// Erklärung: die Koordinaten des Vektors beziehen sich auf das kanonische Koordinatensystem. Die Multiplikation rechnet die Koordinaten des Vektors in Koordinaten
// des Koordinatensystems der Matrix aus.
cvektor2 operator / (const cvektor2 &pv, const cbasis2 &pb)
  {
  // Vektor transponiert mit senkrechtem Raum multiplizieren
  return pv & ~pb;
  }

//---------- cbasis2 Funktionen -------------------------------------------------------------------------------------------

real det (const cbasis2 &pb)
  {
  return senk (pb.x) % pb.y;
  }

cbasis2 transp (const cbasis2 &pb)
  {
  return cbasis2 (cvektor2 (pb.x.x, pb.y.x),
                  cvektor2 (pb.x.y, pb.y.y));
  }

//---------- cbasis2 Operatoren -------------------------------------------------------------------------------------------

// transponierte inverse Matrix bestimmen (senkrechter Raum zur Basis)
cbasis2 operator ~ (const cbasis2 &pb)
  {
  // Haupdiagonale vertauschen, Nebendiagonale Vorzeichen ändern, durch die Determinante teilen
  return cbasis2 (-senk (pb.y), senk (pb.x))/(senk (pb.x) % pb.y);
  }

// Matrixaddition
cbasis2 operator + (const cbasis2 &pb1, const cbasis2 &pb2)
  {
  return cbasis2 (pb1.x + pb2.x, pb1.y + pb2.y);
  }

// Matrixsubtraktion
cbasis2 operator - (const cbasis2 &pb1, const cbasis2 &pb2)
  {
  return cbasis2 (pb1.x - pb2.x, pb1.y - pb2.y);
  }

// Skalardivision
cbasis2 operator / (const cbasis2 &pb, const real &pf)
  {
  return cbasis2 (pb.x/pf, pb.y/pf);
  }

// Matrixmultiplikation
// Erklärung: die Koordinaten der Vektoren der 2. Basis beziehen sich auf die 1. Basis.
// Die Multiplikation rechnet die kanonischen Koordinaten der Vektoren der 2. Basis aus.
cbasis2 operator * (const cbasis2 &pb1, const cbasis2 &pb2)
  {
  return cbasis2 (pb1*pb2.x, pb1*pb2.y);
  }

// Matrixlinksdivision
// Erklärung: die Koordinaten der Vektoren der 2. Basis beziehen sich auf die kanonische Basis
// Die Division rechnet die Koordinaten der Vektoren der 2. Basis in Koordinaten der 1. Basis aus
cbasis2 operator / (const cbasis2 &pb1, const cbasis2 &pb2)
  {
  // transponiert mit dem senkrechten Raum multiplizieren
  return pb1 & ~pb2;
  }

// Matrixrechtsdivision
cbasis2 operator | (const cbasis2 &pb1, const cbasis2 &pb2)
  {
  // von rechts mit dem Inversen multiplizieren
  return pb1 * transp (~pb2);
  }

// Matrix mal transponierte Matrix
cbasis2 operator & (const cbasis2 &pb1, const cbasis2 &pb2)
  {
  return cbasis2 (pb1.x & pb2, pb1.y & pb2);
  }

//---------- cvektor3 Funktionen ------------------------------------------------------------------------------------------

void swap (cvektor3& a, cvektor3& b)
  {
  cvektor3 c;
  c= a;
  a= b;
  b= c;
  }

real abs (const cvektor3 &pv)
  {
  return sqrtr (pv%pv);
  }

// Kreuzfunktion: unärer Operator, senkrechten Vektor in positver Orientierung ermitteln: kürzeste Komponente Null setzen, die anderen beiden senkrechtisieren
cvektor3 senk (const cvektor3 &pv)
  {
  if ((fabsr (pv.x) <= fabsr (pv.y)) && (fabsr (pv.x) <= fabsr (pv.z)))
    return cvektor3 (0, -pv.z, pv.y);
  if (fabsr (pv.y) <= fabsr (pv.z))
    return cvektor3 (pv.z, 0, -pv.x);
  return cvektor3 (-pv.y, pv.x, 0);
  }

cvektor3 normiere (const cvektor3 &pv)
  {
  return pv/sqrtr (pv%pv);
  }

cvektor3 orientiere (const cvektor3 &pv)                          // erster von 0 verschiedener Wert wird positiv gesetzt
  {
  cvektor3 ret (pv);
  if (ret.x < 0)
    ret= -ret;
  if (fabsr (ret.x) <= quantr)
    {
    ret.x= 0;
    if (ret.y < 0)
      ret= -ret;
    if (fabsr (ret.y) <= quantr)
      {
      ret.y= 0;
      if (ret.z < 0)
        ret= -ret;
      if (fabsr (ret.z) <= quantr)
        ret.z= 0;
      }
    }
  return ret;
  }

real winkelb (const cvektor3 &pv1, const cvektor3 &pv2)           // Betrag des Winkels zwischen 2 Vektoren ermitteln, Ergebnis: [0..pi]
  {
  return acosr ((pv1%pv2)/sqrtr ((pv1%pv1)*(pv2%pv2)));
  }

real winkelg (const cvektor3 &pv1, const cvektor3 &pv2)           // Betrag des Winkels zwischen 2 Geraden ermitteln, Ergebnis: [0..pi/2]
  {
  return acosr (fabsr ((pv1%pv2)/sqrtr ((pv1%pv1)*(pv2%pv2))));
  }

//---------- cvektor3 Operatoren ------------------------------------------------------------------------------------------

// Vektoren vergleichen
integer operator == (const cvektor3 &pv1, const cvektor3 &pv2)
  {
  return (pv1.x == pv2.x) && (pv1.y == pv2.y) && (pv1.z == pv2.z);
  }

// Vorzeichen des Vektors ändern
cvektor3 operator - (const cvektor3 &pv)
  {
  return cvektor3 (-pv.x, -pv.y, -pv.z);
  }

// Vektoradditon
cvektor3 operator + (const cvektor3 &pv1, const cvektor3 &pv2)
  {
  return cvektor3 (pv1.x + pv2.x, pv1.y + pv2.y, pv1.z + pv2.z);
  }

// Vektorsubtraktion
cvektor3 operator - (const cvektor3 &pv1, const cvektor3 &pv2)
  {
  return cvektor3 (pv1.x - pv2.x, pv1.y - pv2.y, pv1.z - pv2.z);
  }

// Skalarmultiplikation
cvektor3 operator * (const real &pf, const cvektor3 &pv)
  {
  return cvektor3 (pf*pv.x, pf*pv.y, pf*pv.z);
  }

// Skalardivision
cvektor3 operator / (const cvektor3 &pv, const real &pf)
  {
  return cvektor3 (pv.x/pf, pv.y/pf, pv.z/pf);
  }

// Skalarprodukt
real operator % (const cvektor3 &pv1, const cvektor3 &pv2)
  {
  return pv1.x*pv2.x + pv1.y*pv2.y + pv1.z*pv2.z;
  }

// Kreuzprodukt (senkrecht stehenden Vektor zu 2 Vektoren in positiver Orientierung ermitteln)
cvektor3 operator ^ (const cvektor3 &pv1, const cvektor3 &pv2)
  {
  return cvektor3 (pv1.y*pv2.z - pv1.z*pv2.y, pv1.z*pv2.x - pv1.x*pv2.z, pv1.x*pv2.y - pv1.y*pv2.x);
  }

// einen Vektor aus der Ebene wählen, auf dem der Vektor senkrecht steht
cvektor3 operator ~ (const cvektor3 &pv)
  {
  if ((fabsr (pv.x) < fabsr (pv.y)) && (fabsr (pv.x) < fabsr (pv.z)))
    return cvektor3 (0, pv.z, -pv.y);
  if (fabsr (pv.y) < fabsr (pv.z))
    return cvektor3 (-pv.z, 0, pv.x);
  return cvektor3 (pv.y, -pv.x, 0);
  }

//---------- cvektor3, cbasis3 ---------------------------------------------------------------------------------

// Matrix mal Vektor
cvektor3 operator * (const cbasis3 &pb, const cvektor3 &pv)
  {
  return pv.x*pb.x + pv.y*pb.y + pv.z*pb.z;
  }

// Vektor mal transponierte Matrix
cvektor3 operator & (const cvektor3 &pv, const cbasis3 &pb)
  {
  return cvektor3 (pv%pb.x, pv%pb.y, pv%pb.z);
  }

// Vektor durch eine Matrix teilen
cvektor3 operator / (const cvektor3 &pv, const cbasis3 &pb)
  {
  return pv & ~pb;
  }

//---------- cbasis3 Funktionen ------------------------------------------------------------------------------------------

real norm (cbasis3 pb)
  {
  return pb.x%pb.x + pb.y%pb.y + pb.z%pb.z;
  }

real abs (cbasis3 pb)
  {
  return sqrtr (norm (pb));
  }

real det (const cbasis3 &pb)
  {
  return (pb.x^pb.y)%pb.z;
  }

cbasis3 normiere (const cbasis3 &pb)
  {
  const cvektor3 x (normiere (pb.x));
  const cvektor3 y (normiere (pb.z^x));
  return cbasis3 (x, y, normiere (x^y));
  }

cbasis3 normiere2 (const cbasis3 &pb)
  {
  const cvektor3 x (normiere (pb.x));
  const cvektor3 y (normiere (pb.y - pb.y%x*x));
  const cvektor3 z (normiere (pb.z - pb.z%x*x - pb.z%y*y));
  return cbasis3 (x, y, z);
  }

cbasis3 transp (const cbasis3 &pb)
  {
  return cbasis3 (cvektor3 (pb.x.x, pb.y.x, pb.z.x),
                  cvektor3 (pb.x.y, pb.y.y, pb.z.y),
                  cvektor3 (pb.x.z, pb.y.z, pb.z.z));
  }

cvektor3 geteigen (const cbasis3 &pb)                             // Eigenvektor von einer homogenen Basis berechnen (det = 0)
  {
  const cbasis3 orthobasis (transp (cbasis3 (pb.y^pb.z, pb.z^pb.x, pb.x^pb.y)));
  const real sx (orthobasis.x%orthobasis.x);
  const real sy (orthobasis.y%orthobasis.y);
  const real sz (orthobasis.z%orthobasis.z);

  // längsten Eigenvektor zurückgeben
  if ((sx >= sy) && (sx >= sz))
    return orthobasis.x;
  if (sy >= sz)
    return orthobasis.y;
  return orthobasis.z;
  }

cbasis3 getrotx (const real &pf)
  {
  const real s (sinr(pf));
  const real c (cosr(pf));
  return cbasis3 (cvektor3 (1, 0, 0), cvektor3 (0, c, s), cvektor3 (0, -s, c));
  }

cbasis3 getroty (const real &pf)
  {
  const real s (sinr(pf));
  const real c (cosr(pf));
  return cbasis3 (cvektor3 (c, 0, -s), cvektor3 (0, 1, 0), cvektor3 (s, 0, c));
  }

cbasis3 getrotz (const real &pf)
  {
  const real s (sinr(pf));
  const real c (cosr(pf));
  return cbasis3 (cvektor3 (c, s, 0), cvektor3 (-s, c, 0), cvektor3 (0, 0, 1));
  }

// Spiegelungsmatrix direkt berechnen
cbasis3 getspiegbasis (const cvektor3 &pv)
  {
  if (abs (pv) <= quantr)                                         // Nullvektor als Spiegelachse ist Punktspiegelung also Inversionsmatrix zurückgeben
    return cbasis3 (-1);
  cvektor3 nv= normiere (pv);
  return cbasis3 (1) - 2*cbasis3 (nv, nv, nv)*cbasis3 (nv);
  }

// Spiegelungsmatrix aus (Drehung von 180° um Spiegelachse) berechnen
cbasis3 getdrehspiegbasis (const cvektor3 &pv)
  {
  if (abs (pv) <= quantr)                                         // Nullvektor als Spiegelachse ist Punktspiegelung also Inversionsmatrix zurückgeben
    return cbasis3 (-1);
  return -matrixfromwinkelachse (cvektor4 (PI, pv.x, pv.y, pv.z));
  }

cvektor3 getspiegachse (const cbasis3 &pb)
  {
  return normiere (geteigen (pb + cbasis3 (1)));
  }

integer aehnlich (const cbasis3 &pb1, const cbasis3 &pb2)
  {
  real dif= abs (pb1 - pb2);
  if (dif <= quantr)
    return 1;
  return 0;
  }

//---------- cbasis3 Operatoren ------------------------------------------------------------------------------------------

// transponierte inverse Matrix bestimmen
cbasis3 operator ~ (const cbasis3 &pb)
  {
  return cbasis3 (pb.y^pb.z, pb.z^pb.x, pb.x^pb.y)/((pb.x^pb.y)%pb.z);
  }

// Matrixaddition
cbasis3 operator - (const cbasis3  &pb)
  {
  return -1*pb;
  }

cbasis3 operator + (const cbasis3 &pb1, const cbasis3 &pb2)
  {
  return cbasis3 (pb1.x + pb2.x, pb1.y + pb2.y, pb1.z + pb2.z);
  }

// Matrixsubtraktion
cbasis3 operator - (const cbasis3 &pb1, const cbasis3 &pb2)
  {
  return cbasis3 (pb1.x - pb2.x, pb1.y - pb2.y, pb1.z - pb2.z);
  }

// Skalarmultiplikation
cbasis3 operator * (const real &pf, const cbasis3 &pb)
  {
  return cbasis3 (pf*pb.x, pf*pb.y, pf*pb.z);
  }

// Skalardivision
cbasis3 operator / (const cbasis3 &pb, const real &pf)
  {
  return cbasis3 (pb.x/pf, pb.y/pf, pb.z/pf);
  }

// Matrixmultiplikation
cbasis3 operator * (const cbasis3 &pb1, const cbasis3 &pb2)
  {
  return cbasis3 (pb1*pb2.x, pb1*pb2.y, pb1*pb2.z);
  }

// Matrix mal transponierte Matrix
cbasis3 operator & (const cbasis3 &pb1, const cbasis3 &pb2)
  {
  return cbasis3 (pb1.x & pb2, pb1.y & pb2, pb1.z & pb2);
  }

// Matrixlinksdivision
cbasis3 operator / (const cbasis3 &pb1, const cbasis3 &pb2)
  {
  // transponiert mit dem senkrechten Raum multiplizieren
  return pb1 & ~pb2;
  }

// Matrixrechtsdivision
cbasis3 operator | (const cbasis3 &pb1, const cbasis3 &pb2)
  {
  // von rechts mit dem Inversen multiplizieren
  return pb1 * transp (~pb2);
  }

//---------- cvektor4 Vektor Funktionen -----------------------------------------------------------------------------------------------

real abs (const cvektor4 &pv)
  {
  return sqrtr (pv%pv);
  }

// Kreuzfunktion: unärer Operator, senkrechten Vektor in positver Orientierung ermitteln
cvektor4 senk (const cvektor4 &pv)
  {
  return cvektor4 (-pv.i, pv.r, -pv.ij, pv.j);
  }

cvektor4 normiere (const cvektor4 &pv)
  {
  const real q= pv%pv;
  if (q <= quantr)
    return cvektor4 (0, 0, 0, 0);
  return pv/sqrtr (q);
  }

// Kreuzfunktion (einen senkrecht stehenden Vektor ermitteln)
cvektor4 operator ~ (const cvektor4 &pv)
  {
  return cvektor4 (-pv.i, pv.r, -pv.ij, pv.j);
  }

integer aehnlich (const cvektor4 &pv1, const cvektor4 &pv2)
  {
  real dif= abs (pv1 - pv2);
  if (dif <= quantr)
    return 1;
  return 0;
  }

//---------- cvektor4 Funktionen für Quaternionen -------------------------------------------------------------------------------------

// Kehrwert
cvektor4 kw (const cvektor4 &pv)
  {
  return cvektor4 (pv.r, -pv.i, -pv.j, -pv.ij)/(pv%pv);
  }

cvektor3 getachse (const cvektor4 &pv)
  {
  return cvektor3 (pv.i, pv.j, pv.ij);
  }
//---------- cvektor4 Vektor Operatoren ------------------------------------------------------------------------------------------------

// Vergleich
integer operator == (const cvektor4 &pv1, const cvektor4 &pv2)
  {
  return (pv1.r == pv2.r) && (pv1.i == pv2.i) && (pv1.j == pv2.j) && (pv1.ij == pv2.ij);
  }

// Vorzeichen ändern
cvektor4 operator - (const cvektor4 &pv)
  {
  return cvektor4 (-pv.r, -pv.i, -pv.j, -pv.ij);
  }

// Vektoraddition
cvektor4 operator + (const cvektor4 &pv1, const cvektor4 &pv2)
  {
  return cvektor4 (pv1.r + pv2.r, pv1.i + pv2.i, pv1.j + pv2.j, pv1.ij + pv2.ij);
  }

// Vektorsubtraktion
cvektor4 operator - (const cvektor4 &pv1, const cvektor4 &pv2)
  {
  return cvektor4 (pv1.r - pv2.r, pv1.i - pv2.i, pv1.j - pv2.j, pv1.ij - pv2.ij);
  }

// Skalarmultiplikation
cvektor4 operator * (const real &pf , const cvektor4 &pv)
  {
  return cvektor4 (pf*pv.r, pf*pv.i, pf*pv.j, pf*pv.ij);
  }

// Skalardivision
cvektor4 operator / (const cvektor4 &pv, const real &pf)
  {
  return cvektor4 (pv.r/pf, pv.i/pf, pv.j/pf, pv.ij/pf);
  }

// Skalarprodukt
real operator % (const cvektor4 &pv1, const cvektor4 &pv2)
  {
  return pv1.r*pv2.r + pv1.i*pv2.i + pv1.j*pv2.j + pv1.ij*pv2.ij;
  }

//--------------------- Operatoren für Quaternionen ---------------------------------------------------------

// Quaternionenmultiplikation
cvektor4 operator * (const cvektor4 &pv1, const cvektor4 &pv2)
  {
  return cvektor4 (pv1.r*pv2.r  -  pv1.i*pv2.i  -  pv1.j*pv2.j  -  pv1.ij*pv2.ij,
                   pv1.r*pv2.i  +  pv1.i*pv2.r  +  pv1.j*pv2.ij -  pv1.ij*pv2.j,
                   pv1.r*pv2.j  +  pv1.j*pv2.r  +  pv1.ij*pv2.i -  pv1.i*pv2.ij,
                   pv1.r*pv2.ij +  pv1.ij*pv2.r +  pv1.i*pv2.j  -  pv1.j*pv2.i);
  }

// Quaternionenlinksdivision: von links mit dem Inversen multiplizieren: b*a = c  <=>  a = b^-1 * c  <=>  a = c/b
cvektor4 operator / (const cvektor4 &pv1, const cvektor4 &pv2)
  {
  return kw (pv2) * pv1;
  }

// Quaternionenrechtsdivision: von rechts mit dem Inversen multiplizieren: b*a = c  <=>  b = c * a^-1  <=>  b = c|a
cvektor4 operator | (const cvektor4 &pv1, const cvektor4 &pv2)
  {
  return pv1 * kw (pv2);
  }

// 3D-Vektor mit Drehquaternion drehen
cvektor3 operator * (const cvektor4 &pq, const cvektor3 &pv)
  {
  //  cvektor4 ret= pq*cvektor4 (0, pv.x, pv.y, pv.z)|pq;      v' =  q * v / q

  cvektor4 pv2= cvektor4 (pv.x*pq.i  + pv.y*pq.j  + pv.z*pq.ij,
                          pv.x*pq.r  - pv.y*pq.ij + pv.z*pq.j,
                          pv.x*pq.ij + pv.y*pq.r  - pv.z*pq.i,
                         -pv.x*pq.j  + pv.y*pq.i  + pv.z*pq.r);

  return cvektor3 (pq.r*pv2.i  +  pq.i*pv2.r  +  pq.j*pv2.ij -  pq.ij*pv2.j,
                   pq.r*pv2.j  +  pq.j*pv2.r  +  pq.ij*pv2.i -  pq.i*pv2.ij,
                   pq.r*pv2.ij +  pq.ij*pv2.r +  pq.i*pv2.j  -  pq.j*pv2.i);
  }

//---------- cvektor7 Funktionen ------------------------------------------------------------------------------------------

// Heptanionenmultiplikation
cvektor7 operator * (const cvektor7 &pv1, const cvektor7 &pv2)
  {
  real lr, li, lj, lij, lji, liji, ljij;

  lr= pv1.r*pv2.r - pv1.i*pv2.i - pv1.ij*pv2.ij - pv1.ji*pv2.ji - pv1.iji*pv2.iji - pv1.jij*pv2.jij - pv1.i*pv2.jij - pv1.jij*pv2.i - pv1.j*pv2.iji - pv1.iji*pv2.j + pv1.ij*pv2.ji + pv1.ji*pv2.ij;
  li= pv1.r*pv2.i + pv1.i*pv2.r - pv1.ij*pv2.j - pv1.j*pv2.ji - pv1.iji*pv2.ji - pv1.ij*pv2.iji + pv1.iji*pv2.ij + pv1.ji*pv2.iji;
  lj= pv1.r*pv2.j + pv1.j*pv2.r - pv1.ji*pv2.i - pv1.i*pv2.ij - pv1.jij*pv2.ij - pv1.ji*pv2.jij + pv1.jij*pv2.ji + pv1.ij*pv2.jij;
  lij= pv1.r*pv2.ij + pv1.ij*pv2.r - pv1.iji*pv2.i - pv1.j*pv2.jij - pv1.iji*pv2.jij + pv1.i*pv2.j;
  lji= pv1.r*pv2.ji + pv1.ji*pv2.r - pv1.jij*pv2.j - pv1.i*pv2.iji - pv1.jij*pv2.iji + pv1.j*pv2.i;
  liji= pv1.r*pv2.iji + pv1.iji*pv2.r + pv1.ij*pv2.i + pv1.i*pv2.ji;
  ljij= pv1.r*pv2.jij + pv1.jij*pv2.r + pv1.ji*pv2.j + pv1.j*pv2.ij;

  return cvektor7 (lr, li, lj, lij, lji, liji, ljij);
  }

//---------- cvektor8 Funktionen ------------------------------------------------------------------------------------------

// Oktonionenmultiplikation
cvektor8 operator * (const cvektor8 &pv1, const cvektor8 &pv2)
  {
  real lr, li, lj, lij, lo, lio, ljo, lijo;

  lr=   pv1.r*pv2.r   - pv1.i*pv2.i   - pv1.j*pv2.j   - pv1.ij*pv2.ij  - pv1.o*pv2.o   - pv1.io*pv2.io  - pv1.jo*pv2.jo  - pv1.ijo*pv2.ijo;
  li=   pv1.r*pv2.i   + pv1.i*pv2.r   + pv1.j*pv2.ij  - pv1.ij*pv2.j   + pv1.o*pv2.io  - pv1.io*pv2.o   - pv1.jo*pv2.ijo + pv1.ijo*pv2.jo;
  lj=   pv1.r*pv2.j   - pv1.i*pv2.ij  - pv1.j*pv2.r   + pv1.ij*pv2.i   + pv1.o*pv2.jo  + pv1.io*pv2.ijo - pv1.jo*pv2.o   - pv1.ijo*pv2.io;
  lij=  pv1.r*pv2.ij  + pv1.i*pv2.j   - pv1.j*pv2.i   + pv1.ij*pv2.r   + pv1.o*pv2.ijo - pv1.io*pv2.jo  - pv1.jo*pv2.io  - pv1.ijo*pv2.o;
  lo=   pv1.r*pv2.o   - pv1.i*pv2.io  - pv1.j*pv2.jo  - pv1.ij*pv2.ijo + pv1.o*pv2.r   + pv1.io*pv2.i   + pv1.jo*pv2.j   + pv1.ijo*pv2.ij;
  lio=  pv1.r*pv2.io  + pv1.i*pv2.o   - pv1.j*pv2.ijo + pv1.ij*pv2.jo  - pv1.o*pv2.i   + pv1.io*pv2.r   - pv1.jo*pv2.ij  + pv1.ijo*pv2.j;
  ljo=  pv1.r*pv2.jo  + pv1.i*pv2.ijo + pv1.j*pv2.o   - pv1.ij*pv2.io  - pv1.o*pv2.j   + pv1.io*pv2.ij  + pv1.jo*pv2.r   - pv1.ijo*pv2.i;
  lijo= pv1.r*pv2.ijo + pv1.i*pv2.jo  + pv1.j*pv2.io  + pv1.ij*pv2.o   - pv1.o*pv2.ij  - pv1.io*pv2.j   + pv1.jo*pv2.i   - pv1.ijo*pv2.r;

  return cvektor8 (lr, li, lj, lij, lo, lio, ljo, lijo);
  }


// ------------------------------ Drehdarstellungen umrechnen ------------------------------------------------------------------------

cvektor4 quaternionfromwinkelachse (const cvektor4 pwa)
  {
  real wiha= pwa.r/2;
  cvektor3 achse= normiere (cvektor3 (pwa.i, pwa.j, pwa.ij));
  return cvektor4 (cosr (wiha), sinr (wiha)*achse);               // negativer Winkel invertiert die Drehachse statt Winkel
  }                                                               // Darstellung ist eindeutig. Das negative Quaternion, dessen Drehung zur gleichen Endposition führt (Matrix) ist eine andere Drehung
                                                                  // 90° nach rechts drehen führt zur gleichen Endposition wie 270° nach links drehen, aber es sind verschiedene Drehungen
                                                                  // Somit wird nicht eine Drehung durch 2 Quaternionen repräsentiert, sondern jede Drehung ist eindeutig durch genau ein Quaternion repräsentiert.
                                                                  // Mehrdeutigkeit kommt durch Wicklungen zustande, d.h. wenn der Winkel größer als 360° ist.
                                                                  // Jede Endposition wird durch genau 2 Drehungen erreicht. Das gilt auch für die Anfangsposition.
                                                                  // Die Anfangsposition kann durch eine 0° Drehung oder durch eine 360° Drehung erreicht werden. In beiden Fällen spielt die Drehachse keine Rolle.

cvektor4 winkelachsefromquaternion (const cvektor4 pq)
  {
  if (pq.r >= 1 - quantr)
    return cvektor4 (0, 0, 0, 0);
  if (pq.r <= -1 + quantr)
    return cvektor4 (2*PI, 0, 0, 0);
  real drehw= acosr (pq.r)*2;
  cvektor3 achse (normiere (cvektor3 (pq.i, pq.j, pq.ij)));
  if (fabsr (achse.x) <= quantr)
    achse.x= 0;
  if (fabsr (achse.y) <= quantr)
    achse.y= 0;
  if (fabsr (achse.z) <= quantr)
    achse.z= 0;
  return cvektor4 (drehw, achse.x, achse.y, achse.z);
  }

cvektor4 qwafrommatrix (const cbasis3 &pdreh)                     // nur für Drehmatrizen, nicht für Drehspiegelungsmatrizen
  {
  // Gibt den Winkel in Quaternionenform [-1 bis 1] und die Drehachse unnormiert aber richtig orientiert zurück.

  // ********************* Realteil direkt aus der Matrix berechnen, Problem bei 0° und 180° Drehungen abfangen
  real qr= 1 + pdreh.x.x + pdreh.y.y + pdreh.z.z;                 // qr [4..0] = [0..180]°
  if (qr >= 4 - quantr)             //   0° Drehung
    return cvektor4 (1, 0, 0, 0);

  // ********************* Drehachse durch Eigenwerte berechnen, Eigenvektor numerisch stabil, Länge: [5 1/3 bis 16]
  cbasis3 hdreh (pdreh);
  hdreh.x.x-= 1;
  hdreh.y.y-= 1;
  hdreh.z.z-= 1;
  cvektor3 drehachse (geteigen (hdreh));

  // Drehachse richtig orientieren
  if (qr <= quantr)                                               // 180° Drehung: Es gibt 2 Drehachsen statt nur einer
    {
    qr= 0;
    drehachse= orientiere (drehachse);                            // bei 180° Drehung Achse mit positven ersten von 0 verschiedenem Wert aussuchen. (besser kleinste Anzahl von Minuszeichen)
    }
    else                                                          // Drehung zwischen 0° und 180°
    {
    // Drehachse richtig orientieren (Testen ob die Drehung ein positives Volumen erzeugt, versagt bei 0° und 180° Drehungen da Volumen dann 0 ist)
    cvektor3 s1 (~drehachse);
    cvektor3 s2 (pdreh*s1);
    if (((drehachse^s1)%s2) < 0)
      drehachse= -drehachse;
    }
  return cvektor4 (sqrtr (qr)/2, drehachse.x, drehachse.y, drehachse.z);
  }

cvektor4 winkelachsefrommatrix (const cbasis3 &pdreh)             // Bei Drehspiegelungen wird der Spiegelanteil durch Inversion der Drehspiegelungsmatrix entfernt und dann Winkel und Achse der verbleibenden Drehmatrix bestimmt
  {
  cvektor4 qwa;
  if (det (pdreh) > 0)
    qwa= qwafrommatrix (pdreh);
    else
    qwa= qwafrommatrix (-pdreh);
  if (fabsr (qwa.i) <= quantr)
    qwa.i= 0;
  if (fabsr (qwa.j) <= quantr)
    qwa.j= 0;
  if (fabsr (qwa.ij) <= quantr)
    qwa.ij= 0;
  cvektor3 achse (qwa.i, qwa.j, qwa.ij);
  achse= normiere (achse);
  if (det (pdreh) < 0)
    {
    real wi= 2*acosr (qwa.r);
    if (aehnlich (wi, 0))
      return cvektor4 (-2*PI, achse.x, achse.y, achse.z);                       // pq.r = -360°: Matrix ist die Punktspiegelungsmatrix (Inversion (-id))
      //return cvektor4 (0, achse.x, achse.y, achse.z);                         // Problemfall 0° wäre positiver Winkel also Drehung und nicht Drehspiegelung
    return cvektor4 (-2*acosr (qwa.r), achse.x, achse.y, achse.z);
    }
  return cvektor4 (2*acosr (qwa.r), achse.x, achse.y, achse.z);
  }

cbasis3  matrixfromwinkelachse (const cvektor4 pq)
  {
  return matrixfromquaternion (quaternionfromwinkelachse (pq));
  }

cvektor4 quaternionfrommatrix (const cbasis3 &pdreh)              // Funktioniert bei 0° und 180° Drehungen
  {
  cvektor4 qwa (qwafrommatrix (pdreh));                           // Mehrdeutigkeit der Achse bei 180° Drehungen
  if (qwa.r >= 1 - quantr)      // Drehung ist 0° Drehung
    return qwa;                // 1 zurückgeben
  cvektor3 achse (cvektor3 (qwa.i, qwa.j, qwa.ij));
  real k= sqrtr (1 - qwa.r*qwa.r)/abs (achse);
  return cvektor4 (qwa.r, k*achse);
  }

cvektor4 quaternionfrommatrix2 (const cbasis3 &pdreh)             // Kreuzproduktversion: versagt bei 180° Drehungen
  {
  real qr= sqrtr (1 + pdreh.x.x + pdreh.y.y + pdreh.z.z);
  if (qr <= quantr)                                               // 180° Drehung
    return cvektor4 (0, 1, 0, 0);                                 // Bullshit zurückgeben
  real qi= (pdreh.y.z - pdreh.z.y)/qr;
  real qj= (pdreh.z.x - pdreh.x.z)/qr;
  real qij=(pdreh.x.y - pdreh.y.x)/qr;
  return cvektor4 (qr, qi, qj, qij)/2;
  }

cbasis3 matrixfromquaternion (const cvektor4 pq)                  // Es kommen nur 2-fache Produkte vor, da mat (q) = mat (-q)
  {
  real x, y, z;
  x= 1 - 2*(pq.j*pq.j + pq.ij*pq.ij);
  y= 2*pq.r*pq.ij + 2*pq.i*pq.j;
  z= -2*pq.r*pq.j + 2*pq.i*pq.ij;
  cvektor3 m1 (x, y, z);
  x= -2*pq.r*pq.ij + 2*pq.i*pq.j;
  y= 1 - 2*(pq.i*pq.i + pq.ij*pq.ij);
  z= 2*pq.r*pq.i + 2*pq.j*pq.ij;
  cvektor3 m2 (x, y, z);
  x= 2*pq.r*pq.j + 2*pq.i*pq.ij;
  y= -2*pq.r*pq.i + 2*pq.j*pq.ij;
  z= 1 - 2*(pq.i*pq.i + pq.j*pq.j);
  cvektor3 m3 (x, y, z);
  cbasis3 mat (m1, m2, m3);
  mat= normiere (mat);
  return mat;
  }

cbasis3 matrixfromeulerwinkel (cvektor3 pflugw)
  {
  return normiere (getroty (pflugw.x)*getrotx (-pflugw.y)*getrotz (-pflugw.z));
  }

cvektor3 eulerwinkelfrommatrix (const cbasis3& pdm)
  {
  real laenge= 0;
  real vl= 0;
  real breite= 0;
  real vb= 0;
  real roll= 0;
  real vr= 0;

  // Breitengradberechnung
  vb= pdm.z.y;
  if (fabsr (vb) < 1)
    breite= asinr (vb);
  if (vb >= 1)
    breite= PI/2;
  if (vl <= -1)
    breite= -PI/2;

  // Längengrad- und Rollberechnung
  real cosbr= cosr (breite);
  if (cosbr > quantr)  // Breite nicht polar
    {
    // Längengradberechnung
    vl= pdm.z.z/cosbr;
    if (fabsr (vl) < 1)
      laenge= acosr (vl);
    if (vl >= 1)
      laenge= 0;
    if (vl <= -1)
      laenge= PI;
    if (pdm.z.x < 0)
      laenge = -laenge;

    // Rollberechnung
    vr= pdm.y.y/cosbr;
    if (fabsr (vr) < 1)
      roll= acosr (vr);
    if (vr >= 1)
      roll= 0;
    if (vr <= -1)
      roll= PI;
    if (pdm.x.y > 0)
      roll= -roll;
    }
  if (cosbr <= quantr)  // Spezialfall Breite polar
    {
    vl= pdm.x.x;
    if (fabsr (vl) < 1)
      laenge= acosr (vl);
    if (vl >= 1)
      laenge= 0;
    if (vl <= -1)
      laenge= PI;
    if (pdm.x.z > 0)
      laenge= -laenge;
    roll= 0;
    }
  return cvektor3 (laenge, breite, roll);
  }

cvektor4 quaternionfromeulerwinkel (const cvektor3 pflugw)
  {
  cvektor3 wi (pflugw/2);
  cvektor4 q1 (cosr (wi.x), 0, sinr (wi.x), 0);
  cvektor4 q2 (cosr (wi.y), sinr (-wi.y), 0, 0);
  cvektor4 q3 (cosr (wi.z), 0, 0, sinr (-wi.z));
  cvektor4 ret= q1*q2*q3;
  if (ret.r >= 0)
    return ret;
  return -ret;
  }

//-------------------------------------------------------- Polynomberechnung --------------------------------------------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------- quadratisch ------------------------------------------------------------------------------------------------------------------------------------------------------

void quadratisch (ckomplexk a, ckomplexk b, ckomplexk& x1, ckomplexk& x2)
  {
  ckomplexk a2, D;

  a2= a/-2;
  D= sqrtv (a2*a2 - b);

  x1= a2 + D;
  x2= a2 - D;
  }

// ------------------------------------------------------- kubisch ----------------------------------------------------------------------------------------------------------------------------------------------------------

void uvaddition (ckomplexk z1, ckomplexk z2, ckomplexk bed, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3)
  {
  ckomplexk u1, u2, u3, v[3];
  integer   vindex[3];

  // die 3 Lösungen für u, v
  cbrtv (z1, u1, u2, u3);
  cbrtv (z2, v[0], v[2], v[1]);

  // Standardzuordnung der u's und v's (keine Verschiebung)
  vindex[0]= 0;
  vindex[1]= 1;
  vindex[2]= 2;

  // Die Bedingung u*v = bed muss erfüllt sein
  // Die v-Sequenz einen Schritt rückwärts rotieren falls das u[0], v[1] Paar richtig ist
  if ((absv (u1*v[1] - bed) < absv (u1*v[0] - bed)) && (absv (u1*v[1] - bed) < absv (u1*v[2] - bed)))
    {
    vindex[0]= 1;
    vindex[1]= 2;
    vindex[2]= 0;
    }

  // Die v-Sequenz um einen Schritt vorwärts rotieren falls das u[0], v[2] Paar richtig ist
  if ((absv (u1*v[2] - bed) < absv (u1*v[0] - bed)) && (absv (u1*v[2] - bed) < absv (u1*v[1] - bed)))
    {
    vindex[0]= 2;
    vindex[1]= 0;
    vindex[2]= 1;
    }

  // Bestimmung der Summen durch Addition der korrekt zueinander verschobenen u- und v-Sequenzen
  y1= (u1 + v[vindex[0]]);
  y2= (u2 + v[vindex[1]]);
  y3= (u3 + v[vindex[2]]);
  }

void kubischreduziertcardano (ckomplexk p, ckomplexk q, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3)
  {
  ckomplexk u1, u2;

  quadratisch (q, p*p*p/-27, u1, u2);
  uvaddition (u1, u2, -p, y1, y2, y3);
  }

void kubischreduziertcardano3 (ckomplexk p, ckomplexk q, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3)
  {
  ckomplexk u1, u2;

  quadratisch (q*27, p*p*p*-27, u1, u2);
  uvaddition (u1, u2, p*-3, y1, y2, y3);
  }

void kubischreduziertu (ckomplexk p, ckomplexk q, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3)
  {
  ckomplexk  u1, u2, u, z1, z2, z3;

  quadratisch (q, p*p*p/-27, u1, u2);

  if (absv (u1) >= absv (u2))                                     // die betragsmäßig größere Lösung nehmen um von der Division durch 0 wegzukommen
    cbrtv (u1, z1, z2, z3);
    else
    cbrtv (u2, z1, z2, z3);

  y1= z1 - p/(z1*3);
  y2= z2 - p/(z2*3);
  y3= z3 - p/(z3*3);
  }

void kubischreduziertu3 (ckomplexk p, ckomplexk q, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3)
  {
  ckomplexk  u1, u2, u, z1, z2, z3;

  quadratisch (q*27, p*p*p*-27, u1, u2);

  if (absv (u1) >= absv (u2))                                     // die betragsmäßig größere Lösung nehmen um von der Division durch 0 wegzukommen
    cbrtv (u1, z1, z2, z3);
    else
    cbrtv (u2, z1, z2, z3);

  y1= z1/3 - p/z1;
  y2= z2/3 - p/z2;
  y3= z3/3 - p/z3;
  }

void kubischreduziertreellc (real p, real q, real& y)
  {
  real xl, q2, vxl, l;

  xl= q*q/4 + p*p*p/27;
  if (xl >= 0)
    {
    q2= q/-2;
    vxl= sqrtr (xl);
    y= cbrtr (q2 + vxl) + cbrtr (q2 - vxl);
    }
    else
    {
    l= sqrtr (p*(real (4)/-3));
    y= l*cosr (acosr (q*3/(p*l))/3);
    }
  }

void kubischreduziertreellu (real p, real q, real& y)
  {
  real xl, q2, yt, l;

  xl= q*q/4 + p*p*p/27;
  if (xl >= 0)
    {
    q2= q/-2;
    if (q2 >= 0)
      yt= cbrtr (q2 + sqrtr (xl));
      else
      yt= cbrtr (q2 - sqrtr (xl));
    y= yt - p/(yt*3);
    }
    else
    {
    l= sqrtr (p*(real (4)/-3));
    y= l*cosr (acosr (q*3/(p*l))/3);
    }
  }

void kubischreduziertk (ckomplexk a, ckomplexk b, ckomplexk c, ckomplexk& p, ckomplexk& q)
  {
  p= a*a/-3 + b;
  q= a*(a*a/real (4.5) - b)/3 + c;
  }

void kubisch (ckomplexk a, ckomplexk b, ckomplexk c, ckomplexk& x1, ckomplexk& x2, ckomplexk& x3)
  {
  ckomplexk p, q, y1, y2, y3;
  //real yr;

  kubischreduziertk (a, b, c, p, q);

  //kubischreduziertcardano (p, q, y1, y2, y3);
  kubischreduziertcardano3 (p, q, y1, y2, y3);
  //kubischreduziertu (p, q, y1, y2, y3);
  //kubischreduziertu3 (p, q, y1, y2, y3);
  //kubischreduziertreellu (p.x, q.x, yr);
  //kubischreduziertreellc (p.x, q.x, yr);

  x1= (y1 - a)/3;
  x2= (y2 - a)/3;
  x3= (y3 - a)/3;

  //x1= (yr - a)/3;
  }

//--------------------------------------------------- kubische Resolventen ---------------------------------------------------------------------------------------------------------------------------------------------------------

void kubischeresolventediffp (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& z1, ckomplexk& z2, ckomplexk& z3)
  {
  ckomplexk ak, bk, ck;

  ak= -p;
  bk= r*-4;
  ck= r*p*4 - q*q;

  kubisch (ak, bk, ck, z1, z2, z3);
  }

void kubischeresolventebuch (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& z1, ckomplexk& z2, ckomplexk& z3)
  {
  ckomplexk ak, bk, ck;

  ak= p/-2;
  bk= -r;
  ck= r*p/2 - q*q/8;

  kubisch (ak, bk, ck, z1, z2, z3);
  }

void kubischeresolventepdfw2 (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& z1, ckomplexk& z2, ckomplexk& z3)
  {
  ckomplexk ak, bk, ck;

  ak= p*2;
  bk= p*p - r*4;
  ck= -(q*q);

  kubisch (ak, bk, ck, z1, z2, z3);
  }

void kubischeresolventelagrange (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& z1, ckomplexk& z2, ckomplexk& z3)
  {
  ckomplexk ak, bk, ck;

  ak= p/2;
  bk= p*p/16 - r/4;
  ck= q*q/-64;

  kubisch (ak, bk, ck, z1, z2, z3);
  }

void kubischeresolventez (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& z1, ckomplexk& z2, ckomplexk& z3)
  {
  ckomplexk pk, qk;

  pk= (p*p + r*12)/-3;
  qk= p*(r*36 - p*p)/real (13.5) - q*q;

  kubischreduziertcardano (pk, qk, z1, z2, z3);
  }

void kubischeresolventez3 (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& z1, ckomplexk& z2, ckomplexk& z3)
  {
  ckomplexk pk, qk;

  pk= (p*p + r*12)/-3;
  qk= p*(r*36 - p*p)/real (13.5) - q*q;

  kubischreduziertcardano3 (pk, qk, z1, z2, z3);
  }

// --------------------------------------------  quartischreduziert --------------------------------------------------------------------------------------------------------------------------------------------------------------------

void quartischreduziertdiffpu (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4)
  {
  ckomplexk z1, z2, z3, z, u, v, bed, a1, a2, b1, b2;

  kubischeresolventediffp (p, q, r, z1, z2, z3);

  z= z1;
  u= sqrtv (z - p);

  a1=  u;
  a2= -u;
  b1= (z - q/u)/2;
  b2= (z + q/u)/2;

  quadratisch (a1, b1, y1, y2);
  quadratisch (a2, b2, y3, y4);
  }

void quartischreduziertbuchu (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4)
  {
  ckomplexk z1, z2, z3, z, u, v, bed, a1, a2, b1, b2;

  kubischeresolventebuch (p, q, r, z1, z2, z3);

  z= z3;
  u= sqrtv (z*2 - p);

  a1=  u;
  a2= -u;
  b1= z - q/u/2;
  b2= z + q/u/2;

  quadratisch (a1, b1, y1, y2);
  quadratisch (a2, b2, y3, y4);
  }

void quartischreduziertbuchv (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4)
  {
  ckomplexk z1, z2, z3, z, u, v, bed, a1, a2, b1, b2;

  kubischeresolventebuch (p, q, r, z1, z2, z3);

  z= z2;
  v= sqrtv (z*z - r);

  a1= q/v/-2;
  a2= q/v/2;
  b1= z + v;
  b2= z - v;

  quadratisch (a1, b1, y1, y2);
  quadratisch (a2, b2, y3, y4);
  }

void quartischreduziertbuchf (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4)
  {
  ckomplexk z1, z2, z3, z, u, v, bed, a1, a2, b1, b2;

  kubischeresolventebuch (p, q, r, z1, z2, z3);

  z= z1;
  u= sqrtv (z*2 - p);
  v= sqrtv (z*z - r);

  // Bedingung -2uv = q
  bed= u*v*-2;
  if (absv (bed + q) < absv (bed - q))
    v= -v;

  a1=  u;
  a2= -u;
  b1= z + v;
  b2= z - v;

  quadratisch (a1, b1, y1, y2);
  quadratisch (a2, b2, y3, y4);
  }

void quartischreduziertpdfw2 (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4)
  {
  ckomplexk z1, z2, z3, z, u, a1, a2, b1, b2;

  kubischeresolventepdfw2 (p, q, r, z1, z2, z3);

  z= z1;
  u= sqrtv (z);

  a1=  u;
  a2= -u;
  b1= (z + p - q/u)/2;
  b2= (z + p + q/u)/2;

  quadratisch (a1, b1, y1, y2);
  quadratisch (a2, b2, y3, y4);
  }

void quartischreduziertlagrange (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4)
  {
  ckomplexk z1, z2, z3, u1, u2, u3, bed;

  kubischeresolventelagrange (p, q, r, z1, z2, z3);

  u1= sqrtv (z1);
  u2= sqrtv (z2);
  u3= sqrtv (z3);

  y1=  u1 + u2 + u3;
  y2=  u1 - u2 - u3;
  y3= -u1 + u2 - u3;
  y4= -u1 - u2 + u3;

  // Bedingung: -8*u1*u2*u3 = q
  bed= u1*u2*u3*-8;
  if (absv (bed + q) < absv (bed - q))
    {
    y1= -y1;
    y2= -y2;
    y3= -y3;
    y4= -y4;
    }
  }

void quartischreduziertbuchf3 (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4)
  {
  ckomplexk z1, z2, z3, z, u, v, bed, a1, a2, b1, b2;

  kubischeresolventez3 (p, q, r, z1, z2, z3);

  z= z1;
  u= sqrtv ((z - p*2)/3);
  v= z + p;
  v= sqrtv (v*v - r*36)/6;

  // Bedingung -2uv = q
  bed= u*v*-2;
  if (absv (bed + q) < absv (bed - q))
    v= -v;

  a1=  u;
  a2= -u;
  b1= (z + p)/6 + v;
  b2= (z + p)/6 - v;

  quadratisch (a1, b1, y1, y2);
  quadratisch (a2, b2, y3, y4);
  }

void quartischreduziertpdfw23 (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4)
  {
  ckomplexk z1, z2, z3, z, u, a1, a2, b1, b2;

  kubischeresolventez3 (p, q, r, z1, z2, z3);

  z= z1;
  u= sqrtv ((z - p*2)/3);

  a1=  u;
  a2= -u;
  b1= (z + p)/6 - q/u/2;
  b2= (z + p)/6 + q/u/2;

  quadratisch (a1, b1, y1, y2);
  quadratisch (a2, b2, y3, y4);
  }

void quartischreduziertlagrange3 (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4)
  {
  ckomplexk z1, z2, z3, u1, u2, u3, bed;

  kubischeresolventez3 (p, q, r, z1, z2, z3);

  u1= sqrtv ((z1/2 - p)/6);
  u2= sqrtv ((z2/2 - p)/6);
  u3= sqrtv ((z3/2 - p)/6);

  y1=  u1 + u2 + u3;
  y2=  u1 - u2 - u3;
  y3= -u1 + u2 - u3;
  y4= -u1 - u2 + u3;

  // Bedingung: -8*u1*u2*u3 = q
  bed= u1*u2*u3*-8;
  if (absv (bed + q) < absv (bed - q))
    {
    y1= -y1;
    y2= -y2;
    y3= -y3;
    y4= -y4;
    }
  }

void quartischreduziertk (ckomplexk a, ckomplexk b, ckomplexk c, ckomplexk d, ckomplexk& p, ckomplexk& q, ckomplexk& r)
  {
  p= a*a*3/-8 + b;
  q= a*(a*a - b*4)/8 + c;
  r= a*((a*b - c*4)*16 - a*a*a*3)/256 + d;
  }

void quartisch (ckomplexk a, ckomplexk b, ckomplexk c, ckomplexk d, ckomplexk& x1, ckomplexk& x2, ckomplexk& x3, ckomplexk& x4)
  {
  ckomplexk p, q, r, y1, y2, y3, y4, a4;

  quartischreduziertk (a, b, c, d, p, q, r);

  //quartischreduziertdiffpu (p, q, r, y1, y2, y3, y4);
  //quartischreduziertbuchu (p, q, r, y1, y2, y3, y4);
  //quartischreduziertbuchv (p, q, r, y1, y2, y3, y4);
  //quartischreduziertbuchf (p, q, r, y1, y2, y3, y4);
  //quartischreduziertpdfw2 (p, q, r, y1, y2, y3, y4);
  //quartischreduziertlagrange (p, q, r, y1, y2, y3, y4);
  //quartischreduziertbuchf3 (p, q, r, y1, y2, y3, y4);
  //quartischreduziertpdfw23 (p, q, r, y1, y2, y3, y4);
  quartischreduziertlagrange3 (p, q, r, y1, y2, y3, y4);

  a4= a/4;
  x1= y1 - a4;
  x2= y2 - a4;
  x3= y3 - a4;
  x4= y4 - a4;
  }

//-------------------- quartisch integriert ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void quartischdiffpuintrc (real aq, real bq, real cq, real dq, ckomplexk& x1, ckomplexk& x2, ckomplexk& x3, ckomplexk& x4)
  {
  real aqq, pq, qq, rq, pqq, rq4, pk, qk, aq4;
  ckomplexk ytk, yk, u, v, d, D1, D2;

  // Parameter reduzierte quartische Gleichung
  aqq= aq*aq/8;
  pq= aqq*-3 + bq;
  qq= aq*(aqq + bq/-2) + cq;
  rq= aq*(aq*aqq*(real (3)/-32) + aq*bq/16 + cq/-4) + dq;

  // Parameter reduzierte kubische Gleichung
  pqq= pq*pq;
  rq4= rq*4/-3;
  pk= pqq/-9 + rq4;
  qk= pq*(pqq/27 + rq4) + qq*qq/2;

  // Lösung der reduzierten kubischen Gleichung
  ytk= cbrtv (qk + sqrtv (ckomplexk (pk*pk*pk + qk*qk)));
  yk= (ytk - pk/ytk)/4;

  // Lösungen der beiden quadratischen Gleichungen
  u= sqrtv (yk + pq/-6);
  v= qq/u/4;
  d= pq/-3 - yk;

  D1= sqrtv (d + v);
  D2= sqrtv (d - v);

  // Lösungen der normalen quartischen Gleichung
  aq4= aq/-4;
  x1= aq4 - u - D1;
  x2= aq4 - u + D1;
  x3= aq4 + u - D2;
  x4= aq4 + u + D2;
  }

void quartischdiffpuintr (real aq, real bq, real cq, real dq, cschnittpunkte& psp)
  {
  real aqq, pq, qq, rq, pqq, rq4, pk, qk, xl, ytk, yk, l, pq6, z, uq, u, v, b1, b2, aq4, D, x1, x2, x3, x4;

  // Parameter reduzierte quartische Gleichung
  aqq= aq*aq/8;
  pq= aqq*-3 + bq;
  qq= aq*(aqq + bq/-2) + cq;
  rq= aq*(aq*aqq*(real (3)/-32) + aq*bq/16 + cq/-4) + dq;

  // Parameter reduzierte kubische Gleichung
  pqq= pq*pq;
  rq4= rq*4/-3;
  pk= pqq/-9 + rq4;
  qk= pq*(pqq/27 + rq4) + qq*qq/2;

  // reelle Lösung der kubischen Resolvente
  xl= pk*pk*pk + qk*qk;
  if (xl >= 0)                                                    // 2 oder 0 Schnittpunkte mit dem Torus
    {
    //vxl= sqrtr (xl);                                              // Cardano-Berechnung langsamer, weil 2 Kubikwurzeln berechnet werden müssen
    //yk= (cbrtr (qk + vxl) + cbrtr (qk - vxl))/2;                  // außerdem zusätzliche Stern-Artefakte beim Torus
    if (qk >= 0)                                                  // Fallunterscheidung notwendig, sonst zusätzliche Stern-Artefakte beim Torus
      ytk= cbrtr (qk + sqrtr (xl));
      else
      ytk= cbrtr (qk - sqrtr (xl));                               // qk ist immer ungleich 0 somit keine Auslöschung bei xl = 0
    yk= (ytk - pk/ytk)/2;                                         // ytk = 0 ausgeschlossen, da Auslöschung verhindert
    }
    else                                                          // 4 Schnittpunkte mit dem Torus
    {
    l= sqrtr (-pk);
    yk= l*cosr (acosr (qk/(pk*-l))/3);                            // pk*l = 0 garnicht, qk/(pk*l) > 1 sehr selten, qk/(pk*l) < -1 garnicht
    }

  // Lösungen der beiden quadratischen Gleichungen (ak=-pq für Rückreduzierung)
  pq6= pq/6;
  z= yk + pq6;

  uq= yk/2 - pq6;
  u= sqrtr (uq);                                                  // u > 0 wegen Ungenauigkeit, Abfangen bringt nur rote Fehlerpixel
  v= qq/u/4;

  b1= z - v;
  b2= z + v;

  // Lösungen normale quartische Gleichung
  aq4= aq/-4;
  if (uq >= b1)
    {
    D= sqrtr (uq - b1);
    x1= aq4 - u - D;
    x2= aq4 - u + D;
    if (x1 > 0)
      psp.add (x1);
    if (x2 > 0)
      psp.add (x2);
    }
  if (uq >= b2)
    {
    D= sqrtr (uq - b2);
    x3= aq4 + u - D;
    x4= aq4 + u + D;
    if (x3 > 0)
      psp.add (x3);
    if (x4 > 0)
      psp.add (x4);
    }
  }

void quartischdiffpvintr (real aq, real bq, real cq, real dq, cschnittpunkte& psp)
  {
  real aqq, pq, qq, rq, pqq, rq4, pk, qk, xl, ytk, yk, l, z, v, u, uq, b1, b2, aq4, D, x1, x2, x3, x4;

  // Parameter reduzierte quartische Gleichung
  aqq= aq*aq/8;
  pq= aqq*-3 + bq;
  qq= aq*(aqq + bq/-2) + cq;
  rq= aq*(aq*aqq*(real (3)/-32) + aq*bq/16 + cq/-4) + dq;

  // Parameter reduzierte kubische Gleichung
  pqq= pq*pq;
  rq4= rq*4/-3;
  pk= pqq/-9 + rq4;
  qk= pq*(pqq/27 + rq4) + qq*qq/2;

  // reelle Lösung der kubischen Resolvente
  xl= pk*pk*pk + qk*qk;
  if (xl >= 0)                                                    // 2 oder 0 Schnittpunkte mit dem Torus
    {
    //vxl= sqrtr (xl);                                              // Cardano-Berechnung langsamer, weil 2 Kubikwurzeln berechnet werden müssen
    //yk= (cbrtr (qk + vxl) + cbrtr (qk - vxl))/2;                  // außerdem zusätzliche Stern-Artefakte beim Torus
    if (qk >= 0)                                                  // Fallunterscheidung notwendig, sonst zusätzliche Stern-Artefakte beim Torus
      ytk= cbrtr (qk + sqrtr (xl));
      else
      ytk= cbrtr (qk - sqrtr (xl));                               // qk ist immer ungleich 0 somit keine Auslöschung bei xl = 0
    yk= (ytk - pk/ytk)/2;                                         // ytk = 0 ausgeschlossen, da Auslöschung verhindert
    }
    else                                                          // 4 Schnittpunkte mit dem Torus
    {
    l= sqrtr (-pk);
    yk= l*cosr (acosr (qk/(pk*-l))/3);                            // pk*l = 0 garnicht, qk/(pk*l) > 1 sehr selten, qk/(pk*l) < -1 garnicht
    }

  // Lösungen der beiden quadratischen Gleichungen (ak=-pq/2 für Rückreduzierung)
  z= yk + pq/6;

  v= sqrtr (z*z - rq);                                            // zzrq < 0 wegen Ungenauigkeit, abfangen bringt nur rote Fehlerpixel
  u= qq/v/4;
  uq= u*u;

  b1= z + v;
  b2= z - v;

  // Lösungen normale quartische Gleichung
  aq4= aq/-4;
  if (uq >= b1)
    {
    D= sqrtr (uq - b1);
    x1= aq4 + u - D;
    x2= aq4 + u + D;
    if (x1 > 0)
      psp.add (x1);
    if (x2 > 0)
      psp.add (x2);
    }
  if (uq >= b2)
    {
    D= sqrtr (uq - b2);
    x3= aq4 - u - D;
    x4= aq4 - u + D;
    if (x3 > 0)
      psp.add (x3);
    if (x4 > 0)
      psp.add (x4);
    }
  }

void quartischdiffpfintr (real aq, real bq, real cq, real dq, cschnittpunkte& psp)
  {
  real aqq, pq, qq, rq, pqq, rq4, pk, qk, xl, ytk, yk, l, pq6, z, uq, u, v, bed, b1, b2, aq4, D, x1, x2, x3, x4;

  // Parameter reduzierte quartische Gleichung
  aqq= aq*aq/8;
  pq= aqq*-3 + bq;
  qq= aq*(aqq + bq/-2) + cq;
  rq= aq*(aq*aqq*(real (3)/-32) + aq*bq/16 + cq/-4) + dq;

  // Parameter reduzierte kubische Gleichung
  pqq= pq*pq;
  rq4= rq*4/-3;
  pk= pqq/-9 + rq4;
  qk= pq*(pqq/27 + rq4) + qq*qq/2;

  // reelle Lösung der kubischen Resolvente
  xl= pk*pk*pk + qk*qk;
  if (xl >= 0)                                                    // 2 oder 0 Schnittpunkte mit dem Torus
    {
    //vxl= sqrtr (xl);                                              // Cardano-Berechnung langsamer, weil 2 Kubikwurzeln berechnet werden müssen
    //yk= (cbrtr (qk + vxl) + cbrtr (qk - vxl))/2;                  // außerdem zusätzliche Stern-Artefakte beim Torus
    if (qk >= 0)                                                  // Fallunterscheidung notwendig, sonst zusätzliche Stern-Artefakte beim Torus
      ytk= cbrtr (qk + sqrtr (xl));
      else
      ytk= cbrtr (qk - sqrtr (xl));                               // qk ist immer ungleich 0 somit keine Auslöschung bei xl = 0
    yk= (ytk - pk/ytk)/2;                                         // ytk = 0 ausgeschlossen, da Auslöschung verhindert
    }
    else                                                          // 4 Schnittpunkte mit dem Torus
    {
    l= sqrtr (-pk);
    yk= l*cosr (acosr (qk/(pk*-l))/3);                            // pk*l = 0 garnicht, qk/(pk*l) > 1 sehr selten, qk/(pk*l) < -1 garnicht
    }

  // Lösungen der beiden quadratischen Gleichungen (ak=-pq/2 für Rückreduzierung)
  pq6= pq/6;
  z= yk + pq6;

  uq= yk/2 - pq6;
  u= sqrtr (uq);                                                  // u > 0 wegen Ungenauigkeit, Abfangen bringt nur rote Fehlerpixel
  v= sqrtr (z*z - rq);                                            // zzrq < 0 wegen Ungenauigkeit, abfangen bringt nur rote Fehlerpixel

  // Bedingung -2uv = qq
  bed= u*v*-2;
  if (fabsr (bed + qq) < fabsr (bed - qq))
    {
    b1= z - v;
    b2= z + v;
    }
    else
    {
    b1= z + v;
    b2= z - v;
    }

  // Lösungen normale quartische Gleichung
  aq4= aq/-4;
  if (uq >= b1)
    {
    D= sqrtr (uq - b1);
    x1= aq4 - u - D;
    x2= aq4 - u + D;
    if (x1 > 0)
      psp.add (x1);
    if (x2 > 0)
      psp.add (x2);
    }
  if (uq >= b2)
    {
    D= sqrtr (uq - b2);
    x3= aq4 + u - D;
    x4= aq4 + u + D;
    if (x3 > 0)
      psp.add (x3);
    if (x4 > 0)
      psp.add (x4);
    }
  }

void quartischbuchfintr (real aq, real bq, real cq, real dq, cschnittpunkte& psp)
  {
  real aqq, pq, qq, rq, pqq, pk, qk, xl, ytk, yk, l, pq6, z, uq, u, v, bed, b1, b2, aq4, D, x1, x2, x3, x4;

  // Parameter reduzierte quartische Gleichung
  aqq= aq*aq/8;
  pq= aqq*-3 + bq;
  qq= aq*(aqq + bq/-2) + cq;
  rq= aq*(aq*aqq*(real (3)/-32) + aq*bq/16 + cq/-4) + dq;

  // Parameter reduzierte kubische Gleichung
  pqq= pq*pq;
  pk= pqq/-36 + rq/-3;
  qk= pq*(pqq/216 + rq/-6) + qq*qq/16;

  // reelle Lösung der kubischen Resolvente
  xl= pk*pk*pk + qk*qk;
  if (xl >= 0)                                                    // 2 oder 0 Schnittpunkte mit dem Torus
    {
    //vxl= sqrtr (xl);                                              // Cardano-Berechnung langsamer, weil 2 Kubikwurzeln berechnet werden müssen
    //yk= (cbrtr (qk + vxl) + cbrtr (qk - vxl));                    // außerdem zusätzliche Stern-Artefakte beim Torus
    if (qk >= 0)                                                  // Fallunterscheidung notwendig, sonst zusätzliche Stern-Artefakte beim Torus
      ytk= cbrtr (qk + sqrtr (xl));
      else
      ytk= cbrtr (qk - sqrtr (xl));                               // qk ist immer ungleich 0 somit keine Auslöschung bei xl = 0
    yk= (ytk - pk/ytk);                                           // ytk = 0 ausgeschlossen, da Auslöschung verhindert
    }
    else                                                          // 4 Schnittpunkte mit dem Torus
    {
    l= sqrtr (-pk);
    yk= l*cosr (acosr (qk/(pk*-l))/3)*2;                          // pk*l = 0 garnicht, qk/(pk*l) > 1 sehr selten, qk/(pk*l) < -1 garnicht
    }

  // Lösungen der beiden quadratischen Gleichungen (ak=-pq/2 für Rückreduzierung)
  pq6= pq/6;
  z= yk + pq6;

  uq= yk/2 - pq6;
  u= sqrtr (uq);                                                  // u > 0 wegen Ungenauigkeit, Abfangen bringt nur rote Fehlerpixel
  v= sqrtr (z*z - rq);                                            // zzrq < 0 wegen Ungenauigkeit, abfangen bringt nur rote Fehlerpixel

  // Bedingung -2uv = qq
  bed= u*v*-2;
  if (fabsr (bed + qq) < fabsr (bed - qq))
    {
    b1= z - v;
    b2= z + v;
    }
    else
    {
    b1= z + v;
    b2= z - v;
    }

  // Lösungen normale quartische Gleichung
  aq4= aq/-4;
  if (uq >= b1)
    {
    D= sqrtr (uq - b1);
    x1= aq4 - u - D;
    x2= aq4 - u + D;
    if (x1 > 0)
      psp.add (x1);
    if (x2 > 0)
      psp.add (x2);
    }
  if (uq >= b2)
    {
    D= sqrtr (uq - b2);
    x3= aq4 + u - D;
    x4= aq4 + u + D;
    if (x3 > 0)
      psp.add (x3);
    if (x4 > 0)
      psp.add (x4);
    }
  }

void quartischlagrangeuintr (real aq, real bq, real cq, real dq, cschnittpunkte& psp)
  {
  real aqq, pq, qq, rq, pqq, pk, qk, aq4, ak3, qq8, xl, l, phi3, ykr1, ykr2, ykr3, ur1, ur2, ur3, yr1, yr2, yr3, yr4, bed, xr1, xr2, xr3, xr4;
  ckomplexk yk2, u2;

  // Parameter der reduzierten quartischen Gleichung
  aqq= aq*aq/8;
  pq= aqq*-3 + bq;
  qq= aq*(aqq + bq/-2) + cq;
  rq= aq*(aq*aqq*(real (3)/-32) + aq*bq/16 + cq/-4) + dq;

  // Parameter der reduzierten kubischen Gleichung
  pqq= pq*pq;
  pk= pqq/-144 + rq/-12;
  qk= pq*(pqq/1728 + rq/-48) + qq*qq/128;

  // Lösungen der reduzierten kubischen Gleichung
  aq4= aq/-4;
  ak3= pq/-6;
  qq8= qq/8;

  // Lösungen der kubischen Resolvente
  xl= pk*pk*pk + qk*qk;
  if (xl > 0)                                                     // xl= 0: drei reelle Lösungen der kubischen Resolvente davon eine doppelt, 4 reelle Lösungen der quartischen Gleichung davon eine doppelt
    {                                                             // eine reelle, 2 komplexe Lösungen der kubischen Resolvente, 2 reelle Lösungen der quartischen Gleichung
    if (qk >= 0)                                                  // Fallunterscheidung notwendig, sonst zusätzliche Stern-Artefakte beim Torus
      ykr1= cbrtr (qk + sqrtr (xl));
      else
      ykr1= cbrtr (qk - sqrtr (xl));
    yk2= ckomplexk (ykr1/-2, ykr1*sqrtr (real (0.75)));

    ur1= sqrtr (ak3 + ykr1 - pk/ykr1);                            // Rücktransformation von ykr1
    u2= sqrtv (ak3 + yk2 - pk/yk2);                               // Rücktransformation von yk2

    // Lösungen der reduzierten quartischen Gleichung
    yr1=  ur1 + u2.x*2;
    yr2=  ur1 - u2.x*2;

    // Lösungen der normalen quartischen Gleichung
    // Bedingung: 8*u1*u2*u3 = -qq
    bed= ur1*(u2.x*u2.x + u2.y*u2.y);
    if (fabsr (bed + qq8) < fabsr (bed - qq8))
      {
      xr1= aq4 + yr1;
      xr2= aq4 + yr2;
      }
      else
      {
      xr1= aq4 - yr1;
      xr2= aq4 - yr2;
      }

    // die reell-positiven Lösungen an den Schnittpunktspeicher übergeben
    if (xr1 > 0)
      psp.add (xr1);
    if (xr2 > 0)
      psp.add (xr2);
    }
    else
    {
    // 3 reelle Lösungen der kubischen Resolvente, 4 reelle Lösungen der quartischen Gleichung
    l= sqrtr (-pk);                                               // -pk nie unter 0 wegen xl
    phi3= acosr (qk/(pk*-l))/3;
    ykr1= l*cosr (phi3)*2;                                        // Bereichsüberschreitung acos abfangen lohnt nicht, nur ein Wert 1.000000119 (Float32) sehr selten
    ykr2= l*cosr (phi3 + PI23)*2;
    ykr3= l*cosr (phi3 - PI23)*2;

    if ((ak3 + ykr1 < 0) || (ak3 + ykr2 < 0) || (ak3 + ykr3 < 0)) // ist einer der Werte kleiner 0 kommen nur komplexe Lösungen raus
      return;
    ur1= sqrtr (ak3 + ykr2);
    ur2= sqrtr (ak3 + ykr3);
    ur3= sqrtr (ak3 + ykr1);

    // Lösungen der reduzierten quartischen Gleichung
    yr1=  ur1 - ur2 - ur3;
    yr2=  ur2 - ur3 - ur1;
    yr3=  ur3 - ur1 - ur2;
    yr4=  ur1 + ur2 + ur3;

    // Lösungen der normalen quartischen Gleichung
    // Bedingung: 8*u1*u2*u3 = -qq
    bed= ur1*ur2*ur3;
    if (fabsr (bed + qq8) < fabsr (bed - qq8))
      {
      xr1= aq4 + yr1;
      xr2= aq4 + yr2;
      xr3= aq4 + yr3;
      xr4= aq4 + yr4;
      }
      else
      {
      xr1= aq4 - yr4;
      xr2= aq4 - yr3;
      xr3= aq4 - yr2;
      xr4= aq4 - yr1;
      }

    // positive Lösungen an den Schnittpunktspeicher übergeben
    if (xr1 > 0)
      psp.add (xr1);
    if (xr2 > 0)
      psp.add (xr2);
    if (xr3 > 0)
      psp.add (xr3);
    if (xr4 > 0)
      psp.add (xr4);
    }
  }

void quartischlagrangecintr (real aq, real bq, real cq, real dq, cschnittpunkte& psp)
  {
  real aqq, pq, qq, rq, pqq, pk, qk, aq4, ak3, qq8, xl, vxl, uk1, uk2, l, phi3, ykr1, ykr2, ykr3, ur1, ur2, ur3, yr1, yr2, yr3, yr4, bed, xr1, xr2, xr3, xr4;
  ckomplexk yk2, u2;

  // Parameter der reduzierten quartischen Gleichung
  aqq= aq*aq/8;
  pq= aqq*-3 + bq;
  qq= aq*(aqq + bq/-2) + cq;
  rq= aq*(aq*aqq*(real (3)/-32) + aq*bq/16 + cq/-4) + dq;

  // Parameter der reduzierten kubischen Gleichung
  pqq= pq*pq;
  pk= pqq/-144 + rq/-12;
  qk= pq*(pqq/1728 + rq/-48) + qq*qq/128;

  // Lösungen der reduzierten kubischen Gleichung
  aq4= aq/-4;
  ak3= pq/-6;
  qq8= qq/8;

  // Lösungen der kubischen Resolvente
  xl= pk*pk*pk + qk*qk;
  if (xl > 0)                                                     // xl= 0: drei reelle Lösungen der kubischen Resolvente davon eine doppelt, 4 reelle Lösungen der quartischen Gleichung davon eine doppelt
    {
    // eine reelle, 2 komplexe Lösungen der kubischen Resolvente, 2 reelle Lösungen der quartischen Gleichung
    vxl= sqrtr (xl);                                              // xl immer > 0
    uk1= cbrtr (qk - vxl);
    uk2= cbrtr (qk + vxl);
    ykr1= uk1 + uk2;
    yk2= e31*uk1 + e32*uk2;

    ur1= sqrtr (ak3 + ykr1);
    u2= sqrtv (ak3 + yk2);

    // Lösungen der reduzierten quartischen Gleichung
    yr1=  ur1 + u2.x*2;
    yr2=  ur1 - u2.x*2;

    // Lösungen den normalen quartischen Gleichung
    // Bedingung: 8*u1*u2*u3 = -qq
    bed= ur1*(u2.x*u2.x + u2.y*u2.y);
    if (fabsr (bed + qq8) < fabsr (bed - qq8))
      {
      xr1= aq4 + yr1;
      xr2= aq4 + yr2;
      }
      else
      {
      xr1= aq4 - yr1;
      xr2= aq4 - yr2;
      }

    // die reell-positiven Lösungen an den Schnittpunktspeicher übergeben
    if (xr1 > 0)
      psp.add (xr1);
    if (xr2 > 0)
      psp.add (xr2);
    }
    else
    {
    // 3 reelle Lösungen der kubischen Resolvente, 4 reelle Lösungen der quartischen Gleichung
    l= sqrtr (-pk);                                               // -pk nie unter 0 wegen xl
    phi3= acosr (qk/(pk*-l))/3;
    ykr1= l*cosr (phi3)*2;                                        // Bereichsüberschreitung acos abfangen lohnt nicht, nur ein Wert 1.000000119 (Float32) sehr selten
    ykr2= l*cosr (phi3 + PI23)*2;
    ykr3= l*cosr (phi3 - PI23)*2;

    if ((ak3 + ykr1 < 0) || (ak3 + ykr2 < 0) || (ak3 + ykr3 < 0)) // ist einer der Werte kleiner 0 kommen nur komplexe Lösungen raus
      return;
    ur1= sqrtr (ak3 + ykr2);
    ur2= sqrtr (ak3 + ykr3);
    ur3= sqrtr (ak3 + ykr1);

    // Lösungen der reduzierten quartischen Gleichung
    yr1=  ur1 - ur2 - ur3;
    yr2=  ur2 - ur3 - ur1;
    yr3=  ur3 - ur1 - ur2;
    yr4=  ur1 + ur2 + ur3;

    // Lösungen der normalen quartischen Gleichung
    // Bedingung: 8*u1*u2*u3 = -qq
    bed= ur1*ur2*ur3;
    if (fabsr (bed + qq8) < fabsr (bed - qq8))
      {
      xr1= aq4 + yr1;
      xr2= aq4 + yr2;
      xr3= aq4 + yr3;
      xr4= aq4 + yr4;
      }
      else
      {
      xr1= aq4 - yr4;
      xr2= aq4 - yr3;
      xr3= aq4 - yr2;
      xr4= aq4 - yr1;
      }

    // positive Lösungen an den Schnittpunktspeicher übergeben
    if (xr1 > 0)
      psp.add (xr1);
    if (xr2 > 0)
      psp.add (xr2);
    if (xr3 > 0)
      psp.add (xr3);
    if (xr4 > 0)
      psp.add (xr4);
    }
  }

