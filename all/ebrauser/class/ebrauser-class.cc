#include "cxschachbrett.h"
#include "cend.h"

int main (int argc, char** argv)
  {
  if (argc != 2)
    return 0;
  cend steiner;
///*
  steiner.initfiguren (1, -1, 12, -8);
//  steiner.testdieder ();
  steiner.analysiere ();
  steiner.getextrempos ();
  steiner.saveendspiel ("/mnt/smb-extra/Endspiel/test.end");
//*/
//  steiner.ladeendspiel (argv[1]);
  steiner.brauseendspiel (steiner.maxposw);
  return 0;
  }
