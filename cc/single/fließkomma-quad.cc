// Das Programm gibt die Größen zu den Fließkommatypen aus

#include <cstdio>
#include <cfloat>
#include <climits>
#include <cmath>
#include <quadmath.h>

typedef signed long long integer;

//typedef __float80 real;                         // 20/18 Stellen (unterscheidbar/verlässlich)
typedef long double real;                       // 20/18 Stellen (unterscheidbar/verlässlich)
//typedef __float128 real;                        // 35/33 Stellen   100 mal langsamer wegen Softwareimplementierung statt Hardwareimplementierung

const real zwei (2);                                                                  // der doofe Computer weiß nicht mit welcher Genauigkeit er 2/3 ausrechnen soll. zwei/3 ist eindeutig
const real g (0.5 + sqrtl (1.25));                                                    // goldene Schnitt g= (1+V5)/2  g= 2*cos 36°
const real t ((1 + cbrtl (19 + sqrtl (297)) + cbrtl (19 - sqrtl (297)))/3);           // Tribonacci Konstante  t= (1 + t1 + t2)/3    t1/2= 3V(19+-3V33)

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

//__float80      real80;                          // 20/18 Stellen (unterscheidbar/verlässlich)
//long double    reallongdouble;                  // 20/18 Stellen (unterscheidbar/verlässlich)
//__float128     real128;                         // 35/33 Stellen   100 mal langsamer wegen Softwareimplementierung statt Hardwareimplementierung

  long double dez= logl (10)/logl (2);
  printf ("%20.10LF\n", dez);
  printf ("\n");

printf ("__float80\n");

  __float80 wert6, bit6;

  bit6= 1;
  bit6= bit6/2;

  for (integer lauf= 1; lauf < 100; lauf++)
    {
    wert6= 1;
    wert6= wert6 + bit6;
    if (wert6 == 1)
      {
      printf ("%5lld  %12.10LF\n", lauf, lauf/dez);
      break;
      }
    bit6= bit6/2;
    }

  bit6= 1;
  bit6= bit6/10;

  for (integer lauf= 1; lauf < 100; lauf++)
    {
    wert6= 1;
    wert6= wert6 + bit6;
    if (wert6 == 1)
      {
      printf ("%5lld  \n", lauf);
      break;
      }
    bit6= bit6/10;
    }

printf ("long double\n");

  long double wert7, bit7;

  bit7= 1;
  bit7= bit7/2;

  for (integer lauf= 1; lauf < 100; lauf++)
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

  for (integer lauf= 1; lauf < 100; lauf++)
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

printf ("__float128\n");

  __float128 wert8, bit8;

  bit8= 1;
  bit8= bit8/2;

  for (integer lauf= 1; lauf < 100; lauf++)
    {
    wert8= 1;
    wert8= wert8 + bit8;
    if (wert8 == 1)
      {
      printf ("%5lld  %12.10LF\n", lauf, lauf/dez);
      break;
      }
    bit8= bit8/2;
    }

  bit8= 1;
  bit8= bit8/10;

  for (integer lauf= 1; lauf < 100; lauf++)
    {
    wert8= 1;
    wert8= wert8 + bit8;
    if (wert8 == 1)
      {
      printf ("%5lld  \n", lauf);
      break;
      }
    bit8= bit8/10;
    }

  }

void printkonstanten ()
  {
  __float128 wert;
  char zahl[128];

//------------------------------------------------------------------- g
  printf ("\n");
  wert= 0.5 + sqrtq (1.25);
  quadmath_snprintf (zahl, sizeof zahl, "%60.50Qf", wert);
  printf ("%s\n", zahl);

  wert= -0.5 + sqrtq (1.25);
  quadmath_snprintf (zahl, sizeof zahl, "%60.50Qf", wert);
  printf ("%s\n", zahl);

  wert= 2*cosq (36*acosq (-1)/180);
  quadmath_snprintf (zahl, sizeof zahl, "%60.50Qf", wert);
  printf ("%s\n", zahl);

  wert= 2*cosq (acosq (-1)/5);
  quadmath_snprintf (zahl, sizeof zahl, "%60.50Qf", wert);
  printf ("%s\n", zahl);

  wert= 2*sinq (acosq (-1)/10);
  quadmath_snprintf (zahl, sizeof zahl, "%60.50Qf", wert);
  printf ("%s\n", zahl);

// --------------------------------------------------------------------- g/2
  printf ("\n");
  wert= cosq (acosq (-1)/5);
  quadmath_snprintf (zahl, sizeof zahl, "%60.50Qf", wert);
  printf ("%s\n", zahl);

  wert= sinq (3*acosq (-1)/10);
  quadmath_snprintf (zahl, sizeof zahl, "%60.50Qf", wert);
  printf ("%s\n", zahl);

  wert= cosq (2*acosq (-1)/5);
  quadmath_snprintf (zahl, sizeof zahl, "%60.50Qf", wert);
  printf ("%s\n", zahl);

  wert= sinq (acosq (-1)/10);
  quadmath_snprintf (zahl, sizeof zahl, "%60.50Qf", wert);
  printf ("%s\n", zahl);

// --------------------------------------------------------------------- 3.141592653589793238462643383279502884197169399375;
  printf ("\n");
  wert= acosq (-1);
  quadmath_snprintf (zahl, sizeof zahl, "%60.50Qf", wert);
  printf ("%s\n", zahl);

  wert= (1 + cbrtq (19 + sqrtq (297)) + cbrtq (19 - sqrtq (297)))/3;           // Tribonacci Konstante  t= (1 + t1 + t2)/3    t1/2= 3V(19+-3V33)
  quadmath_snprintf (zahl, sizeof zahl, "%60.50Qf", wert);
  printf ("%s\n", zahl);

// --------------------------------------------------------------------- Brüche
  printf ("\n");
  wert= 2;
  wert= wert/3;
  quadmath_snprintf (zahl, sizeof zahl, "%60.50Qf", wert);
  printf ("%s\n", zahl);

  wert= .5;
  quadmath_snprintf (zahl, sizeof zahl, "%60.50Qf", wert);
  printf ("%s\n", zahl);

  wert= .25;
  quadmath_snprintf (zahl, sizeof zahl, "%60.50Qf", wert);
  printf ("%s\n", zahl);

  wert= .75;
  quadmath_snprintf (zahl, sizeof zahl, "%60.50Qf", wert);
  printf ("%s\n", zahl);

  wert= 1;
  wert= wert/10;
  quadmath_snprintf (zahl, sizeof zahl, "%60.50Qf", wert);
  printf ("%s\n", zahl);

  wert= 2;
  wert= wert/10;
  quadmath_snprintf (zahl, sizeof zahl, "%60.50Qf", wert);
  printf ("%s\n", zahl);

  wert= 3;
  wert= wert/10;
  quadmath_snprintf (zahl, sizeof zahl, "%60.50Qf", wert);
  printf ("%s\n", zahl);

  wert= 4;
  wert= wert/10;
  quadmath_snprintf (zahl, sizeof zahl, "%60.50Qf", wert);
  printf ("%s\n", zahl);

  wert= 6;
  wert= wert/10;
  quadmath_snprintf (zahl, sizeof zahl, "%60.50Qf", wert);
  printf ("%s\n", zahl);

  wert= 7;
  wert= wert/10;
  quadmath_snprintf (zahl, sizeof zahl, "%60.50Qf", wert);
  printf ("%s\n", zahl);

  wert= 8;
  wert= wert/10;
  quadmath_snprintf (zahl, sizeof zahl, "%60.50Qf", wert);
  printf ("%s\n", zahl);

  wert= 9;
  wert= wert/10;
  quadmath_snprintf (zahl, sizeof zahl, "%60.50Qf", wert);
  printf ("%s\n", zahl);

  wert= 27;
  wert= wert/256;
  quadmath_snprintf (zahl, sizeof zahl, "%60.50Qf", wert);
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

  printf ("Größe long double[Byte]:            %6ld\n", sizeof (long double));
  printf ("Anzahl Bits der Matisse:            %6d\n", LDBL_MANT_DIG);
  printf ("Genauigkeit in Dezimalziffern:      %6d\n", LDBL_DIG);
  printf ("Minimale Größe des 2-Exponents:     %6d\n", LDBL_MIN_EXP);
  printf ("Maximale Größe des 2-Exponents:     %6d\n", LDBL_MAX_EXP);
  printf ("Minimale Größe des 10-Exponents:    %6d\n", LDBL_MIN_10_EXP);
  printf ("Maximale Größe des 10-Exponents:    %6d\n", LDBL_MAX_10_EXP);
  printf ("\n");

  printf ("Größe __float80[Byte]:              %6ld\n", sizeof (__float80));

// Diese Angaben fehlen in der quadmath.h
/*
  printf ("Anzahl Bits der Matisse:            %6d\n", FLT80_MANT_DIG);
  printf ("Genauigkeit in Dezimalziffern:      %6d\n", FLT80_DIG);
  printf ("Minimale Größe des 2-Exponents:     %6d\n", FLT80_MIN_EXP);
  printf ("Maximale Größe des 2-Exponents:     %6d\n", FLT80_MAX_EXP);
  printf ("Minimale Größe des 10-Exponents:    %6d\n", FLT80_MIN_10_EXP);
  printf ("Maximale Größe des 10-Exponents:    %6d\n", FLT80_MAX_10_EXP);
*/
  printf ("\n");

  printf ("Größe __float128[Byte]:             %6ld\n", sizeof (__float128));
  printf ("Anzahl Bits der Matisse:            %6d\n", FLT128_MANT_DIG);
  printf ("Genauigkeit in Dezimalziffern:      %6d\n", FLT128_DIG);
  printf ("Minimale Größe des 2-Exponents:     %6d\n", FLT128_MIN_EXP);
  printf ("Maximale Größe des 2-Exponents:     %6d\n", FLT128_MAX_EXP);
  printf ("Minimale Größe des 10-Exponents:    %6d\n", FLT128_MIN_10_EXP);
  printf ("Maximale Größe des 10-Exponents:    %6d\n", FLT128_MAX_10_EXP);
  printf ("\n");
  return;
  }

int main ()
  {
  genauigkeit ();
  genauigkeitsausgabe ();
  printkonstanten ();
  return 0;
  }
