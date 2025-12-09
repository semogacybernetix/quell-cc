#ifndef gruppe_h
#define gruppe_h

#include "vektor.h"

struct cbasis3liste
  {
  integer uebergelaufen;
  integer maxanz;                   // Anzahl von Elementen, bei denen die Liste voll ist
  integer anz;                      // Anzahl der Elemente der Liste

  cbasis3* b;

  integer* ord;                     // Ordnung eines Elements (Anzahl der Potenzen des Elements)
  integer maxord;                   // Ordnung des Elements mit der höchsten Ordnung
  real* winkel;                     // Winkel der Drehung oder Drehinversion
  real miniwinkel;                  // Winkel der Drehspiegelung mit dem kleinsten Winkel (Winkel Inversion (-1 ∈ ℝ³) = 0)
  integer* ordanz;                  // Anzahl der Elemente einer Ordnung
  integer* zykel;
  integer* gepaart;                 // Nummer des negativen Element des Vektors. -1 wenn kein negatives Element vorhanden ist

  cbasis3liste (integer pmaxanz);                  // constructor
  void kopiere (cbasis3liste& pbasis3liste);
  integer elposition (cbasis3 pb);
  void elementhinzu (cbasis3 pb);
  void winkelachsehinzu (cvektor4 pq);
  void winkelachsespieghinzu (cvektor4 pq);
  void laufedurch ();
  void schliesseab ();
  integer ermittleelementordnung (integer pel);
  void ermittleordnung ();                         // Ordnungen der Elemente ermitteln und Anzahlen der jeweiligen Ordnungen ermitteln, maximale Ordnung ermitteln
  void sortiereordnungab (integer pstart, integer pstop);
  void sortieredeterminanteab (integer pstart, integer pstop);
  void erstellezykel ();
  void sortierenachordnung ();
  void ermittlepaarung ();                         // Paarungen und Winkel ermitteln
};

struct cvektor3liste
  {
  integer uebergelaufen;
  integer maxanz;
  integer anz;
  cvektor3* v;
  integer* ord;

  cvektor3liste (integer pmaxanz);
  integer elposition (cvektor3 pv);
  void elementhinzu (cvektor3 pv, integer pord);
  void laufedurch (cbasis3liste& pbliste);
  void schliesseab (cbasis3liste& pbliste);
  };

struct cvektor4liste
  {
  integer uebergelaufen;
  integer maxanz;
  integer anz;
  cvektor4* v;       // Zeiger auf einen Vektor der Liste
  integer* ord;      // Zeiger auf die Ordnung des Vektors
  integer* ordanz;   // Anzahl der Elemente zu einer Ordnung
  integer* zykel;
  integer* gepaart;  // Flag, ob Komplement des Drehquaternions auch in der Liste ist

  cvektor4liste (integer pmaxanz);
  integer elposition (cvektor4 pq);
  void elementhinzu (cvektor4 pq);
  void winkelachsehinzu (cvektor4 pq);
  void laufedurch ();
  void schliesseab ();
  void ermittleordnung ();
  void sortierenachordnung ();
  void ermittlepaarung ();
  };

struct ccluster
  {
  cbasis3liste*    gruppe;
  cbasis3liste*    kern;
  cvektor3liste*   partliste;

  cvektor3liste*   eliste;
  cvektor3liste*   fliste;
  cvektor3liste*   kliste;

  integer ebas, fbas, kbas;

  cbasis3liste*    spieg;
  cbasis3liste*    spiegkoord;
  
  ccluster (const integer pmaxanz);
  void vervollstaendige ();
  cvektor3 ermittleefkdreibein (cvektor3 pvektor, real praum);    // zu einem Vektor die nahsten EFK-Vektoren welche die angegebene Orientierung ({-1, 1}) haben zurückgeben
  void erstelleobjdatei (cvektor3 pefkvektor);
  };

//------------------------ Gruppenfunktionen ---------------------------------------------------------------------------------

cbasis3 drehachsenvonspiegelungen (const cbasis3& pb);
void drehungenvonspiegelungen (cbasis3liste& pliste, const cbasis3& pb);
void spiegelungenvondrehungen (cbasis3liste& pliste, const cvektor4 pd1, const cvektor4 pd2);
cbasis3 spiegelachsenvonebenenwinkele (const cvektor3 wi);   // 3 Winkel zwischen 3 Ebenen in 3 Spiegelachsen umrechnen Rausdrehung aus der gemeinsamen Ebene
cbasis3 spiegelachsenvonebenenwinkeld (const cvektor3 wi);   // 3 Winkel zwischen 3 Ebenen in 3 Spiegelachsen umrechnen  Innenwinkel eines Kugeldreiecks
cbasis3 spiegelachsenvonebenenwinkel2 (const cvektor3 wi);  // 3 Winkel zwischen 3 Ebenen in 3 Spiegelachsen umrechnen
cbasis3 spiegelachsenvonebenenwinkel3 (const cvektor3 wi);  // 3 Winkel zwischen 3 Ebenen in 3 Spiegelachsen umrechnen
cbasis3 spiegelachsenvonebenenwinkelk (const cvektor3 wi);  // 3 Winkel zwischen 3 Ebenen in 3 Spiegelachsen umrechnen
cbasis3 getsternbasis (const real pwi);                     // 3 Achsen spannen ein Dreibein im ppp-Quadranten auf. pwi: Winkel zwischen den Achsen [0° - 120°]
cbasis3 getsternbasis2 (const real pwi);                    // 3 Achsen spannen ein Dreibein im ppp-Quadranten auf. pwi: Winkel zwischen den Achsen [0° - 120°]
void ermittlepartvektoren (cbasis3liste& pgruppe, cvektor3liste& pordliste);           // Vektorgruppe in Ordnungsvektoren partitionieren
void bildekern (const cbasis3liste& pgruppe, cbasis3liste& pkern);                     // alle Matrizen mit positiver Determinante nach pkern kopieren
void bildespieg (const cbasis3liste& pgruppe, cbasis3liste& pspieg);
#endif
