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

/*
debugoutputquartisch ()
    {
    printtext ("  yk/-2: ");
    printreal (yk/-2);
    printtext ("\n  pq6: ");
    printreal (pq6);
    printtext ("\n  uq: ");
    printreal (uq);
    printtext ("\n  u: ");
    printreal (u);
    printtext ("\n  aq: ");
    printreal (aq);
    printtext ("\n  bq: ");
    printreal (bq);
    printtext ("\n  cq: ");
    printreal (cq);
    printtext ("\n  dq: ");
    printreal (dq);
    printtext ("\n  qq: ");
    printreal (qq);
    printtext ("\n");
    }
*/

real vquant= real (1e-8);

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

void vertausche (integer& a, integer& b)
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

//--------------------- real Funktionen -----------------------------------------------------------------------------------------

/*
_Float16 fmodr (const _Float16& a, const _Float16& b)
  {
  return _Float16 (fmodf (a, b));
  }

_Float128 fmodr (const _Float128& a, const _Float128& b)
  {
  return fmodq (a, b);
  }

_Float128 floorr (const _Float128& a)
  {
  return floorq (a);
  }

_Float16 floorr (const _Float16& a)
  {
  return _Float16 (floorq (a));
  }

_Float128 fabsr (const _Float128& a)
  {
  return fabsq (a);
  }

_Float16 fabsr (const _Float16& a)
  {
  return _Float16 (fabsf (a));
  }

_Float128 expr (const _Float128& a)
  {
  return expq (a);
  }

_Float16 expr (const _Float16& a)
  {
  return _Float16 (expf (a));
  }

_Float128 logr (const _Float128& a)
  {
  return logq (a);
  }

_Float16 logr (const _Float16& a)
  {
  return _Float16 (logf (a));
  }

_Float128 powr (const _Float128& a, const _Float128& b)
  {
  return powq (a, b);
  }

_Float16 powr (const _Float16& a, const _Float16& b)
  {
  return _Float16 (powf (a, b));
  }

_Float128 sinr (const _Float128& a)
  {
  return sinq (a);
  }

_Float16 sinr (const _Float16& a)
  {
  return _Float16 (sinf (a));
  }

_Float128 cosr (const _Float128& a)
  {
  return cosq (a);
  }

_Float16 cosr (const _Float16& a)
  {
  return _Float16 (cosf (a));
  }

_Float128 asinr (const _Float128& a)
  {
  return asinq (a);
  }

_Float16 asinr (const _Float16& a)
  {
  return _Float16 (asinf (a));
  }

_Float128 acosr (const _Float128& a)
  {
  return acosq (a);
  }

_Float16 acosr (const _Float16& a)
  {
  return _Float16 (acosf (a));
  }

_Float128 atanr (const _Float128& a)
  {
  return atanq (a);
  }

_Float16 atanr (const _Float16& a)
  {
  return _Float16 (atanf (a));
  }

_Float128 atan2r (const _Float128& a, const _Float128& b)
  {
  return atan2q (a, b);
  }

_Float16 atan2r (const _Float16& a, const _Float16& b)
  {
  return _Float16 (atan2f (a, b));
  }

_Float128 asinhr (const _Float128& a)
  {
  return asinhq (a);
  }

_Float16 asinhr (const _Float16& a)
  {
  return _Float16 (asinhf (a));
  }

_Float128 acoshr (const _Float128& a)
  {
  return acoshq (a);
  }

_Float16 acoshr (const _Float16& a)
  {
  return _Float16 (acoshf (a));
  }

_Float128 atanhr (const _Float128& a)
  {
  return atanhq (a);
  }

_Float16 atanhr (const _Float16& a)
  {
  return _Float16 (atanhf (a));
  }

_Float128 sqrtr (const _Float128& a)
  {
  return sqrtq (a);
  }

_Float16 sqrtr (const _Float16& a)
  {
  return _Float16 (sqrtf (a));
  }

_Float128 cbrtr (const _Float128& a)
  {
  return cbrtq (a);
  }

_Float16 cbrtr (const _Float16& a)
  {
  return _Float16 (cbrtf (a));
  }
*/

real q (const real x)
  {
  return x*x;
  }

float fmodr (const float& a, const float& b)
  {
  return fmodf (a, b);
  }

double fmodr (const double& a, const double& b)
  {
  return fmod (a, b);
  }

long double fmodr (const long double& a, const long double& b)
  {
  return fmodl (a, b);
  }

float floorr (const float& a)
  {
  return floorf (a);
  }

double floorr (const double& a)
  {
  return floor (a);
  }

long double floorr (const long double& a)
  {
  return floorl (a);
  }

float fabsr (const float& a)
  {
  return fabsf (a);
  }

double fabsr (const double& a)
  {
  return fabs (a);
  }

long double fabsr (const long double& a)
  {
  return fabsl (a);
  }

float expr (const float& a)
  {
  return expf (a);
  }

double expr (const double& a)
  {
  return exp (a);
  }

long double expr (const long double& a)
  {
  return expl (a);
  }

float logr (const float& a)
  {
  return logf (a);
  }

double logr (const double& a)
  {
  return log (a);
  }

long double logr (const long double& a)
  {
  return logl (a);
  }

float powr (const float& a, const float& b)
  {
  return powf (a, b);
  }

double powr (const double& a, const double& b)
  {
  return pow (a, b);
  }

long double powr (const long double& a, const long double& b)
  {
  return powl (a, b);
  }

float sinr (const float& a)
  {
  return sinf (a);
  }

double sinr (const double& a)
  {
  return sin (a);
  }

long double sinr (const long double& a)
  {
  return sinl (a);
  }

float cosr (const float& a)
  {
  return cosf (a);
  }

double cosr (const double& a)
  {
  return cos (a);
  }

long double cosr (const long double& a)
  {
  return cosl (a);
  }

float asinr (const float& a)
  {
  return asinf (a);
  }

double asinr (const double& a)
  {
  return asin (a);
  }

long double asinr (const long double& a)
  {
  return asinl (a);
  }

float acosr (const float& a)
  {
  return acosf (a);
  }

double acosr (const double& a)
  {
  return acos (a);
  }

long double acosr (const long double& a)
  {
  return acosl (a);
  }

float atanr (const float& a)
  {
  return atanf (a);
  }

double atanr (const double& a)
  {
  return atan (a);
  }

long double atanr (const long double& a)
  {
  return atanl (a);
  }

float atan2r (const float& a, const float& b)
  {
  return atan2f (a, b);
  }

double atan2r (const double& a, const double& b)
  {
  return atan2 (a, b);
  }

long double atan2r (const long double& a, const long double& b)
  {
  return atan2l (a, b);
  }

float asinhr (const float& a)
  {
  return asinhf (a);
  }

double asinhr (const double& a)
  {
  return asinh (a);
  }

long double asinhr (const long double& a)
  {
  return asinhl (a);
  }

float acoshr (const float& a)
  {
  return acoshf (a);
  }

double acoshr (const double& a)
  {
  return acosh (a);
  }

long double acoshr (const long double& a)
  {
  return acoshl (a);
  }

float atanhr (const float& a)
  {
  return atanhf (a);
  }

double atanhr (const double& a)
  {
  return atanh (a);
  }

long double atanhr (const long double& a)
  {
  return atanhl (a);
  }

float sqrtr (const float& a)
  {
  return sqrtf (a);
  }

double sqrtr (const double& a)
  {
  return sqrt (a);
  }

long double sqrtr (const long double& a)
  {
  return sqrtl (a);
  }

float cbrtr (const float& a)
  {
  return cbrtf (a);
  }

double cbrtr (const double& a)
  {
  return cbrt (a);
  }

long double cbrtr (const long double& a)
  {
  return cbrtl (a);
  }

//--------------------- cvektor2 Vektor Funktionen ------------------------------------------------------------------------------

real norm (const cvektor2 pv)
  {
  return pv%pv;
  }

real absv (const cvektor2 pv)
  {
  return sqrtr (norm (pv));
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
  real z= norm (pv);
  return ckomplexk (pv.x, -pv.y)*(1/z);
  }

ckomplexk sqrtvk (const ckomplexk pv)
  {
  ckomplexp vpol= polar180 (pv);
  vpol.b= sqrtr (vpol.b);
  vpol.w= vpol.w/2;
  return kartes (vpol);
  }

ckomplexk sqrtv (const ckomplexk pv)
  {
  real bet= sqrtr (pv.x*pv.x + pv.y*pv.y);
  real re= sqrtr ((bet + pv.x)/2);
  real im= sqrtr ((bet - pv.x)/2);
  if (pv.y < 0)
    im= -im;
  return ckomplexk (re, im);
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

ckomplexk expv (const ckomplexk pv)
  {
  return kartes (ckomplexp (expr (pv.x), (pv.y)));        // keine Einschränkung Bijektivitätsbereich
  }

ckomplexk logv (const ckomplexk pv)                       // Rückgabe eingeschränkt auf waagerechten ]-pi, pi] Streifen
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
  return expv (pv2*logv (pv1));          // Bijektivitätsbereich: waagerechter ]-pi,pi] Streifen in der rechten Halbebene ohne y-Achse
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
  return expv (pv2*logv (pv1));                             // problematisch wegen Periodizität der exp, log Funktion

/*                                                          // zerlegte Berechung um bijektiven Bereich zu erweitern
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

ckomplexp polar225 (const ckomplexk pv)      // Winkelrückgabe [0, 2pi[
  {
  ckomplexp ret= polar180 (pv);

  if (ret.w < -135)
    ret.w= ret.w + 2*PI;
  return ret;
  }

ckomplexp polar360 (const ckomplexk pv)      // Winkelrückgabe [0, 2pi[
  {
  ckomplexp ret= polar180 (pv);

  if (ret.w < 0)
    ret.w= ret.w + 2*PI;
  return ret;
  }

ckomplexp polar180 (const ckomplexk pv)     // Winkelrückgabe ]-pi, pi]
  {
  return ckomplexp (absv (pv), atan2r (pv.y, pv.x));
  }

ckomplexp polarcos180 (const ckomplexk pv)      // Winkelrückgabe ]-pi, pi]
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

ckomplexp polartan180 (const ckomplexk pv)      // Winkelrückgabe ]-pi, pi]
  {
  real phi= PI/4;

  if (fabsr (pv.x) > fabsr (pv.y))   // pv.x = 0 geht weiter
    {
    phi= atanr (pv.y/pv.x);

    if (pv.x < 0)
      {                                                // Klammer wegen ambigious else
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

    if (fabsr (pv.x) == 0)                 // Die Beträge von x und y sind ab dieser Stelle gleich deshalb ist pv der Nullvektor
      return (ckomplexp (0, 0));

    if (pv.x < 0)                          // linke Hälfte also +-135°
      phi= PI*real (0.75);

    if (pv.y < 0)                          // untere Hälfte also -45° oder -135°
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

// Skalarmultiplikation
cbasis2 operator * (const real &pf, const cbasis2 &pb)
  {
  return cbasis2 (pf*pb.x, pf*pb.y);
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

void vertausche (cvektor3& a, cvektor3& b)
  {
  cvektor3 c;
  c= a;
  a= b;
  b= c;
  }

real norm (const cvektor3 &pv)
  {
  return pv%pv;
  }

real abs (const cvektor3 &pv)
  {
  return sqrtr (norm (pv));
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
  real l (abs (pv));
  if (l <= vquant)
    return cvektor3 (0, 0, 0);  // (0, 0,0) oder (1, 1, 1) ?
  return pv/l;
  }

cvektor3 orientiere (const cvektor3 &pv)   // erster von 0 verschiedener Wert wird positiv gesetzt
  {
  cvektor3 ret (pv);
  if (ret.x < 0)
    ret= -ret;
  if (fabsr (ret.x) <= vquant)
    {
    ret.x= 0;
    if (ret.y < 0)
      ret= -ret;
    if (fabsr (ret.y) <= vquant)
      {
      ret.y= 0;
      if (ret.z < 0)
        ret= -ret;
      if (fabsr (ret.z) <= vquant)
        ret.z= 0;
      }
    }
  return ret;
  }

real winkelb (const cvektor3 &pv1, const cvektor3 &pv2)   // Betrag des Winkels zwischen 2 Vektoren ermitteln, Ergebnis: [0..pi]
  {
  real nenner (abs (pv1)*abs (pv2));
  if (nenner <= vquant)
    return 0;
  real cw= (pv1%pv2)/nenner;
  if (cw >= 1)
    return 0;
  if (cw <= -1)
    return PI;
  return acosr (cw);
  }

real winkelg (const cvektor3 &pv1, const cvektor3 &pv2)   // Betrag des Winkels zwischen 2 Geraden ermitteln, Ergebnis: [0..pi/2]
  {
  real nenner (abs (pv1)*abs (pv2));
  if (nenner <= vquant)
    return 0;
  real cw= (pv1%pv2)/nenner;
  if (cw < 0)
    cw= -cw;
  if (cw >= 1)
    return 0;
  return acosr (cw);
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
  return norm (pb.x) + norm (pb.y) + norm (pb.z);
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

cvektor3 geteigen (const cbasis3 &pb)    // Eigenvektor von einer homogenen Basis berechnen (det = 0)
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
  if (abs (pv) <= vquant)   // Nullvektor als Spiegelachse ist Punktspiegelung also Inversionsmatrix zurückgeben
    return cbasis3 (-1);
  cvektor3 nv= normiere (pv);
  return cbasis3 (1) - 2*cbasis3 (nv, nv, nv)*cbasis3 (nv);
  }

// Spiegelungsmatrix aus (Drehung von 180° um Spiegelachse) berechnen
cbasis3 getdrehspiegbasis (const cvektor3 &pv)
  {
  if (abs (pv) <= vquant)   // Nullvektor als Spiegelachse ist Punktspiegelung also Inversionsmatrix zurückgeben
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
  if (dif <= vquant)
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

real norm (const cvektor4 &pv)
  {
  return pv%pv;
  }

real abs (const cvektor4 &pv)
  {
  return sqrtr (norm (pv));
  }

// Kreuzfunktion: unärer Operator, senkrechten Vektor in positver Orientierung ermitteln
cvektor4 senk (const cvektor4 &pv)
  {
  return cvektor4 (-pv.i, pv.r, -pv.ij, pv.j);
  }

cvektor4 normiere (const cvektor4 &pv)
  {
  const real q= norm (pv);
  if (q <= vquant)
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
  if (dif <= vquant)
    return 1;
  return 0;
  }

//---------- cvektor4 Funktionen für Quaternionen -------------------------------------------------------------------------------------

// Kehrwert
cvektor4 kw (const cvektor4 &pv)
  {
  return cvektor4 (pv.r, -pv.i, -pv.j, -pv.ij)/norm (pv);
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
  return cvektor4 (cosr (wiha), sinr (wiha)*achse);                // negativer Winkel invertiert die Drehachse statt Winkel
  }                                                                // Darstellung ist eindeutig. Das negative Quaternion, dessen Drehung zur gleichen Endposition führt (Matrix) ist eine andere Drehung
                                                                   // 90° nach rechts drehen führt zur gleichen Endposition wie 270° nach links drehen, aber es sind verschiedene Drehungen
                                                                   // Somit wird nicht eine Drehung durch 2 Quaternionen repräsentiert, sondern jede Drehung ist eindeutig durch genau ein Quaternion repräsentiert.
                                                                   // Mehrdeutigkeit kommt durch Wicklungen zustande, d.h. wenn der Winkel größer als 360° ist.
                                                                   // Jede Endposition wird durch genau 2 Drehungen erreicht. Das gilt auch für die Anfangsposition.
                                                                   // Die Anfangsposition kann durch eine 0° Drehung oder durch eine 360° Drehung erreicht werden. In beiden Fällen spielt die Drehachse keine Rolle.

cvektor4 winkelachsefromquaternion (const cvektor4 pq)
  {
  if (pq.r >= 1 - vquant)
    return cvektor4 (0, 0, 0, 0);
  if (pq.r <= -1 + vquant)
    return cvektor4 (2*PI, 0, 0, 0);
  real drehw= acosr (pq.r)*2;
  cvektor3 achse (normiere (cvektor3 (pq.i, pq.j, pq.ij)));
  if (fabsr (achse.x) <= vquant)
    achse.x= 0;
  if (fabsr (achse.y) <= vquant)
    achse.y= 0;
  if (fabsr (achse.z) <= vquant)
    achse.z= 0;
  return cvektor4 (drehw, achse.x, achse.y, achse.z);
  }

cvektor4 qwafrommatrix (const cbasis3 &pdreh)  // nur für Drehmatrizen, nicht für Drehspiegelungsmatrizen
  {
  // Gibt den Winkel in Quaternionenform [-1 bis 1] und die Drehachse unnormiert aber richtig orientiert zurück.

  // ********************* Realteil direkt aus der Matrix berechnen, Problem bei 0° und 180° Drehungen abfangen
  real qr= 1 + pdreh.x.x + pdreh.y.y + pdreh.z.z;              // qr [4..0] = [0..180]°
  if (qr >= 4 - vquant)             //   0° Drehung
    return cvektor4 (1, 0, 0, 0);

  // ********************* Drehachse durch Eigenwerte berechnen, Eigenvektor numerisch stabil, Länge: [5 1/3 bis 16]
  cbasis3 hdreh (pdreh);
  hdreh.x.x-= 1;
  hdreh.y.y-= 1;
  hdreh.z.z-= 1;
  cvektor3 drehachse (geteigen (hdreh));

  // Drehachse richtig orientieren
  if (qr <= vquant)                 // 180° Drehung: Es gibt 2 Drehachsen statt nur einer
    {
    qr= 0;
    drehachse= orientiere (drehachse);  // bei 180° Drehung Achse mit positven ersten von 0 verschiedenem Wert aussuchen. (besser kleinste Anzahl von Minuszeichen)
    }
    else                          // Drehung zwischen 0° und 180°
    {
    // Drehachse richtig orientieren (Testen ob die Drehung ein positives Volumen erzeugt, versagt bei 0° und 180° Drehungen da Volumen dann 0 ist)
    cvektor3 s1 (~drehachse);
    cvektor3 s2 (pdreh*s1);
    if (((drehachse^s1)%s2) < 0)
      drehachse= -drehachse;
    }
  return cvektor4 (sqrtr (qr)/2, drehachse.x, drehachse.y, drehachse.z);
  }

cvektor4 winkelachsefrommatrix (const cbasis3 &pdreh)    // Bei Drehspiegelungen wird der Spiegelanteil durch Inversion der Drehspiegelungsmatrix entfernt und dann Winkel und Achse der verbleibenden Drehmatrix bestimmt
  {
  cvektor4 qwa;
  if (det (pdreh) > 0)
    qwa= qwafrommatrix (pdreh);
    else
    qwa= qwafrommatrix (-pdreh);
  if (fabsr (qwa.i) <= vquant)
    qwa.i= 0;
  if (fabsr (qwa.j) <= vquant)
    qwa.j= 0;
  if (fabsr (qwa.ij) <= vquant)
    qwa.ij= 0;
  cvektor3 achse (qwa.i, qwa.j, qwa.ij);
  achse= normiere (achse);
  if (det (pdreh) < 0)
    {
    real wi= 2*acosr (qwa.r);
    if (aehnlich (wi, 0))
      return cvektor4 (-2*PI, achse.x, achse.y, achse.z);                          // pq.r = -360°: Matrix ist die Punktspiegelungsmatrix (Inversion (-id))
      //return cvektor4 (0, achse.x, achse.y, achse.z);                                   // Problemfall 0° wäre positiver Winkel also Drehung und nicht Drehspiegelung
    return cvektor4 (-2*acosr (qwa.r), achse.x, achse.y, achse.z);
    }
  return cvektor4 (2*acosr (qwa.r), achse.x, achse.y, achse.z);
  }

cbasis3  matrixfromwinkelachse (const cvektor4 pq)
  {
  return matrixfromquaternion (quaternionfromwinkelachse (pq));
  }

cvektor4 quaternionfrommatrix (const cbasis3 &pdreh)  // Funktioniert bei 0° und 180° Drehungen
  {
  cvektor4 qwa (qwafrommatrix (pdreh));                                 // Mehrdeutigkeit der Achse bei 180° Drehungen
  if (qwa.r >= 1 - vquant)      // Drehung ist 0° Drehung
    return qwa;                // 1 zurückgeben
  cvektor3 achse (cvektor3 (qwa.i, qwa.j, qwa.ij));
  real k= sqrtr (1 - qwa.r*qwa.r)/abs (achse);
  return cvektor4 (qwa.r, k*achse);
  }

cvektor4 quaternionfrommatrix2 (const cbasis3 &pdreh)  // Kreuzproduktversion: versagt bei 180° Drehungen
  {
  real qr= sqrtr (1 + pdreh.x.x + pdreh.y.y + pdreh.z.z);
  if (qr <= vquant)                      // 180° Drehung
    return cvektor4 (0, 1, 0, 0);       // Bullshit zurückgeben
  real qi= (pdreh.y.z - pdreh.z.y)/qr;
  real qj= (pdreh.z.x - pdreh.x.z)/qr;
  real qij=(pdreh.x.y - pdreh.y.x)/qr;
  return cvektor4 (qr, qi, qj, qij)/2;
  }

cbasis3 matrixfromquaternion (const cvektor4 pq)   // Es kommen nur 2-fache Produkte vor, da mat (q) = mat (-q)
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
  if (cosbr > vquant)  // Breite nicht polar
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
  if (cosbr <= vquant)  // Spezialfall Breite polar
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

void kubischreduziertu1 (ckomplexk p, ckomplexk q, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3)
  {
  ckomplexk  u1, u2, u, z1, z2, z3;

  quadratisch (q, p*p*p/-27, u1, u2);

  if (absv (u1) > absv (u2))                 // die betragsmäßig größere Lösung nehmen um von der Division durch 0 wegzukommen
    u= u1;
    else
    u=u2;

  cbrtv (u, z1, z2, z3);

  y1= z1 - p/(z1*3);
  y2= z2 - p/(z2*3);
  y3= z3 - p/(z3*3);
  }

void kubischreduziertu3 (ckomplexk p, ckomplexk q, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3)
  {
  ckomplexk  u1, u2, u, z1, z2, z3;

  quadratisch (q*27, p*p*p*-27, u1, u2);

  if (absv (u1) > absv (u2))                 // die betragsmäßig größere Lösung nehmen um von der Division durch 0 wegzukommen
    u= u1;
    else
    u=u2;

  cbrtv (u, z1, z2, z3);

  y1= z1/3 - p/z1;
  y2= z2/3 - p/z2;
  y3= z3/3 - p/z3;
  }

void kubischreduziertreell (real p, real q, real& y)
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

void kubischreduziertk (ckomplexk a, ckomplexk b, ckomplexk c, ckomplexk& p, ckomplexk& q)
  {
  p= a*a/-3 + b;
  q= a*(a*a/real (4.5) - b)/3 + c;
  }

void kubisch (ckomplexk a, ckomplexk b, ckomplexk c, ckomplexk& x1, ckomplexk& x2, ckomplexk& x3)
  {
  ckomplexk p, q, y1, y2, y3;

  kubischreduziertk (a, b, c, p, q);
  kubischreduziertcardano3 (p, q, y1, y2, y3);

  x1= (y1 - a)/3;
  x2= (y2 - a)/3;
  x3= (y3 - a)/3;
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

void kubischeresolvente1z (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& z1, ckomplexk& z2, ckomplexk& z3)
  {
  ckomplexk pk, qk;

  pk= (p*p + r*12)/-3;
  qk= p*(r*36 - p*p)/real (13.5) - q*q;

  kubischreduziertcardano (pk, qk, z1, z2, z3);
  }

void kubischeresolvente3z (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& z1, ckomplexk& z2, ckomplexk& z3)
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

  a1=  q/v/-2;
  a2=  q/v/2;
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

  a1=  u;
  a2= -u;

  v= sqrtv (z*z - r);

  // Bedingung -2uv = q
  bed= u*v*-2;
  if (absv (bed + q) < absv (bed - q))
    v= -v;

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

void quartischreduziertbuch3 (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4)
  {
  ckomplexk z1, z2, z3, z, u, v, bed, a1, a2, b1, b2;

  kubischeresolvente3z (p, q, r, z1, z2, z3);

  z= z1;
  u= sqrtv ((z - p*2)/3);

  a1=  u;
  a2= -u;

  v= z + p;
  v= sqrtv (v*v - r*36)/6;

  // Bedingung -2uv = q
  bed= u*v*-2;
  if (absv (bed + q) < absv (bed - q))
    v= -v;

  b1= (z + p)/6 + v;
  b2= (z + p)/6 - v;

  quadratisch (a1, b1, y1, y2);
  quadratisch (a2, b2, y3, y4);
  }

void quartischreduziertpdfw23 (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4)
  {
  ckomplexk z1, z2, z3, z, u, a1, a2, b1, b2;

  kubischeresolvente3z (p, q, r, z1, z2, z3);

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

  kubischeresolvente3z (p, q, r, z1, z2, z3);

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
  quartischreduziertlagrange (p, q, r, y1, y2, y3, y4);
  //quartischreduziertbuch3 (p, q, r, y1, y2, y3, y4);
  //quartischreduziertpdfw23 (p, q, r, y1, y2, y3, y4);
  //quartischreduziertlagrange3 (p, q, r, y1, y2, y3, y4);

  a4= a/4;
  x1= y1 - a4;
  x2= y2 - a4;
  x3= y3 - a4;
  x4= y4 - a4;
  }

//-------------------- quartisch integriert ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void quartischdiffpintrc (real aq, real bq, real cq, real dq, ckomplexk& x1, ckomplexk& x2, ckomplexk& x3, ckomplexk& x4)
  {
  real aqq, pq, qq, rq, rq4, pqq, pk, qk, aq4;
  ckomplexk yk, z, u, d, e, D1, D2;

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
  yk= cbrtv (qk + sqrtv (ckomplexk (pk*pk*pk + qk*qk)));

  // Lösungen der beiden quadratischen Gleichungen
  z= pq/3 - pk/yk + yk;
  u= sqrtv (z - pq)/2;

  d= (z + pq)/-4;
  e= qq/u/4;
  D1= sqrtv (d + e);
  D2= sqrtv (d - e);

  // Lösungen der normalen quartischen Gleichung
  aq4= aq/-4;
  x1= aq4 - u - D1;
  x2= aq4 - u + D1;
  x3= aq4 + u - D2;
  x4= aq4 + u + D2;
  }

void quartischdiffpintr (real aq, real bq, real cq, real dq, cschnittpunkte& psp)
  {
  real aqq, pq, qq, rq, pqq, rq4, pk, qk, xl, vxl, l, yk, pq6, uq, u, z, qqu, b1, b2, aq4, VD, x1, x2;

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
  xl= qk*qk + pk*pk*pk;
  if (xl >= 0)
    {
    //vxl= sqrtr (xl);
    //yk= (cbrtr (qk + vxl) + cbrtr (qk - vxl))/-2;
    yk= cbrtr (qk + sqrtr (xl));
    yk= (yk - pk/yk)/-2;
    }
    else
    {
    l= -sqrtr (-pk);
    yk= l*cosr (acosr (qk/(pk*l))/3);
    }

  // Lösungen der beiden quadratischen Gleichungen (ak=-pq für Rückreduzierung)
  pq6= pq/6;
  uq= yk/-2 - pq6;
  u= sqrtr (uq);

  z= pq6 - yk;
  qqu= qq/u/4;

  b1= z - qqu;
  b2= z + qqu;

  // Lösungen normale quartische Gleichung
  aq4= aq/-4;
  if (uq >= b1)
    {
    VD= sqrtr (uq - b1);
    x1= aq4 - u - VD;
    x2= aq4 - u + VD;
    if (x1 > 0)
      psp.add (x1);
    if (x2 > 0)
      psp.add (x2);
    }
  if (uq >= b2)
    {
    VD= sqrtr (uq - b2);
    x1= aq4 + u - VD;
    x2= aq4 + u + VD;
    if (x1 > 0)
      psp.add (x1);
    if (x2 > 0)
      psp.add (x2);
    }
  }

void quartischbuchuintr (real aq, real bq, real cq, real dq, cschnittpunkte& psp)
  {
  real aqq, pq, qq, rq, pqq, pk, qk, xl, vxl, l, yk, z, u, uq, qqu, b1, b2, aq4, VD, x1, x2;

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
  xl= qk*qk + pk*pk*pk;
  if (xl >= 0)
    {
    vxl= sqrtr (xl);
    yk= cbrtr (qk + vxl) + cbrtr (qk - vxl);
    }
    else
    {
    l= -sqrtr (-pk);
    yk= l*cosr (acosr (qk/(pk*l))/3)*-2;
    }

  // Lösungen der beiden quadratischen Gleichungen (ak=-pq/2 für Rückreduzierung)
  uq= yk/2 - pq/6;
  u= sqrtr (uq);

  z= yk + pq/6;
  qqu= qq/u/4;

  b1= z - qqu;
  b2= z + qqu;

  // Lösungen normale quartische Gleichung
  aq4= aq/-4;
  if (uq >= b1)
    {
    VD= sqrtr (uq - b1);
    x1= aq4 - u - VD;
    x2= aq4 - u + VD;
    if (x1 > 0)
      psp.add (x1);
    if (x2 > 0)
      psp.add (x2);
    }
  if (uq >= b2)
    {
    VD= sqrtr (uq - b2);
    x1= aq4 + u - VD;
    x2= aq4 + u + VD;
    if (x1 > 0)
      psp.add (x1);
    if (x2 > 0)
      psp.add (x2);
    }
  }

void quartischbuchvintr (real aq, real bq, real cq, real dq, cschnittpunkte& psp)
  {
  real aqq, pq, qq, rq, pqq, pk, qk, xl, vxl, l, yk, z, v, vq, qqv, b1, b2, aq4, VD, x1, x2;

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
  xl= qk*qk + pk*pk*pk;
  if (xl >= 0)
    {
    vxl= sqrtr (xl);
    yk= cbrtr (qk + vxl) + cbrtr (qk - vxl);
    }
    else
    {
    l= -sqrtr (-pk);
    yk= l*cosr (acosr (qk/(pk*l))/3)*-2;
    }

  // Lösungen der beiden quadratischen Gleichungen (ak=-pq/2 für Rückreduzierung)
  z= yk + pq/6;
  v= sqrtr (z*z - rq);

  qqv= qq/v/4;
  vq= qqv*qqv;

  b1= z + v;
  b2= z - v;

  // Lösungen normale quartische Gleichung
  aq4= aq/-4;
  if (vq >= b1)
    {
    VD= sqrtr (vq - b1);
    x1= aq4 + qqv - VD;
    x2= aq4 + qqv + VD;
    if (x1 > 0)
      psp.add (x1);
    if (x2 > 0)
      psp.add (x2);
    }
  if (vq >= b2)
    {
    VD= sqrtr (vq - b2);
    x1= aq4 - qqv - VD;
    x2= aq4 - qqv + VD;
    if (x1 > 0)
      psp.add (x1);
    if (x2 > 0)
      psp.add (x2);
    }
  }

void quartischbuchfintr (real aq, real bq, real cq, real dq, cschnittpunkte& psp)
  {
  real aqq, pq, qq, rq, pqq, pk, qk, xl, vxl, l, yk, pq6, uq, u, z, v, bed, b1, b2, aq4, VD, x1, x2;

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
  xl= qk*qk + pk*pk*pk;
  if (xl >= 0)
    {
    vxl= sqrtr (xl);
    yk= cbrtr (qk + vxl) + cbrtr (qk - vxl);
    }
    else
    {
    l= -sqrtr (-pk);
    yk= l*cosr (acosr (qk/(pk*l))/3)*-2;
    }

  // Lösungen der beiden quadratischen Gleichungen (ak=-pq/2 für Rückreduzierung)
  pq6= pq/6;
  uq= yk/2 - pq6;
  u= sqrtr (uq);

  z= yk + pq6;
  v= sqrtr (z*z - rq);

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
    VD= sqrtr (uq - b1);
    x1= aq4 - u - VD;
    x2= aq4 - u + VD;
    if (x1 > 0)
      psp.add (x1);
    if (x2 > 0)
      psp.add (x2);
    }
  if (uq >= b2)
    {
    VD= sqrtr (uq - b2);
    x1= aq4 + u - VD;
    x2= aq4 + u + VD;
    if (x1 > 0)
      psp.add (x1);
    if (x2 > 0)
      psp.add (x2);
    }
  }

void quartischlagrangeintru (real aq, real bq, real cq, real dq, cschnittpunkte& psp)
  {
  real aqq, pq, qq, rq, pqq, pk, qk, xl, l, aq4, ak3, qq8, yr1, yrx, yry, yr2, yr3, bedr, ur1, ur2, ur3, yqr1, yqr2, yqr3, yqr4, xr1, xr2, xr3, xr4;
  ckomplexk yk2, yk3, u1, u2, u3, yq1, yq2, yq3, yq4, bed, x1, x2, x3, x4;

  // Parameter reduzierte quartische Gleichung
  aqq= aq*aq/8;
  pq= aqq*-3 + bq;
  qq= aq*(aqq + bq/-2) + cq;
  rq= aq*(aq*aqq*(real (3)/-32) + aq*bq/16 + cq/-4) + dq;

  // Parameter reduzierte kubische Gleichung
  pqq= pq*pq;
  pk= pqq/-144 + rq/-12;
  qk= pq*(pqq/1728 + rq/-48) + qq*qq/128;

  // Lösungen reduzierte kubische Gleichung
  aq4= aq/-4;
  ak3= pq/-6;
  qq8= qq/8;
  xl= qk*qk + pk*pk*pk;
  if (xl > 0)
    {
    //großer Aussschnitt eine reelle, 2 komplexe Lösungen
    yr1= cbrtr (qk + sqrtr (xl));         // xl immer größer als 0
    yrx= yr1/-2;
    yry= yr1*sqrtr (real (0.75));
    yk2= ckomplexk (yrx, yry);
    yk3= ckomplexk (yrx, -yry);

    if ((yr1 == 0) || (ak3 + yr1 - pk/yr1 <= 0))             // starke Ungenauigkeit ab 3. Stelle nach dem Komma
      {
      //return;
      real vxl= sqrtr (xl);  // xl immer > 0                 // Berechnung der Lösungen nach Cardano
      real uk1= cbrtr (qk - vxl);
      real uk2= cbrtr (qk + vxl);

      //yr1= uk1 + uk2;
      yk2= e31*uk1 + e32*uk2;
      yk3= ckomplexk (yk2.x, -yk2.y);

      real akyr= ak3 + yr1;
      if (akyr < 0)
        {
        ur1= 0;       // Negativwerte durch Ungenauigkeit der Differenz die bei Genauigkeit 0 wäre
        //return;
        }
        else
        ur1= sqrtr (akyr);
      u2= sqrtv (ak3 + yk2);
      u3= sqrtv (ak3 + yk3);
      }
      else
      {
      ur1= sqrtr (ak3 + yr1 - pk/yr1);
      u2= sqrtv (ak3 + yk2 - pk/yk2);
      u3= sqrtv (ak3 + yk3 - pk/yk3);
      }

    // Lösungen reduzierte quartische Gleichung
    yq1=  ur1 + u2 + u3;
    yq2=  ur1 - u2 - u3;
    yq3=  u2 - ur1 - u3;
    yq4=  u3 - ur1 - u2;

    // Lösungen normale quartische Gleichung
    // Bedingung: 8*u1*u2*u3 = -qq
    bed= ur1*u2*u3;
    if (absv (bed + qq8) < absv (bed - qq8))
      {
      x1= aq4 + yq1;
      x2= aq4 + yq2;
      x3= aq4 + yq3;
      x4= aq4 + yq4;
      }
      else
      {
      x1= aq4 - yq1;
      x2= aq4 - yq2;
      x3= aq4 - yq3;
      x4= aq4 - yq4;
      }

    // reell-positive Lösungen an den Schnittpunktspeicher übergeben
    if (arg (x1) < 1e-8)
      psp.add (x1.x);
    if (arg (x2) < 1e-8)
      psp.add (x2.x);
    if (arg (x3) < 1e-8)
      psp.add (x3.x);
    if (arg (x4) < 1e-8)
      psp.add (x4.x);
    }
    else
    {
    // kleiner Aussschnitt 3 reelle Lösungen
    l= -sqrtr (-pk);   // -pk nie unter 0 wegen xl
    if (qk/(pk*l) < -1)                                     // 1.000000119  immer nur dieser Wert (Bereichsüberschreitung durch Ungenauigkeit)
      {
      yr1= -l;
      yr2= l*2;
      yr3= -l;
      }
    else if (qk/(pk*l) > 1)
      {
      yr1= l*-2;
      yr2= l;
      yr3= l;
      }
    else
      {
      yr1= l*cosr (acosr (qk/(pk*l))/3)*-2;
      yr2= l*cosr (acosr (qk/(pk*l))/3 + PI23)*-2;
      yr3= l*cosr (acosr (qk/(pk*l))/3 - PI23)*-2;
      }

    if ((ak3 + yr1 < 0) || (ak3 + yr2 < 0) || (ak3 + yr3 < 0))    // ist einer der Werte 0 kommen nur komplexe Lösungen raus
      return;
    ur1= sqrtr (ak3 + yr1);
    ur2= sqrtr (ak3 + yr2);
    ur3= sqrtr (ak3 + yr3);

    // Lösungen reduzierte quartische Gleichung
    yqr1=  ur1 + ur2 + ur3;
    yqr2=  ur1 - ur2 - ur3;
    yqr3=  ur2 - ur1 - ur3;
    yqr4=  ur3 - ur1 - ur2;

    // Lösungen normale quartische Gleichung
    // Bedingung: 8*u1*u2*u3 = -qq
    bedr= ur1*ur2*ur3;
    if (fabsr (bedr + qq8) < fabsr (bedr - qq8))
      {
      xr1= aq4 + yqr1;
      xr2= aq4 + yqr2;
      xr3= aq4 + yqr3;
      xr4= aq4 + yqr4;
      }
      else
      {
      xr1= aq4 - yqr1;
      xr2= aq4 - yqr2;
      xr3= aq4 - yqr3;
      xr4= aq4 - yqr4;
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

void quartischlagrangeintrc (real aq, real bq, real cq, real dq, cschnittpunkte& psp)
  {
  real aqq, pq, qq, rq, pqq, pk, qk, xl, vxl, uk1, uk2, l, aq4, ak3, qq8, yr1, yr2, yr3, bedr, akyr, ur1, ur2, ur3, yqr1, yqr2, yqr3, yqr4, xr1, xr2, xr3, xr4;
  ckomplexk yk2, yk3, u1, u2, u3, yq1, yq2, yq3, yq4, bed, x1, x2, x3, x4;

  // Parameter reduzierte quartische Gleichung
  aqq= aq*aq/8;
  pq= aqq*-3 + bq;
  qq= aq*(aqq + bq/-2) + cq;
  rq= aq*(aq*aqq*(real (3)/-32) + aq*bq/16 + cq/-4) + dq;

  // Parameter reduzierte kubische Gleichung
  pqq= pq*pq;
  pk= pqq/-144 + rq/-12;
  qk= pq*(pqq/1728 + rq/-48) + qq*qq/128;

  // Lösungen reduzierte kubische Gleichung
  aq4= aq/-4;
  ak3= pq/-6;
  qq8= qq/8;
  xl= qk*qk + pk*pk*pk;

  if (xl > 0)
    {
    //großer Aussschnitt eine reelle, 2 komplexe Lösungen
    vxl= sqrtr (xl);  // xl immer > 0
    uk1= cbrtr (qk - vxl);
    uk2= cbrtr (qk + vxl);

    yr1= uk1 + uk2;
    yk2= e31*uk1 + e32*uk2;
    yk3= ckomplexk (yk2.x, -yk2.y);

    akyr= ak3 + yr1;
    if (akyr < 0)
      {
      ur1= 0;       // Negativwerte durch Ungenauigkeit der Differenz die bei Genauigkeit 0 wäre
      //return;
      }
      else
      ur1= sqrtr (akyr);
    u2= sqrtv (ak3 + yk2);
    u3= sqrtv (ak3 + yk3);

    // Lösungen reduzierte quartische Gleichung
    yq1=  ur1 + u2 + u3;
    yq2=  ur1 - u2 - u3;
    yq3=  u2 - ur1 - u3;
    yq4=  u3 - ur1 - u2;

    // Lösungen normale quartische Gleichung
    // Bedingung: 8*u1*u2*u3 = -qq
    bed= ur1*u2*u3;
    if (absv (bed + qq8) < absv (bed - qq8))
      {
      x1= aq4 + yq1;
      x2= aq4 + yq2;
      x3= aq4 + yq3;
      x4= aq4 + yq4;
      }
      else
      {
      x1= aq4 - yq1;
      x2= aq4 - yq2;
      x3= aq4 - yq3;
      x4= aq4 - yq4;
      }

    // reell-positive Lösungen an den Schnittpunktspeicher übergeben
    if (arg (x1) < quantr)
      psp.add (x1.x);
    if (arg (x2) < quantr)
      psp.add (x2.x);
    if (arg (x3) < quantr)
      psp.add (x3.x);
    if (arg (x4) < quantr)
      psp.add (x4.x);
    }
    else
    {
    // kleiner Aussschnitt 3 reelle Lösungen
    l= -sqrtr (-pk);   // -pk nie unter 0 wegen xl
    if (qk/(pk*l) < -1)                                     // 1.000000119  immer nur dieser Wert (Bereichsüberschreitung durch Ungenauigkeit)
      {
      yr1= -l;
      yr2= l*2;
      yr3= -l;
      }
    else if (qk/(pk*l) > 1)
      {
      yr1= l*-2;
      yr2= l;
      yr3= l;
      }
    else
      {
      yr1= l*cosr (acosr (qk/(pk*l))/3)*-2;
      yr2= l*cosr (acosr (qk/(pk*l))/3 + PI23)*-2;
      yr3= l*cosr (acosr (qk/(pk*l))/3 - PI23)*-2;
      }

    if ((ak3 + yr1 < 0) || (ak3 + yr2 < 0) || (ak3 + yr3 < 0))    // ist einer der Werte 0 kommen nur komplexe Lösungen raus
      return;
    ur1= sqrtr (ak3 + yr1);
    ur2= sqrtr (ak3 + yr2);
    ur3= sqrtr (ak3 + yr3);

    // Lösungen reduzierte quartische Gleichung
    yqr1=  ur1 + ur2 + ur3;
    yqr2=  ur1 - ur2 - ur3;
    yqr3=  ur2 - ur1 - ur3;
    yqr4=  ur3 - ur1 - ur2;

    // Lösungen normale quartische Gleichung
    // Bedingung: 8*u1*u2*u3 = -qq
    bedr= ur1*ur2*ur3;
    if (fabsr (bedr + qq8) < fabsr (bedr - qq8))
      {
      xr1= aq4 + yqr1;
      xr2= aq4 + yqr2;
      xr3= aq4 + yqr3;
      xr4= aq4 + yqr4;
      }
      else
      {
      xr1= aq4 - yqr1;
      xr2= aq4 - yqr2;
      xr3= aq4 - yqr3;
      xr4= aq4 - yqr4;
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

