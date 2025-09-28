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
//  #define DEFAULT_IF  "lo"


int main(int argc, char *argv[])
  {
  char ifName[IFNAMSIZ] = DEFAULT_IF; /* Interfacename */
  int sockfd;                         /* Socket-Descriptor */
  struct ifreq if_idx;                /* Dateastruktur fuern Interface-Index */
  struct ifreq if_mac;                /* Datenastruktur fuer MAC-Adresse */
  struct ifreq if_ip;                 /* Datenastruktur fuer IP-Adresse */
  unsigned char hwaddr[6];            /* speichert MAC-Adresse */
  int index;                          /* speichert Interface-Index */
  char *addr;                         /* Zeiger auf IP-Adresse (dotted quad) */

  /* Packet-Socket oeffnen */
  if ((sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) == -1)
    {
    perror("socket() ging schief");
    if (errno == EACCES) printf(" (EACCES)\n");
    if (errno == EAFNOSUPPORT) printf(" (EAFNOSUPPORT)\n");
    return 1;
    }

  /* Den Index des Interface ermitteln */
  memset(&if_idx, 0, sizeof(struct ifreq));
  strncpy(if_idx.ifr_name, ifName, IFNAMSIZ-1);
  if (ioctl(sockfd, SIOCGIFINDEX, &if_idx) < 0)
    {
    perror("SIOCGIFINDEX");
    return 1;
    }
  index = if_idx.ifr_ifindex;
  /* Ausgabe */
  printf("The interface index of %s is %d\n",
         ifName, index);

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

  /* Die IP-Adresse des Interface ermitteln */
  memset(&if_ip, 0, sizeof(struct ifreq));
  strncpy(if_ip.ifr_name, ifName, IFNAMSIZ-1);
  if (ioctl(sockfd, SIOCGIFADDR, &if_ip) < 0)
    {
    perror("SIOCGIFADDR");
    return 1;
    }
  /* in "dotted quad" konvertieren */
  addr = inet_ntoa(((struct sockaddr_in *)&if_ip.ifr_addr)->sin_addr);
  /* Ausgabe */
  printf("The IP address of %s is %s\n", ifName, addr);

  return 0;
  }
