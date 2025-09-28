#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <time.h>

void sendeudp ()
  {
  int sock = socket (AF_INET, SOCK_DGRAM, 0);
  sockaddr_in toaddr1;
  bzero (&toaddr1, sizeof (toaddr1));
  toaddr1.sin_family= AF_INET;
  toaddr1.sin_port= htons (7593);  
  char ip1[20]= "130.149.11.6";
  inet_aton (ip1 , &toaddr1.sin_addr);
  time_t sectime;
  tm* loctime;
  while (1)
    {
    time (&sectime);
    loctime= localtime (&sectime);
    printf ("h: %3d m: %3d\n", loctime->tm_hour, loctime->tm_min);
    sendto (sock, "on!!", 5, 0, (sockaddr*) &toaddr1, sizeof (toaddr1));
    sleep (1);
    }
  }

int main ()
  {
  sendeudp ();
  return 0;
  }
