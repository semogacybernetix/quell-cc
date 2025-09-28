#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <sys/times.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/stat.h>

using namespace std;

int createsocket (char* pipaddr)
  {
  sockaddr_in localaddr, peeraddr;
  int retsk;
  bzero (&localaddr, sizeof (localaddr));
  localaddr.sin_family= AF_INET;
  localaddr.sin_port= htons (6006);
  localaddr.sin_addr.s_addr= INADDR_ANY;
  bzero (&peeraddr, sizeof (peeraddr));
  peeraddr.sin_family= AF_INET;
  peeraddr.sin_port= htons (6006);
  if (!inet_aton (pipaddr, &peeraddr.sin_addr))
    {
    cout << "fehlerhafte IP-Adresse" << endl;
    exit (0);
    }
  cout << "peer: " << inet_ntoa (peeraddr.sin_addr) << endl;
  retsk= socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (retsk == -1)
    {
    perror ("Socket konnte nicht angelegt werden");
    exit (0);
    }
  cout << "Socket: " << retsk << endl;
  int bnd= bind (retsk, (sockaddr*) &localaddr, sizeof (localaddr));
  if (bnd == -1)
    {
    perror ("bind fehlgeschlagen");
    exit (0);
    }
  int conn= connect (retsk, (sockaddr*) &peeraddr, sizeof (peeraddr));
  if (conn == -1)
    {
    perror ("Fehler bei connect");
    exit (0);
    }
  return retsk;
  }
  
int              gsksend;

bool             ginfo= false;
unsigned long    gfilepacketanz;
char*            gfilename;

unsigned long    glosslist[256];
unsigned long    glosslistanz= 0;
pthread_mutex_t  glosslistmutex= PTHREAD_MUTEX_INITIALIZER;

void* sendeinfopacket (void* pargs)
  {
  unsigned long infopacket[128];
  infopacket[0]= htonl (0xffffffff);
  infopacket[1]= htonl (gfilepacketanz);
  strcpy ((char*) &infopacket[2], gfilename);
  while (!ginfo)
    {
    write (gsksend, infopacket, 512);
    cout << "Sende Info Packet  " << gfilepacketanz << "\n";
    usleep (100000);
    }
  return NULL;
  }

void empfangeinfobestaetigung ()
  {
  int rsize;
  unsigned long empbuffer[256];
    do
    rsize= read (gsksend, empbuffer, 1024);
  while (rsize != 16);
  ginfo= true;
  cout << "Infobestaetigung empfangen" << endl;
  }

void* empfangeliste (void* pargs)
  {
  unsigned long empbuffer[256];
  signed long empsize;
  unsigned long empanz;
  while (1)
    {
    empsize= read (gsksend, empbuffer, 1024);
    if (empsize == -1)
      {
      perror ("Fehler bei Listenempfang");
      exit (0);
      }
    empanz= empsize/4;
    cout << "empfange Liste: " << empanz << " packets" << endl;
    pthread_mutex_lock (&glosslistmutex);
    glosslistanz= empanz;
    for (unsigned long llauf= 0; llauf < empanz; llauf++)
      glosslist[llauf]= ntohl (empbuffer[llauf]);
    pthread_mutex_unlock (&glosslistmutex);
    }
  return NULL;
  }
  
void sendfile (char* pname, char* pipaddr, unsigned long pdatarate)
  {
  unsigned long datarate= pdatarate;
  gsksend= createsocket (pipaddr);
  struct stat filestat;
  stat (pname, &filestat);
  gfilepacketanz= filestat.st_size/1024 + 1;
  gfilename= pname;
  FILE* datei= fopen (pname, "rb");
  if (!datei)
    {
    perror ("Datei konnte nicht geoeffnet werden");
    exit (0);
    }
  pthread_t tid;
  int thr;
  thr= pthread_create (&tid, NULL, sendeinfopacket, NULL);
  if (thr)
    {
    cout << "Thread sendeinfopacket konnte nicht erzeugt werden" << endl;
    exit (0);
    }
  empfangeinfobestaetigung ();
  thr= pthread_create (&tid, NULL, empfangeliste, NULL);
  if (thr)
    {
    cout << "Thread empfangeliste fehlgeschlagen" << endl;
    exit (0);
    }
  unsigned long packetnr= 0;
  tms zeit;
  unsigned long ticksps= sysconf (_SC_CLK_TCK);
  cout << "Ticks: " << ticksps << endl;
  signed long frame= times (&zeit) + 120;
  frame = frame/100*100;
  signed long sendframe= frame;
  unsigned long sendbuffer[257];
  do
    {
    while (times (&zeit) < frame);
    if (glosslistanz > 0)
      {
      pthread_mutex_lock (&glosslistmutex);
      unsigned long lostpacketnr= glosslist[0];
      for (signed long llauf= 0; llauf < (signed) glosslistanz - 1; llauf++)
        glosslist[llauf]= glosslist[llauf + 1];
      glosslistanz--;
      pthread_mutex_unlock (&glosslistmutex);
      sendbuffer[0]= htonl (lostpacketnr);
      fseek (datei, 1024*lostpacketnr, SEEK_SET);
      int fr= fread (&sendbuffer[1], 1, 1024, datei);
      if (times (&zeit) > frame)
        usleep (5000);
      write (gsksend, sendbuffer, 4 + fr);
      cout << "sending lost packet:  " << lostpacketnr << endl;
      }
  else
    if ((sendframe <= frame) && (packetnr < gfilepacketanz))
      {
      sendbuffer[0]= htonl (packetnr);
      fseek (datei, 1024*packetnr, SEEK_SET);
      int blkgr= fread (&sendbuffer[1], 1, 1024, datei);
      if (times (&zeit) > frame)
        usleep (5000);
      write (gsksend, sendbuffer, 4 + blkgr);
      cout << packetnr << endl;
      packetnr++;
      sendframe+= datarate;
      }
    frame+= 1;
    if (times (&zeit) >= frame)
      cout << "Frameerror " << 1 + times (&zeit) - frame << endl;
    }
  while ((packetnr < gfilepacketanz) || (glosslistanz > 0) || (frame < sendframe + 500));
  fclose (datei);
  }

int main (int argc, char** argv)
  {
  if (argc != 4)
    {
    cout << "filesen <file> <IP-Adresse> <Transferrate> " << endl;
    exit (0);
    }
  unsigned long datarate;
  sscanf (argv[3], "%lu", &datarate);
  sendfile (argv[1], argv[2], datarate);
  return 0;
  }
