#include <cstdio>

unsigned long gzufall= 34250;

unsigned long zufall ()
  {
  gzufall= (gzufall*2349786 + 34988764) % 12498673;
  return gzufall;
  }

void trans (char* pname1, char* pname2, int pd)
  {
  FILE* din= fopen (pname1, "rb");
  FILE* dout= fopen (pname2, "wb");
  char data;
  while (fread (&data, 1, 1, din))
    {
    data+= pd*zufall ();
    fwrite (&data, 1, 1, dout);
    }
  fclose (din);
  fclose (dout);
  }

int main (int argc, char** argv)
  {
  if ((argc != 4) && (argc != 5))
    return 0;
  if (argc == 5)
    sscanf (argv[4], "%lu", &gzufall);
  if (argv[3][0] == '}')
    trans (argv[1], argv[2], 1);
  if (argv[3][0] == '{')
    trans (argv[1], argv[2], -1);
  return 0;
  }
