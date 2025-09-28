#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
//#include <pcap.h>

void reflektiereudp (char* pipaddr, char* pmessage)
  {
  printf ("%s", pmessage);
  int sockemp= socket (AF_INET, SOCK_DGRAM, 0);
  int socksen = socket (AF_INET, SOCK_DGRAM, 0);
  printf ("socket: %d\n", sockemp);
  printf ("socket: %d\n", socksen);
  sockaddr_in laddr;
  sockaddr_in toaddr;
  bzero (&laddr, sizeof (laddr));
  bzero (&toaddr, sizeof (toaddr));
  laddr.sin_family= AF_INET;
  laddr.sin_addr.s_addr= htonl (INADDR_ANY);
  laddr.sin_port= htons (1025);
  signed long bindok= bind (sockemp, (sockaddr*) &laddr, sizeof (laddr));
  printf ("bind: %ld\n", bindok);
  char* puffer= new char[10000];
  toaddr.sin_family= AF_INET;
  if (!inet_aton (pipaddr, &toaddr.sin_addr))
    printf ("fehlerhafte IP-Adresse\n");
  toaddr.sin_port= htons (1025);  
  signed long packets= 0;
  signed long result;
  char* daten[10000];
  result = sendto (socksen, daten, 1472, 0, (sockaddr*) &toaddr, sizeof (toaddr));
  if  (result == -1)
      perror ("fehler");
  sockaddr_in fromaddr;
  socklen_t fromaddrlen;
  while (1)
    {   
    //printf ("\n");
    result= recvfrom (sockemp, puffer, 10000, 0, (sockaddr*) &fromaddr, &fromaddrlen);
    //printf ("recvfrom: %10ld packets: %10ld\n", result, packets);
    //char* ipaddr= inet_ntoa (fromaddr.sin_addr);
    //printf ("ipfrom: ");
    //printf (ipaddr);
    //printf ("\n");
    packets++;
    //printf (puffer);
    //printf ("\n");

    result = sendto (socksen, daten, 1472, 0, (sockaddr*) &toaddr, sizeof (toaddr));
    if  (result == -1)
        perror ("fehler");
    //printf ("sendto: %10ld  send: %10ld\n", result, packets);
    }
  }

int main (int argc, char** argv)
  {
  if (argc != 3)
    return 0;
  reflektiereudp (argv[1], argv[2]);
  return 0;
  }
