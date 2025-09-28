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

/* Default-Netzwerk-Interface */
#define DEFAULT_IF  "eth0"

/* Gibt ein Byte binaer aus */
void print_bin(unsigned char x)
  {
  int i;
  char erg[10];
  erg[9] = '\0';
  erg[8] = ' ';

  for (i = 7; i >= 0 ; i--)
    {
    erg[i] = (x%2 == 0)?'0':'1';
    x = x >> 1;
    }
  printf("%s", erg);
  }


int main(int argc, char *argv[])
  {
  char ifName[IFNAMSIZ] = DEFAULT_IF; /* Interfacename */
  int sockfd;                         /* Socket-Descriptor */
  struct ifreq if_idx;                /* Dateastruktur fuer Interface-Index */
  struct ifreq if_mac;                /* Datenastruktur fuer MAC-Adresse */
  unsigned char hwaddr[6];            /* speichert MAC-Adresse */
  struct sockaddr_ll socket_address;  /* fuer sendto() */
  int index;                          /* speichert Interface-Index */
  unsigned char rcvbuf[ETH_FRAME_LEN];/* Empfangs-Buffer */
  int length = 0;                     /* Laenge des empfangenen Frames */
  int j, k;


  /* Get interface name */
  if (argc > 1)
    strcpy(ifName, argv[1]);
  else
    strcpy(ifName, DEFAULT_IF);

   /* Packet-Socket oeffnen */
  if ((sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) == -1)
    {
    perror("socket() ging schief");
    if (errno == EACCES) printf(" (EACCES)\n");
    if (errno == EAFNOSUPPORT) printf(" (EAFNOSUPPORT)\n");
    return 1;
    }

  /* den Index des Interface ermitteln */
  memset(&if_idx, 0, sizeof(struct ifreq));
  strncpy(if_idx.ifr_name, ifName, IFNAMSIZ-1);
  if (ioctl(sockfd, SIOCGIFINDEX, &if_idx) < 0)
    {
    perror("SIOCGIFINDEX");
    return 1;
    }
  index = if_idx.ifr_ifindex;

  /* Die MAC-Adresse des Interface ermitteln */
  memset(&if_mac, 0, sizeof(struct ifreq));
  strncpy(if_mac.ifr_name, ifName, IFNAMSIZ-1);
  if (ioctl(sockfd, SIOCGIFHWADDR, &if_mac) < 0)
    {
    perror("SIOCGIFHWADDR");
    return 1;
    }
  /* 6 Bytes MAC-Adresse in das Array hwaddr kopieren */
  memcpy(hwaddr, if_mac.ifr_hwaddr.sa_data, 6);
  /* Ausgabe */
  printf("The hardware address of %s, type %d is "
         "%2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x.\n", ifName,
         if_mac.ifr_hwaddr.sa_family, hwaddr[0], hwaddr[1],
         hwaddr[2], hwaddr[3], hwaddr[4], hwaddr[5]);

  /* prepare sockaddr_ll */
  memset(&socket_address, 0, sizeof(struct sockaddr_ll));
  socket_address.sll_family   = PF_PACKET;             /* RAW communication */
  socket_address.sll_protocol = htons(ETH_P_IP);       /* Protokoll oberhalb (egal) */
  socket_address.sll_hatype   = ARPHRD_ETHER;          /* Ethernet */
  socket_address.sll_pkttype  = PACKET_OTHERHOST;      /* Ziel ist ein anderer Rechner */
  socket_address.sll_ifindex  = index;                 /* Interface-Index */
  socket_address.sll_halen    = ETH_ALEN;              /* Address length*/

  length = recvfrom(sockfd, rcvbuf, ETH_FRAME_LEN, 0, NULL, NULL);
  if (length == -1)
    printf("Empfang ging schief");

  printf("The Source address is "
         "%2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x.\n",
         rcvbuf[0], rcvbuf[1], rcvbuf[2], rcvbuf[3], rcvbuf[4], rcvbuf[5]);

  printf("The Destination address is "
         "%2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x.\n",
         rcvbuf[6], rcvbuf[7], rcvbuf[8], rcvbuf[9], rcvbuf[10], rcvbuf[11]);

  /* Ausgabe binaer/ASCII, immer 4 Bytes pro Zeile */
  k = 0;  /* Bytezaehler */
  for (j = 14; j < length; j++)
    {
    k++;
    print_bin(rcvbuf[j]);
    if (rcvbuf[j] >= ' ' && rcvbuf[j] < 127)
      printf("%c ", rcvbuf[j]);
    else
      printf(". ");
    /* alle 4 Bytes Newline */
    if (!(k % 4)) { printf ("\n"); }
    }

  printf("\n");

  return 0;
  }
