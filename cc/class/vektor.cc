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
#include "../../conio/vektorcon.h"      // zum Debuggen (eingabe, printtext, printinteger, printreal)

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

ckomplexk::ckomplexk (const cvektor2 &pv)
  : cvektor2 (pv) {}

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
  switch (a >= b)
    {
    case false: return b;
    case true:  return a;
    }
  }

void savemax (integer& pmax, integer pr)
  {
  pmax= max (pmax, pr);
  }

//--------------------- real Funktionen -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------ finiter ---------------------------------------------------------------------------
integer finiter (const _Float32& a)
  {
  return finitef (a);
  }

integer finiter (const _Float64& a)
  {
  return finite (a);
  }

integer finiter (const _Float80& a)
  {
  return finitel (a);
  }

//------------------------------------------------------------------------------------ fmodr ------------------------------------------------------------------------
_Float32 modr (const _Float32& a, const _Float32& b)
  {
  return fmodf (a, b);
  }

_Float64 modr (const _Float64& a, const _Float64& b)
  {
  return fmod (a, b);
  }

_Float80 modr (const _Float80& a, const _Float80& b)
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

_Float80 floorr (const _Float80& a)
  {
  return floorl (a);
  }

//------------------------------------------------------------------------------------ absr ---------------------------------------------------------------------------
_Float32 absr (const _Float32& a)
  {
  return fabsf (a);
  }

_Float64 absr (const _Float64& a)
  {
  return fabs (a);
  }

_Float80 absr (const _Float80& a)
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

_Float80 sqrtr (const _Float80& a)
  {
  return sqrtl (a);
  }

//------------------------------------------------------------------------------------ sqrtrz ------------------------------------------------------------------------
_Float32 sqrtrz (const _Float32& a)
  {
  if (a > 0)
    /**/ return sqrtf (a);
    else return 0;
  }

_Float64 sqrtrz (const _Float64& a)
  {
  if (a > 0)
    /**/ return sqrt (a);
    else return 0;
  }

_Float80 sqrtrz (const _Float80& a)
  {
  if (a > 0)
    /**/ return sqrtl (a);
    else return 0;
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

_Float80 cbrtr (const _Float80& a)
  {
  return cbrtl (a);
  }

//------------------------------------------------------------------------------------ qnrtr ------------------------------------------------------------------------
_Float32 qnrtr (const _Float32& a)
  {
  if (a >= 0)
    /**/ return  powf ( a, _Float32 (0.2));
    else return -powf (-a, _Float32 (0.2));
  }

_Float64 qnrtr (const _Float64& a)
  {
  if (a >= 0)
    /**/ return  pow ( a, _Float64 (0.2));
    else return -pow (-a, _Float64 (0.2));
  }

_Float80 qnrtr (const _Float80& a)
  {
  if (a >= 0)
    /**/ return  powl ( a, (_Float80) (0.2));
    else return -powl (-a, (_Float80) (0.2));
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

_Float80 expr (const _Float80& a)
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

_Float80 logr (const _Float80& a)
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

_Float80 powr (const _Float80& a, const _Float80& b)
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

_Float80 sinr (const _Float80& a)
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

_Float80 cosr (const _Float80& a)
  {
  return cosl (a);
  }

//------------------------------------------------------------------------------------ tanr ------------------------------------------------------------------------
_Float32 tanr (const _Float32& a)
  {
  return tanf (a);
  }

_Float64 tanr (const _Float64& a)
  {
  return tan (a);
  }

_Float80 tanr (const _Float80& a)
  {
  return tanl (a);
  }

//------------------------------------------------------------------------------------ sinhr ------------------------------------------------------------------------
_Float32 sinhr (const _Float32& a)
  {
  return sinhf (a);
  }

_Float64 sinhr (const _Float64& a)
  {
  return sinh (a);
  }

_Float80 sinhr (const _Float80& a)
  {
  return sinhl (a);
  }

//------------------------------------------------------------------------------------ coshr ------------------------------------------------------------------------
_Float32 coshr (const _Float32& a)
  {
  return coshf (a);
  }

_Float64 coshr (const _Float64& a)
  {
  return cosh (a);
  }

_Float80 coshr (const _Float80& a)
  {
  return coshl (a);
  }

//------------------------------------------------------------------------------------ tanhr ------------------------------------------------------------------------
_Float32 tanhr (const _Float32& a)
  {
  return tanhf (a);
  }

_Float64 tanhr (const _Float64& a)
  {
  return tanh (a);
  }

_Float80 tanhr (const _Float80& a)
  {
  return tanhl (a);
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

_Float80 asinr (const _Float80& a)
  {
  return asinl (a);
  }

//------------------------------------------------------------------------------------ acosr ------------------------------------------------------------------------
_Float32 acosr (const _Float32& a)
  {
  if (a >= 1) return 0;
  if (a <= -1) return M_PIf;
  return acosf (a);
  }

_Float64 acosr (const _Float64& a)
  {
  if (a >= 1) return 0;
  if (a <= -1) return M_PI;
  return acos (a);
  }

_Float80 acosr (const _Float80& a)
  {
  if (a >= 1) return 0;
  if (a <= -1) return M_PIl;
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

_Float80 atanr (const _Float80& a)
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

_Float80 atan2r (const _Float80& a, const _Float80& b)
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

_Float80 asinhr (const _Float80& a)
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

_Float80 acoshr (const _Float80& a)
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

_Float80 atanhr (const _Float80& a)
  {
  return atanhl (a);
  }

//--------------------- cvektor2 Vektor Funktionen ------------------------------------------------------------------------------------------------------------------------------------------------

real absr (const cvektor2 pv)
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
bool operator == (const cvektor2 &pv1, const cvektor2 &pv2)
  {
  return (pv1.x == pv2.x) && (pv1.y == pv2.y);
  }

bool operator != (const cvektor2 &pv1, const cvektor2 &pv2)
  {
  return (pv1.x != pv2.x) || (pv1.y != pv2.y);
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

// -------------------------------------------------- komplexer Kehrwert
ckomplexk kw (const ckomplexk pv)
  {
  real z= pv%pv;
  return ckomplexk (pv.x, -pv.y)/z;
  }

// -------------------------------------------------- Quadratwurzel
ckomplexk sqrtr (const ckomplexk pv)
  {
  real l, x, y;

  l= sqrtr (pv.x*pv.x + pv.y*pv.y);
  x= sqrtr ((l + pv.x)/2);
  y= sqrtr ((l - pv.x)/2);

  if (pv.y >= 0)
    /**/ return ckomplexk (x, y);
    else return ckomplexk (x, -y);
  }

ckomplexk sqrtkr (const ckomplexk pv)
  {
  ckomplexp vpol= polar180 (pv);
  vpol.b= sqrtr (vpol.b);
  vpol.w= vpol.w/2;
  return kartes (vpol);
  }

// -------------------------------------------------- Kubikwurzel
ckomplexk cbrtr (const ckomplexk pv)
  {
  ckomplexp vpol= polar180 (pv);
  vpol.b= cbrtr (vpol.b);
  vpol.w= vpol.w/3;
  return kartes (vpol);
  }

void cbrtr (const ckomplexk pv, ckomplexk& x1, ckomplexk& x2, ckomplexk& x3)
  {
  x1= cbrtr (pv);
  x2= x1*e31;
  x3= x1*e32;
  }

// -------------------------------------------------- vierte Wurzel
ckomplexk qartr (const ckomplexk pv)
  {
  ckomplexp vpol= polar180 (pv);
  vpol.b= powr (vpol.b, real (0.25));
  vpol.w= vpol.w/4;
  return kartes (vpol);
  }

// -------------------------------------------------- fünfte Wurzel
ckomplexk qnrtr (const ckomplexk pv)
  {
  ckomplexp vpol= polar180 (pv);
  vpol.b= powr (vpol.b, real (0.2));
  vpol.w= vpol.w/5;
  return kartes (vpol);
  }

// -------------------------------------------------- n-te Potenz rekursiv
ckomplexk pown (const ckomplexk a, const integer n)
  {
  ckomplexk ret= 1;

  for (integer lauf= 0; lauf < n; lauf++)
    ret= ret*a;
  return ret;
  }

// -------------------------------------------------- z hoch z
ckomplexk powr (const ckomplexk pv1, const ckomplexk pv2)
  {
  ckomplexk ret, retx, rety;

  retx= pv1^pv2.x;
  rety= cosr (logr (pv1)*pv2.y) + ik*sinr (logr (pv1)*pv2.y);
  return retx*rety;
  }

// -------------------------------------------------- Exponentialfunktion
ckomplexk expr (const ckomplexk pv)
  {
  return kartes (ckomplexp (expr (pv.x), (pv.y)));                // keine Einschränkung Bijektivitätsbereich
  }

ckomplexk logr (const ckomplexk pv)                               // Rückgabe eingeschränkt auf waagerechten ]-pi, pi] Streifen
  {
  ckomplexp lv= polar180 (pv);
  if (lv.b > 0)
    /**/ lv.b= logr (lv.b);
    else lv.b= real (-1e10);
  return ckomplexk (lv.b, lv.w);
  }

ckomplexk coshr (const ckomplexk pv)
  {
  return (expr (pv) + expr (-pv))/2;
  }

ckomplexk sinhr (const ckomplexk pv)
  {
  return (expr (pv) - expr (-pv))/2;
  }

ckomplexk cosr (const ckomplexk pv)
  {
  return (expr (pv*ik) + expr (-pv*ik))/2;
  }

ckomplexk sinr (const ckomplexk pv)
  {
  return ik*(expr (pv*ik) - expr (-pv*ik))/-2;
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
  ckomplexk ret= 1;
  integer bpn= llabs (pn);

  for (integer lauf= 0; lauf < bpn; lauf++)
    ret= ret*pv;

  if (pn >= 0)
    /**/ return ret;
    else return kw (ret);
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
  return expr (pv2*logr (pv1));                                   // Bijektivitätsbereich: waagerechter ]-pi,pi] Streifen in der rechten Halbebene ohne y-Achse
  }

//--------------------- ckomplexp Funktionen für polarkomplexe Zahlen -----------------------------------------------------------------

// komplexer Kehrwert
ckomplexp kw (const ckomplexp pv)
  {
  return ckomplexp (1/pv.b, -pv.w);
  }

ckomplexp sqrtr (const ckomplexp pv)
  {
  return ckomplexp (sqrtr (pv.b), pv.w/2);
  }

ckomplexp cbrtr (const ckomplexp pv)
  {
  return ckomplexp (cbrtr (pv.b), pv.w/3);
  }

ckomplexp expr (const ckomplexp pv)
  {
  return ckomplexp (expr (pv.b), (pv.w));
  }

ckomplexp logr (const ckomplexp pv)
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
  return (expr (pv) + expr (ew2*pv))/2;
  }

ckomplexp sinhr (const ckomplexp pv)
  {
  return (expr (pv) - expr (ew2*pv))/2;
  }

ckomplexp cosr (const ckomplexp pv)
  {
  return (expr (pv*ew4) + expr (pv/ew4))/2;
  }

ckomplexp sinr (const ckomplexp pv)
  {
  return (expr (pv*ew4) - expr (pv/ew4))/ew4/2;
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
    if (pv.w <= 0)
      /**/ return ckomplexp (-pf*pv.b, pv.w + PI);
      else return ckomplexp (-pf*pv.b, pv.w - PI);
  }

// Skalardivision
ckomplexp operator / (const ckomplexp &pv, const real &pf)
  {
  if (pf >= 0)
    return ckomplexp (pv.b/pf, pv.w);
    else
    if (pv.w <= 0)
      /**/ return ckomplexp (-pv.b/pf, pv.w + PI);
      else return ckomplexp (-pv.b/pf, pv.w - PI);
  }

// Skalar durch polarkomplexe Zahl
ckomplexp operator / (const real &pf, const ckomplexp &pv)
  {
  if (pf >= 0)
    return ckomplexp (pf/pv.b, -pv.w);
    else
    if (pv.w >= 0)
      /**/ return ckomplexp (-pf/pv.b,  PI - pv.w);
      else return ckomplexp (-pf/pv.b, -PI - pv.w);
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
  return expr (pv2*logr (pv1));                                   // problematisch wegen Periodizität der exp, log Funktion

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
  return absr (atan2r (pv.y, pv.x));
  }

ckomplexk kartes (const ckomplexp pv)
  {
  return ckomplexk (pv.b*cosr (pv.w), pv.b*sinr (pv.w));
  }

ckomplexp polar225 (const ckomplexk pv)                           // Winkelrückgabe [0, 2pi[
  {
  ckomplexp ret= polar180 (pv);

  if (ret.w < -PI3v)
    ret.w= ret.w + PI2;
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
  return ckomplexp (absr (pv), atan2r (pv.y, pv.x));
  }

ckomplexp polarcos180 (const ckomplexk pv)                        // Winkelrückgabe ]-pi, pi]
  {
  real phi= 0;
  real laenge (absr (pv));
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

  if (absr (pv.x) > absr (pv.y))                                  // pv.x = 0 geht weiter
    {
    phi= atanr (pv.y/pv.x);
    if (pv.x < 0)
      {                                                           // Klammer wegen ambigious else
      if (pv.y >= 0)  // 180° statt -180°
        /**/ phi+= PI;
        else phi-= PI;
      }
    return ckomplexp (absr (pv), phi);
    }

  if (absr (pv.x) < absr (pv.y))  // pv.y = 0 geht weiter
    {
    phi= atanr (pv.x/pv.y);

    if (pv.y >= 0)
      /**/ phi= PI/2 - phi;
      else phi= PI/-2 - phi;
    return ckomplexp (absr (pv), phi);
    }

    if (absr (pv.x) == 0)                                        // Die Beträge von x und y sind ab dieser Stelle gleich deshalb ist pv der Nullvektor
      return (ckomplexp (0, 0));

    if (pv.x < 0)                                                 // linke Hälfte also +-135°
      phi= PI*real (0.75);

    if (pv.y < 0)                                                 // untere Hälfte also -45° oder -135°
      phi= -phi;

  return ckomplexp (absr (pv), phi);
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

real absr (const cvektor3 &pv)
  {
  return sqrtr (pv%pv);
  }

// Kreuzfunktion: unärer Operator, senkrechten Vektor in positver Orientierung ermitteln: kürzeste Komponente Null setzen, die anderen beiden senkrechtisieren
cvektor3 senk (const cvektor3 &pv)
  {
  if ((absr (pv.x) <= absr (pv.y)) && (absr (pv.x) <= absr (pv.z)))
    return cvektor3 (0, -pv.z, pv.y);
  if (absr (pv.y) <= absr (pv.z))
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
  if (absr (ret.x) <= quantg)
    {
    ret.x= 0;
    if (ret.y < 0)
      ret= -ret;
    if (absr (ret.y) <= quantg)
      {
      ret.y= 0;
      if (ret.z < 0)
        ret= -ret;
      if (absr (ret.z) <= quantg)
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
  return acosr (absr ((pv1%pv2)/sqrtr ((pv1%pv1)*(pv2%pv2))));
  }

//---------- cvektor3 Operatoren ------------------------------------------------------------------------------------------

// Vektoren vergleichen
bool operator == (const cvektor3 &pv1, const cvektor3 &pv2)
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
  if ((absr (pv.x) < absr (pv.y)) && (absr (pv.x) < absr (pv.z)))
    return cvektor3 (0, pv.z, -pv.y);
  if (absr (pv.y) < absr (pv.z))
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
  return (pb.x%pb.x) + (pb.y%pb.y) + (pb.z%pb.z);
  }

real absr (cbasis3 pb)
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
  if (absr (pv) <= quantg)                                         // Nullvektor als Spiegelachse ist Punktspiegelung also Inversionsmatrix zurückgeben
    return cbasis3 (-1);
  cvektor3 nv= normiere (pv);
  return cbasis3 (1) - 2*cbasis3 (nv, nv, nv)*cbasis3 (nv);
  }

// Spiegelungsmatrix aus (Drehung von 180° um Spiegelachse) berechnen
cbasis3 getdrehspiegbasis (const cvektor3 &pv)
  {
  if (absr (pv) <= quantg)                                         // Nullvektor als Spiegelachse ist Punktspiegelung also Inversionsmatrix zurückgeben
    return cbasis3 (-1);
  return -matrixfromwinkelachse (cvektor4 (PI, pv.x, pv.y, pv.z));
  }

cvektor3 getspiegachse (const cbasis3 &pb)
  {
  return normiere (geteigen (pb + cbasis3 (1)));
  }

integer aehnlich (const cbasis3 &pb1, const cbasis3 &pb2)
  {
  real dif= absr (pb1 - pb2);
  /*
  printbasis3dreh (pb1, 0, 0, 0);
  printbasis3dreh (pb2, 0, 0, 0);
  printf ("dif: %Lf\n", dif);
  getchar ();
  */
  if (dif <= quantg)
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

real absr (const cvektor4 &pv)
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
  if (q <= quantg)
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
  real dif= absr (pv1 - pv2);
  if (dif <= quantg)
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
bool operator == (const cvektor4 &pv1, const cvektor4 &pv2)
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
  if (pq.r >= 1 - quantg)
    return cvektor4 (0, 0, 0, 0);
  if (pq.r <= -1 + quantg)
    return cvektor4 (2*PI, 0, 0, 0);
  real drehw= acosr (pq.r)*2;
  cvektor3 achse (normiere (cvektor3 (pq.i, pq.j, pq.ij)));
  if (absr (achse.x) <= quantg)
    achse.x= 0;
  if (absr (achse.y) <= quantg)
    achse.y= 0;
  if (absr (achse.z) <= quantg)
    achse.z= 0;
  return cvektor4 (drehw, achse.x, achse.y, achse.z);
  }

cvektor4 qwafrommatrix (const cbasis3 &pdreh)                     // nur für Drehmatrizen, nicht für Drehspiegelungsmatrizen
  {
  // Gibt den Winkel in Quaternionenform [-1 bis 1] und die Drehachse unnormiert aber richtig orientiert zurück.

  // ********************* Realteil direkt aus der Matrix berechnen, Problem bei 0° und 180° Drehungen abfangen
  real qr= 1 + pdreh.x.x + pdreh.y.y + pdreh.z.z;                 // qr [4..0] = [0..180]°
  if (qr >= 4 - quantg)             //   0° Drehung
    return cvektor4 (1, 0, 0, 0);

  // ********************* Drehachse durch Eigenwerte berechnen, Eigenvektor numerisch stabil, Länge: [5 1/3 bis 16]
  cbasis3 hdreh (pdreh);
  hdreh.x.x-= 1;
  hdreh.y.y-= 1;
  hdreh.z.z-= 1;
  cvektor3 drehachse (geteigen (hdreh));

  // Drehachse richtig orientieren
  if (qr <= quantg)                                               // 180° Drehung: Es gibt 2 Drehachsen statt nur einer
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
    /**/ qwa= qwafrommatrix (pdreh);
    else qwa= qwafrommatrix (-pdreh);
  if (absr (qwa.i) <= quantg)
    qwa.i= 0;
  if (absr (qwa.j) <= quantg)
    qwa.j= 0;
  if (absr (qwa.ij) <= quantg)
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
  if (qwa.r >= 1 - quantg)      // Drehung ist 0° Drehung
    return qwa;                // 1 zurückgeben
  cvektor3 achse (cvektor3 (qwa.i, qwa.j, qwa.ij));
  real k= sqrtr (1 - qwa.r*qwa.r)/absr (achse);
  return cvektor4 (qwa.r, k*achse);
  }

cvektor4 quaternionfrommatrix2 (const cbasis3 &pdreh)             // Kreuzproduktversion: versagt bei 180° Drehungen
  {
  real qr= sqrtr (1 + pdreh.x.x + pdreh.y.y + pdreh.z.z);
  if (qr <= quantg)                                               // 180° Drehung
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
  if (absr (vb) < 1)
    breite= asinr (vb);
  if (vb >= 1)
    breite= PI/2;
  if (vl <= -1)
    breite= -PI/2;

  // Längengrad- und Rollberechnung
  real cosbr= cosr (breite);
  if (cosbr > quantg)  // Breite nicht polar
    {
    // Längengradberechnung
    vl= pdm.z.z/cosbr;
    if (absr (vl) < 1)
      laenge= acosr (vl);
    if (vl >= 1)
      laenge= 0;
    if (vl <= -1)
      laenge= PI;
    if (pdm.z.x < 0)
      laenge = -laenge;

    // Rollberechnung
    vr= pdm.y.y/cosbr;
    if (absr (vr) < 1)
      roll= acosr (vr);
    if (vr >= 1)
      roll= 0;
    if (vr <= -1)
      roll= PI;
    if (pdm.x.y > 0)
      roll= -roll;
    }
  if (cosbr <= quantg)  // Spezialfall Breite polar
    {
    vl= pdm.x.x;
    if (absr (vl) < 1)
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
    /**/ return  ret;
    else return -ret;
  }

//################################################### Polynomberechnung ######################################################################################################################################################################
//*************************************************** quadratische Verfahren *****************************************************************************************************************************************************************

void quadratisch (ckomplexk a, ckomplexk b, ckomplexk& x1, ckomplexk& x2)
  {
  ckomplexk a2, D;

  a2= a/-2;
  D= sqrtr (a2*a2 - b);

  x1= a2 - D;            // kleinere Lösung zuerst falls im Reellem
  x2= a2 + D;
  }

//*************************************************** kubische Verfahren *********************************************************************************************************************************************************************

void uvaddition (ckomplexk z1, ckomplexk z2, ckomplexk pbed, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3)
  {
  ckomplexk u, v[3], bed[3];
  integer min;

  u= cbrtr (z1);
  v[0]= cbrtr (z2);

  v[1]= v[0]*e31;
  v[2]= v[0]*e32;

  bed[0]= u*v[0];
  bed[1]= u*v[1];
  bed[2]= u*v[2];

  if (absr (bed[0] - pbed) <= absr (bed[1] - pbed))
    /**/ min= 0;
    else min= 1;

  if (absr (bed[2] - pbed) < absr (bed[min] - pbed))
    min= 2;

  y1= u + v[min];
  y2= u*e31 + v[(min + 2) % 3];
  y3= u*e32 + v[(min + 1) % 3];
  }

void kubischreduziertcardano (ckomplexk p, ckomplexk q, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3)
  {
  ckomplexk u1, u2;

  quadratisch (q, p*p*p/-27, u1, u2);
  uvaddition (u1, u2, -p, y1, y2, y3);
  }

void kubischreduziertcardano3 (ckomplexk p, ckomplexk q, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3)  // Cardano/Lagrange-Verfahren mit 3-fachen Lösungen
  {
  ckomplexk u1, u2;

  quadratisch (q*27, p*p*p*-27, u1, u2);
  uvaddition (u1, u2, p*-3, y1, y2, y3);
  }

void kubischreduziertu (ckomplexk p, ckomplexk q, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3)  // u-Verfahren
  {
  ckomplexk  u1, u2, u, z1, z2, z3;

  quadratisch (q, p*p*p/-27, u1, u2);

  if (absr (u1) >= absr (u2))
    /**/ u= u1;
    else u= u2;

  if (absr (u) > 0)                                                             // die betragsmäßig größere Lösung nehmen um von der Division durch 0 wegzukommen
    {
    cbrtr (u1, z1, z2, z3);
    y1= z1 - p/(z1*3);
    y2= z2 - p/(z2*3);
    y3= z3 - p/(z3*3);
    }
  else                                                                          // u1, u2 = 0
    {
    y1= 0;
    y2= 0;
    y3= 0;
    }
  }

void kubischreduziertu3 (ckomplexk p, ckomplexk q, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3)  // u-Verfahren mit 3-fachen Lösungen
  {
  ckomplexk  u1, u2, u, z1, z2, z3;

  quadratisch (q*27, p*p*p*-27, u1, u2);

  if (absr (u1) >= absr (u2))
    /**/ u= u1;
    else u= u2;

  if (absr (u) > 0)                                                             // die betragsmäßig größere Lösung nehmen um von der Division durch 0 wegzukommen
    {
    cbrtr (u1, z1, z2, z3);
    y1= z1 - p*3/z1;
    y2= z2 - p*3/z2;
    y3= z3 - p*3/z3;
    }
  else                                                                          // u1, u2 = 0
    {
    y1= 0;
    y2= 0;
    y3= 0;
    }
  }

void kubischreduziertg (ckomplexk p, ckomplexk q, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3)  // u-Verfahren mit Parameterskalierung
  {
  ckomplexk  xl, z, z1, z2;

  // Lösung der normalen linearen Gleichung
  p= p/-3;
  q= q/-2;
  xl= q*q - p*p*p;

  // Lösung der quadratischen Gleichung
  z= sqrtr (xl);
  z1= q + z;
  z2= q - z;

  if (absr (z1) >= absr (z2))
    /**/ z= z1;
    else z= z2;

  // Lösung der kubischen Gleichung
  if (absr (z) > 0)
    {
    cbrtr (z, y1, y2, y3);
    y1= y1 + p/y1;
    y2= y2 + p/y2;
    y3= y3 + p/y3;
    }
    else
    {
    y1= 0;
    y2= 0;
    y3= 0;
    }
  }

void kubischreduziertg2 (ckomplexk p, ckomplexk q, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3)  // u-Verfahren ganzzahlig skaliert
  {
  ckomplexk  xl, z, z1, z2;

  // Lösung der normalen linearen Gleichung
  xl= q*q*729 + p*p*p*108;

  // Lösung der quadratischen Gleichung
  z= sqrtr (xl);
  z1= q*27 + z;
  z2= q*27 - z;

  if (absr (z1) >= absr (z2))
    /**/ z= z1;
    else z= z2;

  // Lösung der kubischen Gleichung
  if (absr (z) > 0)
    {
    cbrtr (z/-2, y1, y2, y3);
    y1= y1/3 - p/y1;
    y2= y2/3 - p/y2;
    y3= y3/3 - p/y3;
    }
    else
    {
    y1= 0;
    y2= 0;
    y3= 0;
    }
  }

void kubischreduziertk (ckomplexk a, ckomplexk b, ckomplexk c, ckomplexk& p, ckomplexk& q)
  {
  p= a*a/-3 + b;
  q= a*(a*a/real (13.5) + b/-3) + c;
  }

void kubisch (ckomplexk a, ckomplexk b, ckomplexk c, ckomplexk& x1, ckomplexk& x2, ckomplexk& x3)
  {
  ckomplexk p, q, y1, y2, y3;

  kubischreduziertk (a, b, c, p, q);

  //kubischreduziertcardano (p, q, y1, y2, y3);
  //kubischreduziertcardano3 (p, q, y1, y2, y3);
  //kubischreduziertu (p, q, y1, y2, y3);
  //kubischreduziertu3 (p, q, y1, y2, y3);
  //kubischreduziertg (p, q, y1, y2, y3);
  kubischreduziertg2 (p, q, y1, y2, y3);

  x1= y1 - a/3;
  x2= y2 - a/3;
  x3= y3 - a/3;
  }

//--------------------------------------------------- kubisch reelle Verfahren ---------------------------------------------------------------------------------------------------------------------------------------------------------------

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
    l= sqrtr (p/real (-0.75));
    y= cosr (acosr (q*3/p/l)/3)*l;
    }
  }

void kubischreduziertreellu (real p, real q, real& y)
  {
  real xl, yt, l;

  // Lösung der normalen linearen Gleichung
  q= q/-2;
  p= p/-3;
  xl= q*q - p*p*p;

  // reelle Lösung der kubischen Resolvente
  if (xl >= 0)                                                        // 2 oder 0 Schnittpunkte mit dem Torus
    {
    if (q >= 0)                                                       // Fallunterscheidung notwendig, sonst zusätzliche Stern-Artefakte beim Torus
      /**/ yt= cbrtr (q + sqrtr (xl));
      else yt= cbrtr (q - sqrtr (xl));                                // qk ist immer ungleich 0 somit keine Auslöschung bei xl = 0
    y= yt + p/yt;                                                     // ytk = 0 ausgeschlossen, da Auslöschung verhindert
    }
    else                                                              // 4 Schnittpunkte mit dem Torus
    {
    l= sqrtr (p);                                                     // pk > 0 immer, l > 0 immer, wegen Division
    y= cosr (acosr (q/p/l)/3)*l*2;                                    // 1. Fehlerquelle yk, |qk/pk/l| > 1 sehr selten  +-1.00000012F,  behoben in acos Funktion
    }
  }

//--------------------------------------------------- kubisch reell integriert ---------------------------------------------------------------------------------------------------------------------------------------------------------------

void kubischintr (real a, real b, real c, cschnittpunkte& psp)
  {
  real a3, p, q, xl, yt, z1, z2, z3, l, l2, w;

  a3= a/-3;

  // Parameter der reduzierten kubischen Gleichung
  p= a*a/9 + b/-3;
  q= a*(a*a/-27 + b/6) + c/-2;

  xl= q*q - p*p*p;

  // reelle Lösung der kubischen Resolvente
  if (xl >= 0)
    {
    if (q >= 0)
      /**/ yt= cbrtr (q + sqrtr (xl));
      else yt= cbrtr (q - sqrtr (xl));
    z1= yt + p/yt + a3;
    if (z1 > 0)
      psp.add (z1);
    }
    else
    {
    l= sqrtr (p);
    l2= l*2;
    w= acosr (q/p/l)/3;

    z1= a3 + l2*cosr (w);
    z2= a3 + l2*cosr (w + PI2d);
    z3= a3 + l2*cosr (w - PI2d);

    if (z1 > 0)
      psp.add (z1);
    if (z2 > 0)
      psp.add (z2);
    if (z3 > 0)
      psp.add (z3);
    }
  }

//*************************************************** quartische Verfahren *******************************************************************************************************************************************************************
//--------------------------------------------------- kubische Resolventen -------------------------------------------------------------------------------------------------------------------------------------------------------------------

void kubischeresolventeproduktsumme (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& z1, ckomplexk& z2, ckomplexk& z3)  // Σ(y)
  {
  ckomplexk ak, bk, ck;

  ak= -p;
  bk= r*-4;
  ck= p*r*4 - q*q;

  kubisch (ak, bk, ck, z1, z2, z3);
  }

void kubischeresolventesummenprodukt (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& z1, ckomplexk& z2, ckomplexk& z3)  // Π(y)
  {
  ckomplexk ak, bk, ck;

  ak= p*-2;
  bk= p*p + r*-4;
  ck= q*q;

  kubisch (ak, bk, ck, z1, z2, z3);
  }

void kubischeresolventeproduktsumme (ckomplexk a, ckomplexk b, ckomplexk c, ckomplexk d, ckomplexk& z1, ckomplexk& z2, ckomplexk& z3)  // Σ(x)
  {
  ckomplexk ak, bk, ck;

  ak= -b;
  bk= a*c + d*-4;
  ck= d*(b*4 - a*a) - c*c;

  kubisch (ak, bk, ck, z1, z2, z3);
  }

void kubischeresolventesummenprodukt (ckomplexk a, ckomplexk b, ckomplexk c, ckomplexk d, ckomplexk& z1, ckomplexk& z2, ckomplexk& z3)  // Π(x)
  {
  ckomplexk ak, bk, ck;

  ak= b*-2;
  bk= b*b + a*c + d*-4;
  ck= a*(b*-c + d*a) + c*c;

  kubisch (ak, bk, ck, z1, z2, z3);
  }

//--------------------------------------------------- quartisch komplexe Verfahren -----------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------- quartisch komplex reduziert ------------------------------------------------------------------------------------------------------------------------------------------------------------

void quartischreduziertproduktsummediv (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4)
  {
  ckomplexk z1, z2, z3, z, D, a1;

  kubischeresolventeproduktsumme (p, q, r, z1, z2, z3);

  z= z1;

  D= sqrtr (z*z/4 - r);
  a1= q/D/2;

  quadratisch (-a1, z/2 + D, y1, y2);           // kleinere Lösung zuerst
  quadratisch ( a1, z/2 - D, y3, y4);

  //return;

  printtext ("                                   quartisch reduziert produktsumme div Zwischenwerte\n");
  printvektor2komplex ("z          ", z, 0);
  printtext ("\n");
  printvektor2komplex ("D          ", D, 0);
  printtext ("\n");
  printvektor2komplex ("a1         ", -a1, 0);
  printvektor2komplex ("b1         ", z/2 + D, 0);
  printvektor2komplex ("a2         ", a1, 0);
  printvektor2komplex ("b2         ", z/2 - D, 0);
  }

void quartischreduziertproduktsumme (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4)
  {
  ckomplexk z1, z2, z3, z, u, v, bed;

  kubischeresolventeproduktsumme (p, q, r, z1, z2, z3);

  z= z1;

  u= sqrtr (z - p);
  v= sqrtr (z*z/4 - r);

  // Bedingung -2uv = q
  bed= u*v;
  if (absr (bed - q) < absr (bed + q))
    v= -v;

  quadratisch (-u, z/2 - v, y1, y2);           // kleinere Lösung zuerst
  quadratisch ( u, z/2 + v, y3, y4);

  //return;

  printtext ("                                   quartisch reduziert produktsumme Zwischenwerte\n");
  printvektor2komplex ("z          ", z, 0);
  printtext ("\n");
  printvektor2komplex ("u          ", u, 0);
  printvektor2komplex ("v          ", v, 0);
  printtext ("\n");
  printvektor2komplex ("a1         ", -u, 0);
  printvektor2komplex ("b1         ", z/2 - v, 0);
  printvektor2komplex ("a2         ",  u, 0);
  printvektor2komplex ("b2         ", z/2 + v, 0);
  }

void quartischreduziertsummenprodukt (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4)
  {
  ckomplexk z1, z2, z3, z, u, pz, v, bed;

  kubischeresolventesummenprodukt (p, q, r, z1, z2, z3);

  z= z2;

  u= sqrtr (-z);
  pz= (p - z);
  v= sqrtr (pz*pz/4 - r);

  // Bedingung -2uv = q
  bed= u*v;
  if (absr (bed - q) < absr (bed + q))
    v= -v;

  quadratisch (-u, pz/2 - v, y1, y2);           // kleinere Lösung zuerst
  quadratisch ( u, pz/2 + v, y3, y4);

  //return;

  printtext ("                                   quartisch reduziert summenprodukt Zwischenwerte\n");
  printvektor2komplex ("z          ", z, 0);
  printtext ("\n");
  printvektor2komplex ("u          ", u, 0);
  printvektor2komplex ("v          ", v, 0);
  printtext ("\n");
  printvektor2komplex ("a1         ", -u, 0);
  printvektor2komplex ("b1         ", pz/2 - v, 0);
  printvektor2komplex ("a2         ",  u, 0);
  printvektor2komplex ("b2         ", pz/2 + v, 0);
  }

void quartischreduziertlagrange (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4)
  {
  ckomplexk z1, z2, z3, u1, u2, u3, bed;

  kubischeresolventesummenprodukt (p, q, r, z1, z2, z3);

  u1= sqrtr (z1/-4);
  u2= sqrtr (z2/-4);
  u3= sqrtr (z3/-4);

  y1=  u1 - u2 - u3;
  y2= -u1 + u2 - u3;
  y3= -u1 - u2 + u3;
  y4=  u1 + u2 + u3;

  // Bedingung: -8*u1*u2*u3 = q
  bed= u1*u2*u3*-8;
  if (absr (bed + q) < absr (bed - q))
    {
    y1= -y1;
    y2= -y2;
    y3= -y3;
    y4= -y4;
    }

  //return;

  printtext ("                                   quartisch reduziert lagrange Zwischenwerte\n");
  printvektor2komplex ("z1         ", z1, 0);
  printvektor2komplex ("z2         ", z2, 0);
  printvektor2komplex ("z3         ", z3, 0);
  printtext ("\n");
  printvektor2komplex ("u1         ", u1, 0);
  printvektor2komplex ("u2         ", u2, 0);
  printvektor2komplex ("u3         ", u3, 0);
  printtext ("\n");
  printvektor2komplex ("bed        ", bed, 0);
  printtext ("\n");
  }

void quartischreduziertk (ckomplexk a, ckomplexk b, ckomplexk c, ckomplexk d, ckomplexk& p, ckomplexk& q, ckomplexk& r)
  {
  ckomplexk aq;

  aq= a*a/16;
  p= b - aq*6;
  q= a*(aq*2 + b/-2) + c;
  r= aq*(aq*-3 + b) + a*c/-4 + d;
  }

void quartisch (ckomplexk a, ckomplexk b, ckomplexk c, ckomplexk d, ckomplexk& x1, ckomplexk& x2, ckomplexk& x3, ckomplexk& x4)
  {
  ckomplexk p, q, r, y1, y2, y3, y4, a4;

  quartischreduziertk (a, b, c, d, p, q, r);

  //quartischreduziertproduktsummediv (p, q, r, y1, y2, y3, y4);
  quartischreduziertproduktsumme (p, q, r, y1, y2, y3, y4);
  //quartischreduziertsummenprodukt (p, q, r, y1, y2, y3, y4);
  //quartischreduziertlagrange (p, q, r, y1, y2, y3, y4);

  a4= a/-4;
  x1= y1 + a4;
  x2= y2 + a4;
  x3= y3 + a4;
  x4= y4 + a4;
  }

// --------------------------------------------  quartisch komplex normal --------------------------------------------------------------------------------------------------------------------------------------------------------------------

void quartischnormalproduktsummediv (ckomplexk a, ckomplexk b, ckomplexk c, ckomplexk d, ckomplexk& x1, ckomplexk& x2, ckomplexk& x3, ckomplexk& x4)
  {
  ckomplexk z1, z2, z3, z, D, a1, a2, b1, b2;

  kubischeresolventeproduktsumme (a, b, c, d, z1, z2, z3);

  z= z1;

  D= sqrtr (z*z/4 - d);
  b1= z/2 - D;
  b2= z/2 + D;
  a1= (a*b1 - c)/D/-2;        // kleinere Lösung zuerst
  a2= (a*b2 - c)/D/2;

  quadratisch ( a1, b1, x1, x2);
  quadratisch ( a2, b2, x3, x4);

  //return;

  printtext ("                                   quartisch normal produktsumme div Zwischenwerte\n");
  printvektor2komplex ("z          ", z, 0);
  printtext ("\n");
  printvektor2komplex ("D          ", D, 0);
  printtext ("\n");
  printvektor2komplex ("a1         ", a1, 0);
  printvektor2komplex ("b1         ", b1, 0);
  printvektor2komplex ("a2         ", a2, 0);
  printvektor2komplex ("b2         ", b2, 0);
  }

void quartischnormalproduktsumme (ckomplexk a, ckomplexk b, ckomplexk c, ckomplexk d, ckomplexk& x1, ckomplexk& x2, ckomplexk& x3, ckomplexk& x4)
  {
  ckomplexk z1, z2, z3, z, a1, a2, b1, b2, c1, c2;

  kubischeresolventeproduktsumme (a, b, c, d, z1, z2, z3);

  z= z1;

  quadratisch (-a, b-z, a1, a2);
  quadratisch (-z, d, b1, b2);

  c1= a1*b2 + a2*b1;
  c2= a1*b1 + a2*b2;

  if (absr (c1 + c) < absr (c2 + c))
    {
    quadratisch (a1, b1, x1, x2);
    quadratisch (a2, b2, x3, x4);
    }
    else
    {
    quadratisch (a1, b2, x1, x2);
    quadratisch (a2, b1, x3, x4);
    }

  //return;

  printtext ("                                   quartisch normal produktsumme Zwischenwerte\n");
  printvektor2komplex ("z          ", z, 0);
  printtext ("\n");
  printvektor2komplex ("a1         ", a1, 0);
  printvektor2komplex ("b1         ", b1, 0);
  printvektor2komplex ("a2         ", a2, 0);
  printvektor2komplex ("b2         ", b2, 0);
  }

void quartischnormalsummenprodukt (ckomplexk a, ckomplexk b, ckomplexk c, ckomplexk d, ckomplexk& x1, ckomplexk& x2, ckomplexk& x3, ckomplexk& x4)
  {
  ckomplexk z1, z2, z3, z, a1, a2, b1, b2, c1, c2;

  kubischeresolventesummenprodukt (a, b, c, d, z1, z2, z3);

  z= z1;

  quadratisch (-a, z, a1, a2);
  quadratisch (z-b, d, b1, b2);

  c1= a1*b2 + a2*b1;
  c2= a1*b1 + a2*b2;

  if (absr (c1 + c) < absr (c2 + c))
    {
    quadratisch (a1, b1, x1, x2);
    quadratisch (a2, b2, x3, x4);
    }
    else
    {
    quadratisch (a1, b2, x1, x2);
    quadratisch (a2, b1, x3, x4);
    }

  printtext ("                                   quartisch normal summenprodukt Zwischenwerte\n");
  printvektor2komplex ("z          ", z, 0);
  printtext ("\n");
  printvektor2komplex ("a1         ", a1, 0);
  printvektor2komplex ("b1         ", b1, 0);
  printvektor2komplex ("a2         ", a2, 0);
  printvektor2komplex ("b2         ", b2, 0);
  }

void quartischnormallagrange (ckomplexk a, ckomplexk b, ckomplexk c, ckomplexk d, ckomplexk& x1, ckomplexk& x2, ckomplexk& x3, ckomplexk& x4)
  {
  ckomplexk z1, z2, z3, zen, u1, u2, u3, bed, a4;

  kubischeresolventesummenprodukt (a, b, c, d, z1, z2, z3);

  u1= sqrtr (z1/4);
  u2= sqrtr (z2/4);
  u3= sqrtr (z3/4);

  a4= a/-4;
  x1=  (u1 + u2 + u3);
  x2=  (u1 - u2 - u3);
  x3= (-u1 + u2 - u3);
  x4= (-u1 - u2 + u3);

  // Bedingung: -8*u1*u2*u3 = c
  bed= u1*u2*u3*8;

/*
  if (absr (bed + c) < absr (bed - c))
    {
    x1= -x1;
    x2= -x2;
    x3= -x3;
    x4= -x4;
    }
*/

  //return;

  printtext ("                                   quartisch normal lagrange Zwischenwerte\n");
  printvektor2komplex ("z1         ", z1, 0);
  printvektor2komplex ("z2         ", z2, 0);
  printvektor2komplex ("z3         ", z3, 0);
  printtext ("\n");
  printvektor2komplex ("u1         ", u1, 0);
  printvektor2komplex ("u2         ", u2, 0);
  printvektor2komplex ("u3         ", u3, 0);
  printtext ("\n");
  printvektor2komplex ("bed        ", bed, 0);
  printtext ("\n");
  }

//--------------------------------------------------- reelle, integrierte Verfahren ----------------------------------------------------------------------------------------------------------------------------------------------------------

void quartischreduziertintr (real a, real b, real c, real d, cschnittpunkte& psp)
  {
  real p, q, r, pp;
  real aq, pa, qa, xl, ytk, l, yk;
  real zk, uq, vq, u, v, bed, b1, b2, a4;
  real D12, D34, o12, o34, x1, x2, x3, x4;

  // Parameter der reduzierten quartischen Gleichung
  aq= a*a/16;
  p= b/6 - aq;                                         // p/6
  q= a*(aq + b/-4) + c/2;                              // q/2
  r= aq*(aq*-3 + b) + a*c/-4 + d;

  // Parameter der angepassten reduzierten kubischen Gleichung
  pp= p*p;
  pa= pp + r/3;
  qa= p*(pp - r) + q*q/4;                              // -qa um für die Resolvente Summenprodukt die negativen Lösungen zu bekommen, ungünstig weil der sqrtz-Zweig sich dann auf + PI2d verschiebt

  // Parameter der angepassten reduzierten kubischen Gleichung aus den Koeffizienten
  //pa= (a*c/-4 + b*b/12 + d)/3;
  //qa= a*b*c/-48 + b*d/-6 + aq*d + b*b*b/216 + c*c/16;

  // Lösung der normalen linearen Gleichung
  xl= qa*qa - pa*pa*pa;

  // reelle Lösung der kubischen Resolvente
  if (xl >= 0)                                                        // 2 oder 0 Schnittpunkte mit dem Torus
    {
    if (qa >= 0)                                                      // Fallunterscheidung notwendig, sonst zusätzliche Stern-Artefakte beim Torus
      /**/ ytk= cbrtr (qa + sqrtr (xl));
      else ytk= cbrtr (qa - sqrtr (xl));                              // qa ist immer ungleich 0 somit keine Auslöschung bei xl = 0
    yk= ytk + pa/ytk;                                                 // ytk = 0 ausgeschlossen, da Auslöschung verhindert
    }
    else                                                              // 4 Schnittpunkte mit dem Torus
    {
    l= sqrtr (pa);                                                    // pa > 0 immer, l > 0 immer, wegen Division
    yk= cosr (acosr (qa/(pa*l))/3)*l*2;                                 // sqrtz (vq) funktioniert bei Σ(y), nicht bei Π(y)
    //yk= cosr (acosr (qa/(pa*l))/3 + PI2d)*l*2;                      // sqrtz (vq) funktioniert bei Π(y), nicht bei Σ(y)
    //yk= cosr (acosr (qa/(pa*l))/3 - PI2d)*l*2;                      // sqrtz (vq) funktioniert nicht bei Σ(y), nicht bei Π(y)
    }

  //----------------------------------- Ermittlung der Koeffizienten der beiden quadratischen Gleichungen aus der Lösung der reduzierten kubischen Gleichung:  zk= Σ(y)/2 oder zk= Π(y)/-2
  // Produktsumme
  zk= yk + p;                                                         // zk = Σ(y)/2
  uq= yk/2 - p;
  //uq= (zk - p*3)/2;

  // Summenprodukt
  //zk= yk + p*-2;                                                      // zk = Π(y)/-2
  //uq= zk/2;                                                           // berechnet man uq und zk direkt aus yk erhält man die gleichen Werte wie für die Produktsumme
  //zk= zk + p*3;

  // Bestimmung der quadratischen Koeffizienten
  vq= zk*zk - r;

  u= sqrtrz (uq);
  v= sqrtrz (vq);

  // Bedingung uv = -q
  bed= u*v;
  if (absr (bed - q) < absr (bed + q))
    v= -v;

  b1= zk + v;
  b2= zk - v;

  //----------------------------------- Die 4 Lösungen der beiden quadratischen Gleichungen
  a4= a/-4;
  if (uq*2 >= b1)
    {
    D12= sqrtr (uq - b1);                                             // wenn D12 nicht existiert, dann gibt es keine 2 reellen Lösungen
    o12= a4 - u;
    x1= o12 - D12;
    x2= o12 + D12;
    if (x1 > 0)
      psp.add (x1);
    if (x2 > 0)
      psp.add (x2);
    }
  if (uq*2 >= b2)
    {
    D34= sqrtr (uq - b2);                                             // wenn D12 nicht existiert, dann gibt es keine 2 reellen Lösungen
    o34= a4 + u;
    x3= o34 - D34;
    x4= o34 + D34;
    if (x3 > 0)
      psp.add (x3);
    if (x4 > 0)
      psp.add (x4);
    }
  }

void quartischnormalintr (real a, real b, real c, real d, cschnittpunkte& psp)
  {
  //real p, q, r, pp;
  real aq, pa, qa, xl, ytk, l, yk;
  real zk, c1, c2, sw, Da, Db, a4, a1, a2, b1, b2, a1q, a2q;
  real D12, D34, x1, x2, x3, x4;

  // Parameter der reduzierten quartischen Gleichung
  aq= a*a/16;
  //p= b/6 - aq;
  //q= a*(aq + b/-4) + c/2;
  //r= aq*(aq*-3 + b) + a*c/-4 + d;

  // Parameter der angepassten reduzierten kubischen Gleichung
  //pp= p*p;
  //pa= pp + r/3;
  //qa= p*(pp - r) + q*q/4;

  // Parameter der angepassten reduzierten kubischen Gleichung aus den Koeffizienten
  pa= (a*c/-4 + b*b/12 + d)/3;
  qa= a*b*c/-48 + b*d/-6 + aq*d + b*b*b/216 + c*c/16;

  // Lösung der normalen linearen Gleichung
  xl= qa*qa - pa*pa*pa;

  // reelle Lösung der kubischen Resolvente
  if (xl >= 0)                                                        // 2 oder 0 Schnittpunkte mit dem Torus
    {
    if (qa >= 0)                                                      // Fallunterscheidung notwendig, sonst zusätzliche Stern-Artefakte beim Torus
      /**/ ytk= cbrtr (qa + sqrtr (xl));
      else ytk= cbrtr (qa - sqrtr (xl));                              // qa ist immer ungleich 0 somit keine Auslöschung bei xl = 0
    yk= ytk + pa/ytk;                                                 // ytk = 0 ausgeschlossen, da Auslöschung verhindert
    }
    else                                                              // 4 Schnittpunkte mit dem Torus
    {
    l= sqrtr (pa);                                                    // pa > 0 immer, l > 0 immer, wegen Division
    yk= cosr (acosr (qa/(pa*l))/3)*l*2;                                 // 1. Fehleruelle yk, |qa/(pa*l)| > 1 sehr selten  +-1.00000012F,  behoben in acos Funktion
    //yk= cosr (acosr (qa/(pa*l))/3 + PI2d)*l*2;                      // funktioniert nicht mit sqrtz (vq)
    //yk= cosr (acosr (qa/(pa*l))/3 - PI2d)*l*2;                      // funktioniert nicht mit sqrtz (vq)
    }

  //----------------------------------- Ermittlung der Koeffizienten der beiden quadratischen Gleichungen aus der Lösung der reduzierten kubischen Gleichung (ak=-p/2 für Rückreduzierung)
  zk= yk + b/6;

  Da= sqrtrz (yk/2 + aq - b/6);                                       // Da= sqrtrz (zk/2 + aq - b/4);
  Db= sqrtr (zk*zk - d);                                              // Fehler bei sqrtz

  b1= zk + Db;
  b2= zk - Db;

  a4= a/-4;
  a1= a4 + Da;
  a2= a4 - Da;

  c1= a1*b2 + a2*b1;
  c2= a1*b1 + a2*b2;

  if (absr (c2*2 + c) < absr (c1*2 + c))
    {
    sw= b1;
    b1= b2;
    b2= sw;
    }

  //----------------------------------- Die 4 Lösungen der beiden quadratischen Gleichungen
  a1q= a1*a1;
  if (a1q >= b1)
    {
    D12= sqrtr (a1q - b1);
    x1= a1 - D12;
    x2= a1 + D12;
    if (x1 > 0)
      psp.add (x1);
    if (x2 > 0)
      psp.add (x2);
    }
  a2q= a2*a2;
  if (a2q >= b2)
    {
    D34= sqrtr (a2q - b2);
    x3= a2 - D34;
    x4= a2 + D34;
    if (x3 > 0)
      psp.add (x3);
    if (x4 > 0)
      psp.add (x4);
    }
  }

void quartischreduziertdivintr (real a, real b, real c, real d, cschnittpunkte& psp)
  {
  real p, q, r, pp;
  real aq, pa, qa, xl, ytk, l, yk;
  real zk, D, u, uq, b1, b2, a4;
  real D12, D34, o12, o34, x1, x2, x3, x4;

  // Parameter der reduzierten quartischen Gleichung
  aq= a*a/16;
  p= b/6 - aq;
  q= a*(aq + b/-4) + c/2;
  r= aq*(aq*-3 + b) + a*c/-4 + d;

  // Parameter der angepassten reduzierten kubischen Gleichung
  pp= p*p;
  pa= pp + r/3;
  qa= p*(pp - r) + q*q/4;

  // Parameter der angepassten reduzierten kubischen Gleichung aus den Koeffizienten
  //pa= (a*c/-4 + b*b/12 + d)/3;
  //qa= a*b*c/-48 + b*d/-6 + aq*d + b*b*b/216 + c*c/16;

  // Lösung der normalen linearen Gleichung
  xl= qa*qa - pa*pa*pa;

  // reelle Lösung der kubischen Resolvente
  if (xl >= 0)                                                        // 2 oder 0 Schnittpunkte mit dem Torus
    {
    if (qa >= 0)                                                      // Fallunterscheidung notwendig, sonst zusätzliche Stern-Artefakte beim Torus
      /**/ ytk= cbrtr (qa + sqrtr (xl));
      else ytk= cbrtr (qa - sqrtr (xl));                              // qa ist immer ungleich 0 somit keine Auslöschung bei xl = 0
    yk= ytk + pa/ytk;                                                 // ytk = 0 ausgeschlossen, da Auslöschung verhindert
    }
    else                                                              // 4 Schnittpunkte mit dem Torus
    {
    l= sqrtr (pa);                                                    // pa > 0 immer, l > 0 immer, wegen Division
    yk= cosr (acosr (qa/(pa*l))/3)*l*2;                               // starker Mittenschnitt
    //yk= cosr (acosr (qa/(pa*l))/3 + PI2d)*l*2;                        // starkes Außensprühen, Mittenring, innen artefaktfrei
    //yk= cosr (acosr (qa/(pa*l))/3 - PI2d)*l*2;                        // Ring mit Doppelpunkt, innen schwächere Doppellinien
    }

  //----------------------------------- Ermittlung der Koeffizienten der beiden quadratischen Gleichungen aus der Lösung der reduzierten kubischen Gleichung (ak=-p/2 für Rückreduzierung)
  zk= yk + p;

  D= sqrtr (zk*zk - r);                                               // Fehler bei sqrtz

  b1= zk + D;
  b2= zk - D;

  u= q/D/2;
  uq= u*u;

  //----------------------------------- Die 4 Lösungen der beiden quadratischen Gleichungen
  a4= a/-4;
  if (uq >= b1)                                                       // Multiplikation nützt nichts, Fehlersprühen bei Entfernung
    {
    D12= sqrtr (uq - b1);
    o12= a4 + u;
    x1= o12 - D12;
    x2= o12 + D12;
    if (x1 > 0)
      psp.add (x1);
    if (x2 > 0)
      psp.add (x2);
    }
  if (uq >= b2)
    {
    D34= sqrtr (uq - b2);
    o34= a4 - u;
    x3= o34 - D34;
    x4= o34 + D34;
    if (x3 > 0)
      psp.add (x3);
    if (x4 > 0)
      psp.add (x4);
    }
  }

void quartischnormaldivintr (real a, real b, real c, real d, cschnittpunkte& psp)
  {
  //real p, q, r, pp;
  real aq, pa, qa, xl, ytk, l, yk;
  real zk, D, a1, a2, b1, b2, a1q, a2q;
  real D12, D34, x1, x2, x3, x4;

  // Parameter der reduzierten quartischen Gleichung
  aq= a*a/16;
  //p= b/6 - aq;
  //q= a*(aq + b/-4) + c/2;
  //r= aq*(aq*-3 + b) + a*c/-4 + d;

  // Parameter der angepassten reduzierten kubischen Gleichung
  //pp= p*p;
  //pa= pp + r/3;
  //qa= p*(pp - r) + q*q/4;

  // Parameter der angepassten reduzierten kubischen Gleichung aus den Koeffizienten
  pa= (a*c/-4 + b*b/12 + d)/3;
  qa= a*b*c/-48 + b*d/-6 + aq*d + b*b*b/216 + c*c/16;

  // Lösung der normalen linearen Gleichung
  xl= qa*qa - pa*pa*pa;

  // reelle Lösung der kubischen Resolvente
  if (xl >= 0)                                                        // 2 oder 0 Schnittpunkte mit dem Torus
    {
    if (qa >= 0)                                                      // Fallunterscheidung notwendig, sonst zusätzliche Stern-Artefakte beim Torus
      /**/ ytk= cbrtr (qa + sqrtr (xl));
      else ytk= cbrtr (qa - sqrtr (xl));                              // qa ist immer ungleich 0 somit keine Auslöschung bei xl = 0
    yk= ytk + pa/ytk;                                                 // ytk = 0 ausgeschlossen, da Auslöschung verhindert
    }
    else                                                              // 4 Schnittpunkte mit dem Torus
    {
    l= sqrtr (pa);                                                    // pa > 0 immer, l > 0 immer, wegen Division
    yk= cosr (acosr (qa/(pa*l))/3)*l*2;                                 // 1. Fehleruelle yk, |qa/(pa*l)| > 1 sehr selten  +-1.00000012F,  behoben in acos Funktion
    //yk= cosr (acosr (qa/(pa*l))/3 + PI2d)*l*2;                      // funktioniert nicht mit sqrtz (vq)
    //yk= cosr (acosr (qa/(pa*l))/3 - PI2d)*l*2;                      // funktioniert nicht mit sqrtz (vq)
    }

  //----------------------------------- Ermittlung der Koeffizienten der beiden quadratischen Gleichungen aus der Lösung der reduzierten kubischen Gleichung (ak=-p/2 für Rückreduzierung)
  zk= yk + b/6;

  D= sqrtr (zk*zk - d);                                               // Fehler bei sqrtz

  b1= zk + D;
  b2= zk - D;

  a1= (a*b1 - c)/D/-4;
  a2= (a*b2 - c)/D/4;

  //----------------------------------- Die 4 Lösungen der beiden quadratischen Gleichungen
  a1q= a1*a1;
  if (a1q >= b1)
    {
    D12= sqrtr (a1q - b1);
    x1= a1 - D12;
    x2= a1 + D12;
    if (x1 > 0)
      psp.add (x1);
    if (x2 > 0)
      psp.add (x2);
    }
  a2q= a2*a2;
  if (a2q >= b2)
    {
    D34= sqrtr (a2q - b2);
    x3= a2 - D34;
    x4= a2 + D34;
    if (x3 > 0)
      psp.add (x3);
    if (x4 > 0)
      psp.add (x4);
    }
  }

//----------------------------------------------------------------------------- alte Verfahren ---------------------------------------------------------------------------------------------------------------------------------------------------------------------

void quartischreduziertlagrangeuintr (real a, real b, real c, real d, cschnittpunkte& psp)
  {
  real aq, p, q, r, pq, pk, qk, a4, ak3, q8, xl;
  real l, phi3, ykr1, ykr2, ykr3, ur1, ur2, ur3, yr1, yr2, bed, xr1, xr2, xr3, xr4;
  ckomplexk yk2, u2;

  // Parameter der reduzierten quartischen Gleichung
  aq= a*a/8;
  p= aq*-3 + b;
  q= a*(aq + b/-2) + c;
  r= a*(a*aq*real (-0.09375) + a*b/16 + c/-4) + d;

  // Parameter der reduzierten kubischen Gleichung
  pq= p*p;
  pk= pq/-144 + r/-12;
  qk= p*(pq/1728 + r/-48) + q*q/128;

  // Lösungen der reduzierten kubischen Gleichung
  a4= a/-4;
  ak3= p/-6;
  q8= q/8;

  // Lösungen der kubischen Resolvente
  xl= pk*pk*pk + qk*qk;
  if (xl > 0)                                                         // xl= 0: drei reelle Lösungen der kubischen Resolvente davon eine doppelt, 4 reelle Lösungen der quartischen Gleichung davon eine doppelt
    {                                                                 // eine reelle, 2 komplexe Lösungen der kubischen Resolvente, 2 reelle Lösungen der quartischen Gleichung
    if (qk >= 0)                                                      // Fallunterscheidung notwendig, sonst zusätzliche Stern-Artefakte beim Torus
      /**/ ykr1= cbrtr (qk + sqrtr (xl));
      else ykr1= cbrtr (qk - sqrtr (xl));
    yk2= ckomplexk (ykr1/-2, ykr1*sqrtr (real (0.75)));

    ur1= sqrtr (ak3 + ykr1 - pk/ykr1);                                // Rücktransformation von ykr1
    u2= sqrtr (ak3 + yk2 - pk/yk2);                                   // Rücktransformation von yk2

    // Lösungen der reduzierten quartischen Gleichung
    yr1=  ur1 + u2.x*2;
    yr2=  ur1 - u2.x*2;

    // Lösungen der normalen quartischen Gleichung
    // Bedingung: 8*u1*u2*u3 = -q
    bed= ur1*(u2.x*u2.x + u2.y*u2.y);
    if (absr (bed + q8) < absr (bed - q8))
      {
      xr1= a4 + yr1;
      xr2= a4 + yr2;
      }
      else
      {
      xr1= a4 - yr1;
      xr2= a4 - yr2;
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
    l= sqrtr (-pk);                                                   // -pk nie unter 0 wegen xl
    phi3= acosr (qk/(pk*-l))/3;
    ykr1= l*cosr (phi3)*2;                                            // Bereichsüberschreitung acos abfangen lohnt nicht, nur ein Wert 1.000000119 (Float32) sehr selten
    ykr2= l*cosr (phi3 + PI2d)*2;
    ykr3= l*cosr (phi3 - PI2d)*2;

    if ((ak3 + ykr1 < 0) || (ak3 + ykr2 < 0) || (ak3 + ykr3 < 0))     // ist einer der Werte kleiner 0 kommen nur komplexe Lösungen raus
      return;

    ur1= sqrtr (ak3 + ykr1);
    ur2= sqrtr (ak3 + ykr2);
    ur3= sqrtr (ak3 + ykr3);

    // Bedingung: 8*u1*u2*u3 = -q
    bed= ur1*ur2*ur3;
    if (absr (bed - q8) < absr (bed + q8))
      {
      ur1= -ur1;
      ur2= -ur2;
      ur3= -ur3;
      }

    // Lösungen der reduzierten quartischen Gleichung
    xr1=  a4 + ur1 - ur2 - ur3;
    xr2=  a4 + ur2 - ur3 - ur1;
    xr3=  a4 + ur3 - ur1 - ur2;
    xr4=  a4 + ur1 + ur2 + ur3;

    // Lösungen der normalen quartischen Gleichung
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

void quartischreduziertlagrangecintr (real a, real b, real c, real d, cschnittpunkte& psp)
  {
  real aq, p, q, r, pq, pk, qk, a4, ak3, q8, xl;
  real vxl, uk1, uk2, l, phi3, ykr1, ykr2, ykr3, ur1, ur2, ur3, yr1, yr2, bed, xr1, xr2, xr3, xr4;
  ckomplexk yk2, u2;

  // Parameter der reduzierten quartischen Gleichung
  aq= a*a/8;
  p= aq*-3 + b;
  q= a*(aq + b/-2) + c;
  r= a*(a*aq*real (-0.09375) + a*b/16 + c/-4) + d;

  // Parameter der reduzierten kubischen Gleichung
  pq= p*p;
  pk= pq/-144 + r/-12;
  qk= p*(pq/1728 + r/-48) + q*q/128;

  // Lösungen der reduzierten kubischen Gleichung
  a4= a/-4;
  ak3= p/-6;
  q8= q/8;

  // Lösungen der kubischen Resolvente
  xl= pk*pk*pk + qk*qk;
  if (xl > 0)                                                         // xl= 0: drei reelle Lösungen der kubischen Resolvente davon eine doppelt, 4 reelle Lösungen der quartischen Gleichung davon eine doppelt
    {
    // eine reelle, 2 komplexe Lösungen der kubischen Resolvente, 2 reelle Lösungen der quartischen Gleichung
    vxl= sqrtr (xl);                                                  // xl immer > 0
    uk1= cbrtr (qk - vxl);
    uk2= cbrtr (qk + vxl);
    ykr1= uk1 + uk2;
    yk2= e31*uk1 + e32*uk2;

    ur1= sqrtr (ak3 + ykr1);
    u2= sqrtr (ak3 + yk2);

    // Lösungen der reduzierten quartischen Gleichung
    yr1=  ur1 + u2.x*2;
    yr2=  ur1 - u2.x*2;

    // Lösungen den normalen quartischen Gleichung
    // Bedingung: 8*u1*u2*u3 = -q
    bed= ur1*(u2.x*u2.x + u2.y*u2.y);
    if (absr (bed + q8) < absr (bed - q8))
      {
      xr1= a4 + yr1;
      xr2= a4 + yr2;
      }
      else
      {
      xr1= a4 - yr1;
      xr2= a4 - yr2;
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
    l= sqrtr (-pk);                                                   // -pk nie unter 0 wegen xl
    phi3= acosr (qk/(pk*-l))/3;
    ykr1= l*cosr (phi3)*2;                                            // Bereichsüberschreitung acos abfangen lohnt nicht, nur ein Wert 1.000000119 (Float32) sehr selten
    ykr2= l*cosr (phi3 + PI2d)*2;
    ykr3= l*cosr (phi3 - PI2d)*2;

    if ((ak3 + ykr1 < 0) || (ak3 + ykr2 < 0) || (ak3 + ykr3 < 0))     // ist einer der Werte kleiner 0 kommen nur komplexe Lösungen raus
      return;

    ur1= sqrtr (ak3 + ykr1);
    ur2= sqrtr (ak3 + ykr2);
    ur3= sqrtr (ak3 + ykr3);

    // Bedingung: 8*u1*u2*u3 = -q
    bed= ur1*ur2*ur3;
    if (absr (bed - q8) < absr (bed + q8))
      {
      ur1= -ur1;
      ur2= -ur2;
      ur3= -ur3;
      }

    // Lösungen der reduzierten quartischen Gleichung
    xr1=  a4 + ur1 - ur2 - ur3;
    xr2=  a4 + ur2 - ur3 - ur1;
    xr3=  a4 + ur3 - ur1 - ur2;
    xr4=  a4 + ur1 + ur2 + ur3;

    // Lösungen der normalen quartischen Gleichung
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
