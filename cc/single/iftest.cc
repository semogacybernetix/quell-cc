#include <iostream>        // printf

/*
Programmieren durch Einrückung: Compiler kann das leider nicht verstehen

 void innerelse ()
  {
  if (true)
    if (true)
      cout << "if-if\n";
      else
      cout << "if-else\n";
  }

 void outerelse ()
  {
  if (true)
    if (true)
      cout << "if-if\n";
    else
    cout << "else\n";
  }

Es müssen beide Zweige, d.h. der then-Zweig und der else-Zweig einzeln geklammert werden.
Das ganze if zu klammern mit dem else als Trennung in der Mitte funktioniert nicht.
Der else-Zweig ist durch das Schlüsselwort else gekennzeichnet.
Der then-Zweig ist durch kein Schlüsselwort gekennzeichnet.
Das if-Schlüsselwort fasst die beiden Zweige (then, else) zusammen.
*/

void iftest ()
  {
  signed long long a= 6;

//---------------- IF Einzelzweig Einzelanweisung -------------------------------------------------------------------------
  if (a == 5)
    printf ("a ist fünf\n");

  printf ("Das war if mit True-Zweig mit Einzelanweisung\n\n");

  if (a == 5)
    /**/ {}
    else printf ("a ist nicht fünf\n");

  printf ("Das war if mit False-Zweig mit Einzelanweisung\n\n");

//---------------- SWITCH Einzelzweig Einzelanweisung -------------------------------------------------------------------------
  switch (a == 5)
    case true: printf ("a ist fünf\n");                                                    // break Statement am Ende verboten (not in a switch or loop)

  printf ("Das war switch mit True-Zweig mit Einzelanweisung\n\n");

  switch (a == 5)
    case false: printf ("a ist nicht fünf\n");                                             // break Statement am Ende verboten (not in a switch or loop)

  printf ("Das war switch mit False-Zweig mit Einzelanweisung\n\n");

//---------------- IF Einzelzweig Mehrfachanweisung -------------------------------------------------------------------------
  if (a == 5)
    {
    printf ("a ist fünf\n");
    printf ("a ist immer noch fünf\n");
    }

  printf ("Das war if mit True-Zweig mit Mehrfachanweisung\n\n");

  if (a == 5)
    {}
    else
    {
    printf ("a ist nicht fünf\n");
    printf ("a ist immer noch nicht fünf\n");
    }

  printf ("Das war if mit False-Zweig mit Mehrfachanweisung\n\n");

//---------------- SWITCH Einzelzweig Mehrfachanweisung -------------------------------------------------------------------------
  switch (a == 5)
    case true:
    {
    printf ("a ist fünf\n");                                                    // break Statement am Ende verboten (not in a switch or loop)
    printf ("a ist immer noch fünf\n");
    }

  printf ("Das war switch mit True-Zweig mit Mehrfachanweisung\n\n");

  switch (a == 5)
    case false:
    {
    printf ("a ist nicht fünf\n");                                             // break Statement am Ende verboten (not in a switch or loop)
    printf ("a ist immer noch nicht fünf\n");
    }

  printf ("Das war switch mit False-Zweig mit Mehrfachanweisung\n\n");

//---------------- IF Mehrfachzweig Einzelanweisung -------------------------------------------------------------------------
  if (a == 5)
    printf ("a ist fünf\n");
    else
    printf ("a ist nicht fünf\n");

  printf ("Das if mit Mehrfach-Zweig mit Einzelanweisung\n\n");

//------- SWITCH Mehrfachzweig Einzelanweisung ---------------------------------------------------------------------------------------------------------------------------------------
  switch (a == 5)
    {
    case true:  printf ("a ist fünf\n"); break;
    case false: printf ("a ist nicht fünf\n"); break;
    }

  printf ("Das war switch Mehrfachzweig Einzelanweisung\n\n");

  switch (a == 5)
    {
    case false: printf ("a ist nicht fünf\n"); break;
    case true:  printf ("a ist fünf\n"); break;
    }

  printf ("Das war switch Mehrfachzweig Einzelanweisung umgekehrt\n\n");

//---------------- IF Mehrfachzweig Mehrfachanweisung -------------------------------------------------------------------------
  if (a == 5)
    {
    printf ("a ist fünf\n");
    printf ("a ist immer noch fünf\n");
    }
    else
    {
    printf ("a ist nicht fünf\n");
    printf ("a ist immer noch nicht fünf\n");
    }

  printf ("Das if mit Mehrfach-Zweig mit Einzelanweisung\n\n");

//---------------- SWITCH Mehrfachzweig Mehrfachanweisung -------------------------------------------------------------------------
  switch (a == 5)
    {
    case true:
    printf ("a ist fünf\n");
    printf ("a ist immer noch fünf\n");
    break;
    case false:
    printf ("a ist nicht fünf\n");
    printf ("a ist immer noch nicht fünf\n");
    break;
    }

  printf ("Das war switch Mehrfachzweig Mehrfachanweisung\n\n");

  switch (a == 5)
    {
    case false:
    printf ("a ist nicht fünf\n");
    printf ("a ist immer noch nicht fünf\n");
    break;
    case true:
    printf ("a ist fünf\n");
    printf ("a ist immer noch fünf\n");
    break;
    }

  printf ("Das war switch Mehrfachzweig Mehrfachanweisung umgekehrt\n\n");

//-- switch-Kette False-Zweig --------------------------------------------------------------------------------------------------------------------------------------------
  switch (a == 5)
    {
    case true:
    printf ("a ist fünf\n");
    printf ("a ist immer noch fünf\n");
    break;
    case false:
  switch (a == 6)
    {
    case true:
    printf ("a ist sechs\n");
    printf ("a ist immer noch sechs\n");
    break;
    case false:
  switch (a == 7)
    {
    case true:
    printf ("a ist sieben\n");
    printf ("a ist immer noch sieben\n");
    break;
    }
    }
    }
  printf ("Das war die switch-Kette False-Zweig\n\n");

//--- switch-Kette True-Zweig -------------------------------------------------------------------------------------------------------------------------------------------
  switch (a != 5)
    {
    case false:
    printf ("a ist fünf\n");
    printf ("a ist immer noch fünf\n");
    break;
    case true:
    printf ("a ist nicht fünf\n");
    printf ("a ist immer noch nicht fünf\n");
  switch (a != 6)
    {
    case false:
    printf ("a ist sechs\n");
    printf ("a ist immer noch sechs\n");
    break;
    case true:
    printf ("a ist nicht sechs\n");
    printf ("a ist immer noch nicht sechs\n");
  switch (a != 7)
    {
    case false:
    printf ("a ist sieben\n");
    printf ("a ist immer noch sieben\n");
    break;
    case true:
    printf ("a ist nicht sieben\n");
    printf ("a ist immer noch nicht sieben\n");
    break;
    }
    }
    }

  printf ("Das war die switch-Kette True-Zweig\n\n");

//----------------------------------------------------------------------------------------------------------------------------------------------
  switch (a)
    {
    case 5:
    printf ("a ist fünf\n");
    printf ("a ist immer noch fünf\n");
    break;
    case 6:
    printf ("a ist sechs\n");
    printf ("a ist immer noch sechs\n");
    break;
    case 7:
    printf ("a ist sieben\n");
    printf ("a ist immer noch sieben\n");
    break;
    }

  printf ("Switch Mehrfachfall\n\n");

//-- Mehrfachswitches --------------------------------------------------------------------------------------------------------------------------------------------

  switch (a == 5)
    {
    case false:
    printf ("a ist nicht fünf\n");
    printf ("a ist immer noch nicht fünf\n");
    break;
    case true:
    printf ("a ist fünf\n");
    printf ("a ist immer noch fünf\n");
    break;
    }

  switch (a == 6)
    {
    case false:
    printf ("a ist nicht sechs\n");
    printf ("a ist immer noch nicht sechs\n");
    break;
    case true:
    printf ("a ist sechs\n");
    printf ("a ist immer noch sechs\n");
    break;
    }

  switch (a == 7)
    {
    case false:
    printf ("a ist nicht sieben\n");
    printf ("a ist immer noch nicht sieben\n");
    break;
    case true:
    printf ("a ist sieben\n");
    printf ("a ist immer noch sieben\n");
    break;
    }

  printf ("vollständiger Mehrfachswitch\n\n");

//----------------------------------------------------------------------------------------------------------------------------------------------
  printf ("Ende von iftest\n");
  }

int main ()
  {
  iftest ();
  return 0;
  }
