#ifndef cend_h
#define cend_h

//----------------------------- Klasse cvier ----------------------------------------------------------------------------------------

struct cend
  {
  // Daten die während einer Endspielberechnung konstant bleiben
  const signed long endmax= 2*65*65*65*65;
  const signed long bewmax= (1 << 15) - 1;
  signed long  dieder[8][65];
  signed long  gangart[5];    // bitcodiert: König, Springer, Läufer, Turm, 0 = leeres Feld
  signed long  figurnrfb[5];  // Figurnummerfarbe Betrag ist die Figurnummer, Vorzeichen die Farbe
  signed long  maxposw;
  signed long  maxposs;

  // sich während einer Berechnung ändernde Daten
  // signed long  brett[65];     // 64. Feld bedeutet das die Figur nicht auf dem Brett steht (geschlagen wurde)
  // signed long  amzug;         // 1: weiss am Zug, -1: schwarz am Zug
  // signed long  standort[5];  // Standorte der Figuren
  // signed long  hinfeld[65];   // Liste der Hinfelder (Zugmöglichkeiten einer Figur)
  // signed long  hinpos[257];   // Lister der Folgepositionen (Zugmöglichkeiten einer Stellung)

  // Endspielarray
  signed short* endspiel;

  cend ();
  ~cend ();
  void initdieder ();
  void initfiguren (signed long pfig1, signed long pfig2, signed long pfig3, signed long pfig4);
  bool setstandorte (signed long pstellungsnr, signed long* pstandort, signed long* pamzug);
  void setbrett (signed long* pstandort, signed long* pbrett);
  signed long getnumber (signed long* pstandort, signed long pamzug);
  void testefigur (signed long pfeldnr, const signed long* pbrett, signed long* phinfeld);
  void testepos (signed long pstellungsnr, signed long* phinpos);
  void bewertediederstellungen (signed long ppos);
  signed long setendpos ();
  signed long pass ();
  void analysiere ();
  void saveendspiel (const char* pname);
  void ladeendspiel (const char* pname);
  signed long ziehebesterst (signed long ppos);
  void setvisbrett (signed long ppos, signed long *pbrett);
  void setbestfelder (signed long ppos, signed long pvonfeld, signed long* pbrett);
  signed long ziehpos (signed long ppos, signed long pvonfeld, signed long phinfeld);
  void brauseendspiel (signed long ppos);
  // längste Zugfolge bei geschlagener 3. und 4. Figur (um 2-Steiner Maximalposition zu bekommen)
  void getextrempos2 ();
  // längste Zugfolge bei geschlagener 4. Figur (um 3-Steiner Maximalposition zu bekommen)
  void getextrempos3 ();
  void getextrempos ();
  void testdieder ();
  };

#endif
