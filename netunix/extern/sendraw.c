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
  int sendresult;
  int interfaceresult;
  
  unsigned char sendepuffer[10000];
  memset (&sendepuffer, 0, 10000);

  sendepuffer[0]= 0;
  sendepuffer[1]= 1;
  sendepuffer[2]= 2;
  sendepuffer[3]= 3;
  sendepuffer[4]= 4;
  sendepuffer[5]= 5;
  sendepuffer[6]= 6;

  sendepuffer[7]= 7;
  sendepuffer[8]= 8;
  sendepuffer[9]= 9;
  sendepuffer[10]= 10;
  sendepuffer[11]= 11;
  sendepuffer[12]= 8;       // IP-Paket
  sendepuffer[13]= 0;       // IP-Paket

  sendepuffer[14]= 69;   // IP Version 4
  
struct sockaddr_ll socketadresse; 

  char interfacename[IFNAMSIZ] = "enp3s0";    // Interfacename
  struct ifreq interfaceindex;                // Datenstruktur für Interface-Index
  int index;
  
  // Socket öffnen
  socket1 = socket (AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
  printf ("socket1: %10d\n", socket1);
  
  /* den Index des Interface ermitteln */
  printf ("Interfacename: %s\n", interfacename);
  memset (&interfaceindex, 0, sizeof (struct ifreq));
  strncpy (interfaceindex.ifr_name, interfacename, IFNAMSIZ - 1);
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
  sendresult= sendto (socket1, sendepuffer, 1500, 0, (struct sockaddr*) &socketadresse, sizeof (struct sockaddr_ll));
  printf ("sendresult: %10d\n", sendresult);

  printf ("\n");
  return 0;
  }
