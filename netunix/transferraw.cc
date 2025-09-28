// network cable emulator

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

signed long long llmac (unsigned char* pmac)
  {
  signed long long sum= 0;
  signed long long sumd;
  for (signed long lauf= 0; lauf < 6; lauf++)
    {
    sumd= pmac[lauf];
    sum= sum | (sumd << (40 - lauf*8));
    }
  return sum; 
  }

struct macliste
  {
  signed long long anz;
  signed long long mac[100000];
  
  macliste ();
  void add (unsigned char* pmac);
  signed long neu (unsigned char* pmac);
  };

macliste::macliste ()
  {
  anz= 0;
  }

void macliste::add (unsigned char* pmac)
  {
  if (neu (pmac))
    {
    mac[anz]= llmac (pmac);
    anz++;
    }
  }

signed long macliste::neu (unsigned char* pmac)
  {
  signed long long smac;

  smac= llmac (pmac);
  for (signed long lauf= 0; lauf < anz; lauf++)
    if (mac[lauf] == smac)
      return 0;
  return 1;
  }

int main ()
  {
  int sockemp, socksenleft, socksenright;
  signed long result;
  
  unsigned char transferpuffer[10000];

  struct sockaddr_ll sockaddrleft;
  struct sockaddr_ll sockaddrright;
  struct sockaddr_ll sockaddrboth;
  signed long sockaddrsize= sizeof (sockaddrboth);

  char ifnameleft[IFNAMSIZ] = "enx04421a3c65e8";
  char ifnameright[IFNAMSIZ] = "enx000acd400b7b";

  struct ifreq ifindexleft; 
  struct ifreq ifindexright; 
  int indexleft;
  int indexright;
  
  // Socket öffnen
  sockemp= socket (AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
  printf ("sockemp:      %5d\n", sockemp);
  
  // Socket öffnen
  socksenleft= socket (AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
  printf ("socksenleft:  %5d\n", socksenleft);
  
  // Socket öffnen
  socksenright= socket (AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
  printf ("socksenright: %5d\n", socksenright);

  printf ("\n");
  
  /* den Index des Interfaces ermitteln */
  printf ("Interfacename left:  %s\n", ifnameleft);
  printf ("Interfacename right: %s\n", ifnameright);
  printf ("\n");
  memset (&ifindexleft, 0, sizeof (struct ifreq));
  memset (&ifindexright, 0, sizeof (struct ifreq));
  strncpy (ifindexleft.ifr_name, ifnameleft, IFNAMSIZ);
  strncpy (ifindexright.ifr_name, ifnameright, IFNAMSIZ);
  result= ioctl (socksenleft, SIOCGIFINDEX, &ifindexleft);
  result= ioctl (socksenright, SIOCGIFINDEX, &ifindexright);

  indexleft= ifindexleft.ifr_ifindex;
  indexright= ifindexright.ifr_ifindex;
  printf ("interfaceresult: %5ld   indexleft  %5d\n", result, indexleft);
  printf ("interfaceresult: %5ld   indexright %5d\n", result, indexright);

  printf ("\n");

  /* Socketadresse vorbereiten */
  memset (&sockaddrleft, 0, sizeof(struct sockaddr_ll));
  sockaddrleft.sll_family   = PF_PACKET;             /* RAW communication */
  sockaddrleft.sll_hatype   = ARPHRD_ETHER;          /* Ethernet */
  sockaddrleft.sll_pkttype  = PACKET_OTHERHOST;      /* Ziel ist ein anderer Rechner */
  sockaddrleft.sll_ifindex  = indexleft;             /* Interface-Index */
  sockaddrleft.sll_halen    = ETH_ALEN;              /* Address length*/

  /* Socketadresse vorbereiten */
  memset (&sockaddrright, 0, sizeof(struct sockaddr_ll));
  sockaddrright.sll_family   = PF_PACKET;             /* RAW communication */
  sockaddrright.sll_hatype   = ARPHRD_ETHER;          /* Ethernet */
  sockaddrright.sll_pkttype  = PACKET_OTHERHOST;      /* Ziel ist ein anderer Rechner */
  sockaddrright.sll_ifindex  = indexright;            /* Interface-Index */
  sockaddrright.sll_halen    = ETH_ALEN;              /* Address length*/

  /* Socketadresse vorbereiten */
  memset (&sockaddrboth, 0, sizeof(struct sockaddr_ll));
  sockaddrboth.sll_family   = PF_PACKET;             /* RAW communication */
  sockaddrboth.sll_hatype   = ARPHRD_ETHER;          /* Ethernet */
  sockaddrboth.sll_pkttype  = PACKET_OTHERHOST;      /* Ziel ist ein anderer Rechner */
  sockaddrboth.sll_halen    = ETH_ALEN;              /* Address length*/

  // Schnittstellen in den Promiskuitätsmodus schalten
  
  struct ifreq ifr;
  int    raw_socket;
  char   deviceleft[100]= "enx04421a3c65e8";
  char   deviceright[100]= "enx000acd400b7b";
 
  memset (&ifr, 0, sizeof (struct ifreq));

// Open A Raw Socket Deviceleft
    if ((raw_socket = socket (PF_PACKET, SOCK_RAW, htons (ETH_P_ALL))) < 1)
      {
      printf ("ERROR: Could not open socket, Got #?\n");
      exit (1);
      }

    /* Set the device to use */
    strcpy (ifr.ifr_name, deviceleft);

    /* Get the current flags that the device might have */
    if (ioctl (raw_socket, SIOCGIFFLAGS, &ifr) == -1)
      {
      perror ("Error: Could not retrive the flags from the device.\n");
      exit (1);
      }

    /* Set the old flags plus the IFF_PROMISC flag */
    ifr.ifr_flags |= IFF_PROMISC;
    if (ioctl (raw_socket, SIOCSIFFLAGS, &ifr) == -1)
      {
      perror ("Error: Could not set flag IFF_PROMISC");
      exit (1);
      }
    printf ("Entering promiscuous mode\n");

    /* Configure the device */

    if (ioctl (raw_socket, SIOCGIFINDEX, &ifr) < 0)
      {
      perror ("Error: Error getting the device index.\n");
      exit (1);
      }

// Open A Raw Socket Deviceright
    if ((raw_socket = socket (PF_PACKET, SOCK_RAW, htons (ETH_P_ALL))) < 1)
      {
      printf ("ERROR: Could not open socket, Got #?\n");
      exit (1);
      }

    /* Set the device to use */
    strcpy (ifr.ifr_name, deviceright);

    /* Get the current flags that the device might have */
    if (ioctl (raw_socket, SIOCGIFFLAGS, &ifr) == -1)
      {
      perror ("Error: Could not retrive the flags from the device.\n");
      exit (1);
      }

    /* Set the old flags plus the IFF_PROMISC flag */
    ifr.ifr_flags |= IFF_PROMISC;
    if (ioctl (raw_socket, SIOCSIFFLAGS, &ifr) == -1)
      {
      perror ("Error: Could not set flag IFF_PROMISC");
      exit (1);
      }
    printf ("Entering promiscuous mode\n");

    /* Configure the device */

    if (ioctl (raw_socket, SIOCGIFINDEX, &ifr) < 0)
      {
      perror ("Error: Error getting the device index.\n");
      exit (1);
      }

  // Pakete transferieren
  getchar ();
  signed long packetcounter= 0;
  
  macliste emplisteleft;
  macliste emplisteright;
  signed long long sourcemac;
  signed long long destmac;
  signed long proto;
  signed long ipproto;

  while (1)
    {
    result= recvfrom (sockemp, transferpuffer, 10000, 0, (struct sockaddr*) (&sockaddrboth), (socklen_t*)&sockaddrsize);
    if ((sockaddrboth.sll_ifindex != indexleft) && (sockaddrboth.sll_ifindex != indexright))
      {
//      printf ("Packet %10ld  length: %5ld idx: %2d %20llx %10lld %10lld   not from cable\n", packetcounter, result, sockaddrboth.sll_ifindex, llmac (transferpuffer + 6), emplisteleft.anz, emplisteright.anz);
      continue;
      }
    destmac= llmac (transferpuffer);
    sourcemac= llmac (transferpuffer + 6);
    proto= transferpuffer[13] + 256*transferpuffer[12];
    ipproto= transferpuffer[23];
    if ((sockaddrboth.sll_ifindex == indexleft) && (emplisteright.neu (transferpuffer + 6)))
      {
      emplisteleft.add (transferpuffer + 6);   // Ethernet II Paket Quelladresse
      //usleep ((unsigned int) (double (result)*3.2));
      result= sendto (socksenright, transferpuffer, result, 0, (struct sockaddr*) &sockaddrright, sizeof (struct sockaddr_ll));
      printf ("Packetnr: %10ld  len: %5ld  if: %2d  %12llx  ml: %2lld  mr: %2lld  ----->  len: %5ld  if: %2d  %12llx %6lx %4ld\n", packetcounter, result, sockaddrboth.sll_ifindex, sourcemac, emplisteleft.anz, emplisteright.anz, result, indexright, destmac, proto, ipproto);
      packetcounter++;
      continue;
      }
    if ((sockaddrboth.sll_ifindex == indexright) && (emplisteleft.neu (transferpuffer + 6)))
      {
      emplisteright.add (transferpuffer + 6);   // Ethernet II Paket Quelladresse
      //usleep (1000);
      result= sendto (socksenleft, transferpuffer, result, 0, (struct sockaddr*) &sockaddrleft, sizeof (struct sockaddr_ll));
      printf ("Packetnr: %10ld  len: %5ld  if: %2d  %12llx  ml: %2lld  mr: %2lld  <-----  len: %5ld  if: %2d  %12llx %6lx %4ld\n", packetcounter, result, sockaddrboth.sll_ifindex, sourcemac, emplisteleft.anz, emplisteright.anz, result, indexleft, destmac, proto, ipproto);
      packetcounter++;
      continue;
      }
    //printf ("Packet %10ld  empresult: %5ld idx: %2d %20llx %10lld %10lld side wrong\n", packetcounter, result, sockaddrboth.sll_ifindex, llmac (transferpuffer + 6), emplisteleft.anz, emplisteright.anz);
    }
  return 0;
  }
