// Das Programm gibt die Größen zu den Fließkommatypen aus

#include <cstdio>
#include <cfloat>
#include <climits>
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

typedef signed long long integer;

//typedef _Float16 real;                          //

//typedef _Float32 real;                          //  6/8 Stellen (unterscheidbar/verlässlich)
//typedef float real;                             //  6/8 Stellen (unterscheidbar/verlässlich)

//typedef _Float64 real;                          // 15/16 Stellen (unterscheidbar/verlässlich)
//typedef double real;                            // 15/16 Stellen (unterscheidbar/verlässlich)

typedef __float80 real;                         // 20/18 Stellen (unterscheidbar/verlässlich)
//typedef long double real;                       // 20/18 Stellen (unterscheidbar/verlässlich)

//typedef __float128 real;                        // 35/33 Stellen   100 mal langsamer wegen Softwareimplementierung statt Hardwareimplementierung
//typedef _Float128 real;                         // 35/33 Stellen

const real zwei (2);                                                                  // der doofe Computer weiß nicht mit welcher Genauigkeit er 2/3 ausrechnen soll. zwei/3 ist eindeutig
//const real g (0.5 + sqrtl (1.25));                                                    // goldene Schnitt g= (1+V5)/2  g= 2*cos 36°
//const real t ((1 + cbrtl (19 + sqrtl (297)) + cbrtl (19 - sqrtl (297)))/3);           // Tribonacci Konstante  t= (1 + t1 + t2)/3    t1/2= 3V(19+-3V33)

//---------------------------------- Hilfsfunktionen ------------------------------------------------------------

// 0.6666666666666666666666666666666666-345678  128
// 1.6180339887498948482045868343656381-596970  128
// 0.6180339887498948482045868343656381-596970  128
// 0.8090169943749474241022934171828190-798485  128
// 0.3090169943749474241022934171828190-317003  128
// 3.141592653589793238462643383279502-7974791  128
// 1.8392867552141611325518525646532865-010030  128

// 1.61803398874989484820-72100296669248109538  80
// 1.839286755214161132-6051162667027938368847  80

// 2.618033988749894848204586834365638117720309179     (V5+3)/2
// 1.618033988749894848204586834365638117720309179     (V5+1)/2  2cos 36°
// 0.618033988749894848204586834365638117720309179     (V5-1)/2  2sin 18°

// 0.3090169943749474241022934171828                   (V5-1)/4   cos 72°  sin 18°
// 0.5                                                      2/4   cos 60°  sin 30°
// 0.8090169943749474241022934171828                   (V5+1)/4   cos 36°  sin 54°



void genauigkeit ()
  {

  //_Float16       real16;                          //
  //_Float32       real32;                          //  6/8 Stellen (unterscheidbar/verlässlich)
  //float          realfloat;                       //  6/8 Stellen (unterscheidbar/verlässlich)
  //_Float64       real64;                          // 15/16 Stellen (unterscheidbar/verlässlich)
  //double         realdouble;                      // 15/16 Stellen (unterscheidbar/verlässlich)
  //__float80      real80;                          // 20/18 Stellen (unterscheidbar/verlässlich)
  //long double    reallongdouble;                  // 20/18 Stellen (unterscheidbar/verlässlich)
  //__float128     real128;                         // 35/33 Stellen   100 mal langsamer wegen Softwareimplementierung statt Hardwareimplementierung
  //_Float128      real128g;                        // 35/33 Stellen

  long double dez= logl (10)/logl (2);
  printf ("%20.10LF\n", dez);
  printf ("\n");

  printf ("_Float16\n");

  _Float16 wert, bit;

  bit= 1;
  bit= bit/2;

  for (integer lauf= 1; lauf < 100; lauf++)
    {
    wert= 1;
    wert= wert + bit;
    if (wert == 1)
      {
      printf ("%5lld  %12.10LF\n", lauf, lauf/dez);
      break;
      }
    bit= bit/2;
    }

  bit= 1;
  bit= bit/10;

  for (integer lauf= 1; lauf < 100; lauf++)
    {
    wert= 1;
    wert= wert + bit;
    if (wert == 1)
      {
      printf ("%5lld  \n", lauf);
      break;
      }
    bit= bit/10;
    }

  printf ("_Float32\n");

  _Float32 wert2, bit2;

  bit2= 1;
  bit2= bit2/2;

  for (integer lauf= 1; lauf < 100; lauf++)
    {
    wert2= 1;
    wert2= wert2 + bit2;
    if (wert2 == 1)
      {
      printf ("%5lld  %12.10LF\n", lauf, lauf/dez);
      break;
      }
    bit2= bit2/2;
    }

  bit2= 1;
  bit2= bit2/10;

  for (integer lauf= 1; lauf < 100; lauf++)
    {
    wert2= 1;
    wert2= wert2 + bit2;
    if (wert2 == 1)
      {
      printf ("%5lld  \n", lauf);
      break;
      }
    bit2= bit2/10;
    }

  printf ("float\n");

  float wert3, bit3;

  bit3= 1;
  bit3= bit3/2;

  for (integer lauf= 1; lauf < 100; lauf++)
    {
    wert3= 1;
    wert3= wert3 + bit3;
    if (wert3 == 1)
      {
      printf ("%5lld  %12.10LF\n", lauf, lauf/dez);
      break;
      }
    bit3= bit3/2;
    }

  bit3= 1;
  bit3= bit3/10;

  for (integer lauf= 1; lauf < 100; lauf++)
    {
    wert3= 1;
    wert3= wert3 + bit3;
    if (wert3 == 1)
      {
      printf ("%5lld  \n", lauf);
      break;
      }
    bit3= bit3/10;
    }

  printf ("_Float64\n");

  _Float64 wert4, bit4;

  bit4= 1;
  bit4= bit4/2;

  for (integer lauf= 1; lauf < 100; lauf++)
    {
    wert4= 1;
    wert4= wert4 + bit4;
    if (wert4 == 1)
      {
      printf ("%5lld  %12.10LF\n", lauf, lauf/dez);
      break;
      }
    bit4= bit4/2;
    }

  bit4= 1;
  bit4= bit4/10;

  for (integer lauf= 1; lauf < 100; lauf++)
    {
    wert4= 1;
    wert4= wert4 + bit4;
    if (wert4 == 1)
      {
      printf ("%5lld  \n", lauf);
      break;
      }
    bit4= bit4/10;
    }

  printf ("double\n");

  double wert5, bit5;

  bit5= 1;
  bit5= bit5/2;

  for (integer lauf= 1; lauf < 100; lauf++)
    {
    wert5= 1;
    wert5= wert5 + bit5;
    if (wert5 == 1)
      {
      printf ("%5lld  %12.10LF\n", lauf, lauf/dez);
      break;
      }
    bit5= bit5/2;
    }

  bit5= 1;
  bit5= bit5/10;

  for (integer lauf= 1; lauf < 100; lauf++)
    {
    wert5= 1;
    wert5= wert5 + bit5;
    if (wert5 == 1)
      {
      printf ("%5lld  \n", lauf);
      break;
      }
    bit5= bit5/10;
    }

  printf ("_Float128\n");

  _Float128 wert9, bit9;

  bit9= 1;
  bit9= bit9/2;

  for (integer lauf= 1; lauf < 1000; lauf++)
    {
    wert9= 1;
    wert9= wert9 + bit9;
    if (wert9 == 1)
      {
      printf ("%5lld  %12.10LF\n", lauf, lauf/dez);
      break;
      }
    bit9= bit9/2;
    }

  bit9= 1;
  bit9= bit9/10;

  for (integer lauf= 1; lauf < 1000; lauf++)
    {
    wert9= 1;
    wert9= wert9 + bit9;
    if (wert9 == 1)
      {
      printf ("%5lld  \n", lauf);
      break;
      }
    bit9= bit9/10;
    }

  printf ("long double\n");

  long double wert7, bit7;

  bit7= 1;
  bit7= bit7/2;

  for (integer lauf= 1; lauf < 1000; lauf++)
    {
    wert7= 1;
    wert7= wert7 + bit7;
    if (wert7 == 1)
      {
      printf ("%5lld  %12.10LF\n", lauf, lauf/dez);
      break;
      }
    bit7= bit7/2;
    }

  bit7= 1;
  bit7= bit7/10;

  for (integer lauf= 1; lauf < 1000; lauf++)
    {
    wert7= 1;
    wert7= wert7 + bit7;
    if (wert7 == 1)
      {
      printf ("%5lld  \n", lauf);
      break;
      }
    bit7= bit7/10;
    }

  }

void genauigkeit80 ()
  {
  real wert, bit;
  bit= real (0.1);

  for (integer lauf= 1; lauf < 100; lauf++)
    {
    wert= 1;
    wert= wert + bit;
    //printf ("%5lld  %50.40Lf %50.40Lf\n", lauf, wert, bit);
    if (wert == 1)
      break;
    bit= bit/10;
    }
  }

void genauigkeit128 ()
  {
//  __float128 wert, bit;
  _Float32 wert, bit;
  char zahl[128];
  char zahl2[128];
  bit= 1;
  bit= bit/10;

  for (integer lauf= 1; lauf < 100; lauf++)
    {
    wert= 1;
    wert= wert + bit;
//    quadmath_snprintf (zahl, sizeof zahl, "%50.40Qf", wert);
//    quadmath_snprintf (zahl2, sizeof zahl, "%50.40Qf", bit);
    printf ("%5lld  %s  %s\n", lauf, zahl, zahl2);
    if (wert == 1)
      break;
    bit= bit/10;
    }
  }

void printkonstanten ()
  {
// _Float128 wert;
  long double wert;
  char zahl[128];

//------------------------------------------------------------------- g
  printf ("\n");
  wert= 0.5 + sqrtl (1.25);
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

  wert= -0.5 + sqrtl (1.25);
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

  wert= 2*cosl (36*acosl (-1)/180);
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

  wert= 2*cosl (acosl (-1)/5);
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

  wert= 2*sinl (acosl (-1)/10);
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

  wert= 0.5 + sqrtl (1.25);
  wert= wert*wert;
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

// --------------------------------------------------------------------- g/2
  printf ("\n");
  wert= cosl (acosl (-1)/5);
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

  wert= sinl (3*acosl (-1)/10);
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

  wert= cosl (2*acosl (-1)/5);
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

  wert= sinl (acosl (-1)/10);
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

// --------------------------------------------------------------------- 3.141592653589793238462643383279502884197169399375;
  printf ("\n");
  wert= acosl (-1);
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

  wert= (1 + cbrtl (19 + sqrtl (297)) + cbrtl (19 - sqrtl (297)))/3;           // Tribonacci Konstante  t= (1 + t1 + t2)/3    t1/2= 3V(19+-3V33)
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

// --------------------------------------------------------------------- Brüche
  printf ("\n");

  wert= 1;
  wert= wert/2;
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

  wert= 1;
  wert= wert/4;
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

  wert= 1;
  wert= wert/4;
  wert= wert*3;
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

  wert= 1;
  wert= wert/3;
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

  wert= 2;
  wert= wert/3;
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

  wert= 1;
  wert= wert/7;
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

  wert= 3;
  wert= wert/7;
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

  wert= 2;
  wert= wert/7;
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

  wert= 6;
  wert= wert/7;
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

  wert= 4;
  wert= wert/7;
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

  wert= 5;
  wert= wert/7;
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

//  wert= .1L;                                              // Kommazahlen sind immer double
  wert= 1;                                              // Kommazahlen sind immer double
  wert= wert/10;
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

  wert= 2;
  wert= wert/10;
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

  wert= 3;
  wert= wert/10;
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

  wert= 4;
  wert= wert/10;
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

  wert= 6;
  wert= wert/10;
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

  wert= 7;
  wert= wert/10;
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

  wert= 8;
  wert= wert/10;
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

  wert= 9;
  wert= wert/10;
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

  wert= 27;
  wert= wert/256;
  snprintf (zahl, sizeof zahl, "%60.50Lf", wert);
  printf ("%s\n", zahl);

  }

void genauigkeitsausgabe ()
  {
  printf ("\n");
  printf ("signed Char Max:      %20d\n",  SCHAR_MAX);
  printf ("signed Short Max:     %20d\n",  SHRT_MAX);
  printf ("signed Long Max:      %20ld\n", LONG_MAX);
  printf ("signed Long Long Max: %20lld\n", LLONG_MAX);
  printf ("\n");

  printf ("Größe float[Byte]:                  %6ld\n", sizeof (float));
  printf ("Anzahl Bits der Matisse:            %6d\n", FLT_MANT_DIG);
  printf ("Genauigkeit in Dezimalziffern:      %6d\n", FLT_DIG);
  printf ("Minimale Größe des 2-Exponents:     %6d\n", FLT_MIN_EXP);
  printf ("Maximale Größe des 2-Exponents:     %6d\n", FLT_MAX_EXP);
  printf ("Minimale Größe des 10-Exponents:    %6d\n", FLT_MIN_10_EXP);
  printf ("Maximale Größe des 10-Exponents:    %6d\n", FLT_MAX_10_EXP);
  printf ("\n");

  printf ("Größe double[Byte]:                 %6ld\n", sizeof (double));
  printf ("Anzahl Bits der Matisse:            %6d\n", DBL_MANT_DIG);
  printf ("Genauigkeit in Dezimalziffern:      %6d\n", DBL_DIG);
  printf ("Minimale Größe des 2-Exponents:     %6d\n", DBL_MIN_EXP);
  printf ("Maximale Größe des 2-Exponents:     %6d\n", DBL_MAX_EXP);
  printf ("Minimale Größe des 10-Exponents:    %6d\n", DBL_MIN_10_EXP);
  printf ("Maximale Größe des 10-Exponents:    %6d\n", DBL_MAX_10_EXP);
  printf ("\n");

  printf ("Größe long double[Byte]:            %6ld\n", sizeof (long double));
  printf ("Anzahl Bits der Matisse:            %6d\n", LDBL_MANT_DIG);
  printf ("Genauigkeit in Dezimalziffern:      %6d\n", LDBL_DIG);
  printf ("Minimale Größe des 2-Exponents:     %6d\n", LDBL_MIN_EXP);
  printf ("Maximale Größe des 2-Exponents:     %6d\n", LDBL_MAX_EXP);
  printf ("Minimale Größe des 10-Exponents:    %6d\n", LDBL_MIN_10_EXP);
  printf ("Maximale Größe des 10-Exponents:    %6d\n", LDBL_MAX_10_EXP);
  printf ("\n");

  _Float16 floatvar16= 3;
  _Float32 floatvar32= 3;
  _Float64 floatvar64= 3;
  _Float128 floatvar128= 3;

  printf ("Größe _Float16[Byte]:               %6ld\n", sizeof (floatvar16));
  printf ("Größe _Float32[Byte]:               %6ld\n", sizeof (floatvar32));
  printf ("Größe _Float64[Byte]:               %6ld\n", sizeof (floatvar64));
  printf ("Größe _Float128[Byte]:              %6ld\n", sizeof (floatvar128));
  printf ("\n");

  return;
  }

void printreal ()
  {
  float blar= 1.25;

  //real oprf= sqrtf (blar);
  //real oprd= sqrt (blar);
  //real oprl= sqrtl (blar);
  real opr= sqrt (blar);

  signed short pre= 40;
  signed short we= 40;

  cout << fixed;
  cout << setprecision (pre);
  //cout << "oprf  " << setw (we) << oprf << endl;
  //cout << "oprd  " << setw (we) << oprd << endl;
  //cout << "oprl  " << setw (we) << oprl << endl;
  cout << "opr   " << setw (we) << opr << endl;
  }

int main ()
  {
  //genauigkeit ();
  //genauigkeitsausgabe ();
  //printkonstanten ();
  printreal ();
  return 0;
  }
