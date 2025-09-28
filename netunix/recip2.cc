#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

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
  sockaddr_in fromaddr;
  socklen_t fromaddrlen;
  while (1)
    {   
    unsigned long result= recvfrom (sock, puffer, 10000, 0, (sockaddr*) &fromaddr, &fromaddrlen);
    FILE* datei= fopen ("on.txt", "a");
    fprintf (datei, "\n");
    time_t sectime;
    time (&sectime);
    tm* loctime;
    loctime= localtime (&sectime);
    fprintf (datei, "%02d.%02d. %2d:%2d\n", loctime->tm_mday, loctime->tm_mon + 1, loctime->tm_hour, loctime->tm_min);
    fprintf (datei, "recvfrom: %10ld packets: %10ld\n", result, packets);
    char* ipaddr= inet_ntoa (fromaddr.sin_addr);
    fprintf (datei, "ipfrom: ");
    fprintf (datei, "%s", ipaddr);
    fprintf (datei, "\n");
    packets++;
    fprintf (datei, "%s", puffer);
    fprintf (datei, "\n");
    fclose (datei);
    }
  }

int main ()
  {
  empfangeudp ();
  return 0;
  }