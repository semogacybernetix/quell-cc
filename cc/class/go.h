#ifndef go_h
#define go_h

struct cgoanalyse
  {
  static const unsigned char c_leer=            0;
  static const unsigned char c_schwarz=         1;
  static const unsigned char c_weiss=           2;
  static const unsigned char c_invfarbe=        3;

  unsigned char       c_xanz, c_yanz, c_feldanz, c_satzanz;
  unsigned char*      c_feld;
  unsigned char*      c_zamsatz;
  unsigned char       c_mask;
  bool                c_gruppefrei   (unsigned char p_feldnr);
  bool                c_setze        (unsigned char p_satz);

  unsigned char    c_killgroup1, c_killgroup2, c_killgroup3, c_notset;
  unsigned long*   c_zorigin;
  unsigned long    c_anzstellungen;
  bool             c_addfeld          ();
  void             c_addstellungen    ();
  void             c_setanfangsfeld   (unsigned char p_feld);
  bool             c_setnextfeld      (unsigned long* p_baumpos, unsigned char p_feld);
  unsigned char    c_getbewertung     ();
  void             c_setbewertung     (unsigned char p_bewertung);
  unsigned char    c_bewertemin       ();
  unsigned char    c_bewertemax       ();
  bool             c_bewerteebene     (unsigned char p_bewfarbe, bool p_min);
  void             c_bewertealles     ();

  unsigned char*   c_ausgangsstellung;
  cgoanalyse       (char* p_name);
  };

#endif
