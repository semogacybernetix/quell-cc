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

/* Puffergroesse */
#define BUF_SIZ    1024

/* destination host MAC address */
unsigned char dest_mac[6] = {0x00, 0x07, 0xe9, 0x23, 0x71, 0x62};

/* Packet data */
char packet_data[] = "0123456789";

int main(int argc, char *argv[])
  {
  char ifName[IFNAMSIZ] = DEFAULT_IF; /* Interfacename */
  int sockfd;                         /* Socket-Descriptor */
  struct ifreq if_idx;                /* Dateastruktur fuer Interface-Index */
  struct ifreq if_mac;                /* Datenastruktur fuer MAC-Adresse */
  unsigned char hwaddr[6];            /* speichert MAC-Adresse */
  char sendbuf[BUF_SIZ];              /* Sendepuffer */
  struct sockaddr_ll socket_address;  /* fuer sendto() */
  int index;                          /* speichert Interface-Index */

  /* Zeiger auf Sendepuffer-Anfang und -Datenbereich */
  struct ether_header *eh = (struct ether_header *) sendbuf;
  unsigned char *data = (unsigned char *) (sendbuf + sizeof(struct ether_header));

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

  /* Construct the Ethernet header */
  memset(sendbuf, 0, BUF_SIZ);

  /* Ethernet header */
  memcpy(eh->ether_shost, hwaddr, 6);      /* eigene Adresse */
  memcpy(eh->ether_dhost, dest_mac, 6);    /* Zielandresse */
  eh->ether_type = htons(ETH_P_IP);        /* Ethertype field */

   /* Packet data dahinter */
  memcpy(data, packet_data, sizeof(packet_data));

  /* prepare sockaddr_ll */
  memset(&socket_address, 0, sizeof(struct sockaddr_ll));
  socket_address.sll_family   = PF_PACKET;             /* RAW communication */
  socket_address.sll_protocol = htons(ETH_P_IP);       /* Protokoll oberhalb (egal) */
  socket_address.sll_hatype   = ARPHRD_ETHER;          /* Ethernet */
  socket_address.sll_pkttype  = PACKET_OTHERHOST;      /* Ziel ist ein anderer Rechner */
  socket_address.sll_ifindex  = index;                 /* Interface-Index */
  socket_address.sll_halen    = ETH_ALEN;              /* Address length*/
  memcpy(socket_address.sll_addr, dest_mac, ETH_ALEN); /* Zielandresse */

  /* Send packet */
  if (sendto(sockfd, sendbuf, ETH_HLEN + strlen(packet_data), 0,
      (struct sockaddr*)&socket_address, sizeof(struct sockaddr_ll)) < 0)
         printf("Send failed\n");

  return 0;
  }
