// Ausgabe und Eingabe der Gruppenklasse auf das Terminal

#include "gruppecon.h"
#include <iostream>    //cout, printf, scanf, FILE*, fopen

void printv3liste (cvektor3liste& pvliste)
  {
  FILE* datei= fopen ("screenoutput.txt", "ab");
  for (integer lauf= 0; lauf < pvliste.anz; lauf++)
    printvektor3ord (pvliste.v[lauf], pvliste.ord[lauf]);
          printf ("\nVektor Liste: %10lld Elemente", pvliste.anz);
  fprintf (datei, "\nVektor Liste: %10lld Elemente", pvliste.anz);
  if (pvliste.uebergelaufen)
    {
            printf ("    übergelaufen");
    fprintf (datei, "    übergelaufen");
    }
          printf ("\n\n");
  fprintf (datei, "\n\n");
  fclose (datei);
  }

void printv3listeobj (const char* pdateiname, cvektor3liste& pvliste)
  {
  for (integer lauf= 0; lauf < pvliste.anz; lauf++)
    printvektor3blenderobj (pdateiname, pvliste.v[lauf], 8);
  printtextobj (pdateiname, "\n");
  }

void printv3listekantenobj (const char* pdateiname, cvektor3liste& pvliste)
  {
  printv3listeobj (pdateiname, pvliste);

  real minwinkel, akwinkel;
  integer kantenanz= 0;

  for (integer laufx= 0; laufx < pvliste.anz; laufx++)
    {
    minwinkel= PI;
    for (integer laufy= 0; laufy < pvliste.anz; laufy++)
        {
        akwinkel= winkelb (pvliste.v[laufx], pvliste.v[laufy]);
        if ((akwinkel > 0) && (akwinkel < minwinkel))
          minwinkel= akwinkel;
        }

    for (integer laufy= laufx; laufy < pvliste.anz; laufy++)
        {
        akwinkel= winkelb (pvliste.v[laufx], pvliste.v[laufy]);
        if ((akwinkel > 0) && (aehnlich (akwinkel, minwinkel)))
          {
          printkante (pdateiname, laufx+1, laufy+1);
          kantenanz++;
          }
        }
    }
  printtextobj (pdateiname, "\n");
  printtextobj (pdateiname, "# Kanten: ");
  printrealobj (pdateiname, real (kantenanz));
  printtextobj (pdateiname, "\n\n");
  }

void printv3listekreiskantenobj (const char* pdateiname, cvektor3liste& pvliste, integer pkreispunkte)
  {
//  printv3listekantenobj (pdateiname, pvliste);

  real minwinkel, akwinkel;
  integer kantenanz= 0;
  integer kantenpos= 0;
  integer kreisanz= pkreispunkte;

  for (integer laufx= 0; laufx < pvliste.anz; laufx++)
    {
    minwinkel= PI;
    for (integer laufy= 0; laufy < pvliste.anz; laufy++)
        {
        akwinkel= winkelb (pvliste.v[laufx], pvliste.v[laufy]);
        if ((akwinkel > 0) && (akwinkel < minwinkel))
          minwinkel= akwinkel;
        }

    for (integer laufy= laufx; laufy < pvliste.anz; laufy++)
        {
        akwinkel= winkelb (pvliste.v[laufx], pvliste.v[laufy]);
        if ((akwinkel > 0) && (aehnlich (akwinkel, minwinkel)))
          {
//          printkante (pdateiname, laufx+1, laufy+1);
          printkreiskante (pdateiname, pvliste, laufx+1, laufy+1, kreisanz, kantenpos);
          kantenanz++;
          kantenpos= kantenpos + kreisanz + 1;   // letzer Punkt der Linie muss übergangen werden
          }
        }
    }
  printtextobj (pdateiname, "\n");
  printtextobj (pdateiname, "# Kanten: ");
  printrealobj (pdateiname, real (kantenanz));
  printtextobj (pdateiname, "\n");
  }

void printv3listeobjalt (const char* pdateiname, cvektor3liste& pvliste)
  {
  for (integer lauf= 0; lauf < pvliste.anz; lauf++)
    printvektor3obj (pdateiname, pvliste.v[lauf]);
          printf ("\nVektor Liste: %10lld Elemente", pvliste.anz);

  FILE* datei= fopen (pdateiname, "ab");
  if (pvliste.uebergelaufen)
    {
            printf ("    übergelaufen");
    fprintf (datei, "    übergelaufen");
    }
          printf ("\n\n");
  fprintf (datei, "\n");
  fclose (datei);
  }

void printgruppenkoerper (const char* pdateiname, integer gord, cvektor4 dreh1, cvektor4 dreh2, cvektor3 ecke, cvektor3liste& pvliste)
  {
  FILE* datei= fopen (pdateiname, "ab");
  fprintf (datei, "# Gruppenordnung: %5lld\n\n", gord);
  fprintf (datei, "# Drehung1: ");
  printvektor4drehobj (pdateiname, dreh1);
  fprintf (datei, "\n# Drehung2: ");
  printvektor4drehobj (pdateiname, dreh2);
  fprintf (datei, "\n# Eckenvektor: ");
  printvektor3obj (pdateiname, ecke);
  fclose (datei);
  datei= fopen (pdateiname, "ab");
  for (integer lauf= 0; lauf < pvliste.anz; lauf++)
    printvektor3obj (pdateiname, pvliste.v[lauf]);
  if (pvliste.uebergelaufen)
    {
    fprintf (datei, "    übergelaufen");
    }
  fprintf (datei, "\n");
  fclose (datei);
  }

void printb3liste (cbasis3liste& pbliste)
  {
  FILE* datei= fopen ("screenoutput.txt", "ab");
  for (integer lauf= 0; lauf < pbliste.anz; lauf++)
    //printbasis3dreh (pbliste.b[lauf], pbliste.ord[lauf], pbliste.zykel[lauf], pbliste.gepaart[lauf]);
    printbasis3mat (pbliste.b[lauf], pbliste.ord[lauf], pbliste.zykel[lauf]);
  printf ("\nMatrix Liste: %10lld Elemente", pbliste.anz);
  fprintf (datei, "\nMatrix Liste: %10lld Elemente", pbliste.anz);
  if (pbliste.uebergelaufen)
    {
    printf ("    übergelaufen");
    fprintf (datei, "    übergelaufen");
    }
  printf ("\n\n");
  fprintf (datei, "\n\n");
  for (integer lauf= 0; lauf < pbliste.anz + 1; lauf++)
    if (pbliste.ordanz[lauf] > 0)
      {
      printf ("%5lld %5lld\n", pbliste.ordanz[lauf], lauf);
      fprintf (datei, "%5lld %5lld\n", pbliste.ordanz[lauf], lauf);
      }
  printf ("\n");
  fprintf (datei, "\n");
  fclose (datei);
  }

void printv4liste (cvektor4liste& pqliste)
  {
  FILE* datei= fopen ("screenoutput.txt", "ab");
  for (integer lauf= 0; lauf < pqliste.anz; lauf++)
    printvektor4dreh (pqliste.v[lauf], pqliste.ord[lauf], pqliste.zykel[lauf], pqliste.gepaart[lauf]);
  printf ("\nQuaternionen Liste: %10lld Elemente", pqliste.anz);
  fprintf (datei, "\nQuaternionen Liste: %10lld Elemente", pqliste.anz);
  if (pqliste.uebergelaufen)
    {
    printf ("    übergelaufen");
    fprintf (datei, "    übergelaufen");
    }
  printf ("\n\n");
  fprintf (datei, "\n\n");
  for (integer lauf= 0; lauf < pqliste.anz + 1; lauf++)
    if (pqliste.ordanz[lauf] > 0)
      {
      printf ("%5lld %5lld\n", pqliste.ordanz[lauf], lauf);
      fprintf (datei, "%5lld %5lld\n", pqliste.ordanz[lauf], lauf);
      }
  printf ("\n\n");
  fprintf (datei, "\n\n");
  fclose (datei);
  }

void printkreis (const char* pdateiname, cbasis3 pkreisbasis, integer ppunkte)
  {
  FILE* datei= fopen (pdateiname, "ab");
  real winkel;
  cvektor3 kreispunkt;

  printtextobj (pdateiname, "-------------------------------------------------------------------------------------------\n# Kreis");
  printzahlobj (pdateiname, ppunkte, 0, 0);
  printtextobj (pdateiname, "\n\n");
  for (integer lauf= 0; lauf < ppunkte; lauf++)
    {
    winkel= lauf*2*PI/ppunkte;
    kreispunkt.x= cosr (winkel);
    kreispunkt.y= sinr (winkel);
    kreispunkt.z= 0;
    kreispunkt= pkreisbasis*kreispunkt;
    printvektor3obj (pdateiname, kreispunkt);
    }
  printtextobj (pdateiname, "\nl");
  for (integer lauf= 0; lauf < ppunkte; lauf++)
    printzahlobj (pdateiname, lauf+1, 0, 0);
  printzahlobj (pdateiname, 1, 0, 0);
  printtextobj (pdateiname, "\n");
  fclose (datei);
  }

void printkante (const char* pdateiname, integer p1, integer p2)
  {
  printtextobj (pdateiname, "l ");
  printzahlobj (pdateiname, p1, 1);
  printtextobj (pdateiname, " ");
  printzahlobj (pdateiname, p2, 1);
  printtextobj (pdateiname, "\n");
  }

void printkreiskante (const char* pdateiname, cvektor3liste pvliste, integer p1, integer p2, integer pkreisanz, integer ppos)

  {
  cvektor3 kreisx, kreisy, kreisz, kreislauf;
  real kreiswinkel, kreisschritt;
  cvektor3liste kantenliste (1000);

  kreisx= pvliste.v[p1 - 1];                    // wavefront nummeriert die Punkte ab 1 statt ab 0
  kreisy= pvliste.v[p2 - 1];
  kreiswinkel= winkelb (kreisx, kreisy);
  kreisschritt= kreiswinkel/pkreisanz;
  kreisz= normiere (kreisx^kreisy);
  kreisy= kreisz^kreisx;
  kreisz= kreisx^normiere (kreisy);
  printtextobj (pdateiname, "\n");

  for (integer lauf= 0; lauf < pkreisanz + 1; lauf++)                 // einen mehr, weil sonst der Endpunkt nicht geschlossen ist. Endpunkt ist neuer Anfangspunkt. Anfangspunkt und Endpunkt überlappen sich
    {
    kreislauf= cosr (kreisschritt*lauf)*kreisx + sinr (kreisschritt*lauf)*kreisy;
    kantenliste.elementhinzu (kreislauf, 0);
    }

  printv3listeobj (pdateiname, kantenliste);
  printtextobj (pdateiname, "l");
  for (integer lauf= 0; lauf < pkreisanz + 1; lauf++)                 // einen mehr, weil sonst der Endpunkt nicht geschlossen ist. Endpunkt ist neuer Anfangspunkt. Anfangspunkt und Endpunkt überlappen sich
    {
    printtextobj (pdateiname, " ");
    printzahlobj (pdateiname, ppos+lauf + 1, 0);
    }
  printtextobj (pdateiname, "\n\n");
  }

