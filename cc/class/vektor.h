#ifndef vektor_h
#define vektor_h

#include <cmath>                                // M_PIl, cosl, sinl
//#include <quadmath.h>                           // M_PIq, cosq, sinq  quadmath_snprintf %Q    -lquadmath      // fehlt auf Arm-Architektur AARCH64

// ------------------------------------------------------------------------  Datentypen -----------------------------------------------------

typedef signed long long integer;
//                                                                                                                                           xray N97  raspi5  Apfel N97  Apfel raspi5                 orangepi5
// ------------------------- 16 Bit -------------------------------------------------------------------------------------------------------------
//typedef _Float16 real;        //                //   11 Bit:  3.31 Stellen                                                                 5.00              3.96

// ------------------------- 32 Bit -------------------------------------------------------------------------------------------------------------
typedef _Float32 real;        // hw             //   24 Bit:  7.22 Stellen  6/8 Stellen (verlässlich/unterscheidbar)                       5.88      5.88    0.36          0.55                                 7.14
//typedef float real;           // hw             //   1.45 mal schneller als __float80                                                      5.88      5.88    0.36          0.55

// ------------------------- 64 Bit -------------------------------------------------------------------------------------------------------------
//typedef _Float64 real;        // hw             //   53 Bit: 15.95 Stellen 15/16 Stellen (verlässlich/unterscheidbar)                      7.69      5.88    0.61          0.42       28.04              6.66 8.33     20.06
//typedef double real;          // hw           //     1.2 mal langsamer als __float80                                                       5.88      5.88    0.61          0.42

// ------------------------- 80/128 Bit ---------------------------------------------------------------------------------------------------------
//typedef __float80 real;       // hw             //   64 Bit: 19.26 Stellen 18/20 Stellen (verlässlich/unterscheidbar)                      6.90              0.53
//typedef long double real;     // hw                                                                                                        6.90      4.34    0.53         10.84                                  5.55

// ------------------------ 128 Bit -------------------------------------------------------------------------------------------------------------
//typedef _Float128 real;       // sw             //  113 Bit: 34.01 Stellen 33/35 Stellen (verlässlich/unterscheidbar)                      3.84      4.34    9.39         10.84
//typedef __float128 real;      // sw             //  20 mal langsamer als __float80                                                         3.84              9.39

struct cvektor2
  {
  real x, y;

  cvektor2 ();
  cvektor2 (const real &px, const real &py);
  };

struct ckomplexk : public cvektor2
  {
  ckomplexk ();
  ckomplexk (const real &pr);
  ckomplexk (const real &px, const real &py);
  };

struct ckomplexp
  {
  real b, w;

  ckomplexp ();
  ckomplexp (const real &pr);
  ckomplexp (const real &pb, const real &pw);
  };

struct ckugelk
  {
  real x, y;

  ckugelk ();
  ckugelk (const real &px, const real &py);
  };

struct cbasis2
  {
  cvektor2 x, y;

  cbasis2 ();
  cbasis2 (const real &pk);
  cbasis2 (const cvektor2 &pv);
  cbasis2 (const cvektor2 &px, const cvektor2 &py);
  };

struct cvektor3
  {
  real x, y, z;

  cvektor3 ();
  cvektor3 (const real &pr);
  cvektor3 (const real &px, const real &py, const real &pz);
  };

struct cbasis3
  {
  cvektor3 x, y, z;

  cbasis3 ();
  cbasis3 (const real &pk);
  cbasis3 (const cvektor3 &pv);
  cbasis3 (const cvektor3 &px, const cvektor3 &py, const cvektor3 &pz);
  };

struct cvektor4
  {
  real r, i, j, ij;

  cvektor4 ();
  cvektor4 (const real &pr, const real &pi, const real &pj, const real &pij);
  cvektor4 (const real &pr, const cvektor3 &pv);
  };

struct cquaternion : public cvektor4
  {
  cquaternion ();
  cquaternion (const real &pr, const real &pi, const real &pj, const real &pij);
  cquaternion (const real &pr, const cvektor3 &pv);
  };

struct cbasis4
  {
  cvektor4 r, i, j, ij;

  cbasis4 ();
  cbasis4 (const real &pk);
  cbasis4 (const cvektor4 &pv);
  cbasis4 (const cvektor4 &pr, const cvektor4 &pi, const cvektor4 &pj, const cvektor4& pij);
  };

struct cvektor7
  {
  real r, i, j, ij, ji, iji, jij;

  cvektor7 ();
  cvektor7 (const real &pr, const real &pi, const real &pj, const real &pij, const real &pji, const real &piji, const real &pjij);
  };

struct cvektor8
  {
  real r, i, j, ij, o, io, jo, ijo;

  cvektor8 ();
  cvektor8 (const real &pr, const real &pi, const real &pj, const real &pij, const real &po, const real &pio, const real &pjo, const real &pijo);
  };

struct coktonion : public cvektor8
  {
  };

//--------------------------------------------------------------------------------------- Konstanten --------------------------------------------------------------------------------------------------

// reelle Konstanten
const real quantr= real (powl (0.1, sizeof (real)));
const real PI (real (M_PIl));                                                         // die Konstante pi vom Typ real
const real PIh (real (M_PIl/2));                                                      // pi/2
const real PI2 (real (M_PIl*2));                                                      // 2pi
const real PI23 (real (M_PIl*2/3));                                                   // die Konstante 2/3*pi vom Typ real
const real gk (real (0.5 + sqrtl (1.25)));                                            // goldene Schnitt g= (1 + √5)/2 = 2*cos 36°                        = 1.61803398...         x² - x - 1 = 0
const real tk (real ((1 + cbrtl (19 + sqrtl (297)) + cbrtl (19 - sqrtl (297)))/3));   // Tribonacci Konstante  t= (1 + t1 + t2)/3    t1,2= ∛(19 ± 3√33)   = 1.83928675...    x³ - x² - x - 1 = 0

// kartesischkomplexe Konstanten
const ckomplexk nullk (0, 0);
const ckomplexk einsk (1, 0);
const ckomplexk ik (0, 1);
const ckomplexk e31 (real (-0.5),  real (sqrtl (0.75)));
const ckomplexk e32 (real (-0.5), -real (sqrtl (0.75)));

// polarkomplexe Konstanten
const ckomplexp nullp (0);
const ckomplexp einsp (1);
const ckomplexp ew2 (-1);
const ckomplexp ew3 (1, PI*2/3);
const ckomplexp ew4 (1, PI/2);
const ckomplexp ew5 (1, PI*2/5);

// cvektor3 Konstanten
const cvektor3 nullv3 (0);
const cvektor3 xvektor3 (1, 0, 0);
const cvektor3 yvektor3 (0, 1, 0);
const cvektor3 zvektor3 (0, 0, 1);

// quaternionische Konstanten
const cquaternion nullq (0, 0, 0, 0);
const cquaternion einsq (1, 0, 0, 0);
const cquaternion iq    (0, 1, 0, 0);
const cquaternion jq    (0, 0, 1, 0);
const cquaternion ijq   (0, 0, 0, 1);

// Basiskonstanten
const cbasis2 einsb2 (1);
const cbasis3 einsb3 (1);

//--------------------------------------------------------------------------------------- Funktionen und Operatoren -----------------------------------------------------------------------------------
//--------------------- integer Funktionen ------------------------------------------------------------------------------

void     vertausche (integer& a, integer& b);
integer  max        (integer a, integer b);
void     savemax    (integer& pmax, integer pr);

//--------------------- real Funktionen ------------------------------------------------------------------------------

void vertausche (real& a, real& b);

real q (const real x);

//_Float128 fmodr (const _Float128& a, const _Float128& b);
//_Float16 fmodr (const _Float16& a, const _Float16& b);
long double fmodr (const long double& a, const long double& b);
double fmodr (const double& a, const double& b);
float fmodr (const float& a, const float& b);

//_Float128 floorr (const _Float128& a);
//_Float16 floorr (const _Float16& a);
long double floorr (const long double& a);
double floorr (const double& a);
float floorr (const float& a);

//_Float128 fabsr (const _Float128& a);
//_Float16 fabsr (const _Float16& a);
long double fabsr (const long double& a);
double fabsr (const double& a);
float fabsr (const float& a);

//_Float128 expr (const _Float128& a);
//_Float16 expr (const _Float16& a);
long double expr (const long double& a);
double expr (const double& a);
float expr (const float& a);

//_Float128 logr (const _Float128& a);
//_Float16 logr (const _Float16& a);
long double logr (const long double& a);
double logr (const double& a);
float logr (const float& a);

//_Float128 powr (const _Float128& a, const _Float128& b);
//_Float16 powr (const _Float16& a, const _Float16& b);
long double powr (const long double& a, const long double& b);
double powr (const double& a, const double& b);
float powr (const float& a, const float& b);

//_Float128 sinr (const _Float128& a);
//_Float16 sinr (const _Float16& a);
long double sinr (const long double& a);
double sinr (const double& a);
float sinr (const float& a);

//_Float128 cosr (const _Float128& a);
//_Float16 cosr (const _Float16& a);
long double cosr (const long double& a);
double cosr (const double& a);
float cosr (const float& a);

//_Float128 asinr (const _Float128& a);
//_Float16 asinr (const _Float16& a);
long double asinr (const long double& a);
double asinr (const double& a);
float asinr (const float& a);

//_Float128 acosr (const _Float128& a);
//_Float16 acosr (const _Float16& a);
long double acosr (const long double& a);
double acosr (const double& a);
float acosr (const float& a);

//_Float128 atanr (const _Float128& a);
long double atanr (const long double& a);
double atanr (const double& a);
float atanr (const float& a);

//_Float128 atan2r (const _Float128& a, const _Float128& b);
//_Float16 atan2r (const _Float16& a, const _Float16& b);
long double atan2r (const long double& a, const long double& b);
double atan2r (const double& a, const double& b);
float atan2r (const float& a, const float& b);

//_Float128 asinhr (const _Float128& a);
//_Float16 asinhr (const _Float16& a);
long double asinhr (const long double& a);
double asinhr (const double& a);
float asinhr (const float& a);

//_Float128 acoshr (const _Float128& a);
//_Float16 acoshr (const _Float16& a);
long double acoshr (const long double& a);
double acoshr (const double& a);
float acoshr (const float& a);

//_Float128 atanhr (const _Float128& a);
//_Float16 atanhr (const _Float16& a);
long double atanhr (const long double& a);
double atanhr (const double& a);
float atanhr (const float& a);

//_Float128 sqrtr (const _Float128& a);
//_Float16 sqrtr (const _Float16& a);
long double sqrtr (const long double& a);
double sqrtr (const double& a);
float sqrtr (const float& a);

//_Float128 cbrtr (const _Float128& a);
long double cbrtr (const long double& a);
double cbrtr (const double& a);
float cbrtr (const float& a);

//--------------------- cvektor2 Vektor Funktionen ------------------------------------------------------------------------------

//real     norm    (const cvektor2 pv);
real     absv    (const cvektor2 pv);  // Länge des Vektors
cvektor2 senk    (const cvektor2 &pv);

// ---------- cvektor2 Vektor Operatoren ----------------------------------------------------------------------------------------------

integer  operator == (const cvektor2 &pv1, const cvektor2 &pv2);
cvektor2 operator -  (const cvektor2 &pv);                                       // Vorzeichen
cvektor2 operator +  (const cvektor2 &pv1, const cvektor2 &pv2);                 // Addition
cvektor2 operator -  (const cvektor2 &pv1, const cvektor2 &pv2);                 // Subtraktion
cvektor2 operator *  (const real &pf, const cvektor2 &pv);                       // Skalar Links Multiplikation
cvektor2 operator *  (const cvektor2 &pv, const real &pf);                       // Skalar Rechts Multiplikation
cvektor2 operator /  (const cvektor2 &pv, const real &pf);                       // Skalar Division
real     operator %  (const cvektor2 &pv1, const cvektor2 &pv2);                 // Skalarprodukt

// -------------------- ckomplexk Funktionen ----------------------------------------------------------------

// Umwandlungsfunktionen
ckomplexk kartes    (const ckomplexp pv);

// unäre Funktionen
ckomplexk sqrtv     (const ckomplexk pv);  // Quadratwurzel Hauptwert √  Sprung bei 0/360°
ckomplexk sqrtvk    (const ckomplexk pv);  // Quadratwurzel Hauptwert √ ohne Zwischenumwandlung in Polarkoordinaten Sprung bei 180/-180°
ckomplexk cbrtv     (const ckomplexk pv);  // Kubikwurzel Hauptwert  ∛
void      cbrtv     (const ckomplexk pv, ckomplexk& x1, ckomplexk& x2, ckomplexk& x3);  // Kubikwurzel komplett  ∛
ckomplexk expv      (const ckomplexk pv);
ckomplexk logv      (const ckomplexk pv);
ckomplexk coshv     (const ckomplexk pv);
ckomplexk sinhv     (const ckomplexk pv);
ckomplexk cosv      (const ckomplexk pv);
ckomplexk sinv      (const ckomplexk pv);
ckomplexk potenz    (const ckomplexk pv1, const ckomplexk pv2);

// ------- Schnittpunktklasse ------------------------------------------------------------------------------------------------

struct cschnittpunkte
  {
  integer        anz;
  integer        koerpernr[1000];
  integer        sichtbar[1000];
  real           abstand[1000];
  cvektor2       mannigpos[1000];

  cschnittpunkte ();
  void add (const real &pf);
  };

// -------------------- Lösungsformeln für Polynome ----------------------------------------------------------------

void quadratisch (ckomplexk a, ckomplexk b, ckomplexk& x1, ckomplexk& x2);
void uvaddition (ckomplexk z1, ckomplexk z2, ckomplexk bed, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3);
void kubischreduziertcardano (ckomplexk p, ckomplexk q, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3);
void kubischreduziertcardano3 (ckomplexk p, ckomplexk q, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3);
void kubischreduziertu1 (ckomplexk p, ckomplexk q, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3);
void kubischreduziertu3 (ckomplexk p, ckomplexk q, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3);
void kubischreduziertreell (real p, real q, real& y);
void kubischreduziertk (ckomplexk a, ckomplexk b, ckomplexk c, ckomplexk& p, ckomplexk& q);
void kubisch (ckomplexk a, ckomplexk b, ckomplexk c, ckomplexk& x1, ckomplexk& x2, ckomplexk& x3);
void kubischeresolventediffp (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& z1, ckomplexk& z2, ckomplexk& z3);
void kubischeresolventebuch (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& z1, ckomplexk& z2, ckomplexk& z3);
void kubischeresolventepdfw2 (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& z1, ckomplexk& z2, ckomplexk& z3);
void kubischeresolventelagrange (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& z1, ckomplexk& z2, ckomplexk& z3);
void kubischeresolvente1z (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& z1, ckomplexk& z2, ckomplexk& z3);
void kubischeresolvente3z (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& z1, ckomplexk& z2, ckomplexk& z3);
void quartischreduziertdiffpu (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4);
void quartischreduziertbuchu (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4);
void quartischreduziertbuchv (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4);
void quartischreduziertbuchf (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4);
void quartischreduziertpdfw2 (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4);
void quartischreduziertlagrange (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4);
void quartischreduziertbuch3 (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4);
void quartischreduziertpdfw23 (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4);
void quartischreduziertlagrange3 (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4);
void quartischreduziertk (ckomplexk a, ckomplexk b, ckomplexk c, ckomplexk d, ckomplexk& p, ckomplexk& q, ckomplexk& r);
void quartisch (ckomplexk a, ckomplexk b, ckomplexk c, ckomplexk d, ckomplexk& x1, ckomplexk& x2, ckomplexk& x3, ckomplexk& x4);
void quartischdiffpintrc (real aq, real bq, real cq, real dq, ckomplexk& x1, ckomplexk& x2, ckomplexk& x3, ckomplexk& x4);
void quartischdiffpintr (real aq, real bq, real cq, real dq, cschnittpunkte& psp);
void quartischbuchuintr (real aq, real bq, real cq, real dq, cschnittpunkte& psp);
void quartischbuchvintr (real aq, real bq, real cq, real dq, cschnittpunkte& psp);
void quartischbuchfintr (real aq, real bq, real cq, real dq, cschnittpunkte& psp);
void quartischlagrangeintru (real aq, real bq, real cq, real dq, cschnittpunkte& psp);
void quartischlagrangeintrc (real aq, real bq, real cq, real dq, cschnittpunkte& psp);

// --------------------- ckomplexk Operatoren ---------------------------------------------------------

// vererbte Operatoren
ckomplexk operator - (const ckomplexk &pv);                                      // Vorzeichen
ckomplexk operator + (const ckomplexk &pv1, const ckomplexk &pv2);               // Addition
ckomplexk operator - (const ckomplexk &pv1, const ckomplexk &pv2);               // Subtraktion
ckomplexk operator * (const real &pf, const ckomplexk &pv);                      // Skalar Links Multiplikation
ckomplexk operator * (const ckomplexk &pv, const real &pf);                      // Skalar Rechts Multiplikation
ckomplexk operator / (const ckomplexk &pv, const real &pf);                      // Skalar Division

// ckomplexk Operatoren
ckomplexk operator * (const ckomplexk &pv1, const ckomplexk &pv2);               // Multiplikation
ckomplexk operator / (const ckomplexk &pv1, const ckomplexk &pv2);               // Division
ckomplexk operator / (const real &pf,       const ckomplexk &pv);                // Skalar Division reelle Zahl / komplexe Zahl
ckomplexk operator ^ (const ckomplexk &pv,  const integer &pn);                  // komplexe Potenz mit ganzem Exponenten
ckomplexk operator ^ (const ckomplexk &pv,  const real &pr);                     // komplexe Potenz mit reellem Exponenten
ckomplexk operator ^ (const ckomplexk &pv1, const ckomplexk &pv2);               // komplexe Potenz mit komplexem Exponenten

// -------------------- ckomplexp Funktionen -------------------------------------------

// Umwandlungsfunktionen
ckomplexp polar225  (const ckomplexk pv);
ckomplexp polar360  (const ckomplexk pv);
ckomplexp polar180  (const ckomplexk pv);
ckomplexp polarcos180  (const ckomplexk pv);
ckomplexp polartan180  (const ckomplexk pv);

// unäre Funktionen
ckomplexp kw        (const ckomplexp pv);  // komplexer Kehrwert
ckomplexp sqrtv     (const ckomplexp pv);  // Quadratwurzel √
ckomplexp cbrtv     (const ckomplexp pv);  // Kubikwurzel   ∛
ckomplexp expv      (const ckomplexp pv);
ckomplexp logv      (const ckomplexp pv);
ckomplexp coshv     (const ckomplexp pv);
ckomplexp sinhv     (const ckomplexp pv);
ckomplexp cosv      (const ckomplexp pv);
ckomplexp sinv      (const ckomplexp pv);

// -------------------- ckomplexp Operatoren ----------------------------------------------------------------

// vererbte Operatoren
ckomplexp operator - (const ckomplexp &pv);                                      // Vorzeichen
ckomplexp operator + (const ckomplexp &pv1, const ckomplexp &pv2);               // Addition
ckomplexp operator - (const ckomplexp &pv1, const ckomplexp &pv2);               // Subtraktion
ckomplexp operator * (const real &pf, const ckomplexp &pv);                      // Skalar Multiplikation
ckomplexp operator / (const ckomplexp &pv, const real &pf);                      // Skalar Division

// ckomplexp Operatoren
ckomplexp operator * (const ckomplexp &pv1, const ckomplexp &pv2);               // Multiplikation
ckomplexp operator / (const ckomplexp &pv1, const ckomplexp &pv2);               // Division
ckomplexp operator / (const real &pf,       const ckomplexp &pv);                // reelle Zahl / komplexe Zahl
ckomplexp operator ^ (const ckomplexp &pv,  const real &pr);                     // komplexe Potenz mit reellem Exponenten
ckomplexp operator ^ (const ckomplexp &pv1, const ckomplexp &pv2);               // komplexe Potenz mit komplexem Exponenten

// -------------------- gemischtkomplexe Funktionen (Mischung: kartesischkomplex, polarkomplex) ----------------------------------------------------------------

real arg (const ckomplexk pv);

// Umwandlungsfunktionen
ckomplexk kartes    (const ckomplexp pv);

// --------------------- Operatoren für Kugelkoordinaten ------------------------------------------------------

real      operator | (const ckugelk &pv1, const ckugelk &pv2);                   // Winkel zwischen zwei dreidimensionalen Einheitsvektoren in Kugelkoordinaten

//---------- cvektor2, cbasis2 --------------------------------------------------------------------------------

// Matrix mal Vektor
cvektor2 operator * (const cbasis2  &pb, const cvektor2 &pv);
cvektor2 operator & (const cvektor2 &pv, const cbasis2  &pb);
cvektor2 operator / (const cvektor2 &pv, const cbasis2  &pb);

//---------- cbasis2 Funktionen -------------------------------------------------------------------------------------------

real     det     (const cbasis2 &pb);
cbasis2  transp  (const cbasis2 &pb);

//---------- cbasis2 Operatoren -------------------------------------------------------------------------------------------

// transponierte inverse Matrix bestimmen (senkrechter Raum zur Basis)
cbasis2 operator ~ (const cbasis2  &pb);

// Matrixaddition
cbasis2 operator + (const cbasis2 &pb1, const cbasis2 &pb2);
cbasis2 operator - (const cbasis2 &pb1, const cbasis2 &pb2);

// Skalarmultiplikation
//cbasis2 operator * (const real &pf, const cbasis2 &pb);
cbasis2 operator / (const cbasis2 &pb, const real &pf);

// Matrixmultiplikation
cbasis2 operator * (const cbasis2 &pb1, const cbasis2 &pb2);
cbasis2 operator & (const cbasis2 &pb1, const cbasis2 &pb2);
cbasis2 operator / (const cbasis2 &pb1, const cbasis2 &pb2);
cbasis2 operator | (const cbasis2 &pb1, const cbasis2 &pb2);

//---------- cvektor3 Funktionen ------------------------------------------------------------------------------------------

void vertausche (cvektor3& a, cvektor3& b);

real     norm       (const cvektor3 &pv);
real     abs        (const cvektor3 &pv);
cvektor3 senk       (const cvektor3 &pv);
cvektor3 normiere   (const cvektor3 &pv);
cvektor3 orientiere (const cvektor3 &pv);

// Betrag des Winkels zwischen 2 Vektoren ermitteln [0-pi]
real winkelb (const cvektor3 &pv1, const cvektor3 &pv2);

// Betrag des Winkels zwischen 2 Geraden ermitteln  [0-pi/2]
real winkelg (const cvektor3 &pv1, const cvektor3 &pv2);

//---------- cvektor3 Operatoren ------------------------------------------------------------------------------------------

// Vektoren vergleichen
integer operator == (const cvektor3 &pv1, const cvektor3 &pv2);

// Vorzeichen des Vektors ändern
cvektor3 operator - (const cvektor3 &pv);

// Vektoradditon
cvektor3 operator + (const cvektor3 &pv1, const cvektor3 &pv2);
cvektor3 operator - (const cvektor3 &pv1, const cvektor3 &pv2);

// Skalarmultiplikation
//cvektor3 operator * (const real &pf, const cvektor3 &pv);
cvektor3 operator / (const cvektor3 &pv, const real &pf);

// Skalarprodukt
real operator % (const cvektor3 &pv1, const cvektor3 &pv2);

// Kreuzprodukt (senkrecht stehenden Vektor zu 2 Vektoren in positiver Orientierung ermitteln)
cvektor3 operator ^ (const cvektor3 &pv1, const cvektor3 &pv2);

// einen Vektor aus der Ebene wählen, auf dem der Vektor senkrecht steht
cvektor3 operator ~ (const cvektor3 &pv);

//---------- cvektor3, cbasis3 -----------------------------------------------------------------------------------

cvektor3 operator * (const cbasis3  &pb, const cvektor3 &pv);
cvektor3 operator & (const cvektor3 &pv, const cbasis3  &pb);
cvektor3 operator / (const cvektor3 &pv, const cbasis3  &pb);

//---------- cbasis3 Funktionen ------------------------------------------------------------------------------------------

real     norm      (cbasis3 pb);
real     abs       (cbasis3 pb);
real     det       (const cbasis3 &pb);
cbasis3  normiere  (const cbasis3 &pb);
cbasis3  normiere2 (const cbasis3 &pb);
cbasis3  transp    (const cbasis3 &pb);
cvektor3 geteigen  (const cbasis3 &pb);
cbasis3  getrotx   (const real &pf);
cbasis3  getroty   (const real &pf);
cbasis3  getrotz   (const real &pf);
cbasis3  getspiegbasis (const cvektor3 &pv);
cbasis3  getdrehspiegbasis (const cvektor3 &pv);
cvektor3 getspiegachse (const cbasis3 &pb);
integer  aehnlich  (const cbasis3 &pb1, const cbasis3 &pv2);

//---------- cbasis3 Operatoren ------------------------------------------------------------------------------------------

// transponierte inverse Matrix bestimmen
cbasis3  operator ~ (const cbasis3  &pb);

// Matrixaddition (Vektoraddition von Matrizen)
cbasis3  operator - (const cbasis3  &pb);
cbasis3  operator + (const cbasis3 &pb1, const cbasis3 &pb2);
cbasis3  operator - (const cbasis3 &pb1, const cbasis3 &pb2);

// Skalarmultiplikation (Skalarmultiplikation von Matrizen)
//cbasis3  operator * (const real &pf, const cbasis3 &pb);
cbasis3  operator / (const cbasis3 &pb, const real &pf);

// Matrixmultiplikation (Körperoperationen von Matrizen)
cbasis3  operator * (const cbasis3 &pb1, const cbasis3 &pb2);
cbasis3  operator & (const cbasis3 &pb1, const cbasis3 &pb2);
cbasis3  operator / (const cbasis3 &pb1, const cbasis3 &pb2);
cbasis3  operator | (const cbasis3 &pb1, const cbasis3 &pb2);

//---------- cvektor4 Vektor Funktionen -----------------------------------------------------------------------------------------------

real     norm     (const cvektor4 &pv);
real     abs      (const cvektor4 &pv);
cvektor4 senk     (const cvektor4 &pv);
cvektor4 normiere (const cvektor4 &pv);

// Kreuzfunktion (einen senkrecht stehenden Vektor ermitteln)
cvektor4 operator ~ (const cvektor4 &pv);

//---------- cvektor4 Funktionen für Quaternionen -------------------------------------------------------------------------------------

cvektor4 kw       (const cvektor4 &pv);
cvektor3 getachse (const cvektor4 &pv);
integer  aehnlich (const cvektor4 &pv1, const cvektor4 &pv2);

//---------- cvektor4 Vektor Operatoren ------------------------------------------------------------------------------------------------

// Vergleich
integer operator == (const cvektor4 &pv1, const cvektor4 &pv2);

// Vorzeichen ändern
cvektor4 operator - (const cvektor4 &pv);

// Vektorraddition
cvektor4 operator + (const cvektor4 &pv1, const cvektor4 &pv2);
cvektor4 operator - (const cvektor4 &pv1, const cvektor4 &pv2);

// Skalarmultiplikation
//cvektor4 operator * (const real &pf, const cvektor4 &pv);
cvektor4 operator / (const cvektor4 &pv, const real &pf);

// Skalarprodukt
real     operator % (const cvektor4 &pv1, const cvektor4 &pv2);

//----------------------------- Operatoren für Quaternionen --------------------------------------------------------
// Quaternionenmultiplikation
cvektor4 operator * (const cvektor4 &pv1, const cvektor4 &pv2);
cvektor4 operator / (const cvektor4 &pv1, const cvektor4 &pv2);
cvektor4 operator | (const cvektor4 &pv1, const cvektor4 &pv2);
cvektor3 operator * (const cvektor4 &pq, const cvektor3 &pv);    // 3D-Vektor mit Drehquaternion drehen

//----------------------------- Operatoren für Heptanionen --------------------------------------------------------
// Heptanionenmultiplikation
cvektor7 operator * (const cvektor7 &pv1, const cvektor7 &pv2);

//---------- cvektor8 Vektor Operatoren ------------------------------------------------------------------------------------------------

// ------------------------------ Drehdarstellungen umrechnen ------------------------------------------------------------------------

cvektor4 quaternionfromwinkelachse (const cvektor4 pdw);
cvektor4 winkelachsefromquaternion (const cvektor4 pq);

cbasis3  matrixfromquaternion (const cvektor4 pq);
cvektor4 quaternionfrommatrix (const cbasis3& pdm);
cvektor4 quaternionfrommatrix2 (const cbasis3 &pdreh);

cvektor4 winkelachsefrommatrix (const cbasis3 &pdreh);
cbasis3  matrixfromwinkelachse (const cvektor4 pq);

cvektor3 eulerwinkelfrommatrix (const cbasis3& pdm);
cbasis3  matrixfromeulerwinkel (cvektor3 pflugw);

cvektor4 quaternionfromeulerwinkel (const cvektor3 pflugw);

#endif
