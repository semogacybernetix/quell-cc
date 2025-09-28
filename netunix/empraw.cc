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

  struct sockaddr_ll socketadresse;
  signed long sockaddrsize= sizeof (socketadresse);

  char interfacename[IFNAMSIZ] = "enp3s1";    // Interfacename
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
  index = interfaceindex.ifr_ifindex;
  printf ("interfaceresult: %10d\n", interfaceresult);

  /* Socketadresse vorbereiten */
  memset(&socketadresse, 0, sizeof(struct sockaddr_ll));
  socketadresse.sll_family   = PF_PACKET;             /* RAW communication */
  socketadresse.sll_hatype   = ARPHRD_ETHER;          /* Ethernet */
  socketadresse.sll_pkttype  = PACKET_OTHERHOST;      /* Ziel ist ein anderer Rechner */
  socketadresse.sll_ifindex  = index;                 /* Interface-Index */
  socketadresse.sll_halen    = ETH_ALEN;              /* Address length*/

  // Paket empfangen
  while (1)
    {
    sendresult= recvfrom (socket1, sendepuffer, 10000, 0, (struct sockaddr*) (&socketadresse), (socklen_t*)&sockaddrsize);
    if (socketadresse.sll_ifindex == index)
      {
      printf ("empresult: %10ld\n", sendresult);
      printf ("Index: %2d  %2d\n", index, socketadresse.sll_ifindex);
      }
    }

  printf ("\n");
  return 0;
  }
