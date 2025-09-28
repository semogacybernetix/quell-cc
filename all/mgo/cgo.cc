#include "xgo.h"

#include <cstdio>

void bewertefile (int argc, char** argv)
  {
  if (argc != 2)
    {
    printf ("cgo <Gostellungsdatei>\n");
    return;
    }
  cgoanalyse goanalyse (argv[1]);
  goanalyse.c_addstellungen ();
  printf ("Stellungen: %lu\n\n", goanalyse.c_anzstellungen);
  goanalyse.c_bewertealles ();
  cxgobrauser xgobrauser;
  xgobrauser.c_brause (goanalyse);
  }

int main (int argc, char** argv)
  {
  bewertefile (argc, argv);
  return 0;
  }
