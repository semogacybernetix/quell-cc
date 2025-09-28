#include <cstdio>

void diff (char* pname1, char* pname2)
  {
  FILE* d1= fopen (pname1, "rb");
  FILE* d2= fopen (pname2, "rb");
  unsigned char data1, data2;
  unsigned long dcount= 0;
  unsigned long fcount= 0;
  unsigned long first= 0;
  unsigned char a, b= 0;
  bool flag= true;
  while ((a= fread (&data1, 1, 1, d1)) & (b= fread (&data2, 1, 1, d2)))
    {
    if (data1 != data2)
      {
      dcount++;
      if (flag)
        {
        first= fcount;
        flag= false;
        }
      }
    fcount++;
    }
  if (dcount > 0)
    {
    printf ("Verglichene Stellen:             %10lu\n", fcount);
    printf ("Anzahl der Unterschiede:         %10lu\n", dcount);
    printf ("relative Uebereinstimmung:           %4.4f\n", 256 - 256*(dcount/float (fcount)));
    printf ("Stelle des ersten Unterschiedes: %10lu\n", first);
    }
    else
    {
    if (a == b)
      printf ("=\n");
    if (a < b)
      printf ("(\n");
    if (a > b)
      printf (")\n");
    }
  }

signed int main (int argc, char** argv)
  {
  if (argc != 3)
    return 0;
  diff (argv[1], argv[2]);
  return 0;
  }
