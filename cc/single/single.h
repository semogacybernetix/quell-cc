#ifndef single_h
#define single_h

#include "../class/vektor.h"

bool littleendian ();
signed long zufall ();
void wavheader44 (unsigned char* pheader, unsigned long plaenge);
void calccrc (unsigned long& pchecksum, unsigned char* pblock, unsigned long plaenge);
long double rgbtoy (long double irot, long double igrn, long double iblu);
void rgbtohsy (long double irot, long double igrn, long double iblu, long double& ohue, long double& osat, long double& ohell);
void hsytorgb (long double ihue, long double isat, long double ihell, long double& orot, long double& ogrn, long double& oblu);
// Die Sättigung wird anders berechnet: 0 bis 1
void rgbtoabc (long double irot, long double igrn, long double iblu, long double& ohel, long double& osat, long double& ofar);
void abctorgb (long double ihel, long double isat, long double ifar, long double& orot, long double& ogrn, long double& oblu);

#endif
