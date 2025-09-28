#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void empfangeudp ()
  {
  int sock= socket (AF_INET, SOCK_DGRAM, 0);
  printf ("socket: %d\n", sock);
  sockaddr_in laddr;
  bzero (&laddr, sizeof (laddr));
  laddr.sin_family= AF_INET;
  laddr.sin_addr.s_addr= htonl (INADDR_ANY);
//  laddr.sin_port= htons (7593);
  laddr.sin_port= htons (7593);
  unsigned long bindok= bind (sock, (sockaddr*) &laddr, sizeof (laddr));
  printf ("bind: %ld\n", bindok);
  char* puffer= new char[10000];
  unsigned long packets= 0;
  while (1)
    {   
    printf ("\n");
    sockaddr_in fromaddr;
    socklen_t fromaddrlen;
    unsigned long result= recvfrom (sock, puffer, 10000, 0, (sockaddr*) &fromaddr, &fromaddrlen);
    printf ("recvfrom: %10ld packets: %10ld\n", result, packets);
    char* ipaddr= inet_ntoa (fromaddr.sin_addr);
    printf ("ipfrom: ");
    printf ("%s", ipaddr);
    printf ("\n");
    packets++;
    printf ("%s", puffer);
    printf ("\n");
    }
  }

int main ()
  {
  empfangeudp ();
  return 0;
  }