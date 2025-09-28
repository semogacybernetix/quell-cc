// network cable emulator mit qos

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/times.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/ether.h>
#include <arpa/inet.h>
#include <linux/if_packet.h>

struct csdmac
  {
  signed long long smac, dmac;

  csdmac () {};
  csdmac (const signed long long psmac, const signed long long pdmac) : smac (psmac), dmac (pdmac) {};
  };

  // Vektorvergleich
  signed long operator == (const csdmac &pv1, const csdmac &pv2)
    {
    return (pv1.smac == pv2.smac) && (pv1.dmac == pv2.dmac);
    }

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

csdmac llsdmac (unsigned char* pmac)
  {
  csdmac rmac;
  rmac.smac= llmac (pmac + 6);
  rmac.dmac= llmac (pmac);
  return rmac; 
  }

struct cmacliste
  {
  signed long long anz;           // Anzahl der Einträge
  signed long long empsum;        // Summe der empfangenen Pakete

  csdmac sdmac[1000];
  signed long long smac[1000];
  signed long long dmac[1000];
  signed long long empanz[1000];  // Anzahl der empfangenen Pakete einer Sourcemacadresse
  
  cmacliste ();
  signed long pos (unsigned char* psdmac);
  void addsdmac (unsigned char* psdmac);
  };

cmacliste::cmacliste ()
  {
  anz= 0;
  empsum= 0;
  }

signed long cmacliste::pos (unsigned char* psdmac)
  {
  csdmac tsdmac;

  tsdmac= llsdmac (psdmac);
  for (signed long lauf= 0; lauf < anz; lauf++)
    if (sdmac[lauf] == tsdmac)
      return lauf;
  return -1;
  }

void cmacliste::addsdmac (unsigned char* psdmac)
  {
  if (pos (psdmac) < 0)
    {
    sdmac[anz].smac= llmac (psdmac + 6);
    sdmac[anz].dmac= llmac (psdmac);
    empanz[anz]= 0;
    anz++;
    }
  }

void waitnexttic ()
  {
  clock_t now= times (NULL);
  while (now == times (NULL));
  }

//----------------------------------- Hauptprogramm --------------------------------------------------------------------
char deviceleft[100]= "enx00133ba85ea1";  // 100 MBit USB
char deviceright[100]= "enx00133ba9458e";  // 100 MBit USB

//char deviceleft[100]= "enxf8e43b100191";  // 1 GBit USB
//char deviceright[100]= "enxf8e43b1004c3";  // 1 GBit USB

int main ()
  {
  // Genauigkeit der Stoppuhr ausgeben
  signed long ticksps= sysconf (_SC_CLK_TCK);
  printf ("\n");
  printf ("Genauigkeit der Stopuhr: %10ld Ticks pro Sekunde\n", ticksps);

  // Sockets initialisieren
  int sockemp, socksenleft, socksenright;
  signed long result;
  
  unsigned char transferpuffer[10000];

  struct sockaddr_ll sockaddrleft;
  struct sockaddr_ll sockaddrright;
  struct sockaddr_ll sockaddrboth;
  signed long sockaddrsize= sizeof (sockaddrboth);

  char ifnameleft[IFNAMSIZ];
  char ifnameright[IFNAMSIZ];
  strcpy (ifnameleft, deviceleft);
  strcpy (ifnameright, deviceright);
//  char ifnameleft[IFNAMSIZ] = "enp3s0";
//  char ifnameright[IFNAMSIZ] = "enp3s1";
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
 
  memset (&ifr, 0, sizeof (struct ifreq));

// Open A Raw Socket Deviceleft --------------------------------------------------------------
    if ((raw_socket = socket (PF_PACKET, SOCK_RAW, htons (ETH_P_ALL))) < 1)
      {
      printf ("ERROR: Could not open socket, Got #?\n");
      exit (1);
      }

    /* Set the device to use */
    strcpy (ifr.ifr_name, deviceleft);
    printf ("Devicename: %s\n", ifr.ifr_name);

    /* Get the current flags that the device might have */
    if (ioctl (raw_socket, SIOCGIFFLAGS, &ifr) == -1)
      {
      perror ("Error: Could not retrive the flags from the device.\n");
      exit (1);
      }

    /* Set the old flags plus the IFF_PROMISC flag */
    printf ("up:      %6d\n", ifr.ifr_flags & IFF_UP);
    printf ("promisc: %6d\n", ifr.ifr_flags & IFF_PROMISC);
    printf ("dynamic: %6d\n", ifr.ifr_flags & IFF_DYNAMIC);
    printf ("noarp:   %6d\n", ifr.ifr_flags & IFF_NOARP);
    //printf ("echosend:%6d\n", ifr.ifr_flags & IFF_ECHO);
    ifr.ifr_flags |= IFF_UP;
    if (ioctl (raw_socket, SIOCSIFFLAGS, &ifr) == -1)
      {
      perror ("Error: Could not set device up");
      exit (1);
      }
    printf ("Setting Device up\n");
    ifr.ifr_flags |= IFF_PROMISC;
    if (ioctl (raw_socket, SIOCSIFFLAGS, &ifr) == -1)
      {
      perror ("Error: Could not set flag IFF_PROMISC");
      exit (1);
      }
    printf ("Entering promiscuous mode\n");
    ifr.ifr_flags |= IFF_NOARP;
    if (ioctl (raw_socket, SIOCSIFFLAGS, &ifr) == -1)
      {
      perror ("Error: Could not set flag IFF_NOARP");
      exit (1);
      }
    printf ("Entering no arp mode\n");

    /* Configure the device */

    if (ioctl (raw_socket, SIOCGIFINDEX, &ifr) < 0)
      {
      perror ("Error: Error getting the device index.\n");
      exit (1);
      }
    printf ("\n");

// Open A Raw Socket Deviceright -------------------------------------------------------------
    if ((raw_socket = socket (PF_PACKET, SOCK_RAW, htons (ETH_P_ALL))) < 1)
      {
      printf ("ERROR: Could not open socket, Got #?\n");
      exit (1);
      }

    /* Set the device to use */
    strcpy (ifr.ifr_name, deviceright);
    printf ("Devicename: %s\n", ifr.ifr_name);

    /* Get the current flags that the device might have */
    if (ioctl (raw_socket, SIOCGIFFLAGS, &ifr) == -1)
      {
      perror ("Error: Could not retrive the flags from the device.\n");
      exit (1);
      }

    /* Set the old flags plus the IFF_PROMISC flag */
    printf ("up:      %6d\n", ifr.ifr_flags & IFF_UP);
    printf ("promisc: %6d\n", ifr.ifr_flags & IFF_PROMISC);
    printf ("dynamic: %6d\n", ifr.ifr_flags & IFF_DYNAMIC);
    printf ("noarp:   %6d\n", ifr.ifr_flags & IFF_NOARP);
    ifr.ifr_flags |= IFF_UP;
    if (ioctl (raw_socket, SIOCSIFFLAGS, &ifr) == -1)
      {
      perror ("Error: Could not set device up");
      exit (1);
      }
    printf ("Setting Device up\n");
    ifr.ifr_flags |= IFF_PROMISC;
    if (ioctl (raw_socket, SIOCSIFFLAGS, &ifr) == -1)
      {
      perror ("Error: Could not set flag IFF_PROMISC");
      exit (1);
      }
    printf ("Entering promiscuous mode\n");
    ifr.ifr_flags |= IFF_NOARP;
    if (ioctl (raw_socket, SIOCSIFFLAGS, &ifr) == -1)
      {
      perror ("Error: Could not set flag IFF_NOARP");
      exit (1);
      }
    printf ("Entering no arp mode\n");

    /* Configure the device */

    if (ioctl (raw_socket, SIOCGIFINDEX, &ifr) < 0)
      {
      perror ("Error: Error getting the device index.\n");
      exit (1);
      }

// -------------------- Empfangsschleife --------------------------------------------------------
  getchar ();

  cmacliste emplisteleft;
  cmacliste emplisteright;

  signed long printtime= times (NULL);
  
  while (1)
    {
    // Paket empfangen
    result= recvfrom (sockemp, transferpuffer, 10000, 0, (struct sockaddr*) (&sockaddrboth), (socklen_t*)&sockaddrsize);

    // weiterempfangen wenn nicht links oder rechts
    if ((sockaddrboth.sll_ifindex != indexleft) && (sockaddrboth.sll_ifindex != indexright))
      {
//      printf ("Packet %10ld  length: %5ld idx: %2d %20llx %10lld %10lld   not from cable\n", packetcounter, result, sockaddrboth.sll_ifindex, llmac (transferpuffer + 6), emplisteleft.anz, emplisteright.anz);
      continue;
      }

    // Macliste auf Bildschirm ausgeben
    if (times (NULL) >= printtime)
      {
      printtime+= 100;
      printf ("----------------------------------------------------------------------------\n");
      printf ("Macliste links: %20lld                           %4lld\n", emplisteleft.empsum, emplisteleft.anz);
      for (signed long lauf= 0; lauf < emplisteleft.anz; lauf++)
        printf ("%14llx  %14llx  %20lld\n", emplisteleft.sdmac[lauf].smac, emplisteleft.sdmac[lauf].dmac, emplisteleft.empanz[lauf]);
      printf ("\n");
      printf ("Macliste rechts:%20lld                           %4lld\n", emplisteright.empsum, emplisteright.anz);
      for (signed long lauf= 0; lauf < emplisteright.anz; lauf++)
        printf ("%14llx  %14llx  %20lld\n", emplisteright.sdmac[lauf].smac, emplisteright.sdmac[lauf].dmac, emplisteright.empanz[lauf]);
      }
    
    // Pakete links zählen (pro sourcemac und summe)
    if (sockaddrboth.sll_ifindex == indexleft)
      {
      emplisteleft.addsdmac (transferpuffer);
      signed long emppos= emplisteleft.pos (transferpuffer);
      emplisteleft.empanz[emppos]++;
      emplisteleft.empsum++;
      }
    
    // Pakete rechts zählen (pro sourcemac und summe)
    if (sockaddrboth.sll_ifindex == indexright)
      {
      emplisteright.addsdmac (transferpuffer);
      signed long emppos= emplisteright.pos (transferpuffer);
      emplisteright.empanz[emppos]++;
      emplisteright.empsum++;
      }

    //printf ("Packet %10ld  empresult: %5ld idx: %2d %20llx %10lld %10lld side wrong\n", packetcounter, result, sockaddrboth.sll_ifindex, llmac (transferpuffer + 6), emplisteleft.anz, emplisteright.anz);
    }
  return 0;
  }
