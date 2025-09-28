#include <stdio.h>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

void sendeudp ()
  {
  int sock = socket (AF_INET, SOCK_DGRAM, 0);
  sockaddr_in toaddr1, toaddr2;
  bzero (&toaddr1, sizeof (toaddr1));
  toaddr1.sin_family= AF_INET;
  toaddr1.sin_port= htons (7593);  
  char ip1[20]= "130.149.11.6";
  inet_aton (ip1 , &toaddr1.sin_addr);
  memcpy (&toaddr2, &toaddr1, sizeof (toaddr2));
  char ip2[20]= "130.149.5.227";
  inet_aton (ip2 , &toaddr2.sin_addr);
  sendto (sock, "on!!", 5, 0, (sockaddr*) &toaddr1, sizeof (toaddr1));
  sleep (5);
  for (unsigned long plauf= 0; plauf < 10; plauf++)
    {
    sendto (sock, "on!!", 5, 0, (sockaddr*) &toaddr1, sizeof (toaddr1));
    sendto (sock, "on!!", 5, 0, (sockaddr*) &toaddr2, sizeof (toaddr2));
    usleep (100000);
    }
  }

int main ()
  {
  sendeudp ();
  return 0;
  }
