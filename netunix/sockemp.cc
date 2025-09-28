#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void empfangeudp ()
  {
  int sock= socket (AF_INET, SOCK_DGRAM, 0);
  sockaddr_in laddr;
  bzero (&laddr, sizeof (laddr));
  laddr.sin_family= AF_INET;
  laddr.sin_addr.s_addr= htonl (INADDR_ANY);
  laddr.sin_port= htons (6666);
  signed long bindok= bind (sock, (sockaddr*) &laddr, sizeof (laddr));

  printf ("socket: %d\n", sock);
  printf ("bind:   %ld\n", bindok);
  
  char* puffer= new char[10000];
  signed long packetnr= 1;
  sockaddr_in fromaddr;
  socklen_t fromaddrlen;
  while (1)
    {   
    unsigned long result= recvfrom (sock, puffer, 10000, 0, (sockaddr*) &fromaddr, &fromaddrlen);

    printf ("\n");
    printf ("Paketnummer: %11ld\n", packetnr);
    printf ("Paketlänge:  %11ld\n", result);
    char* ipaddr= inet_ntoa (fromaddr.sin_addr);
    printf ("Absender:       %s\n", ipaddr);
    printf ("Nachricht:      %s\n", puffer);
    packetnr++;
    }
  }

int main ()
  {
  empfangeudp ();
  return 0;
  }
