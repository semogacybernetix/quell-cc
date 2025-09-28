#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/ether.h>
#include <arpa/inet.h>
#include <linux/if_packet.h>

int main ()
  {
  int socket1;
  signed long sendresult;
  int interfaceresult;
  
  unsigned char sendepuffer[10000];
  memset (&sendepuffer, 0, 10000);

  sendepuffer[0]= 0x0;
  sendepuffer[1]= 0x5;
  sendepuffer[2]= 0x9e;
  sendepuffer[3]= 0x97;
  sendepuffer[4]= 0xa6;
  sendepuffer[5]= 0xbf;

  sendepuffer[6]= 0x1;
  sendepuffer[7]= 0x2;
  sendepuffer[8]= 0x3;
  sendepuffer[9]= 0x4;
  sendepuffer[10]= 0x5;
  sendepuffer[11]= 0x6;

  sendepuffer[12]= 0x12;       // IP-Paket
  sendepuffer[13]= 0x34;       // IP-Paket

  sendepuffer[14]= 0xab;   // IP Version 4
  sendepuffer[15]= 0xcd;   // IP Version 4
  sendepuffer[59]= 0xef;
  
struct sockaddr_ll socketadresse; 

  char deviceleft[IFNAMSIZ]= "enx00133ba85ea1";  // 100 MBit USB
  char deviceright[IFNAMSIZ]= "enx00133ba9458e";  // 100 MBit USB

  char interfacename[IFNAMSIZ] = "enp3s1";    // Interfacename
  strcpy (interfacename, deviceright);
  struct ifreq interfaceindex;                // Datenstruktur für Interface-Index
  int index;
  
  // Socket öffnen
  socket1 = socket (AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
  printf ("socket1: %10d\n", socket1);
  
  /* den Index des Interface ermitteln */
  printf ("Interfacename: %s\n", interfacename);
  memset (&interfaceindex, 0, sizeof (struct ifreq));
  strncpy (interfaceindex.ifr_name, interfacename, IFNAMSIZ);
  interfaceresult= ioctl (socket1, SIOCGIFINDEX, &interfaceindex);
  printf ("interfaceresult: %10d\n", interfaceresult);
  index = interfaceindex.ifr_ifindex;

  /* Socketadresse vorbereiten */
  memset(&socketadresse, 0, sizeof(struct sockaddr_ll));
  socketadresse.sll_family   = PF_PACKET;             /* RAW communication */
  socketadresse.sll_hatype   = ARPHRD_ETHER;          /* Ethernet */
  socketadresse.sll_pkttype  = PACKET_OTHERHOST;      /* Ziel ist ein anderer Rechner */
  socketadresse.sll_ifindex  = index;                 /* Interface-Index */
  socketadresse.sll_halen    = ETH_ALEN;              /* Address length*/

  // Paket abschicken
  signed long anz= 0;
  while (1)
    {
    sendresult= sendto (socket1, sendepuffer, 60, 0, (struct sockaddr*) &socketadresse, sizeof (struct sockaddr_ll));
    printf ("sendresult: %10ld  %5ld\n", sendresult, anz);
    anz++;
    usleep (10e5);
    }

  printf ("\n");
  return 0;
  }
