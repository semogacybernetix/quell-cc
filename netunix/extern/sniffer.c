#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<netdb.h>
#include<signal.h>
#include<sys/socket.h>
#include<sys/ioctl.h>
#include<sys/time.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netinet/ip_icmp.h>
#include<netinet/udp.h>
#include<netinet/tcp.h>
#include<netinet/ip.h>
#include<net/ethernet.h>
#include<netinet/if_ether.h>

/* Default-Netzwerk-Interface */
#define DEFAULT_IF  "enp3s1"

void do_packet(unsigned char*, int);
void print_ip_header(unsigned char*, int);
void print_tcp_packet(unsigned char *, int);
void print_udp_packet(unsigned char *, int);
void print_icmp_packet(unsigned char*, int);
void dump_data(unsigned char*, int);
void print_data(unsigned char*, int);
void beenden(int);


struct sockaddr_in source, dest;     /* fuer Adressierung */
int tcp = 0, udp = 0, icmp = 0,
    others = 0, igmp = 0,
    total = 0;                       /* Zaehler */
//int i, j;
int go = 1;

int main()
  {
  struct sockaddr saddr;  /* fuer recvfrom() */
  int saddr_size;
  int data_size;          /* Paketgroesse */
  int sockfd;             /* sockethandle */
  unsigned char *buffer = (unsigned char *) malloc(65536); //Its Big!

  /* Signalhandler aktivieren */
  signal(SIGINT,beenden);

  printf("Starte...\n");
  /* Packet-Socket oeffnen */
  if ((sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) == -1)
    {
    perror("socket() ging schief");
    if (errno == EACCES) printf(" (EACCES)\n");
    if (errno == EAFNOSUPPORT) printf(" (EAFNOSUPPORT)\n");
    return 1;
    }

  while(go)
    {
    saddr_size = sizeof saddr;
    /* Paket empfangen */
    data_size = recvfrom(sockfd, buffer, 65536, 0, &saddr, (socklen_t*)&saddr_size);
    if(data_size < 0)
        {
        perror("Recvfrom-Error, Abbruch\n");
        return 1;
        }
    /* Paket verarbeiten */
    do_packet(buffer, data_size);
    }
  close(sockfd);
  /* Zaehler ausgeben */
  printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
  printf("TCP: %d   UDP: %d   ICMP: %d   IGMP: %d   Others: %d   Total: %d\n",
          tcp, udp, icmp, igmp, others, total);
  printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
  printf("Fertig...\n");
  return 0;
  }

void do_packet(unsigned char* buffer, int size)
  {
  /* IP-Header untersuchen; er beginnt nach dem Ethernet-Header */
  struct iphdr *iph = (struct iphdr*)(buffer + sizeof(struct ethhdr));
  ++total;
  switch (iph->protocol) /* Check Protocol */
    {
    case 1:  /* ICMP Protocol */
      ++icmp;
      print_icmp_packet(buffer , size);
      break;
    case 2:  /* IGMP Protocol */
       ++igmp;
       /* keine Ausgabe */
       break;
    case 6:  /* TCP Protocol */
       ++tcp;
       print_tcp_packet(buffer , size);
       break;
    case 17: /* UDP Protocol */
       ++udp;
       print_udp_packet(buffer , size);
       break;
    default: /* andere Protokolle z. B. ARP etc. */
       ++others;
       break;
    }
  }

void print_ethernet_header(unsigned char* Buffer, int Size)
  {
  struct ethhdr *eth = (struct ethhdr *)Buffer;

  printf("\n");
  printf("Ethernet Header\n");
  printf("   Destination Address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n",
         eth->h_dest[0], eth->h_dest[1], eth->h_dest[2],
         eth->h_dest[3], eth->h_dest[4], eth->h_dest[5] );
  printf("   Source Address      : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n",
         eth->h_source[0], eth->h_source[1], eth->h_source[2],
         eth->h_source[3], eth->h_source[4], eth->h_source[5]);
  printf("   Protocol            : %u \n",(unsigned short)eth->h_proto);
  }

void print_ip_header(unsigned char* Buffer, int Size)
  {
  unsigned short iphdrlen;
  struct iphdr *iph = (struct iphdr *)(Buffer  + sizeof(struct ethhdr) );

  print_ethernet_header(Buffer, Size);
  iphdrlen =iph->ihl*4;

  memset(&source, 0, sizeof(source));
  source.sin_addr.s_addr = iph->saddr;

  memset(&dest, 0, sizeof(dest));
  dest.sin_addr.s_addr = iph->daddr;

  printf("\n");
  printf("IP Header\n");
  printf("   IP Version           : %d\n",(unsigned int)iph->version);
  printf("   IP Header Length     : %d DWORDS or %d Bytes\n",
         (unsigned int)iph->ihl,((unsigned int)(iph->ihl))*4);
  printf("   Type Of Service      : %d\n",(unsigned int)iph->tos);
  printf("   IP Total Length      : %d  Bytes(Size of Packet)\n",ntohs(iph->tot_len));
  printf("   Identification       : %d\n",ntohs(iph->id));
  printf("   TTL                  : %d\n",(unsigned int)iph->ttl);
  printf("   Protocol             : %d\n",(unsigned int)iph->protocol);
  printf("   Checksum             : %d\n",ntohs(iph->check));
  printf("   Source IP            : %s\n",inet_ntoa(source.sin_addr));
  printf("   Destination IP       : %s\n",inet_ntoa(dest.sin_addr));
  }

void print_tcp_packet(unsigned char* Buffer, int Size)
  {
  unsigned short iphdrlen;
  int header_size;
  struct iphdr *iph = (struct iphdr *)(Buffer  + sizeof(struct ethhdr) );
  iphdrlen = iph->ihl*4;
  struct tcphdr *tcph = (struct tcphdr*)(Buffer + iphdrlen + sizeof(struct ethhdr));
  header_size =  sizeof(struct ethhdr) + iphdrlen + tcph->doff*4;

  printf("\n\n======================= TCP-Paket ==========================\n");
  print_ip_header(Buffer,Size);

  printf("\n");
  printf("TCP Header\n");
  printf("   Source Port          : %u\n",ntohs(tcph->source));
  printf("   Destination Port     : %u\n",ntohs(tcph->dest));
  printf("   Sequence Number      : %u\n",ntohl(tcph->seq));
  printf("   Acknowledge Number   : %u\n",ntohl(tcph->ack_seq));
  printf("   Header Length        : %d DWORDS or %d BYTES\n" ,
         (unsigned int)tcph->doff,
         (unsigned int)tcph->doff*4);
  printf("   Urgent Flag          : %d\n",(unsigned int)tcph->urg);
  printf("   Acknowledgement Flag : %d\n",(unsigned int)tcph->ack);
  printf("   Push Flag            : %d\n",(unsigned int)tcph->psh);
  printf("   Reset Flag           : %d\n",(unsigned int)tcph->rst);
  printf("   Synchronise Flag     : %d\n",(unsigned int)tcph->syn);
  printf("   Finish Flag          : %d\n",(unsigned int)tcph->fin);
  printf("   Window               : %d\n",ntohs(tcph->window));
  printf("   Checksum             : %d\n",ntohs(tcph->check));
  printf("   Urgent Pointer       : %d\n",tcph->urg_ptr);

  dump_data (Buffer + header_size, Size - header_size);
  }

void print_udp_packet(unsigned char *Buffer , int Size)
  {
  unsigned short iphdrlen;
  int header_size;
  struct iphdr *iph = (struct iphdr *)(Buffer +  sizeof(struct ethhdr));
  iphdrlen = iph->ihl*4;
  struct udphdr *udph = (struct udphdr*)(Buffer + iphdrlen  + sizeof(struct ethhdr));
  header_size = sizeof(struct ethhdr) + iphdrlen + sizeof udph;

  printf("\n\n======================= UDP-Paket ==========================\n");

  print_ip_header(Buffer,Size);

  printf("\nUDP Header\n");
  printf("   Source Port            : %d\n" , ntohs(udph->source));
  printf("   Destination Port       : %d\n" , ntohs(udph->dest));
  printf("   UDP Length             : %d\n" , ntohs(udph->len));
  printf("   UDP Checksum           : %d\n" , ntohs(udph->check));

  dump_data (Buffer + header_size, Size - header_size);
  }

void print_icmp_packet(unsigned char* Buffer, int Size)
  {
  unsigned short iphdrlen;
  int header_size;
  struct iphdr *iph = (struct iphdr *)(Buffer  + sizeof(struct ethhdr));
  iphdrlen = iph->ihl * 4;
  struct icmphdr *icmph = (struct icmphdr *)(Buffer + iphdrlen  + sizeof(struct ethhdr));
  header_size = sizeof(struct ethhdr) + iphdrlen + sizeof icmph;

  printf("\n\n======================= ICMP-Paket =========================\n");

  print_ip_header(Buffer , Size);

  printf("\nICMP Header\n");
  printf("   Type                   : %d",(unsigned int)(icmph->type));

  if((unsigned int)(icmph->type) == 11)
    { printf("  (TTL Expired)\n"); }
  else if((unsigned int)(icmph->type) == ICMP_ECHOREPLY)
    { printf("  (ICMP Echo Reply)\n"); }

  printf("   Code                   : %d\n",(unsigned int)(icmph->code));
  printf("   Checksum               : %d\n",ntohs(icmph->checksum));

  dump_data (Buffer + header_size, Size - header_size);
  }


void dump_data (unsigned char* addr, int len)
  {
  int i;
  unsigned char buff[17];
  unsigned char *pc = (unsigned char*)addr;

  printf("\n- - - - - - - - - - - - Daten-Dump - - - - - - - - - - - - -\n");

  for (i = 0; i < len; i++)
    {
    /* alle 16 Werte eine neue Zeile */
    if ((i % 16) == 0)
      {
      if (i != 0) /* nicht bei der ersten Zeile */
        printf ("  %s\n", buff);
      printf ("  %04x ", i); /* Offset ausgeben */
      }
    printf(" %02x", pc[i]); /* Hexausgabe, ASCCI fuer spaeter speichern */
    if ((pc[i] < 32) || (pc[i] > 127))
      buff[i % 16] = '.';
    else
      buff[i % 16] = pc[i];
    buff[(i % 16) + 1] = '\0';
    }
  /* Rest des Puffers in der letzten Zeile ausgeben */
  while ((i % 16) != 0)
    {
    printf ("   ");
    i++;
    }
  printf ("  %s\n", buff);
  }


void beenden(int dummy)  /* STRG-C behandeln */
  { go = 0; }

