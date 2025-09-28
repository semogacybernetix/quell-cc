#ifndef gruppecon_h
#define gruppecon_h

#include "../cc/class/gruppe.h"
#include "vektorcon.h"

void printv3liste (cvektor3liste& pvliste);
void printv3listeobj (const char* pdateiname, cvektor3liste& pvliste);
void printv3listekantenobj (const char* pdateiname, cvektor3liste& pvliste);
void printv3listekreiskantenobj (const char* pdateiname, cvektor3liste& pvliste, integer pkreispunkte);
void printgruppenkoerper (const char* pdateiname, integer gord, cvektor4 dreh1, cvektor4 dreh2, cvektor3 ecke, cvektor3liste& pvliste);
void printb3liste (cbasis3liste& pbliste);
void printv4liste (cvektor4liste& pqliste);
void printkreis (const char* pdateiname, cbasis3 pkreisbasis, integer ppunkte);
void printkante (const char* pdateiname, integer p1, integer p2);
void printkreiskante (const char* pdateiname, cvektor3liste pvliste, integer p1, integer p2, integer pschritt, integer ppos);

#endif
