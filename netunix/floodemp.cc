#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <strings.h>
#include <sys/times.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

void sendflood (char* pipaddr)
  {
  printf ("%s", pipaddr);
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
  addrflood.sin_addr.s_addr= htonl (INADDR_ANY);
  int bnd= bind (skflood, (sockaddr*) &addrflood, sizeof (addrflood));
  if (bnd != 0)
    {
    cout << "bind fehlgeschlagen" << endl;
    exit (0);
    }
  unsigned int udpdata[4096];
  // tms zeit;
  unsigned long ticksps= sysconf (_SC_CLK_TCK);
  cout << "Ticks: " << ticksps << endl;
  unsigned long frame;
  while (1)
    {
    if (read (skflood, udpdata, 16384) < 0)
      {
      cout << "Fehler bei read" << endl;
      }
    frame= ntohl (udpdata[0]);
    cout << "frame: " << frame << endl;
    }
  }

int main (int argc, char** argv)
  {
  if (argc != 1)
    {
    cout << "floodsen <IP-Adresse> <packet-size>" << endl;
    exit (0);
    }
  sendflood (argv[1]);
  return 0;
  }