#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <strings.h>
#include <sys/times.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;        //damit man nicht std::cout schreiben muss

void sendflood (char* pipaddr, unsigned long pfsize, unsigned long ppsize)
  {
  int skflood= socket (AF_INET, SOCK_DGRAM, 0);
  if (skflood < 0)
    {
    cout << "Socket konnte nicht angelegt werden" << endl;
    exit (0);
    }
  cout << "Socket: " << skflood << endl;
  sockaddr_in addrflood;
  bzero (&addrflood, sizeof (addrflood));
  addrflood.sin_family= htons (AF_INET);
  addrflood.sin_port= htons (6001);
  if (!inet_aton (pipaddr, &addrflood.sin_addr))                                   
    {
    cout << "fehlerhafte IP-Adresse" << endl;
    exit (0);
    }
  cout << "IP: " << inet_ntoa (addrflood.sin_addr) << endl;
  int conn= connect (skflood, (sockaddr*) &addrflood, sizeof (addrflood));
  if (conn != 0)
    {
    cout << "connect fehlgeschlagen" << endl;
    exit (0);
    }
  signed long udpdata[65536];
  tms zeit;
  unsigned long ticksps= sysconf (_SC_CLK_TCK);
  cout << "Ticks: " << ticksps << endl;
  long int frame= times (&zeit) + 120;
  frame = frame/100*100;
  while (1)
    {
    while (times (&zeit) < frame);
    //cout << frame << endl;
    udpdata[0]= htonl (unsigned (frame));
    if (write (skflood, udpdata, ppsize) < 0)
      {
      cout << "Fehler bei write" << endl;
      }
    frame+= pfsize;
    if (times (&zeit) >= frame)
      {
      cout << "Frameerror " << 1 + times (&zeit) - frame << endl;
      frame= times (&zeit) + 1;
      }
    }
  }

int main (int argc, char** argv)
  {
  if (argc != 4)
    {
    cout << "floodsen <IP-Adresse> <framesize> <packetsize>" << endl;
    exit (0);
    }
  unsigned long fsize, psize;
  sscanf (argv[2], "%lu", &fsize);
  sscanf (argv[3], "%lu", &psize);
  sendflood (argv[1], fsize, psize);
  return 0;
  }