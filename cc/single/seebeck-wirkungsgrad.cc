// Diesese Programm berechnet den Wirkungsgrad eines Seebeckelements aus 4 gemessenen Temperaturen

#include <cstdio>
#include <cmath>

void wirkungsgradseebeck ()
  {
  long double wl, dk, a, t1, t2, t3, t4;

  printf ("\n");
  printf ("bitte geben sie die spezifische W‰rmeleitf‰higkeit [W/(mK)] der Messplatten ein:  ");
  scanf ("%Lf", &wl);
  printf ("bitte geben sie die Dicke [mm] der Messplatten ein:  ");
  scanf ("%Lf", &dk);
  printf ("bitte geben sie die Kantenl‰nge [mm] der Messplatten ein:  ");
  scanf ("%Lf", &a);
  printf ("bitte geben sie die 4 gemessenen Temperaturen [∞C] in absteigender Reihenfolge ein.\n");
  printf ("T1:  ");
  scanf ("%Lf", &t1);
  printf ("T2:  ");
  scanf ("%Lf", &t2);
  printf ("T3:  ");
  scanf ("%Lf", &t3);
  printf ("T4:  ");
  scanf ("%Lf", &t4);
  
  long double A= (a/1000)*(a/1000);  // Fl‰che in m≤ umrechnen
  long double d= dk/1000;            // Dicke in m umrechnen
  long double w1= A/d*wl*(t1-t2);    // Fouriersches Gesetz hineinflieﬂender W‰rmestrom
  long double w2= A/d*wl*(t3-t4);    // Fouriersches Gesetz herausflieﬂender W‰rmestrom
  long double pu= w1 - w2;           // die Differenz ist der abgezweigte W‰rmestrom, welcher umgewandelt wurde
  long double wgradp= pu/w1*100;     // Wirkungsgrad ist der abgezweigte W‰rmestrom im Verh‰ltnis zum eingeflossenen W‰rmestrom

  printf ("\n");
  printf ("W‰rmeleitf‰higkeit:                             %24.3Lf W/(mK)\n", wl);
  printf ("Dicke:                                          %24.1Lf mm\n", dk);
  printf ("Kantenl‰nge:                                    %24.0Lf mm\n", a);
  printf ("T1:                                             %24.2Lf ∞C\n", t1);
  printf ("T2:                                             %24.2Lf ∞C\n", t2);
  printf ("T3:                                             %24.2Lf ∞C\n", t3);
  printf ("T4:                                             %24.2Lf ∞C\n", t4);
  printf ("\n");
  printf ("der hereinflieﬂende W‰rmestrom betr‰gt:         %24.3Lf Watt\n", w1);
  printf ("der herausflieﬂende W‰rmestrom betr‰gt:         %24.3Lf Watt\n", w2);
  printf ("die umgewandelte W‰rmeenergie betr‰gt:          %24.3Lf Watt\n", pu);
  printf ("der Wirkungsgrad der Energieumwandlung ist:     %24.3Lf Prozent\n", wgradp);
  printf ("\n");
  }

int main ()
  {
  wirkungsgradseebeck ();
  return 0;
  }
