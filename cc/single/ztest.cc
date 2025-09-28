#include <cstdio>

float chi (char* pname)
  {
  FILE* din= fopen (pname, "rb");
  unsigned char data;
  signed long long v[256]= {0};
  signed long long anz= 0;
  signed long long sum= 0;
  signed long long t= 0;

  while (fread (&data, 1, 1, din))
    {
    v[data]++;
    anz++;
    }
  fclose (din);

  for (signed long long n= 0; n < 256; n++)
    {
    printf ("%3llu:%16llu       ", n, v[n]);
    if (!((n + 1)%8))
      printf ("\n");
    sum+= n*v[n];
    t+= v[n]*v[n];
    }
  printf ("\nAnzahl der Werte: %5lld\n", anz);
  printf ("Durchschnitt:     %5.5Lf\n", (long double) (sum)/anz);
  printf ("Chi-q:            %5.5Lf\n", (long double) (256*t)/anz - anz);
  printf("\n");
  return 0;
  }

int main (int argc, char** argv)
  {
  if (argc != 2)
    {
    printf ("zuf <Zufallsdatei>\n");
    return 0;
    }
  chi (argv[1]);
  return 0;
  }
