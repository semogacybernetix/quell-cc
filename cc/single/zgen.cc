#include <cstdio>

unsigned char data[32]= {29,87,191,237,200,8,74,82,196,183,78,79,41,122,173,109,240,34,63,108,180,173,156,176,53,30,37,8,49,240,159,255};
unsigned char op1= 0;
unsigned char op2= 19;
unsigned char op3= 31;

char zufall ()
  {
  op1= ++op1 & 31;
  op2= ++op2 & 31;
  op3= ++op3 & 31;
  return data[op3]= data[op1] + data[op2];
  }

void zdatei (char* pname, unsigned long panz)
  {
  FILE* dout= fopen (pname, "wb");
  for (unsigned long bcount= 0; bcount < panz; bcount++)
    {
    unsigned char z= zufall ();
    fwrite (&z, 1, 1, dout);
    }
  fclose (dout);
  }

int main (int argc, char** argv)
  {
  if (argc != 3)
    return 0;
  unsigned long anz;
  sscanf (argv[2], "%lu", &anz);
  zdatei (argv[1], anz);
  return 0;
  }
