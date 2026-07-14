#ifndef ray_h
#define ray_h

#include "../screen/vscr.h"  // für die screen-Textur, um aus einem Screen (z.B. jpeg-Datei) texturieren zu können

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

struct csebzyl : public clschnitt
  {
  csebzyl ();
  void init (const cvektor3 &pov);
  void berechne (const cvektor3 &prv, cschnittpunkte &psp);

  private:
  cvektor3 ov;
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

struct clpara                                               // abstraktes Parametrisierungsobjekt, von dem die konkreten Parametrisierungsobjekte abgeleitet sind
  {
  virtual cvektor2 berechne (const cvektor3 &pv)= 0;
  };

//------------------------- 3D-Ebenenfläche -> (u,v)-Parametrisierung --------------------------------------------------------------------------------------------------------------------
struct cparaebenew : clpara                                 // Ebene winkeltreu parametrisieren (triviale Parametrisierung)
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparaebenepol : clpara                               // Ebene in Polarkoordinaten parametrisieren
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparaebenepolw : clpara                              // Ebene in Polarkoordinaten winkeltreu parametrisieren
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

//------------------------- Projektionen -----------------------------------------------------------------------------------------------------------------------------------------------
struct clprojektion : clpara                                // abstrakte Projektion: fehlerhaft, zur Laufzeit sehr langsam
  {
  clpara* parakugel;
  cbasis3 az;

  void setzeaz (real l, real b);
  };

//------------------------- 3D-Ebenenfläche (pv.z = 0) als Kartenprojektion -> 3D-Kugelfläche -> (u,v)-Parametrisierung entsprechend der übergebenen Kugelparametrisierung (Kartenprojektion)
struct cparaebene_platt_kugel : clpara                      // 3D-Plattkarte -> 3D-Kugel parametrisieren
  {
  clpara* parakugel;
  cbasis3 az;

  cparaebene_platt_kugel (clpara* pkugel, real pl, real pb, real pr);
  void setzeaz (real pl, real pb, real pr);
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparaebene_mercator_kugel : clpara                   // 3D-Ebene als Mercatorkarte in 3D-Kugel umrechnen und diese dann entsprechend der übergebenen Kugelparametrisierung (u,v)-parametrisieren
  {
  clpara* parakugel;
  cbasis3 az;

  cparaebene_mercator_kugel (clpara* pkugel, real pl, real pb, real pr);
  void setzeaz (real pl, real pb, real pr);
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparaebene_zylortho_kugel : clpara                   // 3D-Ebene als flächentreue Zylinderkarte in 3D-Kugel umrechnen und diese dann entsprechend der übergebenen Kugelparametrisierung (u,v)-parametrisieren
  {
  clpara* parakugel;
  cbasis3 az;

  cparaebene_zylortho_kugel (clpara* pkugel, real pl, real pb, real pr);
  void setzeaz (real pl, real pb, real pr);
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparaebene_gnom_kugel : clpara                       // 3D-Ebene als gnomonische Projektion in 3D-Kugel umrechnen und diese dann entsprechend der übergebenen Kugelparametrisierung (u,v)-parametrisieren
  {
  clpara* parakugel;
  cbasis3 az;

  cparaebene_gnom_kugel (clpara* pkugel, real pl, real pb);
  void setzeaz (real pl, real pb);
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparaebene_stereo_kugel : clpara                     // 3D-Ebene als stereografische Projektion in 3D-Kugel umrechnen und diese dann entsprechend der übergebenen Kugelparametrisierung (u,v)-parametrisieren
  {
  clpara* parakugel;
  cbasis3 az;

  cparaebene_stereo_kugel (clpara* pkugel, real pl, real pb);
  void setzeaz (real pl, real pb);
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparaebene_mitten_kugel : clpara                     // 3D-Ebene als mittenabstandstreue Projektion in 3D-Kugel umrechnen und diese dann entsprechend der übergebenen Kugelparametrisierung (u,v)-parametrisieren
  {
  clpara* parakugel;
  cbasis3 az;

  cparaebene_mitten_kugel (clpara* pkugel, real pl, real pb);
  void setzeaz (real pl, real pb);
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparaebene_lamb_kugel : clpara                     // 3D-Ebene als flächentreue Projektion in 3D-Kugel umrechnen und diese dann entsprechend der übergebenen Kugelparametrisierung (u,v)-parametrisieren
  {
  clpara* parakugel;
  cbasis3 az;

  cparaebene_lamb_kugel (clpara* pkugel, real pl, real pb);
  void setzeaz (real pl, real pb);
  cvektor2 berechne (const cvektor3 &pv);
  };

//------------------------- 3D-Zylinderfläche -> (u,v)-Parametrisierung -----------------------------------------------------------------------------------------------------------------
struct cparazylinderw : clpara
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

//------------------------- 3D-Kugelfläche -> (u,v)-Parametrisierung -----------------------------------------------------------------------------------------------------------------
struct cparakugel_platt_z : clpara                          // Kugel über pv.z in Plattkarte (u,v)-parametrisieren
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparakugel_platt_xyz : clpara                        // Kugel über pv.x, pv.y, pv.z in Plattkarte (u,v)-parametrisieren (numerisch stabiler)
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparakugel_mercator_z : clpara                       // Kugel über pv.z in Mercatorkarte (u,v)-parametrisieren
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparakugel_mercator_xyz : clpara                     // Kugel über pv.x, pv.y, pv.z in Mercatorkarte (u,v)-parametrisieren (numerisch stabiler)
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparakugel_zylortho_z : clpara                       // Kugel über pv.z in flächentreue Zylinderkarte (u,v)-parametrisieren
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparakugel_gnom : clpara                             // Kugel über pv.z in gnomonische Azimutalprojektion (u,v)-parametrisieren
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparakugel_stereo_z : clpara                         // Kugel über pv.z in stereografische Azimutalprojektion (u,v)-parametrisieren
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparakugel_stereo_xyz : clpara                       // Kugel über pv.x, pv.y, pv.z in stereografische Azimutalprojektion (u,v)-parametrisieren (numerisch stabiler)
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparakugel_lamb_z : clpara                           // Kugel über pv.z in flächentreue Azimutalprojektion (u,v)-parametrisieren
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparakugel_lamb_xyz : clpara                         // Kugel über pv.x, pv.y, pv.z in flächentreue Azimutalprojektion (u,v)-parametrisieren (numerisch stabiler)
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparakugel_mitten_z : clpara                         // Kugel über pv.z in mittenabstandstreue Azimutalprojektion (u,v)-parametrisieren
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparakugel_mitten_xyz : clpara                       // Kugel über pv.x, pv.y, pv.z in mittenabstandstreue Azimutalprojektion (u,v)-parametrisieren (numerisch stabiler)
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

//------------------------- Hyperboloid --------------------------------------------------------------------------------------------------------------------
struct cparahypere : clpara
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparahyperz : clpara
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

//------------------------- Kegel --------------------------------------------------------------------------------------------------------------------------
struct cparakegelw : clpara
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

//------------------------- Rotationsparaboloid ------------------------------------------------------------------------------------------------------------
struct cpararpara : clpara
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

//------------------------- Torus --------------------------------------------------------------------------------------------------------------------------
struct cparatorusu : clpara
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparatoruss : clpara
  {
  cvektor2 berechne (const cvektor3 &pv);
  };

struct cparatorusrl : clpara
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

struct cltextur     // abstrakte Textur, von der die konkreten Texturen abgeleitet sind
  {
  cltextur ();
  virtual cvektor3 getpunkt (const cvektor2 &pv)= 0;        // Färbung eines Punktes berechnen
  cvektor3 getpixel (const cvektor2 &pv);                   // Färbung einer Pixelfläche berechnen, benutzt getpunkt, allgemein für cltextur, unabhängig vom abgeleitetem Objekt
  cvektor3 getpixel16 (const cvektor2 &pv);                 // Färbung einer Pixelfläche aus 16 Punkten berechnen
  };

struct ctexmonochrom : public cltextur
  {
  ctexmonochrom (const cvektor3 &pfarbe);
  cvektor3 getpunkt (const cvektor2 &pv);

  private:
  cvektor3 farbe;
  };

struct cschachfeld : public cltextur
  {
  cschachfeld (const cvektor3 &pfb1, const cvektor3 &pfb2, const real &pkx, const real &pky);
  cvektor3 getpunkt (const cvektor2 &pv);

  private:
  cvektor3 fb1, fb2;        // Färbung des Schachfelds
  real kx, ky;              // Skalierung des Schachfelds (Größe)
  };

struct cschachfeldf : public cltextur
  {
  cschachfeldf (const cvektor3 &pfb1, const cvektor3 &pfb2, const real &pkx, const real &pky);
  cvektor3 getpunkt (const cvektor2 &pv);

  private:
  cvektor3 fb1, fb2;        // Färbung des Schachfelds
  real kx, ky;              // Skalierung des Schachfelds (Größe)
  };

struct cscreentextur : public cltextur     // Zum Texturieren mit Bildern
  {
  cscreentextur (clscreen8* pscreen, const real pkx, const real pky);
  cvektor3 getpunkt (const cvektor2 &pv);

  private:
  clscreen8* screen;
  real kx, ky, xmax, ymax;
  };

struct cscreentexturz : public cltextur     // Zum Texturieren mit Bildern zentriert
  {
  cscreentexturz (clscreen8* pscreen, const real pkx, const real pky);
  cvektor3 getpunkt (const cvektor2 &pv);

  private:
  clscreen8* screen;
  integer xmax, ymax;
  real kx, ky, xz, yz;
  };

struct cscreentexturp : public cltextur     // Zum Texturieren mit Bildern zentriert um 90° nach rechts gedreht für Polkarten
  {
  cscreentexturp (clscreen8* pscreen, const real pkx, const real pky);
  cvektor3 getpunkt (const cvektor2 &pv);

  private:
  clscreen8* screen;
  integer xmax, ymax;
  real kx, ky, xz, yz;
  };

struct cscreentextur2pm : public cltextur     // Zum Texturieren mit Bildern zentriert
  {
  cscreentextur2pm (clscreen8* pscreen1, const real pkx1, const real pky1, clscreen8* pscreen2, const real pkx2, const real pky2);
  cvektor3 getpunkt (const cvektor2 &pv);

  private:
  clscreen8* screen1;
  integer xmax1, ymax1;

  clscreen8* screen2;
  integer xmax2, ymax2;

  real kx1, ky1, xz1, yz1, kx2, ky2, xz2, yz2;
  };

struct cscreentextur2zm : public cltextur     // Zum Texturieren mit Bildern zentriert
  {
  cscreentextur2zm (clscreen8* pscreen1, const real pkx1, const real pky1, clscreen8* pscreen2, const real pkx2, const real pky2);
  cvektor3 getpunkt (const cvektor2 &pv);

  private:
  clscreen8* screen1;
  integer xmax1, ymax1;

  clscreen8* screen2;
  integer xmax2, ymax2;

  real kx1, ky1, xz1, yz1, kx2, ky2, xz2, yz2;
  };

struct cscreentextur2zs : public cltextur     // Zum Texturieren mit Bildern zentriert
  {
  cscreentextur2zs (clscreen8* pscreen1, const real pkx1, const real pky1, clscreen8* pscreen2, const real pkx2, const real pky2);
  cvektor3 getpunkt (const cvektor2 &pv);

  private:
  clscreen8* screen1;
  integer xmax1, ymax1;

  clscreen8* screen2;
  integer xmax2, ymax2;

  real kx1, ky1, xz1, yz1, kx2, ky2, xz2, yz2;
  };

// ------------------------------------------------------------------------------- Geometrische Gebilde -----------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------- Körper ---------------------------------------------------------------------------------------------------------------

struct ckoerper
  {
  ckoerper (clschnitt* pschnitt, clpara* ppara, clbegr* pbegr, cltextur* ptextur, const cvektor3 &ppos, const cbasis3 &pbasis);
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
  cltextur*   textur;

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

struct cwelt : public cltextur
  {
  cwelt (const cvektor3 &paugpos, const cbasis3 &paugbasis);
  cwelt (const char* pname);
  cvektor3 getpunkt (const cvektor2 &pv);
  void addkoerper (ckoerper* pkoerper);

  void setzeposition (const cvektor3 &pv);    // Position des Auges setzen
  void verschiebeauge (const cvektor3 &pv);

  void setzelage (const cbasis3 &pb);
  void dreheauge (const cbasis3 &pb);
  void dreheaugex (const real pwinkel);
  void dreheaugey (const real pwinkel);
  void dreheaugez (const real pwinkel);
  void spiegeleaugex ();
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
  void fuelle (cltextur &ptextur);
  void plotte (clscreen8 &plscreen);

  private:
  cpunkt  *vbild;
  };

#endif
