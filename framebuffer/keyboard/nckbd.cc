#include "nckbd.h"
#include <curses.h>

cnckeyboard::cnckeyboard ()
  {
  initscr ();
  noecho ();
  //curs_set (0);                                                 // blockiert die Bildschirmausgabe
  //raw ();                                                       // blockiert die Bildschirmausgabe
  key[0][0]= 0;
  }

cnckeyboard::~cnckeyboard ()
  {
  endwin ();
  }

void cnckeyboard::flush ()
  {
  int ein;

  ein= getch ();
  if (ein == 195)
    ein= getch ();                                                // Prefix für Umlaute abfangen

  // Funktionstastenreihe
  //if (ein == 27) key[0][0]= 1; else key[0][0]= 0;               // ausgeschaltet wegen Terminalverfälschung nach Abbruch

/*
  // Zahlenreihe
  key[0][1]= (keytab[kb >> 3] >> (kb & 7)) & 1;
  key[1][1]= (keytab[kb >> 3] >> (kb & 7)) & 1;
  key[2][1]= (keytab[kb >> 3] >> (kb & 7)) & 1;
  key[3][1]= (keytab[kb >> 3] >> (kb & 7)) & 1;
  key[4][1]= (keytab[kb >> 3] >> (kb & 7)) & 1;
  key[5][1]= (keytab[kb >> 3] >> (kb & 7)) & 1;
  key[6][1]= (keytab[kb >> 3] >> (kb & 7)) & 1;
  key[7][1]= (keytab[kb >> 3] >> (kb & 7)) & 1;
  key[8][1]= (keytab[kb >> 3] >> (kb & 7)) & 1;
  key[9][1]= (keytab[kb >> 3] >> (kb & 7)) & 1;
  key[10][1]= (keytab[kb >> 3] >> (kb & 7)) & 1;
*/
  // Bewegungen
  if (ein == 113) key[1][2]= 1; else key[1][2]= 0;
  if (ein ==  97) key[1][3]= 1; else key[1][3]= 0;
  if (ein == 119) key[2][2]= 1; else key[2][2]= 0;
  if (ein == 115) key[2][3]= 1; else key[2][3]= 0;
  if (ein == 101) key[3][2]= 1; else key[3][2]= 0;
  if (ein == 100) key[3][3]= 1; else key[3][3]= 0;
  if (ein == 114) key[4][2]= 1; else key[4][2]= 0;
  if (ein == 102) key[4][3]= 1; else key[4][3]= 0;

  // Drehungen
  if (ein == 105) key[8][2]= 1; else key[8][2]= 0;
  if (ein == 107) key[8][3]= 1; else key[8][3]= 0;
  if (ein == 111) key[9][2]= 1; else key[9][2]= 0;
  if (ein == 108) key[9][3]= 1; else key[9][3]= 0;
  if (ein == 112) key[10][2]= 1; else key[10][2]= 0;
  if (ein == 182) key[10][3]= 1; else key[10][3]= 0;
  if (ein == 188) key[11][2]= 1; else key[11][2]= 0;
  if (ein == 164) key[11][3]= 1; else key[11][3]= 0;

  // alle Tasten
  key[19][5]= key[1][2] | key[1][3] | key[2][2] | key[2][3] | key[3][2] | key[3][3] | key [4][2] | key [4][3]    // Bewegungen + Bewegungsschrittweite
            | key[8][2] | key[8][3] | key[9][2] | key[9][3] | key[10][2] | key[10][3] | key[11][2] | key[11][3]  // Drehungen + Drehschrittweite
            | key[7][1] | key[8][1] | key[9][1] | key[10][1] | key[9][1];                                        // Zahlenreihe
  }
