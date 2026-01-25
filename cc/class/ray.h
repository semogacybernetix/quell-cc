#ifndef ray_h
#define ray_h

#include "../screen/vscr.h"  // für die screen-Textur aus einem Screen (z.B. jpeg-Datei) texturieren zu können

//-------------- Schnittobjekte ------------------------------------------------------

struct clschnitt  // abstrakte Schnittklasse von der die konkreten Schnittklassen abgeleitet sind
  {
  virtual void init (const cvektor3 &pov)= 0;
  virtual void berechne (const cvektor3 &prv, cschnittpunkte &psp)= 0;
  };

struct csebene : public clschnitt
  {
  csebene ();
  void init (const cvektor3 &pov);
  void berechne (const cvektor3 &prv, cschnittpunkte &psp);

  private:
  real z;
  };

struct cszylinder : public clschnitt
  {
  cszylinder ();
  void init (const cvektor3 &pov);
  void berechne (const cvektor3 &prv, cschnittpunkte &psp);

  private:
  cvektor3 ov;
  real c;
  };

struct cskugel : public clschnitt
  {
  cskugel ();
  void init (const cvektor3 &pov);
  void berechne (const cvektor3 &prv, cschnittpunkte &psp);

  private:
  cvektor3 ov;
  real c;
  };

struct cshyper : public clschnitt
  {
  cshyper (const real &pf);
  void init (const cvektor3 &pov);
  void berechne (const cvektor3 &prv, cschnittpunkte &psp);

  private:
  real f;
  cvektor3 ov;
  real c;
  };

struct csrpara : public clschnitt
  {
  csrpara ();
  void init (const cvektor3 &pov);
  void berechne (const cvektor3 &prv, cschnittpunkte &psp);

  private:
  cvektor3 ov;
  real c;
  };

struct cshpara : public clschnitt
  {
  cshpara ();
  void init (const cvektor3 &pov);
  void berechne (const cvektor3 &prv, cschnittpunkte &psp);

  private:
  cvektor3 ov;
  real c;
  };

struct cstorus : public clschnitt
  {
  cstorus (const real pr);
  void init (const cvektor3 &pov);
  void berechne (const cvektor3 &prv, cschnittpunkte &psp);

  private:
  real r;
  cvektor3 ov;
  };

//------------------------- Parametrisierungsobjekte -------------------------------------------------------------------------------------------------

struct clpara                                                     // abstraktes Parametrisierungsobjekt, von dem die konkreten Parametrisierungsobjekte abgeleitet sind
  {
  virtual cvektor2 berechne (const cvektor3 &pv)= 0;
  };

struct cparaebenew : clpara
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparaebenepol : clpara
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparaebenepolw : clpara
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparazylinderw : clpara
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparakugel : clpara
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparakugelw : clpara
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparakugelg : clpara
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparakugels : clpara
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparakugelf : clpara
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparakugelm : clpara
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparahypere : clpara
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparahyperz : clpara
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparakegelw : clpara
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cpararpara : clpara
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparatorusu : clpara
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparatoruss : clpara
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

// ----------------------------------------------------------------------- Begrenzungsobjekte -------------------------------------------------------------------------------------------------------------------------------------------

struct clbegr     // abstraktes Begrenzungsobjekt, von dem die konkreten Begrenzungsobjekte abgeleitet sind
  {
  virtual integer sichtbar (const cvektor2 &pv)= 0;
  };

struct cbegrkeine : clbegr
  {
  integer sichtbar (const cvektor2 &pv);
  };

struct cbegrrechteck : clbegr
  {
  cbegrrechteck (const real plinks, const real prechts, const real punten, const real poben);
  integer sichtbar (const cvektor2 &pv);

  private:
  real links, rechts, oben, unten;
  };

struct cbegrkreis : clbegr
  {
  cbegrkreis (const real plinks, const real prechts, const real pinnen, const real paussen);
  integer sichtbar (const cvektor2 &pv);

  real links, rechts, innen, aussen;
  };

struct cbegrellipse : clbegr
  {
  cbegrellipse (const real pha, const real phb);
  integer sichtbar (const cvektor2 &pv);

  private:
  real ha, hb;
  };

//------------------------------- Texturen -------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct ctextur     // abstrakte Textur, von der die konkreten Texturen abgeleitet sind
  {
  ctextur ();
  virtual cvektor3 getpunkt (const cvektor2 &pv)= 0;        // Färbung eines Punktes berechnen
  cvektor3 getpixel (const cvektor2 &pv);                   // Färbung einer Pixelfläche berechnen, benutzt getpunkt, allgemein für ctextur, unabhängig vom abgeleitetem Objekt
  cvektor3 getpixel16 (const cvektor2 &pv);                 // Färbung einer Pixelfläche aus 16 Punkten berechnen
  };

struct cmonochrom : public ctextur
  {
  cmonochrom (const cvektor3 &pfarbe);
  cvektor3 getpunkt (const cvektor2 &pv);

  private:
  cvektor3 farbe;
  };

struct cschachfeld : public ctextur
  {
  cschachfeld (const cvektor3 &pfb1, const cvektor3 &pfb2, const real &pkx, const real &pky);
  cvektor3 getpunkt (const cvektor2 &pv);

  private:
  cvektor3 fb1, fb2;        // Färbung des Schachfelds
  real kx, ky;              // Skalierung des Schachfelds (Größe)
  };

struct cscreentextur : public ctextur     // Zum Texturieren mit Bildern
  {
  cscreentextur (clscreen8* pscreen, const real pkx, const real pky);
  cvektor3 getpunkt (const cvektor2 &pv);

  private:
  clscreen8* screen;
  real kx, ky, xmax, ymax;
  };

struct cscreentexturz : public ctextur     // Zum Texturieren mit Bildern zentriert
  {
  cscreentexturz (clscreen8* pscreen, const real pkx, const real pky);
  cvektor3 getpunkt (const cvektor2 &pv);

  private:
  clscreen8* screen;
  integer xmax, ymax;
  real kx, ky, xz, yz;
  };

struct cscreentexturp : public ctextur     // Zum Texturieren mit Bildern zentriert um 90° nach rechts gedreht für Polkarten
  {
  cscreentexturp (clscreen8* pscreen, const real pkx, const real pky);
  cvektor3 getpunkt (const cvektor2 &pv);

  private:
  clscreen8* screen;
  integer xmax, ymax;
  real kx, ky, xz, yz;
  };

struct cscreentextur2 : public ctextur     // Zum Texturieren mit Bildern zentriert
  {
  cscreentextur2 (clscreen8* pscreen1, const real pkx1, const real pky1, clscreen8* pscreen2, const real pkx2, const real pky2);
  cvektor3 getpunkt (const cvektor2 &pv);

  private:
  clscreen8* screen1;
  integer xmax1, ymax1;

  clscreen8* screen2;
  integer xmax2, ymax2;

  real kx1, ky1, xz1, yz1, kx2, ky2, xz2, yz2;
  };

// ------------------------------------------------------------------------------- Geometrische Gebilde -----------------------------------------------------------------------------------------------------------------------------------

struct ckoerper
  {
  ckoerper (clschnitt* pschnitt, clpara* ppara, clbegr* pbegr, ctextur* ptextur, const cvektor3 &ppos, const cbasis3 &pbasis);
  void setzeauge (const cvektor3 &paugpos, const cbasis3 &paugbasis);
  void drehe (const cbasis3 &pdrehbasis);
  void dreheein ();                                  // auf Einheitsposition setzen
  void verschiebe (const cvektor3 &pv);
  void setzepos (const cvektor3 &pv);
  void begrenze (const cvektor3 &ptransrich, const integer pnr, cschnittpunkte &psp);
  cvektor3 faerbe (const integer pnr, cschnittpunkte &psp);
  void aktualisiere ();

  // Bewegung
  real        startzeit, stopzeit;
  cvektor3    startpos, stoppos;
  cvektor3    koerperpos;

  public:
  clschnitt*  schnitt;

  private:
  clpara*     para;
  clbegr*     begr;
  ctextur*    textur;

  cbasis3     koerperbasis;
  cbasis3     drehbasis;
  cvektor3    augpos;
  cbasis3     augbasis;

  public:
  cbasis3     transbasis;

  private:
  cvektor3    transpos;
  };

struct ckoerperliste
  {
  integer          anz;
  ckoerper*        koerper[1000];

  ckoerperliste ();
  void add (ckoerper* pkoerper);
  void setzeauge (const cvektor3 &paugpos, const cbasis3 &paugbasis);
  };

struct cwelt : public ctextur
  {
  cwelt (const cvektor3 &paugpos, const cbasis3 &paugbasis);
  cwelt (const char* pname);
  cvektor3 getpunkt (const cvektor2 &pv);
  void addkoerper (ckoerper* pkoerper);

  void setzeposition (const cvektor3 &pv);
  void verschiebeauge (const cvektor3 &pv);

  void setzelage (const cbasis3 &pb);
  void dreheauge (const cbasis3 &pb);
  void dreheaugex (const real pwinkel);
  void dreheaugey (const real pwinkel);
  void dreheaugez (const real pwinkel);
  void dreheaugeachse (const real pwinkel);
  void dreheaugenorm (const real pwinkel);   // pwinkel ?
  void dreheaugeein (const real pwinkel);    // auf Einheitsposition setzen
  void aktualisiere ();

  ckoerperliste  koerperliste;
  real           abstand;                    // Abstand der Bildebene in Pixeln vom Ursprung in z-Richtung = Abstand des Betrachters vom Monitor in Pixeln
  cvektor3       augpos;
  cbasis3        augbasis;
  cvektor4       augdrehaw;
  cvektor3       himmelfarbe;
  };

// --------------------------------------------------------------------------------------------
// Bildklassen

struct cpunkt
  {
  cvektor2  pos;
  cvektor3  farbe;
  cpunkt ();
  };

struct cpunktscreen
  {
  integer xanz, yanz;

  cpunktscreen (integer px, integer py);
  ~cpunktscreen ();
  void fuelle (ctextur &ptextur);
  void plotte (clscreen8 &plscreen);

  private:
  cpunkt  *vbild;
  };

#endif
