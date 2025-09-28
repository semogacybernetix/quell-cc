// Partitionstabellenanalysator
//
// Dieses Programm analysiert die Daten des Bootsektors und gibt sie aus

#include <cstdio>

void analysierepartitionstabelle (char* pname)
  {
  // MBR einlesen
  unsigned char bsektor[512];
  FILE* din= fopen (pname, "rb");
  fread (bsektor, 512, 1, din);
  fclose (din);

  // MBR kopieren
  unsigned char part1[16];
  unsigned char part2[16];
  unsigned char part3[16];
  unsigned char part4[16];
  for (signed long plauf= 0; plauf < 16; plauf++)
    {
	part1[plauf]= bsektor[0x1BE + plauf];
	part2[plauf]= bsektor[0x1CE + plauf];
	part3[plauf]= bsektor[0x1DE + plauf];
	part4[plauf]= bsektor[0x1EE + plauf];
	}
  unsigned long lbastart1= part1[8] + part1[9]*0x100 + part1[10]*0x10000 + part1[11]*0x1000000;
  unsigned long lbastart2= part2[8] + part2[9]*0x100 + part2[10]*0x10000 + part2[11]*0x1000000;
  unsigned long lbastart3= part3[8] + part3[9]*0x100 + part3[10]*0x10000 + part3[11]*0x1000000;
  unsigned long lbastart4= part4[8] + part4[9]*0x100 + part4[10]*0x10000 + part4[11]*0x1000000;
  unsigned long lbaanz1= part1[12] + part1[13]*0x100 + part1[14]*0x10000 + part1[15]*0x1000000;
  unsigned long lbaanz2= part2[12] + part2[13]*0x100 + part2[14]*0x10000 + part2[15]*0x1000000;
  unsigned long lbaanz3= part3[12] + part3[13]*0x100 + part3[14]*0x10000 + part3[15]*0x1000000;
  unsigned long lbaanz4= part4[12] + part4[13]*0x100 + part4[14]*0x10000 + part4[15]*0x1000000;
  unsigned long lbaend1= lbastart1 + lbaanz1;
  unsigned long lbaend2= lbastart2 + lbaanz2;
  unsigned long lbaend3= lbastart3 + lbaanz3;
  unsigned long lbaend4= lbastart4 + lbaanz4;
  unsigned long mbanz1= lbaanz1/2048;
  unsigned long mbanz2= lbaanz2/2048;
  unsigned long mbanz3= lbaanz3/2048;
  unsigned long mbanz4= lbaanz4/2048;
  unsigned long gbanz1= lbaanz1/2097152;
  unsigned long gbanz2= lbaanz2/2097152;
  unsigned long gbanz3= lbaanz3/2097152;
  unsigned long gbanz4= lbaanz4/2097152;
  unsigned long hstart1= part1[1];
  unsigned long hstart2= part2[1];
  unsigned long hstart3= part3[1];
  unsigned long hstart4= part4[1];
  unsigned long hend1= part1[5];
  unsigned long hend2= part2[5];
  unsigned long hend3= part3[5];
  unsigned long hend4= part4[5];
  unsigned long sstart1= part1[2] & 63;
  unsigned long sstart2= part2[2] & 63;
  unsigned long sstart3= part3[2] & 63;
  unsigned long sstart4= part4[2] & 63;
  unsigned long send1= part1[6] & 63;
  unsigned long send2= part2[6] & 63;
  unsigned long send3= part3[6] & 63;
  unsigned long send4= part4[6] & 63;
  unsigned long cstart1= part1[3] + 256 * (part1[2] >> 6);
  unsigned long cstart2= part2[3] + 256 * (part2[2] >> 6);
  unsigned long cstart3= part3[3] + 256 * (part3[2] >> 6);
  unsigned long cstart4= part4[3] + 256 * (part4[2] >> 6);
  unsigned long cend1= part1[7] + 256 * (part1[6] >> 6);
  unsigned long cend2= part2[7] + 256 * (part2[6] >> 6);
  unsigned long cend3= part3[7] + 256 * (part3[6] >> 6);
  unsigned long cend4= part4[7] + 256 * (part4[6] >> 6);
  unsigned long signatur= bsektor[510]*256 + bsektor[511];
  
  
  // Parttionstabelle ausgeben
  printf ("\n");
  printf ("Nr Typ Boot    CHS-Start        CHS-End          LBA-Start  LBA-Nächs     MB   GB\n");
  printf ("1   %2x   %2x   %5ld-%3ld-%2ld     %5ld-%3ld-%2ld     %10ld %10ld  %5ld%5ld\n",
                    part1[4],      part1[0], cstart1, hstart1, sstart1, cend1, hend1, send1, lbastart1, lbaend1, mbanz1, gbanz1);
  printf ("2   %2x   %2x   %5ld-%3ld-%2ld     %5ld-%3ld-%2ld     %10ld %10ld  %5ld%5ld\n",
                    part2[4],      part2[0], cstart2, hstart2, sstart2, cend2, hend2, send2, lbastart2, lbaend2, mbanz2, gbanz2);
  printf ("3   %2x   %2x   %5ld-%3ld-%2ld     %5ld-%3ld-%2ld     %10ld %10ld  %5ld%5ld\n",
                    part3[4],      part3[0], cstart3, hstart3, sstart3, cend3, hend3, send3, lbastart3, lbaend3, mbanz3, gbanz3);
  printf ("4   %2x   %2x   %5ld-%3ld-%2ld     %5ld-%3ld-%2ld     %10ld %10ld  %5ld%5ld\n",
                    part4[4],      part4[0], cstart4, hstart4, sstart4, cend4, hend4, send4, lbastart4, lbaend4, mbanz4, gbanz4);
  printf ("\n");
  printf ("Signatur[8-8]: %10lx\n", signatur);
  printf ("\n");
  printf ("Bootcode: \n");
  for (signed long plauf= 0; plauf < 0x1be; plauf++)
    {
	printf ("%3x", bsektor[plauf]);
	if ((plauf & 15) == 15)
	  printf ("\n");
	}
  printf ("\n");
  printf ("\n");
  }

int main (int argc, char** argv)
  {
  if (argc != 2)
    return 0;
  analysierepartitionstabelle (argv[1]);
  return 0;
  }
