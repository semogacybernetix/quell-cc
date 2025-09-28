#include <cstdio>
#include <sys/stat.h>
#include <sys/times.h>
#include <unistd.h>
#include <cstring>

void nulle (char* pname1)
  {
  tms zeit;
  float ticksps= float (sysconf (_SC_CLK_TCK));
  struct stat filestat;
  stat (pname1, &filestat);
  unsigned long fsize= filestat.st_size;
  printf ("\n%10lu   byte", fsize);
  FILE* dio= fopen (pname1, "r+b");
  char first= 1;
  unsigned char* data= new unsigned char[1048576];
  memset (data, 0, 1048576);
  unsigned long filepos= 0;
  clock_t startpos= times (&zeit);
  unsigned long sekpos= startpos;
  unsigned long bcount= 0;
  while (bcount < fsize)
    {
    unsigned long blkgr= (fsize - bcount);
    if (blkgr > 1048576)
      blkgr= 1048576;
    fwrite (data, blkgr, 1, dio);
    bcount+= blkgr;
    if (sekpos + ticksps <= times (&zeit))
      {
      if (first)
        {
 printf ("    %8.1f sek\n\n", fsize/float(bcount));
 first= 0;
 }
      float bps= (bcount - filepos)/1048576.;
      float rzeit= (fsize - bcount)/float ((bcount - filepos));
      float pcent= bcount/float (fsize) * 100;
      float runtime= (times (&zeit) - startpos)/ticksps;
      printf ("         %3.3f MB/sek        %4.1f %%  %12.1f sek     %5.1f sek\n", bps, pcent, rzeit, runtime);
      filepos= bcount;
      sekpos+= (unsigned long) (ticksps);
      }
    }
  fclose (dio);
  printf ("\n    %8.1f sek.\n\n",(times (&zeit) - startpos)/ticksps);
  }

int main (int argc, char** argv)
  {
  if (argc != 2)
    return 0;
  nulle (argv[1]);
  return 0;
  }
