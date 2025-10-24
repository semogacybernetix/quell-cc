// Ausgabe und Eingabe der Vektorklasse auf das Terminal

#include "vektorcon.h"
#include <iostream>     // FILE*, fopen, fclose, scanf

using namespace std;

zahl1010::zahl1010 ()
  {
  wert= 0;
  vz= 1;
  for (integer lauf= 0; lauf < 20; lauf++)
    zf[lauf]= 0;
  est= 20;
  }

void zahl1010::erstelle (real pwert)
  {
  if (pwert < 0)
    {
    vz= -1;
    pwert= -pwert;
    }
  wert= pwert;
  pwert= pwert + pwert*real(1e-16);                               // Genauigkeitsproblem:  verhindern das er  0,0999999999999999999999999999999999 statt 0,1 macht
  pwert= pwert/real (1e10);
  for (integer lauf= 0; lauf < 20; lauf++)
    {
    pwert= pwert*10;
    zf[lauf]= integer (pwert);
    pwert= pwert - real (zf[lauf]);
    }

  est= 9;                                                   // die Stelle vor dem Komma muss immer gedruckt werden selbst wenn sie Null ist somit ist die erste Stelle höchstens 9
  for (integer lauf= 0; lauf < 9; lauf++)
    if (zf[lauf] > 0)
      {
      est= lauf;
      break;
      }
  }

void zahl1010::print (char* pstring, integer pst)
  {
  real bwert= wert;
  erstelle (wert + expr(-(real (pst) + 1)*logr (real (10))));             // erste Stelle nach Genauigkeit temporär um 1 erhöhen um 0.499999999 zu vermeiden

  integer position= 0;
  if (pst > 10)
    pst= 10;
  if ((vz < 0) && (wert > expl (-pst*logl (10))))           // die aus einem negativen Wert durch Abschneiden der Nachkommastellen entstandene Null wird immer ohne Minusvorzeichen ausgegeben
  if (vz < 0)
    {
    sprintf (pstring + position, "-");
    position++;
    }

  for (integer lauf= est; lauf < 10; lauf++)
    if ((zf[lauf] > 0) || (lauf > est) || (lauf == 9))      // Stelle drucken wenn sie größer als Null ist, zwar Null ist aber hinter der ersten Stelle steht oder zwar Null ist aber die Einer-Stelle ist
      {
      sprintf (pstring + position, "%lld", zf[lauf]);
      position++;
      }

  integer lsicht= 9;
  for (integer lauf= 9 + pst; lauf > 9; lauf--)             // letzte Nullen ab der Genauigkeitsstelle zählen um sie dann wegzulassen
    if (zf[lauf] > 0)
      {
      lsicht= lauf;
      break;
      }

  if (lsicht > 9)
    {
    sprintf (pstring + position, ".");                      // Punkt drucken, wenn es auch nach der Genauigkeitsabschneidung Nachkommastellen gibt
    position++;
    for (integer lauf= 10; lauf < 10 + pst; lauf++)
      {
      if ((zf[lauf] > 0) || (lauf < lsicht))                // Nachkommastelle drucken wenn sie größer als Null ist oder kleiner als die letzte sichtbare Stelle ist
        {
        sprintf (pstring + position, "%lld", zf[lauf]);
        position++;
        }
      }
    }
  erstelle (bwert);                                         // alten Wert wiederherstellen
  }

void zahl1010::print (char* pstring, integer vst, integer pst)
  {
  real bwert= wert;
  erstelle (wert + expr(logr (real (10))*-(1 + real (pst))));             // erste Stelle nach Genauigkeit temporär um 1 erhöhen um 0.499999999 zu vermeiden

  char zeichen;
  integer position= 0;

  if (pst > 10)
    pst= 10;
  if ((vz < 0) && (wert > expr (real (-pst)*logr (real (10)))))    // die aus einem negativen Wert durch Abschneiden der Nachkommastellen entstandene Null wird immer ohne Minusvorzeichen ausgegeben
    zeichen= '-';
    else
    zeichen= ' ';

  integer bst= 9 - vst;
  if ((est - 1) < bst)                                      // Formatierung brechen, wenn die Zahl nicht in die Vorkommaformatierung passt
    bst= est;
  for (integer lauf= bst; lauf < 10; lauf++)
    {
    if (lauf == est)
      {
      pstring[position]= zeichen;
      position++;
      }
    if ((zf[lauf] > 0) || (lauf >= est) || (lauf == 9))     // Stelle drucken wenn sie größer als Null ist, zwar Null ist aber hinter der ersten Stelle steht oder zwar Null ist aber die Einer-Stelle ist
      sprintf (pstring + position, "%lld", zf[lauf]);
      else
      sprintf (pstring + position, " ");
    position++;
    }

  integer lsicht= 9;
  for (integer lauf= 9 + pst; lauf > 9; lauf--)             // letzte Nullen ab der Genauigkeitsstelle zählen um sie dann wegzulassen
    if (zf[lauf] > 0)
      {
      lsicht= lauf;
      break;
      }

  if (lsicht > 9)
    {
    sprintf (pstring + position, ".");                      // Punkt drucken, wenn es auch nach der Genauigkeitsabschneidung Nachkommastellen gibt
    position++;
    for (integer lauf= 10; lauf < 10 + pst; lauf++)
      {
      if ((zf[lauf] > 0) || (lauf < lsicht))                // Nachkommastelle drucken wenn sie größer als Null ist oder kleiner als die letzte sichtbare Stelle ist
        {
        sprintf (pstring + position, "%lld", zf[lauf]);
        }
        else
        {
        sprintf (pstring + position, " ");
        }
      position++;
      }
    }
    else
    {
    sprintf (pstring + position, " ");                      // Punkt drucken, wenn es auch nach der Genauigkeitsabschneidung Nachkommastellen gibt
    position++;
    for (integer lauf= 10; lauf < 10 + pst; lauf++)
      {
      if ((zf[lauf] > 0) || (lauf < lsicht))                // Nachkommastelle drucken wenn sie größer als Null ist oder kleiner als die letzte sichtbare Stelle ist
        {
        sprintf (pstring + position, "%lld", zf[lauf]);
        }
        else
        {
        sprintf (pstring + position, " ");
        }
      position++;
      }
    }
  erstelle (bwert);                                         // alten Wert wiederherstellen
  }

void zahl1010::printobj (const char* pdateiname, integer pst)
  {
  char* string1;

  string1= new char[100];
  print (string1, pst);
  FILE* datei= fopen (pdateiname, "ab");
  fprintf (datei, "%s", string1);
  fclose (datei);
  }

void zahl1010::printobj (const char* pdateiname, integer vst, integer pst)
  {
  char* string1;

  string1= new char[100];
  print (string1, vst, pst);
  FILE* datei= fopen (pdateiname, "ab");
  fprintf (datei, "%s", string1);
  fclose (datei);
  }

//------------------------------------------------------------------------ real Eingabe ---------------------------------------------------------------------------------------------------

void realeingabe (_Float32& pr)
  {
  integer scanret;
  float pf;
  scanret= scanf ("%f", &pf);
  scanret+= 0;
  pr= _Float32 (pf);
  }

void realeingabe (_Float64& pr)
  {
  integer scanret;
  double pf;
  scanret= scanf ("%lf", &pf);
  scanret+= 0;
  pr= _Float64 (pf);
  }

void realeingabe (double& pr)
  {
  integer scanret;
  scanret= scanf ("%lf", &pr);
  scanret+= 0;
  }

void realeingabe (long double& pr)
  {
  integer scanret;
  scanret= scanf ("%Lf", &pr);
  scanret+= 0;
  }

//------------------------------------------------------------------------ real Ausgabe ---------------------------------------------------------------------------------------------------

void printtext (const char* ptext)
  {
  FILE* datei= fopen ("screenoutput.txt", "ab");
          printf ("%s", ptext);
  fprintf (datei, "%s", ptext);
  fclose (datei);
  }

void printtextobj (const char* pdateiname, const char* ptext)
  {
  FILE* datei= fopen (pdateiname, "ab");
  fprintf (datei, "%s", ptext);
  fclose (datei);
  }

void printinteger (integer pn)
  {
  FILE* datei= fopen ("screenoutput.txt", "ab");
  printf ("%lld", pn);
  fprintf (datei, "%lld", pn);
  fclose (datei);
  }

void printreal (_Float32 pr)
  {
  float pl= float (pr);
  FILE* datei= fopen ("screenoutput.txt", "ab");
  printf ("%12.9f", pl);
  fprintf (datei, "%12.9f", pl);
  fclose (datei);
  }

void printreal (_Float64 pr)
  {
  double pl= double (pr);
  FILE* datei= fopen ("screenoutput.txt", "ab");
  printf ("%12.9lf", pl);
  fprintf (datei, "%12.9lf", pl);
  fclose (datei);
  }

void printreal (long double pr)
  {
  FILE* datei= fopen ("screenoutput.txt", "ab");
  printf ("%12.9Lf", pr);
  fprintf (datei, "%12.9Lf", pr);
  fclose (datei);
  }

void printrealkomplex (double pr)
  {
  FILE* datei= fopen ("screenoutput.txt", "ab");
  printf ("%56.40lf", pr);
  fprintf (datei, "%56.40lf", pr);
  fclose (datei);
  }

void printrealkomplex (long double pr)
  {
  FILE* datei= fopen ("screenoutput.txt", "ab");
  printf ("%56.40Lf", pr);
  fprintf (datei, "%56.40Lf", pr);
  fclose (datei);
  }

void printrealobj (const char* pdateiname, _Float32 pr)
  {
  FILE* datei= fopen (pdateiname, "ab");
  double pl= pr;
  //printf ("%0.10g", pl);
  fprintf (datei, "%0.10g", pl);
  fclose (datei);
  }

void printrealobj (const char* pdateiname, _Float64 pr)
  {
  FILE* datei= fopen (pdateiname, "ab");
  double pl= pr;
//  printf ("%0.10lg", pl);
  fprintf (datei, "%0.10lg", pl);
  fclose (datei);
  }

void printrealobj (const char* pdateiname, long double pr)
  {
  FILE* datei= fopen (pdateiname, "ab");
  //printf ("%0.10Lg", pr);
  fprintf (datei, "%0.10Lg", pr);  // nimmt kein _Float128
  fclose (datei);
  }

void printzahlobj (const char* pdateiname, real pr, integer pst)
  {
  zahl1010 zahl;
  zahl.erstelle (pr);
  zahl.printobj (pdateiname, pst);
  }

void printzahlobj (const char* pdateiname, real pr, integer vst, integer pst)
  {
  zahl1010 zahl;
  zahl.erstelle (pr);
  zahl.printobj (pdateiname, vst, pst);
  }

// -------------------------------------------------------------------------- cvektor2 Eingabe ----------------------------------------------------------------------------------------------

void vektor2eingabek (cvektor2& pp)
  {
  printtext ("a real:         ");
  realeingabe (pp.x);
  printtext ("a imaginär      ");
  realeingabe (pp.y);
  printtext ("\n");
  }

void vektor2eingabep (ckomplexp& pp)
  {
  printtext ("Betrag        ");
  realeingabe (pp.b);
  printtext ("Winkel        ");
  realeingabe (pp.w);
  printtext ("\n");
  pp.w= pp.w/180*PI;
  }

// -------------------------------------------------------------------------------------------- cvektor2 Ausgabe --------------------------------------------------------------------------------------------

char* schreibzahl (real z)            // Zahlstring von einer Realzahl erzeugen
  {
  char* ret= new char[1000];

  // Vorkommastellen im Array speichern
  real vk= fabsr (z);
  integer vork= integer (vk);
  char zw, zx;
  for (integer lauf= 0; lauf < 20; lauf++)
    {
    zw= char ('0' + (vork % 10));
    ret[19-lauf]= zw;
    vork= vork/10;
    }

  // führende Nullen entfernen und eventuelles Minuszeichen hinzufügen
  for (integer lauf= 0; lauf < 20; lauf++)
    if ((ret[lauf]== '0') && (lauf < 19))        // eine führende 0 nicht an der 1. Stelle vor dem Komma entfernen
      ret[lauf]= ' ';
      else
      {
      if (z < 0)                                // Minuszeichen vor die erste führende Stelle oder vor die Null an 1. Stelle vor dem Komma setzen
        ret[lauf-1]= '-';
      break;
      }

  ret[20]= '.';                                 // Dezimalpunkt setzen
  vk= vk - floorr (vk);
  for (integer lauf= 21; lauf < 41; lauf++)     // Nachkommastellen setzen
    {
    vk= vk*10;
    zx= char (vk);
    zw= char ('0' + zx);
    ret[lauf]= zw;
    vk= vk - zx;
    }
  ret[41]= 0;                                   // Zahlstring mit 0 terminieren
  return ret;
  }

void printvektor2komplex (const char* pstring, ckomplexk pv, integer psw)    // psw Winkelbereich -180,180 oder 0,360
  {
  FILE* datei= fopen ("screenoutput.txt", "ab");

  ckomplexp vpol;
  if (psw == 1)
    vpol= polar360 (pv);
    else
    vpol= polar180 (pv);

  vpol.w= vpol.w*180/PI;

  char* pvxstr= schreibzahl (pv.x);
  char* pvystr= schreibzahl (pv.y);
          printf ("%s %s     %s\n", pvxstr, pvystr, pstring);
  fprintf (datei, "%s %s     %s\n", pvxstr, pvystr, pstring);

//          printf ("%56.40Lf %56.40Lf       %s%56.40Lf %45.40Lf°\n", pv.x, pv.y, pstring, vpol.b, vpol.w);

//  fprintf (datei, "%56.40Lf %56.40Lf       %s%56.40Lf %45.40Lf°\n", pv.x, pv.y, pstring, vpol.b, vpol.w);

  fclose (datei);
  }

void printvektor2komplexp (const char* pstring, ckomplexp pv)
  {
  pstring= pstring;
  if (pv.b == 0)    // -0 in 0 umwandeln (ich könnte auch -0 bei der Abfrage schreiben, aber das suggeriert, dass er die -0 von der 0 unterscheidet, was er aber nicht macht)
    pv.b= -0;
  if (pv.w == 0)    // -0 in 0 umwandeln (ich könnte auch -0 bei der Abfrage schreiben, aber das suggeriert, dass er die -0 von der 0 unterscheidet, was er aber nicht macht)
    pv.w= -0;

//  ckomplexk vkar= kartes (pv);

////  printf ("%50.40Lf %50.30Lf            %s%50.40Lf %50.30Lf°\n", vkar.x, vkar.y, pstring, pv.b, pv.w*180/PI);
//  printf ("%56.40Lf %56.40Lf       %s%56.40Lf %45.40Lf°\n", vkar.x, vkar.y, pstring, pv.b, pv.w*180/PI);
  }

// -------------------------------------------------------------------------------------------- cvkektor3 Eingabe --------------------------------------------------------------------------------------------

void vektor3eingabe (cvektor3& pv)
  {
  printtext ("\n");
  printtext ("x:  ");
  realeingabe (pv.x);
  printtext ("y:  ");
  realeingabe (pv.y);
  printtext ("z:  ");
  realeingabe (pv.z);
  printtext ("\n");
  }

// -------------------------------------------------------------------------------------------- cvkektor3 Ausgabe --------------------------------------------------------------------------------------------

void printvektor3obj (const char* pdateiname, cvektor3 pv)
  {
  pv= pv;
  FILE* datei= fopen (pdateiname, "ab");
  ////      printf ("v %13.9Lf %13.9Lf %13.9Lf\n", pv.x, pv.y, pv.z);
//  fprintf (datei, "v %14.9Lf %14.9Lf %14.9Lf\n", pv.x, pv.y, pv.z);
  fclose (datei);
  }

void printvektor3infobj (const char* pdateiname, cvektor3 pv)
  {
  pv= pv;
  FILE* datei= fopen (pdateiname, "ab");
  //      printf ("v %13.9Lf %13.9Lf %13.9Lf\n", pv.x, pv.y, pv.z);
//  fprintf (datei, "(%0.2Lg %0.2Lg %0.2Lg)", pv.x, pv.y, pv.z);
  fclose (datei);
  }

void printvektor3perfobj (const char* pdateiname, cvektor3 pv, integer pst)         // fehlerhaft, beim gleichen Objekt wird minuszeichen weitergeschleppt
  {
  zahl1010 zahl;
  printtextobj (pdateiname, "(");
  zahl.erstelle (pv.x);
  zahl.printobj (pdateiname, pst);
  printtextobj (pdateiname, " ");
  zahl1010 zahl2;
  zahl2.erstelle (pv.y);
  zahl2.printobj (pdateiname, pst);
  printtextobj (pdateiname, " ");
  zahl1010 zahl3;
  zahl3.erstelle (pv.z);
  zahl3.printobj (pdateiname, pst);
  printtextobj (pdateiname, ")");
  }

void printvektor3perfobj (const char* pdateiname, cvektor3 pv, integer vst, integer pst)     // genauso fehlerhaft
  {
  zahl1010 zahl;
  zahl.erstelle (pv.x);
  zahl.printobj (pdateiname, vst, pst);
  zahl1010 zahl2;
  zahl2.erstelle (pv.y);
  zahl2.printobj (pdateiname, vst, pst);
  zahl1010 zahl3;
  zahl3.erstelle (pv.z);
  zahl3.printobj (pdateiname, vst, pst);
  }

void printvektor3blenderobj (const char* pdateiname, cvektor3 pv, integer pst)
  {
  printtextobj (pdateiname, "v");
  printvektor3perfobj (pdateiname, pv, 4, pst);
  printtextobj (pdateiname, "\n");
  }

void printvektor3ord (cvektor3 pv, integer pord)
  {
  pv= pv;
  pord= pord;
  FILE* datei= fopen ("screenoutput.txt", "ab");
//          printf ("%13.9Lf %13.9Lf %13.9Lf %8lld\n", pv.x, pv.y, pv.z, pord);
//  fprintf (datei, "%13.9Lf %13.9Lf %13.9Lf %8lld\n", pv.x, pv.y, pv.z, pord);
  fclose (datei);
  }

void printvektor3wi (cvektor3 pv, real wi)
  {
  wi= wi;
  pv= pv;
//  wi*= 180/PI;
  FILE* datei= fopen ("screenoutput.txt", "ab");
//          printf ("    %12.9Lf %12.9Lf %12.9Lf %10.3Lf°\n", pv.x, pv.y, pv.z, wi);
//  fprintf (datei, "    %12.9Lf %12.9Lf %12.9Lf %10.3Lf°\n", pv.x, pv.y, pv.z, wi);
  fclose (datei);
  }

// -------------------------------------------------------------------------------------------- cbasis3 Ausgabe --------------------------------------------------------------------------------------------

void printbasis3mat (cbasis3 pb, integer pord, integer pzykel)
  {
  pb= pb;
  pzykel= pzykel;
  pord= pord;
  FILE* datei= fopen ("screenoutput.txt", "ab");
//          printf ("        %12.9Lf %12.9Lf %12.9Lf        %12.9Lf %12.9Lf %12.9Lf        %12.9Lf %12.9Lf %12.9Lf  %4.1Lf%6lld%24lld\n", pb.x.x, pb.x.y, pb.x.z, pb.y.x, pb.y.y, pb.y.z, pb.z.x, pb.z.y, pb.z.z, det (pb), pord, pzykel);
//  fprintf (datei, "        %12.9Lf %12.9Lf %12.9Lf        %12.9Lf %12.9Lf %12.9Lf        %12.9Lf %12.9Lf %15.9Lf  %4.1Lf%6lld%24lld\n", pb.x.x, pb.x.y, pb.x.z, pb.y.x, pb.y.y, pb.y.z, pb.z.x, pb.z.y, pb.z.z, det (pb), pord, pzykel);
  fclose (datei);
  }

void printbasis3dreh (cbasis3 pb, integer pord, integer pzykel, integer ppaar)
  {
  pzykel= pzykel;
  pord= pord;
  ppaar= ppaar;

  cvektor4 aw;
  real detpb= det (pb);
  if (detpb > 0)
    aw= winkelachsefrommatrix (pb);
    else
    aw= winkelachsefrommatrix (-pb);  // Inversion aus der Drehspiegelungsmatrix rausholen und die übrigbleibende Drehmatrix weiterverarbeiten
//  real wi= aw.r*180/PI;
  FILE* datei= fopen ("screenoutput.txt", "ab");
//          printf ("    %12.9Lf %12.9Lf %12.9Lf %10.3Lf  %4.1Lf%6lld%6lld%24lld\n", aw.i, aw.j, aw.ij, wi, det (pb), ppaar, pord, pzykel);
//  fprintf (datei, "    %12.9Lf %12.9Lf %12.9Lf %10.3Lf  %4.1Lf%6lld%6lld%24lld\n", aw.i, aw.j, aw.ij, wi, det (pb), ppaar, pord, pzykel);
  fclose (datei);
  }

// -------------------------------------------------------------------------------------------- cvektor4 Eingabe --------------------------------------------------------------------------------------------

void quaternioneneingabe (cvektor4& pv)
  {
  printtext ("\n");
  printtext ("r:  ");
  realeingabe (pv.r);
  printtext ("i:  ");
  realeingabe (pv.i);
  printtext ("j:  ");
  realeingabe (pv.j);
  printtext ("ij  ");
  realeingabe (pv.ij);
  printtext ("\n");
  }

cvektor4 winkelachseeingabe ()
  {
  cvektor3 achse (0, 0, 0);
  real wi;

  printtext ("\n");
  printtext ("Drehachse x:       ");
  realeingabe (achse.x);
  printtext ("Drehachse y:       ");
  realeingabe (achse.y);
  printtext ("Drehachse z:       ");
  realeingabe (achse.z);
  achse= normiere (achse);
  printtext ("Drehwinkel [°]:    ");
  realeingabe (wi);
  printtext ("\n");
  wi= wi/180*PI;
  return cvektor4 (wi, achse);
  }

// -------------------------------------------------------------------------------------------- cvektor4 Ausgabe --------------------------------------------------------------------------------------------

void printvektor4quat (cvektor4 pv, integer pord, integer pzykel)
  {
  pzykel= pzykel;
  pord= pord;
  pv= pv;
//  cvektor4 aw= winkelachsefromquaternion (pv);
//  real wi= aw.r*180/PI;
  FILE* datei= fopen ("screenoutput.txt", "ab");
//          printf ("%24.9Lf %12.9Lf %12.9Lf %12.9Lf        %12.9Lf %12.9Lf %12.9Lf %10.3Lf%6lld%24lld\n", pv.r, pv.i, pv.j, pv.ij, aw.i, aw.j, aw.ij, wi, pord, pzykel);
//  fprintf (datei, "%24.9Lf %12.9Lf %12.9Lf %12.9Lf        %12.9Lf %12.9Lf %12.9Lf %10.3Lf%6lld%24lld\n", pv.r, pv.i, pv.j, pv.ij, aw.i, aw.j, aw.ij, wi, pord, pzykel);
  fclose (datei);
  }

void printvektor4dreh (cvektor4 pv, integer pord, integer pzykel, integer ppaar)
  {
  ppaar= ppaar;
  pzykel= pzykel;
  pord= pord;
  pv= pv;
//  cvektor4 aw= winkelachsefromquaternion (pv);
//  real wi= aw.r*180/PI;
  FILE* datei= fopen ("screenoutput.txt", "ab");
//          printf ("    %12.9Lf %12.9Lf %12.9Lf %10.3Lf  %3lld    %6lld%24lld\n", aw.i, aw.j, aw.ij, wi, ppaar, pord, pzykel);
//  fprintf (datei, "    %12.9Lf %12.9Lf %12.9Lf %10.3Lf  %3lld    %6lld%24lld\n", aw.i, aw.j, aw.ij, wi, ppaar, pord, pzykel);
  fclose (datei);
  }

void printvektor4drehobj (const char* pdateiname, cvektor4 pv)
  {
  pv= pv;
//  cvektor4 aw= winkelachsefromquaternion (pv);
//  real wi= aw.r*180/PI;
  FILE* datei= fopen (pdateiname, "ab");
//  fprintf (datei, "    %12.9Lf %12.9Lf %12.9Lf %10.3Lf\n", aw.i, aw.j, aw.ij, wi);
  fclose (datei);
  }

