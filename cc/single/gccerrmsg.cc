#include <cstdio>

// stdint.h      int32 uint

int main ()
  {
  signed char var1;
  signed long long int var2= 75;

  signed char chararray[100];
  signed long long int longlongarray[100];


  var1= var2;                                            // ist inkompatibel, wird aber nicht beanstandet trotz härtester Compilerflags
//  var1= &var2;                                         // ist genauso inkompatibel, wird aber beanstandet (error: invalid conversion from ‘long long int*´ to ‘signed char´)

  var1+= 0;                                                // Variable wird "benutzt" damit der Compiler nicht meckert: unused variable
  printf ("\n");
  printf ("var1: %20.4d    \n", var1);
  printf ("var2: %20.4lld  \n", var2);
  printf ("\n");

  longlongarray[10]= 1234567890;
  chararray[9]= 9;
  chararray[11]= 11;
  chararray[10]= longlongarray[10];
  printf ("\n");
  printf ("longlongarray[10]: %20.4lld  \n", longlongarray[10]);
  printf ("chararray[9]: %20.4d    \n", chararray[9]);
  printf ("chararray[10]: %20.4d    \n", chararray[10]);
  printf ("chararray[11]: %20.4d    \n", chararray[11]);
  printf ("\n");

  return 0;
  }

// Compilerbefehl:
// g++ -std=c++11 -Wall -Wextra -pedantic-errors -O2 gccerrmsg.cc -o /root/bin/linux/sbin/gccerrmsg

// erwartete Fehlermeldung:
// error[10]: illegal assignment because of different data types: var1= var2;: var1 is ‘signed char´ but var2 is ‘signed long long int´

 // void (var1)  benutzen 
/*

Warum beanstandet der Compiler in dem einen Fall und in dem anderen nicht, obwohl beide gleich doll inkompatibel sind?
Was sagen andere Compiler wie Visual Studio?, geht es dort?
Kann man es irgendwie anschalten, dass der gcc bei inkompatiblen Zuweisungen meckert?
Meistens ist der Fehler inkompatibler Zuweisung schwerer zu finden als in dem Beispiel, insbesondere wenn man mit Arrays und Zeigern hantiert statt nur einfachen Variablen.

*/

/*
weiterer Compilerfehler: wenn eine Funktion in der h Datei zwar deklariert aber in der cc Datei nicht implementiert ist, meckert der Compiler nicht.
der Linker meckert dann, dass es einen nicht definierten Verweis auf die Funktion gibt.
Eigentlich hätte der Compiler schon beim übersetzen meckern müssen: function bla (dsfs) declareted in h file, but not implemented in cc file
*/

/*
Problem gelöst:
Man muss -Wconversion als Compilerflag angeben. Dann werden die Fehler auch beanstandet:

*/
