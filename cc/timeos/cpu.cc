#include <cstdio>

unsigned long zyklus= 0;

unsigned long lesezelle (FILE* pdatei, unsigned long ppos)
  {
  unsigned char c0, c1, c2, c3;
  fseek (pdatei, ppos << 2, 0);
  fread (&c3, 1, 1, pdatei);
  fread (&c2, 1, 1, pdatei);
  fread (&c1, 1, 1, pdatei);
  fread (&c0, 1, 1, pdatei);
  return (c3 << 24) | (c2 << 16) | (c1 << 8) | c0;
  }

void schreibezelle (FILE* pdatei, unsigned long ppos, unsigned long pdata)
  {
  fseek (pdatei, ppos << 2, 0);
  unsigned char data;
  data= pdata >> 24;
  fwrite (&data, 1, 1, pdatei);
  data= (pdata >> 16) & 0xff;
  fwrite (&data, 1, 1, pdatei);
  data= (pdata >> 8) & 0xff;
  fwrite (&data, 1, 1, pdatei);
  data= pdata & 0xff;
  fwrite (&data, 1, 1, pdatei);
  }

int fuehreaus (const char* pname)
  {
  unsigned long pc, befehl, opaddr1, opaddr2, op1, op2, erg= 0;
  FILE* datei= fopen (pname, "r+b");
  if (!(pc= lesezelle (datei, 0)))
    {
    fclose (datei);
    return 0;
    }
  schreibezelle (datei, 0, pc + 3);
  befehl= lesezelle (datei, pc);
  opaddr1= lesezelle (datei, pc + 1);
  opaddr2= lesezelle (datei, pc + 2);
  op1= lesezelle (datei, opaddr1);
  op2= lesezelle (datei, opaddr2);
  switch (befehl)
    {
    case 0:
      erg= op2;
      printf ("Zyklus: %10lu Addresse: %5lu :  copy %5lu: %5ld %5lu: %5ld\n", zyklus, pc, opaddr1, op1, opaddr2, op2);
      break;
    case 1:
      erg= op1 - op2;
      printf ("Zyklus: %10lu Addresse: %5lu :  sub  %5lu: %5ld %5lu: %5ld\n", zyklus, pc, opaddr1, op1, opaddr2, op2);
      break;
    case 2:
      if (op2)
          erg= op1;
        else
          erg= 0;
      printf ("Zyklus: %10lu Addresse: %5lu :  cond %5lu: %5ld %5lu: %5ld\n", zyklus, pc, opaddr1, op1, opaddr2, op2);
      break;
    default:
      erg= op1;
      printf ("Zyklus: %10lu Addresse: %5lu : %5lu %5lu: %5ld %5lu: %5ld\n", zyklus, pc, befehl, opaddr1, op1, opaddr2, op2);
      break;
    }
  schreibezelle (datei, opaddr1, erg);
  fclose (datei);
  zyklus++;
  return 1;
  }

int main ()
  {
  while (fuehreaus ("ram.cpu"));
  return 0;
  }
