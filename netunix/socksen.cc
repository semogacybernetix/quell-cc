#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
//#include <pcap.h>

void sendeudp (char* pipaddr, char* pmessage, char* plaenge)
  {
  signed long laenge= 0;
  sscanf (plaenge, "%ld", &laenge);

  int sock = socket (AF_INET, SOCK_DGRAM, 0);
  printf ("socket: %d\n", sock);
  sockaddr_in toaddr;
  bzero (&toaddr, sizeof (toaddr));
  toaddr.sin_family= AF_INET;
  if (!inet_aton (pipaddr, &toaddr.sin_addr))
    printf ("fehlerhafte IP-Adresse\n");
  toaddr.sin_port= htons (6666);  
  signed long packetnr= 1;
  while (1)
    {
    long int result = sendto (sock, pmessage, laenge, 0, (sockaddr*) &toaddr, sizeof (toaddr));
    if  (result == -1)
      perror ("fehler");
    printf ("Paketlänge[Bytes]: %10ld  Paketnummer: %10ld\n", result, packetnr);
    usleep (1e6);
    packetnr++;
    }
  }

int main (int argc, char** argv)
  {
  if (argc != 4)
    return 0;
  sendeudp (argv[1], argv[2], argv[3]);
  return 0;
  }
