#ifndef vektorcon_h
#define vektorcon_h

#include "../cc/class/vektor.h"

struct zahl1010
  {
  real wert;                 // Wert der Zahl
  integer zf[20];            // Dezimalstellen  zf[0]= 10^9  zf[9]= 10^0 zf[19]= 10^-10
  integer vz;                // Vorzeichen  1, -1
  integer est;               // Position der ersten von 0 verschiedene Dezimalstelle

  zahl1010 ();
  void erstelle (real pwert);
  void print (char* pstring, integer pst);
  void print (char* pstring, integer vst, integer pst);
  void printobj (const char* pdateiname, integer pst);
  void printobj (const char* pdateiname, integer vst, integer pst);
  };

//------------------------ cvektor0 ------------------------------------------------------------------
void eingabe ();

void printtext (const char* ptext);
void printtextobj (const char* pdateiname, const char* ptext);

//------------------------ cvektor1 ------------------------------------------------------------------
void realeingabe (_Float32& pv);
void realeingabe (_Float64& pv);
void realeingabe (_Float80& pv);

void printinteger (integer pn);

void printreal (_Float32 pr);
void printreal (_Float64 pr);
void printreal (_Float80 pr);

void printrealobj (const char* pdateiname, _Float32 pr);
void printrealobj (const char* pdateiname, _Float64 pr);
void printrealobj (const char* pdateiname, _Float80 pr);

void printzahlobj (const char* pdateiname, real pr, integer pst);
void printzahlobj (const char* pdateiname, integer pi, integer pst);
void printzahlobj (const char* pdateiname, real pr, integer vst, integer pst);
void printzahlobj (const char* pdateiname, integer pi, integer vst, integer pst);

//------------------------ cvektor2 ------------------------------------------------------------------
void vektor2eingabek (cvektor2& pp);
void vektor2eingabep (ckomplexp& pp);

void printvektor2komplex (const char* pstring, ckomplexk pv, integer psw);
void printvektor2komplexp (const char* pstring, ckomplexp pv);

//------------------------ cvektor3 ------------------------------------------------------------------
void vektor3eingabe (cvektor3& pv);

void printvektor3obj (const char* pdateiname, cvektor3 pv);
void printvektor3perfobj (const char* pdateiname, cvektor3 pv, integer pst);
void printvektor3perfobj (const char* pdateiname, cvektor3 pv, integer vst, integer pst);
void printvektor3blenderobj (const char* pdateiname, cvektor3 pv, integer pst);
void printvektor3infobj (const char* pdateiname, cvektor3 pv);
void printvektor3ord (cvektor3 pv, integer pord);
void printvektor3wi (cvektor3 pv, real wi);
void printbasis3mat (cbasis3 pb, integer pord, integer pzykel);
void printbasis3dreh (cbasis3 pb, integer pord, integer pzykel, integer ppaar);

//------------------------ cvektor4 ------------------------------------------------------------------
void quaternioneneingabe (cvektor4& pv);
cvektor4 winkelachseeingabe ();
cvektor4 winkelachseeingaberoh ();

void printvektor4quat (cvektor4 pv, integer pord, integer pzykel);
void printvektor4dreh (cvektor4 pv, integer pord, integer pzykel, integer ppaar);
void printvektor4drehobj (const char* pdateiname, cvektor4 pv);

#endif
