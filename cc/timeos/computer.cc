#include <sys/times.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>

struct ccomputer
  {
  unsigned long m_ram[4194304];
  unsigned long long m_zyklus;
  tms zeit;
  unsigned long ticksps;
  unsigned long long speed;
  unsigned long ticks;

  ccomputer (char* p_name);
  bool run ();
  };

ccomputer::ccomputer (char* p_name)
  {
  FILE* datei= fopen (p_name,"rb");
  unsigned long rampos= 0;
  unsigned char c3;
  while (fread (&c3, 1, 1, datei))
    {
    unsigned char c0, c1, c2;
    fread (&c2, 1, 1, datei);
    fread (&c1, 1, 1, datei);
    fread (&c0, 1, 1, datei);
    m_ram[rampos]= (c3 << 24) | (c2 << 16) | (c1 << 8) | c0;
    rampos++;
    }
  fclose (datei);
  m_zyklus= 0;
  ticksps= sysconf (_SC_CLK_TCK);
  printf ("\nTicks / Sekunde: %lu\n\n", ticksps);
  speed= 10000;
  ticks= times (&zeit);
  }

bool ccomputer::run ()
  {
  while ((unsigned) times (&zeit) == ticks);
  ticks= times (&zeit);
  for (unsigned long long zanz= 0; zanz < speed; zanz++)
  {
  unsigned long pc, befehl, opaddr1, opaddr2, op1, op2, erg;
  pc= m_ram[0];
  if (pc == 0)
    return false;
  m_ram[0]= pc + 3;
  befehl= m_ram[pc];
  opaddr1= m_ram[pc + 1];
  opaddr2= m_ram[pc + 2];
  op1= m_ram[opaddr1];
  op2= m_ram[opaddr2];
  switch (befehl)
    {
    case 0:
      erg= op2;
      break;
    case 1:
      erg= op1 - op2;
      break;
    case 2:
      if (op2)
          erg= op1;
        else
          erg= 0;
      break;
    default:
      erg= op1;
      break;
    }
  m_ram[opaddr1]= erg;
  m_zyklus++;
//  printf ("Zyklus: %10llu Addresse: %5lu :  %5lu %5lu: %5ld %5lu: %5ld\n", m_zyklus, pc, befehl, opaddr1, op1, opaddr2, op2);
  }
  unsigned long gegzeit= times (&zeit);
  if (gegzeit > ticks)
    {
    ticks= gegzeit;
    printf ("Zeitfehler\n");
    exit (0);
    return true;
    }
  printf ("%10llu\n", m_zyklus);
  return true;
  }

int main ()
  {
  ccomputer computer ("ram");
  while (computer.run ());
  printf ("%10llu\n", computer.m_zyklus);
  return 0;
  }
