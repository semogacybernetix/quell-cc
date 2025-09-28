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

void waitnexttic ()
  {
  clock_t now= times (NULL);
  while (now == times (NULL));
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

struct macliste
  {
  signed long long anz;
  signed long long empanz;
  signed long long sendanz;

  signed long long mac[1000];
  unsigned long long ip[1000];
  signed long long empvol[1000];
  signed long long sendvol[1000];
  
  macliste ();
  void add (unsigned char* pmac);
  signed long neu (unsigned char* pmac);
  signed long pos (unsigned char* pmac);
  };

macliste::macliste ()
  {
  anz= 0;
  empanz= 0;
  sendanz= 0;
  }

void macliste::add (unsigned char* pmac)
  {
  if (neu (pmac))
    {
    mac[anz]= llmac (pmac);
    ip[anz]= 0;
    empvol[anz]= 0;
    sendvol[anz]= 0;
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

signed long macliste::pos (unsigned char* pmac)
  {
  signed long long smac;

  smac= llmac (pmac);
  for (signed long lauf= 0; lauf < anz; lauf++)
    if (mac[lauf] == smac)
      return lauf;
  return -1;
  }

void printip (unsigned long pip)
  {
  unsigned char ip1= (pip >> 24) & 0xff;
  unsigned char ip2= (pip >> 16) & 0xff;
  unsigned char ip3= (pip >> 8) & 0xff;
  unsigned char ip4= (pip >> 0) & 0xff;
  printf ("%d.%d.%d.%d", ip1, ip2, ip3, ip4);
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

  getchar ();

  // Pakete transferieren
  signed long packetcounter= 0;
  
  macliste emplisteleft;
  macliste emplisteright;
  signed long long sourcemac;
  signed long long destmac;
  signed long ethtyp;
  signed long ipproto;
  unsigned long sourceip;
  unsigned long destip;

  // Stoppuhr starten
  clock_t startticks;
  startticks= times (NULL);
  clock_t nowl= startticks;
  clock_t nowr= startticks;

  long double rrate= 307200;   // Bytes pro tick (1/100 Sekunde)
  long double lrate= 307200;
  long double sendl= 0;
  long double sendr= 0;
  //long double burst= 1;   // Zeitabschnitt in ticks, in der das durch die Rate bestimmte maximale Datenvolumen einzuhalten ist
  signed long empticks;
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
    destmac= llmac (transferpuffer);
    sourcemac= llmac (transferpuffer + 6);
    ethtyp= 256*transferpuffer[12] + transferpuffer[13];
    ipproto= transferpuffer[23];
    sourceip= (transferpuffer[26] << 24) + (transferpuffer[27] << 16) + (transferpuffer[28] << 8) + transferpuffer[29];
    destip= (transferpuffer[30] << 24) + (transferpuffer[31] << 16) + (transferpuffer[32] << 8) + transferpuffer[33];
    if (ethtyp == 0x800)
      {
      signed long pos= 0;
      pos = emplisteleft.pos (transferpuffer + 6);
      if (pos >= 0)
        emplisteleft.ip[pos]= sourceip;
      pos = emplisteright.pos (transferpuffer + 6);
      if (pos >= 0)
        emplisteright.ip[pos]= sourceip;
      }
    
    // Macliste auf Bildschirm ausgeben
    if (times (NULL) >= printtime)
      {
      printtime+= 100;
      printf ("-----------------------------------------------------\n");
      printf ("Macliste links: %20lld  %20lld  %4lld\n", emplisteleft.empanz, emplisteleft.sendanz, emplisteleft.anz);
      for (signed long lauf= 0; lauf < emplisteleft.anz; lauf++)
        {
        printf ("%14llx  %20lld  %20lld  ", emplisteleft.mac[lauf], emplisteleft.empvol[lauf], emplisteleft.sendvol[lauf]);
        printip (emplisteleft.ip[lauf]);
        printf ("\n");
        }
      printf ("\n");
      printf ("Macliste rechts:%20lld  %20lld  %4lld\n", emplisteright.empanz, emplisteright.sendanz, emplisteright.anz);
      for (signed long lauf= 0; lauf < emplisteright.anz; lauf++)
        {
        printf ("%14llx  %20lld  %20lld  ", emplisteright.mac[lauf], emplisteright.empvol[lauf], emplisteright.sendvol[lauf]);
        printip (emplisteright.ip[lauf]);
        printf ("\n");
        }
      }
    
    // Paket links zählen
    if ((sockaddrboth.sll_ifindex == indexleft) && (!emplisteleft.neu (transferpuffer + 6)))
      {
      signed long emppos= emplisteleft.pos (transferpuffer + 6);
      emplisteleft.empvol[emppos]+= result;
      emplisteleft.empanz+= result;
      }
    
    // Paket von links nach rechts schieben, falls der Absender nicht in rechter Macliste ist 
    if ((sockaddrboth.sll_ifindex == indexleft) && (emplisteright.neu (transferpuffer + 6)))
      {
      if (emplisteleft.neu (transferpuffer + 6))
        {
        emplisteleft.add (transferpuffer + 6);   // Ethernet II Paket Quelladresse
        emplisteleft.empvol[emplisteleft.anz - 1]= result;    // Erstes empfangenes Paket der neuen Macadresse zählen
        emplisteleft.empanz+= result;    // Erstes empfangenes Paket der neuen Macadresse zählen
        }
      empticks= times (NULL) - nowr;
      if (empticks*rrate > sendr)
        sendr= 0;
        else
        sendr= sendr - empticks*rrate;
      while (sendr + result > rrate)
        {
        waitnexttic ();
        sendr= sendr - rrate;
        }
      nowr= times (NULL);
      result= sendto (socksenright, transferpuffer, result, 0, (struct sockaddr*) &sockaddrright, sizeof (struct sockaddr_ll));
      sendr= sendr + result;
      //printf ("\r%10ld  Packetnr: %10ld  len: %5ld  if: %2d  %12llx  ml: %2lld  mr: %2lld  ----->  len: %5ld  if: %2d  %12llx %6lx %4ld",
      //        times (NULL) - startticks, packetcounter, result, sockaddrboth.sll_ifindex, sourcemac, emplisteleft.anz, emplisteright.anz, result, indexright, destmac, ethtyp, ipproto);
      packetcounter++;
      continue;
      }
    
    // Paket rechts zählen
    if ((sockaddrboth.sll_ifindex == indexright) && (!emplisteright.neu (transferpuffer + 6)))
      {
      signed long emppos= emplisteright.pos (transferpuffer + 6);
      emplisteright.empvol[emppos]+= result;
      emplisteright.empanz+= result;
      }
    // Paket von rechts nach links schieben, falls der Absender nicht in rechter Macliste ist 
    if ((sockaddrboth.sll_ifindex == indexright) && (emplisteleft.neu (transferpuffer + 6)))
      {
      if (emplisteright.neu (transferpuffer + 6))
        {
        emplisteright.add (transferpuffer + 6);   // Ethernet II Paket Quelladresse
        emplisteright.empvol[emplisteright.anz - 1]= result;    // Erstes empfangenes Paket der neuen Macadresse zählen
        emplisteright.empanz+= result;    // Erstes empfangenes Paket der neuen Macadresse zählen
        }
      empticks= times (NULL) - nowl;
      if (empticks*lrate > sendl)
        sendl= 0;
        else
        sendl= sendl - empticks*lrate;
      while (sendl + result > lrate)
        {
        waitnexttic ();
        sendl= sendl - lrate;
        }
      nowl= times (NULL);
      result= sendto (socksenleft, transferpuffer, result, 0, (struct sockaddr*) &sockaddrleft, sizeof (struct sockaddr_ll));
      sendl= sendl + result;
      //printf ("\r%10ld  Packetnr: %10ld  len: %5ld  if: %2d  %12llx  ml: %2lld  mr: %2lld  <-----  len: %5ld  if: %2d  %12llx %6lx %4ld",
      //        times (NULL) - startticks, packetcounter, result, sockaddrboth.sll_ifindex, sourcemac, emplisteleft.anz, emplisteright.anz, result, indexleft, destmac, ethtyp, ipproto);
      packetcounter++;
      continue;
      }
    //printf ("Packet %10ld  empresult: %5ld idx: %2d %20llx %10lld %10lld side wrong\n", packetcounter, result, sockaddrboth.sll_ifindex, llmac (transferpuffer + 6), emplisteleft.anz, emplisteright.anz);
    }
  return 0;
  }
