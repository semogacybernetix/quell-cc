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

using namespace std;

struct cliste
  {
  unsigned long *data, *stdata;
  unsigned long maxanz, anz;
  unsigned long stamp;

  cliste (unsigned long panz)
    : maxanz (panz), anz (0), stamp (0)
    {
    data= new unsigned long[maxanz];
    stdata= new unsigned long[maxanz];
    }
  
  ~cliste ()
    {
    delete [] data;
    }
  
  unsigned long getpos (unsigned long pwert)
    {
    unsigned long nwert= htonl (pwert);
    for (unsigned long lnr= 0; lnr < anz; lnr++)
      if (data[lnr] == nwert)
	return lnr;
    return 0xffffffff;
    }
  
  void delnr (unsigned long pnr)
    {
    for (unsigned long lnr= pnr; lnr < anz - 1; lnr++)
      {  
      data[lnr]= data[lnr + 1];
      stdata[lnr]= stdata[lnr + 1];
      }
    anz--;
    }
  
  void insert (unsigned long pwert)
    {
    if (getpos (pwert) != 0xffffffff)
      return;
    if (anz == maxanz)
      {
      cout << "Liste uebergeflossen" << endl;
      exit (0);
      }
    data[anz]= htonl (pwert);
    stdata[anz]= stamp;
    anz++;
    }
  
  void erase (unsigned long pwert)
    {
    unsigned long wpos= getpos (pwert);
    if (wpos == 0xffffffff)
      return;
    delnr (wpos);
    }
  
  unsigned long stanz ()
    {
    unsigned long ret= 0;
    while (stdata[ret] < stamp - 2)
      ret++;
    return ret;
    }
  };

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
  
int              gskemp;
FILE*            gdatei;
unsigned long    gfilepacketanz;
char             gfilename[256];
cliste*          glossliste;
pthread_mutex_t  glosslistmutex= PTHREAD_MUTEX_INITIALIZER;

void* sendeliste (void*)
  {
  unsigned long losslisteanz;
  unsigned long lossliste[256];
  while (1)
    {
    pthread_mutex_lock (&glosslistmutex);
    losslisteanz= glossliste->anz;
    memcpy (lossliste, glossliste->data, losslisteanz*4);
    pthread_mutex_unlock (&glosslistmutex);
    if (losslisteanz > 0)
      {
      write (gskemp, lossliste, losslisteanz*4);
      cout << "sending list: " << losslisteanz << " packets" << endl;
      }
    usleep (1000000);
    }
  return NULL;
  }
  
void handshake ()
  {
  unsigned long empbuffer[1024];
  int rd;
    do
    {
    rd= read (gskemp, empbuffer, 1024);
    if (rd == -1)
      {
      perror ("Empfangen Infopacket");
      exit (0);
      }
    }
  while ((rd != 512) || (empbuffer[0] != ntohl (0xffffffff)));
  gfilepacketanz= ntohl (empbuffer[1]);
  strcpy (gfilename, (char*) &empbuffer[2]);
  cout << "Info: " << gfilename << "  " << gfilepacketanz << endl;
  rd= write (gskemp, empbuffer, 16);
  if (rd == -1)
    {
    perror ("Senden Infopacketbestaetigung");
    exit (0);
    }
  cout << "Sende Info-Bestaetigung Handshake\n";
  }

void empfile (char* pipaddr)
  {
  unsigned long empbuffer[1024];
  glossliste= new cliste (256);
  gskemp= createsocket (pipaddr);
  handshake ();
  gdatei= fopen (gfilename, "wb");
  if (!gdatei)
    {
    perror ("Datei oeffnen");
    exit (0);
    }
  pthread_t tid;
  int thr;
  thr= pthread_create (&tid, NULL, sendeliste, NULL);
  if (thr)
    {
    cout << "Thread sendeliste konnte nicht erzeugt werden" << endl;
    exit (0);
    }
  unsigned long maxpos= 0;
  while ((maxpos < gfilepacketanz) || (glossliste->anz > 0))
    {
    int psize= read (gskemp, empbuffer, 4096);
    if (psize == -1)
      {
      perror ("Fehler bei Paketempfang");
      exit (0);
      }
    unsigned long packetnr= ntohl (empbuffer[0]);
    cout << packetnr << "  " << psize;
    if (packetnr == 0xffffffff)
      {
/*
      if (write (gskemp, empbuffer, 16))
        {
        perror ("Senden Infopacketbestaetigung");
        exit (0);
        }
*/
      cout << " Info, Sende Info-Bestaetigung innen" << endl;
      continue;
      }
    if (packetnr < maxpos)
      {
      cout << " againfound ";
      pthread_mutex_lock (&glosslistmutex);
      if (glossliste->getpos (packetnr) != 0xffffffff)
        {
        glossliste->erase (packetnr);
        pthread_mutex_unlock (&glosslistmutex);
        fseek (gdatei, 1024*packetnr, SEEK_SET);
        fwrite (&empbuffer[1], 1, psize - 4, gdatei);
	}
        else
        {
        pthread_mutex_unlock (&glosslistmutex);
        cout << "double";
        }
      cout << endl;
      continue;
      }
    if (packetnr > maxpos)
      {
      cout << " packetloss "  << packetnr - maxpos << endl;
      fseek (gdatei, 1024*packetnr, SEEK_SET);
      fwrite (&empbuffer[1], 1, psize - 4, gdatei);
      pthread_mutex_lock (&glosslistmutex);
      for (unsigned long lpack= maxpos; lpack < packetnr; lpack++)
        glossliste->insert (lpack);
      glossliste->stamp++;
      pthread_mutex_unlock (&glosslistmutex);
      maxpos= packetnr + 1;
      continue;
      }
    if (packetnr == maxpos)
      {
      cout << endl;
      fseek (gdatei, 1024*packetnr, SEEK_SET);
      fwrite (&empbuffer[1], 1, psize - 4, gdatei);
      maxpos= packetnr + 1;
      continue;
      }
    }
  cout << "Lost Segments: " << glossliste->stamp << endl;
  fclose (gdatei);
  exit (0);
  }

int main (int argc, char** argv)
  {
  if (argc != 2)
    {
    cout << "fileemp <IP-Adresse>" << endl;
    exit (0);
    }
  empfile (argv[1]);
  return 0;
  }
