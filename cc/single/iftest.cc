#include <iostream>

using namespace std;

/*
Programmieren durch Einrückung: Compiler kann das leider nicht verstehen

 void innerelse ()
  {
  if (true)
    if (true)
      cout << "ifif\n";
      else
      cout << "else\n";
  }

 void outerelse ()
  {
  if (true)
    if (true)
      cout << "ifif\n";
    else
    cout << "else\n";
  }

*/

// Obwohl hier nur eine Anweisung im äußerem if-Zweig ist, muss dieser trotzdem in Klammern eingeschlossen werden,
// weil sonst nicht klar ist, zu welchem if das else gehört

/*

if a=b
  then machedas
  else machedies

case a=b
  true: machedas
  false: machedies

*/

void innerelse ()
  {
  if (true)
    {
    if (true)
      cout << "ifif\n";
      else
      cout << "ifelse\n";
    }
  }

// Auch bei dieser Konstruktion muss der If-Zweig in Klammern gesetzt werden

void outerelse ()
  {
  if (true)
    {
    if (true)
      cout << "ifif\n";
    }
    else
    cout << "else\n";
  }

void innerswitchelse ()
  {
  switch (true)
    case true:
    if (true)
      cout << "ifif\n";
      else
      cout << "ifelse\n";
  }

void outerswitchelse ()
  {
  switch (true)
    {
    case true:
    if (true)
      cout << "ifif\n";
    break;

    case false:
    cout << "else\n";
    break;
    }
  }

void innerswitch ()
  {
  switch (true)
    case true:
    switch (true)
      {
      case true:
      cout << "ifif\n";
      break;

      case false:
      cout << "ifelse\n";
      break;
      }
  }


void outerswitch ()
  {
  switch (true)
    {
    case true:
    switch (true)
      case true:
      cout << "ifif\n";
      break;

    case false:
    cout << "else\n";
    break;
    }
  }


void halfifsingle ()
  {
  if (true)
    cout << "true\n";
  }

void halfifmulti ()
  {
  if (true)
    {
    cout << "true1\n";
    cout << "true2\n";
    }
  }

void fullifsingle ()
  {
  if (true)
    cout << "true\n";
    else
    cout << "false\n";
  }

void fullifmulti ()
  {
  if (true)
    {
    cout << "true1\n";
    cout << "true2\n";
    }
    else
    {
    cout << "false1\n";
    cout << "false2\n";
    }
  }

/*
vollständiger Syntax:

if (true)
  else
  cout << "Die Bedingung ist nicht erfüllt\n";
  then
  cout << "Die Bedingung ist erfüllt\n";

*/


/*
Es müssen beide Zweige, d.h. der then-Zweig und der else-Zweig einzeln geklammert werden.
Das ganze if zu klammern mit dem else als Trennung in der Mitte funktioniert nicht.
Der else-Zweig ist durch das Schlüsselwort else gekennzeichnet.
Der then-Zweig ist durch kein Schlüsselwort gekennzeichnet.
Das if-Schlüsselwort fasst die beiden Zweige (then, else) zusammen.
*/
void ifklammerung ()
{
if (true)
  {
  cout << "  1. Die Bedingung ist erfüllt\n";
  cout << "  2. Die Bedingung ist erfüllt\n";
  }
  else
  cout << "  1. Die Bedingung ist nicht erfüllt\n";
  cout << "  2. Die Bedingung ist nicht erfüllt\n";

cout << "True-Zweig abgeschlossen\n";

if (false)
  {
  cout << "  1. Die Bedingung ist erfüllt\n";
  cout << "  2. Die Bedingung ist erfüllt\n";
  }
  else
  {
  cout << "  1. Die Bedingung ist nicht erfüllt\n";
  cout << "  2. Die Bedingung ist nicht erfüllt\n";
  }

cout << "False-Zweig abgeschlossen\n";
}

void elseexperiment ()
{
if (true)
  {
  }
  else
  cout << "Die Bedingung ist nicht erfüllt\n";
}


// bei halfswitchsingle darf kein break stehen, weil sonst der Compiler meckert

void halfswitchsingle ()
  {
  switch (true)
    case true:
    cout << "true\n";
  }

// Obwohl es hier nur einen Fall gibt, muss der switch in Klammern stehen,
// weil der Compiler sonst das break anmeckert.

void halfswitchmulti ()
  {
  switch (false)
    {
    case true:
    cout << "true1\n";
    cout << "true2\n";
    break;
    }
  }

void halfswitchmulti2 ()
  {
  switch (false)
    case true:
    {
    cout << "true1\n";
    cout << "true2\n";
    }
  }

void fullswitchsingle ()
  {
  switch (true)
    {
    case true:
    cout << "true\n";
    break;

    case false:
    cout << "false\n";
    break;
    }
  }

void fullswitchsingle2 ()
  {
  switch (false)
    {
    case true: cout << "true\n"; break;
    case false: cout << "false\n"; break;
    }
  }
void fullswitchmulti ()
  {
  switch (true)
    {
    case true:
    cout << "true1\n";
    cout << "true2\n";
    break;

    case false:
    cout << "false1\n";
    cout << "false2\n";
    break;
    }
  }

void iftest ()
  {
  signed long long a= 6;

//----------------------------------------------------------------------------------------------------------------------------------------------
  switch (a == 5)
    case true: printf ("a ist fünf\n");                                             // break Statement am Ende verboten (not in a switch or loop)
  printf ("Das war einzelif\n\n");

  switch (a == 5)
    case false: printf ("a ist nicht fünf\n");                                             // break Statement am Ende verboten (not in a switch or loop)
  printf ("Das war einzelif\n\n");

//----------------------------------------------------------------------------------------------------------------------------------------------
  switch (a == 5)
    case true:
    {
    printf ("a ist fünf\n");
    printf ("a ist immer noch fünf\n");
    }
  printf ("Das war Blockif\n\n");

//----------------------------------------------------------------------------------------------------------------------------------------------
  switch (a == 5)
    case false:
    {
    printf ("a ist nicht fünf\n");
    printf ("a ist immer noch nicht fünf\n");
    }
  printf ("Das war Blockif\n\n");

//----------------------------------------------------------------------------------------------------------------------------------------------
  switch (a == 5)
    {
    case true:  printf ("a ist fünf\n"); break;
    case false: printf ("a ist nicht fünf\n"); break;
    }
  printf ("Das war ifelse\n\n");

  switch (a == 5)
    {
    case false: printf ("a ist nicht fünf\n"); break;
    case true:  printf ("a ist fünf\n"); break;
    }
  printf ("Das war ifelse umgekehrt\n\n");

  if (a == 5)
    printf ("a ist fünf\n");
  else
    printf ("a ist nicht fünf\n");
  printf ("Das war ifelse\n\n");

//----------------------------------------------------------------------------------------------------------------------------------------------
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
  printf ("Das war Blockifelse\n\n");

//----------------------------------------------------------------------------------------------------------------------------------------------
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
  printf ("Das war Blockifelse\n\n");

//----------------------------------------------------------------------------------------------------------------------------------------------
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
  printf ("Das war die offene ifelse Kette\n\n");

//----------------------------------------------------------------------------------------------------------------------------------------------
  switch (a == 5)
    {
    case true:
    printf ("a ist fünf\n");
    printf ("a ist immer noch fünf\n");
    break;
    case false:
    printf ("a ist nicht fünf\n");
    printf ("a ist immer noch nicht fünf\n");
  switch (a == 6)
    {
    case true:
    printf ("a ist sechs\n");
    printf ("a ist immer noch sechs\n");
    break;
    case false:
    printf ("a ist nicht sechs\n");
    printf ("a ist immer noch nicht sechs\n");
  switch (a == 7)
    {
    case true:
    printf ("a ist sieben\n");
    printf ("a ist immer noch sieben\n");
    break;
  // default
    case false:
    printf ("a ist nicht sieben\n");
    printf ("a ist immer noch nicht sieben\n");
    break;
    }
    }
    }
  printf ("Das war die abgeschlossene ifelse Kette\n\n");

//----------------------------------------------------------------------------------------------------------------------------------------------
  printf ("Ende von iftest\n");
  }

int main ()
  {
  iftest ();
  return 0;
  }
